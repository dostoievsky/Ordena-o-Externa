#include "Quicksort_externo.h"
#include <stdio.h>
#include <limits>
#include <iostream>

using namespace std;

long int escritaQuick = 0;
long int leituraQuick = 0;
long int comparacoesQuick = 0;

#define INT_MIN numeric_limits<int>::min()
#define INT_MAX numeric_limits<int>::max()
#define TAMAREA 20

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir){
	int i, j;
	Tlista* Area;		//Area de armazenamento interna
	if (Dir - Esq < 1)
		return;
	Area = criarLista();//criamos a lista que sera utilizada como estrutura de dados
	Particao(ArqLi, ArqEi, ArqLEs, *Area, Esq, Dir, &i, &j);
	// analisa qual o menor subarquivo e comeca ordenando por ele
	if (i - Esq < Dir - j){
		QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
		QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
	}
	else {
		QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
		QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
	}
}

void LeSup (FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer){
	//Le o valor do limite superior
	fseek(*ArqLEs, ((*Ls) - 1) * sizeof (TipoRegistro), SEEK_SET);
	fread (UltLido, sizeof(TipoRegistro), 1, *ArqLEs);
	leituraQuick++;
	(*Ls)--;
	(*OndeLer) = false;
}

void LeInf (FILE **ArqLi, TipoRegistro *UltLido, int *Li, short *OndeLer){
	//Le o valor do limite inferior
	fread (UltLido, sizeof(TipoRegistro), 1, *ArqLi);
	leituraQuick++;
	(*Li)++;
	(*OndeLer) = true;
}

void InserirArea (Tlista *Area, TipoRegistro *UltLido, int *NRArea){
	//Insere o ultimo registro lido de forma ordenada na Area
	inserirOrdenado(Area, UltLido);//inserir
	comparacoesQuick += getComparacoesOrdenacaoLista();
	(*NRArea) = getCont(Area);
}

void EscreveMax (FILE **ArqLEs, TipoRegistro R, int *Es){
	//Escreve o valor maximo no arquivo
	fseek (*ArqLEs, ((*Es) - 1) * sizeof (TipoRegistro), SEEK_SET);
	fwrite (&R, sizeof(TipoRegistro),1, *ArqLEs);
	escritaQuick++;
	fflush(*ArqLEs);
	(*Es)--;
}

void EscreveMin (FILE **ArqEi, TipoRegistro R, int *Ei){
	//Escreve o valor minimo no arquivo
	fwrite (&R, sizeof(TipoRegistro),1, *ArqEi);
	escritaQuick++;
	fflush(*ArqEi);
	(*Ei)++;
}

void RetiraMax (Tlista*Area, TipoRegistro *R, int *NRArea){
	//Retira o valor maximo da Area
	remover(Area,R,getCont(Area));
	*NRArea = getCont(Area);
}

void RetiraMin (Tlista *Area, TipoRegistro *R, int *NRArea){
	//Retira o valor minimo da Area
	remover(Area,R,0);
	(*NRArea) = getCont(Area);
}

void Particao (FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, 
			Tlista Area, int Esq, int Dir, int *i, int *j){
	int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0;
	float Linf = INT_MIN, Lsup = INT_MAX;
	short OndeLer = true;
	TipoRegistro UltLido, R;
	//fazendo Li e Ei apontar para a primeira posicao do arquivo
	fseek (*ArqLi, (Li - 1) * sizeof (TipoRegistro), SEEK_SET);
	fseek (*ArqEi, (Ei - 1) * sizeof (TipoRegistro), SEEK_SET);
	(*i) = Esq - 1;
	(*j) = Dir + 1;
	while (Ls>=Li){		
	//enquanto Ls e Li nao tiverem cruzados
		if (NRArea < TAMAREA - 1){		
		//verifica se a Area cabe mais do que um elemento
			// verifica se a leitura deve ser superior ou inferior
			if (OndeLer)
				LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
			else
				LeInf(ArqLi, &UltLido, &Li, &OndeLer);
			InserirArea (&Area, &UltLido, &NRArea);		
			//insere o valor lido na Area
			continue;		
			// volta para o inicio do while
		}
		//verifica se precisa mudar a alternancia 
		//para que a escrita nao ultrapasse a leitura
		if (Ls==Es)
			LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
		else if (Li==Ei)
				LeInf(ArqLi, &UltLido, &Li, &OndeLer);
			else if (OndeLer)		//le mais um registro
					LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
				else
					LeInf(ArqLi, &UltLido, &Li, &OndeLer);
		if (UltLido.nota > Lsup){		
		//se a chave for maior que o limite superior, o registro sera escrito em A2
			(*j) = Es;
			EscreveMax(ArqLEs, UltLido, &Es);
			continue;
		}
		if (UltLido.nota < Linf){		
		//se a chave for menor que o limite inferior, o registro sera escrito em A1
			(*i) = Ei;
			EscreveMin(ArqEi, UltLido, &Ei);
			continue;
		}
		InserirArea(&Area, &UltLido, &NRArea);		//insere na area (ficou cheia)
		// avalia qual subarquivo esta mais vazio
		// se for A1, o menor registro da Area e retirado e escrito no arquivo
		// se for A2, o maior registro da Area e retirado e escrito no arquivo
		if (Ei - Esq < Dir - Es){
			RetiraMin(&Area, &R, &NRArea);
			EscreveMin(ArqEi, R, &Ei);
			Linf = R.nota;
		}
		else{
			RetiraMax(&Area, &R, &NRArea);
			EscreveMax(ArqLEs, R, &Es);
			Lsup = R.nota;
		}
	}
	//volta com os pivos para o arquivo
	while (Ei<=Es){
		RetiraMin (&Area, &R, &NRArea);
		EscreveMin (ArqEi, R, &Ei);
	}
}

long int getEscritaQuick(){
	return escritaQuick;
}


long int getLeituraQuick(){
	return leituraQuick;
}

long int getComparacoesQuick(){
	return comparacoesQuick;
}
