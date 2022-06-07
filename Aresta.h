#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

class Aresta{

public:
    Aresta(){};
    ~Aresta(){};

    int getDestinoAresta(){return destinoAresta;};
    void setDestinoAresta(int destino){destinoAresta = destino;};

    int getPesoAresta(){return pesoAresta;};
    void setPesoAresta(int peso){pesoAresta = peso;};

    Aresta* getProxAresta(){return proxAresta;};
    void setProxAresta(Aresta *p){proxAresta = p;};

private:
    int destinoAresta;
    int pesoAresta;
    Aresta *proxAresta;
};

#endif // ARESTA_H_INCLUDED
