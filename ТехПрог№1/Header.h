#pragma once
#include "iostream"
#include "fstream"
#include <string>

using namespace std;

enum key { COMPLEX, SHOT };
struct type
{
	type *next;
	key k; // ключ

};//

struct complex :type
{
	type *next;
	key k; // ключ

	int number1;
	int number2;
};

struct shot :type
{
	type *next;
	key k; // ключ

	int number1;
	int number2;
	string metric;
};

struct container
{
	int len;
	type *current;

};



void Initialisation(container &c);

void In(ifstream &ReadFile, container &c);

void Clear(container &c);

void Out(container &c, ofstream &WriteFile);


// Общий ввод
type * InType(type *current, ifstream &ReadFile);

// Общий вывод
void OutT(type *s, ofstream &WriteFile);


// Ввод дробного числа
shot * InputShot(ifstream &ReadFile);

// Вывод дробного числа
void OutSHOT(shot *m, ofstream &WriteFile);

// Ввод комплексного числа
complex * InputComplex(ifstream &ReadFile);

//Вывод комплексного числа
void OutCOM(complex *d, ofstream &WriteFile);

int NOD(int a, int b);