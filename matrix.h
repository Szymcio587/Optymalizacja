//Ten plik nie powinien by� edytowany

#pragma once

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<random>
#include<chrono>
using namespace std;

#define SEP_SYMBOL ','

class matrix
{
	int n, m;
	double** M;

#pragma region funkcje_zaprzyja�nione
	//zwraca wymiary macierzy n oraz m
	friend int* get_size(const matrix&);

	//zwraca d�ugo�� wektora pionowego n (macierzy nx1) 
	friend int get_len(const matrix&); // throw (string);
#pragma endregion

public:
	//Zmienna typu double, jak r�wnie� zmienna typu int, jest konwertowana na macierz 1x1!
#pragma region konstruktory
	//tworzy macierz 1x1 o podanej warto�ci. Jest r�wnie� wykorzystywanyjako konstruktor konwertuj�cy(zamienia m.in. double i int na matrix)
	matrix(double = 0.0);

	//tworzy macierz nxm, kt�rej ka�dy element jest r�wny trzeciemu argumentowi
	matrix(int, int, double = 0.0); // throw (string);

	//tworzy macierz nx1 (wektor pionowy) i wype�nia warto�ciami podanymi w tablicy 1D
	matrix(int, double*); // throw (string);

	//tworzy macierz nxm i wype�nia warto�ciami podanymi w tablicy 2D
	matrix(int, int, double**); // throw (string);

	//konstruktor kopiuj�cy
	matrix(const matrix&);
	//destruktor
	~matrix();
#pragma endregion

	//Sk�adowe funkcje operatorowe: 
#pragma region operatory
	//operator przypisania
	matrix& operator=(const matrix&);

	//zwraca wskazan� kolumn� macierzy w postaci macierzy nx1 (rezultat zwracany jest przez warto��->u�ycie operatora nie jest l - warto�ci�)
	matrix operator[](int) const; // throw (string);

	// operatory zwracaj� wybrany element macierzy(mog� by� wykorzystane do konwersji matrix na double)
	double& operator()(int = 0, int = 0); // throw (string);
	double operator()(int = 0, int = 0) const; // throw (string);
#pragma endregion

#pragma region funkcje_sk�adowe
	//wstawia we wskazan� kolumn� wektor pionowy (macierz nx1)
	void set_col(const matrix&, int); // throw (string);

	//wstawia we wskazany wiersz wektor poziomy (macierz 1xm)
	void set_row(const matrix&, int); // throw (string);

	//dodaje do macierzy now� kolumn� i wype�nia j� podan� warto�ci�
	void add_col(double = 0.0);

	//dodaje do macierzy nowywiersz i wype�nia go podan� warto�ci�
	void add_row(double = 0.0);

	//dodaje do macierzy now� kolumn� i wstawia w ni� podany wektor pionowy(macierz nx1)
	void add_col(const matrix&); // throw (string);

	//dodaje do macierzy nowy wiersz i wstawie w niego podany wektor poziomu(macierz 1xm)
	void add_row(const matrix&); // throw (string);
#pragma endregion
};

#pragma region globalne_funkcje_operatorowe
//operatory wykonuj� odpowiednie dzia�anie pod warunkiem zgodno�ci wymiar�w macierzy
matrix operator+(const matrix&, const matrix&); // throw (string);
matrix operator-(const matrix&, const matrix&); // throw (string);
matrix operator*(const matrix&, const matrix&); // throw (string);
matrix operator/(const matrix&, const matrix&); // throw (string);

//macierz przeciwna
matrix operator-(const matrix&);

//operatory relacji dzia�aj� tylko dla macierzy 1x1
bool operator<(const matrix&, const matrix&); // throw (string);
bool operator>(const matrix&, const matrix&); // throw (string);
bool operator<=(const matrix&, const matrix&); // throw (string);
bool operator>=(const matrix&, const matrix&); // throw (string);
bool operator==(const matrix&, const matrix&); // throw (string);
bool operator!=(const matrix&, const matrix&); // throw (string);

//wypisanie macierzy na ekran lub do pliku csv.Podczas wypisywani element�w macierzy, cz�� ca�kowita oddzielona jest od cz�ci		u�amkowej za pomoc� zdefiniowanego w linii 13 SEP_SYMBOL
ostream& operator<<(ostream&, const matrix&);

//odczyt macierzy z pliku csv, txt lub klawiatury.Podaj�c elementy macierzy nale�y pami�ta�, �e ka�da liczba musi ko�czy� si� znakiem; Podczas	wprowadzania element�w macierzy, cz�� ca�kowita mo�e by� oddzielona od cz�ci u�amkowej za pomoc� zdefiniowanego w linii 13 SEP_SYMBOL lub . 
istream& operator>>(istream&, matrix&); // throw (string);
#pragma endregion

#pragma region funkcje_globalne
//tworzy macierz jednostkow� nxn 
matrix ident_mat(int = 1); // throw (string);

//tworzy macierz nxm i wype�nia warto�ciami losowymi z przedzia�u[0, 1] o rozk�adzie jednostajnym
matrix rand_mat(int = 1, int = 1); // throw (string);

//tworzy macierz nxm i wype�nia warto�ciami	losowymi o standardowym rozk�adzie normalnym
matrix randn_mat(int = 1, int = 1); // throw (string);

//zamiana macierzy 1x1 na double
double m2d(const matrix&); // throw (string);

//wyznacznik macierzy
double det(const matrix&); // throw (string);

// macierz odwrotna
matrix inv(const matrix&); // throw (string);

//� macierz transponowana
matrix trans(const matrix&);

//podnosi macierz do pot�gi domy�lnie 2
matrix pow(const matrix&, int = 2); // throw (string);

//oblicza norm� z wektora pionowego (macierzy nx1)
double norm(const matrix&); // throw (string);

//poziome po��czenie dw�ch macierzy
matrix hcat(const matrix&, const matrix&); // throw (string);

//pionowe po��czenie dw�ch macierzy
matrix vcat(const matrix&, const matrix&); // throw (string);

//zwraca wskazan� kolumn� macierzy w postaci wektora pionowego(macierzy nx1)
matrix get_col(const matrix&, int); // throw (string);

//zwraca wskazany wiersz macierzy w postaci wektora	poziomego(macierzy 1xm)
matrix get_row(const matrix&, int); // throw (string);
#pragma endregion


