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

int lines = 1;
char separadores[] = {' ','\n','\t','_','-','.',',','!','?',':',';'};

void inicializa(Parvore *node);
void inserir_palavra(Parvore *node, char *palavra);
int buscar_palavra(Parvore node, char *palavra);
int seekChar(char *str, char ch);


int main(int argc, char *argv[]){

	FILE *arquivo1, *arquivo2;
	Parvore arvore;
	char carac_text, carac_dicio;
	char word[2000000];
	char word_text[2000000];
	int i = 0, tam = 0, j = 0;

	inicializa(&arvore);

	arquivo1 = fopen(argv[1], "r");
	arquivo2 = fopen(argv[2], "r");

	//PEGANDO TODAS AS PALAVRAS DO DICIONARIO E INSERINDO NA ARVORE TRIE
	while((carac_dicio = fgetc(arquivo1)) != EOF){

		if(carac_dicio != '\n'){
			word[i] = carac_dicio;
			i++;
		}
		else{
			word[i] = '\0';
			i = 0;
			inserir_palavra(&arvore, word);
		}

	}

	//LENDO E TRATANDO TODOS OS CARACTERES DO ARQUIVO2
	while((carac_text = fgetc(arquivo2)) != EOF)
		tam++;

	//criando string com todo o conteudo do texto
	char string[tam];
	rewind(arquivo2);
	i = 0;
	while((carac_text = fgetc(arquivo2)) != EOF){
		string[i] = carac_text;
		i++;
	}
	string[i] = '\0'; //o texto todo esta nessa string

	i = 0;
	for(j = 0; j < tam; j++){
		
		if(seekChar(separadores, string[j])){
			word_text[i] = '\0';
			i = 0;

			//se achar a palavra na arvore
			if((buscar_palavra(arvore,word_text)) == 1){

				//colocar aqui tratamento para imprimir todas as linhas que a palavra se repete

				printf("%s %d\n", word_text, lines);
			}


			if(string[j] == '\n')
				lines++;
		}
		else{
			word_text[i] = string[j];
			i++;
		}
	}

	fclose(arquivo1);
	fclose(arquivo2);
	return 0;
}

void inicializa(Parvore *node){
	*node = NULL;
}

void inserir_palavra(Parvore *node, char *palavra){

	int i;

	if(*node == NULL){
		*node = (Arvore *)malloc(sizeof(Arvore));
		for(i = 0; i < TAMANHO; i++)
			(*node)->v[i] = NULL;
		if(palavra[0] != '\0'){
			inserir_palavra(&(*node)->v[palavra[0] - 'a'], palavra + 1);
			(*node)->flag = 0;
		}
		else
			(*node)->flag = 1;
	}
	else{
		if(palavra[0] != '\0'){
			inserir_palavra(&(*node)->v[palavra[0] - 'a'], palavra + 1);
		}
		else
			(*node)->flag = 1;
	}
}

//funcao que retorna '0' caso a palavra desejada nao se encontra na arvore trie. Se estiver no dicionario, retorna '1'
int buscar_palavra(Parvore node, char *palavra){
	if(node == NULL)
		return 0;
	else
		if(palavra[0] == '\0')
			return (node->flag ? 1:0); //retornando 1 ou 0 caso a palavra esteja ou nao no dicionario, respectivamente
		else
			return buscar_palavra(node->v[palavra[0] - 'a'], palavra + 1);
}

int seekChar(char *str, char ch){

    int i;
    for(i = 0; i < strlen(str); i++)
        if (str[i] == ch)
            return 1;
    return 0;
}