#define _USE_MATH_DEFINES
#include <cmath>
#include"user_funs.h"

matrix fun1(matrix x, matrix ud1, matrix ud2)
{
    matrix y;
    y = -cos(0.1 * x()) * exp(-pow(0.1 * x() - 2 * M_PI, 2)) + 0.002 * pow(0.1 * x(), 2);
    return y;
}

matrix ff1R(matrix x, matrix ud1, matrix ud2)
{
    matrix y;
    matrix Y0 = matrix(3, new double[3] { 5, 1, 10 });
    matrix* Y = solve_ode(df1, 0, 1, 1000, Y0, ud1, x);
    int n = get_len(Y[0]);
    double max = Y[1](0, 2);
    for (int i = 1; i < n; ++i)
        if (max < Y[1](i, 2))
            max = Y[1](i, 2);
    y = abs(max - 50);
    return y;
}

matrix df1(double t, matrix Y, matrix ud1, matrix ud2)
{
    double a = 0.98;
    double b = 0.63;
    double g = 9.81;
    double PA = 0.75;
    double TA = 90;
    double PB = 1;
    double DB = 0.00365665;
    double Fin = 0.01;
    double Tim = 10;

    matrix dY(3, 1);
    double FAout = a * b * m2d(ud2) * sqrt(2 * g * Y(0) / PA);
    double FBout = a * b * DB * sqrt(2 * g * Y(1) / PB);
    if (Y(0) < 0) FAout = 0;
    if (Y(1) < 0) FBout = 0;

    dY(0) = -FAout;
    dY(1) = FAout + Fin - FBout;
    dY(2) = (Fin / Y(1)) * (Tim - Y(2)) + (FAout / Y(1)) * (TA - Y(2));

    return dY;
}

matrix ff2T(matrix x, matrix ud1, matrix ud2)
{
    matrix y;
    y = pow(x(0), 2) + pow(x(1), 2) - cos(2.5 * M_PI * m2d(x(0))) - cos(2.5 * M_PI * m2d(x(1))) + 2;
    return y;
}

matrix ff2R(matrix x, matrix ud1, matrix ud2)
{
    matrix y = 0;//macierz wynikowa
    matrix Y0 = ud2;

    ud1(8, 0) = x(0);
    ud1(9, 0) = x(1);

    //warunki brzegowe s� podane w mainie i przekazane tu przez ud2
    //warunki pocz�tkowe w postaci wektora pionowego o zadanych w {} warto�ciach
    //w ud1 przekazane s� parametry robota podane w instrukcji
    //p�ki co warunki pocz�tkowe s� zdublowane, w poprzednim kodzie by�a tam macierz x jako wektor wsp�rz�dnych, teraz wsp�rz�dne s� cz��i� ud1
    matrix* Y = solve_ode(df2, 0, 1, 1000, Y0, ud1, ud2);

    int n = get_len(Y[0]);//bierze d�ugo�� wektora wynik�w

    double aref = ud1(3, 0);
    double omegaref = 0;
    //double y = 0;
    //liczenie funkcjona�u jako�ci
    for (int i = 0; i < n; i++) {
        y = y + 10 * pow(aref - Y[1](i, 0), 2) + pow(omegaref - Y[1](i, 1), 2) +
            pow(x(0) * (aref - Y[1](i, 0)) + x(1) * (omegaref - Y[1](i, 1)), 2);
    }

    return y;

}

matrix df2(double t, matrix Y, matrix ud1, matrix ud2)
{
    try {
        //getsize(ud2)[0] zwraca d�ugo�� wektora = ilo�ci zmiennych w kroku czasowym
        matrix dY(get_size(ud2)[0], 1);//obliczany w funkcji krok czasowy, kt�ry potem jest zwracany jako wektor

        double aref = ud1(3, 0);//referencyjny ko�cowy k�t ruchu
        double omegaref = 0;//referencyjna ko�cowa pr�dko�� ruchu
        double dt = ud1(6, 0);


        double k1 = ud1(8, 0);	//ud1(8, 0) = x(0);
        double k2 = ud1(9, 0);	//ud1(9, 0) = x(1);

        dY(2) = k1 * (aref - Y(0)) + k2 * (omegaref - Y(1));
        //w ud2 s� pocz�tkowe warto�ci dla alfy i omegi zmieniajace si� w czasie
        //W otrzymywanym z odesolvera wektorze Y s� ostatnie warto�ci alfy, omegii i momentu si�y. w takiej kolejno�ci:
        //Y(0)k�t, Y(1)pr�dko�c ko�cowa, Y(2)przy�o�ony moment si�y, Y(3) warto�� "y" funkcjona�u jako�ci

        //obliczy� nowe alfa i nowe omega
        dY(0) = Y(1);//nowy k�t
        dY(1) = (dY(2) - ud1(5, 0) * Y(1)) / ud1(4, 0);//nowa pr�dko�� k�towa



        //df2 ma si� uruchomi� tylko raz > rozwi�za� rr-> przekaza� wynik do ff
        return dY;
    }
    catch (string ex_info)
    {
        throw ("df2* sie wywalil(...):\n" + ex_info);
    }
}

matrix ff3T(matrix x1, matrix ud1, matrix ud2)
{
    matrix y;
    y = pow(x1(0), 2) + pow(x1(1), 2) - cos(2.5 * 3.14 * x1(0)) - cos(2.5 * 3.14 * x1(1)) + 2;

    return y;
}

/* find the index of the largest value */
int vg_index(matrix f, int vg, int n)
{
    int j;

    for (j = 0; j <= n; j++)
    {
        if (f(j) > f(vg))
            vg = j;
    }
    return vg;
}

/* find the index of the smallest value */
int vs_index(matrix f, int vs, int n)
{
    int j;

    for (j = 0; j <= n; j++)
    {
        if (f(j) < f(vs))
            vs = j;
    }
    return vs;
}

/* find the index of the second largest value */
int vh_index(matrix f, int vh, int vg, int n)
{
    int j;

    for (j = 0; j <= n; j++)
    {
        if (f(j) > f(vh) && f(j) < f(vg))
            vh = j;
    }
    return vh;
}

/* calculate the centroid */
void centroid(matrix vm, matrix v, int n, int vg)
{
    int j, m;
    double cent;

    for (j = 0; j <= n - 1; j++) {
        cent = 0.0;
        for (m = 0; m <= n; m++) {
            if (m != vg) {
                cent += v(m, j);
            }
        }
        vm(j) = cent / n;
    }
}

