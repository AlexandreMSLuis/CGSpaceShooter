#include "Menu.h"
    /*Loading background image to memory */
    Menu::Menu(){
    //texture variables inicialzation
    menuRenderID = 0;
    menuBuffer = nullptr;
    width = 0;
    height=0;
    bpp = 0;

}

GLvoid Menu::loadImage(std::string filePath){

    stbi_set_flip_vertically_on_load(1);

    menuBuffer = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &menuRenderID);
    glBindTexture(GL_TEXTURE_2D, menuRenderID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, menuBuffer);

    stbi_image_free(menuBuffer);

}

GLvoid Menu::createBackground(){
//drawing image of background
loadImage(backgroundTextureFilePath);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, menuRenderID);

    glBegin(GL_QUADS); {
        glTexCoord2f(0.0, 0.0); glVertex3f(worldCoordinates[0], worldCoordinates[2], 0.0f);
        glTexCoord2f(1.0, 0.0); glVertex3f(worldCoordinates[1], worldCoordinates[2], 0.0f);
        glTexCoord2f(1.0, 1.0); glVertex3f(worldCoordinates[1], worldCoordinates[3], 0.0f);
        glTexCoord2f(0.0, 1.0); glVertex3f(worldCoordinates[0], worldCoordinates[3], 0.0f);
    }glEnd();

    glDisable(GL_TEXTURE_2D);

    //unbinding the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLvoid Menu::createMenuText(){
    loadImage(textMenuTextureFilePath);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, menuRenderID);

    glBegin(GL_QUADS); {
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0, 0.0); glVertex3f(textWidth, 0.0f, 0.0f);
        glTexCoord2f(1.0, 1.0); glVertex3f(textWidth, textHeight, 0.0f);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0f, textHeight, 0.0f);
    }glEnd();

    glDisable(GL_TEXTURE_2D);

    //unbinding the texture
    glBindTexture(GL_TEXTURE_2D, 0);

}

GLvoid Menu::draw(GLint menu){
        switch (menu){
        case 0://game main menu
            backgroundTextureFilePath = "Textures/mainMenu.jpg";
            textMenuTextureFilePath = "Textures/startText.png";
            //enuText dimensions converted to float, had to be manualy calculated....
            textWidth = (float)131 * 0.10f;
            textHeight = (float)63 * 0.10f;
            break;
        case 1: // menu player lost / died
            backgroundTextureFilePath = "Textures/gameOverMenu.jpg";
            textMenuTextureFilePath = "Textures/restartText.png";
            //menuText dimensions converted to float, had to be manualy calculated....
            textWidth = (float)166 * 0.10f;
            textHeight = (float)63 * 0.10f;
            break;
        case 2: // menu player win
            backgroundTextureFilePath = "Textures/winMenu.jpg";
            textMenuTextureFilePath = "Textures/restartText.png";
            //menuText dimensions converted to float, had to be manualy calculated....
            textWidth = (float)166 * 0.10f;
            textHeight = (float)63 * 0.10f;
            break;
        default:
            break;
    }

    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Select projection matrix
    glMatrixMode(GL_PROJECTION);

    //Load identity matrix
    glLoadIdentity();
    //Projection Type
    gluOrtho2D(worldCoordinates[0], worldCoordinates[1], worldCoordinates[2], worldCoordinates[3]);

    //Select Model View Matrix
    glMatrixMode(GL_MODELVIEW);

    //Defines the blending modes of the tresparency <- (used to make activate textMenu image tresparency)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Enables blending mode <- - (used to fade textMenu)
    glEnable(GL_BLEND);

    //Load identity matrix
    glLoadIdentity();

    createBackground();

        //Push the data on matrix - duplicate data
    glPushMatrix();

    //set object translation and save it on the stack
    glTranslatef(centerX - (textWidth / 2), centerY - (textHeight / 2), 0.0f);

    glPushMatrix();

    createMenuText();

    //restore matrix state with object translation
    glPopMatrix();

    //restore original modelview state - atention to this!!!
    glPopMatrix();

}

Menu::~Menu(){


} 
