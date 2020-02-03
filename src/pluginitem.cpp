#include "pluginitem.h"

PluginItem::PluginItem(QString pluginName)
{
    mPluginName = pluginName;
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

void PluginItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QColor fillColor("gray");
    painter->fillRect(QRectF(0, 0, 110, 70), fillColor);
    painter->drawText(0, 80, mPluginName);
}

QRectF PluginItem::boundingRect() const
{
    return QRectF(0, 0, 110, 85);
}
