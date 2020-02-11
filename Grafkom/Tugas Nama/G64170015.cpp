#include <GLFW/glfw3.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;

float countDownSpeed = 10.0f;

// Timer variable
double timer;
double timeLim1 = 3.0;
double timeLim2 = 6.0;
double timeLim3 = 9.0;

//Background color variable
float red = 1.0, green =  0.596, blue = 0.0;
float countRandomCircle = 0.0;
int isColorChange = 0;
double limitRandom = 1.0;

//State Variable
int activateMainPart = 0;
int activateOpeningPart3 = 0;
int activateOpeningPart2 = 0;
int activateOpeningPart1 = 0;
int activateStartLayer = 1;
int activateNameMovement = 0;

//Dynamic variable for moving letter F
float fX = 0.0f;
float fXmax, fXmin;
float fSpeed = 0.1f;

//Dynamic variable for moving letter A
float aY = 0.0f;
float aYmax, aYmin;
float aSpeed = 0.1f;

//Dynamic variable for moving letter R
float rY = 0.0f;
float rYmax, rYmin;
float rWordSpeed = 0.1f;

//Dynamic variable for moving letter I
float iX = 0.0f;
float iXmax, iXmin;
float iSpeed = 0.1f;

class Triangle
{
public:
    double x = 75.0, y = 0.1;
    // int red = 0, green = 255, blue = 0;
    int red = 255, green = 255, blue = 255;

    void display()
    {
        glBegin(GL_TRIANGLES);
        glColor3d(red, green, blue);
        glVertex2f(-x, x);
        glVertex2f(-x, -x);
        glVertex2f(x, 0.0);
        glEnd();
    }

    GLboolean isTriangleSelected(double xpos, double ypos)
    {
        double left = -y;
        double right = y;
        double top = y;
        double bottom = -y;
        if ((xpos > left) && (xpos < right) && (ypos < top) && (ypos > bottom))
            return GL_TRUE;
        else
            return GL_FALSE;
    }

    void doWhenSelected(double xpos, double ypos)
    {
        if (isTriangleSelected(xpos, ypos) == GL_TRUE)
            red = blue = 255;
        else
            red = blue = 0;
    }

    void doWhenClicked(int button, int action, double xpos, double ypos)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            timer = glfwGetTime();
            activateNameMovement = 0;
            activateOpeningPart1 = 0;
            activateOpeningPart2 = 0;
            activateOpeningPart3 = 1;
            activateMainPart = 0;
            activateStartLayer = 0;
        }

    }
};
Triangle tri;

class Square
{
public:
    int rd = 157, gr = 159, bl = 158;
    void draw(double a, double b, double width, double height)
    {
        glBegin(GL_QUADS);
        glColor3ub(rd, gr, bl);
        glVertex2f(a, b);
        glVertex2f(a, b - height);
        glVertex2f(a + width, b - height);
        glVertex2f(a + width, b);
        glEnd();
    }
};
Square obj;

//Function Prototypes
void drawCircle(float cx, float cy, float r, int num_segments, float angle, float thickness);
void drawFilledCircle(float cx, float cy, float r, int num_segments, float angle, float thickness);
void drawRandomCircle(int radius);
void letterF(float fX);
void letterA(float aY);
void letterK();
void letterH();
void letterR(float rY);
void letterI(float iX);
void number1();
void number2();
void number3();
void changeBackgroundColor();
void gradientBackground();
void rollFilm();
void startPart();
void openingPart();
void openingPart1();
void openingPart2();
void openingPart3();

void setup_viewport(GLFWwindow *window)
{
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width,
                           &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(- 350, 350, -350, 350, 1.f,
            -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClearColor(red, green, blue, 0.0f); //Set Background color
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    //Dynamic Changing Background color,
    // if you activate this you must disable the gradientBackground()
    changeBackgroundColor();

    //Gradient Background
    // gradientBackground();
}

static void error_callback(int error, const char *description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        activateOpeningPart1 = 0;
        activateOpeningPart2 = 0;
        activateOpeningPart3 = 0;
        activateMainPart = 1;
        activateStartLayer = 0;
        activateNameMovement = 0;
    }
    if(key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        activateOpeningPart1 = 1;
        activateOpeningPart2 = 0;
        activateOpeningPart3 = 0;
        activateMainPart = 0;
        activateStartLayer = 0;
        activateNameMovement = 0;
    }
    if(key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        activateOpeningPart1 = 0;
        activateOpeningPart2 = 1;
        activateOpeningPart3 = 0;
        activateMainPart = 0;
        activateStartLayer = 0;
        activateNameMovement = 0;
    }
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        activateOpeningPart1 = 0;
        activateOpeningPart2 == 0;
        activateOpeningPart3 = 0;
        activateMainPart = 1;
        activateStartLayer = 0;
        activateNameMovement = 1;
    }

    if (key == GLFW_KEY_N && action == GLFW_PRESS)
    {
        activateOpeningPart1 = 0;
        activateOpeningPart2 == 0;
        activateOpeningPart3 = 0;
        activateMainPart = 1;
        activateStartLayer = 0;
        activateNameMovement = 0;
    }
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    tri.doWhenSelected(xpos, ypos);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    tri.doWhenClicked(button, action, xpos, ypos);
}

int main(void)
{
    GLFWwindow *window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(700, 700, "Muhammad Fakhri", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //Register Callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    float segment = 10.0, x = 0.0, y = 0.0;
    float r = 200.0f, rSpeed = 0.05;
    fXmin = 0.0f;
    fXmax = 184.24f;
    aYmin = 0.0f;
    aYmax = 290.04f;
    rYmin = 0.0f;
    rYmax = 290.04f;
    iXmin = 0.0f;
    iXmax = 180.6f;

    while (!glfwWindowShouldClose(window))
    {
        setup_viewport(window);
        display();

        if (activateStartLayer)
            startPart();
        else if(activateOpeningPart1)
        {
            openingPart1();
        }
        else if(activateOpeningPart2)
            openingPart2();
        else if(activateOpeningPart3)
        {
            //Activate code below if you want auto countdown;
            openingPart();
            //Activate code below if you want manual countdown;
            // openingPart3();
        }
        else if (activateMainPart)
        {
            glColor3d(0.018, 0.659, 0.959);
            if (activateNameMovement)
            {
                //Moving F Speed
                fX += fSpeed;
                //Check if the F letter exceeds the edges
                if (fX > fXmax)
                {
                    fX = fXmax;
                    fSpeed = -fSpeed;
                }
                else if (fX < fXmin)
                {
                    fX = fXmin;
                    fSpeed = -fSpeed;
                }

                //Moving A Speed
                aY += aSpeed;
                //Check if the F letter exceeds the edges
                if (aY > aYmax)
                {
                    aY = aYmax;
                    aSpeed = -aSpeed;
                }
                else if (aY < aYmin)
                {
                    aY = aYmin;
                    aSpeed = -aSpeed;
                }

                //Moving R Speed
                rY += rWordSpeed;
                //Check if the F letter exceeds the edges
                if (rY > rYmax)
                {
                    rY = rYmax;
                    rWordSpeed = -rWordSpeed;
                }
                else if (rY < rYmin)
                {
                    rY = rYmin;
                    rWordSpeed = -rWordSpeed;
                }

                //Moving I Speed
                iX += iSpeed;
                //Check if the F letter exceeds the edges
                if (iX > iXmax)
                {
                    iX = iXmax;
                    iSpeed = -iSpeed;
                }
                else if (iX < iXmin)
                {
                    iX = iXmin;
                    iSpeed = -iSpeed;
                }

                letterF(fX);
                letterA(aY);
                letterR(rY);
                letterI(iX);
                glPushMatrix();
                glRotatef((float) glfwGetTime() * 100.0f, 0.f, 0.f, 1.f);
                letterK();
                glPopMatrix();
                glPushMatrix();
                glRotatef((float) glfwGetTime() * -100.0f, 0.f, 0.f, 1.f);
                letterH();
                glPopMatrix();
                drawRandomCircle(15);
            }
            else
            {
                letterF(fX);
                letterA(aY);
                letterK();
                letterH();
                letterR(rY);
                letterI(iX);
            }

            // Draw the circle around name letter
            glPushMatrix();
            drawCircle(x, y, r, round(segment), 50, 5);
            glPopMatrix();

            // Dynamic Circle Shape
            if(segment < 30)
                segment += 0.01 ;
            else
                segment = 4.0;

            // Dynamic circle radius
            if (r > 250)
            {
                r = 250.0f;
                rSpeed = -rSpeed;
            }
            else if (r < 200)
            {
                r = 200.0f;
                rSpeed = -rSpeed;
            }
            r += rSpeed;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void changeBackgroundColor()
{
    // Random Background Color
    // red =((float)rand()/(float)(RAND_MAX)) * limitRandom;
    // blue =((float)rand()/(float)(RAND_MAX)) * limitRandom;
    // green =((float)rand()/(float)(RAND_MAX)) * limitRandom;
    if(red <= 1.0 && isColorChange == 0)
    {
        red += 0.001;
        green += 0.001;
        blue += 0.001;
    }
    else
    {
        isColorChange = 1;
        red -= 0.001;
        green -= 0.001;
        blue -= 0.001;
        if(red <= 0.0)
            isColorChange = 0;
    }
}

void gradientBackground()
{
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.596, 0.0);
    glVertex2f(-350, 350);
    glVertex2f(350, 350);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(350, -350);
    glVertex2f(-350, -350);
    glEnd();
}

void drawCircle(float cx, float cy, float r, int num_segments, float angle, float thickness)
{
    glRotatef((float) glfwGetTime() * angle, 0.f, 0.f, 1.f);
    glLineWidth(thickness);
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0 * 3.1415926 * (float)ii / (float)num_segments;//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}

void drawFilledCircle(float cx, float cy, float r, int num_segments, float angle, float thickness)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0 * 3.1415926 * (float)ii / (float)num_segments;//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}

void drawRandomCircle(int radius)
{
    glColor3ub(194, 25, 25);
    float skala = rand() % 3;
    glScalef(skala, skala, skala);
    drawFilledCircle(rand() % 350, rand() % 350, radius, 100, 50, 5);
    drawFilledCircle(rand() % 350, rand() % 350, radius, 100, 50, 5);
    drawFilledCircle(rand() % 350, -1 * (rand() % 350), radius, 100, 50, 5);
    drawFilledCircle(-1 * (rand() % 350), rand() % 350, radius, 100, 50, 5);
    drawFilledCircle(-1 * (rand() % 350), -1 * (rand() % 350), radius, 100, 50, 5);
}

void letterF(float fX)
{
    glBegin(GL_POLYGON);
    glVertex2f(-165.76 - fX, 81.21);
    glVertex2f(-165.76 - fX, -83.79);
    glVertex2f(-173.26 - fX, -83.79);
    glVertex2f(-173.26 - fX, 88.71);
    glVertex2f(-143.26 - fX, 88.71);
    glVertex2f(-143.26 - fX, 81.21);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-165.76 - fX, 6.21);
    glVertex2f(-165.76 - fX, -1.29);
    glVertex2f(-143.26 - fX, -1.29);
    glVertex2f(-143.26 - fX, 6.21);
    glEnd();
}

void letterA(float aY)
{
    glBegin(GL_POLYGON);
    glVertex2f(-85.68, 31.25 + aY);
    glVertex2f(-98.18, -83.79 + aY);
    glVertex2f(-104.43, -83.79 + aY);
    glVertex2f(-88.81, 59.96 + aY);
    glVertex2f(-82.56, 59.96 + aY);
    glVertex2f(-66.93, -83.79 + aY);
    glVertex2f(-73.18, -83.79 + aY);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-92.71, -33.79 + aY);
    glVertex2f(-93.49, -40.04 + aY);
    glVertex2f(-77.87, -40.04 + aY);
    glVertex2f(-78.65, -33.79 + aY);
    glEnd();
}

void letterK()
{
    glBegin(GL_POLYGON);
    //glColor3d(1,0,0);
    glVertex2f(-28.45, 31.21);
    glVertex2f(-28.45, -83.79);
    glVertex2f(-23.45, -83.79);
    glVertex2f(-23.45, 31.21);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-20.02, -26.29);
    glVertex2f(-3.45, -83.79);
    glVertex2f(-8.45, -83.79);
    glVertex2f(-23.45, -31.91);
    glVertex2f(-23.45, -20.66);
    glVertex2f(-8.45, 31.21);
    glVertex2f(-3.45, 31.21);
    glEnd();
}

void letterH()
{
    glBegin(GL_POLYGON);
    //glColor3d(1,0,0);
    glVertex2f(34.2, 31.21);
    glVertex2f(34.2, -83.79);
    glVertex2f(39.2, -83.79);
    glVertex2f(39.2, 31.21);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(39.2, -23.79);
    glVertex2f(39.2, -28.79);
    glVertex2f(49.2, -28.79);
    glVertex2f(49.2, -23.79);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(49.2, 31.21);
    glVertex2f(49.2, -83.79);
    glVertex2f(54.2, -83.79);
    glVertex2f(54.2, 31.21);
    glEnd();
}

void letterR(float rY)
{
    glBegin(GL_POLYGON);
    glVertex2f(94.67, 59.96 - rY);
    glVertex2f(94.67, -83.79 - rY);
    glVertex2f(100.92, -83.79 - rY);
    glVertex2f(100.92, 59.96 - rY);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(107.17, -15.04 - rY);
    glVertex2f(100.92, -15.04 - rY);
    glVertex2f(100.92, -8.79 - rY);
    glVertex2f(107.17, -8.79 - rY);
    glVertex2f(113.23, -13.47 - rY);
    glVertex2f(119.67, -83.79 - rY);
    glVertex2f(113.42, -83.79 - rY);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(113.42, -2.54 - rY);
    glVertex2f(107.17, -8.79 - rY);
    glVertex2f(113.23, -13.47 - rY);
    glVertex2f(119.67, -2.54 - rY);
    glVertex2f(119.67, 47.46 - rY);
    glVertex2f(113.23, 47.46 - rY);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(107.17, 53.71 - rY);
    glVertex2f(100.92, 53.71 - rY);
    glVertex2f(100.92, 59.96 - rY);
    glVertex2f(107.17, 59.96 - rY);
    glVertex2f(119.67, 47.46 - rY);
    glVertex2f(113.42, 47.46 - rY);
    glEnd();
}

void letterI(float iX)
{
    glBegin(GL_POLYGON);
    glVertex2f(161.9 + iX, 88.71);
    glVertex2f(161.9 + iX, -83.79);
    glVertex2f(169.4 + iX, -83.79);
    glVertex2f(169.4 + iX, 88.71);
    glEnd();
}

void rollFilm()
{
    //Black Background
    glBegin(GL_QUADS);
    glColor3d(0, 0, 0);
    glVertex2f(-350.0f, 350.0f);
    glVertex2f(-350.0f, -350.0f);
    glVertex2f(350.0f, -350.0f);
    glVertex2f(350.0f, 350.0f);
    glEnd();

    //Little Square Side
    obj.draw(-320.0f, 210.0f, 80.0f, 100.0f);
    obj.draw(-320.0f, 50.0f, 80.0f, 100.0f);
    obj.draw(-320.0f, -110.0f, 80.0f, 100.0f);
    obj.draw(240.0f, -110.0f, 80.0f, 100.0f);
    obj.draw(240.0f, 50.0f, 80.0f, 100.0f);
    obj.draw(240.0f, 210.0f, 80.0f, 100.0f);

    // Little Square Corner
    obj.draw(240.0f, 350.0f, 80.0f, 80.0f);
    obj.draw(240.0f, -270.0f, 80.0f, 80.0f);
    obj.draw(-320.0f, 350.0f, 80.0f, 80.0f);
    obj.draw(-320.0f, -270.0f, 80.0f, 80.0f);

    // Middle Square Up and Bottom
    obj.draw(-210.0f, 350.0f, 420.0f, 80.0f);
    obj.draw(-210.0f, -270.0f, 420.0f, 80.0f);

    // Main Square
    obj.draw(-210.0f, 210.0f, 420.0f, 420.0f);

    //Vertical and Horizontal lines
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 210.0f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, -210.0f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(210.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-210.0f, 0.0f);
    glEnd();
}

void number1()
{
    glBegin(GL_POLYGON);
    glColor3ub(52, 52, 52);
    glVertex2f(-8.93, 52.04);
    glVertex2f(-41.93, 42.79);
    glVertex2f(-50.43, 72.29);
    glVertex2f(-4.43, 88.54);
    glVertex2f(25.57, 88.54);
    glVertex2f(25.57, -86.46);
    glVertex2f(-8.93, -86.46);
    glEnd();
}

void number2()
{
    glBegin(GL_POLYGON);
    glColor3ub(52, 52, 52);
    glVertex2f(-9.28, -48.05);
    glVertex2f(51.21, -48.05);
    glVertex2f(51.21, -78.64);
    glVertex2f(-56.43, -78.64);
    glVertex2f(-56.43, -54.95);
    glVertex2f(16.94, 33.83);
    glVertex2f(48.68, 34.98);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-3.99, 54.76);
    glVertex2f(-30.9, 35.9);
    glVertex2f(-57.58, 51.54);
    glVertex2f(-35.73, 76.84);
    glVertex2f(-4.45, 85.58);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(11.07, 49.01);
    glVertex2f(-3.99, 54.76);
    glVertex2f(-4.45, 85.58);
    glVertex2f(33.04, 71.89);
    glVertex2f(48.68, 34.98);
    glVertex2f(16.94, 33.83);
    glEnd();
}

void number3()
{
    glColor3ub(52, 52, 52);
    glBegin(GL_POLYGON);
    glVertex2f(8.85, 53.26);
    glVertex2f(-54.17, 53.26);
    glVertex2f(-54.17, 82.93);
    glVertex2f(47.03, 82.93);
    glVertex2f(47.03, 56.71);
    glVertex2f(16.9, 17.61);
    glVertex2f(-22.89, 11.86);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(15.18, -12.52);
    glVertex2f(-10.7, -6.54);
    glVertex2f(-22.89, 11.86);
    glVertex2f(16.9, 17.61);
    glVertex2f(53.7, -28.39);
    glVertex2f(21.96, -28.39);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-3.8, -50.24);
    glVertex2f(21.96, -28.39);
    glVertex2f(53.7, -28.39);
    glVertex2f(-3.8, -81.29);
    glVertex2f(-59, -47.25);
    glVertex2f(-31.86, -31.61);
    glEnd();
}

void startPart()
{
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(-350.0, 350.0);
    glVertex2f(-350.0, -350.0);
    glVertex2f(350.0, -350.0);
    glVertex2f(350.0, 350.0);
    glEnd();
    tri.display();
    glBegin(GL_POLYGON);
    glVertex2f(-65.13, -95.86);
    glVertex2f(-65.13, -150.86);
    glVertex2f(-67.63, -150.86);
    glVertex2f(-67.63, -93.36);
    glVertex2f(-62.63, -93.36);
    glVertex2f(-62.63, -95.86);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-60.92, -96.64);
    glVertex2f(-62.63, -95.86);
    glVertex2f(-62.63, -93.36);
    glVertex2f(-59.12, -94.84);
    glVertex2f(-57.63, -98.36);
    glVertex2f(-60.13, -98.36);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-60.13, -118.636);
    glVertex2f(-60.92, -120.15);
    glVertex2f(-59.12, -121.95);
    glVertex2f(-57.63, -118.36);
    glVertex2f(-57.63, -98.36);
    glVertex2f(-60.13, -98.36);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-62.6, -120.86);
    glVertex2f(-65.1, -120.86);
    glVertex2f(-65.13, -123.36);
    glVertex2f(-62.63, -123.36);
    glVertex2f(-59.12, -121.95);
    glVertex2f(-60.88, -120.15);
    glEnd();
    // Huruf L
    glBegin(GL_POLYGON);
    glVertex2f(-40.6, -148.36);
    glVertex2f(-33.1, -148.36);
    glVertex2f(-33.1, -150.86);
    glVertex2f(-43.1, -150.86);
    glVertex2f(-43.1, -93.36);
    glVertex2f(-40.6, -93.36);
    glEnd();
    // Huruf A
    glBegin(GL_POLYGON);
    glVertex2f(-12.4, -104.84);
    glVertex2f(-17.4, -150.86);
    glVertex2f(-19.9, -150.86);
    glVertex2f(-13.65, -93.36);
    glVertex2f(-11.15, -93.36);
    glVertex2f(-4.9, -150.86);
    glVertex2f(-7.4, -150.86);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-15.21, -130.86);
    glVertex2f(-15.53, -133.36);
    glVertex2f(-9.28, -133.36);
    glVertex2f(-9.59, -130.86);
    glEnd();
    // Huruf Y
    glBegin(GL_POLYGON);
    glVertex2f(15.8, -116.33);
    glVertex2f(10.8, -93.36);
    glVertex2f(8.3, -93.36);
    glVertex2f(14.55, -122.11);
    glVertex2f(17.05, -122.11);
    glVertex2f(23.3, -93.36);
    glVertex2f(20.8, -93.36);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(14.55, -122.11);
    glVertex2f(14.55, -150.86);
    glVertex2f(17.05, -150.86);
    glVertex2f(17.05, -122.11);
    glEnd();
    // Tanda Tanya
    glBegin(GL_POLYGON);
    glVertex2f(50.14, -94.29);
    glVertex2f(41.42, -97.1);
    glVertex2f(39.5, -92.21);
    glVertex2f(51.5, -88.78);
    glVertex2f(65.9, -101.9);
    glVertex2f(58.94, -102.62);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(52.46, -115.74);
    glVertex2f(58.94, -102.62);
    glVertex2f(65.9, -101.9);
    glVertex2f(58.22, -117.74);
    glVertex2f(53.18, -129.82);
    glVertex2f(47.02, -129.9);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(47.02, -129.9);
    glVertex2f(47.34, -134.14);
    glVertex2f(53.34, -134.14);
    glVertex2f(53.34, -129.82);
    glEnd();
    drawFilledCircle(50.22f, -146.78f, 5.0f, 50, 50.0f, 3.0f);
}

void openingPart1()
{
    rollFilm();
    number1();
    drawCircle(0.0f, 0.0f, 110.0f, 50, 50.0f, 3.0f);
    drawCircle(0.0f, 0.0f, 180.0f, 50, 50.0f, 3.0f);
    glPushMatrix();
    glRotatef((float) glfwGetTime() * countDownSpeed, 0.f, 0.f, 1.f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 180.0f);
    glEnd();
    glPopMatrix();
}

void openingPart2()
{
    rollFilm();
    number2();
    drawCircle(0.0f, 0.0f, 110.0f, 50, 50.0f, 3.0f);
    drawCircle(0.0f, 0.0f, 180.0f, 50, 50.0f, 3.0f);
    glPushMatrix();
    glRotatef((float) glfwGetTime() * countDownSpeed, 0.f, 0.f, 1.f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 180.0f);
    glEnd();
    glPopMatrix();
}

void openingPart3()
{
    rollFilm();
    number3();
    drawCircle(0.0f, 0.0f, 110.0f, 50, 50.0f, 3.0f);
    drawCircle(0.0f, 0.0f, 180.0f, 50, 50.0f, 3.0f);
    glPushMatrix();
    glRotatef((float) glfwGetTime() * countDownSpeed, 0.f, 0.f, 1.f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 180.0f);
    glEnd();
    glPopMatrix();
}

void openingPart()
{
    if (glfwGetTime() - timer > timeLim3)
    {
        activateOpeningPart1 = 0;
        activateOpeningPart2 == 0;
        activateOpeningPart3 = 0;
        activateMainPart = 1;
        activateStartLayer = 0;
        activateNameMovement = 0;
    }
    else if (glfwGetTime() - timer > timeLim2)
        openingPart1();
    else if (glfwGetTime() - timer > timeLim1)
        openingPart2();
    else
        openingPart3();
}
