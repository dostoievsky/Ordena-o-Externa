#ifndef REGISTRO_H
#define REGISTRO_H

typedef struct registro{
	long int inscricao;
	float nota;
	char estado[3];
	char cidade[51];
	char curso[31];
}TipoRegistro;

TipoRegistro* criarRegistro();
long int getInscricao(TipoRegistro *reg);
void setInscricao(TipoRegistro* reg, long int inst);
float getNota(TipoRegistro *reg);
void setNota(TipoRegistro* reg, float nota);
char* getEstado(TipoRegistro *reg);
void setEstado(TipoRegistro* reg, char* estado);
char* getCidade(TipoRegistro *reg);
void setCidade(TipoRegistro* reg, char* cidade);
char* getCurso(TipoRegistro *reg);
void setCurso(TipoRegistro* reg, char* curso);
void imprimirRegistro(TipoRegistro *registro);

#endif
