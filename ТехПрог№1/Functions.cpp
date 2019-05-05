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
type *InType(container &c, ifstream &ReadFile)
{
	/*string chek;
	ReadFile >> chek;

	if (chek == "\0")
	{
		return false;
	}
	if (chek.length()  > 1)
	{
		ReadFile.get();
		getline(ReadFile, chek, '\n');
		return NULL;
	}
	if (!isdigit(int(unsigned char(chek.front()))))
	{
		ReadFile.get();
		getline(ReadFile, chek, '\n');
		return NULL;
	}
	int k=stoull(chek);
	*/
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
	case 3:
		temp = (type*)InputPolar(ReadFile);
		temp->k = POLAR;
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

/*
////////////////////////////////////////////////////////////////////
Transport* In(ifstream &ifst)
{
	Transport *sp;
	string temp;
	int fuel_consumption;
	int power;
	ifst >> temp;
	if (temp == "\0")
	{
		return false;
	}
	if (temp.length()  > 1)
	{
		ifst.get();
		getline(ifst, temp, '\n');
		return NULL;
	}
	if (!isdigit(int(unsigned char(temp.front()))))
	{
		ifst.get();
		getline(ifst, temp, '\n');
		return NULL;
	}
	int k = stoull(temp);
	ifst >> temp;
	if (temp == "\0")
	{
		return false;
	}
	if (temp.length() > 4)
	{
		getline(ifst, temp, '\n');
		return NULL;
	}
	for (auto iter = temp.begin(); iter != temp.end(); ++iter)
	{
		if (!isdigit(int(unsigned char(*iter))))
		{
			getline(ifst, temp, '\n');
			return NULL;
		}
	}
	power = stoul(temp);

	ifst >> temp;
	if (temp == "\0")
	{
		return false;
	}
	for (auto iter = temp.begin(); iter != temp.end(); ++iter)
	{
		if (!isdigit(int(unsigned char(*iter))))
		{
			getline(ifst, temp, '\n');
			return NULL;
		}
	}
	if (temp.length() > 3)
	{
		getline(ifst, temp, '\n');
		return NULL;
	}
	fuel_consumption = stoull(temp);
	switch (k) {
	case 1:
		sp = (Transport*)InDataForTruck(ifst);
		if (!sp)
		{
			return NULL;
		}
		else
		{
			sp->k = TRUCK;
			sp->power = power;
			sp->fuel_consumption = fuel_consumption;
			return sp;
		}
	case 2:

		sp = (Transport*)InDataForBus(ifst);
		if (!sp)
		{
			return NULL;
		}
		else
		{
			sp->k = BUS;
			sp->power = power;
			sp->fuel_consumption = fuel_consumption;
			return sp;
		}

	case 3:

		sp = (Transport*)InDataForPassengerCar(ifst);
		if (!sp)
		{
			return NULL;
		}
		else
		{
			sp->k = PASSENGER_CAR;
			sp->power = power;
			sp->fuel_consumption = fuel_consumption;
			return sp;
		}
	default:
		getline(ifst, temp, '\n');
		return NULL;
	}
}
///////////////////////////////////////////////////////////////////////
*/
complex * InputComplex(ifstream &ReadFile)
{
	complex *C;
	C = new complex;
	ReadFile >> C->number1;
	ReadFile >> C->number2;
	getline(ReadFile, C->metric, '\n');
	return(C);
}

shot * InputShot(ifstream &ReadFile)
{
	shot *S;
	S = new shot;
	ReadFile >> S->number1;
	ReadFile >> S->number2;
	getline(ReadFile, S->metric, '\n');
	return(S);
}

polar * InputPolar(ifstream & ReadFile)
{
	polar *P;
	P = new polar;
	ReadFile >> P->radius;
	if (P->radius < 0)
		P->radius = 0 - P->radius;
	ReadFile >> P->angle;
	if ((P->angle < 0) || (P->angle > 6.2))
		P->radius = 6.2;
	getline(ReadFile, P->metric, '\n');
	return(P);
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