#ifndef LIB_H_   /* Include guard */
#define LIB_H_
#include<stdio.h>

#define DIMENSION 2
#define CITY 	  52
#define ORIGIN	  52
#define DESTINY   52
#define ANT 	  52

typedef struct graph{
	int city[CITY][DIMENSION];
	double pheromone[CITY][CITY];
	int route[ANT][ORIGIN][DESTINY];
	double probabilities[ORIGIN][DESTINY];
	double pathsize[ANT];
	double bestpath;
	int bestant;
	int firstcity[ANT];
	int visitedcities[ANT][ORIGIN];
	int currentcity[ANT];
	
}AntGraph;
void loadtsp(AntGraph *graph);
void resetgraph(AntGraph *graph);
void printGraph(AntGraph *graph);
void writePath(AntGraph *graph,FILE *file);

#endif // LIB_H_
