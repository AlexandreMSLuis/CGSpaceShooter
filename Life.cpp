#include "Life.h"


Life::Life(GLfloat* pos) {
    currentPosition[0] = pos[0];
    currentPosition[1] = pos[1];

    //set ship dimentions
    size[0] = 2.0f;
    size[1] = 2.0f;

    //texture variables
    lifeRenderID = 0;
    lifeTextureFilePath = "Textures/playerLife.png";
    lifeBuffer = nullptr;
    width = 0;
    height = 0;
    bpp = 0;

    stbi_set_flip_vertically_on_load(1);

    lifeBuffer = stbi_load(lifeTextureFilePath.c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &lifeRenderID);
    glBindTexture(GL_TEXTURE_2D, lifeRenderID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, lifeBuffer);
}

GLvoid  Life::icon(GLvoid) {
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, lifeRenderID);

    glBegin(GL_QUADS); {
        glTexCoord2f(0.0, 0.0); glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0, 0.0); glVertex2f(size[0], 0.0f);
        glTexCoord2f(1.0, 1.0); glVertex2f(size[0], size[1]);
        glTexCoord2f(0.0, 1.0); glVertex2f(0.0f, size[1]);
    }glEnd();

    glDisable(GL_TEXTURE_2D);

    //unbinding the texture
    glBindTexture(GL_TEXTURE_2D, 0);

}


GLvoid Life::draw() {
    //Select the modelview Matrix
    glMatrixMode(GL_MODELVIEW);

    //Push the data on matrix - duplicate data
    glPushMatrix();

    //set object translation and save it on the stack
    glTranslatef(currentPosition[0] - (size[0] / 2), currentPosition[1] - (size[1] / 2), 0.0f);

    //Push the data on matrix - duplicate data
    glPushMatrix();

    //Draw de icon funcion
    icon();

    //restore matrix state with object translation
    glPopMatrix();

    //restore original modelview state - atention to this!!!
    glPopMatrix();

}

GLfloat* Life::getSize() {
    return size;
}

Life::~Life() {
    glDeleteTextures(0, &lifeRenderID);
}