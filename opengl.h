#ifndef OPENGL_H
#define OPENGL_H
#include <gl/glew.h>
#include <QGLWidget>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <gl/glut.h>
#include <glm/glm/glm.hpp>
#include <math.h>




class opengl : public QGLWidget
{
    Q_OBJECT
public:
    explicit opengl(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void movingstuff(void);
signals:
    
public slots:

private:
QTimer time;

};

#endif // OPENGL_H
