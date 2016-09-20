#include <vector>
#include <queue>

namespace Grafos {
    class ListaAdy;
}

class ListaAdy{

    public:
    int nodosTotales;
    std::vector< std::vector < int > > adyacencia;
    ListaAdy(int n);  // Constructor
    void agregarArista(int u, int v);
    int BFS(int s, int t);

};