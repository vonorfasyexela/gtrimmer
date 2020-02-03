#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <QtWidgets>
#include <gst/gst.h>

class PluginItem : public QGraphicsItem
{
public:
    PluginItem(QString pluginName);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    QString mPluginName;
    uint32_t mAlwaysSinksNum = 0;
    uint32_t mAlwaysSourcesNum = 0;
    const int mStep = 20;
    const int mWidth = 5 * mStep;
    int mHeight = 0;
};

#endif // PLUGINITEM_H
