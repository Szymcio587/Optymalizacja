//Ten plik nie powinien byæ edytowany

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

#pragma region funkcje_zaprzyjaŸnione
	//zwraca wymiary macierzy n oraz m
	friend int* get_size(const matrix&);

	//zwraca d³ugoœæ wektora pionowego n (macierzy nx1) 
	friend int get_len(const matrix&); // throw (string);
#pragma endregion

public:
	//Zmienna typu double, jak równie¿ zmienna typu int, jest konwertowana na macierz 1x1!
#pragma region konstruktory
	//tworzy macierz 1x1 o podanej wartoœci. Jest równie¿ wykorzystywanyjako konstruktor konwertuj¹cy(zamienia m.in. double i int na matrix)
	matrix(double = 0.0);

	//tworzy macierz nxm, której ka¿dy element jest równy trzeciemu argumentowi
	matrix(int, int, double = 0.0); // throw (string);

	//tworzy macierz nx1 (wektor pionowy) i wype³nia wartoœciami podanymi w tablicy 1D
	matrix(int, double*); // throw (string);

	//tworzy macierz nxm i wype³nia wartoœciami podanymi w tablicy 2D
	matrix(int, int, double**); // throw (string);

	//konstruktor kopiuj¹cy
	matrix(const matrix&);
	//destruktor
	~matrix();
#pragma endregion

	//Sk³adowe funkcje operatorowe: 
#pragma region operatory
	//operator przypisania
	matrix& operator=(const matrix&);

	//zwraca wskazan¹ kolumnê macierzy w postaci macierzy nx1 (rezultat zwracany jest przez wartoœæ->u¿ycie operatora nie jest l - wartoœci¹)
	matrix operator[](int) const; // throw (string);

	// operatory zwracaj¹ wybrany element macierzy(mog¹ byæ wykorzystane do konwersji matrix na double)
	double& operator()(int = 0, int = 0); // throw (string);
	double operator()(int = 0, int = 0) const; // throw (string);
#pragma endregion

#pragma region funkcje_sk³adowe
	//wstawia we wskazan¹ kolumnê wektor pionowy (macierz nx1)
	void set_col(const matrix&, int); // throw (string);

	//wstawia we wskazany wiersz wektor poziomy (macierz 1xm)
	void set_row(const matrix&, int); // throw (string);

	//dodaje do macierzy now¹ kolumnê i wype³nia j¹ podan¹ wartoœci¹
	void add_col(double = 0.0);

	//dodaje do macierzy nowywiersz i wype³nia go podan¹ wartoœci¹
	void add_row(double = 0.0);

	//dodaje do macierzy now¹ kolumnê i wstawia w ni¹ podany wektor pionowy(macierz nx1)
	void add_col(const matrix&); // throw (string);

	//dodaje do macierzy nowy wiersz i wstawie w niego podany wektor poziomu(macierz 1xm)
	void add_row(const matrix&); // throw (string);
#pragma endregion
};

#pragma region globalne_funkcje_operatorowe
//operatory wykonuj¹ odpowiednie dzia³anie pod warunkiem zgodnoœci wymiarów macierzy
matrix operator+(const matrix&, const matrix&); // throw (string);
matrix operator-(const matrix&, const matrix&); // throw (string);
matrix operator*(const matrix&, const matrix&); // throw (string);
matrix operator/(const matrix&, const matrix&); // throw (string);

//macierz przeciwna
matrix operator-(const matrix&);

//operatory relacji dzia³aj¹ tylko dla macierzy 1x1
bool operator<(const matrix&, const matrix&); // throw (string);
bool operator>(const matrix&, const matrix&); // throw (string);
bool operator<=(const matrix&, const matrix&); // throw (string);
bool operator>=(const matrix&, const matrix&); // throw (string);
bool operator==(const matrix&, const matrix&); // throw (string);
bool operator!=(const matrix&, const matrix&); // throw (string);

//wypisanie macierzy na ekran lub do pliku csv.Podczas wypisywani elementów macierzy, czêœæ ca³kowita oddzielona jest od czêœci		u³amkowej za pomoc¹ zdefiniowanego w linii 13 SEP_SYMBOL
ostream& operator<<(ostream&, const matrix&);

//odczyt macierzy z pliku csv, txt lub klawiatury.Podaj¹c elementy macierzy nale¿y pamiêtaæ, ¿e ka¿da liczba musi koñczyæ siê znakiem; Podczas	wprowadzania elementów macierzy, czêœæ ca³kowita mo¿e byæ oddzielona od czêœci u³amkowej za pomoc¹ zdefiniowanego w linii 13 SEP_SYMBOL lub . 
istream& operator>>(istream&, matrix&); // throw (string);
#pragma endregion

#pragma region funkcje_globalne
//tworzy macierz jednostkow¹ nxn 
matrix ident_mat(int = 1); // throw (string);

//tworzy macierz nxm i wype³nia wartoœciami losowymi z przedzia³u[0, 1] o rozk³adzie jednostajnym
matrix rand_mat(int = 1, int = 1); // throw (string);

//tworzy macierz nxm i wype³nia wartoœciami	losowymi o standardowym rozk³adzie normalnym
matrix randn_mat(int = 1, int = 1); // throw (string);

//zamiana macierzy 1x1 na double
double m2d(const matrix&); // throw (string);

//wyznacznik macierzy
double det(const matrix&); // throw (string);

// macierz odwrotna
matrix inv(const matrix&); // throw (string);

//– macierz transponowana
matrix trans(const matrix&);

//podnosi macierz do potêgi domyœlnie 2
matrix pow(const matrix&, int = 2); // throw (string);

//oblicza normê z wektora pionowego (macierzy nx1)
double norm(const matrix&); // throw (string);

//poziome po³¹czenie dwóch macierzy
matrix hcat(const matrix&, const matrix&); // throw (string);

//pionowe po³¹czenie dwóch macierzy
matrix vcat(const matrix&, const matrix&); // throw (string);

//zwraca wskazan¹ kolumnê macierzy w postaci wektora pionowego(macierzy nx1)
matrix get_col(const matrix&, int); // throw (string);

//zwraca wskazany wiersz macierzy w postaci wektora	poziomego(macierzy 1xm)
matrix get_row(const matrix&, int); // throw (string);
#pragma endregion

