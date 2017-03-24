#ifndef arvoreRetangulo_INCLUDED
#define arvoreRetangulo_INCLUDED

//indica um nó da arvore
typedef void* retangulo;

//Cria uma árvore vázia
void createArvore (retangulo *raiz);

//Insere um retângulo na árvore
void insereRetang (double x, double y, double larg, double alt, char cor[20], retangulo *raiz);


//Troca a cor dos retângulos de cor1 para cor2
void trocaCor (retangulo raiz,char cor1[20], char cor2[20]);

//Imprime os dados da árvore.
void imprimeDados (retangulo raiz);

//Remove o(s) nó(s) que esteja dentro ou seja igual do triângulo indicado
void removeRetangulo (double x, double y, double larg, double alt, retangulo *raiz); 

//Função que retorna  quantidade de nós da árvore
int quantidadeNos ();

// Gera o arquivo svg
void imprimeSVG (retangulo raiz,double x,double y,char sufixo[100]);

//funçao do imprime svg
void imprimeRetan (retangulo raiz,char nomeSVG[100]);

//verifica se um retangulo esta contido em outro
int VerRetan(double x, double y, double larg, double alt,double x1, double y1, double larg1, double alt1);

//troca a cor dos retangulos contidos no retangulo passado por parametro
void trocaRetan(retangulo *raiz,char cor1[20], char cor2[20], double x, double y, double larg, double alt);

// gera o resumo do teste
void Resumo(char diretorio[100],char nomeArq[100],long int prof);

//profundidade da arvore
int height(retangulo raiz);


#endif // arvoreRetangulo_INCLUDED
