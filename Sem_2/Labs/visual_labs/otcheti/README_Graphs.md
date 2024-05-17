# Лабораторная работа "Бинарные деревья"

## Постановка задачи

```txt
Реализовать алгоритмы для собственного, придуманного самим автором, варианта двунаправленного графа, имеющего не менее 6 вершин.
 
Алгоритмы:
1. Обход в ширину.
2. Обход в глубину.
3. Алгоритм Дейкстры.
4. Выполнить задание своего варианта из методички:
Laby_Chast_3.docx (лаб работа по графам)

Требования:

1. Пользовательский интерфейс на усмотрение разработчика с условием кроссплатформенности (поощряется использование Qt или иных фреймворков)

2. Визуализация графа с использованием любой доступной графической библиотеки (SFML, SDL, OpenGL и подобных)

3. Реализованные алгоритмы должны справляться как с графом, представленным в задании варианта, так и с другими на усмотрение проверяющего.

4. Необходимо реализовать функции для редактирования графа: 
- Создание новой вершины.
- Удаление вершины.
- Добавление и удаление ребра. 
- Редактирование весов ребер. 
- Редактирование матрицы смежности (или инцидентности в зависимости от реализации).
- Реализовать вывод графа. 
```

### 7 Вариант:

![graph](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/visual_labs/otcheti/graphTask.jpg)

## UML-диаграмма

![uml](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/visual_labs/otcheti/graphUML.jpg)

## Код программы

`ArrowItem.h`
```cpp
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
```

`ArrowItem.cpp`
```cpp
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
```

`moveitem.h`
```cpp
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
```

`moveitem.cpp`
```cpp
#include "moveitem.h"

MoveItem::MoveItem(QObject *parent) :
    QObject(parent), QGraphicsItem() {}

MoveItem::~MoveItem() {}

QRectF MoveItem::boundingRect() const
{
    return QRectF (-20,-20,40,40);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->setFont(QFont("Montserrat Alternates"));
    painter->drawEllipse(-20,-20,40,40);
    QString text(QString::number(nomer)); painter->drawText(-5, 5, text);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    emit coordinatesChanged();
    this->setPos(mapToScene(event->pos()));
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));\
    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
```

`graphman.h`
```cpp
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
private:
    Ui::GraphMan *ui;
};
#endif // GRAPHMAN_H
```

`graphman.cpp`
```cpp
#include "graphman.h"
#include "ui_graphman.h"
#include "moveitem.h"
#include "ArrowItem.h"
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRegExpValidator>
#include <vector>
#include <queue>

static int randomBetween(int low, int high) // рандом между двумя числами
{
    return ((rand()+rand()) % ((high + 1) - low) + low);
}

Graph::Graph() // конструктор графа
{
    std::vector<long long int> tmp(1, 0);
    tableOfgraph.push_back(tmp);
    tableOfvertex.push_back(nullptr);
    std::vector<ArrowItem*> tmp2(1, nullptr);
    tableOfarrows.push_back(tmp2);
}

void Graph::setEdge(long long int vertexStart, long long int vertexFinish, long long int directWeight, long long int reverseWeight) // установка ребра от и до прямой вес и обратный
{
    if (vertexStart == 0 || vertexFinish == 0) return;
    if (vertexFinish > static_cast<long long int>(tableOfgraph.size()) || vertexStart > static_cast<long long int>(tableOfgraph.size())) return;
    tableOfgraph[vertexStart][vertexFinish] = directWeight;
    tableOfgraph[vertexFinish][vertexStart] = reverseWeight;
}

void Graph::setEdge(long long int vertexStart, long long int vertexFinish, long long int directWeight) // установка ребра от и до
{
    if (vertexStart == 0 || vertexFinish == 0) return;
    if (vertexFinish > static_cast<long long int>(tableOfgraph.size()) || vertexStart > static_cast<long long int>(tableOfgraph.size())) return;
    tableOfgraph[vertexStart][vertexFinish] = directWeight;
}

void Graph::delEdge(long long int vertexStart, long long int vertexFinish) // удаление ребра от и до
{
    if (vertexStart == 0 || vertexFinish == 0) return;
    if (vertexFinish > static_cast<long long int>(tableOfgraph.size()) || vertexStart > static_cast<long long int>(tableOfgraph.size())) return;
    setEdge(vertexStart, vertexFinish, -1);
}

void Graph::addVertex() // добавление вершины
{
    std::vector<long long int> tmp(tableOfgraph.size(), -1);
    tmp[0] = tableOfgraph.size();
    tableOfgraph.push_back(tmp);
    for(unsigned long long int i = 0; i < tableOfgraph.size(); i++) // правильно увеличиваем таблицу смежности
    {
        if(i==0) tableOfgraph[i].push_back(tableOfgraph.size()-1);
        else tableOfgraph[i].push_back(-1);
    }
}

void Graph::delVertex(long long int vertexNumber) // удаляем вершину
{
    if (tableOfgraph.size() < 2) return; // если нечего удалять
    tableOfgraph.erase(std::next(tableOfgraph.begin(), vertexNumber)); // убираем строку вершины из таблицы смежности
    for(unsigned long long int i = 0; i < tableOfgraph.size(); i++) tableOfgraph[i].erase(std::next(tableOfgraph[i].begin(), vertexNumber)); // убираем столб вершины из таблицы смежности
    for(unsigned long long int i = vertexNumber; i < tableOfgraph.size(); i++) tableOfgraph[i][0] = i; // перенумеровываем вершины в таблице смежности и в векторе вершин
    for(unsigned long long int i = vertexNumber; i < tableOfgraph[0].size(); i++) tableOfgraph[0][i] = i;
    for(unsigned long long int i = vertexNumber; i < tableOfvertex.size(); i++) tableOfvertex[i]->nomer=i;
}

GraphMan::GraphMan(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphMan)
{
    ui->setupUi(this);

    // коннекты кнопок
    connect(ui->addVertexBTN, &QPushButton::clicked, this, &GraphMan::newVertexBTNclicked);
    connect(ui->delVertexBTN, &QPushButton::clicked, this, &GraphMan::delVertexBTNclicked);
    connect(ui->addEdgeBTN, &QPushButton::clicked, this, &GraphMan::addEdgeBTNclicked);
    connect(ui->delEdgeBTN, &QPushButton::clicked, this, &GraphMan::delEdgeBTNclicked);
    connect(ui->updateTVBTN, &QPushButton::clicked, this, &GraphMan::updateCoords);
    connect(ui->tableBTN, &QPushButton::clicked, this, &GraphMan::printMatrix);
    connect(ui->graphBTN, &QPushButton::clicked, this, &GraphMan::closeMatrix);
    connect(ui->BFS_BTN, &QPushButton::clicked, this, &GraphMan::BFS_BTNclicked);
    connect(ui->DFS_BTN, &QPushButton::clicked, this, &GraphMan::DFS_BTNclicked);
    connect(ui->deicstraBTN, &QPushButton::clicked, this, &GraphMan::deicstraBTNclicked);

    graphicsView = ui->graphTV; //коннекты телевизора и сцены
    scene = new QGraphicsScene;
    sceneForMatrix = new QGraphicsScene;
    graphicsView -> setScene(scene);
    ui->graphTV->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphTV->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphTV->setViewportUpdateMode(QGraphicsView::FullViewportUpdate); // режим обнавления телека - полный

    QRegExp re("^[0-9]*[1-9][0-9]*$"); // целые положительные числа
    QRegExpValidator*v = new QRegExpValidator(re);

    // устанавливаем ограничения и текст-подсказку на все поля ввода
    ui->addEdgeStart->setPlaceholderText("Начало");
    ui->addEdgeStart->setValidator(v);
    ui->addEdgeFinish->setPlaceholderText("Конец");
    ui->addEdgeFinish->setValidator(v);
    ui->addEdgeWeight->setPlaceholderText("Прям. вес");
    ui->addEdgeWeight->setValidator(v);
    ui->addEdgeReverseWeight->setPlaceholderText("Обрат. вес");
    ui->addEdgeReverseWeight->setValidator(v);
    ui->delEdgeStart->setPlaceholderText("Начало");
    ui->delEdgeStart->setValidator(v);
    ui->delEdgeFinish->setPlaceholderText("Конец");
    ui->delEdgeFinish->setValidator(v);
    ui->delVertexInput->setPlaceholderText("Вершина №");
    ui->delVertexInput->setValidator(v);
    ui->BFS_start->setPlaceholderText("Вершина начала");
    ui->BFS_start->setValidator(v);
    ui->DFS_start->setPlaceholderText("Вершина начала");
    ui->DFS_start->setValidator(v);
    ui->deicstraStart->setPlaceholderText("Вершина начала");
    ui->deicstraStart->setValidator(v);
    ui->deicstraFinish->setPlaceholderText("Вершина конца");
    ui->deicstraFinish->setValidator(v);

    ui->graphBTN->setHidden(true);

    srand(time(NULL)); // обновление сида рандомного генератора
}

void GraphMan::ultimateTVupdater() // хороший такой обновитель дисплея
{
    if (ui->graphTV->scene() == sceneForMatrix) printMatrix(); // если на экране таблица, то выводим ее
    else
    {
        QRectF rect = scene->itemsBoundingRect(); // иначе увеличиваем/уменьшаем сцену, чтобы увидеть вершины за экраном и обновляем дисплей
        rect.setHeight(rect.height()+1); // чинит некоторые визуальные баги, но, к сожалению не все
        scene->setSceneRect(rect);
        ui->graphTV->update();
    }
    ui->output->setText("");
}

void GraphMan::newVertexBTNclicked() // создание новой вершины - модифицирует все таблицы и векторы, какие нужно
{
    MoveItem *item = new MoveItem();        // Создаём графический элемент
    item->nomer = gr.tableOfgraph.size();
    item->setPos(randomBetween(0, 800), randomBetween(0,600));   // Устанавливаем случайную позицию элемента
    scene->addItem(item);   // Добавляем элемент на графическую сцену
    gr.tableOfvertex.push_back(item);
    gr.addVertex();
    addSizeOfArrowsMas();
    ultimateTVupdater();
    connect(item, &MoveItem::coordinatesChanged, this, &GraphMan::updateCoords); // для обновления стрелок, каждый круг испускает сигнал при движении, на который реагируем обновлением координат стрелок
}

void GraphMan::delVertexBTNclicked() // слот, выполняющийся при нажатии на кнопку УДАЛИТЬ ВЕРШИНУ
{
    if(gr.tableOfvertex.size() < 2) return; // если вершин нет то выход
    long long int vertexNumber = ui->delVertexInput->text().toLongLong(); // получаем номер вершины, которую нужно удалить
    if (vertexNumber > static_cast<int64_t>(gr.tableOfvertex.size())-1 || vertexNumber < 1) return; //если номер неадекватен, то выходим
    scene->removeItem(gr.tableOfvertex[vertexNumber]); // убираем вершину со сцены
    gr.tableOfvertex.erase(std::next(gr.tableOfvertex.begin(), vertexNumber)); // убираем вершину из вектора
    gr.delVertex(vertexNumber); // убираем из таблицы смежности и вектора вершин, перенумеровываем
    popSizeOfArrowMas(vertexNumber); // убираем лишние стрелки
    ui->delVertexInput->setText(""); // чистим поле ввода
    ultimateTVupdater(); // обновляем дисплей
}

void GraphMan::addEdgeBTNclicked() // добавление/изменение ребра, разное в зависимости от того, какие веса введены, а какие нет
{
    long long int start = ui->addEdgeStart->text().toLongLong(), finish = ui->addEdgeFinish->text().toLongLong();
    if ((start > static_cast<int64_t>(gr.tableOfgraph.size())-1)||(finish > static_cast<int64_t>(gr.tableOfgraph.size())-1)||(finish < 1)||(start < 1)) return;
    if ((ui->addEdgeWeight->text() == "") && (ui->addEdgeReverseWeight->text() == "")) return;
    if ((ui->addEdgeWeight->text() != "") && (ui->addEdgeReverseWeight->text() != "")) // если ввели и прямой и обратный вес
    {
        long long int weight = ui->addEdgeWeight->text().toLongLong();
        long long int reverseWeight = ui->addEdgeReverseWeight->text().toLongLong();
        gr.setEdge(start, finish, weight, reverseWeight); // модифицируем таблицу смежности

        if(gr.tableOfarrows[start][finish] == nullptr) //если нет ребра
        {
            ArrowItem* arrow = new ArrowItem();
            arrow->weight = weight;
            arrow->start = gr.tableOfvertex[start]->pos();
            arrow->end = gr.tableOfvertex[finish]->pos();
            scene->addItem(arrow);
            gr.tableOfarrows[start][finish] = arrow;
        }
        else // если есть стрелки
        {
            gr.tableOfarrows[start][finish]->weight = weight;
        }

        // повторяем для обратного веса
        if(gr.tableOfarrows[finish][start] == nullptr)
        {
            ArrowItem* arrow = new ArrowItem();
            arrow->weight = reverseWeight;
            arrow->start = gr.tableOfvertex[finish]->pos();
            arrow->end = gr.tableOfvertex[start]->pos();
            scene->addItem(arrow);
            gr.tableOfarrows[finish][start] = arrow;
        }
        else
        {
            gr.tableOfarrows[finish][start]->weight = reverseWeight;
        }
    }
    else if (ui->addEdgeWeight->text() != "") // если есть прямой вес, то все также, но только с прямым
    {
        long long int weight = ui->addEdgeWeight->text().toLongLong();
        gr.setEdge(start, finish, weight);
        if(gr.tableOfarrows[start][finish] == nullptr)
        {
            ArrowItem* arrow = new ArrowItem();
            arrow->weight = weight;
            arrow->start = gr.tableOfvertex[start]->pos();
            arrow->end = gr.tableOfvertex[finish]->pos();
            scene->addItem(arrow);
            gr.tableOfarrows[start][finish] = arrow;
        }
        else
        {
            gr.tableOfarrows[start][finish]->weight = weight;
        }

    }
    else if (ui->addEdgeReverseWeight->text() != "") // с только обратным
    {
        long long int reverseWeight = ui->addEdgeReverseWeight->text().toLongLong();
        gr.setEdge(finish, start, reverseWeight);

        if(gr.tableOfarrows[finish][start] == nullptr)
        {
            ArrowItem* arrow = new ArrowItem();
            arrow->weight = reverseWeight;
            arrow->start = gr.tableOfvertex[finish]->pos();
            arrow->end = gr.tableOfvertex[start]->pos();
            scene->addItem(arrow);
            gr.tableOfarrows[finish][start] = arrow;
        }
        else
        {
            gr.tableOfarrows[finish][start]->weight = reverseWeight;
        }
    }
    // чистим поля ввода
    ui->addEdgeStart->setText("");
    ui->addEdgeFinish->setText("");
    ui->addEdgeWeight->setText("");
    ui->addEdgeReverseWeight->setText("");

    ultimateTVupdater();
}

void GraphMan::delEdgeBTNclicked() // удаление ребра
{
    // проверки на дурака
    long long int start = ui->delEdgeStart->text().toLongLong(), finish = ui->delEdgeFinish->text().toLongLong();
    if ((start > static_cast<int64_t>(gr.tableOfgraph.size())-1) || (finish > static_cast<int64_t>(gr.tableOfgraph.size())-1)) return;
    if (start == 0 || finish == 0) return;
    if (gr.tableOfgraph[start][finish] == -1) return;
    gr.delEdge(start, finish); // модифицируем таблицу смежности
    scene->removeItem(gr.tableOfarrows[start][finish]); // убираем стрелку
    gr.tableOfarrows[start][finish] = nullptr;
    ui->delEdgeStart->setText(""); // чистим поля ввода
    ui->delEdgeFinish->setText("");
    ultimateTVupdater();
}

void GraphMan::addSizeOfArrowsMas() // расширение таблицы со стрелками
{
    std::vector<ArrowItem*> tmp(gr.tableOfarrows.size(), nullptr);
    gr.tableOfarrows.push_back(tmp);
    for (uint64_t i = 0; i < gr.tableOfarrows.size(); i++) gr.tableOfarrows[i].push_back(nullptr);
}

void GraphMan::popSizeOfArrowMas(long long int deletedVertex) // вычеркивание строки и столбца по индексу из таблицы со стрелками
{
    for (uint64_t i = 1; i < gr.tableOfarrows[deletedVertex].size(); i++) // идем по строке
    {
        if (gr.tableOfarrows[deletedVertex][i] != nullptr) // удаляем стрелки, если они есть
        {
            scene->removeItem(gr.tableOfarrows[deletedVertex][i]);
            gr.tableOfarrows[deletedVertex][i]=nullptr;
        }
    }
    gr.tableOfarrows.erase(std::next(gr.tableOfarrows.begin(), deletedVertex)); // стираем строку

    for (uint64_t i = 1; i < gr.tableOfarrows.size(); i++) // идем по столбцу
    {
        if (gr.tableOfarrows[i][deletedVertex] != nullptr)
        {
            scene->removeItem(gr.tableOfarrows[i][deletedVertex]); // если есть стрелка, удаляем
        }
        gr.tableOfarrows[i].erase(std::next(gr.tableOfarrows[i].begin(), deletedVertex)); // удаляем элемент из строки
    }
}

void GraphMan::updateCoords() // обновляет координаты стрелок
{
    for (uint64_t i = 1; i < gr.tableOfarrows.size(); i++) // идем по таблице стрелок и меняем координаты начала и конца в соответствии с текущими координатами вершин
    {
        for(uint64_t j = 1; j < gr.tableOfarrows[i].size(); j++)
        {
            if (gr.tableOfarrows[i][j] != nullptr)
            {
                gr.tableOfarrows[i][j]->start = gr.tableOfvertex[i]->pos();
                gr.tableOfarrows[i][j]->end = gr.tableOfvertex[j]->pos();
            }
        }
    }
    ultimateTVupdater();
}

void GraphMan::printMatrix() // печатает таблицу смежности и сменяет сцену на сцену с таблицей
{
    ui->graphBTN->setHidden(false); ui->tableBTN->setHidden(true); // меняем кнопки переключения режимов местами

    QGraphicsScene* del = sceneForMatrix; // чистим сцену
    sceneForMatrix = new QGraphicsScene;
    delete del;

    unsigned long long int x = 0, y = 30;
    for (uint64_t i = 0; i < gr.tableOfgraph.size(); i++) // добавляем объекты на сцену, меняем цвет в соответствии с моим желанием, если таблица смежности и таблица стрелок не совпадают, то красим в красный (помогло при отладке)
    {
        x = 0;
        for(uint64_t j = 0; j < gr.tableOfgraph[i].size(); j++)
        {
            QColor bruh;
            if ((gr.tableOfgraph[i][j] != -1 && gr.tableOfarrows[i][j] != nullptr)&&i!=0&&j!=0) bruh = QColor(27,235,16);
            else if ((gr.tableOfgraph[i][j] == -1 && gr.tableOfarrows[i][j] == nullptr) && i!=0 && j!=0) bruh = QColor(201,250,255);
            else if ((i == 0 || j == 0) && gr.tableOfarrows[i][j] == nullptr) bruh = QColor(233,255,44);
            else bruh = QColor(255,0,0);
            sceneForMatrix->addPolygon(QPolygonF(QRectF(x, y, 100, 30)), QPen(Qt::black), QBrush(bruh));
            QGraphicsTextItem* text = sceneForMatrix->addText(QString::number(gr.tableOfgraph[i][j]), QFont("Montserrat Alternates", 15, 2));
            text->setPos(x+3, y-2);
            x+=100;
        }
        y+=30;
    }

    ui->graphTV->setScene(sceneForMatrix); // меняем сцену и обновляем дисплей
    ui->graphTV->update();
}

void GraphMan::closeMatrix() // выходим из режима матрицы
{
    ui->graphBTN->setHidden(true); ui->tableBTN->setHidden(false);
    ui->graphTV->setScene(scene);
    ultimateTVupdater();
}

QString BFS(const std::vector<std::vector<long long int>>& adjacency_matrix, long long int start) // обход в ширину
{
    std::vector<bool> visited(adjacency_matrix.size(), false);
    std::queue<long long int> queue;
    std::string path = "";

    visited[start] = true;
    queue.push(start);

    while (!queue.empty())
    {
        long long int vertex = queue.front();
        queue.pop();
        // Добавляем вершину к пути
        path += std::to_string(vertex) + "->";
        // Перебираем всех соседей
        for (unsigned long long int i = 1; i < adjacency_matrix[vertex].size(); ++i)
        {
            if ((adjacency_matrix[vertex][i] !=-1 || adjacency_matrix[i][vertex] !=-1) && !visited[i])
            {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
    // Удаляем последнюю стрелку "->" и выводим путь
    if (!path.empty())
    {
        path.pop_back();
        path.pop_back();
    }
    return QString(QString::fromStdString(path));
}

void GraphMan::BFS_BTNclicked() // производит обход в ширину и выводит в поле вывода
{
    int64_t start = ui->BFS_start->text().toLongLong();
    if(start > static_cast<int64_t>(gr.tableOfvertex.size())-1 || start < 1) return;
    ui->BFS_start->setText("");
    ui->output->setText(BFS(gr.tableOfgraph, start));
}

void DFS(const std::vector<std::vector<long long int>>& graph, long long int start, std::vector<bool>& visited, std::string& path) // основная часть функции рекурсивный обход в глубину
{
    visited[start] = true;
    path += std::to_string(start) + "->";
    for (unsigned long long int i = 1; i < graph[start].size(); i++)
    {
        if ((graph[start][i] !=-1 || graph[i][start] !=-1) && !visited[i])
        {
            DFS(graph, i, visited, path);
        }
    }
}

QString graphTraversal(const std::vector<std::vector<long long int>>& adjacencyMatrix, long long int start) // более удобная обертка для обхода в глубину, возвращающая путь
{
    std::vector<bool> visited(adjacencyMatrix.size(), false);
    std::string path;
    DFS(adjacencyMatrix, start, visited, path);
    // Удаляем последнюю стрелку "->" и возвращаем путь
    if (!path.empty())
    {
        path.pop_back();
        path.pop_back();
    }
    return QString(QString::fromStdString(path));
}

void GraphMan::DFS_BTNclicked() // производит обход в глубину и выводит в поле для вывода
{
    int64_t start = ui->DFS_start->text().toLongLong();
    if(start > static_cast<int64_t>(gr.tableOfvertex.size())-1 || start < 1) return;
    ui->DFS_start->setText("");
    ui->output->setText(graphTraversal(gr.tableOfgraph, start));
}

// Функция реализует алгоритм Дейкстры для поиска кратчайшего пути
QString dijkstra(const std::vector<std::vector<long long int>>& graph, long long int start, long long int end)
{
    // Инициализируем вектор расстояний как бесконечности
    std::vector<long long int> dist(graph.size(), INT64_MAX);
    // Вектор для хранения предыдущих вершин в пути
    std::vector<long long int> prev(graph.size(), -1);
    // Очередь с приоритетами для выбора следующей вершины с минимальным расстоянием
    std::priority_queue<std::pair<long long int, long long int>, std::vector<std::pair<long long int, long long int>>, std::greater<std::pair<long long int, long long int>>> pq;
    // Начальная вершина имеет расстояние 0 от себя
    dist[start] = 0;
    pq.push({0, start});
    // Основной цикл алгоритма
    while (!pq.empty())
    {
        // Получаем вершину с минимальным расстоянием
        long long int distance = pq.top().first;
        long long int current = pq.top().second;
        pq.pop();
        // Если текущее расстояние больше уже найденного, пропускаем вершину
        if (distance > dist[current]) continue;
        // Перебираем всех соседей текущей вершины
        for (long long int i = 1; i < static_cast<int64_t>(graph[current].size()); i++)
        {
            long long int nextDistance = graph[current][i];
            // Если сосед существует и обновление расстояния возможно
            if (nextDistance >= 0 && dist[i] > dist[current] + nextDistance)
            {
                // Обновляем расстояние до соседа
                dist[i] = dist[current] + nextDistance;
                // Запоминаем текущую вершину как предыдущую для соседа
                prev[i] = current;
                // Добавляем соседа в очередь с приоритетами
                pq.push({dist[i], i});
            }
        }
    }
    // Если путь до конечной вершины не найден
    if (dist[end] == INT64_MAX) return "Путь не найден";
    // Восстанавливаем путь от конечной вершины до начальной
    std::vector<long long int> path;
    for (long long int at = end; at != -1; at = prev[at])
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    // Строим строку с путем
    std::string pathStr;
    for (auto v : path)
    {
        pathStr += std::to_string(v) + "->";
    }
    // Удаляем последнюю стрелку "->"
    pathStr.pop_back();
    pathStr.pop_back();
    // Добавляем вес пути в конец строки
    pathStr += " " + std::to_string(dist[end]);
    return QString(QString::fromStdString(pathStr));
}

void GraphMan::deicstraBTNclicked() // находит кратчайший путь от и до по алгоритму Дейкстры, выводит в поле для вывода
{
    int64_t start = ui->deicstraStart->text().toLongLong();
    if(start > static_cast<int64_t>(gr.tableOfvertex.size())-1 || start < 1) return;
    int64_t finish = ui->deicstraFinish->text().toLongLong();
    if(finish > static_cast<int64_t>(gr.tableOfvertex.size())-1 || finish < 1) return;
    ui->deicstraStart->setText("");
    ui->deicstraFinish->setText("");
    ui->output->setText(dijkstra(gr.tableOfgraph, start, finish));
}

GraphMan::~GraphMan()
{
    delete ui;
}
```

`main.cpp`
```cpp
#include "graphman.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphMan w;
    w.show();
    return a.exec();
}
```

`graphman.ui`
```xml
<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>GraphMan</class>
 <widget class="QMainWindow" name="GraphMan">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>1258</width>
    <height>660</height>
   </rect>
  </property>
  <property name="sizePolicy">
   <sizepolicy hsizetype="Fixed" vsizetype="Fixed">
    <horstretch>0</horstretch>
    <verstretch>0</verstretch>
   </sizepolicy>
  </property>
  <property name="minimumSize">
   <size>
    <width>1258</width>
    <height>660</height>
   </size>
  </property>
  <property name="maximumSize">
   <size>
    <width>1258</width>
    <height>660</height>
   </size>
  </property>
  <property name="windowTitle">
   <string>Графы</string>
  </property>
  <widget class="QWidget" name="centralwidget">
   <widget class="QGraphicsView" name="graphTV">
    <property name="geometry">
     <rect>
      <x>370</x>
      <y>10</y>
      <width>881</width>
      <height>641</height>
     </rect>
    </property>
    <property name="sizePolicy">
     <sizepolicy hsizetype="Expanding" vsizetype="Expanding">
      <horstretch>0</horstretch>
      <verstretch>0</verstretch>
     </sizepolicy>
    </property>
   </widget>
   <widget class="QPushButton" name="addVertexBTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>110</y>
      <width>351</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Добавить вершину</string>
    </property>
   </widget>
   <widget class="QPushButton" name="delVertexBTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>160</y>
      <width>241</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Удалить вершину</string>
    </property>
   </widget>
   <widget class="QPushButton" name="addEdgeBTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>210</y>
      <width>351</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Добавить/изменить ребро</string>
    </property>
   </widget>
   <widget class="QPushButton" name="delEdgeBTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>310</y>
      <width>351</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Удалить ребро</string>
    </property>
   </widget>
   <widget class="QLineEdit" name="addEdgeStart">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>260</y>
      <width>71</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="text">
     <string/>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QLineEdit" name="addEdgeFinish">
    <property name="geometry">
     <rect>
      <x>90</x>
      <y>260</y>
      <width>71</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QLineEdit" name="addEdgeWeight">
    <property name="geometry">
     <rect>
      <x>170</x>
      <y>260</y>
      <width>91</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QLineEdit" name="addEdgeReverseWeight">
    <property name="geometry">
     <rect>
      <x>270</x>
      <y>260</y>
      <width>91</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QLineEdit" name="delEdgeStart">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>360</y>
      <width>171</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QLineEdit" name="delEdgeFinish">
    <property name="geometry">
     <rect>
      <x>190</x>
      <y>360</y>
      <width>171</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QLineEdit" name="delVertexInput">
    <property name="geometry">
     <rect>
      <x>260</x>
      <y>160</y>
      <width>101</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="text">
     <string/>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QPushButton" name="updateTVBTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>60</y>
      <width>351</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Обновить экран</string>
    </property>
   </widget>
   <widget class="QPushButton" name="tableBTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>10</y>
      <width>351</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Режим таблицы смежности</string>
    </property>
   </widget>
   <widget class="QPushButton" name="graphBTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>10</y>
      <width>351</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Режим графа</string>
    </property>
   </widget>
   <widget class="QPushButton" name="BFS_BTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>410</y>
      <width>171</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Обход в ширину</string>
    </property>
   </widget>
   <widget class="QLineEdit" name="BFS_start">
    <property name="geometry">
     <rect>
      <x>190</x>
      <y>410</y>
      <width>171</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QPushButton" name="DFS_BTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>460</y>
      <width>171</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Обход в глубину</string>
    </property>
   </widget>
   <widget class="QLineEdit" name="DFS_start">
    <property name="geometry">
     <rect>
      <x>190</x>
      <y>460</y>
      <width>171</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QPushButton" name="deicstraBTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>510</y>
      <width>351</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Алгоритм Дейкстры</string>
    </property>
   </widget>
   <widget class="QLineEdit" name="deicstraStart">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>560</y>
      <width>171</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QLineEdit" name="deicstraFinish">
    <property name="geometry">
     <rect>
      <x>190</x>
      <y>560</y>
      <width>171</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
     </font>
    </property>
    <property name="maxLength">
     <number>18</number>
    </property>
   </widget>
   <widget class="QTextBrowser" name="output">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>610</y>
      <width>351</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>12</pointsize>
     </font>
    </property>
   </widget>
  </widget>
 </widget>
 <resources/>
 <connections/>
</ui>
```

`GraphMan.pro`
```cpp
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ArrowItem.cpp \
    main.cpp \
    graphman.cpp \
    moveitem.cpp

HEADERS += \
    ArrowItem.h \
    graphman.h \
    moveitem.h

FORMS += \
    graphman.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
```

## Тесты скриншоты

Работу программы сложно показать на скриншоте, поэтому здесь есть видео:

[![](https://markdown-videos-api.jorgenkh.no/youtube/puQ_uYhDuMc)](https://youtu.be/puQ_uYhDuMc)