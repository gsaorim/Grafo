// Gabriela Saori Miyasaka       2475448


#include <iostream>
#include  <stdlib.h>
#define true 1
#define false 0

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


typedef int TIPOPESO;

typedef struct adjacencia{
	int vertice;    //vertice de destino
	TIPOPESO peso;  //peso associado a aresta que lave ao vertice de destino
	struct adjacencia *prox;    //O proximo elemento da lista de adjacencias
}ADJACENCIA;

typedef struct vertice {
	//Dados armazenados vão aqui
	ADJACENCIA *cab;   //Possui apenas a cabeça da lista de adjacencia
}VERTICE;

typedef struct grafo{   //Lembrando que cada possui:
	int vertices;   //numero de vertice total do grafo
	int arestas;    //numero de arestas total do grafo
	VERTICE *adj;    //Arranjo de vertices da estrutura
}GRAFO;


/*Função para criar um GRAFO*/
GRAFO *criaGrafo (int v){
	int i;
	
	GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
	g->vertices = v;
	g->arestas;
	g->adj = (VERTICE *)malloc(v*sizeof(VERTICE));
	
	for(i = 0; i < v; i++){
		g->adj[i].cab = NULL;
	}
	
	return (g);
}

/*Adicionando aresrtas ao grafo*/

ADJACENCIA *criaAdj(int v, int peso){
	ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));   //aloca espaço para um nó
	temp->vertice = v;    //vertice alvo da adjacencia
	temp->peso = peso;   //peso da aresta
	temp->prox = NULL;   
	return(temp);    //retorno endereço da adjacencia 
}

int criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p){    //vai de vi a vf
	if(!gr) return 0;    //validações se o grafico existe
	if((vf < 0) || (vf >= gr->vertices)) return 0;   //validações se os valores não são negativos
	if((vf < 0) || (vf >= gr->vertices)) return 0;   //ou maiores que o numero de vertices do grafo
	
	ADJACENCIA *novo = criaAdj(vf, p);   ///crio adjacencia com o vertice final e o peso
	//coloco a adjancencia na lista do vertice inicial
	novo->prox = gr->adj[vi].cab;     //o campo prox da adjacencia vai receber a cabeça da lista
	gr->adj[vi].cab = novo;    //e a cabeça da lista passa a ser o novo elemento
	gr->arestas++;     //atualizo o numero de aresta no grafo
	return 1;
}

/*Exibindo estado do grafo negativamente*/
void imprime(GRAFO *gr){
	//validações se o grafo existe
	
printf("Quantidade de Vértices: %d\n", gr->vertices);
    printf("Quantidade de Arestas: %d\n", gr->arestas);

    printf("Matriz de Adjacência:\n");
    for (int i = 0; i < gr->vertices; i++) {
        printf("v%d: ", i);
        for (int j = 0; j < gr->vertices; j++) {
            ADJACENCIA* ad = gr->adj[i].cab;
            int valor = 0;
            while (ad) {
                if (ad->vertice == j) {
                    valor = ad->peso;
                    break;
                }
                ad = ad->prox;
            }
            printf("%d ", valor);
        }

        printf("\n");
    }

    printf("Lista de Adjacência:\n");
    for (int i = 0; i < gr->vertices; i++) {
        printf("v%d: ", i);
        ADJACENCIA* ad = gr->adj[i].cab;
        while (ad) {
            printf("v%d(%d) ", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
	
}

// Função para calcular o valor total do caminho a partir do grafo
TIPOPESO calculaValorCaminho(GRAFO* gr, int caminho[], int tamanho) {
    TIPOPESO valorTotal = 0;
    
    for (int i = 0; i < tamanho - 1; i++) {
        int origem = caminho[i];
        int destino = caminho[i + 1];
        
        ADJACENCIA* ad = gr->adj[origem].cab;
        while (ad) {
            if (ad->vertice == destino) {
                valorTotal += ad->peso;
                break;
            }
            ad = ad->prox;
        }
    }
    
    return valorTotal;
}

int main(int argc, char** argv) {
	
	int numVertices = 5;
    GRAFO* grafo = criaGrafo(numVertices);

	criaAresta(grafo, 0, 0, 1);
    criaAresta(grafo, 0, 2, 1);
    criaAresta(grafo, 2, 0, 1);
    criaAresta(grafo, 2, 1, 1);
    criaAresta(grafo, 1, 2, 1);
    criaAresta(grafo, 2, 3, 1);
    criaAresta(grafo, 3, 2, 1);
    criaAresta(grafo, 1, 3, 1);
    criaAresta(grafo, 3, 1, 1);
    criaAresta(grafo, 1, 4, 1);
	criaAresta(grafo, 4, 1, 1);
    criaAresta(grafo, 3, 4, 1);
	criaAresta(grafo, 4, 3, 1);	

  
    imprime(grafo);
    
    int caminho[] = {0, 2, 1, 3, 4};
    int tamanhoCaminho = sizeof(caminho) / sizeof(caminho[0]);
    TIPOPESO valorCaminho = calculaValorCaminho(grafo, caminho, tamanhoCaminho);
    
    printf("Valor total do caminho {1, 2, 3, 4, 5}: %d\n", valorCaminho);
	
	return 0;
}
