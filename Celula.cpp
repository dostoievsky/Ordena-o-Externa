#include "Celula.h"
#include <stdlib.h>

struct celula{
	TipoRegistro* registro;
	celula* pAnt;
	celula* pProx;
};

Tcelula* criaCelula(){
	Tcelula* ncelula;
	ncelula = (Tcelula*) malloc(1*sizeof(Tcelula));
	return ncelula;
}

TipoRegistro* getRegistro(Tcelula* celula){
	return celula->registro;
}

Tcelula* getpAnt(Tcelula* celula){
	return celula->pAnt;
}

Tcelula* getpProx(Tcelula* celula){
	return celula->pProx;
}

void setRegistro(Tcelula *celula, TipoRegistro* registro){
	celula->registro=registro;
}

void setpAnt(Tcelula *celula, Tcelula* anterior){
	celula->pAnt = anterior;
}

void setpProx(Tcelula *celula, Tcelula* proximo){
	celula->pProx = proximo;
}
