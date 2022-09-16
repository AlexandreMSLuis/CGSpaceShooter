//
//  Star.hpp
//  SpaceShooter
//
//  Created by Alexandre Luis on 06/08/2022.
//

#pragma once
#ifndef Star_hpp
#define Star_hpp

#include "Sistema.h"

#endif /* Star_hpp */

class Star
{

public:
    GLfloat x, y;
    GLint size;
    Star(GLfloat,GLfloat, GLint);
    GLvoid move(GLvoid);
    GLvoid draw(GLvoid);
    ~Star();
};
