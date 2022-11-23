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

#pragma region funkcje_zaprzyjaźnione
	//zwraca wymiary macierzy n oraz m
	friend int* get_size(const matrix&);

	//zwraca długość wektora pionowego n (macierzy nx1) 
	friend int get_len(const matrix&); // throw (string);
#pragma endregion

public:
	//Zmienna typu double, jak również zmienna typu int, jest konwertowana na macierz 1x1!
#pragma region konstruktory
	//tworzy macierz 1x1 o podanej wartości. Jest również wykorzystywanyjako konstruktor konwertujący(zamienia m.in. double i int na matrix)
	matrix(double = 0.0);

	//tworzy macierz nxm, której każdy element jest równy trzeciemu argumentowi
	matrix(int, int, double = 0.0); // throw (string);

	//tworzy macierz nx1 (wektor pionowy) i wypełnia wartościami podanymi w tablicy 1D
	matrix(int, double*); // throw (string);

	//tworzy macierz nxm i wypełnia wartościami podanymi w tablicy 2D
	matrix(int, int, double**); // throw (string);

	//konstruktor kopiujący
	matrix(const matrix&);
	//destruktor
	~matrix();
#pragma endregion

	//Składowe funkcje operatorowe: 
#pragma region operatory
	//operator przypisania
	matrix& operator=(const matrix&);

	//zwraca wskazaną kolumnę macierzy w postaci macierzy nx1 
	//(rezultat zwracany jest przez wartość->użycie operatora nie jest l - wartością)
	matrix operator[](int) const; // throw (string);

	// operatory zwracają wybrany element macierzy(mogą być wykorzystane do konwersji matrix na double)
	double& operator()(int = 0, int = 0); // throw (string);
	double operator()(int = 0, int = 0) const; // throw (string);
#pragma endregion

#pragma region funkcje_składowe
	//wstawia we wskazaną kolumnę wektor pionowy (macierz nx1)
	void set_col(const matrix&, int); // throw (string);

	//wstawia we wskazany wiersz wektor poziomy (macierz 1xm)
	void set_row(const matrix&, int); // throw (string);

	//dodaje do macierzy nową kolumnę i wypełnia ją podaną wartością
	void add_col(double = 0.0);

	//dodaje do macierzy nowywiersz i wypełnia go podaną wartością
	void add_row(double = 0.0);

	//dodaje do macierzy nową kolumnę i wstawia w nią podany wektor pionowy(macierz nx1)
	void add_col(const matrix&); // throw (string);

	//dodaje do macierzy nowy wiersz i wstawie w niego podany wektor poziomu(macierz 1xm)
	void add_row(const matrix&); // throw (string);
#pragma endregion
};

#pragma region globalne_funkcje_operatorowe
//operatory wykonują odpowiednie działanie pod warunkiem zgodności wymiarów macierzy
matrix operator+(const matrix&, const matrix&); // throw (string);
matrix operator-(const matrix&, const matrix&); // throw (string);
matrix operator*(const matrix&, const matrix&); // throw (string);
matrix operator/(const matrix&, const matrix&); // throw (string);

//macierz przeciwna
matrix operator-(const matrix&);

//operatory relacji działają tylko dla macierzy 1x1
bool operator<(const matrix&, const matrix&); // throw (string);
bool operator>(const matrix&, const matrix&); // throw (string);
bool operator<=(const matrix&, const matrix&); // throw (string);
bool operator>=(const matrix&, const matrix&); // throw (string);
bool operator==(const matrix&, const matrix&); // throw (string);
bool operator!=(const matrix&, const matrix&); // throw (string);

//wypisanie macierzy na ekran lub do pliku csv.Podczas wypisywani elementów macierzy, część całkowita oddzielona jest od części		ułamkowej za pomocą zdefiniowanego w linii 13 SEP_SYMBOL
ostream& operator<<(ostream&, const matrix&);

//odczyt macierzy z pliku csv, txt lub klawiatury.Podając elementy macierzy należy pamiętać, że każda liczba musi kończyć się znakiem; Podczas	wprowadzania elementów macierzy, część całkowita może być oddzielona od części ułamkowej za pomocą zdefiniowanego w linii 13 SEP_SYMBOL lub . 
istream& operator>>(istream&, matrix&); // throw (string);
#pragma endregion

#pragma region funkcje_globalne
//tworzy macierz jednostkową nxn 
matrix ident_mat(int = 1); // throw (string);

//tworzy macierz nxm i wypełnia wartościami losowymi z przedziału[0, 1] o rozkładzie jednostajnym
matrix rand_mat(int = 1, int = 1); // throw (string);

//tworzy macierz nxm i wypełnia wartościami	losowymi o standardowym rozkładzie normalnym
matrix randn_mat(int = 1, int = 1); // throw (string);

//zamiana macierzy 1x1 na double
double m2d(const matrix&); // throw (string);

//wyznacznik macierzy
double det(const matrix&); // throw (string);

// macierz odwrotna
matrix inv(const matrix&); // throw (string);

//– macierz transponowana
matrix trans(const matrix&);

//podnosi macierz do potęgi domyślnie 2
matrix pow(const matrix&, int = 2); // throw (string);

//oblicza normę z wektora pionowego (macierzy nx1)
double norm(const matrix&); // throw (string);

//poziome połączenie dwóch macierzy
matrix hcat(const matrix&, const matrix&); // throw (string);

//pionowe połączenie dwóch macierzy
matrix vcat(const matrix&, const matrix&); // throw (string);

//zwraca wskazaną kolumnę macierzy w postaci wektora pionowego(macierzy nx1)
matrix get_col(const matrix&, int); // throw (string);

//zwraca wskazany wiersz macierzy w postaci wektora	poziomego(macierzy 1xm)
matrix get_row(const matrix&, int); // throw (string);
#pragma endregion


