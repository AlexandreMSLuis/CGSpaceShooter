//
//  Particle.cpp
//  SpaceShooter
//
//  Created by Alexandre Luis on 06/08/2022.
//

#include "Particle.h"


Particle::Particle(GLfloat* pos, GLfloat* vel, GLint rad, GLfloat* col, GLfloat op, GLboolean fd){
    
    position[0] = pos[0];
    position[1] = pos[1];
    
    velocity[0] = vel[0];
    velocity[1] = vel[1];
    
    radius = rad;
    
    color[0] = col[0];
    color[1] = col[1];
    color[2] = col[2];
    
    opacity = op;
    
    fades = fd;
    
}


GLvoid Particle::circle(GLvoid){
    GLfloat x, y, theta;
    GLfloat r = radius;
    GLint numSegments = 20;
    
    glColor4f(color[0], color[1], color[2], opacity);
    glBegin(GL_POLYGON);
    
    for (int i = 0; i < numSegments; i++) {
        theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        
        x = r * cos(theta);
        y = r * sin(theta);
        
        glVertex3f( x, y, 0.0f);
    }
    glEnd();
}


GLvoid Particle::draw(GLvoid){
    //Select modelview matrix
    glMatrixMode(GL_MODELVIEW);

    //push the data on the matrix - duplicate data
    glPushMatrix();

    glTranslatef(position[0], position[1], 0.0f);
    glPushMatrix();
    
    circle();

    glPopMatrix();
    glPopMatrix();
}

GLvoid Particle::move(GLvoid){
    position[0] += velocity[0];
    position[1] += velocity[1];
    
    if(fades){
        opacity -= 0.05;
    }

}

GLfloat* Particle::getPosition(GLvoid){
    return position;
}

GLint Particle::getRadius(GLvoid){
    return radius;
}

GLfloat Particle::getOpacity(GLvoid){
    return opacity;
}
GLvoid Particle::setPosition(GLfloat x, GLfloat y){
    position[0] = x;
    position[1] = y;
}

Particle::~Particle(){
    
}
