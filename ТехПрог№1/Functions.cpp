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
	if (!ReadFile.eof())
	{
		c.current = InType(c.current, ReadFile);
		c.len++;
	}

	while (!ReadFile.eof())
	{
		if ((c.current = InType(c.current, ReadFile)) != 0)
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
type *InType(type *current, ifstream &ReadFile)
{
	type *temp, *help;
	int k;
	ReadFile >> k;
	switch (k) {
	case 1:
		temp = (type*)InputComplex(ReadFile);
		temp->k = COMPLEX;
		break;
	case 2:
		temp = (type*)InputShot(ReadFile);
		temp->k = SHOT;
		break;
	default:
		return 0;
	}

	if (current == NULL)
	{
		temp->next = temp; // указатель на самого себя
	}

	else
	{
		help = current->next; // сохранение указателя на следующий элемент
		current->next = temp; // предыдущий узел указывает на создаваемый
		temp->next = help; // созданный узел указывает на следующий элемент
	}



	return temp;
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
	default:
		break;
	}
}

complex * InputComplex(ifstream &ReadFile)
{
	complex *C;
	C = new complex;
	ReadFile >> C->number1;
	ReadFile >> C->number2;
	ReadFile >> C->metric;
	return(C);
}

void OutCOM(complex *C, ofstream &WriteFile)
{
	WriteFile << "Комплексное число:    Z=" << C->number1;
	if (C->number2 > 0)
		WriteFile << "+" << C->number2 << "i  ||  Е.И " << C->metric << endl;
	else
		WriteFile << C->number2 << "i  ||  Е.И " << C->metric << endl;
}

float Count(complex * C)
{
	double Sort = 0;
	Sort = round(sqrt(C->number1*C->number1 + C->number2 * C->number2) * 100) / 100;
	return Sort;
}

shot * InputShot(ifstream &ReadFile)
{
	shot *S;
	S = new shot;
	ReadFile >> S->number1;
	ReadFile >> S->number2;
	ReadFile >> S->metric;
	return(S);
}

void OutSHOT(shot *S, ofstream &WriteFile)
{
	int Nod;
	WriteFile << "Дробь:   ";
	Nod = NOD(S->number1, S->number2);
	WriteFile << S->number1 / Nod << "/" << S->number2 / Nod << "  ||  Е.И " << S->metric << endl;
}

float Count(shot * S)
{
	double Sort = 0;
	Sort = round((S->number1 / S->number2) * 100) / 100;
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

void Multimethod(container &c, ofstream &WriteFile)
{
	WriteFile << "Multimethod." << endl;
	WriteFile << "================================================" << endl;
	type *First_point = c.current;
	type *Second_point = First_point->next;
	for (int i = 0; i < c.len - 1; i++)
	{
		for (int j = i + 1; j < c.len; j++)
		{
			switch (First_point->k)
			{
			case COMPLEX:
				switch (Second_point->k)
				{
				case COMPLEX:
					WriteFile << "COMPLEX and COMPLEX." << endl;
					break;
				case SHOT:
					WriteFile << "COMPLEX and SHOT." << endl;
					break;
				default:
					WriteFile << "Unknown type" << endl;
				}
				break;
			case SHOT:
				switch (Second_point->k)
				{
				case COMPLEX:
					WriteFile << "SHOT and COMPLEX." << endl;
					break;
				case SHOT:
					WriteFile << "SHOT and SHOT." << endl;
					break;
				default:
					WriteFile << "Unknown type" << endl;
					break;
				}
				break;
			default:
				WriteFile << "Unknown type" << endl;
				break;
			}
			OutT(First_point, WriteFile);
			OutT(Second_point, WriteFile);
			WriteFile << endl;
			Second_point = Second_point->next;
		}
		First_point = First_point->next;
		Second_point = First_point->next;
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