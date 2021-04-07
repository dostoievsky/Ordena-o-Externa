#include "ListaDupla.h"
#include "IntercalacaoBalanceada2fSubs.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

long int comparacoesOrdenacaoLista = 0;


Tcelula* getpPrimeiro(Tlista *lista){
	return lista->pPrimeiro;
}

Tcelula* getpUltimo(Tlista *lista){
	return lista->pUltimo;
}

int getCont(Tlista *lista){
	return lista->cont;
}

void setpPrimeiro(Tlista *lista, Tcelula* ponteiro){
	lista->pPrimeiro = ponteiro;
}

void setpUltimo(Tlista *lista, Tcelula* ponteiro){
	lista->pUltimo = ponteiro;
}

void setCont(Tlista *lista, int tam){
	lista->cont = tam;
}

Tlista* criarLista(){
	Tlista *lista;
	lista = (Tlista*) malloc(1*sizeof(Tlista));
	lista->pPrimeiro=NULL;
	lista->pUltimo=NULL;
	lista->cont=-1;
	return lista;
}

int listaVazia(Tlista *lista){
	if(getpPrimeiro(lista)==NULL)
		return 1;
	else
		return 0;
}

int inserirFinal(Tlista *lista, TipoRegistro* registro){
	Tcelula *nova;
	nova = criaCelula();
	setRegistro(nova,registro);
	if(getpPrimeiro(lista)==NULL){
		lista->cont++;
		lista->pPrimeiro = nova;
		lista->pUltimo=nova;
		setpAnt(nova,NULL);
		setpProx(nova,NULL);
		return 1;
	}else{
		lista->cont++;
		setpProx(getpUltimo(lista),nova);
		setpAnt(nova,getpUltimo(lista));
		lista->pUltimo = nova;
		setpProx(nova,NULL);
		return 1;
	}
}

void imprimirLista(Tlista *lista){
	Tcelula *aux;
	aux = getpPrimeiro(lista);
	while(aux != NULL){
		TipoRegistro *t = getRegistro(aux);
		imprimirRegistro(t);
		aux = getpProx(aux);
	}
}

int inserirOrdenado(Tlista *lista, TipoRegistro* registro){
	comparacoesOrdenacaoLista = 0;
	Tcelula *aux;
	//Criacao de um novo registro para ser inserido na lista
	TipoRegistro *novoRegistro = criarRegistro();
	setInscricao(novoRegistro,getInscricao(registro));
	setNota(novoRegistro,getNota(registro));
	setCidade(novoRegistro,getCidade(registro));
	setEstado(novoRegistro, getEstado(registro));
	setCurso(novoRegistro, getCurso(registro));
	if (listaVazia(lista)){
		inserir(lista,0,novoRegistro);
		return 1;
	}
	aux = getpPrimeiro(lista);
	if (aux!=NULL){
		if (getpProx(aux)!=NULL){

			comparacoesOrdenacaoLista++;

			while ((getNota(getRegistro(aux)))<getNota(registro)){
				comparacoesOrdenacaoLista++;
				if (getpProx(aux)!=NULL){
					aux=getpProx(aux);
				}
				else
					break;
			}
		}
	}
	if (getInscricao(getRegistro(aux))==getInscricao(getRegistro(getpPrimeiro(lista))) 
		&&  (getNota(registro)<=getNota(getRegistro(aux)))){
			inserir(lista,0,novoRegistro);
			return 1;
	}
	comparacoesOrdenacaoLista++;
	if ((getNota(getRegistro(aux)))>getNota(registro)){
		aux=getpAnt(aux);
	}
	inserirApos(lista,novoRegistro,getRegistro(aux));
	return 1;
}

int inserir(Tlista *lista, int posicao, TipoRegistro* registro){
	Tcelula *aux,*aux2,*nova;
	if(posicao<=getCont(lista)+1 && posicao >= 0){
		nova = criaCelula();
		setRegistro(nova,registro);
		if(listaVazia(lista)){
			inserirFinal(lista,registro);
			return 1;
		}
		if(posicao == 0){
			aux = getpPrimeiro(lista);
			setpProx(nova,getpPrimeiro(lista));
			setpAnt(aux,nova);
			setpPrimeiro(lista,nova);
			setpAnt(nova,NULL);
			setCont(lista,getCont(lista)+1);
			return 1;
		}
		aux = getpPrimeiro(lista);
		for(int i=0; i<posicao; i++){
			aux2=aux;
			aux = getpProx(aux);
		}
		setpAnt(nova,aux2);
		setpProx(aux2,nova);
		setpProx(nova,aux);
		setpAnt(aux,nova);
		setCont(lista,getCont(lista)+1);
		return 1;
	}
		return 0;
}

int inserirApos(Tlista *lista, TipoRegistro* registro, TipoRegistro* apos){
	Tcelula *aux,*nova;
	aux = getpPrimeiro(lista);
	while(getpProx(aux) != NULL){
		if(getInscricao(getRegistro(aux)) == getInscricao(apos)){
			nova = criaCelula();
			setRegistro(nova,registro);
			setpAnt(nova,aux);
			setpProx(nova,getpProx(aux));
			setpAnt(getpProx(aux), nova);
			setpProx(aux,nova);
			setCont(lista,getCont(lista)+1);
			return 1;
		}
		aux = getpProx(aux);
	}
	if(getInscricao(getRegistro(aux)) == getInscricao(apos)){
		nova = criaCelula();
		setRegistro(nova,registro);
		setpAnt(nova,aux);
		setpProx(nova,NULL);
		setpProx(aux,nova);
		setpUltimo(lista,nova);
		setCont(lista,getCont(lista)+1);

		return 1;
	}
	return 0 ;
}

int estaNaLista(Tlista *lista, TipoRegistro* registro){
	Tcelula *aux;
	aux = getpPrimeiro(lista);
	while(aux!=NULL){
		if(getNota(getRegistro(aux)) == getNota(registro))
			return 1;
		aux = getpProx(aux);
	}
	return 0;
}

int removerPrimeiro(Tlista *lista, TipoRegistro *registro){
	Tcelula *aux;
	if(listaVazia(lista))
		return 0;
	else{
		if(lista->cont>0){
			aux=getpProx(getpPrimeiro(lista));
			setInscricao(registro,getInscricao(getRegistro(getpPrimeiro(lista))));
			setNota(registro,getNota(getRegistro(getpPrimeiro(lista))));
			setEstado(registro,getEstado(getRegistro(getpPrimeiro(lista))));
			setCidade(registro,getCidade(getRegistro(getpPrimeiro(lista))));
			setCurso(registro,getCurso(getRegistro(getpPrimeiro(lista))));
			free(getpPrimeiro(lista));
			setpPrimeiro(lista,aux);
			setpAnt(aux,NULL);
			setCont(lista,getCont(lista)-1);
			return 1;
		}else{
			setInscricao(registro,getInscricao(getRegistro(getpPrimeiro(lista))));
			setNota(registro,getNota(getRegistro(getpPrimeiro(lista))));
			setEstado(registro,getEstado(getRegistro(getpPrimeiro(lista))));
			setCidade(registro,getCidade(getRegistro(getpPrimeiro(lista))));
			setCurso(registro,getCurso(getRegistro(getpPrimeiro(lista))));
			removerTudo(lista);
			return 1;
		}
	}
}

int remover(Tlista *lista, TipoRegistro *registro, int posicao){
	Tcelula *aux,*aux2;
	int cont;
	aux = getpPrimeiro(lista);
	if(posicao>=0 && posicao<=getCont(lista) && getCont(lista)>=0){
		if(posicao == 0)
		{
			removerPrimeiro(lista,registro);
			return 1;
		}
		if(posicao == getCont(lista)){

			aux = getpAnt(getpUltimo(lista));
			setInscricao(registro,getInscricao(getRegistro(getpUltimo(lista))));
			setNota(registro,getNota(getRegistro(getpUltimo(lista))));
			setEstado(registro,getEstado(getRegistro(getpUltimo(lista))));
			setCidade(registro,getCidade(getRegistro(getpUltimo(lista))));
			setCurso(registro,getCurso(getRegistro(getpUltimo(lista))));
			free(getpUltimo(lista));
			setpUltimo(lista,aux);
			setpProx(aux,NULL);
			setCont(lista,getCont(lista)-1);


			return 1;
		}
		for(cont=0;cont<posicao;cont++){
			aux2 = aux;
			aux = getpProx(aux);
		}
		setInscricao(registro,getInscricao(getRegistro(aux)));
		setNota(registro,getNota(getRegistro(aux)));
		setEstado(registro,getEstado(getRegistro(aux)));
		setCidade(registro,getCidade(getRegistro(aux)));
		setCurso(registro,getCurso(getRegistro(aux)));
		setpAnt(getpProx(aux),aux2);
		setpProx(aux2,getpProx(aux));
		free(aux);
		setCont(lista,getCont(lista)-1);
		return 1;
	}
	else
		return 0;
}

int removerTudo(Tlista *lista){
	Tcelula *aux,*aux2;
	aux = getpPrimeiro(lista);
	while(getpProx(aux)!=NULL){
		aux2 = getpProx(aux);
		setpAnt(aux2,getpAnt(aux));
		free(aux);
		aux=aux2;
	}
	free(aux);
	setpPrimeiro(lista,NULL);
	setpUltimo(lista,NULL);
	setCont(lista,-1);
	return 1;
}

long int getComparacoesOrdenacaoLista(){
	return comparacoesOrdenacaoLista;
}
