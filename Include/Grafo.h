#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "No.h"
#include <iostream>
#include <string>

class Grafo{

public:
    Grafo();
    ~Grafo();

    void insereNo(int id);
    void insereArestaGrafo(int idOrigem, int idDestino, int pesoAresta);
    void imprimeGrafo();
    bool verificaExistenciaNo(int id);

    void setGrafoDirecionado(int num){grafoDirecionado = num;};
    void setPesoArestas(int num){pesoArestas = num;};
    void setPesoNos(int num){pesoNos = num;};

    int getGrafoDirecionado(){return grafoDirecionado;};
    int getPesoArestas(){return pesoArestas;};
    int getPesoNos(){return pesoNos;};

    No* getNo(int id);

    int itemC_coefAgrupLocal(int id);

private:
    int grafoDirecionado;
    int pesoArestas;
    int pesoNos;
    No* primeiroNo;
};

#endif // GRAFO_H_INCLUDED
