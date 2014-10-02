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
}

struct nodo *root = NULL;

//funcao para inserir uma nova palavra na arvore
void inserir(struct node **nodo, char *palavra);
//funcao para realizar uma busca de uma palavra na arvore
int buscar(struct node *nodo, char *palavra);


int main(int argc, char *argv[]){

	FILE *arquivo1, *arquivo2;
	char caracter;

	arquivo1 = fopen(argv[1], "r");
	//arquivo2 = fopen(argv[2], "a");

	while((caracter = fgetc(arquivo1)) != EOF){

		//COLOCAR AQUI OS METODOS DE ARMAZENAR A STRING QUANDO ENCONTRAR UM SEPARADOR
		//VERIFICAR SE A VARIAVEL ESTA CONTIDA NO DICIONARIO
		//SE NAO ESTIVER CONTIDA, INSERIR NA VARIAVEL
		
	}


	fclose(arquivo1);
	//fclose(arquivo2);
	return 0;
}

void inserir(struct node **nodo, char *palavra){
	int i;

	if(*nodo == NULL){
		*nodo = malloc(sizeof(struct nodo));
		for(i = 0; i < k; i++)
			(*nodo)->v[i] = NULL;
		if(palavra[0] != '\0'){
			inserir(&(*nodo)->v[palavra[0] - 'a'], palavra + 1);
			(*nodo)->flag = 0;
		}
		else
			(*nodo)->flag = 1;
	}
	else
		if(palavra[0] == '\0'){
			inserir(&(*nodo)->v[palavra[0] - 'a'], palavra + 1);
		}
		else
			(*nodo)->flag = 1;
}

int buscar(struct node *nodo, char *palavra){
	if(nodo == NULL)
		return 0;
	else
		if(palavra[0] == '\0')
			return (nodo->flag ? 1:0);
		else
			return buscar(nodo->v[palavra[0] - 'a'], palavra + 1);
}