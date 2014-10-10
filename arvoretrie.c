/*                    Universidade Federal da Bahia
Busca em texto - Trabalho de Estrutura de Dados e Algoritmos II - MATA54
                       Professor Mauricio Pamplona
                           Pedro Marcelino             				 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANHO 26

//estrutura da arvore trie
typedef struct Arvore{
	struct Arvore *v[TAMANHO];
	char flag;	
}Arvore, *Parvore;

void inicializa(Parvore *node);
void inserir(Parvore *node, char *palavra);
int buscar(Parvore node, char *palavra);


int main(int argc, char *argv[]){

	FILE *arquivo1, *arquivo2;
	Parvore arvore;
	char caracter, carac_dicio;
	char word[2000000];
	int i = 0;

	inicializa(&arvore);

	arquivo1 = fopen(argv[1], "r");
	//arquivo2 = fopen(argv[2], "a");

	//pegando todas as palavras do dicionario e inserindo na arvore trie
	while((carac_dicio = fgetc(arquivo1)) != EOF){

		if(carac_dicio != '\n'){
			word[i] = carac_dicio;
			i++;
		}
		else{
			word[i] = '\0';
			i = 0;
			inserir(&arvore, word);
		}

	}

	//lendo todos os caracteres do arquivo2

	fclose(arquivo1);
	//fclose(arquivo2);
	return 0;
}

void inicializa(Parvore *node){
	*node = NULL;
}

void inserir(Parvore *node, char *palavra){

	int i;

	if(*node == NULL){
		*node = (Arvore *)malloc(sizeof(Arvore));
		for(i = 0; i < TAMANHO; i++)
			(*node)->v[i] = NULL;
		if(palavra[0] != '\0'){
			inserir(&(*node)->v[palavra[0] - 'a'], palavra + 1);
			(*node)->flag = 0;
		}
		else
			(*node)->flag = 1;
	}
	else{
		if(palavra[0] != '\0'){
			inserir(&(*node)->v[palavra[0] - 'a'], palavra + 1);
		}
		else
			(*node)->flag = 1;
	}
}

//funcao que retorna '0' caso a palavra desejada nao se encontra na arvore trie. Se estiver no dicionario, retorna '1'
int buscar(Parvore node, char *palavra){
	if(node == NULL)
		return 0;
	else
		if(palavra[0] == '\0')
			return (node->flag ? 1:0); //retornando 1 ou 0 caso a palavra esteja ou nao no dicionario, respectivamente
		else
			return buscar(node->v[palavra[0] - 'a'], palavra + 1);
}