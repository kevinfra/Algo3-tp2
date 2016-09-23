#include "grafos3.h"

using namespace std;

ListAdy::ListAdy(int estaciones, int vias, vector<ABC> recorridos) {
	this->N = estaciones;
	this->M = vias;
    this->adyacencia.resize(estaciones);
	for (int i = 0; i < vias; ++i)
	{
		ABC recorrido = recorridos[i];
		int nroNodo = get<0>(recorrido);
		t_node nodo;
		nodo.first = get<1>(recorrido);
		nodo.second = get<2>(recorrido);
		agregarArista(nroNodo, nodo);
	}
}

void ListAdy::agregarArista(int nroNodo, t_node nodo) {
    this->adyacencia[nroNodo].push_back(nodo);
}
    
salida dijkstra() {
    vector<int> distancias(this->N, INFINITO);
    distancias[0] = 0;
    set< pair<int,int> > noVisitados; //lista ordenada de (prioridad, nroNodo)
    noVisitados.insert( {0, 0} );
        
    while (!noVisitados.empty()) {
        int nroNodo = noVisitados.begin()->second;
        if (nroNodo == (this->N) - 1) {
        	return distancias[nroNodo];
        }

        noVisitados.erase(noVisitados.begin());

        for (t_node vecino : this->adyacencia[nroNodo]) { //vecino = (nroNodo, peso)
            if (distancias[vecino.first] > distancias[nroNodo] + vecino.second) {
        		
        		t_node nodoAnterior = { distancias[vecino.first], vecino.first };
                noVisitados.erase(nodoAnterior);

                distancias[vecino.first] = distancias[nroNodo] + vecino.second;

                t_node nodoNuevo = { distancias[vecino.first], vecino.first };
                noVisitados.insert(nodoNuevo);
            }
        }
    }
    return INT_MAX;
}