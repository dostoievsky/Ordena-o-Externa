#ifndef LISTADUPLA_H_
#define LISTADUPLA_H_

#include "Celula.h"

typedef struct lista{
	Tcelula *pPrimeiro;
	Tcelula *pUltimo;
	int cont;
}Tlista;

Tcelula* getpPrimeiro(Tlista *lista);
Tcelula* getpUltimo(Tlista *lista);
int getCont(Tlista *lista);//pega o tamanho da lista
void setpPrimeiro(Tlista *lista, Tcelula* ponteiro);
void setpUltimo(Tlista *lista, Tcelula* ponteiro);
void setCont(Tlista *lista, int tam);

Tlista* criarLista();
int listaVazia(Tlista *lista);//retorna 1 se a lista for vazia e 0 caso contrario
int inserirFinal(Tlista *lista, TipoRegistro* registro);
void imprimirLista(Tlista *lista);
int inserirOrdenado(Tlista *lista, TipoRegistro* registro);
int inserir(Tlista *lista, int posicao, TipoRegistro* registro);//insere um elemento na posicao i
int inserirApos(Tlista *lista, TipoRegistro* registro, TipoRegistro* apos);//inserer um item apos o outro
int estaNaLista(Tlista *lista, TipoRegistro* registro);//retorna 1 se estiver na lista e 0 caso contrario
int removerPrimeiro(Tlista *lista, TipoRegistro *registro);//retorna 1 se remover e 0 caso contrario
int remover(Tlista *lista, TipoRegistro *registro, int posicao);//retorna 1 se remover e 0 caso contrario
int removerTudo(Tlista *lista);//remove todos os elementos da lista
long int getComparacoesOrdenacaoLista();

#endif
