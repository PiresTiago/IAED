/********************/
/*TIAGO PIRES N89544*/
/********************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 9999
#define MAX2 20000
#define MAX_FICH 80

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch1(A, B) { unsigned long t = A; A = B; B = t; }
#define exch2(A, B) { double t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch1(A, B)
#define Atribuicao(A, B) {unsigned long t = A;B=t;}
#define comp1(A, B) if(less(A,B)) Atribuicao(A,B)
#define comp2(A, B) if(less(B,A)) Atribuicao(A,B)

/*Estrutura que armazena os inputs recebidos/entradas da matriz esparsa*/
typedef struct
{
	unsigned long linha, coluna;
	double valor;
}valor;

/*Estrutra que armazena as entradas do Vetor Densidade*/
typedef struct
{
	unsigned long linha;
	double densidade;
}VecDensidade;

/*
------------------------------
      VARIAVEIS GLOBAIS
------------------------------
*/
VecDensidade vetor_densidade[MAX];
valor Matriz[MAX];
unsigned long cnt=0, mini, maxi, minj, maxj;
double zero=0, dens;
char flag, filename[MAX_FICH+1];


/*
 __        __   __        ___     __   __   __  ___ 
|__) |  | |__) |__) |    |__     /__` /  \ |__)  |  
|__) \__/ |__) |__) |___ |___    .__/ \__/ |  \  |  
                                                                                                
*/

/*Ordena por ordem crescente do numero de linha e dentro de cada linha,
por ordem crescente do numero de coluna*/
void bubble_linhas()
{
	unsigned long i, j;
	int done; /*<- flag*/
	for (i = 0; i < cnt; i++)
	{
		done = 1;
		for (j = cnt-1; j > i; j--)
			if (less(Matriz[j].linha, Matriz[j-1].linha))
			{
				exch1(Matriz[j-1].linha, Matriz[j].linha);
				exch1(Matriz[j-1].coluna, Matriz[j].coluna);
				exch2(Matriz[j-1].valor, Matriz[j].valor);
				done = 0;
			}
		if (done) break;
	}
	for (i = 0; i < cnt; i++)
	{
		done = 1;
		for (j = cnt-1; j > i; j--)
			if (less(Matriz[j].coluna, Matriz[j-1].coluna) && 
				Matriz[j].linha == Matriz[j-1].linha)
			{
				exch1(Matriz[j-1].linha, Matriz[j].linha);
				exch1(Matriz[j-1].coluna, Matriz[j].coluna);
				exch2(Matriz[j-1].valor, Matriz[j].valor);
				done = 0;
			}
		if (done) break;
	}
}

/*Ordena por ordem crescente do numero de coluna e dentro de cada coluna,
por ordem crescente do numero de linha*/
void bubble_colunas()
{
	unsigned long i, j; 
	int done;
	for (i = 0; i < cnt; i++)
	{
		done = 1;
		for (j = cnt-1 ; j > i ; j--)
			if (less(Matriz[j].coluna, Matriz[j-1].coluna))
			{
				exch1(Matriz[j-1].linha, Matriz[j].linha);
				exch1(Matriz[j-1].coluna, Matriz[j].coluna);
				exch2(Matriz[j-1].valor, Matriz[j].valor);
				done = 0;
			}
		if (done) break;
	}
	for (i = 0; i < cnt; i++)
	{
		done = 1;
		for (j = cnt-1 ; j > i ; j--)
			if (less(Matriz[j].linha, Matriz[j-1].linha) && 
				Matriz[j].coluna == Matriz[j-1].coluna)
			{
				exch1(Matriz[j-1].linha, Matriz[j].linha);
				exch1(Matriz[j-1].coluna, Matriz[j].coluna);
				exch2(Matriz[j-1].valor, Matriz[j].valor);
				done = 0;
			}
		if (done) break;
	}
}

/*Ordena o vetor Densidade por ordem decrescente de densidade de cada linha*/
void bubble_densidade()
{
	unsigned long i, j; 
	int done; 
	for (i = 0; i < cnt; i++)
	{
		done=1;
		for (j = cnt-1; j > i; j--)
			if (less(vetor_densidade[j-1].densidade,vetor_densidade[j].densidade))
			{
				exch1(vetor_densidade[j-1].linha,vetor_densidade[j].linha);
				exch1(vetor_densidade[j-1].densidade,vetor_densidade[j].densidade);
				done=0;
			}
		if (done) break;
	}
}
/*                                                                                                                                                                                                              
__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __                                                                                                                                                                                                                                                                                                                                                                                                                                                 

*/

/*Funcao que atualiza os extremos da Matriz esparsa,
em relacao 'as linhas e 'as colunas*/
void Atualiza_Limites()
{
	unsigned long i;

	mini = Matriz[0].linha; maxi = Matriz[0].linha;
	minj = Matriz[0].coluna; maxj = Matriz[0].coluna;

	for (i = 0; i < cnt; i++)
	{
		comp1(Matriz[i].linha,mini); comp2(Matriz[i].linha,maxi);
		comp1(Matriz[i].coluna,minj);comp2(Matriz[i].coluna,maxj);
	}
}

/*Funcao que limpa o buffer apos o input 'o coluna'*/
void clearBuffer ()
{
    char c;
    do{
    c = getchar();
    }while(c != '\n' && c != EOF);
}

/*Funcao que adiciona uma entrada 'a Matriz esparsa*/
void Adiciona_elem(valor c)
{
	int entrada_nao_existe = 1, valor_zero = 0; /*<- flags*/
	unsigned long i, j;

	scanf("%lu %lu %lf", &c.linha , &c.coluna , &c.valor);

	if (cnt <= MAX && c.valor != zero)	 /*Se o valor for diferente de 0 o*/
	{					 	 			 /*elemento e' guardado na matriz*/
		for(i = 0; i < cnt; i++)
			if (Matriz[i].linha == c.linha && Matriz[i].coluna == c.coluna)
			{
				Matriz[i].valor = c.valor;
				entrada_nao_existe = 0;
			}
		if (entrada_nao_existe)
		{
			Matriz[cnt].linha = c.linha;
			Matriz[cnt].coluna = c.coluna;
			Matriz[cnt].valor = c.valor;
			cnt++;
			Atualiza_Limites();
		}
	}
	else 	/* Se o valor da variavel valor do input for o zero atual,*/
	{		/*a entrada,relativa ao input, da matriz e' eliminada*/
		for(i = 0 ,j = 0 ;i < cnt; i++)
		{
			if ((Matriz[i].linha == c.linha) && (Matriz[i].coluna == c.coluna))
				valor_zero = 1;/*flag que sinaliza que foi encontrado uma
							     entrada na matriz com os dados do input*/
			else 				
				Matriz[j++] = Matriz[i];
		}
		if (valor_zero) cnt--;/*decrementa o numero de entradas no vetor
							    de estrutras(matriz) pois houve uma 
							    que foi eliminada*/
		Atualiza_Limites();
	}
}


/*Funcao que faz o output dos elementos presentes na Matriz esparsa,
para o terminal.*/
void Lista_elem()
{
	unsigned long i;

	for (i = 0; i < cnt; i++)
		printf("[%lu;%lu]=%.3lf\n", 
			Matriz[i].linha , Matriz[i].coluna , Matriz[i].valor);

	if (cnt == 0)
		printf("empty matrix\n");
}

/*Funcao que faz o output dos extremos da Matriz esparsa, 
do seu numero de elementos(valores!=0),da sua dimensao
e da sua densidade, para o terminal*/
void Lista_lim_dens()
{
	unsigned long size, nelem = cnt;

	if (nelem == 0)
		printf("empty matrix\n");
	else
	{
		size = (maxi - mini + 1) * (maxj - minj + 1);
		dens = (((double) nelem) / size) * 100;
		printf("[%lu %lu] [%lu %lu] %lu / %lu = %.3f%%\n", 
			mini , minj , maxi , maxj , nelem , size , dens);
	}
}

/*Funcao que faz o output de uma linha da Matriz esparsa
para o terminal*/
void Lista_linha(valor c)
{
	unsigned long i, coluna;
	int existe_elem = 1, existe_elem_n_representavel = 1; /*<- flags*/
	scanf("%lu", &c.linha);

	for (i = 0; i < cnt; i++)
		if (Matriz[i].linha == c.linha)
			existe_elem = 0;

	if (existe_elem || c.linha > maxi || c.linha < mini)
		printf("empty line\n");

	else
	{
		for(coluna = minj; coluna <= maxj; coluna++)
		{
			for(i=0 ;i < cnt; i++)
				if ((Matriz[i].coluna == coluna) && (Matriz[i].linha == c.linha))
				{
					printf(" %.3lf",Matriz[i].valor);
					existe_elem_n_representavel = 0;/*flag que sinaliza 
					 								se existem elementos nao		
												    representaveis na linha*/
				}
			if (existe_elem_n_representavel) printf(" %.3lf",zero);
			existe_elem_n_representavel = 1;
		}
		printf("\n");
	}
}

/*Funcao que faz o output de uma coluna da Matriz esparsa
para o terminal*/
void Lista_coluna(valor c)
{
	unsigned long i,linha;
	int existe_elem = 1, existe_elem_n_representavel = 1; /*<- flags*/
	scanf("%lu", &c.coluna);

	for (i = 0 ; i <= cnt; i++)
		if (Matriz[i].coluna == c.coluna) 
			existe_elem = 0;

	if (existe_elem || c.coluna > maxj || c.coluna < minj)
		printf("empty column\n");

	else
	{
	 	for(linha = mini;linha <= maxi; linha++)
	 	{
	 		for(i = 0;i <= cnt; i++)
	 			if (Matriz[i].linha == linha && Matriz[i].coluna == c.coluna)
	 			{
	 				printf("[%lu;%lu]=%.3lf\n",
	 					Matriz[i].linha, Matriz[i].coluna, Matriz[i].valor);
	 				existe_elem_n_representavel = 0;/*flag que sinaliza se  			
												     existem elementos nao
												     representaveis na coluna*/ 
	 			} 
	 		if (existe_elem_n_representavel) printf("[%lu;%lu]=%.3lf\n",
	 			linha,c.coluna,zero);
	 		existe_elem_n_representavel = 1;
	 	}
	}
}

/*Funcao que utiliza o bubblesort para ordenar a Matriz esparsa*/
void Ordena(valor c)
{
	flag = getchar();

	if (flag != '\n')
	{
		bubble_colunas();	
		clearBuffer();
	}	

	else	
		bubble_linhas();
}

/*Funcao que altera o valor do zero atual e como a Matriz esparsa
nao guarda valores zero, e' feita uma verificacao de zeros presente no vetor
e sao eliminados os que sao encontrados*/
void Define_zero(valor c)
{
	unsigned long i,j,contador_zeros = 0;
	scanf("%lf", &c.valor);
	zero = c.valor;

	for(i = 0, j = 0; i < cnt; i++)
	{
		if (Matriz[i].valor != zero)
			Matriz[j++] = Matriz[i];
		else
			contador_zeros++;
	}

	cnt -= contador_zeros;
	Atualiza_Limites();		
}

void Compressor()
{
	unsigned long i, j, w = 0, k = 0, nelem = 0,
	deslocamento=0, max_deslocamento=0, index[MAX2], offset[MAX2];
	double valores[MAX2];
	int Necessita_offset=0, first_run=1;/* <- flags*/
	
	if (dens > 50)
		printf("dense matrix\n");
	else
	{
		/*Ciclo que inicializa as variaveis ate' maxi, pois nao e' preciso mais*/
		for(i = 0; i <= maxi; i++)
		{
			valores[i] = zero; index[i] = zero;
			offset[i] = zero; vetor_densidade[i].densidade=0;
			vetor_densidade[i].linha=-1;
		}
		/*Ciclo que cria um vetor de estrutras(vetor densidade)*/
		for (i = mini; i <= maxi; i++)
		{
			for(j = 0; j < cnt; j++)
				if (Matriz[j].linha == i) nelem++;
			if (nelem != 0)
			{
				vetor_densidade[w].linha = i;
				vetor_densidade[w++].densidade = (((double) nelem)/(maxj-minj+1));
			}
			nelem = 0;
		}
		bubble_densidade();
		
		for (i = 0; i <=maxi; i++) /*Percorre o vetor_densidade*/
		{
		 /*Este vetor e' criado para que nao seja necessario voltar a percorrer
		  a matriz esparsa toda caso seja necessario o uso de um offset*/
			unsigned long indices_matriz[MAX2];
			first_run=1;
			for(j = 0; j < MAX2; j++)
				indices_matriz[j]=-1;

			while(1)
			{
				if (first_run)
				{
					first_run=0;
					for (j = 0; j < cnt; j++) /*Percorre a Matriz esparsa*/
						if (Matriz[j].linha == vetor_densidade[i].linha)
						{
							indices_matriz[k++]=j;
							if(valores[Matriz[j].coluna+deslocamento] != zero)
								Necessita_offset=1;
						}
					
					if (Necessita_offset == 1)
					{
						Necessita_offset=0;
						deslocamento++;
						continue;
					}

					else break;
				}

				else
				{
					for(j = 0;indices_matriz[j]!=-1;j++)
						if (valores[Matriz[indices_matriz[j]].coluna+deslocamento] != zero)
							Necessita_offset=1;
					if (Necessita_offset == 1)
					{
						deslocamento++;
						Necessita_offset=0;
						continue;
					}

					else break;
				}				
			}

			if (deslocamento>max_deslocamento) max_deslocamento=deslocamento;

			for (j = 0;indices_matriz[j]!=-1; j++)
			{
				valores[Matriz[indices_matriz[j]].coluna+deslocamento] = Matriz[indices_matriz[j]].valor;		
				index[Matriz[indices_matriz[j]].coluna+deslocamento]=vetor_densidade[i].linha;
			}
		
			offset[vetor_densidade[i].linha]=deslocamento;
			deslocamento=0;
			Necessita_offset=0;
			k=0;/*k => iterador do vetor indices_matriz volta a zero no final de cada ciclo*/
		}

		printf("value =");
		for (i = minj; i <= (maxj+max_deslocamento); i++)
			printf(" %.3lf",valores[i]);
		printf("\n");

		printf("index =");
		for (i = minj; i <= (maxj+max_deslocamento); i++)
			printf(" %lu",index[i]);
		printf("\n");

		printf("offset =");
		for (i = mini; i <= maxi; i++)
			printf(" %lu",offset[i]);
		printf("\n");
	}
}	

/*Funcao que guarda o conteudo da Matriz esparsa num ficheiro*/
void Guarda_Matriz(valor c)
{
	flag = getchar();
	unsigned long i;
	FILE *fp;
	
	if (flag != '\n')
		scanf("%s", filename);

	fp = fopen(filename,"w");

	for(i = 0; i < cnt; i++)
		fprintf(fp,"%lu %lu %.3lf\n",
			Matriz[i].linha , Matriz[i].coluna , Matriz[i].valor);

	fclose(fp);
}


int main(int argc, char* argv [])
{
	valor input;
	char comando = getchar();

	if (argc>1) /*se argc>1 entao foi recebido um ficheiro e e' feito o loading*/
	{			/*do conteudo para a matriz esparsa,caso contrario,*/
				/*nao e' feito nada*/
		
		FILE *fp;
		
		strcpy(filename, argv[1]);
		
		fp = fopen(filename,"r");
		
		while(fscanf(fp,"%lu %lu %lf",
			&Matriz[cnt].linha,&Matriz[cnt].coluna,&Matriz[cnt].valor) > 0)
		{	
			if (cnt == MAX) break;
			cnt++;
		}

		fclose(fp);
	}

	while (comando != 'q')
	{
		switch (comando)
		{
			case 'a':
				Adiciona_elem(input);
				break;
			case 'p':
				Lista_elem();
				break;
			case 'i':
				Lista_lim_dens();
				break;
			case 'l':
				Lista_linha(input);
				break;
			case 'c':
				Lista_coluna(input);
				break;
			case 'o':
				Ordena(input);
				break;
			case 'z':
				Define_zero(input);
				break;
			case 's':
				Compressor();
				break;
			case 'w':
				Guarda_Matriz(input);
				break;
		}
		comando = getchar();
	}
	return 0;
}