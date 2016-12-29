#include "graphicslist.h"

GraphicsList::GraphicsList()
{
    GraphicShape* obj1 = new GraphicShape(10, 10);
    shapeList.push_back(obj1);

    //    GraphicShape* obj2 = new GraphicShape(300, 10);
    //    shapeList.push_back(obj2);

    //    GraphicShape* obj3 = new GraphicShape(10, 300);
    //    shapeList.push_back(obj3);

}

void GraphicsList::DrawCache(QPainter *g, float ZoomFactor, QPointF Pan)
{

    for(int i = 0; i< this->shapeList.count(); i++)
    {
        this->shapeList[i]->DrawCache(g, ZoomFactor, Pan);
    }

}
void GraphicsList::delete_image_cache()
{
    for(int i = 0 ; i < this->shapeList.count() ; i++){
        delete this->shapeList[i]->img_cache_p;
        this->shapeList[i]->img_cache_p = 0;
    }
}
