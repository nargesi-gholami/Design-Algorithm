#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long int lg;

int n;
#define MAX 1
#define MIN 0
#define CAPACITY 1

/*int find_min_max(vector<lg> cell , bool m)
{
	int min = INT_MAX;
	int max = 0;
	
	for (int j = 0; j < cell.size(); j++)
		if (min > cell[j] && !m)
			min = cell[j];
		else if (max < cell[j] && m)
			max = cell[j];

	if (!m)
		return min;
	else
		return max;
}*/

int send_flow(int source, int sink, int min, vector<bool>& visited, vector<vector<int>>& flow, vector<vector<int>>& table)
{
	visited[source] = true;
	if (source == sink) 
		return min;
	for (int i = 1 ; i < 2*n+2; i++)
	{
		int c = table[source][i] - flow[source][i];
		if(c > 0 &&  !visited[i])
		{
			int f = (min < c) ? min : c;
			int sent_flow = send_flow(i, sink, f, visited, flow, table);
			flow[source][i] += sent_flow ? sent_flow : 0;
			flow[i][source] -= sent_flow ? sent_flow : 0;
			if (sent_flow)
				return sent_flow;
		}
	}
	return 0;
}

int find_flow(vector<vector<int>>& graph)
{
	int total_flow = 0;
	vector<bool> visited(2*n + 2);
	vector<vector<int>> flow(2 * n + 2, vector<int>(2 * n + 2));
	while (true)
	{
		int sent = send_flow(0, 2*n + 1, 1, visited, flow, graph);
		if (!sent)
			break;
		total_flow += sent;
		fill(visited.begin() , visited.end(), 0);
	}
	return total_flow;
}

void make_table(vector<vector<lg>>& box, vector<vector<int>>& graph, lg mid)
{
	for (int i = 1 ; i <= n; i++)
		for (int j = 1 ; j <= n; j++)
			if (box[i-1][j-1] <= mid)
				graph[2 * i - 1][2 * j] = 1;
	for (int i = 1 ; i <= n ; i++)
	{
		graph[0][2 * i - 1] = 1;
		graph[2 * i][2 * n + 1] = 1;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n;
	vector<lg> cell;
	vector<vector<lg>> box(n, vector<lg>(n));
	for (int i = 0 ; i < n ; i++)
		for (int j = 0 ; j < n ; j++)
		{
			lg temp;
			cin >> box[i][j];
			cell.push_back(box[i][j]);
		}
	int min = 0;
	int max = pow(n, 2)-1;
	int mid_index;
	sort(cell.begin(), cell.end());
	vector<bool> check(max);
	while (true)
	{
		mid_index = (min + max) / 2;
		if (check[mid_index])
			break;
		check[mid_index] = true;
		vector<vector<int>> graph(2 * n + 2, vector<int>(2 * n + 2));
		make_table(box, graph, cell[mid_index]);
		int flow =  find_flow(graph);
		max = (flow == n) ? mid_index : max;
		min = (flow != n) ? mid_index : min;
	}
	cout << cell[mid_index + 1] << endl;
	system("pause");
	return 0;
}