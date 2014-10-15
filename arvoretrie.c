/*                    Universidade Federal da Bahia
Busca em texto - Trabalho de Estrutura de Dados e Algoritmos II - MATA54
                       Professor Mauricio Pamplona
                           Pedro Marcelino             				 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO 26

//estrutura da arvore trie
typedef struct Arvore{
	struct Arvore *v[TAMANHO];
	char flag;
}Arvore, *Parvore;

//estrutura para armazenar as palavras em ordem crescente
typedef struct Lista{
    char *palavra;
    struct Lista *prox;
}Lista, *PLista;

char separadores[] = {' ','\n','\t','_','-','.',',','!','?',':',';'};

void inicializaArvore(Parvore *node);
void inicializaLista(PLista *l);
void inserir_palavra(Parvore *node, char *palavra);
int buscar_palavra(Parvore node, char *palavra);
int seekChar(char *str, char ch);
int consultar(PLista l, char *palavra);
void inserir_crescente(PLista *l, char *palavra);



int main(int argc, char *argv[]){
	
	FILE *arquivo1, *arquivo2;
	Parvore arvore;
	PLista lista, p;

	char carac_text, carac_dicio;
	char word[2000000];
	char word_text[2000000];
	int i = 0, tam = 0, j = 0, lines = 1;

	inicializaArvore(&arvore);
	inicializaLista(&lista);

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

			if(buscar_palavra(arvore, word_text) == 1){

				inserir_crescente(&lista, word_text);
				//printf("%s %d\n", word_text, lines);
			}
		}
		else{
			word_text[i] = string[j];
			i++;
		}
	}

	i = 0;
	for(p = lista; (p != NULL); p = p->prox){
		int aux = 1;
		printf("%s", p->palavra);
		for(j = 0; j < tam; j++){

			if(seekChar(separadores, string[j])){
				word_text[i] = '\0';
				i = 0;

				if((strcmp(word_text,p->palavra)) == 0){
					if(aux == 1)
						printf(" %d", lines);
					else
						printf(", %d", lines);
					
					aux = 0;
				}

				if(string[j] == '\n')
					lines++;

			}
			else{
				word_text[i] = string[j];
				i++;
			}
		}
		printf("\n");
		lines = 1;
	}
}



void inicializaArvore(Parvore *node){
	*node = NULL;
}

void inicializaLista(PLista *l){
	*l = NULL;
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
		else{
			(*node)->flag = 1;
		}
	}
	else{
		if(palavra[0] != '\0'){
			inserir_palavra(&(*node)->v[palavra[0] - 'a'], palavra + 1);
		}
		else{
			(*node)->flag = 1;
		}
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

int consultar(PLista l, char *palavra){
	PLista p;
	for(p = l; (p != NULL) && (strcmp(p->palavra, palavra) != 0); p = p->prox);
	//for(p = l; (p != NULL) || (strcmp(p->palavra, palavra) != 0); p = p->prox);
	if(p == NULL)
		return 0;
	else
		return 1;
}

//funcao para inserir em ordem crescente
void inserir_crescente(PLista *l, char *palavra)
{
    PLista p, q, r;
    p = ((Lista *)malloc(sizeof(Lista)));
    p->palavra = malloc(strlen(palavra));
    r = *l;
    if(consultar(*l, palavra) == 1)
    	return;
    if(r == NULL) //lista vazia
    {
        strcpy(p->palavra, palavra);
        p->prox = NULL;
        *l = p;
    }
    else
    {
        for(q = NULL, r = *l; (r); q = r, r = r->prox)
        {
            if((strcmp(palavra, r->palavra) > 0) && (r->prox == NULL)) //final da lista
            {
                strcpy(p->palavra, palavra);
                //printf("ordenada %s\n", p->palavra);
                p->prox = NULL;
                r->prox = p;
                return;
            }
            else
            {
                if((strcmp(palavra, r->palavra) < 0) && (q == NULL)) //inicio da lista
                {
                    strcpy(p->palavra, palavra);
                    //printf("ordenada %s\n", p->palavra);
                    p->prox = r;
                    *l = p;
                    return;
                }
                else
                {
                    if((strcmp(palavra, r->palavra) < 0) && (q)) //meio da lista
                    {
                        strcpy(p->palavra, palavra);
                        //printf("ordenada %s\n", p->palavra);
                        q->prox = p;
                        p->prox = r;
                        return;
                    }
                }
            }
        }
    }
}