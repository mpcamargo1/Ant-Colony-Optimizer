#include"lib.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INT_MAX 2147483647

// Carrega os valores das posições das cidades
void loadtsp(AntGraph *graph){
	 
     graph->city[0][0] = 565; 
     graph->city[0][1] = 575;
     graph->city[1][0] = 25; 
     graph->city[1][1] = 185;
     graph->city[2][0] = 345; 
     graph->city[2][1] = 750;
     graph->city[3][0] = 945; 
     graph->city[3][1] = 685;
     graph->city[4][0] = 845; 
     graph->city[4][1] = 655;
     graph->city[5][0] = 880; 
     graph->city[5][1] = 660;
     graph->city[6][0] =  25; 
     graph->city[6][1] = 230;
     graph->city[7][0] = 525; 
     graph->city[7][1] = 1000;
     graph->city[8][0] = 580; 
     graph->city[8][1] = 1175;
     graph->city[9][0] = 650; 
     graph->city[9][1] = 1130;
     graph->city[10][0] = 1605; 
     graph->city[10][1] = 620;
     graph->city[11][0] = 1220; 
     graph->city[11][1] = 580;
     graph->city[12][0] = 1465; 
     graph->city[12][1] = 200;
     graph->city[13][0] = 1530; 
     graph->city[13][1] = 5;
     graph->city[14][0] = 845; 
     graph->city[14][1] = 680;
     graph->city[15][0] = 725; 
     graph->city[15][1] = 370;
     graph->city[16][0] = 145; 
     graph->city[16][1] = 665;
     graph->city[17][0] = 415; 
     graph->city[17][1] = 635;
     graph->city[18][0] = 510; 
     graph->city[18][1] = 875; 
     graph->city[19][0] = 560; 
     graph->city[19][1] = 365;
     graph->city[20][0] = 300; 
     graph->city[20][1] = 465;
     graph->city[21][0] = 520; 
     graph->city[21][1] = 585;
     graph->city[22][0] = 480; 
     graph->city[22][1] = 415;
     graph->city[23][0] = 835; 
     graph->city[23][1] = 625;
     graph->city[24][0] = 975; 
     graph->city[24][1] = 580;
     graph->city[25][0] = 1215; 
     graph->city[25][1] = 245;
     graph->city[26][0] = 1320; 
     graph->city[26][1] = 315;
     graph->city[27][0] = 1250; 
     graph->city[27][1] = 400;
     graph->city[28][0] = 660; 
     graph->city[28][1] = 180;
     graph->city[29][0] = 410; 
     graph->city[29][1] = 250;
     graph->city[30][0] = 420; 
     graph->city[30][1] = 555;
     graph->city[31][0] = 575; 
     graph->city[31][1] = 665;
     graph->city[32][0] = 1150; 
     graph->city[32][1] = 1160;
     graph->city[33][0] = 700; 
     graph->city[33][1] = 580;
     graph->city[34][0] = 685; 
     graph->city[34][1] = 595;
     graph->city[35][0] = 685; 
     graph->city[35][1] = 610;
     graph->city[36][0] = 770; 
     graph->city[36][1] = 610;
     graph->city[37][0] = 795; 
     graph->city[37][1] = 645;
     graph->city[38][0] = 720; 
     graph->city[38][1] = 635;
     graph->city[39][0] = 760; 
     graph->city[39][1] = 650;
     graph->city[40][0] = 475; 
     graph->city[40][1] = 960;
     graph->city[41][0] = 95; 
     graph->city[41][1] = 260;
     graph->city[42][0] = 875; 
     graph->city[42][1] = 920;
     graph->city[43][0] = 700; 
     graph->city[43][1] = 500;
     graph->city[44][0] = 555; 
     graph->city[44][1] = 815;
     graph->city[45][0] = 830; 
     graph->city[45][1] = 485;
     graph->city[46][0] = 1170; 
     graph->city[46][1] = 65;
     graph->city[47][0] = 830; 
     graph->city[47][1] = 610;
     graph->city[48][0] = 605; 
     graph->city[48][1] = 625;
     graph->city[49][0] = 595; 
     graph->city[49][1] = 360;
     graph->city[50][0] = 1340; 
     graph->city[50][1] = 725;
     graph->city[51][0] = 1740; 
     graph->city[51][1] = 245;
     

     graph->bestpath = INT_MAX;

}

// Reinicializa alguns valores da estrutura
void resetgraph(AntGraph *graph){
	// Cidades visitadas, probabilidades, rota e tamanho das rotas são resetados (Valor = 0)
	
     memset(&graph->pathsize,0,sizeof graph->pathsize);
     memset(&graph->visitedcities,0,sizeof graph->visitedcities);
     memset(&graph->route,0,sizeof graph->route);
     memset(&graph->probabilities,0,sizeof graph->probabilities);
}

// Imprime a rota da melhor formiga e escreve no arquivo na formatação(organização) necessária para plotar no GNUPLOT
void printGraph(AntGraph *graph){
	FILE *path;
	path = fopen("path.txt","w");
	int write=0;
	int origin_aux=0;
	int origin=graph->firstcity[graph->bestant];
	int dest=0;
	for(int i =0;i<CITY;i++){
		for(int j=0;j<CITY;j++){
			if(graph->route[graph->bestant][origin][j]){
				printf("Cidade %d para Cidade %d\n",origin,j);
				origin = j;

				if(write == 0){
				  fprintf(path,"%d %d\n",graph->city[graph->firstcity[graph->bestant]][0]
						  ,graph->city[graph->firstcity[graph->bestant]][1]);
				  fprintf(path,"%d %d\n\n",graph->city[origin][0],graph->city[origin][1]);
				  origin_aux = origin;
				  write++;
				}
				else if (write == 1){
					fprintf(path,"%d %d\n",graph->city[origin_aux][0],graph->city[origin_aux][1]);
					fprintf(path,"%d %d\n\n",graph->city[origin][0],graph->city[origin][1]);
					origin_aux = origin;
				}

				break;
			}

		}
	}


	fclose(path);
	


}

void writePath(AntGraph *graph,FILE *file){



}



