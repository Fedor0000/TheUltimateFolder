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

