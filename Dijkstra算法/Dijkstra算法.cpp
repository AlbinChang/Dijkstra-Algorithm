// Dijkstra算法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>
using namespace std;

const int infinity = std::numeric_limits<int>::max();

//从未被扩展的顶点中选择估计代价值最小的顶点作为下一个扩展顶点
//返回下一个扩展顶点
//如果返回值为-1，表示没有顶点可以继续扩展,一种情况是所有顶点扩展完成，另一种情况是其他顶点不可达。
int extract_min(int cost[], list<int>& wait_expand)
{
	int temp_min = infinity;
	int vertex_expand = -1;
	for (list<int>::iterator iterator = wait_expand.begin(); iterator != wait_expand.end(); iterator++)
	{		
		if (cost[*iterator] < temp_min)
		{
			temp_min = cost[*iterator];
			vertex_expand= *iterator;
		}
	}
	return vertex_expand;
}
void Dijkstra(int* MatrixWeight, const int N, int* cost, int* previous ,list<int>& tree, int source)
{
	//初始化每个顶点的估计代价值为无穷大，
	for (int i = 0; i < N; i++)
		cost[i] = infinity;
	cost[source] = 0; //顶点自己到自己的估计代价值为0

	//初始化每个顶点的前驱为-1，表示没有前驱
	for (int i = 0; i < N; i++)
		previous[i] = -1;

	//我们需要一个列表wait_expand保存未被扩展的顶点，当然被扩展的顶点都会依次被保存在tree列表中
	list<int> wait_expand;
	for (int i = 0; i < N; i++)//初始化未被扩展的顶点
		wait_expand.push_back(i);

	//确保tree列表为空
	tree.clear();

	//开始我们最短路径树的生成	
	int vertex_expand;
	while ( (vertex_expand = extract_min(cost, wait_expand)) != -1 )
	{
		//找到下一个扩展顶点后，添加到最短路径树，并从未扩展结点列表中删除
		tree.push_back(vertex_expand);
		wait_expand.remove(vertex_expand);

		//计算当前扩展顶点指向的顶点的估计代价值
		for (int j = 0; j < N;j++)
		{
			if (vertex_expand == j)
				continue;
			if (MatrixWeight[vertex_expand*N+j] != infinity)
			{
				//如果新的估计代价值小于之前的估计代价值，那么更新估计代价值及前驱
				if (cost[vertex_expand] + MatrixWeight[vertex_expand*N + j] < cost[j])
				{
					cost[j] = cost[vertex_expand] + MatrixWeight[vertex_expand*N + j];
					previous[j] = vertex_expand;
				}
					
			}
		}
	}	
}

void print_matrix(int* matrix_array, const int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrix_array[i*N + j] == infinity)
			{
				cout << "infinity" << " \t";
			}
			else
			{
				cout << matrix_array[i*N + j] << " \t";
			}
			
		}
			
		cout << endl;
	}
	
}
void print_array(int* array, const int N)
{
	for (int i = 0; i < N; i++)
	{
		if (array[i] == infinity)
		{
			cout << "infinity" << " \t";
		}
		else
		{
			cout << array[i] << " \t";
		}
	}
		
	cout << endl;
}

void print_path(int previous[], int destination)
{
	if (destination == -1)
		return;
	
	print_path(previous, previous[destination]);
	cout << destination << "->";
}
int _tmain(int argc, _TCHAR* argv[])
{
	//首先要有一个非负权值的有向图，包含两个集合，一个是顶点集合，一个是有向边集合（带有非负权值）
	//如果用一个N*N的矩阵数组M表示一个有N个结点非负权值的有向图，那么M（i*N+j）就表示结点i到结点j的有向边的非负权值
	//如果M（i*N+j）=infinity，表示没有这个有向边
	const int N =  5;					//顶点个数
	int MatrixWeight[N*N] = {
		0,2,infinity,3,6,
		6,0,infinity,9,6,
		7,3,0,infinity,4,
		10,infinity,26,0,3,
		6,25,infinity,3,0
	};
	
	//有了图，需要给出源顶点source
	int source = 2;
	//我们需要一个数组保存每个顶点的估计代价值
	int cost[N];
	//我们需要一个数组保存每个顶点的前驱，这样就能保存每个顶点的最短路径信息
	int previous[N];
	//我们需要一个列表保存最短路径树的扩展顺序
	list<int> tree;
	
	
	print_matrix(MatrixWeight, N);
	Dijkstra(MatrixWeight, N, cost,previous, tree, source);
	
	cout << "顶点扩展的顺序以及每个顶点的最短路径：" << endl;
	for (list<int>::iterator iterator = tree.begin(); iterator != tree.end(); iterator++)
	{
		cout << *iterator << ":\t" << "代价:"<<cost[*iterator]<<"\t";
		cout << "最短路径：";
		print_path(previous, previous[*iterator]);
		cout << *iterator << endl;;
	}
	
	
	system("pause");
	
	return 0;
}

