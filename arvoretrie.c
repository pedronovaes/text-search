/*                    Universidade Federal da Bahia
Busca em texto - Trabalho de Estrutura de Dados e Algoritmos II - MATA54
                       Professor Mauricio Pamplona
                           Pedro Marcelino             				 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO 26
#define NUMMIN(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

//estrutura da arvore trie
typedef struct Arvore{
	struct Arvore *v[TAMANHO];
	char flag;
	char *palavra;
}Arvore, *Parvore;

//estrutura para armazenar as palavras em ordem crescente
typedef struct Lista{
    char *palavra;
    struct Lista *prox;
}Lista, *PLista;

char separadores[] = {' ','\n','\t','_','-','.',',','!','?',':',';'};
char menorpalavra[2000000];
int menor = 100;

void inicializaArvore(Parvore *node);
void inicializaLista(PLista *l);
void inserir_palavra(Parvore *node, int size, char *palavra);
int buscar_palavra(Parvore node, char *palavra);
int seekChar(char *str, char ch);
int consultar(PLista l, char *palavra);
void inserir_crescente(PLista *l, char *palavra);
void inserir_final(PLista *l, char *palavra);
void imprimir(PLista l);
int editDistance(char *palavra1, char *palavra2);
void buscarMenor(Parvore node, char *palavra);
//void buscarMenor(PLista l, char *palavra);
void inserir_normal(PLista *l, char *palavra);


int main(int argc, char *argv[]){
	
	FILE *arquivo1, *arquivo2;
	Parvore arvore;
	PLista lista, lista2, lista3, p, z, y;

	char carac_text, carac_dicio;
	char word[2000000];
	char word_text[2000000];
	char other_word[2000000];
	int i = 0, tam = 0, j = 0, lines = 1, k;

	inicializaArvore(&arvore);
	inicializaLista(&lista);
	inicializaLista(&lista2);
	inicializaLista(&lista3);

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
			inserir_palavra(&arvore, strlen(word), word);
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

		if((seekChar(separadores,string[j])) && (i == 0)){
			//j++;
			continue;
		}
		if(seekChar(separadores, string[j])){

			word_text[i] = '\0';
			strcpy(other_word,word_text);
			i = 0;

			for(k = 0; k < strlen(word_text); k++)
				word_text[k] = tolower(word_text[k]);

			if(buscar_palavra(arvore, word_text) == 1){
				inserir_crescente(&lista, word_text);
			}
			else{
				inserir_final(&lista2, other_word);
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
		int number;

		printf("%s", p->palavra);
		for(j = 0; j < tam; j++){

			if(seekChar(separadores, string[j])){
				word_text[i] = '\0';
				i = 0;

				for(k = 0; k < strlen(word_text); k++)
					word_text[k] = tolower(word_text[k]);

				if((strcmp(word_text,p->palavra)) == 0){

					if (lines != number){
						if(aux == 1){
								printf(" %d", lines);
								number = lines;

						}
						else{
								printf(", %d", lines);
								number = lines;

						}
					aux = 0;
					}
				}

				if(string[j] == '\n'){
					lines++;
					number = lines-1;
				}

			}
			else{
				word_text[i] = string[j];
				i++;
			}
		}
		printf("\n");
		lines = 1;
	}
	//imprimir(lista2);
	for(z = lista2; (z != NULL); z = z->prox){
		printf("%s ", z->palavra);
		//for(y = lista3; (y != NULL); y = y->prox){
			buscarMenor(arvore, z->palavra);
			printf("%s\n", menorpalavra);
			menorpalavra[0] = '\0';
			menor = 100;

	}
}



void inicializaArvore(Parvore *node){
	*node = NULL;
}

void inicializaLista(PLista *l){
	*l = NULL;
}

void inserir_palavra(Parvore *node, int size, char *palavra){

	int i;

	if(*node == NULL){
		*node = (Arvore *)malloc(sizeof(Arvore));
		for(i = 0; i < TAMANHO; i++)
			(*node)->v[i] = NULL;
		if(palavra[0] != '\0'){
			inserir_palavra(&(*node)->v[palavra[0] - 'a'], size, palavra + 1);
			(*node)->flag = 0;
		}
		else{
			(*node)->flag = 1;
			(*node)->palavra = malloc(size);
			strcpy((*node)->palavra, palavra - size);
		}
	}
	else{
		if(palavra[0] != '\0'){
			inserir_palavra(&(*node)->v[palavra[0] - 'a'], size, palavra + 1);
		}
		else{
			(*node)->flag = 1;
			(*node)->palavra = malloc(size);
			strcpy((*node)->palavra, palavra - size);
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

void inserir_final(PLista *l, char *palavra){
	PLista p, q;
	p = ((Lista *)malloc(sizeof(Lista)));
	p->palavra = malloc(strlen(palavra));
	if(*l == NULL){
		*l = p;
		strcpy(p->palavra, palavra);
		p->prox = NULL;
	}
	else{
		for(q = *l; (q->prox); q = q->prox);
		q->prox = p;
		strcpy(p->palavra, palavra);
		p->prox = NULL;
	}
}

void imprimir(PLista l){
	PLista p;
	for(p = l; (p); p = p->prox)
		printf("%s\n", p->palavra);
}

int editDistance(char *palavra1, char *palavra2){

    unsigned int a, b, tamP1, tamP2;
    tamP1 = strlen(palavra1);
    tamP2 = strlen(palavra2);
    unsigned int vetor[tamP2+1][tamP1+1];

    vetor[0][0] = 0;

    for (a = 1; a <= tamP2; a++)
        vetor[a][0] = vetor[a - 1][0] + 1;

    for (b = 1; b <= tamP1; b++)
        vetor[0][b] = vetor[0][b - 1] + 1;
    
    for (a = 1; a <= tamP2; a++)
        for (b = 1; b <= tamP1; b++)
            vetor[a][b] = NUMMIN(vetor[a - 1][b] + 1, vetor[a][b - 1] + 1, vetor[a - 1][b - 1] + (palavra1[b - 1] == palavra2[a - 1] ? 0 : 1));
 
    return(vetor[tamP2][tamP1]);
}

void buscarMenor(Parvore node, char *palavra){
	int i;
	int variavel;
	if(node == NULL)
		return;
	for(i = 0; i < TAMANHO; i++){
		if(node->flag == 1){
			variavel = editDistance(node->palavra, palavra);
			if(variavel < menor){
				menor = variavel;
				strcpy(menorpalavra, node->palavra);
			}
		}
		else
			buscarMenor(node->v[i], palavra);
	}
}

/*void buscarMenor(PLista l, char *palavra){
	PLista p;
	int variavel;
	int menor = 100;

	for(p = l; (p); p = p->prox){

		variavel = editDistance(palavra, p->palavra);
		if(variavel < menor){
			menor = variavel;
			strcpy(menorpalavra, p->palavra);
		}
	}
	printf("%s\n", menorpalavra);
}*/
