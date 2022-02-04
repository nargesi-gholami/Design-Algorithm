#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long int lg;
#define INT_MAX 1000
int n;

void print(vector<vector<lg>>& friends)//debug
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cout << friends[i][j];
}

int find(int source, int dst, int min, vector<vector<lg>>& friends,  vector<bool>& visited, vector<vector<int>>& flow)
{
	visited[source] = 1;
	if (source == dst) 
		return min;
	for (int i = 1 ; i < visited.size() ; i++)
	{
		int c = friends[source][i] - flow[source][i];
		if (!visited[i] && c > 0)
		{
			int f = (min < c) ? min : c;
			int sent_flow = find(i, dst, f, friends, visited, flow);
			if (sent_flow)
				flow[source][i] += (friends[source][i]) ? sent_flow : 0;
			if(sent_flow)
				return sent_flow;
		}
	}
	return 0;
}

int find_flow(vector<vector<lg>> friends)
{
	int flow = 0;
	vector<bool> visited(n + 2);
	vector<vector<int>> Flow(n + 2, vector<int>(n + 2));
	for(int f = find(0, n + 1, INT_MAX, friends, visited, Flow) ; f ; f = find(0, n + 1, INT_MAX, friends, visited, Flow))
	{
		flow = flow + f;
		fill(visited.begin(), visited.end(), 0);
	}
	return flow;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int m;
	cin >> n >> m;

	vector<int> vote(n);
	vector<vector<lg>> friends(n+2, vector<lg>(n+2));
	for (int i = 0; i < n; i++)
		cin >> vote[i];

	for (int j = 0; j < m; j++)
	{
		int u, v;
		cin >> u >> v;
		if (vote[u - 1] != vote[v - 1] && !vote[u-1])
		{
			friends[u][v] = 1;
			friends[0][u] = 1;
			friends[v][n + 1] = 1;
		}
		else if (vote[u - 1] != vote[v - 1] && !vote[v-1])
		{
			friends[v][u] = 1;
			friends[0][v] = 1;
			friends[u][n + 1] = 1;
		}
		else if (vote[u - 1] == vote[v - 1] && !vote[u - 1])
		{
			friends[u][v] = 1;
			friends[v][u] = 1;
			friends[0][v] = 1;
			friends[0][u] = 1;
		}
		else if (vote[u - 1] == vote[v - 1] && vote[u - 1])
		{
			friends[u][v] = 1;
			friends[v][u] = 1;
			friends[u][n+1] = 1;
			friends[v][n+1] = 1;
		}
	}
	cout << find_flow(friends) << endl;
	system("pause");
	return 0;
}