#include "opengl.h"
#define _USE_MATH_DEFINES


float m_distance;
float mx=NULL;
float my=NULL;
int lastX;
int lastY;
int xRot;
int yRot;
int lastzoom;
int xmove;
int ymove;
int lastmovex;
int lastmovey;

GLfloat angle = 0.0;

opengl::opengl(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&time,SIGNAL(timeout()),this,SLOT(updateGL()));
        time.start(16);
    setMouseTracking(true);
}

void opengl::initializeGL()
{
    glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_SPECULAR);
    glEnable(GL_AMBIENT);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DIFFUSE);
    glEnable(GL_SHININESS);
    glEnable(GL_COLOR);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void opengl::movingstuff(void)
{
glTranslatef(0.0f, -6.0f, -50.0f);	// Move 40 Units And Into The Screen
    glTranslatef(0, 0, -m_distance);
    time.stop();
    glTranslatef(xmove/100,ymove/100,0);
    time.stop();
    glRotatef(xRot, 1, 0, 0);
    time.stop();
    glRotatef(yRot, 0, 1, 0);
    time.stop();
}

void opengl::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            movingstuff();
            glutSolidTeapot(10);
           time.start();
}

void opengl::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0f,(float)w/h,0.01,1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);
}

void opengl::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastX;
           int dy = event->y() - lastY;

           if (event->buttons() & Qt::LeftButton)
           {
               xRot += 3 * dy;
               yRot += 3 * dx;
           }
           else if (event->buttons() & Qt::RightButton)
           {
               xRot += 3 * dy;
               yRot += 3 * dx;
           }
           else if (event->buttons() & Qt::MiddleButton)
           {
               xmove += 3 * dx;
               ymove -= 3 * dy;

           }

           lastX = event->pos().x();
           lastY = event->pos().y();
           lastmovex = event->pos().x();
           lastmovey = event->pos().y();
}

void opengl::mousePressEvent(QMouseEvent *event)
{
    lastX = event->pos().x();
        lastY = event->pos().y();
        lastmovex=event->pos().x();
        lastmovey=event->pos().y();
}

void opengl::wheelEvent(QWheelEvent *event)
{
 m_distance += (event->delta()/120);
}
