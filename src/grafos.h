#include <vector>

namespace Grafos {
    class Nodos;
}

class Nodos{
    public:
        char color;
        Nodos* antecesor;
        bool esPared;
        int paredesRotas;
        int distanciaAlOrigen;
        Nodos(bool esPared);
        ~Nodos();


    private:
};