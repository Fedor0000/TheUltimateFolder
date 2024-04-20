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
class Plurality
{
public:
	Plurality();
	Plurality(unsigned int);
	Plurality(unsigned int s, int k);
	Plurality(const Plurality& a);
	~Plurality();
	unsigned int getCapacity();
	void deleteDubs();
	void pushBack(int);
	int& back();
	int popBack();
	void diet();
	void setSize(unsigned int);
	void setCapacity(unsigned int);
	Plurality& operator=(const Plurality&);
	unsigned int operator ()();
	int& operator[](int);
	Plurality operator+(const int);
	Plurality operator*(Plurality&);
	Plurality& operator--(int);
	Plurality& operator--();
	friend ostream& operator<<(ostream& out, Plurality& a);
	friend istream& operator>>(istream& in, Plurality& a);
private:
	unsigned int capacity; // размер массива
	unsigned int size; // НОМЕР самого последнего элемента
	int* data;
};