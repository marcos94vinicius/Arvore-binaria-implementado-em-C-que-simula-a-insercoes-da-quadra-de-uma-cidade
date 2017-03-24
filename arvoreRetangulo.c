#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arvoreB.h"
#include "arvoreRetangulo.h"

//Estrutura que contém os dados do retângulo
struct retang{
	
	double x;
	double y;
	double larg;
	double alt;
	double area;
	char cor[20];
};
typedef struct retang retang;

//Contador para armazenar a quantidade de nós da árvore
int cont = 0;
long int cont1=0;
long int Inseridos=0;
long int Removidos=0;


//Cria uma árvore vázia
void createArvore (retangulo *raiz){

	*raiz = emptyTree();
}

//Insere um retângulo na árvore
void insereRetang (double x, double y, double larg, double alt, char cor[20], retangulo *raiz){

	retang *novoRetangulo = (retang *)malloc(sizeof(retang));
	novoRetangulo->x = x;
	novoRetangulo->y = y;
	novoRetangulo->larg = larg;
	novoRetangulo->alt = alt;
	novoRetangulo->area = larg * alt;
	strcpy(novoRetangulo->cor,cor);
	cont++;
	Inseridos++;

	apontNo no = makeTree(novoRetangulo);

	if (*raiz == NULL){

		*raiz = no;
		return;		
	}
	else{

		//ponteiro auxiliar que aponta para a raiz
		apontNo aux = *raiz;
		apontNo aux2;
		//ponteiro que recebe o conteudo de cada mó da árvore
		retang *auxRetan = (retang *) info (aux);
		//entra no while até encontrar a posição certa de inserir
		while(1){

			if(novoRetangulo->area > auxRetan->area){
		
				aux2 = right(aux);
				if(aux2 == NULL){

					setRight (aux, no);
					setFather (aux, no);
					return;
				}
				aux = right (aux);
			}
			else{

				aux2 = left(aux);
				if(aux2 == NULL){

					setLeft (aux, no);
					setFather (aux, no);
					return;
				}			
				aux = left (aux);
			}
			auxRetan = (retang *) info (aux);
		}
	}
}

//imprime o campo "área" de todos os nós da árvore
void imprimeDados (retangulo raiz){

	if (raiz == NULL)
		return;
	retang *aux = (retang *) info (raiz);
	printf ("ALTURA: %lf\n", aux->alt);
	retangulo esq, dir;
	esq = left (raiz);
	dir =  right (raiz);
	imprimeDados (esq);
	imprimeDados(dir);
}



//Remove o(s) nó(s) que esteja dentro ou seja igual do triângulo indicado
void removeRetangulo (double x, double y, double larg, double alt, retangulo *raiz){
	if (*raiz == NULL)
		return;
	retangulo aux = *raiz;
	retang *conteudo = (retang *) info (aux);
	retangulo pai = father (aux);
	retangulo verifica = left (pai);
	int help = 0;  //Variável que ajuda a verifica qual filho vou remover (direito ou esquerdo)
	retangulo set = aux;
	int v;
	
	if( (conteudo->x >= x) && ((conteudo->x + conteudo->larg) <= (x + larg)) && (conteudo->y >= y) && ((conteudo->y + conteudo->alt) <= (y + alt)) ){
	
		if (verifica == aux)
			help = 1;
		set = Remove (aux);	
		if (help == 1)
			setLeft (pai, set);
		else
			setRight (pai, set);
		if (pai == NULL)
			*raiz = set;
		cont--;
		Removidos++;
		
	}

	if (set == NULL || *raiz == NULL)
		return;

	retangulo esq, dir;	
	esq = left (set); 
	dir = right (set);
	retang *conteudoDIR = (retang *) info(dir);	

	removeRetangulo (x, y, larg, alt, &esq);
	if (dir != NULL)
		if (conteudoDIR->area <= (alt * larg))
			removeRetangulo (x, y, larg, alt, &dir);
}

//Função que retorna  quantidade de nós da árvore
int quantidadeNos (){

	return cont;
}


//Funçao q gera o arquivo svg
void imprimeSVG (retangulo raiz,double x,double y,char nomeSVG[100]){
	FILE *arq;

	strcat(nomeSVG,".svg");
	
	arq=fopen(nomeSVG,"w");

    fprintf(arq,"<svg height=\"%lf\" width=\"%lf\">\n",y,x);
	
	fclose(arq);
	
	imprimeRetan(raiz,nomeSVG);
	
	arq=fopen(nomeSVG,"a");
	fprintf(arq,"</svg>");
	fclose(arq);
}

//Funçao q gera o arquivo svg
void imprimeRetan (retangulo raiz,char nomeSVG[100]){
	FILE *arq;
	arq=fopen(nomeSVG,"a");
	if (raiz == NULL){
		
		return;}
	retang *aux = (retang *) info (raiz);
	fprintf (arq,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:%s;stroke:black;stroke-width:0.5\"/>\n", aux->x,aux->y,aux->larg,aux->alt,aux->cor);
	retangulo esq, dir;
	esq = left (raiz);
	dir =  right (raiz);
	imprimeRetan(esq,nomeSVG);
	imprimeRetan(dir,nomeSVG);
	fclose(arq);
}

//Funçao que troca os retangulos de cor1 para cor2
void trocaCor (retangulo raiz,char cor1[20], char cor2[20]){

	if (raiz == NULL)
		return;
	retang *aux = (retang *) info (raiz);
	if (strcmp(cor1,aux->cor)==0){
		strcpy(aux->cor,cor2);
		cont1++;
	}
	retangulo esq, dir;
	esq = left (raiz);
	dir =  right (raiz);
	trocaCor (esq,cor1,cor2);
	trocaCor (dir,cor1,cor2);

}

//funçao que troca as cores de todos os retangulos contidos no retangulo passado por parametro
void trocaRetan(retangulo *raiz,char cor1[20], char cor2[20], double x, double y, double larg, double alt){
	if (*raiz == NULL)
		return;
	retangulo aux = *raiz;
	retang *conteudo = (retang *) info (aux);
	retangulo pai = father (aux);
	retangulo verifica = left (pai);
	int help = 0;  
	
	if( (conteudo->x >= x) && ((conteudo->x + conteudo->larg) <= (x + larg)) && (conteudo->y >= y) && ((conteudo->y + conteudo->alt) <= (y + alt)) ){
		strcpy(conteudo->cor,cor2);
		cont1++;
	}

	retangulo esq, dir;	
	esq = left (aux); 
	dir = right (aux);
	retang *conteudoDIR = (retang *) info(dir);	

	trocaRetan (&esq,cor1,cor2, x, y, larg, alt);
	if (dir != NULL)
		if (conteudoDIR->area <= (alt * larg))
			trocaRetan (&dir, cor1, cor2, x, y, larg, alt);
	
}

//funçao que gera o resumo do arquivo
void Resumo(char diretorio[100],char nomeArq[100],long int prof){
	
	FILE *arq;
	strcat(diretorio,"/resumo.txt");
	
	arq=fopen(diretorio,"a");
	
	fprintf(arq,"%s %li %d %li %li %li\n",nomeArq,cont,prof,Inseridos,Removidos,cont1);
	
	fclose(arq);
}

//funçao para verificar profundidade
int height(retangulo raiz) {

    int u, v;
    if (raiz == NULL)
		return -1;
	retang *aux = (retang *) info (raiz);
	retangulo esq, dir;
	esq = left (raiz);
	dir =  right (raiz);
	u=height (esq);
	v=height(dir);
    if (u > v) return u+1;
    else return v+1;
}

