#include "CellItem.h"

CellItem::CellItem(QObject *parent) :
    QObject(parent), QGraphicsItem() {}

CellItem::~CellItem() {}

QRectF CellItem::boundingRect() const
{
    return QRectF(-(scale/2),-(scale/2),scale,scale);
}

void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (isSelected) painter->setBrush(QColor(235, 169, 255));
    else if (number) painter->setBrush(QColor(171, 255, 174));
    else painter->setBrush(QColor(255, 207, 168));
    painter->drawPolygon(QRectF(-(scale/2),-(scale/2),scale,scale));
    painter->setPen(Qt::black);
    painter->setFont(QFont("Montserrat Alternates", scale/1.3));
    QString text(QString::number(static_cast<int>(number))); if (text == "1") text = " 1";
    painter->drawText(-scale/2.7, scale/2.7, text);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isSelected) isSelected = false;
    else
    {
        isSelected = true;
    }
    emit activeChanged();
    Q_UNUSED(event);
}
