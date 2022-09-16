//
//  Particle.hpp
//  SpaceShooter
//
//  Created by Alexandre Luis on 06/08/2022.
//

#ifndef Particle_hpp
#define Particle_hpp

#include "Sistema.h"

#endif /* Particle_hpp */


class Particle {
private:
    GLfloat position[2],
        velocity[2],
        color[3],
        opacity;
    GLint radius;
    GLboolean fades;
    
    GLvoid circle(GLvoid);
    

public:
    Particle(GLfloat*, GLfloat*, GLint, GLfloat*, GLfloat, GLboolean);
    GLvoid draw(GLvoid);
    GLvoid move(GLvoid);
    GLfloat* getPosition(GLvoid);
    GLint getRadius(GLvoid);
    GLfloat getOpacity(GLvoid);
    GLvoid setPosition(GLfloat x, GLfloat y);
    ~Particle();
};
