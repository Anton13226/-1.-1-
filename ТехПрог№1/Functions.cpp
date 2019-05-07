#include "stdafx.h"
#include "Header.h"


///////////////////________КОНТЕЙНЕР________////////////////////
// Инициализация контейнера
void Initialisation(container &c)
{
	c.current = NULL;
	c.len = 0;
}

// Ввод содержимого контейнера
void In(ifstream &ReadFile, container &c)
{
	/*if (!ReadFile.eof())
	{
		c.current = InType(c, ReadFile);
		c.len++;
	}
	*/
	while (!ReadFile.eof())
	{
		if (InType(c, ReadFile))
		{
			c.len++;
		}
	}
}


// Вывод содержимого контейнера
void Out(container &c, ofstream &WriteFile)
{
	c.current = c.current->next;

	for (int i = 0; i < c.len; i++)
	{
		WriteFile << i + 1 << ": ";
		if (c.len > 0)
		{
			OutT(c.current, WriteFile);
			c.current = c.current->next;
		}
	}
}

// Очистка контейнера от элементов
void Clear(container &c)
{
	while (c.len > 0)
	{
		if (c.len == 1)
		{
			type *temp = c.current;
			c.current = nullptr;
			delete(temp);
			c.len = c.len - 1;
			break;
		}
		type *temp;
		temp = c.current->next;
		while (temp->next != c.current)
			temp = temp->next;

		temp->next = c.current->next;
		free(c.current);
		c.current = temp;
		c.len = c.len - 1;
	}
}



///////////////////________СПИСОК___________////////////////////
//Общий ввод
bool InType(container &c, ifstream &ReadFile)
{
	string chek;
	ReadFile >> chek;

	if (chek == "\0")
	{
		return false;
	}

	if (chek.length()  > 1)
	{
		ReadFile.get();
		getline(ReadFile, chek, '\n');
		return false;
	}

	if (!isdigit(int(unsigned char(chek.front()))))
	{
		ReadFile.get();
		getline(ReadFile, chek, '\n');
		return false;
	}

	int k = stoul(chek);
	type *temp, *help;

//	int k;
//	ReadFile >> k;
	switch (k) {
	case 1:
		temp = new complex;
		if (!InputComplex((complex*)temp,ReadFile))
			return false;
		temp->k = COMPLEX;
		break;
	case 2:
		temp = new shot;
		if (!InputShot((shot*)temp, ReadFile))
			return false;
		temp->k = SHOT;
		break;
	case 3:
		temp = new polar;
		if (!InputPolar((polar*)temp, ReadFile))
			return false;
		temp->k = POLAR;
		break;

	default:
		return 0;
	}

	if (c.current == NULL)
	{
		c.current = temp;
		temp->next = temp; // указатель на самого себя
	}

	else
	{
		help = c.current->next; // сохранение указателя на следующий элемент
		c.current->next = temp; // предыдущий узел указывает на создаваемый
		temp->next = help; // созданный узел указывает на следующий элемент
	}
	return true;
}


bool InputComplex(complex *temp,ifstream &ReadFile)
{
	//complex *C;
	//C = new complex;

	string chek;
	string chek2;
	bool chekMinus = false;
	ReadFile >> chek;
	if (chek == "\0")
	{
		return false;
	}

	if (chek[0] == '-')
	{
		char *buff = new char[chek.size() - 1];
		for (int i = 1; i < chek.size(); i++)
		{
			buff[i - 1] = chek[i];
		}
		buff[chek.size() - 1] = '\0';
		chek = buff;
		chekMinus = true;
	}

	for (int i = 0; i < chek.size(); i++)
	{
		if (!isdigit(double(unsigned char(chek[i]))))
		{
			ReadFile.get();
			getline(ReadFile, chek, '\n');
			return false;
		}
	}
	temp->number1 = stoul(chek);
	if (chekMinus)
	{
		temp->number1 = (-1)*temp->number1;
	}
	ReadFile >> chek2;
	if (chek2 == "\0")
	{
		return false;
	}
	if (chek2[0] == '-')
	{
		char *buff = new char[chek2.size() - 1];
		for (int i = 1; i < chek2.size(); i++)
		{
			buff[i - 1] = chek2[i];
		}
		buff[chek2.size() - 1] = '\0';
		chek2 = buff;
		chekMinus = true;
	}

	for (int i = 0; i < chek2.size(); i++)
	{
		if (!isdigit(double(unsigned char(chek2[i]))))
		{
			ReadFile.get();
			getline(ReadFile, chek2, '\n');
			return false;
		}
	}
	temp->number2 = stoul(chek2);
	if (chekMinus)
	{
		temp->number2 = (-1)*temp->number2;
	}

	getline(ReadFile, temp->metric, '\n');
	return true;
}

bool InputShot(shot *temp, ifstream &ReadFile)
{
	string chek;
	string chek2;
	bool chekMinus = false;
	ReadFile >> chek;
	if (chek == "\0")
	{
		return false;
	}

	if (chek[0] == '-')
	{
		char *buff = new char[chek.size() - 1];
		for (int i = 1; i < chek.size(); i++)
		{
			buff[i - 1] = chek[i];
		}
		buff[chek.size() - 1] = '\0';
		chek = buff;
		chekMinus = true;
	}

	for (int i = 0; i < chek.size(); i++)
	{
		if (!isdigit(double(unsigned char(chek[i]))))
		{
			ReadFile.get();
			getline(ReadFile, chek, '\n');
			return false;
		}
	}
	temp->number1 = stoul(chek);
	if (chekMinus)
	{
		temp->number1 = (-1)*temp->number1;
	}
	ReadFile >> chek2;
	if (chek2 == "\0")
	{
		return false;
	}
	if (chek2[0] == '-')
	{
		char *buff = new char[chek2.size() - 1];
		for (int i = 1; i < chek2.size(); i++)
		{
			buff[i - 1] = chek2[i];
		}
		buff[chek2.size() - 1] = '\0';
		chek2 = buff;
		chekMinus = true;
	}

	for (int i = 0; i < chek2.size(); i++)
	{
		if (!isdigit(double(unsigned char(chek2[i]))))
		{
			ReadFile.get();
			getline(ReadFile, chek2, '\n');
			return false;
		}
	}
	temp->number2 = stoul(chek2);
	if (chekMinus)
	{
		temp->number2 = (-1)*temp->number2;
	}

	getline(ReadFile, temp->metric, '\n');
	return true;
}

bool InputPolar(polar *temp, ifstream & ReadFile)
{
	string chek;
	string chek2;
	ReadFile >> chek;
	if (chek == "\0")
	{
		return false;
	}

	if (chek[0] == '-')
	{
		return false;
	}

	for (int i = 0; i < chek.size(); i++)
	{
		if (!isdigit(double(unsigned char(chek[i]))))
		{
			ReadFile.get();
			getline(ReadFile, chek, '\n');
			return false;
		}
	}
	temp->radius = stoul(chek);
	ReadFile >> chek2;
	if (chek2 == "\0")
	{
		return false;
	}
	if (chek2[0] == '-')
	{
		return false;
	}

	for (int i = 0; i < chek2.size(); i++)
	{
		if (!isdigit(double(unsigned char(chek2[i]))))
		{
			ReadFile.get();
			getline(ReadFile, chek2, '\n');
			return false;
		}
	}
	temp->angle = stoul(chek2);
	getline(ReadFile, temp->metric, '\n');
	return true;
}



// Вывод текущей структуры
void OutT(type *s, ofstream &WriteFile)
{

	switch (s->k) {
	case COMPLEX:

		OutCOM((complex*)s, WriteFile);
		break;

	case SHOT:

		OutSHOT((shot*)s, WriteFile);
		break;
	case POLAR:
		OutPOL((polar*)s, WriteFile);
		break;

	default:
		break;
	}
}



void OutSHOT(shot *S, ofstream &WriteFile)
{
	int Nod;
	WriteFile << "Дробь:   ";
	Nod = NOD(S->number1, S->number2);
	WriteFile << S->number1 / Nod << "/" << S->number2 / Nod << "  ||  Е.И " << S->metric << endl;
}

void OutCOM(complex *C, ofstream &WriteFile)
{
	WriteFile << "Комплексное число:    Z=" << C->number1 ;
	if (C->number2 > 0)
		WriteFile << "+" << C->number2 << "i  ||  Е.И " << C->metric << endl;
	else
		WriteFile << C->number2 << "i  ||  Е.И " << C->metric << endl;
}

void OutPOL(polar * P, ofstream & WriteFile)
{
	WriteFile << "Полярные координаты:   ";
	WriteFile << "(" << P->radius << ";" << P->angle << ")  ||  Е.И " << P->metric << endl;
}


float Count(shot * S)
{
	double Sort = 0;
	Sort = round((S->number1 / S->number2) * 100) / 100;
	return Sort;
}

float Count(complex * C)
{
	double Sort = 0;
	Sort = round(sqrt(C->number1*C->number1 + C->number2 * C->number2) * 100) / 100;
	return Sort;
}

float Count(polar * P)
{
	double Sort = 0;
	Sort = P->angle;
	return Sort;
}


float Sravnenie(type *s)
{
	float temp;
	switch (s->k) {
	case COMPLEX:

		temp = Count((complex*)s);
		return temp;

	case SHOT:

		temp = Count((shot*) s);
		return temp;
	case POLAR:

		temp = Count((polar*)s);
		return temp;
	}
}

void Sorting(container &c)
{
		for (int i = 0; i < c.len - 1; i++)
		{
			for (int j = 0; j < c.len - 1; j++)
			{
				if (Sravnenie(c.current) > Sravnenie(c.current->next))
				{
					type *prediudushiy = c.current;

					while (prediudushiy->next != c.current)
						prediudushiy = prediudushiy->next;

					type *next1 = c.current->next;
					type *next2 = next1->next;

					next1->next = c.current;
					c.current->next = next2;
					prediudushiy->next = next1;
					c.current = next1;
				}
				c.current = c.current->next;
			}
			c.current = c.current->next;
		}
}

void SwitchOut(type *s, ofstream &WriteFile)
{
	switch (s->k) {
	case COMPLEX:

		break;

	case SHOT:

		OutSHOT((shot*)s, WriteFile);
		break;
	case POLAR:

		break;

	default:
		break;
	}
}

void FiltredOut(container &c, ofstream &WriteFile)
{
	WriteFile << endl << "Только дроби" << endl;
	for (int i = 0; i < c.len; i++)
	{
		if (c.len > 0)
		{
			SwitchOut(c.current, WriteFile);
			c.current = c.current->next;
		}
	}
}





int NOD(int a, int b)
{
	while ((a && b) != 0)
		if (a >= b)
			a %= b;
		else
			b %= a;
	return a | b;
}