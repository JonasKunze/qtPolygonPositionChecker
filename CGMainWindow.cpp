
#include "CGMainWindow.h"
#include "CGView.h"

#include <QMenu>
#include <QFrame>
#include <QMenuBar>
#include <QApplication>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QFileDialog>
#include <QKeyEvent>

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>


CGMainWindow::CGMainWindow (QWidget* parent, Qt::WindowFlags flags)
: QMainWindow (parent, flags) {
    resize (604, 614);

    // Create a menu
    QMenu *file = new QMenu("&File",this);
    file->addAction ("Load polygon", this, SLOT(loadPolygon()), Qt::CTRL+Qt::Key_L);
    file->addAction ("Save polygon", this, SLOT(savePolygon()), Qt::CTRL+Qt::Key_S);
    file->addAction ("Quit", qApp, SLOT(quit()), Qt::CTRL+Qt::Key_Q);

    QMenu *options = new QMenu("&Options",this);
    options->addAction ("Contour/Filling", this, SLOT(fillPolygon()), Qt::CTRL+Qt::Key_F);

    menuBar()->addMenu(file);
    menuBar()->addMenu(options);

    // Create a nice frame to put around the OpenGL widget
    QFrame* f = new QFrame (this);
    f->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    f->setLineWidth(2);

    // Create our OpenGL widget
    ogl = new CGView (this,f);

    // Put the GL widget inside the frame
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(ogl);
    layout->setMargin(0);
    f->setLayout(layout);

    setCentralWidget(f);

    statusBar()->showMessage("Ready",1000);
}

CGMainWindow::~CGMainWindow () { }

void CGMainWindow::fillPolygon() {
    ogl->fillMode = (ogl->fillMode+1)%3;
    ogl->updateGL();
}

void CGMainWindow::savePolygon() {
    QString fn = QFileDialog::getSaveFileName(this, "Save as ...", QString(), "POL files (*.pol)" );

    if (fn.isEmpty()) return;
    statusBar()->showMessage ("Saving polygon ...");
    std::ofstream file(fn.toLatin1());
    file.close();
}

void CGMainWindow::loadPolygon() {
    QString fn = QFileDialog::getOpenFileName(this, "Load polygon ...", QString(), "POL files (*.pol)" );

    if (fn.isEmpty()) return;
    statusBar()->showMessage ("Loading polygon ...");
    std::ifstream file(fn.toLatin1());
    double x,y;
    int m,n;

    ogl->minX = ogl->minY = std::numeric_limits<double>::max();
    ogl->maxX = ogl->maxY = -ogl->minX;

    file >> n;
    ogl->poly.resize(n);
    for(int i=0;i<n;i++) {
        file >> m;
        ogl->poly[i].resize(3*m);
        for(int j=0;j<m;j++) {
            file >> x >> y;
            if (x < ogl->minX) ogl->minX = x;
            else if (x > ogl->maxX) ogl->maxX = x;
            if (y < ogl->minY) ogl->minY = y;
            else if (y > ogl->maxY) ogl->maxY = y;
            ogl->poly[i][3*j+0] = x;
            ogl->poly[i][3*j+1] = y;
            ogl->poly[i][3*j+2] = 0.0;
        }
    }
    file.close();

    std::cout << "minX = " << ogl->minX << std::endl;
    std::cout << "maxX = " << ogl->maxX << std::endl;
    std::cout << "minY = " << ogl->minY << std::endl;
    std::cout << "maxY = " << ogl->maxY << std::endl;

    ogl->zoom = 2.0/std::max(ogl->maxX-ogl->minX,ogl->maxY-ogl->minY);
    ogl->centerX = (ogl->minX+ogl->maxX)/2;
    ogl->centerY = (ogl->minY+ogl->maxY)/2;

    ogl->updateGL();
    statusBar()->showMessage ("Loading polygon done.",3000);
}

void CGMainWindow::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_I: std::cout << "I" << std::flush; break;
    case Qt::Key_M: std::cout << "M" << std::flush; break;
    }

    ogl->updateGL();
}
