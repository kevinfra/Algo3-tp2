#include <iostream>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atol */
#include <fstream>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <chrono>
#include <random>
#include <grafos.h>
#include <ejercicio1.h>
#include <ejercicio2.h>
#include <grafos3.h>


using namespace std;

static chrono::time_point<chrono::high_resolution_clock> start_time;

void start_timer() {
	start_time = chrono::high_resolution_clock::now();
}

double stop_timer() {
	chrono::time_point<chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();
	return double(chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count());
}

std::vector< std::vector< char > > cargarMatrizEj1(int c, int f);
std::vector< std::vector< char > > cargarMatrizEj2(int c, int f);

int main(int argc, char *argv[]) {
	int numeroDeEjercicio = 0;
	bool experimentos = false;
	bool random = false;
	if (argc == 2) {
		numeroDeEjercicio = atoi(argv[1]);
	}
	else if (argc == 3) {
		numeroDeEjercicio = atoi(argv[1]);
		string exp = argv[2];
		if (exp == "-exp") {
			experimentos = true;
		}
		if (exp == "-random"){
			random = true;
		}
	}
	else {
		cout << "Modo de uso: \n tp2 numeroDeEjercicio \n Opcional luego del numero de ejercicio: " << endl;
		cout << "   -exp para experimentos" << endl;
		return -1;
	}


	if (!(experimentos || random))
		cout << "Corriendo ejercicio numero " << numeroDeEjercicio << endl;

	if (numeroDeEjercicio == 1) {
		if (!experimentos && !random) {
			int f, c, p;
			cout << "Ingrese filas, columnas y el numero de las paredes que pueden derribarse" << endl;
			cin >> f;
			cin >> c;
			cin >> p;
			cout << "ingresar en las siguientes " << f << " filas los chars '.' para indicar camino," << endl;
			cout << "'#' para indicar pared, 'o' para inicio y 'x' para destino. El largo de las filas debe ser " << c << endl;
			Grafos::ListaAdy grafo(c*f*(p+1));
			int s, t;
			std::vector< std::vector< char > > matriz = cargarMatrizEj1(c, f);
			parserEj1(f, c, p, matriz, grafo, s, t);
			int caminoMinimo = grafo.BFS(s, t, f, c);
			if (caminoMinimo == -1){
				cout << -1 << endl;
			}
			else {
				cout << "El camino mínimo tiene distancia: " << caminoMinimo << endl;
			}
		}
		else if(experimentos){ //modo de uso: -exp <nombreDeArchivoEntrada >nombreDeArchivoSalida
			cout << "----" << endl;
			cout << "todas paredes salvo inicio y final en matriz de 10x10" << endl;
			cout << "---" << endl;
			int f = 10;
			int c = 10;
			std::vector< std::vector< char > > matriz;
			for (int cantidadDeMatrices = 0; cantidadDeMatrices < 5; ++cantidadDeMatrices){
				cout << "----" << endl;
				cout << "mitad paredes en matriz de 10x10" << endl;
				cout << "---" << endl;
				f = 10;
				c = 10;
				matriz = cargarMatrizEj1(c, f);
				for (int p = 0; p < 100; ++p){
					Grafos::ListaAdy grafo(c*f*(p+1));
					for (int j = 0; j < 100; ++j){
						int s,t;
						start_timer();
						parserEj1(f, c, p, matriz, grafo, s, t);
						int caminoMinimo = grafo.BFS(s, t, f, c);
						double tiempo = stop_timer();
						cout << f << " " << c << " " << p << " " << caminoMinimo << " " << tiempo << endl;
					}
				}
			}
			for (int veces = 0; veces < 5; ++veces){
				cout << "----" << endl;
				cout << "matrices random nro " << veces << endl;
				cout << "---" << endl;
				cin >> f;
				cin >> c;
				matriz = cargarMatrizEj1(c, f);
				for (int p = 0; p < 100; ++p){
					Grafos::ListaAdy grafo(c*f*(p+1));
					for (int j = 0; j < 100; ++j){
						int s,t;
						start_timer();
						parserEj1(f, c, p, matriz, grafo, s, t);
						int caminoMinimo = grafo.BFS(s, t, f, c);
						double tiempo = stop_timer();
						cout << f << " " << c << " " << p << " " << caminoMinimo << " " << tiempo << endl;
					}
				}
			}
		}
		else if(random){
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<> tam(3,50);
			uniform_int_distribution<> caracter2(0,1);
			uniform_int_distribution<> caracter3(0,49);
			uniform_int_distribution<> caracter4(0,79);
			for (int veces = 0; veces < 4; ++veces){
				int f = tam(gen);
				int c = tam(gen);
				char puntoOPared[2] = {'.', '#'};
				cout << f << " " << c << endl;
				for (int i = 0; i < f; ++i){
					for (int k = 0; k < c; ++k){
						if(i == 0 && k == 0) cout << 'o';
						else if(i == f-1 && k == c-1) cout << 'x';
						else cout << puntoOPared[caracter2(gen)];
					}
					cout << endl;
				}
			}

		}
	}
	else if (numeroDeEjercicio == 2) {
		if (!experimentos && !random) {
			int filasReal;
			int columnasReal;
			cin >> filasReal;
			cin >> columnasReal;
			cout << "Ingresar en las siguientes " << filasReal << " filas los chars '.' para indicar camino," << endl;
			cout << "'#' para indicar pared indestructuble, un num natural para indicar esfuerzo para romper la pared. El largo de las filas debe ser " << columnasReal << endl;
			vector< vector<char> > matriz = cargarMatrizEj2(columnasReal,filasReal);
			int res = solveEj2(matriz, filasReal, columnasReal);
			cout << res << endl;
		}
		else if(experimentos){ //modo de uso: -exp <nombreDeArchivoEntrada >nombreDeArchivoSalida
			int f;
			int c;
			std::vector< std::vector< char > > matriz;
			for (int veces = 0; veces < 1000; ++veces){
				cin >> f;
				cin >> c;
				matriz = cargarMatrizEj2(c, f);
				for (int repes = 0; repes < 50; ++repes){
					start_timer();
					int res = solveEj2(matriz, f, c);
					double tiempo = stop_timer();
					cout << f << " " << c << " " << res << " " << tiempo << endl;
				}
			}
		}
		else if(random){

			random_device rd;
			mt19937 gen(rd());
			// uniform_int_distribution<> tam(1,100000);
			uniform_int_distribution<> caracter4(0,9);
			uniform_int_distribution<> dame1(0,1);
			char puntoParedONumero[2][10] = {{'#', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
																				{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}};
			for (int veces = 1; veces < 1001; ++veces){
				// int f = tam(gen);
				int f = veces;
				// int c = tam(gen);
				int c = veces;
				char matriz[f][c];
				cout << f << " " << c << endl;
				for (int i = 0; i < f; ++i){
					for (int k = 0; k < c; ++k){
						if(i == 0 || k == 0 || i == f-1 || k == c -1) matriz[i][k] = '#';
						else matriz[i][k] = puntoParedONumero[dame1(gen)][caracter4(gen)];
					}
				}
				for (int i = 0; i < f; ++i){
					for (int k = 0; k < c; ++k){
						int paredes = 0;
						if(i == 0 || k == 0 || i == f-1 || k == c -1) cout << matriz[i][k];
						else if(matriz[i][k] != '.'){
							if(matriz[i][k+1] != '.') paredes++;
							if(matriz[i][k-1] != '.') paredes++;
							if(matriz[i+1][k] != '.') paredes++;
							if(matriz[i-1][k] != '.') paredes++;
							if(paredes == 2) cout << matriz[i][k];
							else cout << '#';
						}
						else if(matriz[i][k] == '.') cout << matriz[i][k];
					}
					cout << endl;
				}
			}

		}
	}
	else if (numeroDeEjercicio == 3) {

		if (!experimentos) {
			int n, m;
			cout << "Ingrese estaciones y vias..." << endl;
			cin >> n >> m;
 
			int viaA;
			int viaB;
			int viaC;
			vector<ABC> vias;
			for (int via = 0; via < m; ++via)
			{
				cout << "Ingrese la vía " << (via + 1) << "..." << endl;
				cin >> viaA >> viaB >> viaC;

				ABC viaCompleta;
				get<0>(viaCompleta) = viaA;
				get<1>(viaCompleta) = viaB;
				get<2>(viaCompleta) = viaC;
				vias.push_back(viaCompleta);
			}
			 	
			grafos3::ListAdy listAdy3(n, m, vias);
			grafos3::salida salida3 = listAdy3.dijkstra();
			cout << "Mínimo tiempo: " << endl;
			cout << salida3.T << endl;

			if (salida3.T > -1)
			{
			 	cout << "Cantidad de estaciones que debe recorrer: " << endl;
			 	cout << salida3.S << endl;
			 	cout << "Forma de escapar lo más rapido posible: " << endl;
			 	for (uint i = 0; i < salida3.escape.size(); ++i)
			 	{
			 		cout << salida3.escape[i] << " ";
			 	}
			 	cout << endl;
			}
		}
		else {

		}
	}
	else {
		cout << "numero de ejercicio no valido!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		return -1;
	}
	return 0;
}


std::vector< std::vector< char > > cargarMatrizEj1(int c, int f){
	std::vector< std::vector< char > > matriz(c);
  for (int i = 0; i < c; ++i){
    matriz[i].resize(f);
  }
  char puntoOPared;
  for (int k = 0; k < f; ++k) {
    for (int i = 0; i < c; ++i){
      std::cin >> puntoOPared;
      matriz[i][k] = puntoOPared;
    }
  }
  return matriz;
}

std::vector< std::vector< char > > cargarMatrizEj2(int c, int f){
	std::vector< std::vector< char > > matriz(f);
  for (int i = 0; i < f; ++i){
    matriz[i].resize(c);
  }
  char puntoOPared;
  for (int k = 0; k < f; ++k) {
  	for (int i = 0; i < c; ++i){
      std::cin >> puntoOPared;
      matriz[k][i] = puntoOPared;
    }
  }
  return matriz;
}