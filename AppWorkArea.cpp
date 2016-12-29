#include "AppWorkArea.h"
#include <QDebug>
#include <QtCore>


#include "graphicslist.h"
extern GraphicsList *graphicPath;

AppWorkArea::AppWorkArea()
{
    rect = QRectF(100, 200, 300, 400);
    rotation = 0;
    setAcceptedMouseButtons(Qt::AllButtons);
    this->pan = QPointF(this->width() / 2, this->height() / 2);
}

void AppWorkArea::paint(QPainter *painter)
{
    QPen pen(Qt::DashLine);
    pen.setColor(Qt::darkGray);
    painter->setPen(pen);

    graphicPath->DrawCache(painter,graphicPath->zoomScale , this->pan);

    if (this->rotation != 0)
    {
        QPointF offset_rotate = rect.center();
        QTransform rotateTransform;
        rotateTransform.translate(offset_rotate.x(), offset_rotate.y());
        rotateTransform.rotate(this->rotation);
        rotateTransform.translate(-offset_rotate.x(), -offset_rotate.y());
        painter->setTransform(rotateTransform);
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
bool AppWorkArea::event(QEvent *event)
{
    qDebug() << this->pan << this->width() << this->height();
    //detect one finger or two fingers
#if __APPLE__ && !defined(Q_OS_IOS)//macbook pro

    if(event->type() == QEvent::Wheel)
    {//move
        QWheelEvent* ss = static_cast<QWheelEvent*>(event);
        QPoint pt_shifft = ss->pixelDelta();

        this->pan.setX(this->pan.x() + pt_shifft.x());
        this->pan.setY(this->pan.y() + pt_shifft.y());

        this->update();

    }


    if(event->type() == QEvent::NativeGesture)
    {//zoom in and zoom out
        QNativeGestureEvent* ss = static_cast<QNativeGestureEvent*>(event);
        //            qDebug() << "ZOOM SCALE = " << ss->value() << "; MOUSE LOCATION:" << ss->localPos();
        qDebug() << ss;
        if(ss->gestureType() == Qt::ZoomNativeGesture)
        {
            graphicPath->zoomScale *= (1 + ss->value());//((AppGraphicsList*)graphicPath)->zoomScale *= (1 + ss->value());

            this->update();
        }



        if(ss->gestureType() == Qt::EndNativeGesture)
        {
            graphicPath->delete_image_cache();//((AppGraphicsList*)graphicPath)->delete_image_cache();

        }

        //            ((AppGraphicsList*)graphicPath)->onSetFitScale(((AppGraphicsList*)graphicPath)->zoomScale);

        if(ss->gestureType() == Qt::EndNativeGesture)
        {
            this->update();//                graphicPath->RefreshWA();
        }
    }
    return  QQuickPaintedItem::event(event);
#endif
    static bool b_set_zoom_scale;
    if(event->type() == QEvent::TouchBegin
            || event->type() == QEvent::TouchUpdate
            || event->type() == QEvent::TouchEnd )
    {
        bool_use_antialiasing = false;
        qDebug() << event->type();
        if(event->type() == QEvent::TouchBegin)
        {
            bOneFingerEnable = true;
            b_set_zoom_scale = true;
        }
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        for (int idxTouch = 0 ; idxTouch < touchEvent->touchPoints().count(); ++idxTouch)
        {
            qDebug() << touchEvent->touchPoints()[idxTouch].startPos()
                     << touchEvent->touchPoints()[idxTouch].lastPos();
        }
        if (touchEvent->touchPoints().count() > 1)
        {//multi-touch
            bOneFingerEnable = false;
            const QTouchEvent::TouchPoint &touchPoint0 = touchEvent->touchPoints().first();
            const QTouchEvent::TouchPoint &touchPoint1 = touchEvent->touchPoints().last();//   touchPoints.last();

            static float tmp_zoom_scale = graphicPath->zoomScale;
            if(touchEvent->touchPoints().count() == 2)
            {
                //zoom in/out
                if(b_set_zoom_scale)
                {
                    tmp_zoom_scale = graphicPath->zoomScale;
                    b_set_zoom_scale = false;
                }

                double start_Length = sqrt(pow(touchPoint0.startPos().x() - touchPoint1.startPos().x(), 2) + pow(touchPoint0.startPos().y() - touchPoint1.startPos().y(), 2));
                double last_Length = sqrt(pow(touchPoint0.lastPos().x() - touchPoint1.lastPos().x(), 2) + pow(touchPoint0.lastPos().y() - touchPoint1.lastPos().y(), 2));

                graphicPath->zoomScale = tmp_zoom_scale * (last_Length / start_Length);

                //move
                if(bool_move_state)
                {
                    pt_end_move = (touchPoint0.lastPos() + touchPoint1.lastPos()) / 2;
                    QPointF pt_shifft = pt_end_move - pt_start_move;

                    this->pan.setX(this->pan.x() + pt_shifft.x());
                    this->pan.setY(this->pan.y() + pt_shifft.y());

                    pt_start_move = pt_end_move;
                }
                else
                {
                    pt_start_move = (touchPoint0.lastPos() + touchPoint1.lastPos()) / 2;
                    bool_move_state = true;
                }
                this->update();

            }
            else
            {
                b_set_zoom_scale = true;
            }
        }
        else if(touchEvent->touchPoints().count() == 1 && bOneFingerEnable)
        {//one finger
            bool_move_state = false;
            b_set_zoom_scale = true;
            if(event->type() == QEvent::TouchBegin)
            {
                QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonPress,
                                                 touchEvent->touchPoints()[0].pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                mousePressEvent(e); //==> meilleure methode
            }
            else if(event->type() == QEvent::TouchUpdate)
            {
                QMouseEvent *e = new QMouseEvent(QEvent::MouseMove,
                                                 touchEvent->touchPoints()[0].pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                mouseMoveEvent(e);
            }
            else if( event->type() == QEvent::TouchEnd)
            {
                QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonRelease,
                                                 touchEvent->touchPoints()[0].pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                mouseReleaseEvent(e);
            }
        }
        else
        {
            bool_move_state = false;

            b_set_zoom_scale = true;
        }
    }

    if(event->type() == QEvent::TouchEnd )
    {
        bool_use_antialiasing = true;
        bool_move_state = false;

        b_set_zoom_scale = true;
        graphicPath->delete_image_cache();
        this->update();

    }


    return true;
}
