#include <iostream>
#include <fstream>
#include <string>
#include "Grafo.h"

//Grupo 11 - Gabriel Farias Alves (202165565C) e Caio da Cunha Moacyr (201935045)

int main(int argc, char ** argv)
{
    ///verifica argumentos da linha de comando
    if(argc != 6){
        std::cout << "Numero invalido de argumentos!" << std::endl;
        return 1;
    }

    ///cria grafo e faz a configuracao do que vai ser tratado posteriormente
    Grafo g1;
    g1.setGrafoDirecionado(std::stoi(argv[3]));
    g1.setPesoArestas(std::stoi(argv[4]));
    g1.setPesoNos(std::stoi(argv[5]));
    g1.setNumNos(0);

    ///leitura arquivo
    std::ifstream input(argv[1]);    //arquivo a ser lido
    bool aux = true;                 //controla apenas a primeira execucao do loop
    std::string infoAresta[3];       //[0] = idOrigem / [1] = idDestino / [2] = peso da aresta (se possuir)
    int posicaoInfoAresta;           //controla o tipo de informacao que sera passado para o array infoAresta

    //itera por todas as linhas
    for(std::string line; std::getline(input, line);){

        //insercao nos
        //na primeira execucao do loop captura a ordem do grafo e cria os nos necessarios
        if(aux){
            for(int i = 0; i < std::stoi(line); i++){
                g1.insereNo(i);
                g1.setNumNos((g1.getNumNos() + 1));
            }
            aux = false;
            continue;
        }

        //insercao arestas
        infoAresta[0] = "";     //inicia leitura da linha com os campos vazios
        infoAresta[1] = "";
        infoAresta[2] = "";
        posicaoInfoAresta = 0;  //inicia a gravacao no array pelo idOrigem

        //itera por todas as posicoes da string
        int tam = line.length();
        for(int i = 0; i < tam; i++){
            if(line[i] == 32){
                posicaoInfoAresta++;                    //ao encontrar um espaco em branco (ASCII 32), altera a posicao que
                continue;                               //esta sendo preenchida no array infoAresta
            }
            infoAresta[posicaoInfoAresta] += line[i];   //informacao sao capturadas do arquivo a cada caractere
        }


        if(g1.getPesoArestas() == 0){
            g1.insereArestaGrafo(stoi(infoAresta[0]), stoi(infoAresta[1]), -1);                     //passa -1 como peso das arestas para grafos nao ponderados nas arestas
        }else{
            if(infoAresta[2] == ""){infoAresta[2] = "-1";}                                          //passa -1 como peso da aresta caso o usuario informe que o grafo eh ponderado, mas com uma instancia que nao informa o peso das arestas
            g1.insereArestaGrafo(stoi(infoAresta[0]), stoi(infoAresta[1]), stoi(infoAresta[2]));    //passa o peso da aresta lido da instancia para grafos ponderados nas arestas e instancias adequeadas
        }

    }


    //Coleta parâmetros para executar os itens
    int numNosGrafo = g1.getNumNos();
    int idNoItemA = -1;
    int idNoItemB = -1;
    if(g1.getGrafoDirecionado() == 1){ 
        // a) Fecho transitivo direto
        do{
            std::cout << std::endl;
            std::cout << "\tInforme o id do vértice em que será calculado o fecho transitivo direto (item A): ";
            std::cin >> idNoItemA;

            if(idNoItemA < 0 || idNoItemA >= g1.getNumNos()){
                std::cout << "\tPor favor informe um id entre 0 e " << g1.getNumNos() -1;
            }

        }while(idNoItemA < 0 || idNoItemA >= g1.getNumNos());
        

        // b) Fecho transitivo indireto
        do{
            std::cout << std::endl;
            std::cout << "\tInforme o id do vértice em que será calculado o fecho transitivo indireto (item B): ";
            std::cin >> idNoItemB;

            if(idNoItemB < 0 || idNoItemB >= g1.getNumNos()){
                std::cout << "\tPor favor informe um id entre 0 e " << g1.getNumNos() -1;
            }

        }while(idNoItemB < 0 || idNoItemB >= g1.getNumNos());        
    }

    // c) Coeficiente de agrupamento local
        int idNoItemC = -1;
        do{
            std::cout << std::endl;
            std::cout << "\tInforme o id do vértice em que será calculado o coeficiente de agrupamento local (item C): ";
            std::cin >> idNoItemC;

            if(idNoItemC < 0 || idNoItemC >= g1.getNumNos()){
                std::cout << "\tPor favor informe um id entre 0 e " << g1.getNumNos() -1;
            }

        }while(idNoItemC < 0 || idNoItemC >= g1.getNumNos());

        // d) Coeficiente de agrupamento médio do grafo (usuário não precisa passar dados)

        // e) Caminho mínimo entre dois vértices do grafo usando algoritmo de Dijkstra
        int idOrigemItemE = -1;
        do{
            std::cout << std::endl;
            std::cout << "\tInforme o id do vértice que será a origem do caminho mínimo utilizando o algoritmo de Dijkstra (item E): ";
            std::cin >> idOrigemItemE;

            if(idOrigemItemE < 0 || idOrigemItemE >= g1.getNumNos()){
                std::cout << "\tPor favor informe um id entre 0 e " << g1.getNumNos() -1;
            }

        }while(idOrigemItemE < 0 || idOrigemItemE >= g1.getNumNos());

        int idDestinoItemE = -1;
        do{
            std::cout << std::endl;
            std::cout << "\tInforme o id do vértice que será o destino do caminho mínimo utilizando o algoritmo de Dijkstra (item E): ";
            std::cin >> idDestinoItemE;

            if(idDestinoItemE < 0 || idDestinoItemE >= g1.getNumNos()){
                std::cout << "\tPor favor informe um id entre 0 e " << g1.getNumNos() -1;
            }

        }while(idDestinoItemE < 0 || idDestinoItemE >= g1.getNumNos());

        //--------------------------------------------------------





        //Resultado dos itens:

        std::cout << std::endl<< "\t--------------------------------------" << std::endl;
        std::cout << "\tResultados: " << std::endl << std::endl;

        if(g1.getGrafoDirecionado() == 1){
            // a)
            std::vector<int> resultadoItemA = g1.itemA_fechoTransitivoDireto(idNoItemA);
            if(resultadoItemA.size() > 0){
                std::cout << "\ta) Fecho transitivo direto do nó " << idNoItemA << ": [ " << resultadoItemA[0];
                for(int i = 1; i < resultadoItemA.size(); i++){
                    std::cout << ", " << resultadoItemA[i]; 
                }
                std::cout << " ]" << std::endl << std::endl;
            }else{
                std::cout << "\ta) [ ]" << std::endl << std::endl;
            }

            // b)
            std::vector<int> resultadoItemB = g1.itemB_fechoTransitivoIndireto(idNoItemB);
            if(resultadoItemB.size() > 0){
                std::cout << "\tb) Fecho transitivo indireto do nó "<< idNoItemB << " [ " << resultadoItemB[0];
                for(int i = 1; i < resultadoItemB.size(); i++){
                    std::cout << ", " << resultadoItemB[i]; 
                }
                std::cout << " ]" << std::endl << std::endl;
            }else{
                std::cout << "\tb) [ ]" << std::endl << std::endl;
            }
        }else{
            // a)
            std::cout << "\ta) Não foi possível calcular o fecho transitivo direto de um vértice em um grafo não direcionado." << std::endl << std::endl;

            // b)
            std::cout << "\tb) Não foi possível calcular o fecho transitivo indireto de um vértice em um grafo não direcionado." << std::endl << std::endl;
        }

        // c)
        std::cout << "\tc) Coeficiente de agrupamento local do nó " << idNoItemC << ": " << g1.itemC_coefAgrupLocal(idNoItemC) << std::endl << std::endl;

        // d)
        std::cout << "\td) Coeficiente de agrupamento médio do grafo: " << g1.itemD_coefAgrupMedio() << std::endl << std::endl;

        // e)
        int intInfinite = 2147483647;
        std::vector<int> caminhoMinimo = g1.itemE_caminhoMinimoDijkstra(idOrigemItemE, idDestinoItemE);
        std::cout << "\te) Custo do caminho mínimo entre os nós " << idOrigemItemE << " e " << idDestinoItemE << " usando o algoritmo de Dijkstra: ";
        if(caminhoMinimo[caminhoMinimo.size() - 1] == intInfinite || caminhoMinimo[caminhoMinimo.size() - 1] < 0){
            std::cout << "Não existe um caminho entre os nós " << idOrigemItemE << " e " << idDestinoItemE << " neste grafo.";
        }else{
            std::cout << caminhoMinimo[caminhoMinimo.size() - 1];
        }


        std::cout << std::endl << std::endl;
   

    return 0;
}
