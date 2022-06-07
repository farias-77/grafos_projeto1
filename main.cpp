#include <iostream>
#include <fstream>
#include <string>
#include "Grafo.h"

using namespace std;

int main(int argc, char ** argv)
{
    ///verifica argumentos da linha de comando
    if(argc != 6){
        cout << "Numero invalido de argumentos!" << endl;
        return 1;
    }

    ///cria grafo e faz a configuração do que vai ser tratado posteriormente
    Grafo g1;
    g1.setGrafoDirecionado(stoi(argv[3]));
    g1.setPesoArestas(stoi(argv[4]));
    g1.setPesoNos(stoi(argv[5]));

    ///leitura arquivo
    ifstream input(argv[1]);         //arquivo a ser lido
    bool aux = true;                 //controla apenas a primeira execução do loop
    string infoAresta[3];            //[0] = idOrigem / [1] = idDestino / [2] = peso da aresta (se possuir)
    int posicaoInfoAresta;           //controla o tipo de informação que será passado para o array infoAresta

    //itera por todas as linhas
    for(string line; getline(input, line);){

        //inserção nós
        //na primeira execução do loop captura a ordem do grafo e cria os nós necessários
        if(aux){
            for(int i = 0; i < stoi(line); i++){
                g1.insereNo(i);
            }
            aux = false;
            continue;
        }

        //inserção arestas
        posicaoInfoAresta = 0;  //inicia a gravação no array pelo idOrigem
        infoAresta[0] = "";     //inicia leitura da linha com os campos vazios
        infoAresta[1] = "";
        infoAresta[2] = "";

        //itera por todas as posições da string
        for(int i = 0; i < line.size(); i++){
            if(line[i] == 32){
                posicaoInfoAresta++;                    //ao encontrar um espaço em branco (ASCII 32), altera a posição que
                continue;                               //está sendo preenchida no array infoAresta
            }
            infoAresta[posicaoInfoAresta] += line[i];   //informações são capturadas do arquivo a cada caractere
        }


        if(g1.getPesoArestas() == 0){
            g1.insereArestaGrafo(stoi(infoAresta[0]), stoi(infoAresta[1]), -1);                     //passa -1 como peso das arestas para grafos não ponderados nas arestas
        }else{
            if(infoAresta[2] == ""){infoAresta[2] = "-1";}                                          //passa -1 como peso da aresta caso o usuário informe que o grafo é ponderado, mas com uma instância que não informa o peso das arestas
            g1.insereArestaGrafo(stoi(infoAresta[0]), stoi(infoAresta[1]), stoi(infoAresta[2]));    //passa o peso da aresta lido da instância para grafos ponderados nas arestas e instâncias adequeadas
        }

    }

    g1.imprimeGrafo();

    return 0;
}
