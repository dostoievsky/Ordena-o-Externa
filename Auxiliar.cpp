#include "Auxiliar.h"

using namespace std;

int geraFitas(char* nomeFita, int quantidade){
	//GERADOR DE FITAS UTILIZADAS NA ORDENAÇÃO
	char aux[50] = "";
	char num[10];
	FILE *arq;
	for(int i = 0; i < quantidade; i++){
		
		//DEFINE FITA
		strcat(aux, nomeFita);
		fflush(stdin);
		sprintf(num,"%d",i+1);
		strcat(aux,num);
		strcat(aux, ".bin");

		arq = fopen(aux, "wb");
		if(arq == NULL){
			cout << "Erro ao abrir o arquivo" << endl;
			return 0;
		}
		fclose(arq);
		strcpy(aux, "");
	}
	return 1;
}

int excluirFitas(char* nomeFita, int quantidade){
	//Exclui as fitas utilizadas na ordenacao
	char aux[50] = "";
	char num[10];
	for(int i = 0; i < quantidade; i++){
		strcat(aux, nomeFita);
		fflush(stdin);
		sprintf(num,"%d",i+1);
		strcat(aux,num);
		strcat(aux, ".bin");
		if (remove(aux)!=0){
			cout << "Falha ao remover o arquivo" << endl;
			return 0;
		}
        strcpy(aux, "");
	}
	return 1;
}

void tamanhoFitas(FILE **fitas, long int *tamanhos, int quantFitas, int size){
    //Mede o tamanho de arquivos, os arquivos sao passados abertos para a função
     for (int i=0; i<quantFitas;i++){
    	if(fitas[i] == NULL) {
			cout << "Erro no arquivo recebido para medir tamanho." << endl;
			exit(1);
		}
        fseek(fitas[i], 0, SEEK_END);
        tamanhos[i] = ftell(fitas[i])/size;
        rewind(fitas[i]);
    }
}

void tamanhoFitasAtual (FILE **fitas, long int *tamanhos, int quantFitas, int size){
    //Mede o tamanho do arquivo ate a ultima posicao que foi lida
     for (int i=0; i<quantFitas;i++){
    	if(fitas[i] == NULL) {
			cout << "Erro no arquivo recebido para medir tamanho." << endl;
			exit(1);
		}
        tamanhos[i] = ftell(fitas[i])/size;
    }
}

bool leuTodasFitas(long int *tamFitasAtual, long int *tamFitasOriginal, int quantFitas){
	//Confere se todas as fitas de entrada terminaram de ser lidas
     for(int i = 0 ; i < quantFitas; i++){
     	if(tamFitasAtual[i] != tamFitasOriginal[i])
        	return false;
     }
     return true;
}

bool apenasUmaFitaSaida(long int *tamFitasAtual, int quantFitas){
	//Confere se so existe uma fita de saida
    int cont = 0;
    for(int i = 0 ; i < quantFitas; i++){
    	if(tamFitasAtual[i] != 0)
       	cont++;
    }
    if(cont == 1)
    	return true;
    else
    	return false;
}

void deletaFitas(char** nomeFitas, int fitaEntrada){
	//Deleta as fitas e deixa a fita de saida
	if(fitaEntrada - 1 == 0){ 
	//Se fita de entrada == 1, nao apaga a fita f
		for(int i = 0; i < ff; i++){
			if(i != f){
				if(remove(nomeFitas[i])){
					cout << "Erro ao tentar apagar arquivo" << endl;
					exit(1);
				}
			}
		}
	}else{
		for(int i = 0; i < ff; i++){
			if(i != 0){ 
			//Se fita de entrada == f, nao apaga a fita 0
				if(remove(nomeFitas[i])){
					cout << "Erro ao tentar apagar arquivo" << endl;
					exit(1);
				}
			}
		}
	}
}

void liberaNomeFitas(char **nomeFitas){
	for (int i = 0; i < ff; i++) {
			free(nomeFitas[i]);
		}
		free(nomeFitas);
}

