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

float Grafo::itemC_coefAgrupLocal(int id){

    // inicializa componentes da equação
    float Pv = 0;                       //pares de vértices adjacentes ao nó analisado com aresta entre si
    float grauNo = 0;
    
    //reconhece nó analisado
    No* p = this->getNo(id);

    //passa por todas as arestas do nó analisado
    for(Aresta *a = p->getPrimeiraAresta(); a != NULL; a = a->getProxAresta()){

        //reconhece destino de cada aresta
        No* n = this->getNo(a->getDestinoAresta());
        
        //passa por todas as arestas do nó analisado para comparar
        for(Aresta *b = p->getPrimeiraAresta(); b != NULL; b = b->getProxAresta()){
            
            //reconhece destino de cada aresta do segundo loop
            No* m = this->getNo(b->getDestinoAresta());
            
            //evita comparação de nós iguais
            if(n != m){

                //verifica se existe aresta entre dois nós adjacentes ao nó analisado 
                for(Aresta *c = n->getPrimeiraAresta(); c != NULL; c = c->getProxAresta()){
                    
                    if(c->getDestinoAresta() == m->getIdNo()){
                        Pv++;
                    }
                }
            }  
        }

        grauNo++;
    }

    if(!grafoDirecionado){
        Pv = Pv/2;
    }

    if(Pv == 0){
        return 0;
    }

    return grauNo/Pv;
}

float Grafo::itemD_coefAgrupMedio(){

    float somaCoefAgrupLocais = 0;
    float numNos = 0;

    //soma todos os coeficientes de agrupamento dos nós do grafo e divide pelo número de nós 
    for(No* p= primeiroNo; p != NULL; p = p->getProxNo()){
        somaCoefAgrupLocais += itemC_coefAgrupLocal(p->getIdNo());
        numNos++;
    }

    return (somaCoefAgrupLocais/numNos);
}

std::vector<int> Grafo::itemA_fechoTransitivoDireto(int id){
    return {};
}

// a) fecho transitivo direto --> busca em profundidade (todos que o nó pode alcançar)
// b) fecho transitivo indireto --> floy
// c) [FEITO] coef agrupamento local
// d) [FEITO] coef agrupamento médio do grafo
// e) dijkstra --> pegar pronto