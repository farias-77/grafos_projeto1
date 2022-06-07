#include <iostream>
#include <fstream>
#include <string>
#include "./Grafo.h"

using namespace std;

int main(int argc, char ** argv)
{
    ///verifica argumentos da linha de comando
    if(argc != 6){
        cout << "Numero invalido de argumentos!" << endl;
        return 1;
    }

    ///cria grafo e faz a configura��o do que vai ser tratado posteriormente
    Grafo g1;
    g1.setGrafoDirecionado(stoi(argv[3]));
    g1.setPesoArestas(stoi(argv[4]));
    g1.setPesoNos(stoi(argv[5]));

    ///leitura arquivo
    ifstream input(argv[1]);         //arquivo a ser lido
    bool aux = true;                 //controla apenas a primeira execu��o do loop
    string infoAresta[3];            //[0] = idOrigem / [1] = idDestino / [2] = peso da aresta (se possuir)
    int posicaoInfoAresta;           //controla o tipo de informa��o que ser� passado para o array infoAresta

    //itera por todas as linhas
    for(string line; getline(input, line);){

        //inser��o n�s
        //na primeira execu��o do loop captura a ordem do grafo e cria os n�s necess�rios
        if(aux){
            for(int i = 0; i < stoi(line); i++){
                g1.insereNo(i);
            }
            aux = false;
            continue;
        }

        //inser��o arestas
        posicaoInfoAresta = 0;  //inicia a grava��o no array pelo idOrigem
        infoAresta[0] = "";     //inicia leitura da linha com os campos vazios
        infoAresta[1] = "";
        infoAresta[2] = "";

        //itera por todas as posi��es da string
        int tam = line.length();
        for(int i = 0; i < tam; i++){
            if(line[i] == 32){
                posicaoInfoAresta++;                    //ao encontrar um espa�o em branco (ASCII 32), altera a posi��o que
                continue;                               //est� sendo preenchida no array infoAresta
            }
            infoAresta[posicaoInfoAresta] += line[i];   //informa��es s�o capturadas do arquivo a cada caractere
        }


        if(g1.getPesoArestas() == 0){
            g1.insereArestaGrafo(stoi(infoAresta[0]), stoi(infoAresta[1]), -1);                     //passa -1 como peso das arestas para grafos n�o ponderados nas arestas
        }else{
            if(infoAresta[2] == ""){infoAresta[2] = "-1";}                                          //passa -1 como peso da aresta caso o usu�rio informe que o grafo � ponderado, mas com uma inst�ncia que n�o informa o peso das arestas
            g1.insereArestaGrafo(stoi(infoAresta[0]), stoi(infoAresta[1]), stoi(infoAresta[2]));    //passa o peso da aresta lido da inst�ncia para grafos ponderados nas arestas e inst�ncias adequeadas
        }

    }

    g1.imprimeGrafo();

    return 0;
}
