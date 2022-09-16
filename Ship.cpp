#include "Ship.h"

Ship::Ship(GLfloat* pos) {
    currentPosition[0] = pos[0];
    currentPosition[1] = pos[1];

    //Set speed as 1.5% of the screen width
    speed[0] = (worldCoordinates[1] - worldCoordinates[0]) * 0.015;
    speed[1] = (worldCoordinates[3] - worldCoordinates[2]) * 0.015;

    //set ship dimentions
    size[0] = 6.0f;
    size[1] = 6.0f;

    //texture variables
    shipRenderID = 0;
    shipTextureFilePath = "Textures/player.png";
    shipBuffer = nullptr;
    width = 0;
    height = 0;
    bpp = 0;
}

GLvoid  Ship::body(GLvoid) {

   stbi_set_flip_vertically_on_load(1);

    shipBuffer = stbi_load(shipTextureFilePath.c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &shipRenderID);
    glBindTexture(GL_TEXTURE_2D, shipRenderID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, shipBuffer);
    
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, shipRenderID);

    glBegin(GL_QUADS); {
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0, 0.0); glVertex3f(size[0], 0.0f, 0.0f);
        glTexCoord2f(1.0, 1.0); glVertex3f(size[0] , size[1], 0.0f);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0f, size[1], 0.0f);
    }glEnd();

    glDisable(GL_TEXTURE_2D);

    //unbinding the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}


GLvoid Ship::draw() {
    //Select the modelview Matrix
    glMatrixMode(GL_MODELVIEW);

    //Push the data on matrix - duplicate data
    glPushMatrix();

    //set object translation and save it on the stack
    glTranslatef(currentPosition[0] - (size[0] / 2), currentPosition[1] - (size[1] / 2), 0.0f);

    glPushMatrix();

    body();

    //restore matrix state with object translation
    glPopMatrix();

    //restore original modelview state - atention to this!!!
    glPopMatrix();

}

/* method to move the ship
 * Recieves an integer that codes ship movement direction
 * 0 - right
 * 1 - down
 * 2 - left
 * 3 - up
 * returns true if the ship was moved
 * returns false if the ship was unable to move
 */

GLboolean Ship::move(GLint dir) {
    GLboolean canMove = false;

    switch (dir) {
    case 0:
        if ((currentPosition[0] + speed[0]) < (worldCoordinates[1] - 3.0f)) {
            currentPosition[0] += speed[0];
            canMove = true;
        }
        break;

    case 1:
        if ((currentPosition[1] - speed[1]) > (worldCoordinates[2] + 2.5f)) {
            currentPosition[1] -= speed[1];
            canMove = true;
        }
        break;

    case 2:
        if ((currentPosition[0] - speed[0]) > (worldCoordinates[0] + 3.0f)) {
            currentPosition[0] -= speed[0];
            canMove = true;
        }
        break;

    case 3:
        if ((currentPosition[1] + speed[1]) < (worldCoordinates[3] - 2.5f)) {
            currentPosition[1] += speed[1];
            canMove = true;
        }
        break;

    default:
        break;
    }
    return canMove;
}


GLfloat* Ship::getPosition() {
    return currentPosition;
}

GLfloat* Ship::getSize() {
    return size;
}

Ship::~Ship() {
    glDeleteTextures(0, &shipRenderID);
}

