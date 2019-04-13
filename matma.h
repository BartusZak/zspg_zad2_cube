#ifndef MATMA_H
#define MATMA_H

#include "glfunctions.h"

#ifndef M_PI
    #define M_PI 3.14159265
#endif

class Mat4{
public:
    Mat4(); // Unit matrix
    operator const GLfloat* () const{return matrix_;}
    static Mat4 CreateProjectionMatrix(GLfloat fovy,
                                       GLfloat aspect_ratio,
                                       GLfloat near_plane,
                                       GLfloat far_plane);
    static Mat4 CreatePerpendicularViewMatrix(GLfloat left, GLfloat right,
                                              GLfloat bottom, GLfloat top,
                                              GLfloat n, GLfloat f);
    void RotateAboutX(GLfloat angle); //gedrees
    void RotateAboutY(GLfloat angle); //gedrees
    void RotateAboutZ(GLfloat angle); //gedrees
    void Scale(GLfloat x_scale, GLfloat y_scale, GLfloat z_scale);
    void Translate(GLfloat delta_x, GLfloat delta_y, GLfloat delta_z);
    void SetUnitMatrix();
    void Log();
private:
    GLfloat matrix_[16]; // column-major
    void MultiplyBy(const Mat4 &);
    explicit Mat4(GLfloat);
};


#endif // MATMA_H
