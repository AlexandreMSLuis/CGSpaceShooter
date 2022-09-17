#pragma once
#include "Sistema.h"

class Menu
{
private:
    GLuint menuRenderID;
    std::string backgroundTextureFilePath, textMenuTextureFilePath;
    unsigned char* menuBuffer;
    GLint width, height, bpp;
    GLfloat textWidth, textHeight;
    //variables used to get the center of the screen
    GLfloat centerX = (worldCoordinates[0] + worldCoordinates[1]) / 2;
    GLfloat centerY = (worldCoordinates[2] + worldCoordinates[3]) / 2;

    GLvoid loadImage(std::string filePath);
    GLvoid createBackground();
    GLvoid createMenuText();

public:
    Menu();
    GLvoid draw(GLint);
    ~Menu();    
};