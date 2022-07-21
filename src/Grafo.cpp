#include <iostream>
#include <string>
#include "Grafo.h"

Grafo::Grafo(){
    primeiroNo = NULL;
}

Grafo::~Grafo(){
    No *p = primeiroNo;

    while(p != NULL){
        primeiroNo = primeiroNo->getProxNo();
        delete p;
        p = primeiroNo;
    }
}

void Grafo::imprimeGrafo(){

    //exibe o no e suas arestas no terminal
    for(No *p = primeiroNo; p != NULL; p = p->getProxNo()){
        std::cout << p->getIdNo();
        if(p->getPrimeiraAresta() != NULL){
            p->imprimeArestas();
        }
        std::cout << "\n";
    }
}

void Grafo::insereNo(int id){

    //impede insercao de nos duplicados
    if(verificaExistenciaNo(id)){
        return;
    }

    //inicializa no
    No *p = new No();
    p->setIdNo(id);
    p->setProxNo(NULL);

    if(primeiroNo != NULL){
        No *q = primeiroNo;                 //navega ate o ultimo no para inserir o novo
        while(q->getProxNo() != NULL)
            q = q->getProxNo();

        q->setProxNo(p);
    }else{
        primeiroNo = p;                     //insere como primeiro no caso de o grafo nao ter nos
    }
}

void Grafo::insereArestaGrafo(int idOrigem, int idDestino, int pesoAresta){

    //verifica se os nos necess�rios existem
    if(!verificaExistenciaNo(idOrigem)){
        insereNo(idOrigem);
    }
    if(!verificaExistenciaNo(idDestino)){
        insereNo(idDestino);
    }


    for(No *p = primeiroNo; p != NULL; p = p->getProxNo()){

        if(p->getIdNo() == idOrigem){
            p->insereArestaNo(idDestino, pesoAresta);           //insere a aresta como destino do n� de origem
        }

        if(!getGrafoDirecionado()){                         //se o grafo n�o for direcionado, insere a aresta no sentido oposto
            if(p->getIdNo() == idDestino){
                p->insereArestaNo(idOrigem, pesoAresta);
            }
        }
    }
}

bool Grafo::verificaExistenciaNo(int id){


    for(No *p = primeiroNo; p != NULL; p = p->getProxNo()){
        if(p->getIdNo() == id){
            return true;            //true se encontrar o n� no grafo
        }
    }
    return false;                   //false se o n� n�o existir no grafo
}

No* Grafo::getNo(int id){

    for(No *p = primeiroNo; p != NULL; p = p->getProxNo()){
        if(p->getIdNo() == id){
            return p;
        }
    }
    return NULL;
}

int Grafo::itemC_coefAgrupLocal(int id){

    int Pv = 0;
    int grauNo = 0;
    
    No* p = this->getNo(id);

    for(Aresta *a = p->getPrimeiraAresta(); a != NULL; a = a->getProxAresta()){

        No* n = this->getNo(a->getDestinoAresta());

        for(Aresta *b = p->getPrimeiraAresta(); b != NULL; b = b->getProxAresta()){
            
            No* m = this->getNo(b->getDestinoAresta());

            if(n != m){

                for(Aresta *c = n->getPrimeiraAresta(); c != NULL; c = c->getProxAresta()){
                    
                    if(c->getDestinoAresta() == m->getIdNo()){
                        Pv++;
                    }
                }
            }  
        }
    
        grauNo++;
    }

    if(grafoDirecionado){
        Pv = Pv/2;
    }

    return grauNo/Pv;
}

//fecho transitivo direto
//fecho transitivo indireto
//coef agrupamento local [X]
//coef agrupamento médio do grafo
// dijkstra