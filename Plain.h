//
//  Plain.h
//  3dGLFW
//
//  Created by Syritx on 2020-12-04.
//

#ifndef Plain_h
#define Plain_h

#include "libs.h"
#include "Shader.h"

#include <iostream>
#include <glm/gtc/noise.hpp>
using namespace std;

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 vertexPosition;"
"layout (location = 1) in vec3 aNormal;"
"out vec3 FragPos;"
"out vec3 Normal;"
"uniform mat4 mWorld;"
"uniform mat4 mView;"
"uniform mat4 mProj;"
"\n"
"void main()"
"{"
"    FragPos = vec3(mWorld * vec4(vertexPosition, 1.0));"
"    Normal = mat3(transpose(inverse(mWorld))) * aNormal;"
"    gl_Position = mProj * mView * vec4(FragPos, 1.0);"
"}";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;"
"in vec3 Normal;"
"in vec3 FragPos;"
"\n"
"uniform vec3 lightPos = vec3(100,100,100);"
"uniform vec3 viewPos = vec3(10, 50, 0);"
"uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);"
"uniform vec3 objectColor = vec3(1.0, 0.5, 0.31);"
"\n"
"void main()"
"{"
"    float ambientStrength = 0.1;"
"    vec3 ambient = ambientStrength * lightColor;"
"    vec3 norm = normalize(Normal);"
"    vec3 lightDir = normalize(lightPos - FragPos);"
"    float diff = max(dot(norm, lightDir), 0.0);"
"    vec3 diffuse = diff * lightColor;"
"    float specularStrength = 0.5;"
"    vec3 viewDir = normalize(viewPos - FragPos);"
"    vec3 reflectDir = reflect(-lightDir, norm);"
"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
"    vec3 specular = specularStrength * spec * lightColor;"
"    vec3 result = (ambient + diffuse + specular) * objectColor;"
"    FragColor = vec4(result, 1.0);"
"}";

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

int mapSize = 10;
float tileSize = 2.f;

float size = 10.5f;
int indicies_array_size;
float seed = (int)random() % 100000;

vec3 player_position = vec3(0,0,0);
perlin_noise n = perlin_noise();

float vertices[] = {
        -0.5f*size, -0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,
         0.5f*size, -0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,
         0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,
         0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,
        -0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,
        -0.5f*size, -0.5f*size, -0.5f*size,  0.0f,  0.0f, -1.0f,

        -0.5f*size, -0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,
         0.5f*size, -0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,
         0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,
         0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,
        -0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,
        -0.5f*size, -0.5f*size,  0.5f*size,  0.0f,  0.0f,  1.0f,

        -0.5f*size,  0.5f*size,  0.5f*size, -1.0f,  0.0f,  0.0f,
        -0.5f*size,  0.5f*size, -0.5f*size, -1.0f,  0.0f,  0.0f,
        -0.5f*size, -0.5f*size, -0.5f*size, -1.0f,  0.0f,  0.0f,
        -0.5f*size, -0.5f*size, -0.5f*size, -1.0f,  0.0f,  0.0f,
        -0.5f*size, -0.5f*size,  0.5f*size, -1.0f,  0.0f,  0.0f,
        -0.5f*size,  0.5f*size,  0.5f*size, -1.0f,  0.0f,  0.0f,

         0.5f*size,  0.5f*size,  0.5f*size,  1.0f,  0.0f,  0.0f,
         0.5f*size,  0.5f*size, -0.5f*size,  1.0f,  0.0f,  0.0f,
         0.5f*size, -0.5f*size, -0.5f*size,  1.0f,  0.0f,  0.0f,
         0.5f*size, -0.5f*size, -0.5f*size,  1.0f,  0.0f,  0.0f,
         0.5f*size, -0.5f*size,  0.5f*size,  1.0f,  0.0f,  0.0f,
         0.5f*size,  0.5f*size,  0.5f*size,  1.0f,  0.0f,  0.0f,

        -0.5f*size, -0.5f*size, -0.5f*size,  0.0f, -1.0f,  0.0f,
         0.5f*size, -0.5f*size, -0.5f*size,  0.0f, -1.0f,  0.0f,
         0.5f*size, -0.5f*size,  0.5f*size,  0.0f, -1.0f,  0.0f,
         0.5f*size, -0.5f*size,  0.5f*size,  0.0f, -1.0f,  0.0f,
        -0.5f*size, -0.5f*size,  0.5f*size,  0.0f, -1.0f,  0.0f,
        -0.5f*size, -0.5f*size, -0.5f*size,  0.0f, -1.0f,  0.0f,

        -0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  1.0f,  0.0f,
         0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  1.0f,  0.0f,
         0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  1.0f,  0.0f,
         0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  1.0f,  0.0f,
        -0.5f*size,  0.5f*size,  0.5f*size,  0.0f,  1.0f,  0.0f,
        -0.5f*size,  0.5f*size, -0.5f*size,  0.0f,  1.0f,  0.0f
    };

class Plain {
private:
    GLuint ibo, vbo, vao;
    float a = 1;
    
    float createNoiseLayer(int o, float l, float p, float x, float y, float seed) {
        
        float freq = 2,
        ampl = 15;
                
        float noise = 0;
        
        for (int i = 0; i < o; i++) {
            noise += n.noise(x*freq, y*freq, seed)*ampl;
            freq *= l;
            ampl *= p;
        }
        return noise;
    }
    
public:
    Shader shader = Shader(vertexShaderSource, fragmentShaderSource);
    
    Plain() {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        try {
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/sizeof(vertices[0]) * sizeof(float), vertices, GL_STATIC_DRAW);
        }
        catch (const exception& e ){
            cout << e.what();
        }
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float), nullptr);
        
        glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        BUFFER_OFFSET(3 * sizeof(float)));
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        shader.use_shader();
        
        int worldUniformLocation = glGetUniformLocation(shader.program, "mWorld"),
            viewUniformLocation = glGetUniformLocation(shader.program, "mView"),
            projectionUniformLocation = glGetUniformLocation(shader.program, "mProj");
        
        mat4 worldMatrix = mat4(1.0f);
        mat4 viewMatrix = lookAt(vec3(0,0,0), vec3(0,0,0), vec3(0,1,0));
        mat4 projection = perspective(radians(90.f), 1000.f/720.f, .1f, 2000.f);
        
        shader.set_mat4(worldUniformLocation, worldMatrix);
        shader.set_mat4(viewUniformLocation, viewMatrix);
        shader.set_mat4(projectionUniformLocation, projection);
    }
    
    void render(vec3 position, vec3 eye, vec3 up) {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.use_shader();
        
        int worldUniformLocation = glGetUniformLocation(shader.program, "mWorld"),
            viewUniformLocation = glGetUniformLocation(shader.program, "mView"),
            projectionUniformLocation = glGetUniformLocation(shader.program, "mProj");
        
        mat4 worldMatrix = mat4(1.0f);
        mat4 viewMatrix = lookAt(position, position+eye, up);
        mat4 projection = perspective(radians(90.f), 1000.f/720.f, .1f, 2000.f);
        
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        vec3 color = vec3(1, greenValue, 0);
                
        shader.set_vec3(glGetUniformLocation(shader.program, "viewPos"), position);
        shader.set_vec3(glGetUniformLocation(shader.program, "objectColor"), color);
        
        shader.set_mat4(worldUniformLocation, worldMatrix);
        shader.set_mat4(viewUniformLocation, viewMatrix);
        shader.set_mat4(projectionUniformLocation, projection);
        
        player_position = position;
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/sizeof(vertices[0]) * sizeof(float), vertices, GL_STATIC_DRAW);
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
};

#endif /* Plain_h */
