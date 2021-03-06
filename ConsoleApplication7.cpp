// ConsoleApplication7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "stack"
#include <queue>
#include <cctype>

using namespace std;

const int SIZE = 50;   // максимальний розмір уведеного рядка

int prior(char a);
queue<char> polish(char s[]);     //черга виконання
float result(queue<char> x);     // виводимо результат

int main()
{
	char *String = new char[SIZE];
	cin.getline(String, SIZE);
	cout << result(polish(String)) << endl;
	return 0;
}

int prior(char a) //розставляємо пріоритети операцій
{
	switch (a)
	{
	case '^':
		return 4;
	case '*':
	case '/':
		return 3;

	case '-':
	case '+':
		return 2;

	case '(':
		return 1;
	}
}

queue<char> polish(char*s)      //черга
{
	const int zero = 48;
	queue<char> pol;
	stack <char> symbol;
	for (int i(0); i < strlen(s); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			int help = s[i] - zero; i++;
			while (s[i] >= '0' && s[i] <= '9' && i < strlen(s))
			{                                                       //записуємо в чергу перший символ
				help = help * 10 + s[i] - zero;                           // перевірка цифра/число
				i++;
			}
			i--;                                                     //оскільки ми вийшли з циклу, то далі не цифра
			pol.push(help);                                         //записали цифру/число в чергу
		}
		else                                                            //якщо ми отримали не цифру/число
		{
			if (s[i] == '(') symbol.push(s[i]);                         //маємо відкриваючу дужку - заносимо її в стек
			else {
				if (s[i] == ')')                                        //маємо закриваючу дужку, переносимо всі елементи в чергу
				{
					while (symbol.top() != '(')
					{
						pol.push(symbol.top());
						symbol.pop();
					}
					symbol.pop();
				}
				else {
					if (symbol.empty() || (prior(symbol.top()) < prior(s[i]))) symbol.push(s[i]);
					else
					{
						while (!symbol.empty() && prior(symbol.top()) >= prior(s[i]))
						{
							pol.push(symbol.top());
							symbol.pop();
						}
						symbol.push(s[i]);
					}
				}
			}
		}
	}
	while (!symbol.empty())
	{
		pol.push(symbol.top());
		symbol.pop();
	}
	return pol;
}

float result(queue<char> x)
{
	stack<float> odd;
	while (!x.empty())
	{
		char s = x.front(); //беремо перший елемент черги(верхній)
		switch (s) {
		case '+': {float a, b;
			a = odd.top();
			odd.pop();
			b = odd.top();//first
			odd.pop(); odd.push(a + b); break; }
		case '-': {float a, b;
			a = odd.top();
			odd.pop();
			b = odd.top();//first
			odd.pop(); odd.push(b - a); break; }
		case '*': {float a, b;
			a = odd.top();
			odd.pop();
			b = odd.top();//first
			odd.pop(); odd.push(a*b); break; }
		case '/': {float a, b;
			a = odd.top();
			odd.pop();
			b = odd.top();//first
			odd.pop(); odd.push(b / a); break; }
		case '^': {float a, b;
			a = odd.top();
			odd.pop();
			b = odd.top();//first
			odd.pop(); odd.push(pow(b, a)); break; }
		default: {odd.push(s); }

		}
		x.pop();
	}
	return odd.top();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
