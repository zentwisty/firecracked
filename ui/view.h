#ifndef VIEW_H
#define VIEW_H

#include "GL/glew.h"
#include <qgl.h>
#include <QElapsedTimer>
#include <QTimer>

class View : public QGLWidget {
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();


    float size();
    void setSize(float value);

private:
    QElapsedTimer m_time;
    QTimer m_timer;
    bool m_captureMouse;

    float m_size;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void tick();
};

#endif // VIEW_H
