#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <QtWidgets>

class PluginItem : public QGraphicsItem
{
public:
    PluginItem(QString pluginName);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    QString mPluginName;
};

#endif // PLUGINITEM_H
