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

private:
    QElapsedTimer m_time;
    QTimer m_timer;
    bool m_captureMouse;

    int m_size;
    int m_weight;
    int m_red;
    int m_green;
    int m_blue;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);

//    void keyPressEvent(QKeyEvent *event);
//    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void setSize(int size);
    void setWeight(int weight);
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);

    void onLaunch();
    void tick();
};

#endif // VIEW_H
