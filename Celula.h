#ifndef CELULA_H_
#define CELULA_H_
#include "Registro.h"

typedef struct celula Tcelula;

Tcelula* criaCelula();
TipoRegistro* getRegistro(Tcelula* celula);
Tcelula* getpAnt(Tcelula* celula);
Tcelula* getpProx(Tcelula* celula);
void setRegistro(Tcelula *celula, TipoRegistro* registro);
void setpAnt(Tcelula *celula, Tcelula* anterior);
void setpProx(Tcelula *celula, Tcelula* proximo);

#endif
