#include <iostream>
#include <fstream>
#include <string>
#include "Grafo.h"

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

    
    //item A
    std::vector<int> resultadoItemA = g1.itemA_fechoTransitivoDireto(0);
    if(resultadoItemA.size() > 0){
        std::cout << "a) [ " << resultadoItemA[0];
        for(int i = 1; i < resultadoItemA.size(); i++){
            std::cout << ", " << resultadoItemA[i]; 
        }
        std::cout << " ]" << std::endl;
    }else{
        std::cout << "a) [ ]" << std::endl;
    }

    //item B
    std::vector<int> resultadoItemB = g1.itemB_fechoTransitivoIndireto(0);
    if(resultadoItemB.size() > 0){
        std::cout << "b) [ " << resultadoItemB[0];
        for(int i = 1; i < resultadoItemB.size(); i++){
            std::cout << ", " << resultadoItemB[i]; 
        }
        std::cout << " ]" << std::endl;
    }else{
        std::cout << "a) [ ]" << std::endl;
    }
    
    //item C
    std::cout << "c)" << g1.itemC_coefAgrupLocal(0) << std::endl;

    //item D
    std::cout << "d)" << g1.itemD_coefAgrupMedio() << std::endl;

    return 0;
}
