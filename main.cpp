/*********************************************
Kod stanowi uzupe�nienie materia��w do �wicze�
w ramach przedmiotu metody optymalizacji.
Kod udost�pniony na licencji CC BY-SA 3.0
Autor: dr in�. �ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia G�rniczo-Hutnicza
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
		tab[i][0] = (rand() % 201 - 100);
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

	////Funkcja testowa
	//for (int i = 0; i < 100; i++)
	//{
	//	opt = fib(ff1T, tab[i][1], tab[i][2], epsilon);
	//	//cout << opt << endl << endl;
	//	tab2[i][0] = m2d(opt.x);
	//	tab2[i][1] = m2d(opt.y);
	//	tab2[i][2] = solution::f_calls;
	//	//for(int z =0; z<3; z++)
	//	//cout << "aaaaaaaa\t " << tab2[i][z] << endl;
	//	solution::clear_calls();
	//}

	//ofstream zapis2("3tablice.txt");
	//for (int j = 0; j < 3; j++)
	//{
	//	for (int i = 0; i < 100; i++)
	//	{
	//		zapis2 << tab2[i][j] << endl;
	//	}
	//	zapis2 << endl << endl;
	//}
	//zapis2.close();

	////////////////////////////////////////////////////
	//// 
	//for (int i = 0; i < 100; i++)
	//{
	//	opt = lag(ff1R, tab[i][1], tab[i][2], epsilon, gamma, Nmax);
	//	cout << opt << endl << endl;
	//	tab3[i][0] = m2d(opt.x);
	//	tab3[i][1] = m2d(opt.y);
	//	tab3[i][2] = solution::f_calls;
	//	for (int z = 0; z < 3; z++)
	//		cout << "aaaaaaaa\t " << tab3[i][z] << endl;

	//	solution::clear_calls();
	//}

	//ofstream zapis3("3tablice2.txt");
	//for (int j = 0; j < 3; j++)
	//{
	//	for (int i = 0; i < 100; i++)
	//	{
	//		zapis3 << tab3[i][j] << endl;
	//	}
	//	zapis3 << endl << endl;
	//}
	//zapis3.close();



	//opt = lag(ff1T, -10, 1, 0.0001, 1e-7, Nmax);
	//cout << opt << endl;
	//solution::clear_calls();

	////Zbiorniki
	//epsilon = 1e-10;
	//opt = fib(ff1R, 1e-4, 1e-2, 1e-10);
	//cout << opt << endl << endl;
	//cout << opt.x << endl << opt.y << endl;
	//solution::clear_calls();

	//opt = lag(ff1R, 1e-4, 1e-2, epsilon, gamma, Nmax);
	//cout << opt << endl << endl;
	//solution::clear_calls();
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
