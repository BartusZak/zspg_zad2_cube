#ifndef WINDOW_H
#define WINDOW_H

#include "glfunctions.h"

#include "cube.h"
#include "modelprogram.h"
#include "matma.h"

#include <ctime>

#include <QtGui/QWindow>
#include <QtGui/QScreen>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QtGui/QKeyEvent>
#include <QtGui/QOpenGLDebugLogger>

class Window : public QWindow, protected GLFunctions{
    Q_OBJECT
public:
    explicit Window(QWindow* parent=nullptr);
    virtual ~Window();
    virtual void render(QPainter *painter);

public slots:
    void render();

protected:
    void exposeEvent(QExposeEvent *event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent * event);

private:
    QOpenGLContext *context_;
    QOpenGLPaintDevice* device_;
    QOpenGLDebugLogger* logger_;

    void Initialize();
    void InitPrograms();
    void InitModels();
    void SetViewMatrix();
    void SetProjectionMatrix();

    void ZoomIn();
    void ZoomOut();
    void SetPerspectiveView();
    void SetPerpendicularView();

    Cube cube_;
    ModelProgram program_;

    Mat4 perpendicular_view_matrix_;
    Mat4 projection_matrix_;
    Mat4 view_matrix_;

    clock_t last_time_;
private slots:
    void onMessageLogged( QOpenGLDebugMessage message );

};

#endif // WINDOW_H
