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
#include <grafos2.h>
#include <ejercicio1.h>
#include <grafosEj3.h>

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
		cout << "Modo de uso: \n tp2 numeroDeEjercicio \n Opcional luego del numero de ejercicio: " << endl;
		cout << "   -exp para experimentos" << endl;
		return -1;
	}


	if (!experimentos)
		cout << "Corriendo ejercicio numero " << numeroDeEjercicio << endl;

	if (numeroDeEjercicio == 1) {
		if (!experimentos) {
			int f, c, p;
			cout << "Ingrese filas, columnas y el numero de las paredes que pueden derribarse" << endl;
			cin >> f;
			cin >> c;
			cin >> p;
			cout << "ingresar en las siguientes " << f << " filas los chars '.' para indicar camino," << endl;
			cout << "'#' para indicar pared, 'o' para inicio y 'x' para destino. El largo de las filas debe ser " << c << endl;
			//Falta transformar entrada a grafo

			Grafos::ListaAdy grafo(c*f*p);
			int s, t;
			parserEj1(f, c, p, grafo, s, t);
			int caminoMinimo = grafo.BFS(s, t);
			if (caminoMinimo == -1){
				cout << -1 << endl;
			}
			else {
				cout << "El camino mínimo tiene distancia: " << caminoMinimo << endl;
			}

		}
		else {

		}
	}
	else if (numeroDeEjercicio == 2) {
		if (!experimentos) {
			int f, c;
			cout << "Ingrese Filas, columnas:" << endl;
			cin >> f;
			cin >> c;
			cout << "Ingresar en las siguientes " << f << " filas los chars '.' para indicar camino," << endl;
			cout << "'#' para indicar pared indestructuble, un num natural para indicar esfuerzo para romper la pared. El largo de las filas debe ser " << c << endl;
			int filasReal = f;
			int columnasReal = c;
			char matriz[filasReal][columnasReal];
			char caminoPared;

			for (int i = 0; i < filasReal; ++i) { //Para este entonces, asumo que aquellas paredes indestructibles, seran pasadas como #.
				for (int j = 0; j < columnasReal; ++j) {
						(cin >> caminoPared);	
						matriz[i][j] = caminoPared;			
				}
			}

			vector<arista> aristas;
			for (int iFilas = 0; iFilas < filasReal; ++iFilas) {
				for (int iColumnas = 0; iColumnas < columnasReal; ++iColumnas) {
					if (matriz[iFilas][iColumnas] == '.') {	
						if (matriz[iFilas][iColumnas + 1] != '#') {
							arista a;
							a.inicio = iFilas * columnasReal + iColumnas;
							a.fin = iFilas * columnasReal + iColumnas + 1;
							a.costo = 0;
							aristas.push_back(a);
						}

						if (matriz[iFilas + 1][iColumnas] != '#') {
							arista a;
							a.inicio = iFilas * columnasReal + iColumnas;
							a.fin = (iFilas + 1) * columnasReal + iColumnas;
							a.costo = 0;
							aristas.push_back(a);
						}
					}
					
					if (esNumero(matriz[iFilas][iColumnas])) {
						bool puseNumero = false;
						if (matriz[iFilas][iColumnas + 1] != '#' && !esNumero(matriz[iFilas][iColumnas + 1])) {
							arista a;
							a.inicio = iFilas * columnasReal + iColumnas;
							a.fin = iFilas * columnasReal + iColumnas + 1;
							a.costo = matriz[iFilas][iColumnas] - '0';
							aristas.push_back(a);
							puseNumero = true;
						} 
						if (matriz[iFilas + 1][iColumnas] != '#' && !esNumero(matriz[iFilas + 1][iColumnas])) {
							arista a;
							a.inicio = iFilas * columnasReal + iColumnas;
							a.fin = (iFilas + 1) * columnasReal + iColumnas;
							a.costo = 0;
							if(!puseNumero)
								a.costo = matriz[iFilas][iColumnas] - '0';
							aristas.push_back(a);
						}
					}
				}
			}

			int res = 0;

			if(aristas.size() == 0){
				res = -1;
				cout << res << endl;
			}
			else{
				int V = f*c;
				init(V);
				vector<arista> solucion;
				sort(aristas.begin(), aristas.end()); // ordeno las aristas por costo de menor a mayor


				for (uint i = 0; i < aristas.size(); i++) {
					arista a = aristas[i];
					if (find(a.inicio) != find(a.fin)) {
						solucion.push_back(a);
						uni(a.inicio, a.fin);
					}
				}
				
				for (int i = 0; i < solucion.size(); ++i)
				{
					res += solucion[i].costo;
				}

				cout << res << endl;
			}
		}
		else {
		}
	}
	else if (numeroDeEjercicio == 3) {

		if (!experimentos){
			// int n, m;
			// cout << "Ingrese la cantidad de estaciones y la cantidad de vias" << endl;
			// cin >> n;
			// cin >> m;
			// cout << "ingresar en las siguientes " << n << " filas los chars '.' para indicar camino," << endl;
			// cout << "'#' para indicar pared, 'o' para inicio y 'x' para destino. El largo de las filas debe ser " << m << endl;
			// const int tamArray = m*3;
			// int matrizPlana[tamArray];
			// int estacionODistancia;
			// for (int i = 0; i < tamArray && (cin >> estacionODistancia); ++i) {
			// 	matrizPlana[i] = estacionODistancia;
			// }
			// vector< vector< Ej3::Nodos > > listaDeAd();
			// for (int indiceColumnas = 0; indiceColumnas < m; ++indiceColumnas){
			// 	for (int indiceFilas = 0; indiceFilas < 3; ++indiceFilas){
					
			// 	}
			// }
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
