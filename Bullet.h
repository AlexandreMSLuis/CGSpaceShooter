#pragma once
#include "Sistema.h"

class Bullet {
private:
    GLfloat currentPosition[2],
        speed[2],
        size[2];
    GLint bulletDirection, bulletColor;

    //bullet Textures
    GLuint bulletRenderID;
    std::string bulletTextureFilePath;
    unsigned char* bulletBuffer;
    GLint width, height, bpp;

    //GLvoid head(GLvoid);
    //GLvoid tail(GLvoid);
    GLvoid shell(GLvoid);

public:
    Bullet(GLfloat*, GLfloat*, GLint, GLint);
    GLvoid draw(GLvoid);
    GLvoid move(GLvoid);
    GLfloat* getPosition(GLvoid);
    GLfloat* getSize(GLvoid);
    GLint getDirection(GLvoid);
    ~Bullet();
};
