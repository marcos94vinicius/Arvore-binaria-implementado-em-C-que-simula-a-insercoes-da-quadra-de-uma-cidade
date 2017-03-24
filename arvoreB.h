#ifndef arvoreB_INCLUDED
#define arvoreB_INCLUDED

//Indica um nó da árvore.
typedef void* apontNo;

//Informação armazenada no nó da árvore.
typedef void* InfoNo;

//Cria uma árvore vazia
apontNo emptyTree ();

//Cria uma (sub-)árvore com um único nó contendo a informação X.
apontNo makeTree (InfoNo x);

//Retorna verdadeiro se p é ancestral do nó indicado por d.
int isAncestor (apontNo p, apontNo d);

//A sub-árvore indicada por lft é associada com a sub-árvore esquerda da árvore do nó indicado por p.
void setLeft (apontNo p, apontNo lft);

//A sub-árvore indicada por rgt é associada com a sub-árvore direita da árvore do nó indicado por p.
void setRight (apontNo p, apontNo rgt);

//A sub-árvore indicada por p é associada com a sub-árvore "father" da árvore indicada por fat.
void setFather (apontNo p, apontNo fat);

//Retorna o nó pai do nó indicado por d. Caso d seja a raiz da árovere, retorna NULL.
apontNo father (apontNo d);

//Retorna o filho esquerdo do nó indicado por p. Caso a sub-árvore esquerda de p seja vazia, retorna NULL.
apontNo left (apontNo p);
//Retorna o filho direito do nó indicado por p. Caso a sub-árvore direita de p seja vazia, retorna NULL.
apontNo right (apontNo p);

//Retorna o irmão do nó indicado por d. Caso d não possua um irmão, retorna NULL.
apontNo brother (apontNo d);

//Retorna verdadeiro se lft é o filho esquerdo do nó indicado por p.
int isLeft (apontNo p, apontNo lft);

//Retorna verdadeiro se rgt é o filho direito do nó indicado por p.
int isRight (apontNo p, apontNo rgt);

//Retorna verdadeiro se p é o pai do nó indicado por d.
int isFather (apontNo p, apontNo d);

//Retorna a informação armazenada no nó indicado por p.
InfoNo info (apontNo p);

//Método que remove o nó indicado por p.
apontNo Remove (apontNo p);

#endif // arvoreB_INCLUDED
