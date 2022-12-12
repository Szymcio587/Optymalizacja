//Ten plik nie powinien by� edytowany

#pragma once

#include"matrix.h"
#include"user_funs.h"
//funkcja rozwi�zuj�ca r�wnanie r�zniczowe pierwszego rz�du metod� Eulera
//argumenty: wka�nik do funkcji zwracaj�cej matrix o argumentach: (double, matrix, matrix, matrix)
//double t0  - czas pocz�tkowy 
//double dt - krok czasowy
//double tend - czas ko�cowy
//matrix Y0 - warunki pocz�tkowe
//matrix ud1, matrix ud2
matrix* solve_ode(matrix(*)(double, matrix, matrix, matrix), double, double, double, matrix, matrix = NAN, matrix = NAN); // throw (string);