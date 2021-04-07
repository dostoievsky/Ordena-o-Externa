#include "Gerador.h"

using namespace std;

int geraBinOrd(char *nomeArquivo){
	//Recebe o nome de um arquivo binario e realiza a geracao dele com as chaves ordenadas
	FILE *ArqLi = fopen(nomeArquivo, "r+b");
	if(ArqLi == NULL){
		cout << "Erro ao abrir o arquivo " << endl;
		return 0;
	}
	FILE *ArqEi = fopen(nomeArquivo, "r+b");
	if(ArqEi == NULL){
		cout << "Erro ao abrir o arquivo " << endl;
		fclose(ArqLi);
		return 0;
	}
	FILE *ArqLEs = fopen(nomeArquivo, "r+b");
	if(ArqLEs == NULL){
		cout << "Erro ao abrir o arquivo " << endl;
		fclose (ArqLi);
		fclose(ArqEi);
		return 0;
	}
	fseek (ArqLi, 0, SEEK_END);
	int tamanhoArq = ftell(ArqLi)/sizeof(TipoRegistro);
	fseek (ArqLi, 0, SEEK_SET);
	
	QuicksortExterno(&ArqLi,&ArqEi,&ArqLEs, 1, tamanhoArq);
	fclose(ArqLi);
	fclose(ArqEi);
	fclose(ArqLEs);
	return 1;
}

int geraArquivoLimitado (char *nomeArquivoIn, char *nomeArquivoOut, int quant){
	/*
	 * Pega um pedaco do arquivo original
	 */
	FILE *arqIn = fopen(nomeArquivoIn, "r");
	FILE *arqOut = fopen(nomeArquivoOut, "wb");
	if(arqIn == NULL){
		cout << "Erro ao abrir o arquivo de entrada" << endl;
		return 0;
	}
	if(arqOut == NULL){
		cout << "Erro ao abrir o arquivo de saida" << endl;
		fclose(arqIn);
		return 0;
	}
	TipoRegistro reg;
	for(int i =0; i<quant; i++){
		fscanf(arqIn,"%ld %f ",&reg.inscricao, &reg.nota);
		fgets(reg.estado,3, arqIn);
		reg.estado[strlen(reg.estado) + 1] ='\0';
		fgets(reg.cidade,50, arqIn);
		reg.cidade[strlen(reg.cidade) + 1] ='\0';
		fgets(reg.curso,31, arqIn);
		reg.curso[strlen(reg.curso) - 1] ='\0';
		fwrite(&reg,sizeof(reg), 1, arqOut);
	}
	fclose(arqIn);
	fclose(arqOut);
	return 1;
}

int binParaTxt(char *nomeArquivo, char *nomeArquivotxt){
	 /*
	  * Recebe o nome de um arquivo binario e realiza a geracao dele
	  */
	FILE *arquivo = fopen(nomeArquivo, "rb");
	if(arquivo == NULL){
		cout << "Erro ao abrir o arquivo binario" << endl;
		return 0;
	}
	FILE *arquivotxt = fopen(nomeArquivotxt, "w");
	if(arquivotxt == NULL){
		cout << "Erro ao abrir o arquivo texto" << endl;
		return 0;
	}
	TipoRegistro reg;
	while (fread(&reg, sizeof(reg), 1, arquivo) == 1){
		fprintf(arquivotxt, "%ld %f %-3s %-51s %-31s \n", reg.inscricao, reg.nota, reg.estado, reg.cidade, reg.curso);
	}
	fclose(arquivotxt);
	fclose(arquivo);
	return 1;
}





