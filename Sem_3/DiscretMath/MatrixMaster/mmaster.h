#ifndef MMASTER_H
#define MMASTER_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "matrixxx.h"
#include "CellItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MMaster; }
QT_END_NAMESPACE

class MMaster : public QMainWindow
{
    Q_OBJECT

public:
    MMaster(QWidget *parent = nullptr);
    ~MMaster();
    QGraphicsView *graphicsView; // телевизор
    QGraphicsScene *scene; // сцена для отображения
    QGraphicsScene *sceneForText;
    Matrixxx matr;
    std::vector<std::vector<CellItem*>> indexation;
    void text(QString text, QFont font);
public slots:
    void printMatrix();
    void scaleChanged();
    void selectedCell();
    void getMatrixFromFile();
    void createMatrix();
    void nullBTN();
    void oneBTN();
    void randBTN();
    void toFile();
    void appendMatr();
    void disappendMatr();
    void delMatr();
    void analyzeMatr();
private:
    Ui::MMaster *ui;
};
#endif // MMASTER_H
