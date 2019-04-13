#ifndef INDEXMODEL_H
#define INDEXMODEL_H

#include "glfunctions.h"

class IndexModel: protected GLFunctions{
public:
    ~IndexModel();
protected:
    GLuint vao_;
    GLuint vertex_buffer_;
    GLuint index_buffer_;
};


#endif // INDEXMODEL_H
