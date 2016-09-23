#include <iostream>
#include <algorithm>
#include <vector>
#include <stdbool.h>

using namespace std;

typedef pair<int, int> t_node; //nroNodo, peso

namespace Grafos {
    class ListAdy;
}

class ListAdy {

    public:
	    ListAdy(int estaciones, int vias, vector<ABC> recorridos);  // Constructor
	    void agregarArista(int nroNodo, t_node nodo);
	    salida dijkstra();
    private:
    	int N;
    	int M;
    	vector< vector < int > > adyacencia;
};

typedef tuple<int, int, int> ABC; //Para llegar de A a B tarda C

struct salida {
	int T; //mínimo tiempo para ir de la estación 1 a N, o -1
	int S; //cantidad de estaciones que debe recorrer
	vector<int> escape; //S enteros que indican la forma de escapar lo más rapido posible
}

salida ejercicio3 (int N, int M, vector<ABC> vias); //N estaciones y M vías

struct arista {
	int inicio;
	int fin;
	int costo;
	
	bool operator<(const arista a) const
	{
		if (costo != a.costo)
			return costo < a.costo;
		if (inicio != a.inicio)
			return inicio < a.inicio;
		return fin < a.fin;
	}
};