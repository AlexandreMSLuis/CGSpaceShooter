#include "Bullet.h"


Bullet::Bullet(GLfloat* pos, GLfloat* speedSpec, GLint bDir, GLint bColor) {
    //Set bullet start position
    currentPosition[0] = pos[0];
    currentPosition[1] = pos[1];

    //set bullet speed
    speed[0] = speedSpec[0];
    speed[1] = speedSpec[1];

    //set bullet size
    size[0] = 0.5f;
    size[1] = 2.0f;

    // Variable used to store the direction that the bullet is currently moving
    bulletDirection = bDir;

    bulletColor = bColor;

    //texture variables

    switch (bulletColor)
    {
    case 1:
        bulletTextureFilePath = "Textures/laserGreen.png";
        break;
    case 2:
        bulletTextureFilePath = "Textures/laserRed.png";
        break;
    default:
        break;
    }

    bulletRenderID = 0;
    bulletBuffer = nullptr;
    width = 0;
    height = 0;
    bpp = 0;

    stbi_set_flip_vertically_on_load(1);

    bulletBuffer = stbi_load(bulletTextureFilePath.c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &bulletRenderID);
    glBindTexture(GL_TEXTURE_2D, bulletRenderID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bulletBuffer);

}

GLvoid Bullet::shell(GLvoid) {
    

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, bulletRenderID);

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

GLvoid Bullet::draw(GLvoid) {
    //Select modelview matrix
    glMatrixMode(GL_MODELVIEW);

    //push the data on the matrix - duplicate data
    glPushMatrix();

    glTranslatef(currentPosition[0], currentPosition[1], 0.0f);
    glPushMatrix();
    //center the bullet
    glTranslatef(-0.5f, -0.5f, 0.0f);

    //glTranslatef(0.0f, posOfFire / 2, 0.0f);
    shell();

    glPopMatrix();
    glPopMatrix();
}

GLvoid Bullet::move(GLvoid) {

    switch (bulletDirection)
    {
    case 0: // move right
        currentPosition[0] -= speed[0];
        break;

    case 1: //move down
        currentPosition[1] -= speed[1];
        break;

    case 2: // move Left
        currentPosition[0] += speed[0];
        break;

    case 3: // move up
        currentPosition[1] += speed[1];
        break;

    default:
        break;
    }

}

GLfloat* Bullet::getPosition(GLvoid) {
    return currentPosition;
}

GLfloat* Bullet::getSize(GLvoid) {
    return size;
}

GLint Bullet::getDirection(GLvoid) {

    return bulletDirection;
}

Bullet::~Bullet() {
    glDeleteTextures(0, &bulletRenderID);
}
