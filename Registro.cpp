#include "Registro.h"
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <iostream>

using namespace std;

TipoRegistro* criarRegistro(){
	TipoRegistro* registro;
	registro = (TipoRegistro*) malloc(1*sizeof(TipoRegistro));
	return registro;
}

long int getInscricao(TipoRegistro *reg){
	return reg->inscricao;
}

void setInscricao(TipoRegistro* reg, long int inst){
	reg->inscricao = inst;
}

float getNota(TipoRegistro *reg){
	return reg->nota;
}

void setNota(TipoRegistro* reg, float nota){
	reg->nota = nota;
}

char* getEstado(TipoRegistro *reg){
	return reg->estado;
}

void setEstado(TipoRegistro* reg, char* estado){
	strcpy(reg->estado,estado);
}

char* getCidade(TipoRegistro *reg){
	return reg->cidade;
}

void setCidade(TipoRegistro* reg, char* cidade){
	strcpy(reg->cidade,cidade);
}

char* getCurso(TipoRegistro *reg){
	return reg->curso;
}

void setCurso(TipoRegistro* reg, char* curso){
	strcpy(reg->curso,curso);
}

void imprimirRegistro(TipoRegistro *registro){
	cout << "Aluno numero : " << registro->inscricao
		 << " \tNota:" << setprecision(5) << registro->nota
		 << " \tEstado : " << registro->estado 
		 << "\t Cidade : " << registro->cidade
		 << " \tCurso : " << registro->curso << endl;
}

