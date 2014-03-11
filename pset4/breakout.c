//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// height and width of paddle
#define P_HEIGHT 500
#define P_WIDTH 162

// height and width of bricks
#define B_HEIGHT 10
#define B_WIDTH 33

//height and width of ball
#define BALL_HEIGHT 290
#define BALL_WIDTH 190


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    double y_velocity = 2.0;
    double x_velocity = drand48() * 2;
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // Beginning of Paddle Movement
        GMouseEvent e = getNextEvent(MOUSE_EVENT);
        if (e != NULL)
        {
            if (getEventType(e) == MOUSE_MOVED && paddle != NULL)
            {           
                double x = getX(e) - getWidth(paddle)/2;
                double y = P_HEIGHT;
                setLocation (paddle,x,y);
            }
        } 
        // End of Paddle Movement
        
        
        //Beginning of Ball Movement
        
                      
        move(ball, x_velocity, y_velocity);
               
        if (getY(ball) + getWidth(ball) >= getHeight(window))
        {
            lives--;
            setLocation(ball, 200, 300);
            x_velocity = drand48();
            waitForClick();
        }
        else if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
        else if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            x_velocity = -x_velocity;
        }
        else if (getX(ball) <= 0)
        {
            x_velocity = -x_velocity;
        }
        pause(5);
        
        // End of Ball Movement
        
        //Beginning of Collision
        GObject ball_c = detectCollision(window, ball);
	    if (ball_c == paddle)
	    {
            y_velocity = -y_velocity;
	    }
	    if (ball_c != NULL && ball_c != paddle)
        {      
            if (strcmp(getType(ball_c), "GRect") == 0)
            {
                y_velocity = -y_velocity;
                removeGWindow(window, ball_c);
                bricks--;
                points++;
                updateScoreboard(window, label, points);
            }
        }
        //End of Collision
    }
    
    //If player gets all 50 bricks
    if (points == 50)
    {
        printf("You win!!!!\n");
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int x;
    int y = 30;
    for (int j = 0; j < ROWS; j++)
    {
        x = 10;
        
        for (int i = 0; i < COLS; i++)
        {
            
            GRect initBricks = newGRect(x,y,B_WIDTH,B_HEIGHT);
            add(window, initBricks);
            x = x + 38;
            if (j == 0 || j == 4)
            {
                setColor(initBricks, "RED");
                setFilled(initBricks, true);
            }
            else if (j == 1 || j == 3)
            {
                setColor(initBricks, "ORANGE");
                setFilled(initBricks, true);
            }
            else if (j == 2)
            {
                setColor(initBricks, "YELLOW");
                setFilled(initBricks, true);
            }
            
        }
        y = y + 15;
    }
    return;
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval initBall = newGOval(BALL_WIDTH,BALL_HEIGHT,RADIUS * 2,RADIUS * 2);
    setFilled(initBall, true);
    add(window, initBall);
    return initBall;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect initPaddle = newGRect(P_WIDTH,P_HEIGHT,75,8);
    setFilled(initPaddle, true);
    setColor(initPaddle, "BLUE");
    add(window, initPaddle);
    return initPaddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel initScoreboard;
    initScoreboard = newGLabel("0");
    
    setFont(initScoreboard, "SansSerif-70"); //Font:SansSerif, Size: 70
    
    double x = (getWidth(window) - getWidth(initScoreboard)) / 2;
    double y = (getHeight(window) + getFontAscent(initScoreboard)) / 3;
    
    setLocation(initScoreboard, x, y);
    sendToBack(initScoreboard); //Sends object to the back of the layers
    setColor(initScoreboard, "GRAY");
    
    add(window,initScoreboard);
    
    return initScoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
