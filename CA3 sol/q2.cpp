#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool flag = false;

void add_edge(vector<vector<long long int>>& graph, long long int u, long long int v)
{
	graph[v].push_back(u);
	graph[u].push_back(v);
}

/*int BFS(vector<vector<int>>& graph, int first, vector<bool>& eat, int& max_dis)
{
	vector<int> queue;

	vector<int> distances(graph.size(), -1);

	distances[first] = 0;
	queue.push_back(first);

	while (!queue.empty())
	{
		first = queue.front();
		queue.erase(queue.begin());
		for (int i = 0; i < graph[first].size(); i++)
		{
			if (!eat[graph[first][i]] && distances[graph[first][i]] == -1)
			{
				distances[graph[first][i]] = distances[first] + 1;
				queue.push_back(graph[first][i]);
			}
		}
	}

}*/

void DFS(vector<vector<long long int>>& graph, long long int first,  vector<bool>& visited, vector<long long int>& distance, int dis, long long int& max)
{
	visited[first] = true;
	distance[first] = dis;
	for (int i = 0; i < graph[first].size(); i++)
		if (!visited[graph[first][i]])
			DFS(graph, graph[first][i], visited, distance, dis + 1, max);
	
	if (dis > distance[max])
		max = first;
}

void DFS2(vector<vector<long long int>>& graph, long long int first, long long int last, vector<bool>& visited, vector<long long int>& path)
{
	if (!flag) 
		path.push_back(first);
	if (first == last)
	{
		flag = true;
		return;
	}
	
	visited[first] = true;
	for (int i = 0; i < graph[first].size(); i++)
		if (!visited[graph[first][i]])
			DFS2(graph, graph[first][i], last, visited, path);
	
	if(!flag)
		path.pop_back();
}

int main()
{
	long long int n;
	cin >> n;

	vector<vector<long long int>> tree(n);

	for (int j = 0; j < n - 1; j++)
	{
		long long int u, v;
		cin >> u >> v;
		add_edge(tree, u - 1, v - 1);
	}

	////// find path from 0th node
	vector<long long int> distance1(n);
	vector<bool> visited1(n);
	long long int farthest_v1 = 0;
	DFS(tree, 0, visited1, distance1, 0, farthest_v1);

	////// find path from farthest node
	vector<long long int> distance2(n);
	vector<bool> visited2(n);
	long long int farthest_v2 = 0;
	DFS(tree, farthest_v1, visited2, distance2, 0, farthest_v2);

	///// find path from farthest node2/ update distance1
	long long int dump = 0;
	vector<bool> visited3(n);
	DFS(tree, farthest_v2, visited3, distance1, 0, dump);

	/////find path between two node
	vector<long long int> longest_path;
	vector<bool> visited(n); 
	DFS2(tree, farthest_v1, farthest_v2, visited, longest_path);

	///// specify nodes in the longest path
	vector<bool> eat(n);
	for (int i = 0; i < longest_path.size(); i++)
		eat[longest_path[i]] = true;

	//// calculate answer
	long long int chocolate = 0;
	for (int i = 0; i < n; i++)
		chocolate += eat[i] ? 0 : (distance1[i] > distance2[i]) ? distance1[i] : distance2[i];
	long long int l = longest_path.size() - 1;
	chocolate +=  l*(l + 1) / 2;

	cout << chocolate << endl;

	system("pause");
	return 0;
}