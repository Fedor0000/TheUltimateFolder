#ifndef ARROWITEM_H
#define ARROWITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class ArrowItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ArrowItem(QObject *parent = 0);
    ~ArrowItem();
    long long int weight; // вес ребра
    QPointF start; // координаты старта ребра
    QPointF end; // координаты конца ребра
signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // рисование ребра

public slots:
};

#endif // ARROWITEM_H
