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
#include <grafos2.h>
#include <ejercicio1.h>
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
			int nodos = 0;
			bool encerrado = false;
			bool encerradoRes = false;

			for (int i = 0; i < filasReal; ++i) { //Para este entonces, asumo que aquellas paredes indestructibles, seran pasadas como #.
				for (int j = 0; j < columnasReal; ++j) {
						(cin >> caminoPared);
						matriz[i][j] = caminoPared;
				}
			} //La entrada es guardada como una matriz.

			vector<arista> aristas;
			for (int iFilas = 0; iFilas < filasReal; ++iFilas) {
				for (int iColumnas = 0; iColumnas < columnasReal; ++iColumnas) {
					if (matriz[iFilas][iColumnas] == '.') {
						nodos++; //Chequeo cuantos nodos hay
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
						encerrado = matriz[iFilas][iColumnas + 1] == '#' && matriz[iFilas + 1][iColumnas] == '#' && matriz[iFilas - 1][iColumnas] == '#' && matriz[iFilas][iColumnas - 1] == '#';
						encerradoRes = encerradoRes || encerrado;
						//Me fijo si hay algun nodo inalcanzable (en el caso de que haya uno solo se contempla con #nodos).
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

			if(nodos == 0 || (nodos > 1 && encerradoRes) ){ //Chequeo que sean todas paredes o haya alguno inalcanzable
				res = -1;
				cout << res << endl;
			}
			else{
				int V = f*c;
				init(V);
				vector<arista> solucion;
				sort(aristas.begin(), aristas.end()); // ordeno las aristas por costo de menor a mayor


				for (uint i = 0; i < aristas.size(); i++) { //Kruskal
					arista a = aristas[i];
					if (find(a.inicio) != find(a.fin)) {
						solucion.push_back(a);
						uni(a.inicio, a.fin);
					}
				}	//Fin Kruskal
				
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