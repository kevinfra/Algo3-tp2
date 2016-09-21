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
#include "grafos2.h"

using namespace std;

static chrono::time_point<chrono::high_resolution_clock> start_time;

void start_timer() {
	start_time = chrono::high_resolution_clock::now();
}

double stop_timer() {
	chrono::time_point<chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();
	return double(chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count());
}

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
			int f, c;
			cout << "Ingrese Filas, columnas Kevin" << endl;
			cin >> f;
			cin >> c;
			cout << "ingresar en las siguientes " << f << " filas los chars '.' para indicar camino," << endl;
			cout << "'#' para indicar pared indestructuble, un num natural para indicar esfuerzo para romper la pared. El largo de las filas debe ser " << c << endl;
			int filasReal = f + 2;
			int columnasReal = c + 2;
			char matriz[filasReal][columnasReal];
			char caminoPared;
			long long costoTotal = 0;

			for (int i = 0; i < filasReal; ++i) { //Para este entonces, asumo que aquellas paredes indestructibles, seran pasadas como #.
				for (int j = 0; j < columnasReal; ++j) {
					if (j == 0 || i == 0 || j == filasReal - 1 || i == columnasReal - 1){
						matriz[i][j] = '#';						
					} else {
						(cin >> caminoPared);	
						matriz[i][j] = caminoPared;
					}			
				}
			}
			

			vector<arista> aristas;
			for (int iFilas = 0; iFilas < filasReal; ++iFilas) {
				for (int iColumnas = 0; iColumnas < columnasReal; ++iColumnas) {
					if (matriz[iFilas][iColumnas] == '.') {	
						if (matriz[iFilas][iColumnas + 1] != '#') {
							arista a;
							a.inicio = iColumnas;
							a.fin = iColumnas + 1;
							a.costo = 0;
							aristas.push_back(a);
						}

						if (matriz[iFilas + 1][iColumnas] != '#') {
							arista a;
							a.inicio = iFilas;
							a.fin = iFilas + 1;
							a.costo = 0;
							aristas.push_back(a);
						}
					}
					
					if (esNumero(matriz[iFilas][iColumnas])) {
						bool puseNumero = false;
						if (matriz[iFilas][iColumnas + 1] != '#' && !esNumero(matriz[iFilas][iColumnas + 1])) {
							arista a;
							a.inicio = iColumnas;
							a.fin = iColumnas + 1;
							a.costo = matriz[iFilas][iColumnas] - '0';
							aristas.push_back(a);
							puseNumero = true;
						} 
						if (matriz[iFilas + 1][iColumnas] != '#' && !esNumero(matriz[iFilas + 1][iColumnas])) {
							arista a;
							a.inicio = iFilas;
							a.fin = iFilas + 1;
							a.costo = 0;
							if(!puseNumero)
								a.costo = matriz[iFilas][iColumnas] - '0';
							aristas.push_back(a);
						}
					}
				}
			}

			sort(aristas.begin(), aristas.end()); // ordeno las aristas por costo de mayor a menor
			int camaraMasCara = -1;
			for (uint i = 0; i < aristas.size(); i++) {
				arista a = aristas[i];
				if (find(a.inicio) != find(a.fin)) {
					costoTotal -= a.costo;
					uni(a.inicio, a.fin);
				} 
				else if (camaraMasCara == -1) {
					camaraMasCara = a.costo;
				}
			}
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




