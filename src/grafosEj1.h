#include <vector>
#include <queue>

namespace Ej1 {
    class Grafo;
}

class Grafo{

    public:
    int nodosTotales;
    std::vector< std::vector < int > > adyacencia;
    Grafo(int n);  // Constructor
    void agregarArista(int u, int v);
    int BFS(int s, int t);

};