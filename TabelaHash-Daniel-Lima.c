#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Tabela Hash 
// Daniel Lima

typedef struct No
{
	char texto[50];
	struct No *prox;
}TNo;

typedef TNo* TLista;

void inicializar(TLista Tabela[])
{
	int i;
	for(i=0;i<10;i++)
	{
		Tabela[i] = NULL;
	}
}

int gerar_indice(char tex[])
{
	int res = 0, tam, i;

	tam = strlen(tex);

	for(i=0;i<tam;i++)
	{
		res = res + tex[i];
	}
	return res % 10;
}

void exibir(TLista L[], int id)
{
	TLista aux = L[id];  

	if (!aux) 
	{
		printf("Lista vazia!\n");
	}
	else
	{
		printf("lista %d: ", id);
		while (aux) 
		{
			printf("%s->", aux->texto);  
			aux = aux->prox;  
		}
		printf("NULL");
		printf("\n");
	}
}

int inserir(TLista tabela[], char tex[], int id)
{
	TLista aux = (TLista)malloc(sizeof(TNo));
	TLista aux_percorrer = tabela[id];

	if (aux == NULL)
	{
		return 0;
	}
	if (tabela[id] == NULL || tex[0] < tabela[id]->texto[0]) // primeiro nó ou se for NULL.
	{
		strcpy(aux->texto, tex);
		aux->prox = tabela[id];
		tabela[id] = aux;
		return 1;
	}
	while(aux_percorrer->prox != NULL) // outros nós depois do primeiro.
	{
		if(tex[0] < aux_percorrer->prox->texto[0])
		{
			strcpy(aux->texto, tex);
			aux->prox = aux_percorrer->prox;
			aux_percorrer->prox = aux;
			return 1;
		}
		aux_percorrer = aux_percorrer->prox;
	}
	// se chegou aqui é porque passou por todos os nós e vai inseir no final.
	strcpy(aux->texto, tex);
	aux->prox = aux_percorrer->prox;
	aux_percorrer->prox = aux;
	return 1;
}

TLista pesquisar(TLista tabela[], char tex[], int id)
{
	TLista aux = tabela[id], aux_percorrer;
	if(aux == NULL)
	{
		return NULL;
	}
	while(aux != NULL)
	{
		if(strcmp(aux->texto,tex) == 0)
		{
			return aux;
		}
		aux = aux->prox;
	}
	return NULL;
}

int remover(TLista tabela[], char tex[], int id)
{
	TLista res, aux = tabela[id], aux_percorrer;
	
	if(aux == NULL)
	{
		return 0;
	}
	if(strcmp(tabela[id]->texto,tex) == 0) //primeiro caso.
	{	
		aux_percorrer = tabela[id];
		tabela[id] = tabela[id]->prox;
		free(aux_percorrer);
		return 1;
	}
	while(aux->prox != NULL) // se não for o primeiro.
	{
		if(strcmp(aux->prox->texto, tex) == 0)
		{
			aux_percorrer = aux->prox;
			aux->prox = aux->prox->prox;
			free(aux_percorrer);
			return 1;
		}
		aux = aux->prox;
	}
	return 0;
}
int alterar(TLista tabela[], char tex[], char tex2[])
{
	int res,id,id2;
	
	id = gerar_indice(tex);
	if(!pesquisar(tabela,tex,id)) // se for falso
	{
		return 2;
	}
	id2 = gerar_indice(tex2);
	if(pesquisar(tabela,tex2,id2)) // se for verdadeiro
	{
		return 3;
	}
	if(remover(tabela,tex,id) == 1 && inserir(tabela,tex2,id2) == 1)// remove e insere.
	{
		return 1;
	}
	return 0;
}

void exibir_tudo(TLista tabela[])
{
	TLista aux;
	int i;
	
	for(i=0;i<10;i++)
	{
		aux = tabela[i];
		if(!aux)
		{
			printf("Lista %d: Vazia! \n\n",i);
		}
		else
		{
			printf("Lista %d: ",i);
			while(aux)
			{
				printf("%s->",aux->texto);
				aux = aux->prox;
			}
			printf("NULL\n\n");	
		}
	}
}
int main()
{
	TLista Tabela[10],aux;
	char tex[50], tex2[50];
	int id,opcao,res;
	
	inicializar(Tabela);
	
	do
	{
		printf("\n(1)inserir (2)Remover (3)Alterar (4)Pesquisar (5)Exibir (0)Sair:");
		scanf("%i",&opcao);
		switch(opcao)
		{
			//Inserir
			case 1: printf("Texto:");
					scanf(" %[^\n]", tex);
			
					id = gerar_indice(tex);
					if(pesquisar(Tabela,tex,id) == NULL)
					{
						res = inserir(Tabela,tex,id);
						if(res == 1)
						{
							printf("\nInserido com suscesso!");
						}
						else
						{
							printf("\nERRO ao inserir!");
						}
					}
					else
					{
						printf("\nERRO:Texto ja se encontra na lista!");
					}
			break;
			//remover
			case 2: printf("Texto:"); 
					scanf(" %[^\n]", tex);
					id = gerar_indice(tex); 
					res = remover(Tabela,tex,id);
					if(res == 1)
					{
						printf("Removido!");
					}
					else
					{
						printf("Texto nao encontrado!");
					}
			break; 
			//alterar
			case 3: printf("Texto a ser alterado: ");
					scanf(" %[^\n]", tex);
					printf("Texto que ira substituir: ");
					scanf(" %[^\n]", tex2);
					
					res = alterar(Tabela,tex,tex2);
					if(res == 1)
					{
						printf("Alteracao feita corretamente!");
					}
					else if(res == 2)
					{
						printf("ERRO: Texto a ser alterado NAO ENCONTRADO!!");
					}
					else if(res == 3)
					{
						printf("ERRO: Texto que ira substituir JA EXISTE!!");
					}
					else
					{
						printf("ERRO na alteracao!");
					}
					
			break; 
			// pesquisar
			case 4: printf("Texto:");
					scanf(" %[^\n]", tex);
			
					id = gerar_indice(tex); 
					aux = pesquisar(Tabela,tex,id);
					if(aux != NULL)
					{
						printf("ENCONTRADO: Lista %d no endereco %p", id, aux);
					}
					else
					{
						printf("Nao Encontrado!");
					}
			break; 
			// exibir;
			case 5: printf("\n(1)Exibir Tudo (2)Escolher Uma Lista: ");
					scanf("%d", &opcao);
					if(opcao == 1)
					{
						exibir_tudo(Tabela);
					}
					else
					{
						printf("\nEscolha uma lista de 0 a 9: ");
						scanf("%d", &id);
						if(id >= 0 && id <= 9)
						{
							exibir(Tabela,id);
						}
						else
						{
							printf("\nOpcao incorreta! tente novamente!");
						}
					}
			
			break; 
			case 0: printf("\n\nSistema encerrado!");
			break;
			default: printf("\nOpcao incorreta!");
				
		}
		printf("\n\n");
		system("pause");
		system("cls");
	}while(opcao != 0);
	
	return 0;
}


