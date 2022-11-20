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
	y = pow(x[0], 2) + pow(x[1], 2) - cos(2.5 * M_PI * m2d(x[0])) - cos(2.5 * M_PI * m2d(x[1])) + 2;
	return y;
}
