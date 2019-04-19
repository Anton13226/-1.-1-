#pragma once
#include "iostream"
#include "fstream"
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

	int number1;
	int number2;
};

struct shot :type
{
	type *next;
	key k; // ����

	int number1;
	int number2;
	string metric;
};

struct polar :type
{
	type *next;
	key k; // ����

	int radius;
	float angle;
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


// ����� ����
type * InType(type *current, ifstream &ReadFile);

// ����� �����
void OutT(type *s, ofstream &WriteFile);


// ���� �������� �����
shot * InputShot(ifstream &ReadFile);

// ����� �������� �����
void OutSHOT(shot *S, ofstream &WriteFile);

// ���� ������������ �����
complex * InputComplex(ifstream &ReadFile);

//����� ������������ �����
void OutCOM(complex *C, ofstream &WriteFile);

polar * InputPolar(ifstream &ReadFile);

//����� ������������ �����
void OutPOL(polar *P, ofstream &WriteFile);

int NOD(int a, int b);