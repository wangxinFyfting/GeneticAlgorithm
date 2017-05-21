//
//  GA.h
//  Genetic_Algorithm
//
//  Created by He11o_Liu on 2016/10/13.
//  Copyright © 2016年 He11o_Liu. All rights reserved.
//

#ifndef GA_h
#define GA_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8
#define SmallProbablity 10 //10/1000

typedef int* Individual;
typedef struct {
    int length;
    int **Population;
} Population;

typedef int bool;
#define true 1
#define false 0
int Fitness_FN();
Individual Genetic_Algorithm(Population pop,int (*Fitness_FN)());
Individual Random_Selection(Population pop,int (*Fitness_FN)());
void Reproduce(Individual father,Individual mother,Individual *child);
Individual Mutate(Individual child);
Individual ChooseBestIndividual(Population pop,int (*Fitness_FN)());
void AddNewPopulation(Population* pop,Individual individual);
bool FitEnough(Population pop,int (*Fitness_FN)());
bool SmallRandomProbability();
void printNChessman(Individual object);

#endif /* GA_h */
