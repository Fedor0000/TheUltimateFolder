# Лабораторная работа "Бинарные деревья"

## Постановка задачи

```txt
1. Самостоятельно придумать вид Дерева и реализовать алгоритмы для этого собственного варианта бинарного дерева поиска, имеющего не менее трёх уровней.

2. Алгоритмы:
2.1. Необходимо реализовать функции для редактирования дерева:
 - Вставка узла.
 - Удаление узла.
 - Поиск элемента по ключу.
2.2 Реализовать алгоритмы обхода дерева:
2.3 Прямой
2.4 Симметричный
2.5 Обратный
2.6 Выполнить задание своего варианта из методички:
Laby_Chast_3.docx

3. Реализовать алгоритм балансировки дерева.

4. Реализовать вертикальную и горизонтальную печать.

5. Визуализацию дерева выполнить с использованием любой доступной графической библиотеки – SFML, SDL, OpenGL…
6. Пользовательский интерфейс – на усмотрение разработчика - с условием кроссплатформенности (например, Windows Forms; также поощряется использование Qt или иных фреймворков).
```

### 7 Вариант:

Дерево с полем char*.

## UML-диаграмма

![uml](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/visual_labs/otcheti/binWoods.jpg)

## Код программы

`wood.h`
```cpp
#include <QChar>
#ifndef WOOD_H
#define WOOD_H

class Wood
{
public:
    Wood();
    ~Wood();
    QChar* data; // данные узла дерева
    Wood* left; // указатель на левое поддерево
    Wood* right; // указатель на правое поддерево
    int dataSize = 0; // размер массива символов
    int depth = 0; // глубина дерева (задействованно только для первого дерева, в теории, можно считать глубину для каждого поддерева)
};

#endif // WOOD_H
```

`wood.cpp`
```cpp
#include "wood.h"
Wood::Wood() // конструктор
{
    data = nullptr;
    left = nullptr;
    right = nullptr;
}

void deleteWoods(Wood* w) // удаление дерева/поддерева
{
    if(w == nullptr) return;
    Wood* current = w;
    if(current->left != nullptr) deleteWoods(current->left);
    if(current->right != nullptr) deleteWoods(current->right);
    if (current != nullptr)
    {
        delete[] current->data;
        current->data = nullptr;
    }
}


Wood::~Wood() // деструктор
{
    if(this == nullptr) return;
    Wood* current = this;
    if(current->left != nullptr) deleteWoods(current->left);
    if(current->right != nullptr) deleteWoods(current->right);
    if (current != nullptr)
    {
        delete[] current->data;
        current->data = nullptr;
        dataSize = 0;
    }
}
```

`binarywoods.h`
```cpp
#ifndef BINARYWOODS_H
#define BINARYWOODS_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <wood.h>

QT_BEGIN_NAMESPACE
namespace Ui { class BinaryWoods; }
QT_END_NAMESPACE

class BinaryWoods : public QMainWindow
{
    Q_OBJECT

public:
    BinaryWoods(QWidget *parent = nullptr);
    ~BinaryWoods();
    QGraphicsView *graphicsView; // телевизор для вывода графической сцены
    QGraphicsScene *scene; // собственно сама графическая сцена
    Wood* binaryWood = nullptr; //указатель на бинарное дерево
    void allBTNsBlock(); // метод блокировки всех кнопок
    void allBTNsUnBlock(); // метод разблокировки кнопок
    void printWood(int, int, int, Wood*); // печать дерева (рекурсивная)
    void reCreateTV(); // пересоздать телевизор
    Wood* pathWood(QString); // возвращает указатель на предпоследний элемент, найденный по пути вида rlrl, проверяет путь на правильность
    void obhodPrinter(); // выводит результаты обхода на телевизор
public slots:
    void getText(); // получает текст из поля ввода в глобальную строку
    void stop(); // останавливает ввод элементов
    void createWood(); // создает дерево
    void balanceTree(); // балансирует дерево
    void addElement(); // добавляет элемент в дерево
    void delElement(); // удаляят элемент из дерева по пути, за элементом удаляется и все его поддерево
    void delWood(); // удаляет дерево
    void searcher(); // ищет элементы в дереве
    void closeSearch(); // закрывает режим поиска
    void directObhod(); // прямой обход дерева и его вывод на телевизор
    void symmetricalObhod(); // симметричный обход дерева и его вывод на телевизор
    void reverseObhod(); // обратный обход дерева и его вывод на телевизор
    void closeObhod(); // закрывает режим обхода и чистит от него телевизор
private:
    Ui::BinaryWoods *ui;
};
#endif // BINARYWOODS_H
```

`binarywoods.cpp`
```cpp
#include "wood.h"
#include "binarywoods.h"
#include "ui_binarywoods.h"
#include <QIntValidator>
#include <QTime>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <cmath>
#define EMERGENCY_STOP "🛑🛑🛑🛑🛑🛑🛑🛑🛑🛑🛑🛑🛑🛑🛑🛑" // последоватеьность, которую явно нельзя ввести, нужна для остановки ввода элементов

QString str = ""; // для пользовательского ввода
std::vector<std::pair<QString, QString>> sea; //вектор для поиска: 1 - путь, 2 - сам элемент
std::vector<QString> obh; // вектор для обходов

BinaryWoods::BinaryWoods(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BinaryWoods)
{
    ui->setupUi(this);
    connect(ui->createWoodBTN, &QPushButton::clicked, this, &BinaryWoods::createWood); //коннекты кнопок
    connect(ui->okBTN, &QPushButton::clicked, this, &BinaryWoods::getText);
    connect(ui->balanceBTN, &QPushButton::clicked, this, &BinaryWoods::balanceTree);
    connect(ui->addElemsBTN, &QPushButton::clicked, this, &BinaryWoods::addElement);
    connect(ui->deleteElemBTN, &QPushButton::clicked, this, &BinaryWoods::delElement);
    connect(ui->delWoodBTN, &QPushButton::clicked, this, &BinaryWoods::delWood);
    connect(ui->findElemsBTN, &QPushButton::clicked, this, &BinaryWoods::searcher);
    connect(ui->closeSearchBTN, &QPushButton::clicked, this, &BinaryWoods::closeSearch);
    connect(ui->stopBTN, &QPushButton::clicked, this, &BinaryWoods::stop);
    connect(ui->directBTN, &QPushButton::clicked, this, &BinaryWoods::directObhod);
    connect(ui->closeObhodBTN, &QPushButton::clicked, this, &BinaryWoods::closeObhod);
    connect(ui->symetricalBTN, &QPushButton::clicked, this, &BinaryWoods::symmetricalObhod);
    connect(ui->reverseBTN, &QPushButton::clicked, this, &BinaryWoods::reverseObhod);

    ui->closeSearchBTN->setHidden(true);//прячем пока не нужные кнопки
    ui->stopBTN->setHidden(true);
    ui->closeObhodBTN->setHidden(true);

    graphicsView = ui->woodTV; //коннекты деревянного телевизора и сцены
    scene = new QGraphicsScene;
    graphicsView -> setScene(scene);

    srand(time(NULL)); // обнавление сида генератора случайных чисел
}

void delay() //ждём
{
    QTime dieTime= QTime::currentTime().addMSecs(1);
    while (QTime::currentTime() < dieTime) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QString randomString() // генератор случайной строки
{
    QString mass = "~!@#$%^&*()_+|<>{}[]`=-№.,;:1234567890АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюяABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // массив символов, из которых генерируется случайная строка
    QChar qch; // символ для генерации
    QString s; // строка-результат
    int len = rand() % 16; // выбираем длину строки
    if (len==0) len = 1; // пустые строки делаем длиной 1
    for(int i = 0; i < len; i++) // заполняем строку
    {
        qch = mass[(rand() % mass.size())]; // получаем случайный символ
        s.push_back(qch); // добавляем в строку
    }
    return s; // возвращаем результат
}

int maxDepth(Wood* T) //находим глубину рекурсивно
{
    if (T==NULL) return 0;
    return std::max(maxDepth(T->left),maxDepth(T->right))+1;
}

void BinaryWoods::allBTNsBlock() //выключаем все кнопки
{
    ui->addElemsBTN->setEnabled(false);
    ui->createWoodBTN->setEnabled(false);
    ui->balanceBTN->setEnabled(false);
    ui->deleteElemBTN->setEnabled(false);
    ui->delWoodBTN->setEnabled(false);
    ui->findElemsBTN->setEnabled(false);
    ui->directBTN->setEnabled(false);
    ui->symetricalBTN->setEnabled(false);
    ui->reverseBTN->setEnabled(false);
}
void BinaryWoods::allBTNsUnBlock() //включаем все кнопки
{
    ui->addElemsBTN->setEnabled(true);
    ui->createWoodBTN->setEnabled(true);
    ui->balanceBTN->setEnabled(true);
    ui->deleteElemBTN->setEnabled(true);
    ui->delWoodBTN->setEnabled(true);
    ui->findElemsBTN->setEnabled(true);
    ui->directBTN->setEnabled(true);
    ui->symetricalBTN->setEnabled(true);
    ui->reverseBTN->setEnabled(true);
}

void BinaryWoods::reCreateTV() //пересоздать сцену и телевизор, очищает все полностью
{
    QGraphicsScene* del = scene;
    scene = new QGraphicsScene;
    delete del;
    ui->woodTV->setScene(scene);
    ui->woodTV->update();
}

void NewTree(Wood*&r, QChar* data, int masLen)   //функция создания нового дерева/добавления элемента
{
    if(NULL==r)
    {
        r=new Wood;
        r->left=r->right=NULL;
        r->data=data;       //запись элемента
        r->dataSize = masLen; // и длины массива
    }
    else
    {
        if(data<r->data)     //запись в левое поддерево
        {
            if(r->left!=NULL) NewTree(r->left,data, masLen);
            else
            {
                r->left=new Wood;
                r->left->left=r->left->right=NULL;
                r->left->data=data;
                r->left->dataSize = masLen;
            }
        }
        else                 //запись в правое поддерево
        {
            if(r->right!=NULL) NewTree(r->right,data, masLen);
            else
            {
                r->right=new Wood;
                r->right->right=r->right->left=NULL;
                r->right->data=data;
                r->right->dataSize = masLen;
            }
        }
    }
    r->depth = maxDepth(r); // запись глубины
}

void collectNodes(Wood* node, std::vector<std::pair<QChar*, int>>& nodes) //получает вектор пар, где первое - данные узла дерева (массив символов), второе - его размер
    {
        if (node == nullptr)
        {
            return;
        }
        collectNodes(node->left, nodes);
        collectNodes(node->right, nodes);
        nodes.push_back(std::make_pair(node->data, node->dataSize));
    }

Wood* buildBalancedTree(const std::vector<std::pair<QChar*, int>>& nodes, int start, int finish) //создает сбалансированное дерево из вектора пар
{
        if (start > finish)
        {
            return nullptr;
        }

        int mid = (start + finish) / 2;
        Wood* newNode = new Wood;
        newNode->data = nodes[mid].first;
        newNode->dataSize = nodes[mid].second;
        newNode->left = buildBalancedTree(nodes, start, mid - 1);
        newNode->right = buildBalancedTree(nodes, mid + 1, finish);
        return newNode;
}

void BinaryWoods::balanceTree() //создает сбалансированное дерево и обновляет дисплей
{
        std::vector<std::pair<QChar*, int>> nodes;
        collectNodes(binaryWood, nodes);
        binaryWood = nullptr;
        std::sort(nodes.begin(), nodes.end());
        binaryWood = buildBalancedTree(nodes, 0, nodes.size() - 1);
        reCreateTV();
        binaryWood->depth = maxDepth(binaryWood);
        printWood((pow(2, binaryWood->depth-1)*55), 0, 0, binaryWood);
}

void BinaryWoods::printWood(int sdvig, int x, int y, Wood* woo) //выводит дерево на деревянный телевизор рекурсивно
{
    if (binaryWood != nullptr)
    {
        QString text;
        for(int i = 0; i < woo->dataSize; i++) text.push_back(woo->data[i]);               // вывод текущего узла
        scene->addPolygon(QRectF(x, y, 200, 30), QPen(Qt::black), QBrush(Qt::lightGray));
        QGraphicsTextItem *textItem = scene->addText(text);
        textItem->setFont(QFont("Cascadia Code", 12, 2, false));
        textItem->setPos(x+4, y-2);
        if (woo->left != nullptr) // вывод левого поддерева
        {
            printWood(sdvig/2, x-std::abs(sdvig), y+100, woo->left);
            scene->addLine(x+100, y+30, x-std::abs(sdvig)+100, y+100, QPen(Qt::black));
        }
        if (woo->right != nullptr) // вывод правого поддерева
        {
            printWood(sdvig/2, x+std::abs(sdvig), y+100, woo->right);
            scene->addLine(x+100, y+30, x+std::abs(sdvig)+100, y+100, QPen(Qt::black));
        }
        ui->woodTV->update();
    }
}

void BinaryWoods::getText() //получает текст в глобальную строку по нажатию ОК
{
    if(ui->inputVsego->text()=="") return; // если текста нет, то выходим
    str = ui->inputVsego->text(); // если есть то берем
    ui->okBTN->setEnabled(false); // выключам кнопку
    ui->inputVsego->clear(); // чистим поле ввода
    ui->inputVsego->setEnabled(false); // выключаем его
    ui->textovoePole->setText(""); // убираем из него текст
}

void BinaryWoods::stop() // остановка ввода
{
    str = EMERGENCY_STOP; // вводит специальную последовательность, останавливающую ввод
}

void BinaryWoods::createWood() //создать/пересоздать дерево
{
    if (binaryWood !=nullptr) // если есть дерево - удалить деструктор справится, я проверил
    {
        binaryWood->~Wood();
        binaryWood = nullptr;
    }
    reCreateTV(); // прочистить сцену и телик
    allBTNsBlock(); //выкл кнопки
    ui->textovoePole->setText("Введите количество элементов:");
    ui->inputVsego->setEnabled(true); //делаем активным то что нужно и меняем текст
    ui->okBTN->setEnabled(true);
    QValidator *validator = new QIntValidator(1, 1000000000, this); // ограничим ввод
    ui->inputVsego->setValidator(validator);
    ui->inputVsego->setFocus();
    while(str=="") //ждём ввода
    {
        delay();
    }
    int elemKolvo = str.toInt();
    str = "";
    for(int i = 0; i < elemKolvo; i++) //вводим сами элементы
    {
        QString tekst = "Введите элемент №";
        tekst.push_back(QString::number (i)); //меняем текст
        tekst.push_back(':');
        ui->textovoePole->setText(tekst);
        ui->inputVsego->setEnabled(true);// делаем активным только нужное
        ui->okBTN->setEnabled(true);
        ui->inputVsego->setMaxLength(15); // ограничили ввод на 15 символов
        ui->inputVsego->setValidator(NULL); // убрали ограничение на числа
        ui->inputVsego->setText(randomString()); // рандомная строка для быстрого создания дерева
        ui->inputVsego->setSelection(0, 16); // если введем свою, рандомная сотрется, тк выделена
        ui->inputVsego->setFocus();
        ui->stopBTN->setHidden(false);

        while(str=="") //ждем ввода
        {
            delay();
        }

        if (str == EMERGENCY_STOP) // если нажали стоп то остановить цикл аккуратно
        {
            str="";
            ui->stopBTN->setHidden(true);
            ui->textovoePole->setText("");
            ui->inputVsego->clear();
            ui->inputVsego->setEnabled(false);
            ui->okBTN->setEnabled(false);
            break;
        }

        QChar* data = new QChar[str.size()]; //получили поле данных для узла дерева
        for(int j = 0; j < str.size(); j++)
        {
            data[j] = str[j];
        }
        NewTree(binaryWood, data, str.size()); //добавили элемент или создали дерево, если он первый
        str = ""; // очистили строку
    }
    ui->stopBTN->setHidden(true); // спрятали кнопку стоп
    printWood((pow(2, binaryWood->depth-1)*55), 0, 0, binaryWood); //вывели дерево на деревянный телевизор
    ui->createWoodBTN->setText("Пересоздать дерево"); //изменили текст кнопки
    allBTNsUnBlock(); //вкл кнопки
}

void BinaryWoods::addElement() // добавить элемент
{
    allBTNsBlock(); //выкл кнопки
    QString tekst = "Введите элемент:";
    ui->textovoePole->setText(tekst);
    ui->inputVsego->setEnabled(true);// делаем активным только нужное
    ui->okBTN->setEnabled(true);
    ui->inputVsego->setMaxLength(15); // ограничили ввод на 15 символов
    ui->inputVsego->setValidator(NULL); // убрали ограничение на числа
    ui->inputVsego->setFocus();
    while(str=="") //ждем ввода
    {
        delay();
    }
    QChar* data = new QChar[str.size()]; //получили поле данных для узла дерева
    for(int j = 0; j < str.size(); j++)
    {
        data[j] = str[j];
    }
    NewTree(binaryWood, data, str.size()); //добавили элемент или создали дерево, если он первый
    str = ""; // очистили строку
    reCreateTV(); // прочистили сцену и телек
    binaryWood->depth = maxDepth(binaryWood); // нашли новую глубину
    printWood((pow(2, binaryWood->depth-1)*55), 0, 0, binaryWood); // вывели дерево
    allBTNsUnBlock(); //вкл кнопки
}

Wood* BinaryWoods::pathWood(QString path) //доходит по пути до предпоследнего элемента, проверяя правильность всего пути
{
    Wood* current = binaryWood;
    for (int i = 0; i <path.size()-1; i++)
    {
        if (path[i] == 'r')
        {
            if (current->right != nullptr) current = current->right;
            else return nullptr; //тк путь уже неверный
        }
        else if (path[i] == 'l')
        {
            if (current->left != nullptr) current = current->left;
            else return nullptr; //тк путь уже неверный
        }
    }
    if ((path[path.size()-1] == 'r')&&(current->right) != nullptr) return current; //путь верный, возврат предпосл. элемента
    if ((path[path.size()-1] == 'l')&&(current->left) != nullptr) return current; // путь верный, возврат предпосл. элемента
    return nullptr; //тк последнее звено пути неверно
}

void BinaryWoods::delElement() // удаляет элемент, и как следствие, всю его ветку
{
    allBTNsBlock(); //выкл кнопки
    QString tekst = "Введите путь в виде rrllrl:";
    ui->textovoePole->setText(tekst);
    ui->inputVsego->setEnabled(true);// делаем активным только нужное
    ui->okBTN->setEnabled(true);
    ui->inputVsego->setMaxLength(1000000); // почти сняли ограничение ввода
    QRegExp re("[rl]+$"); // ограничение на буквы
    QRegExpValidator*v = new QRegExpValidator(re);
    ui->inputVsego->setValidator(v); // убрали ограничение на числа и поставили на буквы r l
    ui->inputVsego->setFocus();
    while(str=="") //ждем ввода
    {
        delay();
    }
    if(pathWood(str) != nullptr) //если путь верный
    {
        Wood* parentOfDelWood = pathWood(str); //получили путь и по пути указатель на родителя удаляемого элемента
        Wood* delWood = (str[str.size()-1] == 'r' ? parentOfDelWood->right : parentOfDelWood->left);
        if (str[str.size()-1] == 'r') parentOfDelWood->right = nullptr;
        else parentOfDelWood->left = nullptr;
        delWood->~Wood(); //удалили поддерево
        reCreateTV();
        binaryWood->depth = maxDepth(binaryWood);
        printWood((pow(2, binaryWood->depth-1)*55), 0, 0, binaryWood);
    }
    else
    {
        ui->textovoePole->setText("Неверный путь!");
        QTime dieTime= QTime::currentTime().addMSecs(1500);
        while (QTime::currentTime() < dieTime) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        ui->textovoePole->setText("");
    }
    str = ""; // очистили строку
    allBTNsUnBlock(); //вкл кнопки
}

void pathSearch(QChar key, QString path, Wood*w) // поиск элемнта по первому символу рекурсивно, в глобальный вектор добавляет пары из найденного элемента и его пути
{
    if (w == nullptr) return;
    if (w->left != nullptr) pathSearch(key, path+"l", w->left);
    if (w->right != nullptr) pathSearch(key, path+"r", w->right);
    if (w->data[0] == key)
    {
        QString convertedData;
        for (int i = 0; i < w->dataSize; i++) convertedData.push_back(w->data[i]);
        sea.push_back(std::make_pair(path, convertedData));
    }
}

void BinaryWoods::searcher() // поиск и вывод результатов на экран
{
    allBTNsBlock(); //выкл кнопки
    QString tekst = "Введите символ для поиска:";
    ui->textovoePole->setText(tekst);
    ui->inputVsego->setEnabled(true); // делаем активным только нужное
    ui->okBTN->setEnabled(true);
    ui->inputVsego->setMaxLength(1); // ограничение ввода
    ui->inputVsego->setValidator(NULL); // убрали ограничение на числа
    ui->inputVsego->setFocus();
    while(str=="") //ждем ввода
    {
        delay();
    }
    QChar key = str[0];
    str="";
    pathSearch(key, "", binaryWood);

    int y = 0;
    for(unsigned int i = 0; i < sea.size(); i++) // печатаем пары: элемент и  путь
    {
        QGraphicsTextItem *textItem = scene->addText(sea[i].second);
        textItem->setFont(QFont("Cascadia Code", 20, 2, false));
        textItem->setPos(-200, y-100);

        QGraphicsTextItem *textItem1 = scene->addText(sea[i].first);
        textItem1->setFont(QFont("Cascadia Code", 20, 2, false));
        textItem1->setPos(300, y-100);
        y-=100;
    }
    QGraphicsTextItem *textItem = scene->addText("Результаты поиска:"); // печать заголовка
    textItem->setFont(QFont("Cascadia Code", 20, 2, false));
    textItem->setPos(-140, y-200);

    QString result = "Найдено "; // ... и кол-ва найденных элементов
    result.push_back(QString::number(sea.size()));
    result.push_back(" элемента(ов).");
    QGraphicsTextItem *textItem1 = scene->addText(result);
    textItem1->setFont(QFont("Cascadia Code", 20, 2, false));
    textItem1->setPos(-150, y-100);

    ui->woodTV->update();
    sea.clear();

    ui->findElemsBTN->setHidden(true); // кнопки меняем
    ui->closeSearchBTN->setHidden(false);
}

void BinaryWoods::closeSearch() // закрыть поиск и убрать с телека лишнее
{
    ui->findElemsBTN->setHidden(false);
    ui->closeSearchBTN->setHidden(true);
    reCreateTV();
    printWood((pow(2, binaryWood->depth-1)*55), 0, 0, binaryWood);
    allBTNsUnBlock();
}

void BinaryWoods::delWood() // удаляет все дерево
{
    if (binaryWood!=nullptr)
    {
        binaryWood->~Wood();
        binaryWood = nullptr;
    }
    allBTNsBlock();
    ui->createWoodBTN->setText("Создать дерево");
    ui->createWoodBTN->setEnabled(true);
    reCreateTV();
}

void BinaryWoods::obhodPrinter() // печатает результат обхода из глобальной строки
{
    int y = -(obh.size()+1)*50;
    for(unsigned int i = 0; i < obh.size(); i++)
    {
        QGraphicsTextItem *textItem = scene->addText(obh[i]);
        textItem->setFont(QFont("Cascadia Code", 20, 2, false));
        textItem->setPos(-50, y+50);
        y+=50;
    }
    ui->woodTV->update();
}

void direct(Wood *tree) //прямой обход, созраняет в вектор с парами
{
    if (tree!=NULL) //Пока не встретится пустой узел
    {
        QString tmp;
        for (int i = 0; i < tree->dataSize; i++) tmp.push_back(tree->data[i]);
        obh.push_back(tmp);
        direct(tree->left); //Рекурсивная функция для левого поддерева
        direct(tree->right); //Рекурсивная функция для правого поддерева
    }
}

void BinaryWoods::directObhod() // производит прямой обход и выводит результат
{
    allBTNsBlock();
    obh.clear();
    direct(binaryWood);
    obhodPrinter();
    int y = -(obh.size()+2)*50;
    QGraphicsTextItem *textItem = scene->addText("Прямой обход:");
    textItem->setFont(QFont("Cascadia Code", 20, 2, false));
    textItem->setPos(-50, y+50);
    obh.clear();
    ui->closeObhodBTN->setHidden(false);
    ui->closeObhodBTN->setGeometry(10, 430, 291, 51);
}

void symmetrical(Wood *tree) //симметричный обход
{
    if (tree!=NULL) //Пока не встретится пустой узел
    {
      symmetrical(tree->left); //Рекурсивная функция для левого поддерева
      QString tmp;
      for (int i = 0; i < tree->dataSize; i++) tmp.push_back(tree->data[i]);
      obh.push_back(tmp);
      symmetrical(tree->right); //Рекурсивная функция для правого поддерева
    }
}

void BinaryWoods::symmetricalObhod() // производит симметричный обход и выводит на телек
{
    allBTNsBlock();
    obh.clear();
    symmetrical(binaryWood);
    obhodPrinter();
    int y = -(obh.size()+2)*50;
    QGraphicsTextItem *textItem = scene->addText("Симметр. обход:");
    textItem->setFont(QFont("Cascadia Code", 20, 2, false));
    textItem->setPos(-50, y+50);
    obh.clear();
    ui->closeObhodBTN->setHidden(false);
    ui->closeObhodBTN->setGeometry(10, 500, 291, 51);
}

void reverse(Wood *tree) //обратный обход, созраняет в вектор с парами
{
    if (tree!=NULL) //Пока не встретится пустой узел
    {
        direct(tree->left); //Рекурсивная функция для левого поддерева
        direct(tree->right); //Рекурсивная функция для правого поддеревa
        QString tmp;
        for (int i = 0; i < tree->dataSize; i++) tmp.push_back(tree->data[i]);
        obh.push_back(tmp);
    }
}

void BinaryWoods::reverseObhod() // производит обратный обход и выводит на телек
{
    allBTNsBlock();
    obh.clear();
    reverse(binaryWood);
    obhodPrinter();
    int y = -(obh.size()+2)*50;
    QGraphicsTextItem *textItem = scene->addText("Обратный обход:");
    textItem->setFont(QFont("Cascadia Code", 20, 2, false));
    textItem->setPos(-50, y+50);
    obh.clear();
    ui->closeObhodBTN->setHidden(false);
    ui->closeObhodBTN->setGeometry(10, 570, 291, 51);
}

void BinaryWoods::closeObhod() // чистит телек от обходов и вклячает нужные кнопки
{
    ui->closeObhodBTN->setHidden(true);
    reCreateTV();
    printWood((pow(2, binaryWood->depth-1)*55), 0, 0, binaryWood);
    allBTNsUnBlock();
}

BinaryWoods::~BinaryWoods()
{
   delete ui;
}
```

`main.cpp`
```cpp
#include "binarywoods.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BinaryWoods w;
    w.show();
    return a.exec();
}
```

`binarywoods.ui`
```xml
<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>BinaryWoods</class>
 <widget class="QMainWindow" name="BinaryWoods">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>1866</width>
    <height>963</height>
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
    <width>1866</width>
    <height>963</height>
   </size>
  </property>
  <property name="maximumSize">
   <size>
    <width>1866</width>
    <height>963</height>
   </size>
  </property>
  <property name="windowTitle">
   <string>Бинарные деревья</string>
  </property>
  <widget class="QWidget" name="centralwidget">
   <widget class="QPushButton" name="createWoodBTN">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>10</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Создать дерево</string>
    </property>
   </widget>
   <widget class="QPushButton" name="addElemsBTN">
    <property name="enabled">
     <bool>false</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>150</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Добавить элемент</string>
    </property>
   </widget>
   <widget class="QPushButton" name="deleteElemBTN">
    <property name="enabled">
     <bool>false</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>220</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Удалить элемент</string>
    </property>
   </widget>
   <widget class="QPushButton" name="delWoodBTN">
    <property name="enabled">
     <bool>false</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>290</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Удалить дерево</string>
    </property>
   </widget>
   <widget class="QPushButton" name="balanceBTN">
    <property name="enabled">
     <bool>false</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>80</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Баланс дерева</string>
    </property>
   </widget>
   <widget class="QLabel" name="textovoePole">
    <property name="enabled">
     <bool>true</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>640</y>
      <width>291</width>
      <height>31</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>9</pointsize>
     </font>
    </property>
    <property name="text">
     <string/>
    </property>
    <property name="alignment">
     <set>Qt::AlignCenter</set>
    </property>
   </widget>
   <widget class="QLineEdit" name="inputVsego">
    <property name="enabled">
     <bool>false</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>100</x>
      <y>680</y>
      <width>113</width>
      <height>21</height>
     </rect>
    </property>
   </widget>
   <widget class="QPushButton" name="findElemsBTN">
    <property name="enabled">
     <bool>false</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>360</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="mouseTracking">
     <bool>false</bool>
    </property>
    <property name="text">
     <string>Найти элементы</string>
    </property>
   </widget>
   <widget class="QPushButton" name="okBTN">
    <property name="enabled">
     <bool>false</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>220</x>
      <y>680</y>
      <width>41</width>
      <height>21</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>9</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="tabletTracking">
     <bool>false</bool>
    </property>
    <property name="text">
     <string>OK</string>
    </property>
    <property name="autoDefault">
     <bool>false</bool>
    </property>
    <property name="default">
     <bool>false</bool>
    </property>
   </widget>
   <widget class="QGraphicsView" name="woodTV">
    <property name="geometry">
     <rect>
      <x>310</x>
      <y>0</y>
      <width>1551</width>
      <height>961</height>
     </rect>
    </property>
    <property name="sizePolicy">
     <sizepolicy hsizetype="Expanding" vsizetype="Expanding">
      <horstretch>0</horstretch>
      <verstretch>0</verstretch>
     </sizepolicy>
    </property>
   </widget>
   <widget class="QPushButton" name="closeSearchBTN">
    <property name="enabled">
     <bool>true</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>360</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="mouseTracking">
     <bool>false</bool>
    </property>
    <property name="text">
     <string>Закрыть поиск</string>
    </property>
   </widget>
   <widget class="QPushButton" name="stopBTN">
    <property name="enabled">
     <bool>true</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>100</x>
      <y>710</y>
      <width>111</width>
      <height>31</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="mouseTracking">
     <bool>false</bool>
    </property>
    <property name="text">
     <string>СТОП</string>
    </property>
   </widget>
   <widget class="QPushButton" name="directBTN">
    <property name="enabled">
     <bool>false</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>430</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Прямой обход</string>
    </property>
   </widget>
   <widget class="QPushButton" name="symetricalBTN">
    <property name="enabled">
     <bool>false</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>500</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Симметричный обход</string>
    </property>
   </widget>
   <widget class="QPushButton" name="reverseBTN">
    <property name="enabled">
     <bool>false</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>570</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="text">
     <string>Обратный обход</string>
    </property>
   </widget>
   <widget class="QPushButton" name="closeObhodBTN">
    <property name="enabled">
     <bool>true</bool>
    </property>
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>430</y>
      <width>291</width>
      <height>51</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <family>Montserrat Alternates</family>
      <pointsize>14</pointsize>
     </font>
    </property>
    <property name="cursor">
     <cursorShape>PointingHandCursor</cursorShape>
    </property>
    <property name="mouseTracking">
     <bool>false</bool>
    </property>
    <property name="text">
     <string>Закрыть обход</string>
    </property>
   </widget>
  </widget>
 </widget>
 <resources/>
 <connections/>
</ui>
```

`binarywoods.pro`
```cpp
QT += opengl

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    binarywoods.cpp \
    wood.cpp

HEADERS += \
    binarywoods.h \
    wood.h

FORMS += \
    binarywoods.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
```

## Тесты скриншоты

Работу программы сложно показать на скриншоте, поэтому здесь есть видео:

![видео](https://youtu.be/QN4MX_hL6bs)