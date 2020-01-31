#include "pluginitem.h"

PluginItem::PluginItem()
{
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

void PluginItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QColor fillColor("gray");
    painter->fillRect(QRectF(0, 0, 110, 70), fillColor);
}

QRectF PluginItem::boundingRect() const
{
    return QRectF(0, 0, 110, 70);
}
