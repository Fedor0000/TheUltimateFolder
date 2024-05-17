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

