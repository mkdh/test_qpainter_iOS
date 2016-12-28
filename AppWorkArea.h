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
};

#endif // APPWORKAREA_H
