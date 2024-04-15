/*
👍🏼 - Он убирает кракозябры.
Класс-контейнер МНОЖЕСТВО с элементами типа int.
Реализовать операции:
[]     – доступа по индексу;
int()  – определение размера вектора;
*      – пересечение множеств;
--     - переход к предыдущему элементу ( с помощью класса-итератора).
*/
#pragma once
using namespace std;
class Iterator
{
	friend class Plurality;
	int* elem;
public:
	Iterator()
	{
		elem = 0;
	}
	Iterator(int* e)
	{
		elem = e;
	}
	Iterator(const Iterator& it)
	{
		elem = it.elem;
	}
	bool operator==(const Iterator& it)
	{
		return elem == it.elem;
	}
	bool operator!=(const Iterator& it)
	{
		return elem != it.elem;
	}
	Iterator operator++();
	Iterator operator--();
	Iterator operator++(int);
	Iterator operator--(int);
	int& operator *() const
	{
		return *elem;
	}
};
class Plurality
{
public:
	Plurality(int s, int k = 0);
	//конструктор с параметрами
	Plurality(const Plurality& a);
	//деструктор
	~Plurality();
	Iterator first()
	{
		return beg;
	}
	Iterator last()
	{
		return end;
	}
	void deleteDubs();
	Plurality& operator=(const Plurality&);
	int operator ()();
	int& operator[](int);
	Plurality operator+(const int);
	Plurality operator*(Plurality&);
	friend ostream& operator<<(ostream& out, Plurality& a);
	friend istream& operator>>(istream& in, Plurality& a);
private:
	int size;
	int* data;
	Iterator beg;
	Iterator end;
};