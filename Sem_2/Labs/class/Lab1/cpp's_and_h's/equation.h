#pragma once
class equation
{
	bool isNumber(std::string);
public:
	double first;
	double second;
	void Init(double, double);
	void Init(std::string, std::string);
	void Read();
	void Show();
	double Function(double);
};