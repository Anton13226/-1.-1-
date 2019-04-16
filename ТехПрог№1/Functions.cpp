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
		temp->next = temp; // ��������� �� ������ ����
	}

	else
	{
		help = current->next; // ���������� ��������� �� ��������� �������
		current->next = temp; // ���������� ���� ��������� �� �����������
		temp->next = help; // ��������� ���� ��������� �� ��������� �������
	}
	return temp;
}


// ���� ������������ �����
complex * InputComplex(ifstream &ReadFile)
{
	complex *d;
	d = new complex;
	ReadFile >> d->number1;
	ReadFile >> d->number2;
	return(d);
}

//���� �������� �����
shot * InputShot(ifstream &ReadFile)
{
	shot *m;
	m = new shot;
	ReadFile >> m->number1;
	ReadFile >> m->number2;
	return(m);
}

// ����� ������� ���������
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



// ����� ������� ���������
void OutSHOT(shot *m, ofstream &WriteFile)
{
	int Nod;
	WriteFile << "�����:   " << "||";
	Nod = NOD(m->number1, m->number2);
	WriteFile << m->number1 / Nod << "/" << m->number2 / Nod << endl;
}




//����� ����������� ���������
void OutCOM(complex *d, ofstream &WriteFile)
{
	WriteFile << "����������� �����:    Z=" << d->number1 ;
	if (d->number2 > 0)
		WriteFile << "+" << d->number2 << "i" << endl;
	else
		WriteFile << d->number2 << "i" << endl;
}


float Count(shot * m)
{
	double Sort = 0;
	Sort = round((m->number1 / m->number2) * 100) / 100;
	return Sort;
}

float Count(complex * d)
{
	double Sort = 0;
	Sort = round(sqrt(d->number1*d->number1 + d->number2 * d->number2) * 100) / 100;
	return Sort;
}

/*void Sorting(container &c)
{
		for (int i = 0; i < c.len - 1; i++)
		{
			for (int j = 0; j < c.len - 1; j++)
			{
				if ((type*)Count(c.current) > (type*)Count(c.current->next))
				{
					Node *prediudushiy = head;

					while (prediudushiy->next != head)
						prediudushiy = prediudushiy->next;

					Node *next1 = head->next;
					Node *next2 = head->next->next;

					next1->next = head;
					head->next = next2;
					prediudushiy->next = next1;
					head = next1;
				}
				head = head->next;
			}
			head = head->next;
		}
}
*/

int NOD(int a, int b)
{
	while ((a && b) != 0)
		if (a >= b)
			a %= b;
		else
			b %= a;
	return a | b;
}