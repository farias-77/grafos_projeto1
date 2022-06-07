#include "./No.h"
#include <iostream>

using namespace std;

No::No(){
    primeiraAresta = NULL;
}

No::~No(){
    Aresta *p = primeiraAresta;

    while(p != NULL){
        primeiraAresta = primeiraAresta->getProxAresta();
        delete p;
        p = primeiraAresta;
    }
}

void No::insereArestaNo(int destino, int pesoAresta){

    //bloqueia multiarestas
    for(Aresta *a = primeiraAresta; a != NULL; a = a->getProxAresta()){
        if(a->getDestinoAresta() == destino){
            return;
        }
    }

    //inicializa aresta
    Aresta *p = new Aresta();
    p->setDestinoAresta(destino);
    p->setProxAresta(NULL);
    p->setPesoAresta(pesoAresta);

    if(primeiraAresta != NULL){
        Aresta *q = primeiraAresta;
        while(q->getProxAresta() != NULL)       //navega at� a �ltima aresta para inserir a nova
            q = q->getProxAresta();

        q->setProxAresta(p);
    }else{
        primeiraAresta = p;                     //insere como primeira no caso de o n� n�o possuir arestas
    }
}

void No::imprimeArestas(){

    //exibe aresta no terminal
    for(Aresta *p = primeiraAresta; p != NULL; p = p->getProxAresta()){
        if(p->getPesoAresta() == -1){
            cout << " - " << p->getDestinoAresta() << "()";
        }else{
            cout << " - " << p->getDestinoAresta() << "(" << p->getPesoAresta() << ")";
        }
    }
}
