#include <iostream>
#include <string>
#include "./Grafo.h"
#include "./No.h"

using namespace std;

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

    //exibe o n� e suas arestas no terminal
    for(No *p = primeiroNo; p != NULL; p = p->getProxNo()){
        cout << p->getIdNo();
        if(p->getPrimeiraAresta() != NULL){
            p->imprimeArestas();
        }
        cout << "\n";
    }
}

void Grafo::insereNo(int id){

    //impede inser��o de n�s duplicados
    if(verificaExistenciaNo(id)){
        return;
    }

    //inicializa n�
    No *p = new No();
    p->setIdNo(id);
    p->setProxNo(NULL);

    if(primeiroNo != NULL){
        No *q = primeiroNo;                 //navega at� o �ltimo n� para inserir o novo
        while(q->getProxNo() != NULL)
            q = q->getProxNo();

        q->setProxNo(p);
    }else{
        primeiroNo = p;                     //insere como primeiro no caso de o grafo n�o ter n�s
    }
}

void Grafo::insereArestaGrafo(int idOrigem, int idDestino, int pesoAresta){

    //verifica se os n�s necess�rios existem
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

        if(getGrafoDirecionado() == 0){                         //se o grafo n�o for direcionado, insere a aresta no sentido oposto
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









