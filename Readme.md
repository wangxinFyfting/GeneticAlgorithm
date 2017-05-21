# 遗传算法的简单C语言实现

遗传算法的一种简单的C语言实现

## 伪代码

```c
function Genetic_Algorithm(population,Fitness_FN) returns an individual
//输入为包含了一定数量个体的种群对象，以及针对个体评估其适应程度的方法
	 repeat
		 new_population <- empty set
		 //初始化下一代种群，该种群的大小与原来的种群大小保持一致（这个可以根据算力修改）
		 //下面的循环开始生成新种群中的个体
		 for i = 1 to sizeof(population) do
			 father <- Random_Selection(population,Fitness_FN)
			 mother <- Random_Selection(population,Fitness_FN)
			 //下一代的个体的父母通过评估函数计算其生存概率从种群中选择
			 child <- Reproduce(father , mother)
			 //下一代个体通过将其父母的基因根据随机分段位置分别取出拼凑而成
			 if(small random probability) child <- Mutate(child)
			 //下一代个体将有一定概率发生基因突变
			 add child to new_population
			 //将新的个体加入到新的种群中
		population <- new_population
		//结束本代种群组建，准备开始下一代种群的组建
	until some individual is fit enough or enough time has clasped
	//当种群中有些个体已经足够符合，或者计算时间达到限制，结束循环
	return the best individual in population according to Fitness_FN
	//返回本种群中最佳个体
```
## C语言实现

参考*人工智能 一种现代的方法* 实现了遗传算法求解八皇后的问题。

## 参考

*人工智能 一种现代的方法*