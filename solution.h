//Ten plik nie powinien byæ edytowany

#pragma once

#include"ode_solver.h"

class solution
{
public:
#pragma region sk³adowe_obiektu
	//macierz(najczêœciej nx1) zawieraj¹ca wspó³rzêdne punktu stanowi¹ce rozwi¹zanie
	matrix x;

	//– macierz (najczêœciej 1x1) zawieraj¹ca wartoœæ funkcji celu w punkcie x
	matrix y;

	// macierz nx1 zawieraj¹ca gradient funkcji celu w punkcie x
	matrix g;

	// macierz nxn zawieraj¹ca hesjan funkcji celu w punkcie x
	matrix H;

	//used data – macierz do dyspozycji u¿ytkownika (used data) 
	matrix ud;

	//liczba ca³kowita zawieraj¹ca informacjê o przyczynie zakoñczenia poszukiwania minimum funkcji celu.
	int flag;

	//zmienna statyczna zawieraj¹ca liczbê wywo³añ funkcji celu
	static int f_calls;

	//zmienna statyczna zawieraj¹ca liczbê obliczeñ gradientu funkcji celu
	static int g_calls;

	//zmienna statyczna zawieraj¹ca liczbê obliczeñ hesjanu funkcji celu 
	static int H_calls;
#pragma endregion

	//funkcja statyczna zeruj¹ca zmienne f_calls, h_calls oraz H_calls
	static void clear_calls();

#pragma region konstruktory
	//tworzy rozwi¹zanie o przes³anej wspó³rzêdnej
	solution(double = NAN);

	// tworzy rozwi¹zanie o przes³anych wspó³rzêdnych
	solution(const matrix&);

	//tworzy rozwi¹zanie o przes³anych wspó³rzêdnych
	solution(int, double*); // throw (string);

	//konstruktor kopiuj¹cy (macierz ud nie jest kopiowana je¿eli w	obiekcie wzorcowym ud(0, 0) ma wartoœæ NAN)
	solution(const solution&);
#pragma endregion

	//operator przypisania (macierz ud nie jest	przypisywana je¿eli w obiekcie wzorcowym ud(0, 0) ma wartoœæ NAN)
	solution& operator=(const solution&);

#pragma region funkcje_sk³adowe
	//funkcja wyznacza wartoœæ zmiennej y poprzez wywo³anie funkcji, której adres jest pierwszym argumentem oraz zwiêksza f_calls
	matrix fit_fun(matrix(*)(matrix, matrix, matrix), matrix = NAN, matrix = NAN); // throw (string);

	//funkcja wyznacza wartoœæ zmiennej g poprzez wywo³anie funkcji, której adres jest pierwszym argumentem oraz zwiêksza g_calls
	matrix grad(matrix(*)(matrix, matrix, matrix), matrix = NAN, matrix = NAN); // throw (string);

	//funkcja wyznacza wartoœæ zmiennej H poprzez wywo³anie funkcji, której adres jest pierwszym argumentem oraz zwiêksza H_calls
	matrix hess(matrix(*)(matrix, matrix, matrix), matrix = NAN, matrix = NAN); // throw (string);
#pragma endregion

};

//funkcja zwraca d³ugoœæ wektora (macierzy nx1) x
int get_dim(const solution&); // throw (string);

//wypisanie rozwi¹zania na ekran (wartoœci g_calls i H_calls s¹ wypisywane tylko wtedy, gdy s¹ wiêksze od 0).
ostream& operator<<(ostream&, const solution&);