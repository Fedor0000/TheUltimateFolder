#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class MoveItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MoveItem(QObject *parent = 0);
    ~MoveItem();
    long long int nomer;
signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // рисование вершины
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event); // событие передвижения вершины
    void mousePressEvent(QGraphicsSceneMouseEvent *event); // событие нажатия мыши (смена курсора на руку)
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); // событие отпускания мыши (смена курсора на стандартный)

public slots:
signals:
    void coordinatesChanged(); // сигнал о смене координат вершины
};

#endif // MOVEITEM_H
