#include "pluginitem.h"

PluginItem::PluginItem(QString pluginName)
{
    // save all the data
    mPluginName = pluginName;

    // setup the behavior of the item
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);

    // working with GStreamer data
    // 1. Get the factory
    GstElementFactory *factory = gst_element_factory_find(qPrintable(mPluginName));

    // !! Check that factory is not NULL

    GList *list = (GList*)gst_element_factory_get_static_pad_templates(factory);
    guint length = g_list_length(list);
    qDebug() << "List length is" << length;
    GList *l;
    for (l = list; l != nullptr; l = l->next)
    {
        GstStaticPadTemplate *templ = (GstStaticPadTemplate*)(l->data);
        if (templ->direction == GST_PAD_SINK && templ->presence == GST_PAD_ALWAYS)
        {
            mAlwaysSinksNum++;
        }
        if (templ->direction == GST_PAD_SRC && templ->presence == GST_PAD_ALWAYS)
        {
            mAlwaysSourcesNum++;
        }
    }
    qDebug() << "Always sinks number is" << mAlwaysSinksNum;
    qDebug() << "Always sources number is" << mAlwaysSourcesNum;
}

void PluginItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    // first we draw the plugin rectangle
    int32_t max = mAlwaysSinksNum > mAlwaysSourcesNum ? mAlwaysSinksNum : mAlwaysSourcesNum;
    mHeight = (max + 1) * mStep;
    QColor fillColor("gray");
    painter->fillRect(QRectF(0, 0, mWidth, mHeight), fillColor);
    // sign it
    painter->drawText(0, mHeight + 10, mPluginName);

    // now draw pins
    int32_t i = 0;
    for (i = 0; i < mAlwaysSinksNum; i++)
    {
        painter->drawLine(-mStep, (i + 1) * mStep, 0, (i + 1) * mStep);
    }
    for (i = 0; i < mAlwaysSourcesNum; i++)
    {
        painter->drawLine(mWidth, (i + 1) * mStep, mWidth + mStep, (i + 1) * mStep);
    }
}

QRectF PluginItem::boundingRect() const
{
    int32_t width = mWidth +
            (mAlwaysSinksNum ? mStep : 0) +
            (mAlwaysSourcesNum ? mStep : 0);

    return QRectF(mAlwaysSinksNum ? -mStep : 0, 0, width, mHeight + 15);
}

void PluginItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    qDebug() << "Hover entered";
    QGraphicsItem::hoverEnterEvent(event);
}
