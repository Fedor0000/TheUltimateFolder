#ifndef CELLITEM_H
#define CELLITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class CellItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit CellItem(QObject *parent = 0);
    ~CellItem();
    bool number;
    bool isSelected;
    int scale;
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // рисование вершины
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
signals:
    void activeChanged(); // сигнал о смене координат вершины
};

#endif // CELLITEM_H
