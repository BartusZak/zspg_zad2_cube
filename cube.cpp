#include <iostream>

#include "cube.h"
#include "vertices.h"

Cube::Cube(GLfloat init_velocity, GLfloat init_angle){
    velocity_ = init_velocity;
    angle_ = init_angle;
    animated_ = false;
}

void Cube::Move(){
}

void Cube::MoveLeft(){
 model_matrix_.RotateAboutY(-velocity_);
}

void Cube::MoveRight(){
 model_matrix_.RotateAboutY(velocity_);
}

void Cube::MoveUp(){
 model_matrix_.RotateAboutX(-velocity_);
}

void Cube::MoveDown(){
model_matrix_.RotateAboutX(velocity_);
}

void Cube::SpeedUp(){
    velocity_ *= 1.09544f;
}

void Cube::SlowDown(){
    velocity_ /= 1.09544f;
}

void Cube::ToggleAnimated(){
    animated_ = ! animated_;
}

const GLuint kIndices[52] =
{
  0,1,2,    0,2,7,  2,3,11, 9,11,2,
  3,11,5,   3,4,5,  0,1,10, 10,8,0,
  10,8,5,   5,4,10, 8,5,6,  6,5,9,
  6,7,8,    7,2,9,  7,6,9,  1,10,3,
  3,4,10
};

void Cube::Initialize(){
    initializeOpenGLFunctions();

    const ColorVertex kVertices[12] =
    {
        { { -.5f, -.5f,  .0f, 1.0f }, { 0, 1, 1, 1 } },
        { { -.5f, -.5f, -.5f, 1.0f }, { 1, 0, 1, 1 } },
        { {  .0f, -.5f, -.5f, 1.0f }, { 0, 1, 1, 1 } },
        { {  .5f, -.5f, -.5f, 1.0f }, { 1, 0, 1, 1 } },
        { {  .5f,  .5f, -.5f, 1.0f }, { 0, 1, 1, 1 } },
        { {  .5f,  .5f,  .0f, 1.0f }, { 1, 0, 1, 1 } },
        { {  .0f,  .5f,  .5f, 1.0f }, { 0, 1, 1, 1 } },
        { { -.5f,  .0f,  .0f, 1.0f }, { 1, 0, 1, 1 } },
        { { -.5f,  .5f,  .0f, 1.0f }, { 0, 1, 1, 1 } },
        { {  .5f,  .0f,  .0f, 1.0f }, { 1, 0, 1, 1 } },
        { { -.5f,  .5f, -.5f, 1.0f }, { 0, 1, 1, 1 } },
        { {  .5f, -.5f,  .0f, 1.0f }, { 1, 1, 0, 1 } }
    };

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices), kVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(kVertices[0]), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(kVertices[0]),
             reinterpret_cast<const GLvoid*>( sizeof(kVertices[0].position)) );
    glEnableVertexAttribArray(1);


    glGenBuffers(1, &index_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(kIndices), kIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void Cube::Draw(ModelProgram &program) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glUseProgram(program);
    glBindVertexArray(vao_);

    program.SetModelMatrix(model_matrix_);

    glDrawElements(GL_TRIANGLES, sizeof(kIndices), GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);
}
