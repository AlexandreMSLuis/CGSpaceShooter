#pragma once
#ifndef Sistema_h
#define Sistema_h
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <math.h>
#include <vector>
#include <sstream>
//#include <string.h>
//#include <cstdlib> // para a função rand()
//#include <GLUT/glut.h>
//#include <unistd.h>
#include <GL/freeglut.h>


//stb image to extract information of imgage/texture (width, height, bpp, etc)
#include "stb_image.h"

//audio engine libraly
#include "External/irrklang/include/irrKlang.h"
using namespace irrklang;

using namespace std;
extern GLfloat worldCoordinates[4];
#endif /* Sistema_h */
#pragma once

/*

Textures:
https://opengameart.org/content/space-shooter-art
https://opengameart.org/content/space-shooter-redux

video of textures:
https://youtu.be/n4k7ANAFsIQ


audio library and tutorial:
https://learnopengl.com/In-Practice/2D-Game/Audio
https://www.ambiera.com/irrklang/downloads.html


audios:
Main Theme: https://freesound.org/people/FoolBoyMedia/sounds/320232/
win:       https://freesound.org/people/LittleRobotSoundFactory/sounds/270402/
lose:       https://freesound.org/people/cabled_mess/sounds/371451/

*/
