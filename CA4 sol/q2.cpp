#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long int lg;
#define INF 1e9


/*void add_edge(vector<vector<lg>>& graph, lg u, lg v)
{
	graph[u].push_back(v);
}

void DFS(vector<vector<long long int>>& graph, long long int first, vector<bool>& visited)
{
	visited[first] = true;
	for (int i = 0; i < graph[first].size(); i++)
	{
		if (!visited[graph[first][i]])
			DFS(graph, graph[first][i], visited);
		else
			visited[first] = false;
	}

}*/

bool is_valid(lg u, lg v,lg weight, vector<lg>& distance, vector<lg>& distance2)
{
	return ((distance[v] > (distance[u] + weight) * 2) && ((distance[v] != -INF && distance2[v] != -INF) || (distance[u] != -INF && distance2[u] != -INF)));
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	lg n, m;
	cin >> n >> m;
	vector<vector<lg>> edges;
	vector<vector<lg>> edges_reverse;
	vector<vector<lg>> graph(n);


	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--; v--;
		vector<lg> temp(3, 1);
		temp[0] = u;
		temp[1] = v;
		edges.push_back(temp);
	
		vector<lg> temp2(3, 1);
		temp2[0] = v;
		temp2[1] = u;
		edges_reverse.push_back(temp2);
	}

	bool flag = true;
	vector<lg> d(n, -INF);
	vector<lg> d2(n, -INF);

	d[0] = 0;
	d2[n - 1] = 0;
	for (lg i = 1 ; i <= n -1 ; i++)
	{
		for (lg j = 0 ; j < m ; j++)
		{
			lg u = edges[j][0];
			lg v = edges[j][1];
			if(d[u] != -INF && d[u] + 1 > d[v])
				d[v] = d[u] + 1;
			/////////////////////////
			lg x = edges_reverse[j][0];
			lg y = edges_reverse[j][1];
			if (d2[x] != -INF && d2[x] + 1 > d2[y])
				d2[y] = d2[x] + 1;
		}
	}

	d[0] = 0;
	for (lg i = 1 ; i <= n - 1 ; i++)
	{
		for (lg j = 0 ; j < m ; j++)
		{
			lg u = edges[j][0];
			lg v = edges[j][1];
			lg weight = edges[j][2];
			if (d[u] + weight < d[v])
			{
				if(is_valid(u, v, weight, d, d2))
					flag = false;
				edges[j][2] = 2;
				d[u] = d[v] - edges[j][2];
			}			
		}
	}

	if (flag)
	{
		cout << "Yes" << endl;
		for (lg j = 0; j < m; j++)
			cout << edges[j][2] << endl;
	}
	else
		cout << "No" << endl;

	system("pause");
	return 0;
}