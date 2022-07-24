#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "No.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    void setNumNos(int num){numNos = num;};

    int getGrafoDirecionado(){return grafoDirecionado;};
    int getPesoArestas(){return pesoArestas;};
    int getPesoNos(){return pesoNos;};
    int getNumNos(){return numNos;};

    No* getNo(int id);

    std::vector<int> itemA_fechoTransitivoDireto(int id);
    std::vector<int> itemB_fechoTransitivoIndireto(int id);
    float itemC_coefAgrupLocal(int id);
    float itemD_coefAgrupMedio();
    std::vector<int> itemE_caminhoMinimoDijkstra(int idVertice1, int idVertice2);
    void caminhamentoEmProfundidade(int id, std::vector<int>&visitados);

private:
    int grafoDirecionado;
    int pesoArestas;
    int pesoNos;
    int numNos;
    No* primeiroNo;
};

#endif // GRAFO_H_INCLUDED
