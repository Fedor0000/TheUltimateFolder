#include "ArrowItem.h"
#include <cmath>

ArrowItem::ArrowItem(QObject *parent) :
    QObject(parent), QGraphicsItem() {}

ArrowItem::~ArrowItem() {}

QRectF ArrowItem::boundingRect() const // прямоугольник ограничение стрелки - нужен для правильного расширения и сужения сцены
{
    return QRectF(start.x(),start.y(), (start.x()<end.x() ? abs(end.x()-start.x()) : -abs(end.x()-start.x())), (start.y()<end.y() ? -abs(end.y()-end.y()) : abs(end.y()-end.y())));
}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal arrowSize = 10; // размер башки стрелочки
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->setFont(QFont("Montserrat Alternates", 15));
    QLineF line(end, start);
    double angle = std::atan2(-line.dy(), line.dx()); // угол между стрелкой и ОХ

    // отодвигаем конец и начало стрелки от центра круга с радиусом 20
    line.setP2(QPointF(start.x()-20*cos(angle), start.y()+20*sin(angle)));
    line.setP1(QPointF(end.x()+20*cos(angle), end.y()-20*sin(angle)));

    // точки для рисования башки стрелки
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);
    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    painter->drawLine(line); // бошка стрелки
    if(start != end) painter->drawPolygon(arrowHead); // обраотка петель - стрелка на петли не рисуется
    painter->setPen(Qt::blue);
    if(start != end) painter->drawText(QPointF(end.x()+50*cos(angle), end.y()-50*sin(angle)), QString::number(weight)); // текст отодвинут
    else painter->drawText(QPointF(end.x(), end.y()-30), QString::number(weight)); // вес ребра
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
