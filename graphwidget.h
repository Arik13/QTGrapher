#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "openglcontroller.h"
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include <qopenglfunctions.h>
#include "keyboardstatemap.h"

/*
 * A Qt widget which is responsible for:
 *      - Providing a surface for opengl to draw onto
 *      - Translating qt events for the opengl controller, in order to keep the opengl code portable
 *      - Telling the openGL controller when to render
 *      - Communicating graphing instructions (add/delete) to the controller
 *      - Passing camera movement commands (WASD and mouse moves) to the controller
 *      - Entering and exiting camera control mode through mouse clicks and ESC key
 */
class GraphWidget : public QOpenGLWidget, public QOpenGLFunctions  {
    Q_OBJECT

public:
    GraphWidget(QWidget *parent) : QOpenGLWidget(parent) {
        // Cache width and height
        auto r = this->contentsRect();
        width = r.width();
        height = r.height();

        // Starts the render loop
        connect(&timer, &QTimer::timeout, this, &GraphWidget::refresh);
        timer.start(0);
        create();
    }
    void initializeGL() override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void toggleInCameraControlMode();

public slots:
    void refresh();
    void addFunction(std::string fs);
    void deleteFunction(int index);
private:
    OpenGLController controller;
    QTimer timer;
    KeyboardStateMap ksMap;
    bool isInCameraControlMode = true;
    int width;
    int height;
};

#endif // GRAPHWIDGET_H
