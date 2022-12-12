//Ten plik nie powinien byæ edytowany

#pragma once

#include"matrix.h"
#include"user_funs.h"
//funkcja rozwi¹zuj¹ca równanie rózniczowe pierwszego rzêdu metod¹ Eulera
//argumenty: wkaŸnik do funkcji zwracaj¹cej matrix o argumentach: (double, matrix, matrix, matrix)
//double t0  - czas pocz¹tkowy 
//double dt - krok czasowy
//double tend - czas koñcowy
//matrix Y0 - warunki pocz¹tkowe
//matrix ud1, matrix ud2
matrix* solve_ode(matrix(*)(double, matrix, matrix, matrix), double, double, double, matrix, matrix = NAN, matrix = NAN); // throw (string);