#include <QApplication>
#include <QGLFormat>

#include <iostream>

#include <iostream>

#include "CGMainWindow.h"

#ifdef max
#undef max
#endif

int main (int argc, char **argv) {
    QApplication app(argc, argv);

	if (!QGLFormat::hasOpenGL()) {
		qWarning ("This system has no OpenGL support. Exiting.");
		return 1;
	}

	CGMainWindow *w = new CGMainWindow(NULL);

	w->show();

	return app.exec();
}

