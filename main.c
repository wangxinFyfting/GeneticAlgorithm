//
//  main.c
//  GA
//
//  Created by He11o_Liu on 2016/10/13.
//  Copyright © 2016年 He11o_Liu. All rights reserved.
//

#include <stdio.h>
#include "GA.h"
#define SizeofPopulation 30

int main(int argc, const char * argv[]) {

    int StartIndividual[SizeofPopulation][N] ;
    int i = 0,j = 0;
    Individual ans;

    srand((unsigned int)time(0));

    for(i = 0; i<30;i++)
        for(j = 0; j<N;j++)
            StartIndividual[i][j] = rand()%N+1;
    Population startPopulation;

    startPopulation.length = SizeofPopulation;
    startPopulation.Population = malloc(startPopulation.length*sizeof(int));


    for(i = 0; i<startPopulation.length;i++){
        startPopulation.Population[i] = malloc(N*sizeof(int));
        startPopulation.Population[i] = StartIndividual[i];
        printNChessman(startPopulation.Population[i]);
    }


    ans = Genetic_Algorithm(startPopulation,*Fitness_FN);
    printf("result:");
    printNChessman(ans);
    printf("FN:%d\n",Fitness_FN(ans));
    return 0;
}
