#include "baseprogram.h"

#include<QCoreApplication>

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


void BaseProgram::Initialize(const char *vertex_shader_file, const char *fragment_shader_file){
    initializeOpenGLFunctions();

    vertex_shader_ = LoadAndCompileShaderOrDie(vertex_shader_file, GL_VERTEX_SHADER);

    fragment_shader_ = LoadAndCompileShaderOrDie(fragment_shader_file, GL_FRAGMENT_SHADER);

    program_ = LinkProgramOrDie(vertex_shader_, fragment_shader_);

    glUseProgram(program_);
}


GLuint BaseProgram::LinkProgramOrDie(GLuint vertex_shader, GLuint fragment_shader){
    GLuint new_program = glCreateProgram();
    glAttachShader(new_program, vertex_shader);
    glAttachShader(new_program, fragment_shader);
    glLinkProgram(new_program);

    GLint  linked;
    glGetProgramiv(new_program, GL_LINK_STATUS, &linked);
    if ( !linked ) {
        std::cerr << "Shader program failed to link" << std::endl;
        GLint  log_size;
        glGetProgramiv(new_program, GL_INFO_LOG_LENGTH, &log_size);
        char* log_msg = new char[static_cast<GLuint>(log_size)];
        glGetProgramInfoLog(new_program, log_size, nullptr, log_msg);
        std::cerr << log_msg << std::endl;
        delete [] log_msg;
        QCoreApplication::exit();
    }

    return new_program;
}

BaseProgram::~BaseProgram(){
    glUseProgram(0);

    glDetachShader(program_, vertex_shader_);
    glDetachShader(program_, fragment_shader_);

    glDeleteShader(fragment_shader_);
    glDeleteShader(vertex_shader_);

    glDeleteProgram(program_);

}

GLuint BaseProgram::LoadAndCompileShaderOrDie(const char * source_file, GLenum type){
    long int file_size;
    char * shader_code;
    GLuint shader=glCreateShader(type);
    ifstream file (source_file, ios::in|ios::ate|ios::binary);
    if (file.is_open()) {
        file_size = file.tellg();
        shader_code = new char [file_size+1];
        file.seekg (0, ios::beg);
        file.read (shader_code, file_size);
        shader_code[file_size]='\0';
        file.close();

        glShaderSource(shader, 1, static_cast<GLchar**>(&shader_code), nullptr);
        glCompileShader(shader);
        delete[] shader_code;

    }
    else{ //file was not opened
        cerr<<"Could not open the file "<<source_file<<endl;
        QCoreApplication::exit(EXIT_FAILURE);
    }

    GLint  compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        switch(type){
        case GL_VERTEX_SHADER:
            cerr << "vertex ";
        break;
        case GL_FRAGMENT_SHADER:
            cerr << "fragment ";
        break;
        }
        cerr << "shader is failed to compile:" << endl;
        GLint  log_size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        char* log_msg = new char[log_size];
        glGetShaderInfoLog(shader, log_size, nullptr, log_msg);
        cerr << log_msg << endl;
        delete [] log_msg;
        QCoreApplication::exit(EXIT_FAILURE);
    }
    return shader;
}

GLint BaseProgram::GetUniformLocationOrDie(const char* var_name){
    GLint location=-1;
    location = glGetUniformLocation(program_, var_name);
    if (location < 0){
        cerr << "ERROR: cannot find uniform location " << var_name << endl;
        QCoreApplication::exit(EXIT_FAILURE);
    }
    return location;
}
