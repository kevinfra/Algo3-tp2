#include <grafosEj1.h>

Grafo::Grafo(int n){
    this->nodosTotales = n;
    for (int i = 0; i < n; ++i){
      std::vector<int> listaNodoI;
      this->adyacencia.push_back(listaNodoI);
    }
}

void Grafo::agregarArista(int u, int v){
    this->adyacencia[u].push_back(v);
}

int Grafo::BFS(int s, int t){
  int res = -1;
  std::queue<int> cola;
  int distancias[this->nodosTotales];
  //inicializo distancias en negativo ya que no se puede usar "infinito"
  for (int i = 0; i < this->nodosTotales; ++i){
    distancias[i] = -1;
  }

  cola.push(s);
  distancias[s] = 0;
  while (!cola.empty()) {
    int tope = cola.front();
    cola.pop();
    if (tope == t) {
      return distancias[t];
    }
    for (int nroVecino = 0; nroVecino < this->adyacencia[tope].size(); ++nroVecino){
      if (distancias[this->adyacencia[tope][nroVecino]] < 0){
        distancias[this->adyacencia[tope][nroVecino]] = distancias[tope] + 1;
        cola.push(this->adyacencia[tope][nroVecino]);
      }
    }
  }
  return res;
}