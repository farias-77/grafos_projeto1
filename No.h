#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include "./Aresta.h"

class No{

public:
    No();
    ~No();

    //M�todos para o n� como parte da lista encadeada Grafo
    int getIdNo(){return idNo;};
    void setIdNo(int id){idNo = id;};
    No* getProxNo(){return proxNo;};
    void setProxNo(No *p){proxNo = p;};

    //M�todos para o n� como in�cio da lista encadeada de Arestas
    void insereArestaNo(int destino, int peso);
    void imprimeArestas();
    Aresta* getPrimeiraAresta(){return primeiraAresta;};

private:
    int idNo;
    No* proxNo;
    Aresta* primeiraAresta;
};

#endif // NO_H_INCLUDED
