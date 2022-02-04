#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define INF 1e9



void warshal(vector<vector<int>>& distance)
{
	int n = distance.size();
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i != j)
					distance[i][j] = distance[i][j] < (distance[i][k] + distance[k][j]) ?
					distance[i][j] : distance[i][k] + distance[k][j];//update dis
}

vector<vector<int>> cal_potential(vector<vector<int>>& distance, vector<vector<int>> L, vector<vector<int>> potential)
{
	int q;
	cin >> q;
	int n = distance.size();
	for (int j = 0; j < q; j++)
	{
		int u, v, l;
		cin >> u >> v >> l;
		u--; v--;
		L[u][v] = L[v][u] = l;
		for (int i = 0; i < n; i++)
		{
			potential[i][u] = max(potential[i][u], (l - distance[i][v]));//potential[i][u] > (l - distance[i][v]) ? potential[i][u] : l - distance[i][v];
			potential[i][v] = max(potential[i][v], (l - distance[i][u]));//max(potential[i][u] ,(l - distance[i][v])) ? potential[i][v] : l - distance[i][u];
		}
	}
	return potential;
}


void print(vector<vector<int>> dis)
{
	for (int i = 0; i < dis.size() ; i++)
	{
		for (int j = 0; j < dis.size() ; j++)
			cout << dis[i][j] << " ";
		cout << endl;
	}
	cout << "#####" << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int n;
	int m;
	cin >> n >> m;
	vector<vector<int>> distance(n, vector<int>(n, INF));
	vector<vector<int>> edges;
	vector<vector<int>> weight(n, vector<int>(n));
	vector<vector<int>> L(n, vector<int>(n));
	vector<vector<int>> potential(n, vector<int>(n, -INF));
	

	for (int i = 0 ; i < m ; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		x--; y--;
		distance[x][y] = w;
		distance[y][x] = distance[x][y];
		weight[x][y] = w;
		weight[y][x] = w;

		vector<int> temp;
		temp.push_back(x);
		temp.push_back(y);
		edges.push_back(temp);
	}

	for (int j = 0; j < n; j++)
		distance[j][j] = 0;
	warshal(distance);
	potential = cal_potential(distance, L, potential);
	//print(distance);
	//print(potential);
	int cute_num = 0;
	for (auto &edge : edges)
	{
		int a = edge[0];
		int b = edge[1];
		int w = weight[a][b];
		for (int i = 0 ; i < n ; i++)
		{
			if (potential[a][i] >= distance[b][i] + w)
			{
				cute_num++;
				break;
			}
		}
	}

	cout << cute_num << endl;
	system("pause");
}