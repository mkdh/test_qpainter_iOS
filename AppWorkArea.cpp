#include "AppWorkArea.h"
#include <QDebug>
AppWorkArea::AppWorkArea()
{
    rect = QRectF(100, 200, 300, 400);
    rotation = 0;
    setAcceptedMouseButtons(Qt::AllButtons);

}
void AppWorkArea::paint(QPainter *painter)
{
    QPen pen(Qt::DashLine);
    pen.setColor(Qt::darkGray);
    painter->setPen(pen);
    if (this->rotation != 0)
    {
        QPointF offset_rotate = rect.center();
        QTransform rotateTransform;
        rotateTransform.translate(offset_rotate.x(), offset_rotate.y());
        rotateTransform.rotate(this->rotation);
        rotateTransform.translate(-offset_rotate.x(), -offset_rotate.y());
        painter->setTransform(rotateTransform);
      }
    else
    {

    }
    painter->drawRect(rect);
}
void AppWorkArea::mousePressEvent(QMouseEvent *e)
{
    rotation = 45;
    qDebug() << rotation;
    this->update();
    return;
}
void AppWorkArea::mouseMoveEvent(QMouseEvent *e)
{
    rotation = ++rotation % 360;
    qDebug() << rotation;
    this->update();

    return;
}
void AppWorkArea::mouseReleaseEvent(QMouseEvent *e)
{
    rotation = 0;
    qDebug() << rotation;
    this->update();

    return;
}
