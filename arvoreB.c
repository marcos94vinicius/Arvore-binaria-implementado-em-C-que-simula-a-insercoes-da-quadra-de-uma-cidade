#include<stdio.h>
#include<stdlib.h>
#include "arvoreB.h"

//estrutura que é um nó da árvore
struct No{

	apontNo left;
	apontNo right;
	InfoNo dado;
	apontNo father;
};
typedef struct No No;

//Atribuindo NULL, árvore vázia
apontNo emptyTree (){

	return NULL;
}

//Inserindo um único nó, que vai receber o conteúdo
apontNo makeTree (InfoNo x){

	No *newNo = (No *)malloc(sizeof(No));

	if(newNo == NULL)
		return NULL;

	newNo->dado = x;
	newNo->left = NULL;
	newNo->right = NULL;
	newNo->father = NULL; 

	return newNo;
}

//Retorna 1 se p estiver antes de d, -1 caso contrário
int isAncestor (apontNo p, apontNo d){
	
	if (p == NULL)
		return -1;	
		
	No *pontD = (No*)d;
	No *pontPai = (No *)pontD->father;

	while(pontPai != NULL){

		if (pontPai == p)
			return 1;
		pontPai = pontPai->father;
	}
	return -1;
}

//Associa left a p->lft
void setLeft (apontNo p, apontNo lft){

	if(p == NULL)
		return;	
	
	int x = isAncestor (lft, p);
	if(x == 1)
		return;	
	else{

		No *pontP = (No *)p;
		No *pontLft = (No*)lft;
		pontP->left = lft;
		if (pontLft != NULL)
			pontLft->father = p;
	}
}

//Associa rgt a p->right
void setRight (apontNo p, apontNo rgt){

	if(p == NULL)
		return;

	int x = isAncestor (rgt, p);
	if(x == 1)
		return;

	else{

		No *pontP = (No*)p;
		No *pontRgt = (No*)rgt;
		pontP->right = rgt;
		if (pontRgt != NULL)
			pontRgt->father = p;
	}
}

//A sub-árvore indicada por p é associada com a sub-árvore "father" da árvore indicada por fat.
void setFather (apontNo p, apontNo fat){
	
	if (fat == NULL)
		return;
	
	int x = isAncestor(fat, p);
	if(x == -1)
		return;
	else{

		No * aux = (No *)p;
		aux->father = fat;
	}
}

//Retorna o endereço do pai do respectivo nó
apontNo father (apontNo d){
	
	if (d == NULL)
		return NULL;
	No *aux = (No*)d;
	return (aux->father);
}

//Retorna o endereço do sub-nó esquerdo da árvore
apontNo left (apontNo p){
	
	if(p == NULL)
		return NULL;
	
	No *aux = (No *)p;
	if(aux->left == NULL)
		return NULL;
	else
		return aux->left;
}

//Retorna o endereço do sub-nó direito da árvore
apontNo right (apontNo p){

	if(p == NULL)
		return NULL;

	No *aux = (No *)p;
	if(aux->right == NULL)
		return NULL;
	else
		return aux->right;		
}

//Retorna o irmão do nó indicado por d. Caso d não possua um irmão, retorna NULL.
apontNo brother (apontNo d){

	No *auxD = (No*)d;
	No *btr = (No*)auxD->father;

	if (auxD == btr->left)
		return (btr->right);
	else
		return (btr->left);	
}

//Retorna verdadeiro se lft é o filho esquerdo do nó indicado por p.
int isLeft (apontNo p, apontNo lft){

	No *aux = (No*)p;
	
	if(aux->left == (No *)lft)
		return 1;
	else
		return -1;
}

//Retorna verdadeiro se rgt é o filho direito do nó indicado por p.
int isRight (apontNo p, apontNo rgt){

	No *aux = (No*)p;

	if(aux->right == (No*)rgt)
		return 1;
	else
		return -1;
}

//Retorna verdadeiro se p é o pai do nó indicado por d.
int isFather (apontNo p, apontNo d){

	No *aux = (No*)p;

	if(aux->left == (No*)d || aux->right == (No*)d)
		return 1;
	else
		return -1;
}

//Retorna a informação armazenada no nó indicado por p.
InfoNo info (apontNo p){
	
	if(p == NULL)
		return;

	No *aux = (No*)p;
	return (aux->dado);
}
  
//Método que remove o nó indicado por p.
apontNo Remove (apontNo p){

	//Caso a árvore esteja vázia
	if (p == NULL)
		return NULL;

	No *aux = (No *) p;
	No *pai = (No *) aux->father;
	No *aux2, *aux3, *aux4;

	//Caso seja a raiz e seus filhos forem NULL
	if (aux->father == NULL && aux->left == NULL && aux->right == NULL){

		free (aux);
		return NULL;
	}
	
	//Caso esteja removendo um nó que seja uma folha (não tenha nem um filho)
	if (aux->left == NULL && aux->right == NULL){

		free (aux);
		return NULL;
	}
	//Caso remova um nó que tenha um filho (um dos filhos não é NULL)
	if ((aux->left == NULL && aux->right != NULL) || (aux->left != NULL && aux->right == NULL)){
	
		if (aux->left == NULL){
			
			aux2 = aux->right;
			free (aux);
			return aux2;
		}else{

			aux2 = aux->left;
			free (aux);
			return aux2;
		}
	}
	//Removendo nó que tenha os dois filhos
	if (aux->left != NULL && aux->right != NULL){
	
		No *auxl = left (aux), *aux3;
		No *paiAux3;	
		int help = 0;
		while(auxl != NULL){

			aux3 = auxl;
			auxl = right (auxl);
		}
		paiAux3 = (No *)aux3->father;
		if (paiAux3->left == aux3)
			help = 1;
		aux->dado = aux3->dado;
		aux4 = Remove (aux3);
		if (help == 1)
			setLeft (paiAux3, aux4);
		else
			setRight (paiAux3, aux4);
		return aux;
	}	
}
