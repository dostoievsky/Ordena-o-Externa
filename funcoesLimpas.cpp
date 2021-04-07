#include "header.h"

int gerador(char *quantidade, char *situacao, 
			char *nomeArquivoIn, char *nomeArquivoOut) {
	// situacao = ( 1 - ordenado ascendentemente, 
	//2 - ordenado descendentemente, 3 - desordenado)
	int qtd = atoi(quantidade);
	if (geraArquivoLimitado (nomeArquivoIn,nomeArquivoOut,qtd)){
		if (strcmp(situacao, "1") == 0) {	
		// gera o arquivo de registros ordenado ascendentemente
			if (geraBinOrd(nomeArquivoOut))
				return 1;
			else {
				cout << "!!! Falha na geracao do arquivo !!!" << endl;
				return 0;
			}
		} else if (strcmp(situacao, "2") == 0) {	
		//gera o arquivo de registros ordenado descentendemente
				char entradaAki[50] = "EntradaCopia.bin";
				if (geraBinOrdInv(nomeArquivoOut,entradaAki,qtd)){
						copiaBin(entradaAki, nomeArquivoOut);
						if(remove(entradaAki)){
							cout << "Erro ao remover o arquivo" << endl;
							exit(1);
						}
						char copia[50] = "Copia.txt";
						binParaTxt(nomeArquivoOut, copia);
						return 1;
					}
					else {
						cout << "!!! Falha na geracao do arquivo !!!" << endl;
						return 0;
					}
				} else if (strcmp(situacao, "3") == 0)	
					//gera o arquivo de registros de forma desordenada
							return 1;
						else
							return 0;
	} else {
		cout << "!!! Erro gerar o arquivo limitado !!!" << endl;
		return 0; //situacao invalida
	}
	return 0;
}

int geraBinOrdInv (char *nomeArquivoIn, char *nomeArquivoOut, int qtd){
	//Para geração dos arquivos ordenados inversamente, 
	//nós geramos um arquivo ordenado e invertemos a saida dele
	geraBinOrd(nomeArquivoIn);
	FILE *arquivoEntrada, *arquivoSaida;
	arquivoEntrada = fopen(nomeArquivoIn, "rb");
	arquivoSaida = fopen(nomeArquivoOut, "wb");
	if(arquivoEntrada == NULL || arquivoSaida == NULL){
		cout << "Erro ao abrir o arquivo" << endl;
		return 0;
	}
	TipoRegistro *reg = criarRegistro();
	fseek(arquivoEntrada,0,SEEK_END);
	for(int i = 0; i < qtd; i++){
		fseek(arquivoEntrada,-sizeof(TipoRegistro),SEEK_CUR);
		fread(reg,sizeof(TipoRegistro),1,arquivoEntrada);
		fwrite(reg,sizeof(TipoRegistro),1,arquivoSaida);
		fseek(arquivoEntrada,-sizeof(TipoRegistro),SEEK_CUR);
	}
	fclose(arquivoEntrada);
	fclose(arquivoSaida);
	return 1;
}

int lerBin(char *nomeArquivo){
//Recebe um arquivo binario, e imprime seus valores na tela
	FILE *arquivo = fopen(nomeArquivo, "rb");
	if(arquivo == NULL){
		return 0;
	}
	TipoRegistro ch;
	while(fread(&ch, sizeof(ch), 1, arquivo)){
		imprimirRegistro(&ch);
	}
	fclose(arquivo);
	return 1;
}

int copiaBin (char *nomeArquivoIn, char* nomeArquivoOut){
//Copia um arquivo binario para outro
	FILE *arquivoIn = fopen(nomeArquivoIn, "rb");
	if(arquivoIn == NULL){
		return 0;
	}
	FILE *arquivoOut = fopen(nomeArquivoOut, "wb");
	if(arquivoOut == NULL){
		return 0;
	}
	TipoRegistro ch;
	while(fread(&ch, sizeof(ch), 1, arquivoIn)){
		fwrite(&ch,sizeof(TipoRegistro),1,arquivoOut);
	}
	fclose(arquivoIn);
	fclose(arquivoOut);
	return 1;
}

void visu()
{
	cout<<endl;
	for(int i=0; i<120; i++)
	{
		cout<<"_";
	}
	cout<<endl;
}