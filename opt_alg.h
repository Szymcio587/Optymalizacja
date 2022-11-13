//Ten plik nie powinien byæ edytowany

#pragma once

#include"solution.h"
//x0 punkt starowy
//d odleg³oœæ poszukiwania kolejnego kroku (zaczynamy w prawo)
//alpha wspólczynnik ekspansji, alpha > 1
//algorytm szuka kolejnych punktów w prawo od x0
//jeœli wartoœæ w kolejnym punkcie jest za du¿a lub równa tej z poprzedniego punktu: poszukiwanie przedzia³u siê koñczy, zwrócone s¹ ostatnie dwa z trzech badanych punktów (xi-1, xi, xi+1). output zale¿y od wzajemnych relacji wartoœci funkcji w tych punktach
//je¿eli w pierwszej iteracji krok w prawo jest wiêkszy ni¿ f(x0) algorytm poszukuje punktu na lewo od x0
double* expansion(matrix(*ff)(matrix, matrix, matrix), double x0, double d, double alpha, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);
//metoda oparta o z³oty podzia³
//a i b to punkty pocz¹tkowe przedzia³u
//epsilon jest najwiêksz¹ akceptowaln¹ d³ugoœci¹ przedzia³u
//cel funkcji: znaleŸæ przedzia³ poszukiwañ, którego d³ugoœæ jest mniejsza ni¿ epsilon
//wartoœæ zwracana: x optymalny znajduj¹cy siê w granicach znalezionego przedzia³u. 
solution fib(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);
//a,b pocz¹tkowy przedzia³ poszukiwañ
//epsilon minimalny przedzia³ poszukiwañ
//gamma minimalna ró¿nica wartoœci punktu interpolowanego i zak³adanego minimum
//dzia³anie: tworzony jest punkt c bêd¹cy w po³owie odleg³oœæi ab
//przez punkty a c b przeprowadzamy parabolê
//punkt d jest minimum paraboli przeprowadzonej przez punkty  a c b ( a < c < b )
//liczona jest waroœæ funkcji w punktach c, d, nastepnie wartoœci s¹ porównywane
//je¿eli f(d)<f(c) zamieniamy koniec przedzia³u (b) na punkt c i punkt c na punkt d  //b->c, c->d
//ponownie tworzymy parabolê etc
//przypisywanie ró¿ni siê w zale¿noœci od porównania
solution lag(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, double gamma, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);

solution HJ(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double epsilon, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);
solution HJ_trial(matrix(*ff)(matrix, matrix, matrix), solution XB, double s, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);
solution Rosen(matrix(*ff)(matrix, matrix, matrix), matrix x0, matrix s0, double alpha, double beta, double epsilon, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);

solution pen(matrix(*ff)(matrix, matrix, matrix), matrix x0, double c, double dc, double epsilon, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);
solution sym_NM(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double beta, double gamma, double delta, double epsilon, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);

solution SD(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);
solution CG(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);
solution Newton(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix(*Hf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);
solution golden(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);

solution Powell(matrix(*ff)(matrix, matrix, matrix), matrix x0, double epsilon, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);

solution EA(matrix(*ff)(matrix, matrix, matrix), int N, matrix limits, int mi, int lambda, matrix sigma0, double epsilon, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);

