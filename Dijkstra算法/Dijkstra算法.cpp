// Dijkstra�㷨.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <list>
using namespace std;

const int infinity = std::numeric_limits<int>::max();

//��δ����չ�Ķ�����ѡ����ƴ���ֵ��С�Ķ�����Ϊ��һ����չ����
//������һ����չ����
//�������ֵΪ-1����ʾû�ж�����Լ�����չ,һ����������ж�����չ��ɣ���һ��������������㲻�ɴ
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
	//��ʼ��ÿ������Ĺ��ƴ���ֵΪ�����
	for (int i = 0; i < N; i++)
		cost[i] = infinity;
	cost[source] = 0; //�����Լ����Լ��Ĺ��ƴ���ֵΪ0

	//��ʼ��ÿ�������ǰ��Ϊ-1����ʾû��ǰ��
	for (int i = 0; i < N; i++)
		previous[i] = -1;

	//������Ҫһ���б�wait_expand����δ����չ�Ķ��㣬��Ȼ����չ�Ķ��㶼�����α�������tree�б���
	list<int> wait_expand;
	for (int i = 0; i < N; i++)//��ʼ��δ����չ�Ķ���
		wait_expand.push_back(i);

	//ȷ��tree�б�Ϊ��
	tree.clear();

	//��ʼ�������·����������	
	int vertex_expand;
	while ( (vertex_expand = extract_min(cost, wait_expand)) != -1 )
	{
		//�ҵ���һ����չ�������ӵ����·����������δ��չ����б���ɾ��
		tree.push_back(vertex_expand);
		wait_expand.remove(vertex_expand);

		//���㵱ǰ��չ����ָ��Ķ���Ĺ��ƴ���ֵ
		for (int j = 0; j < N;j++)
		{
			if (vertex_expand == j)
				continue;
			if (MatrixWeight[vertex_expand*N+j] != infinity)
			{
				//����µĹ��ƴ���ֵС��֮ǰ�Ĺ��ƴ���ֵ����ô���¹��ƴ���ֵ��ǰ��
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
	//����Ҫ��һ���Ǹ�Ȩֵ������ͼ�������������ϣ�һ���Ƕ��㼯�ϣ�һ��������߼��ϣ����зǸ�Ȩֵ��
	//�����һ��N*N�ľ�������M��ʾһ����N�����Ǹ�Ȩֵ������ͼ����ôM��i*N+j���ͱ�ʾ���i�����j������ߵķǸ�Ȩֵ
	//���M��i*N+j��=infinity����ʾû����������
	const int N =  5;					//�������
	int MatrixWeight[N*N] = {
		0,2,infinity,3,6,
		6,0,infinity,9,6,
		7,3,0,infinity,4,
		10,infinity,26,0,3,
		6,25,infinity,3,0
	};
	
	//����ͼ����Ҫ����Դ����source
	int source = 2;
	//������Ҫһ�����鱣��ÿ������Ĺ��ƴ���ֵ
	int cost[N];
	//������Ҫһ�����鱣��ÿ�������ǰ�����������ܱ���ÿ����������·����Ϣ
	int previous[N];
	//������Ҫһ���б������·��������չ˳��
	list<int> tree;
	
	
	print_matrix(MatrixWeight, N);
	Dijkstra(MatrixWeight, N, cost,previous, tree, source);
	
	cout << "������չ��˳���Լ�ÿ����������·����" << endl;
	for (list<int>::iterator iterator = tree.begin(); iterator != tree.end(); iterator++)
	{
		cout << *iterator << ":\t" << "����:"<<cost[*iterator]<<"\t";
		cout << "���·����";
		print_path(previous, previous[*iterator]);
		cout << *iterator << endl;;
	}
	
	
	system("pause");
	
	return 0;
}

