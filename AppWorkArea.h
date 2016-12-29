#ifndef APPWORKAREA_H
#define APPWORKAREA_H

#include <QQuickPaintedItem>
#include <QPainter>

class AppWorkArea : public QQuickPaintedItem
{
    Q_OBJECT
public:
    AppWorkArea();
    void paint(QPainter *painter);
    QRectF rect;
    int rotation;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    bool event(QEvent* event);
private:
    bool bool_move_state = false;
    QPointF pt_start_move;
    QPointF pt_end_move;
    QPointF pan;
    bool bOneFingerEnable;

    bool bool_use_antialiasing = false;
};

#endif // APPWORKAREA_H
