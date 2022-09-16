#pragma once
#include "Sistema.h"

class Enemy
{
private:
    GLfloat currentPosition[2],
        speed[2],
        size[2],
        color[3];
    //texture variabales
    GLuint enemyRenderID;
    std::string enemyTextureFilePath;
    unsigned char* enemyBuffer;
    GLint width, height, bpp;
    GLvoid enemyBody(GLvoid);
public:
    Enemy(GLfloat, GLfloat, GLint);
    GLvoid draw();
    GLboolean move(GLint);
    GLfloat* getPosition();
    GLfloat* getSize();
    GLfloat* getColor();
    ~Enemy();
};
