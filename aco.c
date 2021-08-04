#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include"lib.h"
#include"mtwister.h"			// Biblioteca

#define max_it		5000		// Máximo de iterações
#define ALPHA		2.0 		// Valor Alpha
#define BETA		4.0			// Valor Beta
#define RHO 		0.5			// Valor RHO
#define Q 		100.0			// Valor Q
#define B		5.0				// Valor B
#define TAU 		pow(10,-6); // Macro para calcular o valor TAU
#define ELITIST_ANT	5			// Quantidade de formigas elitistas

// Protótipo das funções
void ACO(AntGraph *graph);
double distance(AntGraph *graph,int origin,int destiny);
void updateroute(AntGraph *graph);
void evaluatepath(AntGraph *graph);
void buildpath(AntGraph *graph,int currentant);
int buildprobabilities(AntGraph *graph,int currentant,int currentcity);
void init_pheromone(AntGraph *graph);
void init_visit(AntGraph *graph);
double sumdenominator(AntGraph *graph,int currentant,int currentcity);
void selectcity(AntGraph *graph,int currentant,int currentcity,int countvisited);
double sumpheromone(AntGraph *graph,int origin,int dest);
AntGraph graph;
MTRand r;
int t;
FILE *fp;
int main(void){
	loadtsp(&graph);
	srand(time(NULL));
	r = seedRand(rand());   
	//printf("%d e %d\n",graph.city[8][0],graph.city[8][1]);	
	//printf("%d e %d\n",graph.city[5][0],graph.city[5][1]);
	ACO(&graph);
	//printf("%lf\n",distance(&graph,8,5));
}

// Programa principal
void ACO(AntGraph *graph){
	fp = fopen("bestpath.txt","w");
	int i=0;
	init_pheromone(graph);					// Inicializa os feromônios
	while(t < max_it){
		init_visit(graph);					// Coloca cada formiga em uma cidade específica
		for(i=0;i<ANT;i++)					 // Para cada formiga
			buildpath(graph,i);     			 // Construa o caminho
		evaluatepath(graph);					 // Avalia o caminho
		updateroute(graph);					 // Atualiza o caminho
		t++;								// Incrementa t
	}
	fclose(fp);

}
// Cada formiga é colocada em uma cidade específica
void init_visit(AntGraph *graph){
	int random;
	for(int i=0;i<CITY;i++){
		random = i;
		graph->firstcity[i] = random;
		graph->currentcity[i] = random;
		graph->visitedcities[i][random] = 1;
	}
}

// Constrói as probabilidades
int buildprobabilities(AntGraph *graph,int currentant,int currentcity){

	double sum = sumdenominator(graph,currentant,currentcity);
	double notfinished=0;
	for(int dest=0;dest<CITY;dest++){
	// Se a cidade é atual ou se a cidade já foi visitada, a probabilidade dela ser visitada é zero
		if( currentcity==dest || graph->visitedcities[currentant][dest] == 1)
			graph->probabilities[currentcity][dest] = (double) 0;
		else{
		// Calcula a probabilidade da formiga ir da cidade origem para cidade destino
			double numerator = pow(graph->pheromone[currentcity][dest],ALPHA)*pow(1/distance(graph,currentcity,dest),BETA);
			graph->probabilities[currentcity][dest] = numerator/sum;
			// Flag mostrando que não é necessário voltar a cidade origem -- primeira e última cidade a ser visitada
			notfinished=1;					
		}
	}
	return notfinished;

}
// Retorna a soma necessária para realizar o cálculo das probabilidades
double sumdenominator(AntGraph *graph,int currentant,int currentcity){
	double result=0;
		for(int j=0;j<CITY;j++){
			if(graph->visitedcities[currentant][j] == 0 && (currentcity!=j)){
	 		  result +=  pow(graph->pheromone[currentcity][j],ALPHA)*pow(1/distance(graph,currentcity,j),BETA);
		}
	}
}
// Constroi a rota
void buildpath(AntGraph *graph,int currentant){
	// Para cada cidade
	for(int i=0;i<CITY;i++){
			// Constroi as probabilidades da formiga ir da cidade atual para qualquer cidade não visitada
	    	if(buildprobabilities(graph,currentant,graph->currentcity[currentant]))
	    		// Seleciona a cidade a ser visitada	        
		    	selectcity(graph,currentant,graph->currentcity[currentant],i);
			else{
				// A função buildprobabilities retornou zero, significando que é necessário voltar a origem
				graph->route[currentant][graph->currentcity[currentant]][graph->firstcity[currentant]] = 1;
			}

	}		
}
// Seleciona a cidade a ser visitada
void selectcity(AntGraph *graph,int currentant,int currentcity,int countvisited){
	//double random = (double)rand()/(double)RAND_MAX;
	double random = genRand(&r);
	double sum=0;
	int selectedcity;
	int dest;
	// Verifica a probabilidade de cada cidade e seleciona a cidade a ser visitada
		for(dest=0;dest<CITY;dest++){
			sum += graph->probabilities[currentcity][dest];
			if(sum != 0){					// Evita a comparação (double) = 0, PROBLEMA NA IMPLEMENTAÇÃO EM C !!!
				if(random <= sum){
					selectedcity = dest;
			    	dest = CITY;
			    }
			}
		}

		//fprintf(stderr,"Selecionada %d",selectedcity);
		graph->visitedcities[currentant][selectedcity] = 1; 		// Sinaliza que a cidade já foi visitada
		graph->currentcity[currentant] = selectedcity;				// Sinaliza que a cidade atual da formiga é a cidade que foi selecionada
		graph->route[currentant][currentcity][selectedcity] = 1;	// Constrói a rota
}

// Calcula cada distância necessária para percorrer a rota das formigas
void evaluatepath(AntGraph *graph){
	for(int i=0;i<ANT;i++){
		for(int origin=0;origin<CITY;origin++){
			for(int dest=0;dest<CITY;dest++){

				
				if(graph->route[i][origin][dest] == 1){
					graph->pathsize[i] += distance(graph,origin,dest);	
				}
				
				
			}
		}
		// Verifica se a rota calculada é melhor que melhor rota
		if(graph->pathsize[i] < graph->bestpath){
			graph->bestpath = graph->pathsize[i];						// Salva a distância a percorrer do caminho
			graph->bestant  = i; 										// Memoriza qual formiga realizou a rota
		}
		
	}
	printf("Melhor caminho %lf\n",graph->bestpath);
	fprintf(fp,"%d %lf\n",t,graph->bestpath);

}

// Atualiza o feromônio que interliga todas as cidades a partir da origem
void updateroute(AntGraph *graph){

	for(int origin=0;origin<CITY;origin++){
		for(int dest=0;dest<CITY;dest++){
			graph->pheromone[origin][dest] = (1 - RHO)*graph->pheromone[origin][dest] + sumpheromone(graph,origin,dest);
		}
	}
	// Se for a última iteração, imprime a melhor rota
	if(t+1 == max_it)
		printGraph(graph);			// Ver função implementada em "lib.c"
	
	// Reinicializa alguns valores (Ver função implementada em "lib.c")
	resetgraph(graph);

}

// Calcula o total de feromônios presente entre a origem e o destino
double sumpheromone(AntGraph *graph,int origin,int dest){
	double pheromone=0;
	for(int i=0;i<ANT;i++){
		if(graph->route[i][origin][dest] == 1)
			pheromone += Q/graph->pathsize[i];
	
		if(i == graph->bestant)
			pheromone += (ELITIST_ANT)*Q/graph->bestpath;	
	}
	
	return pheromone;

}

// Inicializa os feromônios das rotas
void init_pheromone(AntGraph *graph){
	int i=0;
	for(i=0;i<1;i++){
		for(int j=0;j<CITY;j++)
			graph->pheromone[i][j]= TAU;
	}
	for(i=1;i<ANT;i++)
		memcpy(graph->pheromone[i],graph->pheromone[0],sizeof graph->pheromone[0]);

	//printf("%lf\n",graph->pheromone[1][0]);
}

// Calcula distância entre duas cidades
double distance(AntGraph *graph,int origin,int destiny){
	double a = pow(graph->city[origin][0] - graph->city[destiny][0],2);
	double b = pow(graph->city[origin][1]- graph->city[destiny][1],2);
	return pow(a+b,0.5);

}

