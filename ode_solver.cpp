//Ten plik nie powinien byæ edytowany

#include"ode_solver.h"

matrix* solve_ode(matrix(*diff)(double, matrix, matrix, matrix), double t0, double dt, double tend, matrix Y0, matrix ud1, matrix ud2)
{
	try
	{
		int N = static_cast<int>(floor((tend - t0) / dt) + 1);//iloœæ podzia³ów czasu
		if (N < 2)
			throw string("matrix* solve_ode(...):\nprzedzial czasu nie jest zdefiniowany poprawnie");
		int* s = get_size(Y0);
		if (s[1] != 1)//warunki pocz¹tkowe
			throw string("matrix* solve_ode(...):\nwarunek poczatkowy musi byc wektorem pionowym");
		int n = s[0];//wiloœæ warunków pocz¹tkowych
		delete[]s;
		//pierwszy wektor jest wektorem iloœci powtórzeñ i czasów dla tego powtórzenia
		//drugi jest macierz¹ wyników iloœæ_warunków_poczatkowych X iloœæ_powtórzeñ
		matrix* S = new matrix[2]{ matrix(N,1), matrix(n,N) };
		S[0](0) = t0;
		for (int i = 0; i < n; ++i)
			S[1](i, 0) = Y0(i);//przyporz¹dkowanie warunków pocz¹tkowych do pierwszej kolumny macierzy
		matrix k1(n, 1), k2(n, 1), k3(n, 1), k4(n, 1);
		for (int i = 1; i < N; ++i)
		{
			//S[1][i-1] zwraca ca³¹ kolumnê o numerze i-1
			S[0](i) = S[0](i - 1) + dt;//wyraz czasu i jest poprzednim powiekszonym
			k1 = dt * diff(S[0](i - 1), S[1][i - 1], ud1, ud2);//liczenie wartoœci funkcji diff
			k2 = dt * diff(S[0](i - 1) + 0.5 * dt, S[1][i - 1] + 0.5 * k1, ud1, ud2);
			k3 = dt * diff(S[0](i - 1) + 0.5 * dt, S[1][i - 1] + 0.5 * k2, ud1, ud2);
			k4 = dt * diff(S[0](i - 1) + dt, S[1][i - 1] + k3, ud1, ud2);
			for (int j = 0; j < n; ++j)//przypisanie nieco skorygowanej sumy jako kolumna tablicy
				S[1](j, i) = S[1](j, i - 1) + (k1(j) + 2 * k2(j) + 2 * k3(j) + k4(j)) / 6;
		}
		S[1] = trans(S[1]);
		return S;
	}
	catch (string ex_info)
	{
		throw ("matrix* solve_ode(...):\n" + ex_info);
	}
}