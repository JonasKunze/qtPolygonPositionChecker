#ifndef CGVIEW_H
#define CGVIEW_H

#include <QGLWidget>



#include "CGMainWindow.h"



#if _MSC_VER
    #include <gl/glu.h>
#elif __APPLE__
  #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

/*
 * Forward declarations
 *
 */

class QWidget;
class CGMainWindow;

// OGL Context
class CGView : public QGLWidget {
    Q_OBJECT
public:
    CGView(CGMainWindow*,QWidget*);

    void initializeGL();
    void worldCoord(int, int, double&, double&);

    std::vector<std::vector<double> > poly;
        double minX,minY,maxX,maxY;
    double centerX,centerY,zoom;
    int fillMode;
protected:
    void paintGL();
    void resizeGL(int,int);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);

    CGMainWindow *main;
    GLUtriangulatorObj* tobj;
};

#endif // CGVIEW_H
