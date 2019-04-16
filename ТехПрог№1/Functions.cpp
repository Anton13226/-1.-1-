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


// Ввод комплексного числа
complex * InputComplex(ifstream &ReadFile)
{
	complex *d;
	d = new complex;
	ReadFile >> d->number1;
	ReadFile >> d->number2;
	return(d);
}

//Ввод дробного числа
shot * InputShot(ifstream &ReadFile)
{
	shot *m;
	m = new shot;
	ReadFile >> m->number1;
	ReadFile >> m->number2;
	return(m);
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
		WriteFile << "Incorrect figure!" << endl;
	}
}



// Вывод дробной структуры
void OutSHOT(shot *m, ofstream &WriteFile)
{
	int Nod;
	WriteFile << "Дробь:   ";
	Nod = NOD(m->number1, m->number2);
	WriteFile << m->number1 / Nod << "/" << m->number2 / Nod << endl;
}




//Вывод комплексной структуры
void OutCOM(complex *d, ofstream &WriteFile)
{
	WriteFile << "Комплексное число:    Z=" << d->number1 ;
	if (d->number2 > 0)
		WriteFile << "+" << d->number2 << "i" << endl;
	else
		WriteFile << d->number2 << "i" << endl;
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