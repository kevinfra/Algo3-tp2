#include "grafos3.h"

using namespace std;
using namespace grafos3;

ListAdy::ListAdy(int estaciones, int vias, vector<ABC> recorridos) {
	this->N = estaciones;
	this->M = vias;
    this->adyacencia.resize(estaciones);
	for (uint i = 0; i < recorridos.size(); ++i)
	{
		ABC recorrido = recorridos[i];
		int nroNodo = get<0>(recorrido) - 1; //nroNodo
		t_node vecino = { get<1>(recorrido) - 1, get<2>(recorrido) }; //nodo vecino, costo en llegar
		this->adyacencia[nroNodo].push_back(vecino);
	}
}

salida ListAdy::dijkstra() {
	salida salida1;
    vector<int> distancias(this->N, INFINITO);
    vector<int> antecesores(this->N, INFINITO);
    distancias[0] = 0;
    set< pair<int,int>, Cmp > noVisitados; //lista ordenada de (prioridad, nroNodo


    noVisitados.insert( {0, 0} );
        
    while (!noVisitados.empty()) {

        int nroNodo = noVisitados.begin()->second;

        if (nroNodo == this->N - 1) break;

        noVisitados.erase(noVisitados.begin());

        for (t_node vecino : this->adyacencia[nroNodo]) { //vecino = (nroNodo, peso)

            if (distancias[vecino.first] > distancias[nroNodo] + vecino.second) { 
            //peso de llegar al vecino (que ya tenia) > peso de llegar al nodo actual + peso del vecino

        		t_node nodoAnterior = { distancias[vecino.first], vecino.first };

                noVisitados.erase(nodoAnterior);

                distancias[vecino.first] = distancias[nroNodo] + vecino.second;

                t_node nodoNuevo = { distancias[vecino.first], vecino.first };
                
                noVisitados.insert(nodoNuevo);

                antecesores[vecino.first] = nroNodo;
            }
        }
    }

    salida1.T = -1;
    int distanciaFinal = distancias[(this->N) - 1];
    if (distanciaFinal != INFINITO) {
    	salida1.T = distanciaFinal;

        int iNodo = this->N - 1;
        salida1.S = 1;
        
        while (iNodo > 0) {
            salida1.escape.insert(salida1.escape.begin(), iNodo + 1);
            iNodo = antecesores[iNodo];
            
            salida1.S++;
        }
        salida1.escape.insert(salida1.escape.begin(), 1);
    }

    return salida1;
}