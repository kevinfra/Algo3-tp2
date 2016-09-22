#include "grafos3.h"

using namespace std;

ListAdy::ListAdy(int n) {
    this->nodosTotales = n;
    vector< vector < int > > listaAd(n);
    this->adyacencia = listaAd;
}

void ListAdy::gregarArista(int nroNodo, t_node nodo) {
    this->adyacencia[nroNodo].push_back(nodo);
}



salida ejercicio3 (int N, int M, vector<ABC> vias)
{

} 

void dijkstra(grafo g, nodo s) {
	vector<int> distancias;
	for (int i = 0; i < g.cantVectores; ++i)
	{
		distancias.push_back(INFINITO);
	}
	set< vector<int> , nodo> noVisitados;
	while (v = g.vectores) {
		if (v.nodo != s) {
			noVisitados.add(v);
		}
	}
	noVisitados.encolar((0, s));
	dist[s] = 0;

	while (!noVisitados.empty()) {
		p = noVisitados.extraerMin();
		for (int i = 0; i < g.vecinos(p); ++i)
		{
			q = g.vecinos(p)[i];

			if (distancias[q] > distancias[p] + costo(p, q)) {
				distancias[q] = distancias[p] + costo(p, q);
				noVisitados.actualizarPrio(q, distancias[q]);
			}
		}
	}
}