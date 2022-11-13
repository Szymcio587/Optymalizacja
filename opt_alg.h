//Ten plik nie powinien by� edytowany

#pragma once

#include"solution.h"
//x0 punkt starowy
//d odleg�o�� poszukiwania kolejnego kroku (zaczynamy w prawo)
//alpha wsp�lczynnik ekspansji, alpha > 1
//algorytm szuka kolejnych punkt�w w prawo od x0
//je�li warto�� w kolejnym punkcie jest za du�a lub r�wna tej z poprzedniego punktu: poszukiwanie przedzia�u si� ko�czy, zwr�cone s� ostatnie dwa z trzech badanych punkt�w (xi-1, xi, xi+1). output zale�y od wzajemnych relacji warto�ci funkcji w tych punktach
//je�eli w pierwszej iteracji krok w prawo jest wi�kszy ni� f(x0) algorytm poszukuje punktu na lewo od x0
double* expansion(matrix(*ff)(matrix, matrix, matrix), double x0, double d, double alpha, int Nmax, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);
//metoda oparta o z�oty podzia�
//a i b to punkty pocz�tkowe przedzia�u
//epsilon jest najwi�ksz� akceptowaln� d�ugo�ci� przedzia�u
//cel funkcji: znale�� przedzia� poszukiwa�, kt�rego d�ugo�� jest mniejsza ni� epsilon
//warto�� zwracana: x optymalny znajduj�cy si� w granicach znalezionego przedzia�u. 
solution fib(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, matrix ud1 = NAN, matrix ud2 = NAN); // throw (string);
//a,b pocz�tkowy przedzia� poszukiwa�
//epsilon minimalny przedzia� poszukiwa�
//gamma minimalna r�nica warto�ci punktu interpolowanego i zak�adanego minimum
//dzia�anie: tworzony jest punkt c b�d�cy w po�owie odleg�o��i ab
//przez punkty a c b przeprowadzamy parabol�
//punkt d jest minimum paraboli przeprowadzonej przez punkty  a c b ( a < c < b )
//liczona jest waro�� funkcji w punktach c, d, nastepnie warto�ci s� por�wnywane
//je�eli f(d)<f(c) zamieniamy koniec przedzia�u (b) na punkt c i punkt c na punkt d  //b->c, c->d
//ponownie tworzymy parabol� etc
//przypisywanie r�ni si� w zale�no�ci od por�wnania
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

