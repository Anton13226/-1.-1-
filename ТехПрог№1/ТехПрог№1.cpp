// ТехПрог№1.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Header.h"



int main()
{
	ifstream ReadFile("input.txt");
	ofstream WriteFile("output.txt");
	cout << "Start" << endl;
	container c;
	Initialisation(c);
	In(ReadFile, c);
	Sorting(c);
	Out(c, WriteFile);
	Clear(c);
	cout << "Stop" << endl;
	return 0;
}

