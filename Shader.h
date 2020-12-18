//
//  Shader.h
//  3dGLFW
//
//  Created by Syritx on 2020-12-04.
//

#ifndef Shader_h
#define Shader_h

#include "libs.h"
#include <iostream>

class Shader {
public:
    GLuint program, vertexShader, fragmentShader;
    
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource) {
        
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);
        
        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        
        GLchar infoLog[1024];
        GLint success;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
            std::cout << infoLog << std::endl;
        }
    }
    
    void use_shader() {
        glUseProgram(program);
    }
    
    void set_mat4(int loc, mat4 &matrix) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
    }
    
    void set_vec3(int loc, vec3 &vec3d) {
        glUniform3fv(loc, 1, &vec3d[0]);
    }
};


#endif
