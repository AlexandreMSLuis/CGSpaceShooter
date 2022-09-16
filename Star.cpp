//
//  Star.cpp
//  SpaceShooter
//
//  Created by Alexandre Luis on 06/08/2022.
//

#include "Star.h"

Star::Star(GLfloat xIn, GLfloat yIn, GLint sizeIn) {
    x = xIn;
    y = yIn;
    size = sizeIn;
}

GLvoid Star::move(GLvoid) {
     y -= 0.2f;
}

GLvoid Star::draw(GLvoid) {
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPointSize(size);
    glColor3f(1, 1, 1);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    //glFlush();

}

Star::~Star() {

}
