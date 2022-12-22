#define _USE_MATH_DEFINES
#include"cmath"
#include"opt_alg.h"
#include <windows.h>
#include <fstream>

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
		std::cout << "\nskonczylo program\n";
	}
	catch (string EX_INFO)
	{
		cerr << "ERROR w mainie:\n";
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
	double x0 = m2d(100), d = 1.0, alpha = 1.2, epsilon = 1e-5, gamma = 1e-200;
	int Nmax = 1000;
	double* ab;
	solution opt;
	
	ab = expansion(ff1R, 100, d, alpha, Nmax);
	double x = solution::f_calls;
	cout << x << endl << endl << endl << endl;
	solution solF = fib(ff1R, ab[0], ab[1], epsilon);
	solution solL = lag(ff1R, ab[0], ab[1], epsilon, gamma, Nmax);
	cout << "________________________" << endl;
	matrix Z0 = matrix(3, new double[3] { 5, 1, 10 });

	matrix* Z = solve_ode(df1, 0, 1, 1000, Z0, 0, solF.x);
	//cout  << " " << Z[1][2] << " " << endl<<endl<<endl<<"LAG:\n";

	matrix* Z1 = solve_ode(df1, 0, 1, 1000, Z0, 0, solL.x);
	cout << " " << Z1[1][2] << " " << endl;


	//opt = fib(fun1, -100, 100, epsilon);

	//solution::clear_calls();

	//opt = lag(fun1, -100, 100, 0.0001, 1e-7, Nmax);
	//cout << opt << endl << endl;
	//solution::clear_calls();



	//for (int i = 0; i < 100; i++)
	//{
	//	tab[i][0] = (rand() % 2000 - 1000);
	//	tab[i][0] /= 10;

	//	ab = expansion(fun1, tab[i][0], d, alpha, Nmax);
	//	tab[i][1] = ab[0];
	//	tab[i][2] = ab[1];
	//	tab[i][3] = solution::f_calls;
	//	solution::clear_calls();
	//}
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

	////Funkcja testowa
	//for (int i = 0; i < 100; i++)
	//{
	//	opt = fib(fun1, tab[i][1], tab[i][2], epsilon);
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
	// for (int i = 0; i < 100; i++)
	// {
	//	opt = lag(ff1R, tab[i][1], tab[i][2], epsilon, gamma, Nmax);
	//	cout << opt << endl << endl;
	//	tab3[i][0] = m2d(opt.x);
	//	tab3[i][1] = m2d(opt.y);
	//	tab3[i][2] = solution::f_calls;
	//	for(int z =0; z<3; z++)
	//	cout << "aaaaaaaa\t " << tab3[i][z] << endl;

	//	solution::clear_calls();
	// }

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

	//Zbiorniki
	/*epsilon = 1e-10;
	opt = fib(ff1R, 1e-4, 1e-2, 1e-10);
	cout << opt << endl << endl;
	cout << opt.x << endl << opt.y << endl;
	solution::clear_calls();

	opt = lag(ff1R, 1e-4, 1e-2, epsilon, gamma, Nmax);
	cout << opt << endl << endl;
	solution::clear_calls();*/
}

void lab2()
{
	double s = 0.5;//zmienna okreœlaj¹ca d³ugoœæ kroku
	matrix ss(2, 2, s);// matrix d³ugoœci kroku
	ss(1, 0) = 0;
	ss(0, 1) = 0;

	//parametry
	double alphaHJ = 0.5;
	double alphaR = 2;
	double beta = 0.5;
	double epsilon = 0.00000001;
	int Nmax = 1000;

	//matrix x0hj(2, 1, 0.75);
	//solution sol1 = HJ(ff2T, x0hj, s, alphaHJ, epsilon, Nmax, NULL, NULL);
	//cout << sol1 << endl;
	//solution::clear_calls();

	matrix ud1(10, 1, 0.0);//ud1 jako wektor 10x1 o wartoœciach 0
	ud1(0, 0) = 0.5;//d³ugoœæ ramienia robota
	ud1(1, 0) = 1;//masa ramienia robota
	ud1(2, 0) = 9;//masa ciêzarka
	ud1(3, 0) = 3.14;//k¹t obrotu koñcowy:    pi rad
	//moment bezw³adnoœci
	////ciê¿arek jest traktowany jako punkt na koñcu ramienia
	ud1(4, 0) = ((1 / 3) * ud1(1, 0) * pow((ud1(0, 0)), 2)) + ud1(2, 0) * pow(ud1(0, 0), 2);
	ud1(5, 0) = 0.5;//wspó³czynnik tarcia
	ud1(6, 0) = 0.1;//krok czasowy
	ud1(7, 0) = 0.1;//tend - czas koñcowy

	//warunki pocz¹tkowe i póŸniej kolejne wyrazy zapisu
	//k¹t0, prêdkoœc koñcowa0, przy³o¿ony moment si³y0, wartoœæ funkcjona³u jakoœci0
	matrix ud2 = matrix(4, new double[4] { 0, 0, 0, 0 });//warunki pocz¹tkowe

	//matrix punktu startowego
	//parametry wymiar n, wymiar m, wartoœæi wszystkich wyrazów w tablicy
	//x0.x i x0.y powinny byæ z przedzia³u [0,10]
	matrix x0(2, 1, 0.75);


	solution sol1 = HJ(ff2R, x0, s, alphaHJ, epsilon, Nmax, ud1, ud2);
	cout << sol1 << endl;
	solution::clear_calls();

	solution sol2 = Rosen(ff2R, x0, ss, alphaR, beta, epsilon, Nmax, ud1, ud2);
	cout << sol2 << endl;

	//funkcja zwraca solution, przyjmuje:
	//wskaŸnik do funkcji zwracaj¹cej matrix, matrix wspolrzedne (pocz¹tkowe), matrix dlugosc_kroku, 
	//double alpha, double beta, double epsilon, int Nmax, matrix ud1, matrix ud2
	//solution sol2 = Rosen(ff2T, x0, ss, alphaR, beta, epsilon, Nmax, ud1, ud2);

	//solution sol2 = Rosen(ff2R, x0, ss, alphaR, beta, epsilon, Nmax, ud1, ud2);
	//cout << sol2 << endl;

	//matrix* Z = solve_ode(df2, 0, 1, 1000, ud2, ud1, ud2);
	//cout << Z[1](0) << "\n";
	//cout << Z[1](1) << "\n";
	//cout << Z[1](2) << "\n";
	//cout << Z[1](3) << "\n";

	//cout << sol2.y << "\n";
	
}

void lab3()
{
	//matrix x0(2, 1, -2.0);
	//x0(0, 0) = -3;
	//matrix z = ff3T(x0);
	//cout << z;

	matrix x0(2, 1, 0.0);
	double alpha = 1.0, beta = 0.5, gamma = 0.5, delta = 0.5, epsilon = 0.0001;
	int s = 3, Nmax = 100;
	solution sol = sym_NM(ff3R, x0, s, alpha, beta, gamma, delta, epsilon, Nmax);

	std::cout << sol;

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

