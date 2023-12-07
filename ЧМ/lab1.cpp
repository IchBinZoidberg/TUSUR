#include <locale.h>
#include <iostream>
#include "PolStr.h"
#include <iomanip>
#include <fstream>
#include <cmath>

#define tay (sqrt(double(5)) + 1) / 2.0


using namespace std;

double Combined(char* func, double a, double b, double eps, double& value, double& result)
{
	cout << "Комбинационный метод" << endl;
	while (1) 
	{
		double c = a - EvalPolStr(func, a, 0) / (EvalPolStr(func, b, 0) - EvalPolStr(func, a, 0)) * (b - a);
		if (EvalPolStr(func, a, 0) * EvalPolStr(func, a, 2) > 0)
		{
			double derivative = EvalPolStr(func, a, 1);
			a -= EvalPolStr(func, a, 0) / derivative;
			b = c;
		}
		else {
			a = c;
			double derivative = EvalPolStr(func, b, 1);
			b -= EvalPolStr(func, b, 0) / derivative;
		}
		result = fabs(EvalPolStr(func, (a + b) / 2, 0));
		value = fabs(b - a) / 2;
		if (value <= eps && result <= eps) 
		{
			return (a + b) / 2;
		}
	}
}
double Iteration(char* func, double a, double b, double eps, double& value, double& result)
{
	cout << "Метод итераций" << endl;
	double x = -1;
	for (double i = a; i < b; i += 0.01)
	{
		if (fabs(EvalPolStr(func, i, 1)) > x)
			x = i;
	}
	double derivative = fabs(EvalPolStr(func, x, 1));
	while (1)
	{
		result = EvalPolStr(func, x, 0);
		double temp = x - result / derivative;
		result = fabs(result);
		value = fabs(temp - x);
		if (result <= eps && value <= eps)
		{
			return temp;
		}
		x = temp;
		break;
	}
}
double Golden(char* func, double a, double b, double eps, double& value, double& result)
{
	cout << "Метод золотого сечения: \n";
	const double ratio = (sqrt(5) + 1) / 2;
	while (1)
	{
		double d = a + (b - a) / ratio;
		double c = b + a - d;
		if (EvalPolStr(func, c, 0) * EvalPolStr(func, d, 0) <= 0)
			b = d;
		else
			a = c;
		result = fabs(EvalPolStr(func, (a + b) / 2, 0));
		value = fabs(b - a) / 2;
		if (result <= eps && value <= eps) {
			return (a + b) / 2;
		}
	}
}
int main()
{
	setlocale(LC_ALL, "russian");

	int n = 0;
	int input = 0;
	double a, b, eps;
	a = b = eps = 0.0;
	char function[1024] = "";
	cout << "Выберете тип ввода ( 1 - с клавиатуры; 2 - с файла): ";
	cin >> input;
	switch (input)
	{
	case 1:

		cout << "Введите номер метода" << endl << "1. Дихотомия" << endl << "2. Метод хорд" << endl << "3. Метод Ньютона" << endl << "4.Комбинированный метод" << endl << "5.Метод итераций" << endl << "6.Метод золотого сечения" << endl;
		cin >> n;
		cout << "Введите функцию в аналитическом виде" << endl;
		cin >> function;
		cout << "Введите границы отрезка" << endl;
		cin >> a >> b;
		cout << "Введите точность решения" << endl;
		cin >> eps;

		break;
	case 2:

		ifstream FileIn("input.txt");
		if (!FileIn.is_open())
		{
			cout << "Ошибка при открытии файла" << endl;
			exit(EXIT_FAILURE);
		}

		FileIn >> n;
		cout << n << endl;

		FileIn >> function;
		cout << function << endl;

		FileIn >> a >> b;
		cout << a << "  " << b << endl;

		FileIn >> eps;
		cout << eps << endl;

		break;
	}

	char* polstr = CreatePolStr(function, 0);
	if (EvalPolStr(polstr, a) * EvalPolStr(polstr, b) > 0)
	{
		cout << "Решений нет или их 2 и более" << endl;
		return 0;
	}


	int countofeps;
	countofeps = -log10f(eps);
	cout << "Cтепень точности - " << countofeps << endl;

	switch (n)
	{
	case 1:
	{
		int count = 0;
		double x = (a + b) / 2;
		while ((b - a) / 2 >= eps || fabs(EvalPolStr(polstr, x) >= eps))
		{

			double c;
			c = (a + b) / 2;

			if (EvalPolStr(polstr, a) * EvalPolStr(polstr, c) <= 0)
			{
				b = c;
			}
			else
			{
				a = c;
			}
			x = (a + b) / 2;
			count++;
		}
		cout.setf(ios::fixed);
		cout.precision(countofeps);
		cout << "Ответ - " << x << endl;
		cout << "Значение функции - " << EvalPolStr(polstr, x) << endl;
		cout << scientific << "Погрешность решения - " << fabs(0 - EvalPolStr(polstr, x)) << endl;

		break;
	}

	case 2:
	{
		int count = 0;
		double x, xnext, c;
		c = xnext = a - (EvalPolStr(polstr, a) / ((EvalPolStr(polstr, b) - EvalPolStr(polstr, a))) * (b - a));
		if (EvalPolStr(polstr, a) * EvalPolStr(polstr, c) <= 0)
		{
			b = c;
		}
		else
		{
			a = c;
		}
		count++;
		x = xnext;
		c = xnext = a - (EvalPolStr(polstr, a) / ((EvalPolStr(polstr, b) - EvalPolStr(polstr, a))) * (b - a));
		cout.setf(ios::fixed);
		cout.precision(countofeps);
		while (fabs(xnext - x) >= eps || fabs(EvalPolStr(polstr, xnext) >= eps))
		{
			x = xnext;
			if (EvalPolStr(polstr, a) * EvalPolStr(polstr, c) <= 0)
			{
				b = c;
			}
			else
			{
				a = c;
			}
			count++;
			c = xnext = a - (EvalPolStr(polstr, a) / ((EvalPolStr(polstr, b) - EvalPolStr(polstr, a))) * (b - a));
			cout << "x" << " - " << x << " xnext" << " - " << xnext << endl;

		}
		cout << "Ответ - " << x << endl;
		cout << "Значение функции - " << EvalPolStr(polstr, x) << endl;
		cout << scientific << "Погрешность решения - " << fabs(xnext - x) << endl;

		break;
	}
	case 4:
	{
		double x, eq_eps, y;
		Combined(polstr, a, b, eps, eq_eps, y);

	}
	case 5:
	{
		double x, eq_eps, y;
		Iteration(polstr, a, b, eps, eq_eps, y);

	}
	case 6:
	{
		double x, eq_eps, y;
		Golden(polstr, a, b, eps, eq_eps, y);



	}
	case 3:
	{
		int count = 0;
		double x, c, xnext;
		c = a - (EvalPolStr(polstr, a) / (EvalPolStr(polstr, b) - EvalPolStr(polstr, a)) * (b - a));
		if (EvalPolStr(polstr, a) * EvalPolStr(polstr, c) <= 0)
		{
			x = a;
		}
		else
		{
			x = b;
		}
		xnext = x - (EvalPolStr(polstr, x) / EvalPolStr(polstr, x, 1));

		while (fabs(xnext - x) >= eps && fabs(EvalPolStr(polstr, x) >= eps))
		{
			x = xnext;
			xnext = x - (EvalPolStr(polstr, x) / EvalPolStr(polstr, x, 1));
			cout << "\nxnext - " << xnext << endl;
		}

		cout.setf(ios::fixed);
		cout.precision(countofeps);
		cout << "\nОтвет - " << x << endl;
		cout << "Значение функции - " << EvalPolStr(polstr, x) << endl;
		cout << scientific << "Погрешность решения - " << fabs(xnext - x) << endl;
		ofstream fout;
		fout.open("file.txt");
		fout.setf(ios::fixed);
		fout.precision(countofeps);
		fout << "\nОтвет - " << x << endl;
		fout << "Значение функции - " << EvalPolStr(polstr, x) << endl;
		fout << scientific << "Погрешность решения - " << fabs(xnext - x) << endl;
		break;
	}
	}

	return 0;
}

