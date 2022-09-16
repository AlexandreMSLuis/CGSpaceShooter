#pragma once
#include "Sistema.h"

class Life
{
private:
    GLfloat currentPosition[2],
        size[2];

    GLuint lifeRenderID;
    std::string lifeTextureFilePath;
    unsigned char* lifeBuffer;
    GLint width, height, bpp;

    GLvoid icon(GLvoid);

public:
    Life(GLfloat*);
    GLvoid draw();
    GLfloat* getSize();
    ~Life();
};

