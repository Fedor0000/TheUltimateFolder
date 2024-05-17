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
