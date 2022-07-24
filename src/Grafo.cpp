#include "Grafo.h"
#include <vector>

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

std::vector<int> Grafo::itemA_fechoTransitivoDireto(int id){
    
    //vetor para controlar nós visitados
    std::vector<int>visitados ={};
    
    //retorna vazio se o grafo não for direcionado
    if(!grafoDirecionado){
        return visitados;
    }

    //encontra o nó desejado
    No* p = this->getNo(id); 

    //executa o caminhamento em profundidade para o nó desejado e exclui ele mesmo da lista final
    caminhamentoEmProfundidade(id, visitados);
    visitados.erase(visitados.begin());

    return visitados;
}

std::vector<int> Grafo::itemB_fechoTransitivoIndireto(int id){
    
    //vetor que irá receber todos os nós que podem chegar ao nó desejado
    std::vector<int>resultado ={};
    
    //retorna vazio se o grafo não for direcionado
    if(!grafoDirecionado){
        return resultado;
    }

    for(No *p = primeiroNo; p != NULL; p = p->getProxNo()){
        
        //executa o fecho transitivo direto para todos os nós
        std::vector<int>fechoTransitivoDiretoNoP = itemA_fechoTransitivoDireto(p->getIdNo());

        //se o nó desejado estiver no fecho transitivo direto de um nó n, inclui o nó n no fecho transitivo indireto do nó desejado 
        if(std::find(fechoTransitivoDiretoNoP.begin(), fechoTransitivoDiretoNoP.end(), id) != fechoTransitivoDiretoNoP.end()){
            resultado.push_back(p->getIdNo());
        }
    }

    return resultado;
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

std::vector<int> Grafo::itemE_caminhoMinimoDijkstra(int origem, int destino){
    //função calcula o caminho mínimo da origem para todos os outros nós do grafo, e no final retorna o caminho entre a origem e o destino


    int intInfinite = 2147483647;

    int numNos = this->getNumNos();
    std::vector<int> Sbarra = {};       //vetor Sbarra contém os nós que ainda não estão na solução
    std::vector<int> S = {origem};      //vetor S contém os nós que já estão na solução
    std::vector<int> custos = {};       //vetor custos contém o custo do nó origem até o nó n
    No* p = this->getNo(origem);

    //inicializa custos com infinito da linguagem (exceção para o nó de origem) e vetor com nós fora da solução final
    for(int i = 0; i < numNos; i++){
        if(i == origem){
            custos.push_back(0);
        }else{
            custos.push_back(intInfinite);
            Sbarra.push_back(i);
        }
    }

    //ajusta custos para os adjacentes
    for(Aresta *a = p->getPrimeiraAresta(); a != NULL; a = a-> getProxAresta()){
        custos[a->getDestinoAresta()] = a->getPesoAresta();
    }

    while(Sbarra.size() != 0){

        //inicia o nó de menor custo como o primeiro nó de Sbarra e compara com todos para obter o real menor custo
        int idSbarraMenorCusto = Sbarra[0];
        for(int i = 0; i < Sbarra.size(); i++){
            if(custos[Sbarra[i]] < custos[idSbarraMenorCusto]){
                idSbarraMenorCusto = Sbarra[i];
            }
        }

        //busca a posição do Sbarra de menor custo
        int posicaoSbarraMenorCusto;
        for(int i = 0; i < Sbarra.size(); i++){
            if(Sbarra[i] == idSbarraMenorCusto){
                posicaoSbarraMenorCusto = i;
            }
        }

        //adiciona o nó de menor custo à solução final (vetor S) e deleta de Sbarra
        std::vector<int>::iterator it = Sbarra.begin() + posicaoSbarraMenorCusto;
        S.push_back(Sbarra[posicaoSbarraMenorCusto]);
        No* adicionadoSolucao = this->getNo(Sbarra[posicaoSbarraMenorCusto]);
        Sbarra.erase(it);

        //atualiza os custos para o caso de ter um caminho mais barato para um nó passando pelo nó recém adicionado à S
        for(Aresta *b = adicionadoSolucao->getPrimeiraAresta(); b != NULL; b = b->getProxAresta()){

            if(custos[adicionadoSolucao->getIdNo()] + b->getPesoAresta() < custos[b->getDestinoAresta()]){
                custos[b->getDestinoAresta()] = custos[adicionadoSolucao->getIdNo()] + b->getPesoAresta();
            }
        }
    }

    //copia dados do vetor S para o vetor caminho final (pegando só os nós entre a origem e o destino)
    std::vector<int> caminhoFinal = {};
    for(int i = 0; i < S.size(); i++){
        caminhoFinal.push_back(S[i]);
        if(S[i] == destino){
            break;
        } 
    }

    //coloca o custo do caminho entre o destino e a origem na última posição do array
    caminhoFinal.push_back(custos[destino]);

    return caminhoFinal;
}

void Grafo::caminhamentoEmProfundidade(int id, std::vector<int>&visitados){

    No* p = this->getNo(id);

    visitados.push_back(id);
    
    //avança enquanto for possível, quando não for mais possível, recua (utilizando recursividade)
    for(Aresta *a = p->getPrimeiraAresta(); a != NULL; a = a->getProxAresta()){

        No* n = this->getNo(a->getDestinoAresta());
        if(std::find(visitados.begin(), visitados.end(), n->getIdNo()) == visitados.end()){
            caminhamentoEmProfundidade(n->getIdNo(), visitados);
        }
    }
}