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
    int32_t mAlwaysSinksNum = 0;
    int32_t mAlwaysSourcesNum = 0;
    const int32_t mStep = 20;
    const int32_t mWidth = 5 * mStep;
    int32_t mHeight = 0;
};

#endif // PLUGINITEM_H
