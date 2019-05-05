#pragma once
#include "iostream"
#include <fstream>
#include <string>

using namespace std;

enum key { COMPLEX, SHOT, POLAR };
struct type
{
	type *next;
	key k; // ����

};//

struct complex :type
{
	type *next;
	key k; // ����

	double number1;
	double number2;
	string metric;
};

struct shot :type
{
	type *next;
	key k; // ����

	double number1;
	double number2;
	string metric;
};

struct polar :type
{
	type *next;
	key k; // ����

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

float Count(shot *S);

float Count(complex *C);

float Count(polar *P);

void Sorting(container &c);

float Sravnenie(type *s);


void FiltredOut(container &c, ofstream &WriteFile);

void SwitchOut(type *s, ofstream &WriteFile);



// ����� ����
bool InType(container &c, ifstream &ReadFile);

// ����� �����
void OutT(type *s, ofstream &WriteFile);


// ���� �������� �����
bool InputShot(shot *temp, ifstream &ReadFile);

// ����� �������� �����
void OutSHOT(shot *S, ofstream &WriteFile);

// ���� ������������ �����
bool InputComplex(complex *temp,ifstream &ReadFile);

//����� ������������ �����
void OutCOM(complex *C, ofstream &WriteFile);

bool InputPolar(polar *temp, ifstream &ReadFile);

//����� ������������ �����
void OutPOL(polar *P, ofstream &WriteFile);

int NOD(int a, int b);