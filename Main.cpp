#include "header.h"

using namespace std;

//formato de entrada : <nomePrograma> <metodo> <quantItens> <situacao> <opcional>
int main(int argc, char** argv) {
	if (argc < 4 && argc > 5) {
		/*
		 * verifica se os valores passados pelo prompt sao validos
		 */
		cout << "Formato de entrada invalido" << endl;
		return 0;
	}

	// funcao auxiliar
	srand(time(NULL));
	struct timeval inicio, final;
    int tmili;
	//declaracao das variaveis
	char nomeArquivoTexto[50]="PROVAO.TXT";
	char nomeArquivo[50] = "arq.bin";
	char nomeFita[30] = "Fita";
	char aux[50] = "", num[10] = "";
	FILE *arqSaida;

	//atribui para variaveis os valores recebidos pelo prompt
	char *metodo = argv[1];
	char *quantidade = argv[2];
	char *situacao = argv[3];
	char* opcional;
	if (argc == 5)			//analisa se foi passado o argumento opcional
		opcional = argv[4];
	else
		opcional = NULL;

	if (strcmp(metodo, "1") == 0) {

		// * Intercalacao balanceada de varios caminhos (2f fitas) utilizando mergeSort

		if (gerador(quantidade, situacao,nomeArquivoTexto, nomeArquivo)) { //gera o arquivo binario
		
			gettimeofday(&inicio, NULL);

			gerarFitasOrdenadas(nomeArquivo); // Chama o método de ordenação 2f
			misturarFitas(1);

		
			gettimeofday(&final, NULL);
   		    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);			

			visu();
			
			cout << "Intercalacao balanceada de varios caminhos utilizando mergeSort";
			
			visu();
			
			if(strcmp(situacao,"1") == 0){
				cout << "Arquivo ordenado ascendentemente" << endl;
			}else if (strcmp(situacao,"2") == 0){
				cout << "Arquivo ordenado descendentemente" << endl;
			}else if (strcmp(situacao, "3") == 0){
				cout << "Arquivo desordenado" << endl;
			}
			
			visu();
			
			cout << "Arquivo com " << quantidade << " registros" << endl;
			cout << "transferencias de memoria secundaria para memoria principal = " << getLeitura2f() << endl;
			cout << "transferencias de memoria principal para a memoria secundária = " << getEscrita2f() << endl;
			cout << "comparacoes entre notas = " << getComparacoes2f() << endl;
			cout << "Tempo em ms = " << tmili;
			
			visu();
			
			int fMaisUm = 11;
			if (opcional != NULL) { 
			//opcao de imprimir ativada, imprime os registros
				cout << endl;
				cout << "==================================" << endl;
				cout << "Arquivo de entrada : " << endl;
				lerBin(nomeArquivo);
				cout << endl;
				cout << "==================================" << endl;
				cout << "Arquivo de Saida : " << endl;
				//o arquivo de saida vai estar ou na fita um ou na f+1
				strcat(aux, nomeFita);
				sprintf(num, "%d", fMaisUm);
				strcat(aux, num);
				strcat(aux, ".bin");
				arqSaida = fopen(aux, "rb");
				if(arqSaida == NULL){
					strcpy(aux, "");
					strcat(aux, nomeFita);
					sprintf(num, "%d", 1);
					strcat(aux, num);
					strcat(aux, ".bin");
					arqSaida = fopen(aux, "rb");
					if(arqSaida == NULL){
						cout << "Erro ao abrir arquivo de saida ! " << endl;
						exit(1);
					}
				}
				fclose(arqSaida);
				lerBin(aux);
				cout << "==================================" << endl;
			}
		} else {
			cout << "Situacao invalida" << endl;
			return 0;
		}
		return 1;
	} else if (strcmp(metodo, "2") == 0) {
		 //Intercalacao balanceada de varios caminhos (2f fitas) utilizando selecao por substituicao
		if (gerador(quantidade, situacao,nomeArquivoTexto,nomeArquivo)) { //gera o arquivo binario
			gettimeofday(&inicio, NULL);
			gerarFitasOrdenadasSubs(nomeArquivo);
			misturarFitasSubs(1);
			gettimeofday(&final, NULL);
   		    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
			visu();
			cout << "Intercalacao balanceada 2f utilizando substituicao" << endl;
			visu();
			if(strcmp(situacao,"1") == 0){
				cout << "Arquivo ordenado ascendentemente" << endl;
			}else if (strcmp(situacao,"2") == 0){
				cout << "Arquivo ordenado descendentemente" << endl;
			}else if (strcmp(situacao, "3") == 0){
				cout << "Arquivo desordenado" << endl;
			}
			
			visu();
			cout << "Arquivo com " << quantidade << " registros" << endl;
			cout << "transferencias de memoria secundaria para memoria principal = " << getLeitura2fSubs() << endl;
			cout << "transferencias de memoria principal para a memoria secundária = " << getEscrita2fSubs() << endl;
			cout << "comparacoes entre notas = " << getComparacoes2fSubs() << endl;
			cout << "Tempo em ms = " << tmili;
			visu();
			
			int fMaisUm = 11;
			if (opcional != NULL) { //opcao de imprimir ativada, imprime os registros
				cout << endl;
				cout << "==================================" << endl;
				cout << "Arquivo de entrada : " << endl;
				lerBin(nomeArquivo);
				cout << endl;
				cout << "==================================" << endl;
				cout << "Arquivo de Saida : " << endl;
				//o arquivo de saida vai estar ou na fita um ou na f+1
				strcat(aux, nomeFita);
				sprintf(num, "%d", fMaisUm);
				strcat(aux, num);
				strcat(aux, ".bin");
				arqSaida = fopen(aux, "rb");
				if(arqSaida == NULL){
					strcpy(aux, "");
					strcat(aux, nomeFita);
					sprintf(num, "%d", 1);
					strcat(aux, num);
					strcat(aux, ".bin");
					arqSaida = fopen(aux, "rb");
					if(arqSaida == NULL){
						cout << "Erro ao abrir arquivo de saida ! " << endl;
						exit(1);
					}
				}
				fclose(arqSaida);
				lerBin(aux);
				cout << "==================================" << endl;
			}
		} else {
			cout << "Situacao invalida" << endl;
			return 0;
		}
		return 1;
	} else if (strcmp(metodo, "3") == 0) {
		//QuickSort externo
		gettimeofday(&inicio, NULL);
		if (gerador(quantidade, situacao,nomeArquivoTexto, nomeArquivo)) { //gera o arquivo binario
			char nomeCopia[30] = "Copia.bin";
			if(copiaBin(nomeArquivo, nomeCopia) == 0){
				cout << "Erro ao copiar arquivo no quick sort" << endl;
				exit(1);
			}
			FILE *ArqLi = fopen (nomeArquivo, "r+b");
			FILE *ArqEi = fopen (nomeArquivo, "r+b");
			FILE *ArqLEs = fopen (nomeArquivo, "r+b");
			int qtd = atoi(quantidade);
			QuicksortExterno(&ArqLi,&ArqEi,&ArqLEs,1,qtd);
			fclose (ArqLi);
			fclose (ArqEi);
			fclose (ArqLEs);
			gettimeofday(&final, NULL);
			tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + 
							(final.tv_usec - inicio.tv_usec) / 1000);	
			visu();
			cout << "QuickSort Externo" << endl;
			visu();
			if(strcmp(situacao,"1") == 0){
				cout << "Arquivo ordenado ascendentemente" << endl;
			}else if (strcmp(situacao,"2") == 0){
				cout << "Arquivo ordenado descendentemente" << endl;
			}else if (strcmp(situacao, "3") == 0){
				cout << "Arquivo desordenado" << endl;
			}
			visu();
			cout << "Arquivo com " << quantidade << " registros" << endl;
			cout << "leitura da memoria externa para interna = " << getLeituraQuick() << endl;
			cout << "escrita da memoria interna para a memoria externa = " << getEscritaQuick() << endl;
			cout << "comparacoes entre notas = " << getComparacoesQuick() << endl;
			cout << "Tempo em ms = " << tmili;
			visu();
			
			if (opcional != NULL) { //opcao de imprimir ativada, imprime os registros
				cout << endl;
				cout << "==================================" << endl;
				cout << "Arquivo de entrada" << endl;
				lerBin(nomeCopia);
				cout << "==================================" << endl;
				cout << endl;
				cout << "==================================" << endl;
				cout << "Arquivo de Saida : " << endl;
				lerBin(nomeArquivo);
				cout << "==================================" << endl;
			}
		} else {
			cout << "Situacao invalida" << endl;
			return 0;
		}
		return 1;

	}else if(strcmp(metodo, "4") == 0){
		//Intercalacao balanceada de varios caminhos (f+1 fitas) 
		//utilizando o metodo de selecao por substituicao;
		if (gerador(quantidade, situacao,nomeArquivoTexto,nomeArquivo)) { 
		//gera o arquivo binario
			gettimeofday(&inicio, NULL);
			gerarFitasOrdenadasSubsMaisUm(nomeArquivo);
			char ** nomeFitasSubs;
			nomeFitasSubs = (char**) malloc(20 * sizeof(char*));
			for (int i = 0; i < 20; i++)
				nomeFitasSubs[i] = (char*) malloc(30 * sizeof(char));
			ordenaFMaisUmSubs(nomeFitasSubs);
			gettimeofday(&final, NULL);
   		    	tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);	
			for (int i = 0; i < 20; i++) {
				free(nomeFitasSubs[i]);
			}
			free(nomeFitasSubs);
			visu();
			cout << "Intercalacao balanceada (f + 1) utilizando substituicao" << endl;
			visu();
			if(strcmp(situacao,"1") == 0){
				cout << "Arquivo ordenado ascendentemente" << endl;
			}else if (strcmp(situacao,"2") == 0){
				cout << "Arquivo ordenado descendentemente" << endl;
			}else if (strcmp(situacao, "3") == 0){
				cout << "Arquivo desordenado" << endl;
			}
			visu();
			cout << "Arquivo com " << quantidade << " registros" << endl;
			cout << "leitura da memoria externa para interna = " << getLeiturafMaisUmSubs() << endl;
			cout << "escrita da memoria interna para a memoria externa = " << getEscritafMaisUmSubs() << endl;
			cout << "comparacoes entre notas = " << getComparacoesfMaisUmSubs() << endl;
			cout << "Tempo em ms = " << tmili;
			visu();
			int fMaisUm = 20;
			if (opcional != NULL) { 
			 //opcao de imprimir ativada, imprime os registros
				cout << endl;
				cout << "==================================" << endl;
				cout << "Arquivo de entrada : " << endl;
				lerBin(nomeArquivo);
				cout << endl;
				cout << "==================================" << endl;
				cout << "Arquivo de Saida : " << endl;
				//o arquivo de saida vai estar ou na fita um ou na f+1
				strcpy(aux, "");
				strcat(aux,nomeFita);
				sprintf(num, "%d", fMaisUm);
				strcat(aux, num);
				strcat(aux, ".bin");
				arqSaida = fopen(aux, "rb");
				if(arqSaida == NULL){
					cout << "Erro ao abrir arquivo de saida ! " << endl;
					exit(1);
				}
				fclose(arqSaida);
				lerBin(aux);
				cout << "==================================" << endl;
			}
		} else {
			cout << "Situacao invalida" << endl;
			return 0;
		}
		return 1;
		
	}

	return 0;
}