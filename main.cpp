/*********************************************
Kod stanowi uzupe³nienie materia³ów do æwiczeñ
w ramach przedmiotu metody optymalizacji.
Kod udostêpniony na licencji CC BY-SA 3.0
Autor: dr in¿. £ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia Górniczo-Hutnicza
*********************************************/

#include"opt_alg.h"

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
	double tab[100][4];
	double tab2[100][3];
	double tab3[100][4];
	double x0 = 100, d = 1.0, alpha = 1.2, epsilon = 1e-5, gamma = 1e-200;
	int Nmax = 1000;
	double* ab;
	solution opt;

	ab = expansion(ff1T, 100, d, alpha, Nmax);
	double x = solution::f_calls;
	cout << x << endl << endl;
	solution::clear_calls();

	opt = fib(ff1T, -100, 100, epsilon);
	cout << opt << endl << endl;
	solution::clear_calls();

	opt = lag(ff1T, -100, 100, 0.0001, 1e-7, Nmax);
	cout << opt << endl << endl;
	solution::clear_calls();

	srand(time(NULL));

	for (int i = 0; i < 100; i++)
	{
		tab[i][0] = (rand() % 2000 - 1000);
		tab[i][0] /= 10;
		ab = expansion(ff1T, tab[i][0], d, alpha, Nmax);
		tab[i][1] = ab[0];
		tab[i][2] = ab[1];
		tab[i][3] = solution::f_calls;
		solution::clear_calls();
	}
	//ofstream zapis("4tablice.txt");
	//for (int j = 0; j < 4; j++)
	//{
	//	for (int i = 0; i < 100; i++)
	//	{
	//		zapis << tab[i][j] << endl;
	//	}
	//	zapis << endl << endl;
	//}
	//zapis.close();
	//fstream result("data_2.csv", ios::app);
	//for (int j = 0; j < 100; j++) {
	//	for (int i = 0; i < 4; i++)
	//		result << tab[j][i] << ";";
	//	result << "\n";
	//}
	//result.close();

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
