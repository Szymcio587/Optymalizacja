/*********************************************
Kod stanowi uzupe³nienie materia³ów do æwiczeñ
w ramach przedmiotu metody optymalizacji.
Kod udostêpniony na licencji CC BY-SA 3.0
Autor: dr in¿. £ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia Górniczo-Hutnicza
*********************************************/

#include"opt_alg.h"
#include "xlsxwriter.h"
#include <iostream>

struct Data {
	double x0, x, y;
	int calls;
};

void writeHeader(lxw_worksheet* worksheet, const char* name, int row, int col) {
	worksheet_write_string(worksheet, row++, col, name, NULL);
	worksheet_write_string(worksheet, row, col, "X", NULL);
	worksheet_write_string(worksheet, row, col + 1, "Y", NULL);
	worksheet_write_string(worksheet, row, col + 2, "Liczba wywolan", NULL);
	worksheet_write_string(worksheet, row, col + 3, "Minimum globalne/lokalne", NULL);
}

void writeData(lxw_worksheet* worksheet, int row, int col, solution opt) {
	worksheet_write_number(worksheet, row, col, m2d(opt.x), NULL);
	worksheet_write_number(worksheet, row, col + 1, m2d(opt.y), NULL);
	worksheet_write_number(worksheet, row, col + 2, opt.f_calls, NULL);
	if (m2d(opt.x) > 31)
		worksheet_write_number(worksheet, row, col + 3, 62.73, NULL);
	else
		worksheet_write_number(worksheet, row, col + 3, 0, NULL);
	solution::clear_calls();
}

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
		lab1();
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
	struct Data data[100];
	const double d = 1.0, epsilon = 1e-5, gamma = 1e-200;
	double alpha = 1.2;
	const int Nmax = 1000;
	double* ab;
	solution opt;

	//ab = expansion(ff1T, 100, d, alpha, Nmax);
	//double x = solution::f_calls;
	//cout << x << endl << endl;
	//solution::clear_calls();

	//opt = fib(ff1T, -100, 100, epsilon);
	//cout << opt << endl << endl;
	//solution::clear_calls();

	//opt = lag(ff1T, -100, 100, 0.0001, 1e-7, Nmax);
	////cout << opt << endl << endl;
	//solution::clear_calls();

	srand(time(NULL));

	lxw_workbook* workbook = workbook_new("Cwiczenia_1.xlsx");
	lxw_worksheet* worksheet = workbook_add_worksheet(workbook, "Tabela 1");

	for (int i = 0; i < 100; i++) 
	{
		data[i].x0 = (rand() % 2000 - 1000);
		data[i].x0 /= 10;
	}

	worksheet_write_string(worksheet, 1, 1, "Ekspansja", NULL);
	worksheet_write_string(worksheet, 2, 0, "Wspolczynnik ekspansji", NULL);
	worksheet_write_string(worksheet, 2, 1, "Punkt startowy", NULL);
	worksheet_write_string(worksheet, 2, 2, "X", NULL);
	worksheet_write_string(worksheet, 2, 3, "Y", NULL);
	worksheet_write_string(worksheet, 2, 4, "Liczba wywolan", NULL);
	writeHeader(worksheet, "Fibo", 1, 6);
	writeHeader(worksheet, "Lag", 1, 11);

	for (int q = 0; q < 3; q++) {
		if (q == 0)
			alpha = 2;
		if (q == 1)
			alpha = 5;

		if (q == 2)
			alpha = 1.2;

		for (int i = 0; i < 100; i++) 
		{
			ab = expansion(ff1T, data[i].x0, d, alpha, Nmax);
			data[i].x = ab[0];
			data[i].y = ab[1];
			data[i].calls = solution::f_calls;
			solution::clear_calls();
		}

		int row = 3 + 102 * q, col = 0;

		worksheet_write_number(worksheet, row, col, alpha, NULL);

		for (row; row < 103 + 102 * q; row++) 
		{
			worksheet_write_number(worksheet, row, col + 1, data[row - (3 + 102 * q)].x0, NULL);
			worksheet_write_number(worksheet, row, col + 2, data[row - (3 + 102 * q)].x, NULL);
			worksheet_write_number(worksheet, row, col + 3, data[row - (3 + 102 * q)].y, NULL);
			worksheet_write_number(worksheet, row, col + 4, data[row - (3 + 102 * q)].calls, NULL);
		}

		col += 6;

		for (int row = 3 + 102 * q; row < 103 + 102 * q; row++)
			writeData(worksheet, row, col, fib(ff1T, data[row - (3 + 102 * q)].x, data[row - (3 + 102 * q)].y, epsilon));

		col += 5;

		
		for (int row = 3 + 102 * q; row < 103 + 102 * q; row++)
			writeData(worksheet, row, col, lag(ff1T, data[row - (3 + 102 * q)].x, data[row - (3 + 102 * q)].y, 0.0001, 1e-7, Nmax));
	}
	

	lxw_worksheet* worksheet_2 = workbook_add_worksheet(workbook, "Tabela 2");
	workbook_close(workbook);

}

void lab2()
{

}

void lab3()
{

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
