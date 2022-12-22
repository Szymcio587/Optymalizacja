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

matrix ff3T(matrix x1, matrix ud1, matrix ud2);

/* find the index of the largest value */
int vg_index(matrix f, int vg, int n);
/* find the index of the smallest value */
int vs_index(matrix f, int vs, int n);
/* find the index of the second largest value */
int vh_index(matrix f, int vh, int vg, int n);
/* calculate the centroid */
void centroid(matrix vm, matrix v, int n, int vg);

matrix df3(double t, matrix Y, matrix ud1, matrix ud2);
matrix ff3R(matrix X, matrix ud1, matrix ud2);