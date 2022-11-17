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
	//try
	//{
	//	solution Xopt, XB, XSB, X;
	//	X = x0;
	//	do
	//	{
	//		XB = X;
	//		X = HJ_trial(ff, XB, s, ud1, ud2);
	//		if (ff(X.x, NULL, NULL) < ff2T(XB.x)) {
	//			do
	//			{
	//				XSB = XB;
	//				XB = X;
	//				X.x = 2 * XB.x - XSB.x;
	//				X.y = 2 * XB.y - XSB.y;
	//				X = HJ_trial(ff, XB, s, ud1, ud2);
	//				if (solution::f_calls > Nmax)
	//				{
	//					Xopt = XB;
	//					Xopt.flag = 2;
	//					return Xopt;
	//				}
	//			} while (ff2T(X.x) < ff2T(XB.x));
	//			X = XB;
	//		}
	//		else
	//		{
	//			s *= alpha;
	//		}
	//		if (solution::f_calls > Nmax)
	//		{
	//			Xopt = XB;
	//			Xopt.flag = 1;
	//			return Xopt;
	//		}
	//	} while (s >= epsilon);
	//	Xopt = XB;
	//	return Xopt;
	//}
	//catch (string ex_info)
	//{
	//	throw ("solution HJ(...):\n" + ex_info);
	//}

	try
	{
		solution XB;
		solution X(x0);
		solution Xopt;
		solution XB_old;

		XB = X;
		XB.fit_fun(ff, ud1, ud2);
	
		while (true)
		{
			X = HJ_trial(ff, XB, s);
	
			if (X.y < XB.y)
			{
				while (true)
				{
					XB_old = XB;
					XB = X;
					X.x = 2 * XB.x - XB_old.x;
					X = HJ_trial(ff, X, s);
					if (X.y >= XB.y || solution::f_calls > Nmax) {
						Xopt = XB;
						Xopt.flag = 1;
						break;
					}
				}
			}
			else {
				s = alpha * s;
			}

			if (s < epsilon || solution::f_calls > Nmax) {
				Xopt = XB;
				Xopt.flag = 1;
				break;
			}
		}
	
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution HJ(...):\n" + ex_info);
	}
}

solution HJ_trial(matrix(*ff)(matrix, matrix, matrix), solution XB, double s, matrix ud1, matrix ud2)
{
	//try
	//{
	//	for (int i = 0; i < get_dim(XB); i++)
	//	{
	//		if (ff2T(XB.x + s * pow(M_E, i)) < ff2T(XB.x))
	//			XB.x = XB.x + s * (pow(M_E, i));
	//
	//		else
	//			if (ff2T(XB.x - s * pow(M_E, i)) < ff2T(XB.x))
	//				XB.x = XB.x - s * (pow(M_E, i));
	//	}
	//	return XB;
	//}
	//catch (string ex_info)
	//{
	//	throw ("solution HJ_trial(...):\n" + ex_info);
	//}
	try
	{
		solution XBnew;
		for (int j = 1; j < get_dim(XB); j++)
		{
			XBnew.x = XB.x + s * pow(2.718, j);
			if (XBnew.fit_fun(ff, ud1, ud2) < XB.fit_fun(ff, ud1, ud2))
			{
				XB.x = XBnew.x;
			}
			else
			{
				XBnew.x = XB.x - s * pow(2.718, j);
				if (XBnew.fit_fun(ff, ud1, ud2) < XB.fit_fun(ff, ud1, ud2))
				{
					XB.x = XBnew.x;
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
solution Rosen(matrix(*ff)(matrix, matrix, matrix), matrix x0, matrix s0, double alpha, double beta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
//zrobić macież s żeby przechowywać długości kroków, zrobić macierz lambda na 2xN żeby przechować ilość udanych kroków i macież p(porażek) na nieudane kroki
		bool running = true;//zmienna do kończenia pętli głównej funkcji
		solution Xopt;
		Xopt.f_calls = 0;
		int n = 2;//zbierać wymiar przestrzeni
		int j = n;
		int i = 0;
		matrix d = new matrix(n, 1, 1);
		matrix λ = new matrix(n, 1, 0);//poprawne kroki
		matrix p = new matrix(n, 1, 1);//porażki
		matrix s = s0;
		double* e = { 1, 1 };//baza x, y

		double* xB = {x0(0),x0(1)};
		double x0 = m2d(x0(0));
		double x1 = m2d(x0(1));
		//mamy x0, i s0 jako matrixy - tablice 1xn
		//mamy przesłane alpha, beta, epsilon i Nmax. do tego jest ud1 i ud2

		//punkt startowy x(0), wektor długość kroków s(0), współczynnik ekspansji α > 1,
		//współczynnik kontrakcji 0 < β < 1, dokładność ε > 0, maksymalna liczba wywołań funkcji celu Nmax
		//macierze Q i D odpowiadają obrotowi bazy
		//zapis dj(0) to: tablica d indeks j wyraz 0
		// indeks chyba oznacza oś np X index 1 to Ox, X indeks 2 to Oy
		//wektor e to baza
		d[j] = e[j];	// j = 1, 2, …, n
		λ[j][n] = 0;		// j = 1, 2, …, n
		p[j][n] = 0;	    // j = 1, 2, …, n
		xB = x(0);
			do {
				for (int j = 0; j < n; j++) { //sprawdzaj w każdym kierunku
					if (ff2T(xB + s[j][i] * d[j][i]) < ff2T(xB)) {//przerobić warunek
							xB = xB + s[j][i] * d[j][i];//rozdzielić na współrzędne
							λ[j][i + 1] = λ[j][i] + s[j][i];
							s[j][i + 1] = alpha * s[j][i];
					}
					else {
							s[j][i + 1] = -beta * s[j][i];
							p[j][i + 1] = p[j][i] + 1;
					}
				}
				i = i + 1;
				x(i) = xB;
					//sprawdzaj czy zmiana bazy
					//czy mamy wykonać obrót?
					//tak jeżeli w każdym kierunku nastąpiło i przesunięcie i porażka
				if (λ[j][i] != 0 && p[j][n] != 0) {  // j = 1, 2, …, n
					//zmiana bazy kierunków dj(i); //dopisać rotacje
					λ[j][i + 1] = 0;			// j = 1, 2, …, n
					p[j][i] = 0;			// j = 1, 2, …, n
					s[j][i] = s[j][0];		// j = 1, 2, …, n
				}
				if (Xopt.f_calls > Nmax) { //sprawdzenie czy przekroczono fcalls
					std::cout << "\nzrypalo sie, za dużo iteracji \n";
					Xopt.flag = 666;
					return Xopt;
				}
				Xopt.f_calls++;

				//sprawdzenie czy długość kroku przekroczyła minimum
				for (int dupa_1 = 0; i < n; i++) {
					for (int dupa_2 = 0; j < n; j++) {
						if (abs(m2d(s[dupa_1][dupa_2])) < epsilon) {
							running = false;
						}
					}
				}
			} while (running);//trzeba badać wartości bezwzględne bo krok może być ujemny
		//return x * = x(i)		Xopt?

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