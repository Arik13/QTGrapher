#include "graphwidget.h"
#include <iostream>


void GraphWidget::initializeGL() {
    setFocusPolicy(Qt::ClickFocus);
    initializeOpenGLFunctions();
    controller.initialize();
}

// Proxies the paint commands to the openGL controller
void GraphWidget::paintGL() {
    controller.paint();
}

// Stores the key as pressed in a KeyStateMap, in order to smooth out the uneven timing of the default keyboard event system
void GraphWidget::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;
    if (event->key() == Qt::Key_Escape) {
        toggleInCameraControlMode();
    }
    ksMap[event->key()] = true;
}

// Stores the key as not pressed in a KeyStateMap, in order to smooth out the uneven timing of the default keyboard event system
void GraphWidget::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;
    ksMap[event->key()] = false;
}

// Updates the cached width and height after a resize
void GraphWidget::resizeEvent(QResizeEvent *e) {
    width = e->size().width();
    height = e->size().width();
}

// When the widget is clicked, toggle we
void GraphWidget::mouseReleaseEvent(QMouseEvent *event) {
    toggleInCameraControlMode();
}

// Toggles whether the user is in camera control mode, which takes control of the mouse in order to move the camera
void GraphWidget::toggleInCameraControlMode() {
    QCursor c = cursor();
    auto p2 = mapToGlobal(QPoint(width/2, height/2));
    c.setPos(p2);
    isInCameraControlMode = !isInCameraControlMode;
    (isInCameraControlMode)? c.setShape(Qt::ArrowCursor) : c.setShape(Qt::BlankCursor);
    setCursor(c);
}

// Notifies the openGL controller of camera movements and tells Qt to repaint the widget
void GraphWidget::refresh() {
    makeCurrent();
    if (!isInCameraControlMode) {
        // Notify controller of cursor moves & movement keys pressed
        auto p = this->mapFromGlobal(QCursor::pos());
        controller.update(&ksMap, p.x()-width/2, p.y()-height/2);

        // Reset cursor
        QCursor c = cursor();
        auto p2 = mapToGlobal(QPoint(width/2, height/2));
        c.setPos(p2);
        setCursor(c);
    }
    update();
    doneCurrent();
}

// Adds a function to the openGL controller to be graphed
void GraphWidget::addFunction(std::string fs) {
    makeCurrent();
    controller.addFunction(fs);
    doneCurrent();
}

// Tells the openGL controller to delete a function graph
void GraphWidget::deleteFunction(int index) {
    controller.deleteFunction(index);
}
