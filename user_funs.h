#pragma once

#include"ode_solver.h"
//funkcja jaœka
matrix iloczyn_macierzy(matrix, matrix, int, int, int, int);

matrix ff1T(matrix, matrix = NAN, matrix = NAN);
matrix ff1R(matrix, matrix = NAN, matrix = NAN);
matrix df1(double, matrix, matrix = NAN, matrix = NAN);

matrix ff2T(matrix x, matrix = NAN, matrix = NAN);
matrix ff2R(matrix x, matrix = NAN, matrix = NAN);
matrix df2(double, matrix, matrix = NAN, matrix = NAN);


