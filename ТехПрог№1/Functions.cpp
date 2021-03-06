#include "stdafx.h"
#include "Header.h"


///////////////////________���������________////////////////////
// ������������� ����������
void Initialisation(container &c)
{
	c.current = NULL;
	c.len = 0;
}

// ���� ����������� ����������
void In(ifstream &ReadFile, container &c)
{
	while (!ReadFile.eof())
	{
		if ((c.current = InType(c.current, ReadFile)) != 0)
		{
			c.len++;
		}
	}
}

// ����� ����������� ����������
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

// ������� ���������� �� ���������
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

///////////////////________������___________////////////////////
//����� ����
type *InType(type *current, ifstream &ReadFile)
{
	type *temp, *help;
	int k;
	ReadFile >> k;
	switch (k)
	{
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
		temp->next = temp; // ��������� �� ������ ����
	else
	{
		help = current->next; // ���������� ��������� �� ��������� �������
		current->next = temp; // ���������� ���� ��������� �� �����������
		temp->next = help; // ��������� ���� ��������� �� ��������� �������
	}
	return temp;
}

// ����� ������� ���������
void OutT(type *s, ofstream &WriteFile)
{
	switch (s->k) 
	{
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

complex * InputComplex(ifstream &ReadFile)
{
	complex *C;
	C = new complex;
	ReadFile >> C->number1;
	ReadFile >> C->number2;
	getline(ReadFile, C->metric, ' ');
	return(C);
}

void OutCOM(complex *C, ofstream &WriteFile)
{
	WriteFile << "����������� �����:    Z=" << C->number1;
	if (C->number2 > 0)
		WriteFile << "+" << C->number2 << "i  ||  �.� " << C->metric << endl;
	else
		WriteFile << C->number2 << "i  ||  �.� " << C->metric << endl;
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
	getline(ReadFile, S->metric, ' ');
	return(S);
}

void OutSHOT(shot *S, ofstream &WriteFile)
{
	int Nod;
	WriteFile << "�����:   ";
	Nod = NOD(S->number1, S->number2);
	WriteFile << S->number1 / Nod << "/" << S->number2 / Nod << "  ||  �.� " << S->metric << endl;
}

float Count(shot * S)
{
	double Sort = 0;
	Sort = round((S->number1 / S->number2) * 100) / 100;
	return Sort;
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
	getline(ReadFile, P->metric, ' ');
	return(P);
}

void OutPOL(polar * P, ofstream & WriteFile)
{
	WriteFile << "�������� ����������:   ";
	WriteFile << "(" << P->radius << ";" << P->angle << ")  ||  �.� " << P->metric << endl;
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
	switch (s->k) 
	{
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
	WriteFile << endl << "������ �����" << endl;
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