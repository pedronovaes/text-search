/*                            Universidade Federal da Bahia
        Busca em texto - Trabalho de Estrutura de Dados e Algoritmos II - MATA54
                               Professor Mauricio Pamplona
                                     Pedro Marcelino             				 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define k 26

//estrutura da arvore trie
struct nodo{
	struct nodo *v[k];
	char flag;	
};

struct nodo *root = NULL;


//funcao para inserir uma nova palavra na arvore
void inserir(struct nodo **node, char *palavra);
//funcao para realizar uma busca de uma palavra na arvore
int buscar(struct nodo *node, char *palavra);


int main(int argc, char *argv[]){

	FILE *arquivo1, *arquivo2;
	char caracter, carac_dicio;
	char token[100];
	int i = 0;

	arquivo1 = fopen(argv[1], "r");
	//arquivo2 = fopen(argv[2], "a");

	//lendo caracter por caracter para inserir no dicionario
	while((carac_dicio = fgetc(arquivo1)) != EOF){

		if(carac_dicio != '\n'){
			token[i] = carac_dicio;
			i++;
		}
		else{
			token[i] = '\0';
			i = 0;
			inserir(&())
		}

	}

	//lendo todos os caracteres do arquivo2
	while((caracter = fgetc(arquivo2)) != EOF){

		if((caracter != ' ') && (caracter != '-')){

		}
		//COLOCAR AQUI OS METODOS DE ARMAZENAR A STRING QUANDO ENCONTRAR UM SEPARADOR
		//VERIFICAR SE A VARIAVEL ESTA CONTIDA NO DICIONARIO
		//SE NAO ESTIVER CONTIDA, INSERIR NA VARIAVEL
		
	}


	fclose(arquivo1);
	//fclose(arquivo2);
	return 0;
}

void inserir(struct nodo **node, char *palavra){

	int i;

	if(*node == NULL){
		*node = malloc(sizeof(struct nodo));
		for(i = 0; i < k; i++)
			(*node)->v[i] = NULL;
		if(*palavra != '\0'){
			inserir(&(*node)->v[*palavra - 'a'], palavra + 1);
			(*node)->flag = 0;
		}
		else
			(*node)->flag = 1;
	}
	else{
		if(*palavra == '\0'){
			inserir(&(*node)->v[*palavra - 'a'], palavra + 1);
		}
		else
			(*node)->flag = 1;
	}
}

int buscar(struct nodo *node, char *palavra){
	if(node == NULL)
		return 0;
	else
		if(palavra[0] == '\0')
			return (node->flag ? 1:0);
		else
			return buscar(node->v[palavra[0] - 'a'], palavra + 1);
}