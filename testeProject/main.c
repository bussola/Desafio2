#include <stdio.h>
#include <stdlib.h>

struct Node{
    char nome[20];
    char descricao[20];
    int forca;
    int percep;
    int resist;
    int caris;
    int intel;
    int agil;
    int sorte;
    int id;
	struct Node *prox;
};
typedef struct Node node;

int tam;

int menu(void);
void opcao(node *FILA, int op);
void inicia(node *FILA);
int vazia(node *FILA);
node *aloca();
void insere(node *FILA);
node *retira(node *FILA);
void exibe(node *FILA);
void libera(node *FILA);


int main(void)
{
	node *FILA = (node *) malloc(sizeof(node));
	if(!FILA){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else{
	inicia(FILA);
	int opt;

	pegaDados(FILA);

	do{
		opt=menu();
		opcao(FILA,opt);
	}while(opt);

	free(FILA);
	return 0;
	}
}


int menu(void)
{
	int opt;

	printf("Escolha a opcao\n");
	printf("0. Sair\n");
	printf("1. Zerar fila\n");
	printf("2. Exibir fila\n");
	printf("3. Adicionar Elemento na Fila\n");
	printf("4. Retirar Elemento da Fila\n");
	printf("Opcao: "); scanf("%d", &opt);

	return opt;
}

void opcao(node *FILA, int op)
{
	node *tmp;
	switch(op){
		case 0:
			libera(FILA);
			break;

		case 1:
			libera(FILA);
			inicia(FILA);
			break;

		case 2:
			exibe(FILA);
            break;

		case 3:
			insere(FILA);
			break;

		//case 4:
		//	tmp= retira(FILA);
		//	if(tmp != NULL){
		//		printf("Retirado: %3d\n\n", tmp->num);
		//		libera(tmp);
		//	}
			break;

		default:
			printf("Comando invalido\n\n");
	}
}

void inicia(node *FILA)
{
	FILA->prox = NULL;
	tam=0;
}

int vazia(node *FILA)
{
	if(FILA->prox == NULL)
		return 1;
	else
		return 0;
}

node *aloca(){
	node *novo=(node *) malloc(sizeof(node));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else{
        FILE *f;
        f = fopen("fichas.txt", "a");
        int num;
        char aux[10];
        if(f){
            printf("\nDigite a forca do personagem:");
            scanf("%i", &num);
            novo->forca = num;
            fprintf(f, "%d,", num);
            printf("******");

            printf("Nova percepcao: "); scanf("%d", &novo->percep); //fprintf(f, "%d,", num);
            printf("Nova resistencia: "); scanf("%d", &novo->resist); //fprintf(f, "%d,", num);
            printf("Novo carisma: "); scanf("%d", &novo->caris); //fprintf(f, "%d,", num);
            printf("Nova inteligencia: "); scanf("%d", &novo->intel); //fprintf(f, "%d,", num);
            printf("Nova agilidade: "); scanf("%d", &novo->agil); //fprintf(f, "%d,", num);
            printf("Nova sorte: "); scanf("%d", &novo->sorte); //fprintf(f, "%d,", num);

            printf("Novo nome: ");
            scanf("%s", aux);
            fputs(aux, f);
            fputs(",", f);
            strcpy(novo->nome , aux);

            printf("Nova classe: ");
            scanf("%s", &novo->descricao);
            return novo;
            fclose (f);
        }
        else{
            printf("Arquivo nao encontrado.");
        }
	}
}

void insere(node *FILA)
{
	node *novo=aloca();
	novo->prox = NULL;

	if(vazia(FILA))
		FILA->prox=novo;
	else{
		node *tmp = FILA->prox;

		while(tmp->prox != NULL)
			tmp = tmp->prox;

		tmp->prox = novo;
	}
	tam++;
}


node *retira(node *FILA)
{
	if(FILA->prox == NULL){
		printf("Fila ja esta vazia\n");
		return NULL;
	}else{
		node *tmp = FILA->prox;
		FILA->prox = tmp->prox;
		tam--;
		return tmp;
	}

}


void exibe(node *FILA)
{
	if(vazia(FILA)){
		printf("Fila vazia!\n\n");
		return ;
	}

	node *tmp;
	tmp = FILA->prox;
	printf("Fila :");
	while( tmp != NULL){
		printf("\nForca:%5d", tmp->forca);
		printf("\nPercepcao%5d", tmp->percep);
		printf("\nResistencia%5d", tmp->resist);
		printf("\nCarisma%5d", tmp->caris);
		printf("\nInteligencia%5d", tmp->intel);
		printf("\nAgilidade:%5d", tmp->agil);
		printf("\nSorte:%5d", tmp->sorte);
		printf("\nNome: %5s", tmp->nome);
		printf("\nClasse: %5s", tmp->descricao);
		tmp = tmp->prox;
	}
	printf("\n        ");
	int count;
	for(count=0 ; count < tam ; count++)
		printf("  ^  ");
	printf("\nOrdem:");
	for(count=0 ; count < tam ; count++)
		printf("%5d", count+1);


	printf("\n\n");
}

void libera(node *FILA)
{
	if(!vazia(FILA)){
		node *proxNode,
			  *atual;

		atual = FILA->prox;
		while(atual != NULL){
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

void pegaDados(node *FILA){ //Pega os dados do txt
    int size = 1024, pos;
    int c;
    char *buffer = (char *)malloc(size);

    FILE *f = fopen("fichas.txt", "r");
    if(f) {
        do { // Roda enquanto o arquivo nao terminou
            pos = 0; //Variavel que guarda a posicao de cada caracter
            do{ // Roda enquanto o arquivo nao terminou e nao esta no fim da linha
                c = fgetc(f); //c recebe o primeiro caracter da linha
                if(c != EOF) { //Se nao esta no fim do arquivo
                    buffer[pos++] = (char)c; //Guarda o caracter do txt na variavel buffer. Utiliza a variavel pos e ja a aumenta em 1
                }
                if(pos >= size - 1) { // increase buffer length - leave room for 0
                    size *=2;
                    buffer = (char*)realloc(buffer, size);
                }
            }while(c != EOF && c != '\n');
            buffer[pos] = 0;
            // line is now in buffer
            popula(buffer, size, FILA);
        } while(c != EOF);
        fclose(f);
    }
    else{
        printf("Arquivo nao encontrado.");
    }
    free(buffer);

}


void popula (char *buffer, int size, node *FILA){
    char primeiraLetra;
    char *linha = (char *)malloc(size); //Ponteiro para guardar as linhas
    strcpy ( linha, buffer) ; //copia a string buffer para linha
    primeiraLetra = linha[0];

    //Se a primeira letra for um numero
    if(primeiraLetra == '0' || primeiraLetra == '1' || primeiraLetra == '2'|| primeiraLetra == '3' || primeiraLetra == '4' || primeiraLetra == '5'
       || primeiraLetra == '6'|| primeiraLetra == '7' || primeiraLetra == '8' || primeiraLetra == '9'  ){
       node *novo=(node *) malloc(sizeof(node));
        if(!novo){
            printf("Sem memoria disponivel!\n");
            exit(1);
        }
        char *desmembra;
        desmembra = strtok (linha,",");
        int contCaracteristica = 0; //Contador para cada caracteristica do personagem
        while (desmembra != NULL){
            switch(contCaracteristica){
                case 0:
                    novo->forca = atoi(desmembra);
                break;
                case 1:
                    novo->percep = atoi(desmembra);
                break;
                case 2:
                    novo->resist = atoi(desmembra);
                break;
                case 3:
                    novo->caris = atoi(desmembra);
                break;
                case 4:
                    novo->intel = atoi(desmembra);
                break;
                case 5:
                    novo->agil = atoi(desmembra);
                break;
                case 6:
                    novo->sorte = atoi(desmembra);
                break;
                case 7:
                     strcpy(novo->nome , desmembra);
                break;
                case 8:
                    strcpy(novo->descricao , desmembra);
                break;
            }
            desmembra = strtok (NULL, ",");
            contCaracteristica++;
        }
        novo->prox = NULL;
        if(vazia(FILA))
            FILA->prox=novo;
        else{
            node *tmp = FILA->prox;

            while(tmp->prox != NULL)
                tmp = tmp->prox;

            tmp->prox = novo;
        }
        tam++;
    }
}
