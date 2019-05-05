// ТехПрог№1.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Header.h"



int main()
{
	ifstream ReadFile("input.txt");
	ofstream WriteFile("output.txt");
	if (!ReadFile.is_open())
	{
		cout << "No input file found or could not open!" << endl;
		system("pause");
		return 1;
	}
	cout << "Start" << endl;
	container c;
	Initialisation(c);
	In(ReadFile, c);
	Out(c, WriteFile);
	WriteFile << "================================================" << endl;
	Sorting(c);
	Out(c, WriteFile);
	FiltredOut(c, WriteFile);
	Clear(c);
	cout << "Stop" << endl;
	return 0;
}

