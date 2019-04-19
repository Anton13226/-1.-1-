#pragma once
#include "iostream"
#include "fstream"
#include <string>

using namespace std;

enum key { COMPLEX, SHOT, POLAR };
struct type
{
	type *next;
	key k; // ключ

};//

struct complex :type
{
	type *next;
	key k; // ключ

	double number1;
	double number2;
	string metric;
};

struct shot :type
{
	type *next;
	key k; // ключ

	double number1;
	double number2;
	string metric;
};

struct polar :type
{
	type *next;
	key k; // ключ

	double radius;
	double angle;
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
void OutSHOT(shot *S, ofstream &WriteFile);

// Ввод комплексного числа
complex * InputComplex(ifstream &ReadFile);

//Вывод комплексного числа
void OutCOM(complex *C, ofstream &WriteFile);

polar * InputPolar(ifstream &ReadFile);

//Вывод комплексного числа
void OutPOL(polar *P, ofstream &WriteFile);

int NOD(int a, int b);