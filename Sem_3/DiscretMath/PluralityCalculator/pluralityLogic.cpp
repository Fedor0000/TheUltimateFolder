#include "PluralityLogic.h"

Plurality PluralityLogic::intersection(Plurality a, Plurality b)
{
    Plurality result;
    for (uint64_t i = 0; i < a.elements.size(); i++)
    {
        for (uint64_t j = 0; j < b.elements.size(); j++)
        {
            if (a.elements[i] == b.elements[j]) // просто отправляем в результат все, что одинаковое
            {
                result.elements.push_back(a.elements[i]);
                break;
            }
        }
    }
    return result;
}

Plurality PluralityLogic::merger(Plurality a, Plurality b)
{
    Plurality result;
    result.elements = a.elements; // отправляем в результат все из первого множества
    for (uint64_t i = 0; i < b.elements.size(); i++) // идем по всем элементам второго множества
    {
        result.elements.push_back(b.elements[i]);
    }
    result.deleteDubs();
    result.sorter(); // результат мог стать неотсортированным, исправляем
    return result;
}

Plurality PluralityLogic::minus(Plurality a, Plurality b)
{
    Plurality result;
    if (a.elements.size() == 0) return result;
    if (b.elements.size() == 0)
    {
        result = a;
        return a;
    }
    for (uint64_t i = 0; i < a.elements.size(); i++)
    {
        for (uint64_t j = 0; j < b.elements.size(); j++)
        {
            if (a.elements[i] == b.elements[j]) // просто отправляем в результат все, что НЕ одинаковое
            {
                break; // если равны, то идем к следующему элементу а
            }

            if (j == (b.elements.size()-1)) // если дошли до конца и ничего не совпало, то пушим в результат
            {
                result.elements.push_back(a.elements[i]);
            }
        }
    }
    return result;
}

Plurality PluralityLogic::symmetricalMinus(Plurality a, Plurality b) // симметрическая разность
{
    Plurality result;
    result = merger(a, b); // сливаем
    result = minus(result, intersection(a, b)); // вычитаем пересечение
    result.sorter(); // результат мог стать неотсортированным, исправляем
    return result;
}

Plurality PluralityLogic::addToUniversum(Plurality a) // дополнение до универсума
{
    Plurality result;
    for (int64_t i = uni.left; i <= uni.right; i++) result.elements.push_back(i); // весь универсум вливаем в результат
    result = minus(result, a); // вычитаем а
    return result;
}

void PluralityLogic::addPlurality(QString name) // добавить пустое множество с указанным именем
{
    for (uint64_t i = 0; i < Pluralities.size(); i++) // если уже есть такое имя, то выходим
    {
        if (Pluralities[i].name == name)
        {
            return;
        }
    }
    Plurality newP;
    newP.name = name;
    Pluralities.push_back(newP);
}

void PluralityLogic::delPluralityByName(QString name) // удалить множество по имени
{
    for (uint64_t i = 0; i < Pluralities.size(); i++)
    {
        if (Pluralities[i].name == name)
        {
            Pluralities.erase(Pluralities.begin()+i);
        }
    }
}
