#ifndef PLURALITYLOGIC_H
#define PLURALITYLOGIC_H

#include <QString>
#include <vector>

struct Universum // Универсум
{
    int64_t left = 0; // левая граница
    int64_t right = 0; // правая граница
};

struct Plurality // Множество
{
    std::vector<int64_t> elements; // вектор с элементами множества
    QString name; // название множества
    void deleteDubs()
    {
        if (elements.empty()) return;
        std::vector<int> biloUzhe;
        biloUzhe.push_back(elements[0]);
        for (uint64_t i = 1; i < elements.size(); i++)
        {
            bool yest = false;
            for (uint64_t j = 0; j < biloUzhe.size(); j++)
            {
                if (elements[i] == biloUzhe[j])
                {
                    yest = true;
                    break;
                }
            }
            if (!yest) biloUzhe.push_back(elements[i]);
        }
        elements.clear();
        for (uint64_t i = 0; i < biloUzhe.size(); i++) elements.push_back(biloUzhe[i]);
    }
    void sorter()
    {
        if (elements.empty()) return;
        sort(elements.begin(), elements.end());
    }
    Plurality& operator=(const Plurality& a) // учим его приравниванию
    {
        if (this == &a) return *this;
        name = a.name;
        elements = a.elements;
        return *this;
    }
};

class PluralityLogic // логика работы с множествами
{
public:
    Universum uni;
    std::vector<Plurality> Pluralities;

    Plurality intersection(Plurality, Plurality); // пересечение, возвращает результат пересечения а и б
    Plurality merger(Plurality, Plurality); // объединение, возвращает результат объединения а и б
    Plurality minus(Plurality, Plurality); // возвращает результат вычитания а - б
    Plurality symmetricalMinus(Plurality, Plurality); // возвращает результат вычитания а треугольник б
    Plurality addToUniversum(Plurality); // возвращает результат дополнения а до универсума
    void addPlurality(QString);
    void delPluralityByName(QString);
};

#endif // PLURALITYLOGIC_H
