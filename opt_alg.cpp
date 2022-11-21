#define _USE_MATH_DEFINES
#include"opt_alg.h"
#include<cmath>
double* expansion(matrix(*ff)(matrix, matrix, matrix), double x0, double d, double alpha, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		double* p = new double[2] { 0, 0 };
		int i = 0;
		solution X0(x0), X1(x0 + d);
		X0.fit_fun(ff, ud1, ud2);
		X1.fit_fun(ff, ud1, ud2);
		if (X0.y == X1.y)
		{
			p[0] = m2d(X0.x);
			p[1] = m2d(X1.x);
			return p;
		}
		if (X0.y < X1.y)
		{
			d *= -1;
			X1.x = X0.x + d;
			X1.fit_fun(ff, ud1, ud2);
			if (X1.y >= X0.y)
			{
				p[0] = m2d(X1.x);
				p[1] = m2d(X0.x) - d;
				return p;
			}
		}
		solution X2;
		while (true)
		{
			++i;
			X2.x = x0 + pow(alpha, i) * d;
			X2.fit_fun(ff, ud1, ud2);
			if (X2.y >= X1.y || solution::f_calls > Nmax)
				break;
			X0 = X1;
			X1 = X2;
		}
		d > 0 ? p[0] = m2d(X0.x), p[1] = m2d(X2.x) : (p[0] = m2d(X2.x), p[1] = m2d(X0.x));
		return p;
	}
	catch (string ex_info)
	{
		throw ("double* expansion(...):\n" + ex_info);
	}
}

solution fib(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		Xopt.ud = b - a;
		int n = static_cast<int>(ceil(log2(sqrt(5) * (b - a) / epsilon) / log2((1 + sqrt(5)) / 2)));
		int* F = new int[n] {1, 1};
		for (int i = 2; i < n; ++i)
			F[i] = F[i - 2] + F[i - 1];
		solution A(a), B(b), C, D;
		C.x = B.x - 1.0 * F[n - 2] / F[n - 1] * (B.x - A.x);
		D.x = A.x + B.x - C.x;
		C.fit_fun(ff, ud1, ud2);
		D.fit_fun(ff, ud1, ud2);
		for (int i = 0; i <= n - 3; ++i)
		{
			//cout << abs(m2d(B.x) - m2d(A.x)) << "\n";
			if (C.y < D.y)
				B = D;
			else
				A = C;
			C.x = B.x - 1.0 * F[n - i - 2] / F[n - i - 1] * (B.x - A.x);
			D.x = A.x + B.x - C.x;
			C.fit_fun(ff, ud1, ud2);
			D.fit_fun(ff, ud1, ud2);

			Xopt.ud.add_row((B.x - A.x)());
		}
		Xopt = C;
		Xopt.flag = 0;
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution fib(...):\n" + ex_info);
	}

}

solution lag(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, double gamma, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		Xopt.ud = b - a;

		solution A(a), B(b), C, D, D_old(a);
		C.x = (a + b) / 2;

		A.fit_fun(ff1T, ud1, ud2);
		B.fit_fun(ff1T, ud1, ud2);
		C.fit_fun(ff1T, ud1, ud2);

		double l, m;

		while (true)
		{
			l = m2d(A.y * (pow(B.x) - pow(C.x)) + B.y * (pow(C.x) - pow(A.x)) + C.y * (pow(A.x) - pow(B.x)));
			m = m2d(A.y * (B.x - C.x) + B.y * (C.x - A.x) + C.y * (A.x - B.x));

			//cout << abs(m2d(B.x) - m2d(A.x)) << "\n";

			if (m <= 0)
			{
				Xopt = D_old;
				Xopt.flag = 2;
				return Xopt;
			}

			D.x = 0.5 * l / m;
			D.fit_fun(ff1T, ud1, ud2);

			if (A.x <= D.x && D.x <= C.x)
			{
				if (D.y < C.y)
				{
					A.x = A.x;
					C.x = D.x;
					B.x = C.x;

					A.fit_fun(ff1T, ud1, ud2);
					B.fit_fun(ff1T, ud1, ud2);
					C.fit_fun(ff1T, ud1, ud2);
				}
				else
				{
					A.x = D.x;
					C.x = C.x;
					B.x = B.x;

					A.fit_fun(ff1T, ud1, ud2);
					B.fit_fun(ff1T, ud1, ud2);
					C.fit_fun(ff1T, ud1, ud2);
				}
			}
			else if (C.x <= D.x && D.x <= B.x)
			{
				if (D.y < C.y)
				{
					A.x = C.x;
					B.x = B.x;
					C.x = D.x;

					A.fit_fun(ff1T, ud1, ud2);
					B.fit_fun(ff1T, ud1, ud2);
					C.fit_fun(ff1T, ud1, ud2);

				}
				else
				{
					B.x = D.x;
					C.x = C.x;
					A.x = A.x;

					A.fit_fun(ff1T, ud1, ud2);
					B.fit_fun(ff1T, ud1, ud2);
					C.fit_fun(ff1T, ud1, ud2);
				}
			}
			else
			{
				A.fit_fun(ff1T, ud1, ud2);
				B.fit_fun(ff1T, ud1, ud2);
				C.fit_fun(ff1T, ud1, ud2);

				Xopt = D_old;
				Xopt.flag = 2;

				return Xopt;
			}

			Xopt.ud.add_row((B.x - A.x)());

			if (B.x - A.x < epsilon || abs(D.x() - D_old.x()) < gamma)
			{
				A.fit_fun(ff1T, ud1, ud2);
				B.fit_fun(ff1T, ud1, ud2);
				C.fit_fun(ff1T, ud1, ud2);

				Xopt = D;
				Xopt.flag = 0;
				break;
			}
			if (solution::f_calls > Nmax)
			{

				A.fit_fun(ff1T, ud1, ud2);
				B.fit_fun(ff1T, ud1, ud2);
				C.fit_fun(ff1T, ud1, ud2);

				Xopt = D;
				Xopt.flag = 1;
				break;
			}
			A.fit_fun(ff1T, ud1, ud2);
			B.fit_fun(ff1T, ud1, ud2);
			C.fit_fun(ff1T, ud1, ud2);

			D_old = D;
		}
		A.fit_fun(ff1T, ud1, ud2);
		B.fit_fun(ff1T, ud1, ud2);
		C.fit_fun(ff1T, ud1, ud2);

		return Xopt;

	}
	catch (string ex_info)
	{
		throw ("solution lag(...):\n" + ex_info);
	}
}

solution HJ(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Xopt.XB
		solution X, XB, XBold;
		X = x0;

		while (true) {
			XB = X;
			X = HJ_trial(ff, XB, s, ud1, ud2);
			X.fit_fun(ff, ud1, ud2);
			XB.fit_fun(ff, ud1, ud2);

			if (X.y < XB.y) {

				while (true) {
					XBold = XB;
					XB = X;
					X.x = 2 * XB.x - XBold.x;
					X = HJ_trial(ff, XB, s, ud1, ud2);
					if (solution::f_calls > Nmax) {
						return -1;
					}
					X.fit_fun(ff, ud1, ud2);
					XB.fit_fun(ff, ud1, ud2);
					if (X.y >= XB.y)
						break;
				}
				X = XB;

			}
			else {
				s = alpha * s;
			}
			if (solution::f_calls > Nmax) {
				return -1;
			}
			if (s < epsilon) {
				break;
			}
		}
		Xopt = XB;
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution HJ(...):\n" + ex_info);
	}
}

solution HJ_trial(matrix(*ff)(matrix, matrix, matrix), solution XB, double s, matrix ud1, matrix ud2)
{
	try
	{
		int n = get_dim(XB);
		matrix E = ident_mat(n);
		solution X;

		for (int j = 0; j < n; j++) {
			X.x = XB.x + s * E[j];
			X.fit_fun(ff, ud1, ud2);
			XB.fit_fun(ff, ud1, ud2);
			if (X.y < XB.y) {
				XB.x = XB.x + s * E[j];
			}
			else {
				X.x = XB.x - s * E[j];
				X.fit_fun(ff, ud1, ud2);
				if (X.y < XB.y) {
					XB.x = XB.x - s * E[j];
				}
			}
		}
		return XB;
	}

	catch (string ex_info)
	{
		throw ("solution HJ_trial(...):\n" + ex_info);
	}
}
//punkt startowy x(0), wektor długość kroków s(0), współczynnik ekspansji α > 1,
//współczynnik kontrakcji 0 < β < 1, dokładność ε > 0, maksymalna liczba wywołań funkcji celu Nmax
//macierze Q i D odpowiadają obrotowi bazy
solution Rosen(matrix(*ff)(matrix, matrix, matrix), matrix wspolrzedne, matrix dlugosc_kroku, double alpha, double beta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{

		bool running = true;//zmienna do kończenia pętli głównej funkcji
		solution Xopt;
		int n = get_dim(wspolrzedne);//zbierać wymiar przestrzeni
		matrix poczatkowe_wspolrzedne = wspolrzedne;
		matrix preNowaBaza(n, n, 0.0);
		matrix nowe_wspolrzedne(n, 1, 0.0);
		matrix kierunek(n, n, 0.0);
		matrix roznica_poczatku_baz(n, n, 0.0);

		kierunek(0, 0) = 1;
		kierunek(1, 1) = 1;
		double x_roznica, y_roznica;

		int i = 0;
		matrix lambda(n, 1, 0.0);//poprawne kroki
		matrix porazki(n, 1, 0.0);//porażki
		double dl_kroku;
		cout << kierunek << endl << endl;
		do {
			for (int j = 0; j < n; j++)
			{
				Xopt.f_calls++;
				nowe_wspolrzedne = wspolrzedne;
				nowe_wspolrzedne(0) += (dlugosc_kroku(j, 0) * kierunek(0, 0) + dlugosc_kroku(j, 1) * kierunek(1, 0));
				nowe_wspolrzedne(1) += (dlugosc_kroku(j, 0) * kierunek(0, 1) + dlugosc_kroku(j, 1) * kierunek(1, 1));
				// zapisane [x]
				//			[y]


				if (ff2T(wspolrzedne) > ff2T(nowe_wspolrzedne)) //kierunek nie musi być zgodny z osiami
				{
					wspolrzedne = nowe_wspolrzedne;
					lambda(j)++;
					dlugosc_kroku(j, 0) *= alpha;
					dlugosc_kroku(j, 1) *= alpha;
				}
				else
				{
					dlugosc_kroku(j, 0) *= -beta;
					dlugosc_kroku(j, 1) *= -beta;
					porazki(j)++;
				}

			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			

			i++;
			if (porazki(0) * porazki(1) * lambda(0) * lambda(1))
			{
				matrix wektor1(n, 1, 0.0);
				matrix wektor2(n, 1, 0.0);
				//zmiana bazy dopisać
				x_roznica = poczatkowe_wspolrzedne(0) - wspolrzedne(0);
				y_roznica = poczatkowe_wspolrzedne(1) - wspolrzedne(1);
				poczatkowe_wspolrzedne = wspolrzedne;

				roznica_poczatku_baz(0, 0) = x_roznica;
				roznica_poczatku_baz(1, 0) = y_roznica;
				roznica_poczatku_baz(1, 1) = y_roznica;

				//nowy_kierunek(0, 0) = (kierunek(0, 0) * roznica_poczatku_baz(0, 0) + kierunek(0, 1) * roznica_poczatku_baz(1, 0));
				//nowy_kierunek(0, 1) = (kierunek(0, 0) * roznica_poczatku_baz(0, 1) + kierunek(0, 1) * roznica_poczatku_baz(1, 1));
				//nowy_kierunek(1, 0) = (kierunek(1, 0) * roznica_poczatku_baz(0, 0) + kierunek(1, 1) * roznica_poczatku_baz(1, 0));
				//nowy_kierunek(1, 1) = (kierunek(1, 0) * roznica_poczatku_baz(0, 1) + kierunek(1, 1) * roznica_poczatku_baz(1, 1));

				preNowaBaza = iloczyn_macierzy(kierunek, roznica_poczatku_baz, 2, 2, 2, 2);
				wektor1(0, 0) = preNowaBaza(0, 1);
				wektor1(1, 0) = preNowaBaza(1, 1);
				wektor2(0, 0) = dlugosc_kroku(1, 0);
				wektor2(1, 0) = dlugosc_kroku(1, 1);
				wektor1 = trans(wektor1);
				wektor1 = iloczyn_macierzy(wektor1, wektor2, 1, 2, 2, 1);
				wektor2(0, 0) = wektor2(0, 0) * wektor1(0);
				wektor2(1, 0) = wektor2(1, 0) * wektor1(0);
				//cout << "wektor2: " << endl << wektor2 << endl;
				// to wszystko miało służyć obliczeniu drugiego wektora, ale nie dziala nie wiem czemu
				//dlatego oszukam system :P
				//preNowaBaza(0, 1) -= wektor2(1, 0);
				//preNowaBaza(1, 1) -= wektor2(1, 0);
				preNowaBaza(0, 1) = -preNowaBaza(1, 0);
				preNowaBaza(1, 1) = preNowaBaza(0, 0);


				kierunek = preNowaBaza;
				//cout << endl << endl << "Nowa baza poczatkowa:" << endl << wspolrzedne << endl << endl << endl;
				//cout << kierunek << endl << endl;
				lambda(0) = 0;
				lambda(1) = 0;
				porazki(0) = 0;
				porazki(1) = 0;
			}

			if (i >= Nmax)	break;
			dl_kroku = sqrt(dlugosc_kroku(0, 0) * dlugosc_kroku(0, 0) + dlugosc_kroku(0, 1) * dlugosc_kroku(0, 1));
			//cout << dl_kroku << endl;
			if (dl_kroku < epsilon)
			{
				Xopt.flag = 0;
				break;
			}

		} while (running);//trzeba badać wartości bezwzględne bo krok może być ujemny
		//return x * = x(i)		Xopt?
		Xopt = wspolrzedne;
		Xopt.y = ff2T(wspolrzedne);
		return Xopt;

	}
	catch (string ex_info)
	{
		throw ("solution Rosen(...):\n" + ex_info);
	}
}

solution pen(matrix(*ff)(matrix, matrix, matrix), matrix x0, double c, double dc, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try {
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution pen(...):\n" + ex_info);
	}
}

solution sym_NM(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double beta, double gamma, double delta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution sym_NM(...):\n" + ex_info);
	}
}

solution SD(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution SD(...):\n" + ex_info);
	}
}

solution CG(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution CG(...):\n" + ex_info);
	}
}

solution Newton(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix),
	matrix(*Hf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Newton(...):\n" + ex_info);
	}
}

solution golden(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution golden(...):\n" + ex_info);
	}
}

solution Powell(matrix(*ff)(matrix, matrix, matrix), matrix x0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Powell(...):\n" + ex_info);
	}
}

solution EA(matrix(*ff)(matrix, matrix, matrix), int N, matrix limits, int mi, int lambda, matrix sigma0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution EA(...):\n" + ex_info);
	}
}