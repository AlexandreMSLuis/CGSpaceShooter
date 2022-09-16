#include "Enemy.h"

Enemy::Enemy(GLfloat x, GLfloat y, GLint eType) {
    currentPosition[0] = x;
    currentPosition[1] = y;
    size[0] = 3.0f;
    size[1] = 2.0f;

    speed[0] = 0.3f;
    speed[1] = 3.0f;


    switch (eType)
    {
    case 1:
        enemyTextureFilePath = "Textures/enemy1.png";
        color[0] = 0.39f;
        color[1] = 0.50f;
        color[2] = 0.30f;
        break;

    case 2:
        enemyTextureFilePath = "Textures/enemy2.png";
        color[0] = 0.38f;
        color[1] = 0.34f;
        color[2] = 0.42f;
        break;

    case 3:
        enemyTextureFilePath = "Textures/enemy3.png";
        color[0] = 0.24f;
        color[1] = 0.53f;
        color[2] = 0.63f;
        break;
    case 4:
        enemyTextureFilePath = "Textures/enemy4.png";
        color[0] = 0.73f;
        color[1] = 0.42f;
        color[2] = 0.18f;
        break;
    default:
        break;
    }


    //texture variables
    enemyRenderID = 0;
    enemyBuffer = nullptr;
    width = 0;
    height = 0;
    bpp = 0;

    stbi_set_flip_vertically_on_load(1);

    enemyBuffer = stbi_load(enemyTextureFilePath.c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &enemyRenderID);
    glBindTexture(GL_TEXTURE_2D, enemyRenderID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, enemyBuffer);
}

GLvoid Enemy::enemyBody(GLvoid) {

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, enemyRenderID);

    glBegin(GL_QUADS); {
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0, 0.0); glVertex3f(3.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0, 1.0); glVertex3f(3.0f, 3.0f, 0.0f);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0f, 3.0f, 0.0f);
    } glEnd();

    glDisable(GL_TEXTURE_2D);

    //unbinding the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLvoid Enemy::draw() {
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glTranslatef(currentPosition[0] - (size[0] / 2), currentPosition[1] - (size[1] / 2), 0.0f);

    glPushMatrix();

    enemyBody();

    glPopMatrix();

    glPopMatrix();

}

GLboolean Enemy::move(GLint direction) {
    GLboolean canMove = false;

    switch (direction) {
    case 0: // move right
        if (((currentPosition[0] + speed[0]) < worldCoordinates[1]) - size[0] / 2)
        {
            currentPosition[0] += speed[0];
            canMove = true;

        }
        break;

    case 1: //move down
        currentPosition[1] -= speed[1];
        canMove = true;

        break;

    case 2: // move Left
        if (((currentPosition[0] - speed[0]) > worldCoordinates[0]) + size[0] / 2)
        {
            currentPosition[0] -= speed[0];
            canMove = true;

        }
        break;

    case 3: // move up
        if (currentPosition[1] + speed[1] < worldCoordinates[3])
        {
            currentPosition[0] += speed[0];
            canMove = true;

        }
        break;

    default:
        break;
    }

    return canMove;
}

GLfloat* Enemy::getPosition() {
    return currentPosition;
}

GLfloat* Enemy::getSize() {
    return size;
}

GLfloat* Enemy::getColor() {
    return color;
}

Enemy::~Enemy() {
    glDeleteTextures(0, &enemyRenderID);
}