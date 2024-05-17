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
