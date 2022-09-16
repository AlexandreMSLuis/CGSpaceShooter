#pragma once
#include "Sistema.h"

class Ship
{
private:
    GLfloat currentPosition[2],
        speed[2],
        size[2];
    GLuint shipRenderID;
    std::string shipTextureFilePath;
    unsigned char* shipBuffer;
    GLint width, height, bpp;
    GLvoid body(GLvoid);

public:
    Ship(GLfloat*);

    //GLvoid draw();
    GLvoid draw();
    GLboolean move(GLint);
    GLfloat* getPosition();
    GLfloat* getSize();

    ~Ship();
};
