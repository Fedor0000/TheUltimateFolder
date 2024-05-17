#ifndef GRAPHMAN_H
#define GRAPHMAN_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include "moveitem.h"
#include "ArrowItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GraphMan; }
QT_END_NAMESPACE

class Graph // класс графа
{
public:
    std::vector<std::vector<long long int>> tableOfgraph; // таблица смежности
    std::vector<MoveItem*> tableOfvertex; // вектор с указателями на графический объект - вершину
    std::vector<std::vector<ArrowItem*>> tableOfarrows; // таблица с указателями на стрелки (ребра графа)
    Graph(); // конструктор
    void setEdge(long long int, long long int, long long int, long long int); //метод установки/смены ребра сразу в две стороны
    void setEdge(long long int, long long int, long long int); // метод установки/смены ребра в одну сторону
    void delEdge(long long int, long long int); //метод удаления ребра в одну сторону
    void addVertex(); // метод добавления вершины
    void delVertex(long long int);
};

class GraphMan : public QMainWindow
{
    Q_OBJECT

public:
    GraphMan(QWidget *parent = nullptr);
    ~GraphMan();
    QGraphicsView *graphicsView; // телевизор
    QGraphicsScene *scene; // сцена для отображения графа
    QGraphicsScene *sceneForMatrix; //сцена для отображения таблицы смежности
    Graph gr; // граф

    void ultimateTVupdater(); // обновитель телевизора
    void addSizeOfArrowsMas(); // увеличить размер таблицы со стрелками
    void popSizeOfArrowMas(long long int); // убрать из таблицы со стрелками строку и столбец по индексу

public slots:
    void newVertexBTNclicked(); // добавление вершины
    void delVertexBTNclicked(); // удаление вершины
    void addEdgeBTNclicked(); // добавление/изменение ребра
    void delEdgeBTNclicked(); // удаление ребра
    void updateCoords(); // обновление координат стрелок
    void printMatrix(); // вывод таблицы смежности вместо графа
    void closeMatrix(); // выход из режима таблицы смежности в режим графа
    void BFS_BTNclicked(); // вывод результатов обхода в ширину
    void DFS_BTNclicked(); // вывод результатов обхода в глубину
    void deicstraBTNclicked(); // вывод кратчайшего пути от одной вершины до другой
    void kommiBTNclicked(); // решение и вывод ответа на задачу Коммивояжёра
private:
    Ui::GraphMan *ui;
};
#endif // GRAPHMAN_H
