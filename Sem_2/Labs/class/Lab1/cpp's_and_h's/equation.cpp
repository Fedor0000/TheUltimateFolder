#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "equation.h"
using namespace std;
bool equation::isNumber(const string str)
{
    double val;
    istringstream iss(str);
    iss >> noskipws >> val;
    return iss.eof() && !iss.fail();
}
void equation::Init(double F, double S)
{
    first = F;
    second = S;
}
void equation::Init(string F, string S)
{
    cout << "According to you " << F << " and " << S << " - is a numbers?";
    exit(1);
}
void equation::Read()
{
    string tmp;
    cout << "Enter number А: ";
    cin >> tmp;
    if (isNumber(tmp))
    {
        first = stod(tmp);
    }
    else
    {
        cout << "According to you " << tmp << " - is a number?";
        exit(1);
    }
    cout << "Enter number B: ";
    cin >> tmp;
    if (isNumber(tmp))
    {
        second = stod(tmp);
    }
    else
    {
        cout << "According to you " << tmp << " - is a number?";
        exit(1);
    }
}
void equation::Show()
{
    cout << "А = " << first;
    cout << "\nB = " << second << endl;
}
double equation::Function(double x)
{
    return (first*x+second);
}