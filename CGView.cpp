
#include "CGView.h"

#include <iostream>

#include <QMouseEvent>


CGView::CGView (CGMainWindow *mainwindow,QWidget* parent ) : QGLWidget (parent) {
    main = mainwindow;
}

void CGView::initializeGL() {
    qglClearColor(Qt::white);
    zoom = 1.0;
    fillMode = 0;

    tobj = gluNewTess();
#ifdef _MSC_VER
    gluTessCallback(tobj,(GLenum)GLU_TESS_BEGIN, (void(APIENTRY*)()) glBegin);
    gluTessCallback(tobj,(GLenum)GLU_TESS_VERTEX,(void(APIENTRY*)()) glVertex3dv);
    gluTessCallback(tobj,(GLenum)GLU_TESS_END,   (void(APIENTRY*)()) glEnd);
#elif __MINGW32__
    gluTessCallback(tobj,(GLenum)GLU_TESS_BEGIN, (void(APIENTRY*)()) glBegin);
    gluTessCallback(tobj,(GLenum)GLU_TESS_VERTEX,(void(APIENTRY*)()) glVertex3dv);
    gluTessCallback(tobj,(GLenum)GLU_TESS_END,   (void(APIENTRY*)()) glEnd);
#else
    gluTessCallback(tobj,(GLenum)GLU_TESS_BEGIN, (void(*)())glBegin);
    gluTessCallback(tobj,(GLenum)GLU_TESS_VERTEX,(void(*)())glVertex3dv);
    gluTessCallback(tobj,(GLenum)GLU_TESS_END,   (void(*)())glEnd);
#endif
    gluTessProperty(tobj,GLU_TESS_BOUNDARY_ONLY,GL_FALSE);
}

void CGView::paintGL() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScaled(zoom,zoom,1.0);
    glTranslated(-centerX,-centerY,0.0);

    glClear(GL_COLOR_BUFFER_BIT);

    if (fillMode > 0) {
        glColor3f(0.0f,1.0f,0.0f);
        for(int i=0;i<(int) poly.size();i++) {
            gluTessBeginPolygon(tobj,NULL);
            gluTessBeginContour(tobj);
            for(int j=0;j<(int) poly[i].size()/3;j++)
                gluTessVertex(tobj,&poly[i][3*j],&poly[i][3*j]);
            gluTessEndContour(tobj);
            gluTessEndPolygon(tobj);
        }
    }

    if (fillMode % 2 == 0) {
        glColor3f(0.0f,0.0f,0.0f);
        for(int i=0;i<(int) poly.size();i++) {
            glBegin(GL_LINE_STRIP);
            for(int j=0;j<(int) poly[i].size()/3;j++)
                glVertex2d(poly[i][3*j+0],poly[i][3*j+1]);
            glEnd();
        }
    }
}

void CGView::resizeGL(int width, int height) {
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width > height) {
        double ratio = width/(double) height;
        gluOrtho2D(-ratio,ratio,-1.0,1.0);
    }
    else {
        double ratio = height/(double) width;
        gluOrtho2D(-1.0,1.0,-ratio,ratio);
    }
    glMatrixMode (GL_MODELVIEW);
}

void CGView::worldCoord(int x, int y, double &dx, double &dy) {
    if (width() > height()) {
        dx = (2.0*x-width())/height();
        dy = 1.0-2.0*y/(double) height();
    } else {
        dx = 2.0*x/(double) width()-1.0;
        dy = (height()-2.0*y)/width();
    }
    dx /= zoom;
    dy /= zoom;
    dx += centerX;
    dy += centerY;
}



void CGView::mousePressEvent(QMouseEvent *event) {
    double dx, dy;
    worldCoord(event->x(),event->y(),dx,dy);
    std::cout << "Mouse pressed at (" << dx << "," << dy <<")" << std::endl;

    double px = dx;
    double py = dy;
    double ux,uy,vx,vy;
    int i = 0;
    int intersect = 0;
    for(int j=0;j<(int) poly[i].size()/3-1;j++){

        // ADD YOUR INTERSECT CODE HERE!

    }
    std::cout << ((intersect%2==1)?"inside":"outside") << std::endl;


}

void CGView::mouseReleaseEvent (QMouseEvent* event) {
    std::cout << "Mouse released" << std::endl;
}

void CGView::wheelEvent(QWheelEvent* event) {
    if (event->delta() < 0) zoom *= 1.1; else zoom *= 1/1.1;
    update();
}

void CGView::mouseMoveEvent (QMouseEvent* event) {
    QPoint current = event->pos();
    std::cout << "Mouse moved" << std::endl;

    int x = current.x();
    int y = current.y();
    if (event->button() == Qt::LeftButton)
        updateGL();
}
