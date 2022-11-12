//Ten plik nie powinien by� edytowany

#pragma once

#include"ode_solver.h"

class solution
{
public:
#pragma region sk�adowe_obiektu
	//macierz(najcz�ciej nx1) zawieraj�ca wsp�rz�dne punktu stanowi�ce rozwi�zanie
	matrix x;

	//� macierz (najcz�ciej 1x1) zawieraj�ca warto�� funkcji celu w punkcie x
	matrix y;

	// macierz nx1 zawieraj�ca gradient funkcji celu w punkcie x
	matrix g;

	// macierz nxn zawieraj�ca hesjan funkcji celu w punkcie x
	matrix H;

	//used data � macierz do dyspozycji u�ytkownika (used data) 
	matrix ud;

	//liczba ca�kowita zawieraj�ca informacj� o przyczynie zako�czenia poszukiwania minimum funkcji celu.
	int flag;

	//zmienna statyczna zawieraj�ca liczb� wywo�a� funkcji celu
	static int f_calls;

	//zmienna statyczna zawieraj�ca liczb� oblicze� gradientu funkcji celu
	static int g_calls;

	//zmienna statyczna zawieraj�ca liczb� oblicze� hesjanu funkcji celu 
	static int H_calls;
#pragma endregion

	//funkcja statyczna zeruj�ca zmienne f_calls, h_calls oraz H_calls
	static void clear_calls();

#pragma region konstruktory
	//tworzy rozwi�zanie o przes�anej wsp�rz�dnej
	solution(double = NAN);

	// tworzy rozwi�zanie o przes�anych wsp�rz�dnych
	solution(const matrix&);

	//tworzy rozwi�zanie o przes�anych wsp�rz�dnych
	solution(int, double*); // throw (string);

	//konstruktor kopiuj�cy (macierz ud nie jest kopiowana je�eli w	obiekcie wzorcowym ud(0, 0) ma warto�� NAN)
	solution(const solution&);
#pragma endregion

	//operator przypisania (macierz ud nie jest	przypisywana je�eli w obiekcie wzorcowym ud(0, 0) ma warto�� NAN)
	solution& operator=(const solution&);

#pragma region funkcje_sk�adowe
	//funkcja wyznacza warto�� zmiennej y poprzez wywo�anie funkcji, kt�rej adres jest pierwszym argumentem oraz zwi�ksza f_calls
	matrix fit_fun(matrix(*)(matrix, matrix, matrix), matrix = NAN, matrix = NAN); // throw (string);

	//funkcja wyznacza warto�� zmiennej g poprzez wywo�anie funkcji, kt�rej adres jest pierwszym argumentem oraz zwi�ksza g_calls
	matrix grad(matrix(*)(matrix, matrix, matrix), matrix = NAN, matrix = NAN); // throw (string);

	//funkcja wyznacza warto�� zmiennej H poprzez wywo�anie funkcji, kt�rej adres jest pierwszym argumentem oraz zwi�ksza H_calls
	matrix hess(matrix(*)(matrix, matrix, matrix), matrix = NAN, matrix = NAN); // throw (string);
#pragma endregion

};

//funkcja zwraca d�ugo�� wektora (macierzy nx1) x
int get_dim(const solution&); // throw (string);

//wypisanie rozwi�zania na ekran (warto�ci g_calls i H_calls s� wypisywane tylko wtedy, gdy s� wi�ksze od 0).
ostream& operator<<(ostream&, const solution&);