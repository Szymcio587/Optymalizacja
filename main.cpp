#define _USE_MATH_DEFINES
#include"cmath"
#include"opt_alg.h"
#include <windows.h>
#include <fstream>
#include "xlsxwriter.h"

void lab1();
void lab2();
void lab3();
void lab4();
void lab5();
void lab6();

int main()
{
	try
	{
		lab3();
	}
	catch (string EX_INFO)
	{
		cerr << "ERROR:\n";
		cerr << EX_INFO << endl << endl;
	}
	system("pause");
	return 0;
}

void lab1()
{
	//double tab[100][4];
	//double tab2[100][3];
	//double tab3[100][4];
	//double x0 = 100, d = 1.0, alpha = 1.2, epsilon = 1e-5, gamma = 1e-200;
	//int Nmax = 1000;
	//double* ab;
	//solution opt;

	//ab = expansion(ff1T, 100, d, alpha, Nmax);
	//double x = solution::f_calls;
	//cout << x << endl << endl;
	//solution::clear_calls();

	//opt = fib(ff1T, -100, 100, epsilon);
	//cout << opt << endl << endl;
	//solution::clear_calls();

	//opt = lag(ff1T, -100, 100, 0.0001, 1e-7, Nmax);
	//cout << opt << endl << endl;
	//solution::clear_calls();

	//srand(time(NULL));

	//for (int i = 0; i < 100; i++)
	//{
	//	tab[i][0] = (rand() % 201 - 100);
	//	ab = expansion(ff1T, tab[i][0], d, alpha, Nmax);
	//	tab[i][1] = ab[0];
	//	tab[i][2] = ab[1];
	//	tab[i][3] = solution::f_calls;
	//	solution::clear_calls();
	//}

}

void lab2()
{
	double s = 0.5;
	matrix ss(2, 2, s);
	ss(1, 0) = 0;
	ss(0, 1) = 0;

	double alphaHJ = 0.5;
	double alphaR = 2;
	double beta = 0.5;
	double epsilon = 0.00000001;
	int Nmax = 100;

	matrix ud1(10, 1, 0.0);//ud1 jako wektor 10x1 o wartoiach 0
	ud1(0, 0) = 0.5;//d逝go ramienia robota
	ud1(1, 0) = 1;//masa ramienia robota
	ud1(2, 0) = 9;//masa ci瞛arka
	ud1(3, 0) = 3.14;//k靖 obrotu ko鎍owy:    pi rad
	ud1(4, 0) = ((1 / 3) * ud1(1, 0) * pow((ud1(0, 0)), 2)) + ud1(2, 0) * pow(ud1(0, 0), 2);
	ud1(5, 0) = 0.5;//wsp馧czynnik tarcia
	ud1(6, 0) = 0.1;//krok czasowy
	ud1(7, 0) = 0.1;//tend - czas ko鎍owy

	matrix ud2 = matrix(4, new double[4] { 0, 0, 0, 0 });

	matrix x0(2, 1, 5);

	//solution sol1 = HJ(ff2R, x0, s, alphaHJ, epsilon, Nmax, ud1, ud2);
	//cout << sol1 << endl;
	//solution::clear_calls();
	solution sol2 = Rosen(ff2R, x0, ss, alphaR, beta, epsilon, Nmax, ud1, ud2);
	cout << sol2 << endl;

	//srand(time(NULL));
	//lxw_workbook* workbook = workbook_new("Cwiczenia_2.xlsx");
	//lxw_worksheet* worksheet = workbook_add_worksheet(workbook, "Tabela 1");
	//matrix x0[10][10];
	//double X[2];
	//double s = 0.2;
	//matrix ss(2, 2, s);
	//ss(1, 0) = 0;
	//ss(0, 1) = 0;
	//	for (int j = 0; j < 10; j++) {
	//		for (int i = 0; i < 10; i++)
	//		{
	//			X[0] = i * 1;
	//			X[1] = j * 1;
	//			//X[0] = 1;
	//			//X[1] = 1;
	//			x0[j][i] = matrix(2, X);
	//			//cout << x0[i] << endl;
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 1, X[0], NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 2, X[1], NULL);
	//			solution sol1 = HJ(ff2R, x0[j][i], s, alphaR, epsilon, Nmax, ud1, ud2);
	//			//cout << sol1 << endl;
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 3, m2d(sol1.x(0, 0)), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 4, m2d(sol1.x(0, 0)), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 5, m2d(sol1.y), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 6, sol1.f_calls, NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 7, sol1.flag, NULL);
	//			sol1.clear_calls();
	//			solution sol2 = Rosen(ff2R, x0[j][i], ss, alphaR, beta, epsilon, Nmax, ud1, ud2);
	//			//cout << sol2 << endl;
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 8, m2d(sol2.x(0, 0)), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 9, m2d(sol2.x(0, 0)), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 10, m2d(sol2.y), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 11, sol2.f_calls, NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 12, sol2.flag, NULL);
	//			sol2.clear_calls();
	//		}
	//	}
	//workbook_close(workbook);
}

void lab3()
{
	//matrix x0(2, 1, -2.0);
	//x0(0, 0) = -3;
	//matrix z = ff3T(x0);
	//cout << z;

	matrix x0(2, 1, 0.0);
	double alpha = 4.0, beta = 0.5, gamma = 0.5, delta = 0.5, epsilon = 0.0001;
	int s = 3, Nmax = 100;
	solution sol = sym_NM(ff3R, x0, s, alpha, beta, gamma, delta, epsilon, Nmax);
	//std::cout << sol;

	//srand(time(NULL));
	//lxw_workbook* workbook = workbook_new("Cwiczenia_3.xlsx");
	//lxw_worksheet* worksheet = workbook_add_worksheet(workbook, "Tabela 1");
	//matrix x0[100];
	//double X[2];
	//matrix ss(2, 2, s);
	//ss(1, 0) = 0;
	//ss(0, 1) = 0;
	//	for (int j = 0; j < 1; j++) {
	//		for (int i = 0; i < 100; i++)
	//		{
	//			X[0] = (double) rand() / RAND_MAX * 10;
	//			X[1] = (double) rand() / RAND_MAX * 10;
	//			//X[0] = 1;
	//			//X[1] = 1;
	//			x0[i] = matrix(2, X);
	//			//cout << x0[i] << endl;
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 1, X[0], NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 2, X[1], NULL);
	//			beta = 0.5, gamma = 0.5, delta = 0.5, epsilon = 0.01;
	//			solution sol1 = sym_NM(ff3R, x0[i], s, alpha, beta, gamma, delta, epsilon, Nmax);
	//			cout << sol1 << endl;
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 3, m2d(sol1.x(0, 0)), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 4, m2d(sol1.x(1, 0)), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 5, pow(pow(m2d(sol1.x(0, 0)), 2) + pow(m2d(sol1.y), 2), 0.5), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 6, m2d(sol1.y), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 7, sol1.f_calls, NULL);
	//			sol1.clear_calls();
	//			beta = 0.1, gamma = 0.1, delta = 0.1, epsilon = 0.0001;
	//			solution sol2 = sym_NM(ff3R, x0[i], s, alpha, beta, gamma, delta, epsilon, Nmax);
	//			cout << sol2 << endl;
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 8, m2d(sol2.x(0, 0)), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 9, m2d(sol2.x(1, 0)), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 10, pow(pow(m2d(sol2.x(0, 0)), 2) + pow(m2d(sol2.y), 2), 0.5), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 11, m2d(sol2.y), NULL);
	//			worksheet_write_number(worksheet, 100 * j + i + 1, 12, sol2.f_calls, NULL);
	//			sol2.clear_calls();
	//		}
	//	}
	//workbook_close(workbook);
}

void lab4()
{

}

void lab5()
{

}

void lab6()
{

}
