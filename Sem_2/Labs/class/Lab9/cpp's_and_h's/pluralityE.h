/*
👍🏻 - Он убирает кракозябры.
Класс - контейнер МНОЖЕСТВО с элементами типа int.
Реализовать операции:
[]    – доступа по индексу;
int() – определение размера вектора;
*     – пересечение множеств;
--    - удаление элемента из множества.
1 и 2 реализация

1. Реализовать класс, перегрузить для него операции, указанные в варианте.
2. Определить исключительные ситуации.
3. Предусмотреть генерацию исключительных ситуаций.
*/
#pragma once
using namespace std;
class PluralityE
{
public:
	PluralityE();
	PluralityE(unsigned int);
	PluralityE(unsigned int s, int k);
	PluralityE(const PluralityE& a);
	~PluralityE();
	unsigned int getCapacity();
	void deleteDubs();
	void pushBack(int);
	int& back();
	int popBack();
	void diet();
	void setSize(unsigned int);
	void setCapacity(unsigned int);
	PluralityE& operator=(const PluralityE&);
	unsigned int operator ()();
	int& operator[](int);
	PluralityE operator+(const int);
	PluralityE operator*(PluralityE&);
	PluralityE& operator--(int);
	PluralityE& operator--();
	friend ostream& operator<<(ostream& out, PluralityE& a);
	friend istream& operator>>(istream& in, PluralityE& a);
private:
	unsigned int capacity; // размер массива
	unsigned int size; // НОМЕР самого последнего элемента
	int* data;
};