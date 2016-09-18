#include <iostream>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atol */
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <chrono>
#include <random>
#include <grafos.h>

using namespace std;

static chrono::time_point<chrono::high_resolution_clock> start_time;

void start_timer() {
	start_time = chrono::high_resolution_clock::now();
}

double stop_timer() {
	chrono::time_point<chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();
	return double(chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count());
}


struct arista {
	int inicio;
	int fin;
	int costo;
	
	bool operator<(const arista a) const
	{
		if (costo != a.costo)
			return costo > a.costo;
		if (inicio != a.inicio)
			return inicio > a.inicio;
		return fin > a.fin;
	}
};


int main(int argc, char *argv[]) {
	int numeroDeEjercicio = 0;
	bool experimentos = false;
	if (argc == 2) {
		numeroDeEjercicio = atoi(argv[1]);
	}
	else if (argc == 3) {
		numeroDeEjercicio = atoi(argv[1]);
		string exp = argv[2];
		if (exp == "-exp") {
			experimentos = true;
		}
	}
	else {
		cout << "Modo de uso: \n tp1 numeroDeEjercicio \n Opcional luego del numero de ejercicio: " << endl;
		cout << "   -exp para experimentos" << endl;
		return -1;
	}


	if (!experimentos)
		cout << "Corriendo ejercicio numero " << numeroDeEjercicio << endl;

	if (numeroDeEjercicio == 1) {
		if (!experimentos) {
			int f, c, p;
			cout << "Ingrese Filas, columnas y #paredes que pueden derribarse" << endl;
			cin >> f;
			cin >> c;
			cin >> p;
			cout << "ingresar en las siguientes " << f << " filas los chars '.' para indicar camino," << endl;
			cout << "'#' para indicar pared, 'o' para inicio y 'x' para destino. El largo de las filas debe ser " << c << endl;
			const int tamArray = c*f;
			int matrizPlana[tamArray];
			char paseOPared;
			for (int i = 0; i < tamArray && (cin >> paseOPared); ++i) {
				matrizPlana[i] = paseOPared;
			}
			vector< vector< Grafos::Nodos > > listaDeAd();
			for (int indiceFilas = 0; indiceFilas < f; ++indiceFilas){
				// switch indiceFilas:
				
				// listaDeAd[indiceFilas].push_back();
			}


		}
		else {

		}
	}
	else if (numeroDeEjercicio == 2) {
		if (!experimentos) {
			// int f, c;
			// cout << "Ingrese Filas, columnas Kevin" << endl;
			// cin >> f;
			// cin >> c;
			// cout << "ingresar en las siguientes " << f << " filas los chars '.' para indicar camino," << endl;
			// cout << "'#' para indicar pared indestructuble, un num natural para indicar esfuerzo para romper la pared. El largo de las filas debe ser " << c << endl;
			// int filasReal = f + 2;
			// int columnasReal = c + 2;
			// int matriz[filasReal][columnasReal]
			// char caminoPared;

			// for (int i = 0; i < filasReal; ++i) {
			// 	for (int j = 0; j < columnasReal + 2; ++j) {
			// 		if (j == 0 || i == 0 || j == filasReal - 1 || i == columnasReal - 1 || ){
			// 			matriz[i][j] = '#';						
			// 		} else {
			// 			matriz[i][j] = (cin >> caminoPared);	
			// 		}			
			// 	}
			// }
			

			// vector<arista> aristas;
			// for (int iFilas = 1; iFilas < f; ++iFilas) {
			// 	for (int iColumnas = 1;  iColumnas < c; ++iColumnas) {
			// 		if (matriz[iFilas][iColumnas + 1] == '.') {
						
			// 		}

			// 	}
			// }


		}
		else {

		}
	}
	else if (numeroDeEjercicio == 3) {

		if (!experimentos){

		}
		else{

		}
	}
	else {
		cout << "numero de ejercicio no valido!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		return -1;
	}
	return 0;
}




