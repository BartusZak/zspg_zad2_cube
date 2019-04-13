#ifndef CAMERAPROGRAM_H
#define CAMERAPROGRAM_H

#include "glfunctions.h"

#include "baseprogram.h"
#include "matma.h"


class CameraProgram : public BaseProgram
{
public:
    void Initialize(const char* vertex_shader_file, const char* fragment_shader_file);
    void SetViewMatrix(const Mat4 &);
    void SetProjectionMatrix(const Mat4 &);
private:
    GLint projection_matrix_location_;
    GLint view_matrix_location_;
};

#endif // CAMERAPROGRAM_H
