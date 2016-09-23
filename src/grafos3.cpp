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
		this->adyacencia[nroNodo].push_back(nodo);
	}
}

salida dijkstra() {
	salida salida1;
    vector<int> distancias(this->N, INFINITO);
    distancias[0] = 0;
    set< pair<int,int>, Cmp > noVisitados; //lista ordenada de (prioridad, nroNodo)
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

    
    salida1.T = -1;
    int distanciaFinal = distancias[(this->N) - 1];
    if (distanciaFinal != INFINITO)
    	salida1.T = distanciaFinal;

    return salida;
}