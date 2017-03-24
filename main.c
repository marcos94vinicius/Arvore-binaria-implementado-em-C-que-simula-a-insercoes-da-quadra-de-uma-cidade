#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arvoreRetangulo.h"

main(int argc, char *argv[]){

	//tratamento do(s) argumento(s)
	int i = 1;
	char *nomeArq;
	char *dir;

	while(i < argc){
		
		if(strcmp("-f", argv[i]) == 0){
			i++;
			nomeArq = (char *) malloc ((strlen(argv[i])+1)*sizeof(char));
			strcpy(nomeArq, argv[i]);
		}
			
		if(strcmp("-o", argv[i]) == 0){
			i++;
			dir = (char *) malloc ((strlen(argv[i])+1)*sizeof(char));
			strcpy(dir, argv[i]);
		}
		i++;
	}
	//Leitura do arquivo
	
	///home/vitor/Área de Trabalho/Trabalho3/tmx1-001.ops tmx1-001.ops
	
	//pega apenas o nome do arquivo ,do seu endereço
	char nomeArq1[100];
	char nomeArq2[100];
	i=0;
	int j=0;
	int cont=0;
	
	strcpy(nomeArq1,nomeArq);
	
	while(nomeArq1[i]!='\0'){
		if(nomeArq1[i]=='/'){
			cont++;
		}
		i++;
	}
	i=i+3;
	if(cont>0){
		while(nomeArq1[i]!='/'){
			i--;
		}
		i++;
		while(nomeArq[i]!='.'){
			nomeArq2[j]=nomeArq1[i];
			i++;
			j++;
		}
		nomeArq2[j]='\0';
	}
	else{
		
		strcpy(nomeArq2,nomeArq1);
		i=0;
		while(nomeArq2[i]!='\0'){
			if(nomeArq2[i]=='.'){
				nomeArq2[i]='\0';
			}
			i++;
		}
	}

	//leitura e respectivo tratamento para cada funçao
	
	char string[100];
	char ch;
	FILE *file = fopen (nomeArq, "r");
	
	
	retangulo raiz;
	createArvore(&raiz); 
	
	double x,y,larg,alt;
	double xmax=0,ymax=0,largmax=0,altmax=0;
	char cor[20];
	char cor1[20],cor2[20];
	char sufixo[100];

	while(1){

		ch=fgetc(file);
		if (ch == '#')
			break;
		if (ch=='r'){
			
			putchar(ch);
			fscanf(file," %lf %lf %lf %lf %s\n",&x,&y,&larg,&alt,&cor);
		
			insereRetang(x,y,larg,alt,cor,&raiz);
			if(x>xmax)
				xmax=x;
			if(y>ymax)
				ymax=y;
			if(larg>largmax)
				largmax=larg;
			if(alt>altmax)
				altmax=alt;
		}
		if (ch=='c'){
			
			x=-1;
			y=-1;
			larg=-1;
			alt=-1;
			putchar(ch);
			fscanf(file," %s %s [%lf %lf %lf %lf]\n",cor1,cor2,&x,&y,&larg,&alt);
		
			if(x==-1 && y==-1 && larg==-1 && alt==-1){
				trocaCor(raiz,cor1,cor2);
			}
			else{
				trocaRetan(&raiz,cor1,cor2,x,y,larg,alt);
			}
		}
		if (ch=='d'){
			
			putchar(ch);
			fscanf(file," %lf %lf %lf %lf\n",&x,&y,&larg,&alt);
			
			int w,z;
			w=0;
			z=quantidadeNos();
			while(w<z){
				removeRetangulo(x,y,larg,alt,&raiz);
				w++;
			}
			
		}
		if (ch=='o'){
			
			
			putchar(ch);
			fscanf(file," %s\n",&sufixo);
			
			strcpy(nomeArq1,dir);
			strcat(nomeArq1,"/");
			strcat(nomeArq1,nomeArq2);
			strcat(nomeArq1,"-");
			strcat(nomeArq1,sufixo);
			
			strcpy(sufixo,nomeArq1);
			imprimeSVG (raiz,xmax+largmax+10,ymax+altmax+10,sufixo);
			
		}
	}
	long int prof=0;
	prof=height(raiz);
	strcpy(nomeArq1,dir);
	Resumo(nomeArq1,nomeArq2,prof);


	return 0;
}
