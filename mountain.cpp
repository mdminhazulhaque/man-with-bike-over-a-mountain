#include <GL/glut.h> /* OpenGL Utility Toolkit */
#include <cmath> /* Some sin/cos calculations */
#include <cstdlib>
#include <iostream> /* Basic C++ */

#ifdef __linux__
#include <unistd.h>
#include <GL/gl.h> /* OpenGL header*/
#include <GL/glu.h> /* OpenGL Utility */
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

#define TWOPI 6.28318 /* Value of 2xPi */
#define AXMAX 1 /* Axis maximum unit */
#define AXMIN -(AXMAX) /* Axis minimum unit */
#define CIRCLESLICES 100

float zAxis = -18; /* Viewport Zoom */
float yAxis = 1.0; /* Y-axis */
float angle = 0; /*  Rotation unit initial value*/
float anglestep = 1.0; /* Rotation step value */
float axis = 0; /* Axis */
float axisstep = 0.005; /* Axis step value */
bool touchedMax = false; /* For up-down purpose */
///\NOTE: Grey circle, for wheel and head

void DrawCircle(float x, float y, float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.25f,0.25f,0.25f); /* Grey color */
    glVertex2f(x, y); /* Set center */
    for(int i=0; i<=CIRCLESLICES; i++)
    {
        glVertex2f(
            x + (radius * cos(i * TWOPI / CIRCLESLICES)),
            y + (radius * sin(i * TWOPI / CIRCLESLICES))
        ); /* Draw circle borders */
    }
    glColor3f(0.0f,0.0f,0.0f); /* Reset color */
    glEnd();
}

///\NOTE: Yellow lines, constructing wheel rim

void DrawRim(float x1, float y1, float x2, float y2, float width)
{
    float angle = atan2(y2 - y1, x2 - x1); /* Two equal triangle creates a bold line */
    float tsina = width / 2 * sin(angle);
    float tcosa = width / 2 * cos(angle);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,1.0f,0.0f); /* Yellow color */
    glVertex2f(x1 + tsina, y1 - tcosa);
    glVertex2f(x2 + tsina, y2 - tcosa);
    glVertex2f(x2 - tsina, y2 + tcosa);
    glVertex2f(x2 - tsina, y2 + tcosa);
    glVertex2f(x1 - tsina, y1 + tcosa);
    glVertex2f(x1 + tsina, y1 - tcosa);
    glColor3f(0.0f,0.0f,0.0f); /* Reset canvas color */
    glEnd();
}

///\NOTE: Orange rods, constructing bicycle body

void DrawRod(float x1, float y1, float x2, float y2, float width)
{
    float angle = atan2(y2 - y1, x2 - x1); /* Two equal triangle creates a bold line */
    float tsina = width / 2 * sin(angle);
    float tcosa = width / 2 * cos(angle);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,0.5f,0.0f); /* Orange color */
    glVertex2f(x1 + tsina, y1 - tcosa);
    glVertex2f(x2 + tsina, y2 - tcosa);
    glVertex2f(x2 - tsina, y2 + tcosa);
    glVertex2f(x2 - tsina, y2 + tcosa);
    glVertex2f(x1 - tsina, y1 + tcosa);
    glVertex2f(x1 + tsina, y1 - tcosa);
    glColor3f(0.0f,0.0f,0.0f); /* Reset canvas color */
    glEnd();
}

///\NOTE: Grey lines, human body

void DrawBody(float x1, float y1, float x2, float y2, float width)
{
    float angle = atan2(y2 - y1, x2 - x1); /* Two equal triangle creates a bold line */
    float tsina = width / 2 * sin(angle);
    float tcosa = width / 2 * cos(angle);

    glBegin(GL_TRIANGLES);
    glColor3f(0.25f,0.25f,0.25f); /* Grey color */
    glVertex2f(x1 + tsina, y1 - tcosa);
    glVertex2f(x2 + tsina, y2 - tcosa);
    glVertex2f(x2 - tsina, y2 + tcosa);
    glVertex2f(x2 - tsina, y2 + tcosa);
    glVertex2f(x1 - tsina, y1 + tcosa);
    glVertex2f(x1 + tsina, y1 - tcosa);
    glColor3f(0.0f,0.0f,0.0f); /* Reset canvas color */
    glEnd();
}

///\NOTE: GL initialization

void init()
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective(65.0, 4/3.0, 0.5, 100); /* Set perspective, ratio, z-axis seek and percentage */
    glMatrixMode(GL_MODELVIEW); /* Model matrix type, for rotating objects */
    gluLookAt(0,0, 4.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); /* Set camera */
    glColor3d(0,0,0); /* Canvas color */
}

///\NOTE: Keyboard integration

void keyboard(unsigned char key, int mousePositionX, int mousePositionY)
{
    switch(key)
    {
    case 'w':
        glutSetWindowTitle("W: Zoom In");
        if(zAxis>-10.0)
            break;
        zAxis++;
        break;
    case 's':
        glutSetWindowTitle("S: Zoom Out");
        if(zAxis<-30)
            break;
        zAxis--;
        break;
    case 'a':
        glutSetWindowTitle("A: Moving Left");
        if(yAxis<-15)
            break;
        yAxis-=0.5;
        break;
    case 'd':
        glutSetWindowTitle("D: Moving Right");
        if(yAxis>10)
            break;
        yAxis+=0.5;
        break;
    case ']':
        glutSetWindowTitle("Speeding Up");
        anglestep++;
        axisstep+=0.01;
        break;
    case '[':
        glutSetWindowTitle("Speeding Down");
        anglestep--;
        axisstep-=0.01;
        break;
    case 27:
        exit(1);
        break;
    default:
        break;
    }
}

///\NOTE: Main display function

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /// Moving mountain
    glPushMatrix();
    glTranslatef(0, -0.60,-5);
    glBegin(GL_POLYGON);
    glColor3f(0.1f,0.8f,0.0f); /* Grass color */
    float point = -4.5;
    glVertex2f(-4.5,-5);
    for(float i=point; i<=-point; i+=0.25)
        glVertex2f(i,sin(i)*axis*0.55);
    glVertex2f(4.5,-5);
    glColor3f(0.0f,0.0f,0.0f); /* Reset canvas color */
    glEnd();
    glPopMatrix();

    ///Front wheel
    glTranslatef(yAxis, axis, zAxis);
    glPushMatrix();
    glRotatef(angle,0,0,1); /* Rotate front wheel across Z-axis */
    DrawCircle(0,0,2.5);
    DrawRim(-2,0,2,0,0.5);
    DrawRim(0,2,0,-2,0.5);
    DrawRim(-1.41,1.41,1.41,-1.41,0.5);
    DrawRim(1.41,1.41,-1.41,-1.41,0.5);
    glPopMatrix();

    /// Rear wheel
    glTranslatef(7, axis/22, 0);
    glPushMatrix();
    glRotatef(angle,0,0,1); /* Rotate rear wheel across Z-axis */
    DrawCircle(0,0,2.5);
    DrawRim(-2,0,2,0,0.5);
    DrawRim(0,2,0,-2,0.5);
    DrawRim(-1.41,1.41,1.41,-1.41,0.5);
    DrawRim(1.41,1.41,-1.41,-1.41,0.5);
    glPopMatrix();

    /// Cycle body
    DrawRod(-7.15,-0.25,-5,6,0.5); /* Cycle front rod */
    DrawCircle(-6.95,-0.0,1); /* wheel rim */
    DrawBody(-1.95,3.5,-5,1.95,0.5); /* Back leg */
    DrawRod(-6,3.75,0.5,-0.25,0.5); /* Cycle base rod */
    DrawCircle(0,0,1); /* Wheel rim */

    /// Draw Man
    DrawCircle(-3,9,1.25); /* Head */
    DrawBody(-3,9,-2,3,0.5); /* Body */
    DrawBody(-6,5.5,-2.5,6.5,0.5); /* Hand */
    DrawBody(-1.95,3.5,-3.5,0,0.5); /* Front leg */

    angle += anglestep;
    /// Increase axis to MAX and then decrease it to MIN
    if(touchedMax)
        axis-=axisstep;
    else
        axis+=axisstep;
    if(axis>AXMAX)
        touchedMax=true;
    else if(axis<AXMIN)
        touchedMax=false;

#ifdef _WIN32
    Sleep(2); /* Slow down the loop, for visual comfort*/
#endif

#ifdef __linux__
    usleep(1125); /* 1.125 seconds,Slow down the loop, for visual comfort*/
#endif

    glutSwapBuffers(); /* Send the buffer to display */
    glutPostRedisplay(); /* Recall this function */
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); /* Pass args to GL */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(400,300);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Man Riding His Bike Over A Mountain");
    glutDisplayFunc(display); /* Draw shapes */
    glClearColor(1.0f, 1.0f, 1.0f,0.0f);
    glViewport(0,0, 400, 300);
    glutKeyboardFunc(keyboard);
    init(); /* Initialize basic GL settings */
    glutMainLoop(); /* There you go */
}
