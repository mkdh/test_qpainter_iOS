#ifndef GRAPHICSLIST_H
#define GRAPHICSLIST_H

#include <QPainter>
#include <QtMath>
//the object
class GraphicShape
{
public:
    GraphicShape(int shift_x, int shift_y){
        float rect_edge = 300;
        QPoint pt_start(rect_edge / 2, rect_edge / 2 );
        int number_point = 11680;//
        float idx_radius;
        for(int i = 0; i< number_point ; i++)
        {
            idx_radius = (float)i * (rect_edge / 2) / (float)number_point;
            embPointList.push_back( pt_start + QPoint(idx_radius * qCos(i % 360),  idx_radius *qSin(i % 360)));
        }

        this->shift_x = shift_x;
        this->shift_y = shift_y;

        this->sizeRectangle = QRectF(0, 0, rect_edge, rect_edge);
    }

    QImage* img_cache_p = 0;
    QRectF sizeRectangle;
    int shift_x, shift_y;
    float rotation;
    QList<QPoint> embPointList;
    float zoom_scale_cache = 1;

    void build_image_cache(float ZoomFactor){
        if(img_cache_p)
        {
            delete img_cache_p;
            img_cache_p = 0;
        }
        img_cache_p = new QImage(this->sizeRectangle.width() * ZoomFactor, this->sizeRectangle.height()  * ZoomFactor, QImage::Format_ARGB32);

        img_cache_p->fill(qRgba(0, 255, 0, 100));//  //Qt::green

        QPainter paint_img(img_cache_p);
        QPointF panCache(0,0);//QPointF panCache(ZoomFactor * (this->scale_ *this->sizeRectangle.width() / 2 - center.x()), ZoomFactor *(this->scale_ *this->sizeRectangle.height() / 2 - center.y()));

        this->Draw(&paint_img, ZoomFactor, panCache, true);
        paint_img.end();
    }

    void Draw(QPainter *g, float ZoomFactor, QPointF Pan, bool b_rotated)
    {
        QPointF P1(0, 0);
        QPointF P2(0, 0);

        QPen pen(Qt::red);
        pen.setWidth(10);

        for (int i = 0; i < this->embPointList.count(); i++)
        {
            QPoint Pt = this->embPointList[i];//CPointF Pt = this->Transform(this->embPointList[i], b_rotated);

            Pt.setX(Pt.x() * ZoomFactor + Pan.x());
            Pt.setY(Pt.y() * ZoomFactor + Pan.y());

            if (i == 0)
                P1 = Pt;
            else
            {
                P2 = Pt;

                if (this->embPointList.count() > i)
                {
                    g->drawLine(P1.x(), P1.y(), P2.x(), P2.y());

                    P1 = P2;
                }
            }
        }
    }

    void DrawCache(QPainter *g, float ZoomFactor, QPointF Pan)
    {
        if(this->img_cache_p == 0){
            build_image_cache(ZoomFactor);
            this->zoom_scale_cache = ZoomFactor;
        }
        if(this->img_cache_p)
        {
            QRect rectCache = this->img_cache_p->rect();

            QImage img_tmp_cache = this->img_cache_p
                    ->scaled(rectCache.width() * ZoomFactor  / this->zoom_scale_cache
                             , rectCache.height() * ZoomFactor  / this->zoom_scale_cache
                             , Qt::KeepAspectRatio);

            g->drawImage(Pan + QPointF(this->shift_x, this->shift_y), img_tmp_cache);
        }
    }
};

//the object list
class GraphicsList
{
public:
    GraphicsList();
    void DrawCache(QPainter *g, float ZoomFactor, QPointF Pan);
    QList<GraphicShape*> shapeList;
    float zoomScale = 1;
    void delete_image_cache();

};


#endif // GRAPHICSLIST_H
