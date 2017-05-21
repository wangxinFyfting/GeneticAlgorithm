//
//  GA.c
//  Genetic_Algorithm
//
//  Created by He11o_Liu on 2016/10/13.
//  Copyright © 2016年 He11o_Liu. All rights reserved.
//

#include "GA.h"

void printNChessman(Individual object){
    int i;
    for(i = 0 ; i < N;i++)
        printf("%d ",object[i]);
    printf("\n");
}

/**
 * 这个函数用于算N皇后的适应度
 * N利用宏定义 (c语言不好实现对数组指针获取其数组长度)
 * Param Individual 判断个体
 * return Fitness_FN 适应度
 * Author 刘年
 * 2016-10-14
 */
int Fitness_FN(Individual object){
    int row = 0,i = 0,collion = 0;
    for( i = 0; i<N ; i++ )
        for(row = i+1; row <N;row++)
            if((object[row] == object[i]+row -i)||
               (object[row] == object[i]-row +i)||
               (object[row] == object[i])) collion ++ ;
    return N*(N-1)/2 - collion;
}

/**
 * 这个函数用于从种群中随机根据适应度随机选取一个适合的个体
 * Param Population 种群
 * Param Fitness_FN 适应函数
 * return Individual 选择的个体
 * Author 刘年
 * 2016-10-14
 */
Individual Random_Selection(Population pop,int (*Fitness_FN)()){
    int i = 0 , sum = 0, selectNum = 0;
    int popFN[pop.length];
    for(i = 0; i<pop.length;i++){
        popFN[i] = Fitness_FN(pop.Population[i]);
        sum += popFN[i];
    }
    selectNum = rand()%sum;
    i = 0;
    while(selectNum > 0){
        selectNum -= popFN[i];
        if(selectNum < 0) break;
        i++;
    }
    return pop.Population[i];
}

/**
 * 交配函数，从父亲和母亲的基因中随机继承一段
 * Param Individual father 父亲
 * Param Individual mother 母亲
 * Param Individual 孩子
 * Author 刘年
 * 2016-10-14
 */
void Reproduce(Individual father,Individual mother,Individual* child){
    int randomLength = 0,i = 0;
    randomLength = rand()%N;
    for(i = 0; i < N; i ++)
        if(i < randomLength) (*child)[i] = mother[i];
        else (*child)[i] = father[i];
}

/**
 * 获取小概率可能性
 * return bool 小概率为true
 * Author 刘年
 * 2016-10-14
 */
bool SmallRandomProbability(){
//    srand((unsigned int)time(0));
    return rand()%1000<SmallProbablity?true:false;
}

/**
 * 变异函数 当小概率发生时 子代基因发生变异
 * Param Individual 发生变异的对象
 * Return Individual 变异后的个体
 * Author 刘年
 * 2016-10-14
 */
Individual Mutate(Individual object){
    int MutatePos,MutateData;
//    srand((unsigned int)time(0));
    MutatePos = rand()%N;
    MutateData = rand()%N+1;
    object[MutatePos] = MutateData;
    return object;
}

/**
 * 添加新的个体到种群中
 * Param Individual 需要添加的个体
 * Param Population 添加到的种群
 * Author 刘年
 * 2016-10-14
 */
void AddNewPopulation(Population* pop,Individual individual){
    int i = 0;
    for(i = 0; i < N;i++) pop->Population[pop->length][i] = individual[i];
    pop->length ++;
}

/**
 * 种群中已经有足够多的个体符合要求
 * Param Individual 需要添加的个体
 * Param Population 添加到的种群
 * Author 刘年
 * 2016-10-14
 */
bool FitEnough(Population pop,int (*Fitness_FN)()){
    int i = 0,fitcount = 0;
    int fit = N*(N-1)/2;
    bool ans = false;
    for(i = 0 ; i < pop.length;i++)
        if( Fitness_FN(pop.Population[i]) == fit) fitcount ++;
    if(fitcount > 0) ans = true;
    return ans;
}

/**
 * 返回种群中最佳个体
 * Param Population 种群
 * Param Fitness_FN 适应函数
 * Return Individual 最佳个体
 * Author 刘年
 * 2016-10-14
 */
Individual ChooseBestIndividual(Population pop,int (*Fitness_FN)()){
    int i = 0;
    int max = 0,maxi = 0;
    for(i = 0 ; i < pop.length;i++)
        if( Fitness_FN(pop.Population[i]) > max) maxi = i;
    return pop.Population[maxi];
}

/**
 * 遗传算法主方法
 * Param Population 种群
 * Param Fitness_FN 适应函数
 * Return Individual 最佳个体
 * Author 刘年
 * 2016-10-14
 */
Individual Genetic_Algorithm(Population pop,int (*Fitness_FN)()){
    Population new_population;
    Individual father,mother,child;
    int i = 0,Generation = 0;
    //init population
    srand((unsigned int)time(0));
    new_population.Population = malloc(pop.length*sizeof(int*));
    for(i = 0; i<pop.length;i++)
        new_population.Population[i] = malloc(N*sizeof(int));
    child = malloc(sizeof(N*sizeof(int)));
    
    while(!FitEnough(pop,Fitness_FN)&&Generation<500000){
        new_population.length = 0;
        for(i = 0; i < pop.length ; i++){
            father = Random_Selection(pop,Fitness_FN);
            mother = Random_Selection(pop,Fitness_FN);
            Reproduce(father,mother,&child);
            if(SmallRandomProbability())
                child = Mutate(child);
            AddNewPopulation(&new_population,child);
        }
        pop.Population = new_population.Population;
        Generation ++;
    }
    return ChooseBestIndividual(pop,Fitness_FN);
}
