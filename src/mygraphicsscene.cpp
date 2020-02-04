#include "mygraphicsscene.h"

MyGraphicsScene::MyGraphicsScene()
{

}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "Got mouse press event";
    qDebug() << "Screen coordinates X =" << mouseEvent->screenPos().x() << "Y =" << mouseEvent->screenPos().y();
    qDebug() << "Scene  coordinates X =" << mouseEvent->scenePos().x() << "Y =" << mouseEvent->scenePos().y();

    QGraphicsScene::mousePressEvent(mouseEvent);
}
