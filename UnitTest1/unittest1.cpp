#include "stdafx.h"
#include "CppUnitTest.h"
#include "Header.h"
#include "ТехПрог№1.cpp"
#include "Functions.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(InComplex)
		{		
			ifstream ReadFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\InComplex.txt");
			complex expected;
			expected.number1 = 5;
			type *actual;
			complex *temp;
			actual = (type*)InputComplex(ReadFile);
			actual->k = COMPLEX;
			temp = (complex*)actual;
			Assert::AreEqual(double(expected.number1), double(temp->number1));
		}
		TEST_METHOD(InShot)
		{
			ifstream ReadFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\InShot.txt");
			shot expected;
			expected.number1 = 156;
			type *actual;
			shot *temp;
			actual = (type*)InputShot(ReadFile);
			actual->k = SHOT;
			temp = (shot*)actual;
			Assert::AreEqual(double(expected.number1), double(temp->number1));
		}
		TEST_METHOD(InPolar)
		{
			ifstream ReadFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\InPolar.txt");
			polar expected;
			expected.radius = 6.2;
			type *actual;
			polar *temp;
			actual = (type*)InputPolar(ReadFile);
			actual->k = POLAR;
			temp = (polar*)actual;
			Assert::AreEqual(double(expected.radius), double(temp->radius));
		}
		TEST_METHOD(OutS)
		{
			ofstream WriteFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\expecSHOT.txt");
			shot temp;
			temp.number1 = 5;
			temp.number2 = 50;
			temp.metric = "см";
			OutSHOT(&temp, WriteFile);
			WriteFile.close();
			ifstream ReadFile1("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\factSHOT.txt");
			ifstream ReadFile2("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\expecSHOT.txt");
			string expected;
			getline(ReadFile1, expected, '\0');
			string actual;
			getline(ReadFile2, actual, '\0');
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(OutC)
		{
			ofstream WriteFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\expecCOM.txt");
			complex temp;
			temp.number1 = 5;
			temp.number2 = -4;
			temp.metric = "см";
			OutCOM(&temp, WriteFile);
			WriteFile.close();
			ifstream ReadFile1("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\factCOM.txt");
			ifstream ReadFile2("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\expecCOM.txt");
			string expected;
			getline(ReadFile1, expected, '\0');
			string actual;
			getline(ReadFile2, actual, '\0');
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(OutP)
		{
			ofstream WriteFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\expecPOL.txt");
			polar temp;
			temp.angle = 5;
			temp.radius = 5;
			temp.metric = "см";
			OutPOL(&temp, WriteFile);
			WriteFile.close();
			ifstream ReadFile1("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\factPOL.txt");
			ifstream ReadFile2("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\expecPOL.txt");
			string expected;
			getline(ReadFile1, expected, '\0');
			string actual;
			getline(ReadFile2, actual, '\0');
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(OutContainer)
		{
			ofstream WriteFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\OutConainer.txt");
			ifstream ReadFile1("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\input.txt");
			container c;
			Initialisation(c);
			In(ReadFile1, c);
			Out(c, WriteFile);
			WriteFile.close();
			ifstream ReadFile2("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\OutList.txt");
			ifstream ReadFile3("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\OutConainer.txt");
			string expected;
			getline(ReadFile2, expected, '\0');
			string actual;
			getline(ReadFile3, actual, '\0');
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestSort)
		{
			ofstream WriteFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\OutSorting.txt");
			ifstream ReadFile1("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\input.txt");
			container c;
			Initialisation(c);
			In(ReadFile1, c);
			Sorting(c);
			Out(c, WriteFile);
			WriteFile.close();
			ifstream ReadFile2("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\expecSorting.txt");
			ifstream ReadFile3("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\OutSorting.txt");
			string expected;
			getline(ReadFile2, expected, '\0');
			string actual;
			getline(ReadFile3, actual, '\0');
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(OutOShot)
		{
			ofstream WriteFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\FilterOut.txt");
			ifstream ReadFile1("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\input.txt");
			container c;
			Initialisation(c);
			In(ReadFile1, c);
			FiltredOut(c, WriteFile);
			WriteFile.close();
			ifstream ReadFile2("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\expecFilterOut.txt");
			ifstream ReadFile3("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\FilterOut.txt");
			string expected;
			getline(ReadFile2, expected, '\0');
			string actual;
			getline(ReadFile3, actual, '\0');
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestSravnenie)
		{
			ifstream ReadFile1("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\inputSravnenie.txt");
			bool actual;
			type *temp;
			temp = (type*)InputShot(ReadFile1);
			temp->k = SHOT;
			type *temp2;
			temp2 = (type*)InputShot(ReadFile1);
			temp2->k = SHOT;
			if (Sravnenie(temp) > Sravnenie(temp2))
				actual = true;
			bool expected = true;
			Assert::AreEqual(expected, actual);
		}
	};
}

/*TEST_METHOD(OutChoose)
{
ofstream WriteFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\OutChoose.txt");
type temp;
temp.k = SHOT;
OutT(&temp, WriteFile);
WriteFile.close();
ifstream ReadFile1("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\FactOutChoose.txt");
ifstream ReadFile2("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\OutChoose.txt");
string expected;
getline(ReadFile1, expected, '\0');
string actual;
getline(ReadFile2, actual, '\0');
Assert::AreEqual(expected, actual);*/

/*TEST_METHOD(InputType)
{
	ifstream ReadFile("C:\\Users\\Антоха\\Documents\\Visual Studio 2015\\Projects\\ТехПрога№1\\UnitTest1\\InputType.txt");
	type* actual = NULL;
	container c;
	c.current = NULL;
	c.len = 0;
	actual = InType(c.current, ReadFile);
	type expected;
	expected.k = SHOT;
	Assert::AreEqual(int(expected.k), int(actual->k));
}*/