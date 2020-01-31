#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <QtWidgets>

class PluginItem : public QGraphicsItem
{
public:
    PluginItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // PLUGINITEM_H
