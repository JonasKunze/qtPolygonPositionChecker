#ifndef CGMAINWINDOW_H
#define CGMAINWINDOW_H

#include <qnamespace.h>

#include "QMainWindow"



class CGView;

/// Main Window
class CGMainWindow : public QMainWindow {
    Q_OBJECT
public:
    CGMainWindow (QWidget* parent = 0, Qt::WindowFlags flags = Qt::Window);
    ~CGMainWindow ();
public slots:
    void loadPolygon();
    void savePolygon();
    void fillPolygon();
public:
protected:
    void keyPressEvent(QKeyEvent*);
private:
    CGView *ogl;
};

#endif // CGMAINWINDOW_H
