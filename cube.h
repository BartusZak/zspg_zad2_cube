#ifndef CUBE_H
#define CUBE_H

#include "glfunctions.h"

#include "indexmodel.h"
#include "movablemodel.h"
#include "modelprogram.h"
#include "matma.h"

class Cube: public IndexModel, public MovableModel{
 public:
    Cube(GLfloat init_velocity=40, GLfloat init_angle=0);
    void SetInitAngle(GLfloat angle){angle_= angle;}
    void SetVelocity(GLfloat velocity){velocity_= velocity;}
    void Initialize();
    void Draw(ModelProgram & program);
    void Move(GLfloat delta_t);
    void SpeedUp();
    void SlowDown();
    void ToggleAnimated();
 private:
    GLfloat angle_;
    GLfloat velocity_;
    bool animated_;
};

#endif // CUBE_H
