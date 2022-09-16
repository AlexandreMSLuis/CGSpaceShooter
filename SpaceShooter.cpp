#include "Sistema.h"
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Star.h"
#include "Particle.h"
#include "Enemy.h"
#include "Life.h"

/*+++++++++++++++++++++++++++++++++
Space Invasion!!

 0 - move right
 1 - move down
 2 - move left
 3 - move up

++++++++++++++++++++++++++++++++++*/

// number for stars of the background quantity
GLint nStars;

//Global world coordinates
GLfloat worldCoordinates[4] = { -40.0f, 40.0f, -40.0f, 40.0f };
//GLfloat worldCoordinates[4] = { -20.0f, 20.0f, -20.0f, 20.0f };

//buffer to write text on OpenGL scenes
stringstream buffer;

//create the element that player controls
Ship* player;

//Control over the player's movement direction
GLint playerDirection;

//Controls of bullets directions
GLint playerBulletDirection;

//variables for player bullet creation
GLfloat* playerBulletPosition;
GLfloat playerBulletSpeed[2];
vector <Bullet*> playerBullets;

//Controls of enemy bullets directions
GLint enemyBulletDirection;

//Control players position
GLfloat playerPosition[2];

//Game timer expired
GLboolean gameTimerExpired;

//player shoot timer
GLboolean playerCanShoot;
GLint playerShootTime;

//player death aniamtion timer 
GLint playerDieTimer;

//Create data structure to hold Enemies
vector <Enemy*> enemies;

//Control over the enemy's movement direction
GLint enemyDirection;

//number of times the enemies colision box touched the walls
GLint enemyWallHits;

//variables for enemy bullet creation
GLfloat* enemyBulletPosition;
GLfloat enemyBulletSpeed[2];
vector <Bullet*> enemyBullets;

//level manage
GLboolean levelFinished, isPlayerAlive;
GLint score;
//GLint lives;
GLint gameTime;
vector <Life*> lives;

//starts
vector <Star*> stars;

//particles storage
vector <Particle*> particles;

// Number of particles to create
GLint numParticles = 20;

/* DEBUG AXIS FOR CENTER OF WINDOW
//Debug axis line
GLvoid drawAxis() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES); {
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 10.0);

    }glEnd();
    glBegin(GL_LINES); {
        glVertex2f(0.0, 0.0);
        glVertex2f(10.0, 0.0);
    }glEnd();
}*/


/* 
    FUNCTION SIGNATURES

*/

GLvoid  gameStart(GLvoid);
GLvoid gameFinish(GLvoid);
GLvoid loop(GLvoid);

//game timer function
void gameTimer(GLint value) {
    gameTimerExpired = true;
    glutTimerFunc(gameTime, gameTimer, 0);
}

//player shoot timer function
void playerShootTimer(GLint value) {
    playerCanShoot = true;
    glutTimerFunc(playerShootTime, playerShootTimer, 0);
}

// function that generates a random number between a negative and a positive GLfloat
GLfloat RandomNumber(GLfloat Min, GLfloat Max)
{
    return ((GLfloat(rand()) / GLfloat(RAND_MAX)) * (Max - Min)) + Min;
}

// function that create explosion particles
GLvoid createParticles(GLfloat objectPosition[2], GLfloat objectColor[3]) {
    //this for loop have "numParticles" iterations, its the number of particles created for the explosion
    for (int i = 0; i < numParticles; i++)
    {
        GLfloat x = (((float)rand() / RAND_MAX) - 0.5) * 2;
        GLfloat y = (((float)rand() / RAND_MAX) - 0.5) * 2;
        GLfloat speed[2] = { x, y };
        GLfloat opacity = 1.0f;
        GLint radius = rand() % 3;

        Particle* part = new Particle(objectPosition, speed, radius, objectColor, opacity, true);
        particles.push_back(part);
    }
}

//function that shows stars on background of game
GLvoid showStars(GLvoid) {
    for (int i = 0; i < stars.size(); i++)
    {
        //first lets verify if the star is at the bottom of the screen or not
        if (stars[i]->y >= worldCoordinates[2])
        {
            // if is inside the screen limits, we simply move and draw it
            stars[i]->move();
            stars[i]->draw();
        }
        else
        {
            // In case of the star already reached the bottom of the screen,
            // we reposition it on a new cordinate at the top of the screen, in random X value
            stars[i]->x = RandomNumber(worldCoordinates[0], worldCoordinates[1]);
            stars[i]->y = worldCoordinates[3];
        }
    }
}

//function that creates N stars
GLvoid createStars(GLvoid) {
    Star* star;
    GLfloat starX, starY;
    GLint size;

    for (int i = 0; i < nStars; i++)
    {
        starX = RandomNumber(worldCoordinates[0], worldCoordinates[1]);
        starY = RandomNumber(worldCoordinates[2], worldCoordinates[3]);
        size = rand() % 3 + 1;

        star = new Star(starX, starY, size);
        stars.push_back(star);

    }

}

//Game Keyboard callback
GLvoid gameKeyboard(unsigned char key, int x, int y) {
    Bullet* bullet;
    GLfloat* playerSize;
    //GLfloat testBp[] = {30.0f,-10.0f};
    GLfloat firePosition[2];
    switch (key) {
    case 'Q':
    case 'q':
        exit(0);
        break;

    case 'W':
    case 'w':
        playerDirection = 3;
        break;

    case 'A':
    case 'a':
        playerDirection = 2;
        break;

    case 'S':
    case 's':
        playerDirection = 1;
        break;

    case 'D':
    case 'd':
        playerDirection = 0;
        break;

    case 32:
        if (playerCanShoot) {
            playerCanShoot = false;
            //we need to get the player current position
            playerBulletPosition = player->getPosition();
            playerSize = player->getSize();
            //we want to fire the bullet on top of the ship, so we dont change the X but the Y need to have half of ship size
            firePosition[0] = playerBulletPosition[0];
            firePosition[1] = playerBulletPosition[1] + (playerSize[1] / 2);
            bullet = new Bullet(firePosition, playerBulletSpeed, playerBulletDirection, 2);
            playerBullets.push_back(bullet);
        }
        break;

    default:
        break;
    }

}

//Game Keyboard callback
GLvoid menuKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'Q':
    case 'q':
        exit(0);
        break;

    case 'n':
    case 'N':
        gameStart();
        glutPostRedisplay();
        break;

    default:
        break;
    }

}

//check if enemies are destroyed
GLvoid checkAllEnemiesDestroyed(GLvoid) {
    if (enemies.size() == 0) {
        gameFinish();
        glutPostRedisplay();
    }
}

//check if the player is destroyed
GLvoid checkPlayerLives(GLvoid) {
    if (lives.empty()) {
        isPlayerAlive = false;
        GLfloat color[] = { 0.5,0.5,0.5 };
        createParticles(player->getPosition(), color);
        player->~Ship();
        cout << "DEAD!!!" << endl;
    }
}

GLvoid playerDieAnimation(GLvoid) {
    if (!isPlayerAlive){
        if (playerDieTimer == 50){
                gameFinish();
        }else{
                playerDieTimer++;
        }
    }
}

// function that will check if the player bullets are colliding with enemies and if colision ocurre, bullet and enemy are destroyed
GLvoid checkBulletColidingEnemies(GLvoid) {
    if (playerBullets.size() > 0 && isPlayerAlive) {
        GLfloat* currentEnemyPosition,
            * currentEnemySize,
            * currentBulletPosition,
            * currentBulletSize;

        for (int i = 0; i < enemies.size(); i++) {
            currentEnemyPosition = enemies.at(i)->getPosition();
            currentEnemySize = enemies.at(i)->getSize();

            for (int j = 0; j < playerBullets.size(); j++) {
                currentBulletPosition = playerBullets.at(j)->getPosition();
                currentBulletSize = playerBullets.at(j)->getSize();

                if (!(
                    ((currentBulletPosition[1] - currentBulletSize[1] / 2) > (currentEnemyPosition[1] + currentEnemySize[1] / 2))
                    ||
                    ((currentBulletPosition[0] - currentBulletSize[0] / 2) > (currentEnemyPosition[0] + currentEnemySize[0] / 2))
                    ||
                    ((currentBulletPosition[1] + currentBulletSize[1] / 2) < (currentEnemyPosition[1] - currentEnemySize[1] / 2))
                    ||
                    ((currentBulletPosition[0] + currentBulletSize[0] / 2) < (currentEnemyPosition[0] - currentEnemySize[0] / 2))
                    )) {

                    //colision detected between a bullet and an enemy
                    createParticles(enemies.at(i)->getPosition(), enemies.at(i)->getColor());
                    //removing bullet texture from memory
                    playerBullets[j]->~Bullet();
                    //removing bullet from vector
                    playerBullets.erase(playerBullets.begin() + j);
                    //removing enemy texture from memory
                    enemies[i]->~Enemy();
                    //removing enemy from vector
                    enemies.erase(enemies.begin() + i);

                    score += 10;
                    break;
                }
            }

        }
    }
}

// function that will check if the enemy bullets are colliding with the player and if colision ocurre,
//bullet is destroyed and life mechanims applied.
GLvoid checkBulletColidingPLayer(GLvoid) {
    if (enemyBullets.size() > 0 && isPlayerAlive) {
        GLfloat* currentBulletPosition,
            * currentBulletSize;
        GLfloat* currentPlayerPosition = player->getPosition();
        GLfloat* currentPlayerSize = player->getSize();

        for (int i = 0; i < enemyBullets.size(); i++) {
            currentBulletPosition = enemyBullets.at(i)->getPosition();
            currentBulletSize = enemyBullets.at(i)->getSize();

            if (!(
                ((currentBulletPosition[1] - currentBulletSize[1] / 2) > (currentPlayerPosition[1] + currentPlayerSize[1] / 2))
                ||
                ((currentBulletPosition[0] - currentBulletSize[0] / 2) > (currentPlayerPosition[0] + currentPlayerSize[0] / 2))
                ||
                ((currentBulletPosition[1] + currentBulletSize[1] / 2) < (currentPlayerPosition[1] - currentPlayerSize[1] / 2))
                ||
                ((currentBulletPosition[0] + currentBulletSize[0] / 2) < (currentPlayerPosition[0] - currentPlayerSize[0] / 2))
                )) {

                //colision detected between a bullet and the player
                //removing bullet texture from memory
                enemyBullets[i]->~Bullet();
                //removing enemy bullet from vector
                enemyBullets.erase(enemyBullets.begin() + i);
                //getting the index of the last icon in the vector
                GLint idx = lives.size() - 1;
                //remove the icon from the screen
                lives.at(idx)->~Life();
                //remove life icon of player from the vector of lives
                lives.erase(lives.begin() + idx);
                //calling the function that checks the player lives and act has necessary  
                checkPlayerLives();
                break;
            }


        }
    }
}

//function that recieve a vector of bullets and check if contains bullets outside worldcoords boundaries
// if so, remove those bullets and after that returns the vector
vector<Bullet*> checkBulletOutsideBoundaries(vector <Bullet*> bullets) {
    if (bullets.size() > 0) {
        GLfloat* currentBulletPosition;
        GLint currentBulletDirection;

        for (int i = 0; i < bullets.size(); i++) {
            //1st - for each bullet inside the vector, we retrieve the bullet position and its moving direction
            currentBulletPosition = bullets[i]->getPosition();
            currentBulletDirection = bullets[i]->getDirection();

            // 2nd - acording to the bullet direction, we check the bullet position and the respective worldcoords,
                // if the position is outside the boundaries, the bullet is removed from the vector
            switch (currentBulletDirection) {
            case 0: // bullet moving to the right
                if (currentBulletPosition[0] < worldCoordinates[0]) {
                    //removing bullet texture from memory
                    bullets[i]->~Bullet();
                    //removing bullet from vector
                    bullets.erase(bullets.begin() + i);
                }
                break;

            case 1: // bullet moving to the down
                if (currentBulletPosition[1] < worldCoordinates[2]) {
                    //removing bullet texture from memory
                    bullets[i]->~Bullet();
                    //removing bullet from vector
                    bullets.erase(bullets.begin() + i);

                }
                break;

            case 2:  // bullet moving to the left
                if (currentBulletPosition[0] > worldCoordinates[1]) {
                    //removing bullet texture from memory
                    bullets[i]->~Bullet();
                    //removing bullet from vector
                    bullets.erase(bullets.begin() + i);
                }
                break;

            case 3:  // bullet moving to the up
                if (currentBulletPosition[1] > worldCoordinates[3]) {
                    //removing bullet texture from memory
                    bullets[i]->~Bullet();
                    //removing bullet from vector
                    bullets.erase(bullets.begin() + i);
                }
                break;

            default:
                break;
            }
        }
    }
    // 3rd - returning the "cleaned" vector
    return bullets;
}

//create enemies
GLvoid createEnemies(GLfloat startX, GLfloat startY, GLint numberX, GLint numberY) {
    GLint numberOfEnemies, maxNumberOfEnemies = numberX * numberY;
    GLfloat xPos, yPos = 0;
    Enemy* enemy;
    GLint enemyType;

    for (numberOfEnemies = 0; numberOfEnemies < maxNumberOfEnemies; numberOfEnemies++) {
        xPos = startX + numberOfEnemies % numberX * 6;
        yPos = startY + numberOfEnemies % numberY * -4;
        enemyType = rand() % 4 + 1;

        enemy = new Enemy(xPos, yPos, enemyType);
        enemies.push_back(enemy);
    }
}

//function that fires an enemy bullet
GLvoid enemyFireBullet(GLvoid) {
    GLint probability = rand() % 10000;

    if (probability < 100) {
        if (enemies.size() > 0) {
            Bullet* enemyBullet;
            GLint randEnemy = rand() % enemies.size();
            GLfloat* enemyBulletPosition = enemies.at(randEnemy)->getPosition();
            GLfloat enemyBulletSpeed[] = { 1.0f, 1.0f };
            enemyBullet = new Bullet(enemyBulletPosition, enemyBulletSpeed, enemyBulletDirection, 1);
            enemyBullets.push_back(enemyBullet);
        }
    }
}

GLvoid idle(GLvoid) {
    GLboolean playerUpdate = false,
        screenRefresh = false;

    GLfloat xMin = worldCoordinates[1],
        xMax = worldCoordinates[0],
        yMin = worldCoordinates[3],
        yMax = worldCoordinates[2],
        * currentEnemyPosition,
        * currentEnemySize;


    //player movement
    if (playerDirection != -1) {
        playerUpdate = player->move(playerDirection);
        if (playerUpdate) {
            screenRefresh = true;
            playerDirection = -1;
        }
    }

    //enemy movement
    if (gameTimerExpired) {
        gameTimerExpired = false;
        //screenRefresh = true;
        checkPlayerLives();
        checkAllEnemiesDestroyed();
        //call of the function that makes the enemy fire a bullet
        enemyFireBullet();


        for (int i = 0; i < enemies.size(); i++) {
            currentEnemyPosition = enemies.at(i)->getPosition();
            currentEnemySize = enemies.at(i)->getSize();

            //check X bounderies, update as necesary
            if (xMin > currentEnemyPosition[0])
                xMin = currentEnemyPosition[0] - (currentEnemySize[0] / 2);
            if (xMax < currentEnemyPosition[0])
                xMax = currentEnemyPosition[0] + (currentEnemySize[0] / 2);

            //check Y bounderies, update as necesary
            if (yMin > currentEnemyPosition[1])
                yMin = currentEnemyPosition[1] - (currentEnemySize[1] / 2);
            if (yMax < currentEnemyPosition[1])
                yMax = currentEnemyPosition[1] + (currentEnemySize[1] / 2);
        }

        //change direction
        switch (enemyDirection) {
        case 0: // move right
            if (xMax + 0.3f > worldCoordinates[1]) {
                enemyDirection = 2;
                enemyWallHits++;
            }
            break;

        case 1: // move down
            enemyDirection = 0;
            enemyWallHits = 0;

            break;

        case 2: //move left
            if (xMin - 0.3f < worldCoordinates[0]) {
                enemyDirection = 0;
                enemyWallHits++;
            }
            break;

        case 3: // move up
            break;

        default:
            break;
        }


        if (enemyWallHits == 6) {
            enemyDirection = 1;
        }


        //move enemies
        for (int i = 0; i < enemies.size(); i++) {
            enemies.at(i)->move(enemyDirection);
        }

        //update all bullets position
        for (int i = 0; i < playerBullets.size(); i++) {
            playerBullets[i]->move();

        }

        for (int i = 0; i < enemyBullets.size(); i++) {
            enemyBullets.at(i)->move();
        }

        // call of the function that check colision of bullets with enemies
        checkBulletColidingEnemies();
        // call of the function that check colision of bullets with the player
        checkBulletColidingPLayer();

        // call of the function that check if enemyBullets are outside boundaries and replace the actual vector
        enemyBullets = checkBulletOutsideBoundaries(enemyBullets);
        // call of the function that check if playerBullets are outside boundaries and replace the actual vector
        playerBullets = checkBulletOutsideBoundaries(playerBullets);

        //update particles
        for (int i = 0; i < particles.size(); i++)
        {
            if (particles.at(i)->getOpacity() > 0) {
                particles.at(i)->move();
            }
            else {
                particles.erase(particles.begin() + i);
            }
        }
        //cout << "Player bullets: " << playerBullets.size() << endl;
        //cout << "Enemy bullets: " << enemyBullets.size() << endl;


    }// end of gameTimer

    //update screen refresh
    if (screenRefresh) {
        glutPostRedisplay();
        screenRefresh = false;
    }
}

//Game Draw callback
GLvoid drawGame(GLvoid) {

    char c;
    buffer.str(""); //coloca a string vazia
    buffer.clear(); // limpa a buffer

    //Define background color
    glClearColor(0.11, 0.16, 0.21, 0);

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

    //Load identity matrix
    glLoadIdentity();

    //Defines the blending modes of the tresparency <- (used to the particles fading)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Enables blending mode <- - (used to the particles fading)
    glEnable(GL_BLEND);


    //show score counter
    buffer << "Score: " << score << endl;
    glRasterPos3f(worldCoordinates[0] + 1.0f, worldCoordinates[3] - 3.0f, 0.0);
    while (buffer.get(c))
    {

        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    }

    buffer.str(""); //coloca a string vazia
    buffer.clear(); // limpa a buffer


    //draw all particles on the screen
    for (int i = 0; i < particles.size(); i++) {
        particles.at(i)->draw();
    }

    //Select Model View Matrix
    glMatrixMode(GL_TEXTURE);

    //Load identity matrix
    glLoadIdentity();

    // draw stars on the screen
    showStars();

    // draw player ship
    if(isPlayerAlive)
        player->draw();


    //draw all enemies on the screen
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->draw();
    }

    //draw all player bullets on the screen
    for (int i = 0; i < playerBullets.size(); i++) {
        playerBullets[i]->draw();
    }

    //draw all enemy bullets on the screen
    for (int i = 0; i < enemyBullets.size(); i++) {
        enemyBullets.at(i)->draw();
    }


    //draw 3 lives icons on top right of screen
    for (int i = 0; i < lives.size(); i++)
    {
        lives.at(i)->draw();
    }

    //drawAxis();
    glutSwapBuffers();
}

// Menu Draw callback
GLvoid drawMenu(GLvoid) {
    string text1 = "Space Shooter!!!";
    string text2 = "N - New Game";

    //variables used to get the center of the screen
    GLfloat centerX = (worldCoordinates[0] + worldCoordinates[1]) / 2;
    GLfloat centerY = (worldCoordinates[2] + worldCoordinates[3]) / 2;

    //variable used to calculate the width of the string
    GLfloat stringWidth = 0;

    //Define background color
    glClearColor(0, 0, 0, 0);

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

    //Load identity matrix
    glLoadIdentity();

    //calculate the width of the string text1
    stringWidth = text1.length();

    //positioning text1 in the center of the screen and 5.0f uper of its center
    glRasterPos3f(centerX - stringWidth / 2, centerY / 2 + 5.0f, 0.0);

    //displaying the charaters of the string text1 with the respective font and font size
    for (int i = 0; i < text1.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }


    //calculate the width of the string text2
    stringWidth = text2.length();

    //positioning text2 in the center of the screen
    glRasterPos3f(centerX - stringWidth / 2, centerY / 2, 0.0);

    //displaying the charaters of the string text2 with the respective font and font size
    for (int i = 0; i < text2.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text2[i]);
    }
    glutSwapBuffers();
}

// Menu Draw callback
GLvoid drawFinish(GLvoid) {
    string text1 = "Congratulations!!!";
    string text2 = "N - New Game";
    string text3 = "Q - Exit";

    //variables used to get the center of the screen
    GLfloat centerX = (worldCoordinates[0] + worldCoordinates[1]) / 2;
    GLfloat centerY = (worldCoordinates[2] + worldCoordinates[3]) / 2;

    //variable used to calculate the width of the string
    GLfloat stringWidth = 0;


    //Define background color
    glClearColor(0, 0, 0, 0);

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

    //Load identity matrix
    glLoadIdentity();

    //calculate the width of the string text1
    stringWidth = text1.length();

    //positioning text1 in the center of the screen and 5.0f uper of its center
    glRasterPos3f(centerX - stringWidth / 2, centerY / 2 + 5.0f, 0.0);

    //displaying the charaters of the string text1 with the respective font and font size
    for (int i = 0; i < text1.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }


    //calculate the width of the string text2
    stringWidth = text2.length();

    //positioning text2 in the center of the screen
    glRasterPos3f(centerX - stringWidth / 2, centerY / 2, 0.0);

    //displaying the charaters of the string text2 with the respective font and font size
    for (int i = 0; i < text2.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text2[i]);
    }


    //calculate the width of the string text3
    stringWidth = text3.length();

    //positioning text3 in the center of the screen
    glRasterPos3f(centerX - stringWidth / 2, (centerY / 2) - 3.0f, 0.0);

    //displaying the charaters of the string text3 with the respective font and font size
    for (int i = 0; i < text3.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[i]);
    }
    glutSwapBuffers();
}

//start game function
GLvoid gameStart(GLvoid) {
    //level manage
    levelFinished = false;
    isPlayerAlive = true;
    playerDieTimer = 0;
    score = 0;
    //lives = 3;
    nStars = 100;
    gameTime = 1000/45;

    //variables for player bullet creation
    playerBulletSpeed[0], playerBulletSpeed[1] = 1.0f;

    //Control over the enemy's movement direction
    enemyDirection = 0;

    //number of times the enemies colision box touched the walls
    enemyWallHits = 0;

    //Control over the player's movement direction
    playerDirection = -1;

    //Controls of bullets directions
    playerBulletDirection = 3;
    enemyBulletDirection = 1;

    playerCanShoot = false;
    playerShootTime = 1000;

    //Control players position
    playerPosition[0] = (worldCoordinates[0] + worldCoordinates[1]) / 2;
    playerPosition[1] = worldCoordinates[2] / 2;

    player = new Ship(playerPosition);

    //Game timer expired
    gameTimerExpired = false;

    //Create Enemies
    createEnemies(worldCoordinates[0] + 4.0f, worldCoordinates[3] - 6.0f, 8, 3);

    //CreateStars
    createStars();

    //create 3 lives icons on top right of screen
    float inc = 2.0f;
    for (int i = 0; i < 3; i++)
    {
        GLfloat lifePosition[] = { worldCoordinates[1] - inc, worldCoordinates[3] - 2.0f };
        Life* icon = new Life(lifePosition);
        lives.push_back(icon);
        inc += 3.0f;
    }

    //Set display callback
    glutDisplayFunc(drawGame);

    //Set keyboard callback
    glutKeyboardFunc(gameKeyboard);

    //Set Idle callback
    glutIdleFunc(loop);

}

//finish function
GLvoid gameFinish(GLvoid) {

    //clear vectors every time the game finish
    playerBullets.clear();
    enemyBullets.clear();
    enemies.clear();
    stars.clear();

    //Set display callback
    glutDisplayFunc(drawFinish);

    //Set keyboard callback
    glutKeyboardFunc(menuKeyboard);

}

GLvoid loop(GLvoid) {
    GLboolean playerUpdate;

    GLfloat xMin = worldCoordinates[1],
        xMax = worldCoordinates[0],
        yMin = worldCoordinates[3],
        yMax = worldCoordinates[2],
        * currentEnemyPosition,
        * currentEnemySize;

    //player movement
    if (playerDirection != -1) {
        playerUpdate = player->move(playerDirection);
        if (playerUpdate) {
            playerDirection = -1;
        }
    }

    //enemy movement
    if (gameTimerExpired) {
        gameTimerExpired = false;
        //screenRefresh = true;
        //checkPlayerLives();
        playerDieAnimation();
        checkAllEnemiesDestroyed();
        //call of the function that makes the enemy fire a bullet
        enemyFireBullet();


        for (int i = 0; i < enemies.size(); i++) {
            currentEnemyPosition = enemies.at(i)->getPosition();
            currentEnemySize = enemies.at(i)->getSize();

            //check X bounderies, update as necesary
            if (xMin > currentEnemyPosition[0])
                xMin = currentEnemyPosition[0] - (currentEnemySize[0] / 2);
            if (xMax < currentEnemyPosition[0])
                xMax = currentEnemyPosition[0] + (currentEnemySize[0] / 2);

            //check Y bounderies, update as necesary
            if (yMin > currentEnemyPosition[1])
                yMin = currentEnemyPosition[1] - (currentEnemySize[1] / 2);
            if (yMax < currentEnemyPosition[1])
                yMax = currentEnemyPosition[1] + (currentEnemySize[1] / 2);
        }

        //change direction
        switch (enemyDirection) {
        case 0: // move right
            if (xMax + 0.3f > worldCoordinates[1]) {
                enemyDirection = 2;
                enemyWallHits++;
            }
            break;

        case 1: // move down
            enemyDirection = 0;
            enemyWallHits = 0;

            break;

        case 2: //move left
            if (xMin - 0.3f < worldCoordinates[0]) {
                enemyDirection = 0;
                enemyWallHits++;
            }
            break;

        case 3: // move up
            break;

        default:
            break;
        }


        if (enemyWallHits == 6) {
            enemyDirection = 1;
        }


        //move enemies
        for (int i = 0; i < enemies.size(); i++) {
            enemies.at(i)->move(enemyDirection);
        }

        //update all bullets position
        for (int i = 0; i < playerBullets.size(); i++) {
            playerBullets[i]->move();

        }

        for (int i = 0; i < enemyBullets.size(); i++) {
            enemyBullets.at(i)->move();
        }

        // call of the function that check colision of bullets with enemies
        checkBulletColidingEnemies();
        // call of the function that check colision of bullets with the player
        checkBulletColidingPLayer();

        // call of the function that check if enemyBullets are outside boundaries and replace the actual vector
        enemyBullets = checkBulletOutsideBoundaries(enemyBullets);
        // call of the function that check if playerBullets are outside boundaries and replace the actual vector
        playerBullets = checkBulletOutsideBoundaries(playerBullets);

        //update particles
        for (int i = 0; i < particles.size(); i++)
        {
            if (particles.at(i)->getOpacity() > 0) {
                particles.at(i)->move();
            }
            else {
                particles.erase(particles.begin() + i);
            }
        }
        //cout << "Player bullets: " << playerBullets.size() << endl;
        //cout << "Enemy bullets: " << enemyBullets.size() << endl;
        //cout << "Timer: " << gameTime << endl;
        //cout << "nStars: " << nStars << endl;
    glutPostRedisplay();
    }// end of gameTimer

}

//main loop
int main(int argc, char** argv) {
    //Init window system
    glutInit(&argc, argv);

    //Define display mode
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    //Define window start position
    glutInitWindowPosition(0, 0);

    //Define window size
    glutInitWindowSize(800, 800);

    //Create window with name
    glutCreateWindow("Space Shooter");

    //Set display callback
    glutDisplayFunc(drawMenu);

    //Set keyboard callback
    glutKeyboardFunc(menuKeyboard);

    //Set game timer function
    gameTimer(1);

    //Set player shoot timer
    playerShootTimer(1);

    //Run the main loop
    glutMainLoop();

    return 0;
}
