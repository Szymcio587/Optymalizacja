#define _USE_MATH_DEFINES
#include"cmath"
#include"user_funs.h"

matrix iloczyn_macierzy(matrix A, matrix B, int wiersz_a, int kolumny_a, int wiersz_b, int kolumny_b)
{
	if (kolumny_a != wiersz_b)
	{
		cout << "Bledne rozmiary macierzy" << endl;
		cerr << "ERROR:\n";

	}
	//cout << "Iloczyn macierzy: " << endl;
	//cout << A << endl << endl << B << endl << endl;
	matrix C(wiersz_a, kolumny_b, 0.0);
	for (int i = 0; i < wiersz_a; i++)
		for (int j = 0; j < kolumny_b; j++)
			for (int k = 0; k < wiersz_b; k++)
				C(i, j) += A(i, k) * B(k, j);

	//cout << "=" << endl << C << endl << endl << endl;
	return C;
}

matrix ff1T(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	y = -cos(0.1 * x()) * exp(-pow(0.1 * x() - 2 * 3.14, 2)) + 0.002 * pow(0.1 * x(), 2);
	return y;
}

matrix ff1R(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	matrix Y0 = matrix(3, new double[3] { 5, 1, 10 });
	matrix* Y = solve_ode(df1, 0, 1, 1000, Y0, ud1, x);
	int n = get_len(Y[0]);
	double max = Y[1](0, 2);
	for (int i = 1; i < n; ++i)
		if (max < Y[1](i, 2))
			max = Y[1](i, 2);
	y = abs(max - 40);
	return y;
}


matrix df1(double t, matrix Y, matrix ud1, matrix ud2)
{
	double Pa = 0.75, Va = 5, Ta = 90;
	double Pb = 1, Vb = 1, Tb = 10, DB = 0.00365665;
	double Fin = 0.01, Tin = 10;
	double a = 0.98, b = 0.63, g = 9.81;

	matrix dY(3, 1);
	double FAout = Y(0) > 0 ? a * b * m2d(ud2) * sqrt(2 * g * Y(0) / Pa) : 0;
	double FBout = Y(1) > 0 ? a * b * DB * sqrt(2 * g * Y(1) / Pb) : 0;
	dY(0) = -FAout;
	dY(1) = FAout + Fin - FBout;
	dY(2) = Fin / Y(1) * (Tin - Y(2)) + FAout / Y(1) * (Ta - Y(2));
	return dY;
}

matrix ff2T(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	y = pow(x(0), 2) + pow(x(1), 2) - cos(2.5 * 3.14 * m2d(x(0))) - cos(2.5 * 3.14 * m2d(x(1))) + 2;
	return y;
}

matrix ff2R(matrix x, matrix ud1, matrix ud2)
{
	matrix y = 0;//macierz wynikowa
	matrix Y0 = ud2;

	ud1(8, 0) = x(0);
	ud1(9, 0) = x(1);

	//warunki brzegowe s� podane w mainie i przekazane tu przez ud2
	//warunki pocz�tkowe w postaci wektora pionowego o zadanych w {} warto�ciach
	//w ud1 przekazane s� parametry robota podane w instrukcji
	//p�ki co warunki pocz�tkowe s� zdublowane, w poprzednim kodzie by�a tam macierz x jako wektor wsp�rz�dnych, teraz wsp�rz�dne s� cz��i� ud1
	matrix* Y = solve_ode(df2, 0, 1, 1000, Y0, ud1, ud2);

	int n = get_len(Y[0]);//bierze d�ugo�� wektora wynik�w

	double aref = ud1(3, 0);
	double omegaref = 0;
	//double y = 0;
	//liczenie funkcjona�u jako�ci
	for (int i = 0; i < n; i++) {
		y = y + 10 * pow(aref - Y[1](i, 0), 2) + pow(omegaref - Y[1](i, 1), 2) +
			pow(x(0) * (aref - Y[1](i, 0)) + x(1) * (omegaref - Y[1](i, 1)), 2);
	}

	return y;

}
//ma zwraca� wektor warunk�w pocz�tkowych po zmianie => wektor nx1
//macierz Y to przes�any wektor warunk�w pocz�tkowych danego kroku czasowego o wymiarze nx1
//jest to kolumna wybrana dla danego kroku czasowego
matrix df2(double t, matrix Y, matrix ud1, matrix ud2)
{
	try {
		//getsize(ud2)[0] zwraca d�ugo�� wektora = ilo�ci zmiennych w kroku czasowym
		matrix dY(get_size(ud2)[0], 1);//obliczany w funkcji krok czasowy, kt�ry potem jest zwracany jako wektor

		//dane
		//ud1(0, 0) = 0.5;//d�ugo�� ramienia robota
		//ud1(1, 0) = 1;//masa ramienia robota
		//ud1(2, 0) = 9;//masa ci�zarka
		//ud1(3, 0) = 180;//k�t obrotu	aref
		//moment bezw�adno�ci
		//ci�arek jest traktowany jako punkt na ko�cu ramienia
		//ud1(4, 0) = (1 / 3) * ud1(1, 0) * pow((ud1(0, 0)), 2) + ud1(2, 0) * pow(ud1(0, 0), 2);
		//ud1(5, 0) = 0.5;//wsp�czynnik tarcia
		//ud1(6, 0) = 0.1;//krok czasowy

		double aref = ud1(3, 0);//referencyjny ko�cowy k�t ruchu
		double omegaref = 0;//referencyjna ko�cowa pr�dko�� ruchu
		double dt = ud1(6, 0);


		double k1 = ud1(8, 0);	//ud1(8, 0) = x(0);
		double k2 = ud1(9, 0);	//ud1(9, 0) = x(1);

		dY(2) = k1 * (aref - Y(0)) + k2 * (omegaref - Y(1));
		//w ud2 s� pocz�tkowe warto�ci dla alfy i omegi zmieniajace si� w czasie
		//W otrzymywanym z odesolvera wektorze Y s� ostatnie warto�ci alfy, omegii i momentu si�y. w takiej kolejno�ci:
		//Y(0)k�t, Y(1)pr�dko�c ko�cowa, Y(2)przy�o�ony moment si�y, Y(3) warto�� "y" funkcjona�u jako�ci

		//obliczy� nowe alfa i nowe omega
		dY(0) = Y(1);//nowy k�t
		dY(1) = (dY(2) - ud1(5, 0) * Y(1)) / ud1(4, 0);//nowa pr�dko�� k�towa



		//df2 ma si� uruchomi� tylko raz > rozwi�za� rr-> przekaza� wynik do ff
		return dY;
	}
	catch (string ex_info)
	{
		throw ("df2* sie wywalil(...):\n" + ex_info);
	}
}