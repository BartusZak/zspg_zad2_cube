#include "matma.h"

#include <cmath>
#include <iostream>

using namespace std;

void Mat4::Log(){
    for (int i=0; i<16; i++){
        cout<<matrix_[i]<<' ';
        if(i % 4 == 3) cout<<endl;
    }
}

Mat4::Mat4(){// Unit matrix
    for (int i=0; i<16; i++) matrix_[i]=0;
    matrix_[0]=matrix_[5]=matrix_[10]=matrix_[15]=1;
}

void Mat4::SetUnitMatrix(){// Unit matrix
    for (int i=0; i<16; i++) matrix_[i]=0;
    matrix_[0]=matrix_[5]=matrix_[10]=matrix_[15]=1;
}

void Mat4::MultiplyBy(const Mat4 & m2){
    GLfloat new_matrix[16];
    unsigned int row, column, row_offset;

    for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4)
        for (column = 0; column < 4; ++column)
            new_matrix[row_offset + column] =
                (matrix_[row_offset + 0] * m2.matrix_[column + 0]) +
                (matrix_[row_offset + 1] * m2.matrix_[column + 4]) +
                (matrix_[row_offset + 2] * m2.matrix_[column + 8]) +
                (matrix_[row_offset + 3] * m2.matrix_[column + 12]);
    for (int i=0; i<16; i++) matrix_[i]=new_matrix[i];
}

void Mat4::Scale(GLfloat x, GLfloat y, GLfloat z){
    Mat4 scale;

    scale.matrix_[0] = x;
    scale.matrix_[5] = y;
    scale.matrix_[10] = z;

    MultiplyBy(scale);
}

void Mat4::Translate(GLfloat x, GLfloat y, GLfloat z){
    Mat4 translate;

    translate.matrix_[12] = x;
    translate.matrix_[13] = y;
    translate.matrix_[14] = z;

    MultiplyBy(translate);
}

void Mat4::RotateAboutX(GLfloat degrees){
    Mat4 rotation;
    GLfloat radians=degrees*static_cast<GLfloat>(M_PI)/180.0f;
    GLfloat sine = static_cast<GLfloat>(sin(radians));
    GLfloat cosine = static_cast<GLfloat>(cos(radians));

    rotation.matrix_[5] = cosine;
    rotation.matrix_[6] = sine;
    rotation.matrix_[9] = -sine;
    rotation.matrix_[10] = cosine;

    MultiplyBy(rotation);
}

void Mat4::RotateAboutY(GLfloat degrees){
    Mat4 rotation;
    GLfloat radians=degrees*static_cast<GLfloat>(M_PI)/180.0f;
    GLfloat sine = static_cast<GLfloat>(sin(radians));
    GLfloat cosine = static_cast<GLfloat>(cos(radians));

    rotation.matrix_[0] = cosine;
    rotation.matrix_[2] = -sine;
    rotation.matrix_[8] = sine;
    rotation.matrix_[10] = cosine;

    MultiplyBy(rotation);
}

void Mat4::RotateAboutZ(GLfloat degrees){
    Mat4 rotation;
    GLfloat radians=degrees*static_cast<GLfloat>(M_PI)/180.0f;
    GLfloat sine = static_cast<GLfloat>(sin(radians));
    GLfloat cosine = static_cast<GLfloat>(cos(radians));

    rotation.matrix_[0] = cosine;
    rotation.matrix_[1] = sine;
    rotation.matrix_[4] = -sine;
    rotation.matrix_[5] = cosine;

    MultiplyBy(rotation);
}

Mat4 Mat4::CreateProjectionMatrix(
        GLfloat fovy, GLfloat aspect_ratio,
        GLfloat near_plane, GLfloat far_plane){
    Mat4 out(0);

    GLfloat y_scale = 1.0f/tan(fovy * static_cast<GLfloat>(M_PI) / 360.0f );
    GLfloat x_scale = y_scale / aspect_ratio;
    GLfloat frustum_length = far_plane - near_plane;

    out.matrix_[0] = x_scale;
    out.matrix_[5] = y_scale;
    out.matrix_[10] = -((far_plane + near_plane) / frustum_length);
    out.matrix_[11] = -1;
    out.matrix_[14] = -((2 * near_plane * far_plane) / frustum_length);

    return out;
}

Mat4 Mat4::CreatePerpendicularViewMatrix(
        GLfloat left, GLfloat right,
        GLfloat bottom, GLfloat top,
        GLfloat n, GLfloat f){
    Mat4 out(0);

    out.matrix_[0] = 2 / (right - left);
    out.matrix_[3] = -(right + left) / (right - left);
    out.matrix_[5] = 2 / (top - bottom);
    out.matrix_[7] = -(top + bottom) / (top - bottom);
    out.matrix_[10] = -(2 / (f - n));
    out.matrix_[11] = -(f + n) / (f - n);
    out.matrix_[15] = 1;

    return out;
}
Mat4::Mat4(GLfloat val){
    for(int i=0; i<16; i++){
        matrix_[i]=val;
    }
}
