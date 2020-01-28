#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <QtWidgets>

class PluginItem : public QGraphicsItem
{
public:
    PluginItem();

    QRectF boundingRect() const
    {
        qreal penWidth = 1;
        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2, 20 + penWidth, 20 + penWidth);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        painter->drawRoundedRect(-100, -100, 200, 200, 5, 5);
        (void)option;
        (void)widget;
    }
};

#endif // PLUGINITEM_H
