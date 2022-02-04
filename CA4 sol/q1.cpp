#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int lg;

lg find_parent(lg u, vector<lg>& parent)
{
	if (parent[u] == -1)
		return u;
	return find_parent(parent[u], parent);
}

lg union_tree(lg u, lg v, vector<lg>& heights)
{
	lg fa;

	if (heights[u] > heights[v])
		fa = u;
	else if (heights[u] < heights[v])
		fa = v;
	else
	{
		fa = u;
		heights[u] ++;
	}
	return fa;
}

lg find_MST_tree(vector<vector<lg>> edges, lg n)
{
	vector<lg> heights(n);
	vector<lg> parent(n, -1);
	vector<lg> node_num(n, 1);

	sort(edges.begin(), edges.end(), [&edges](vector<lg> v1,vector<lg> v2) { return v1[0] > v2[0]; });

	lg u, v, w, ru , rv;
	lg ans = 0;
	lg edge_num = 0;

	for (lg i = 0 ; i < edges.size() ; i++)
	{
		w = edges[i][0];
		u = edges[i][1];
		v = edges[i][2];

		ru = find_parent(u, parent);
		rv = find_parent(v, parent);

		if (ru != rv)
		{
			lg father = union_tree(ru, rv, heights);
			lg child = (father == rv) ? ru : rv;

			ans += w*(node_num[father])*(node_num[child]);
			
			parent[child] = father;
			node_num[father] += node_num[child];
		}
		if (edge_num == n - 1)
			break;
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	lg n, m;
	cin >> n >> m;

	vector<lg> population(n);
	for (lg j = 0; j < n; j++)
		cin >> population[j];

	lg node1, node2;
	
	vector<vector<lg>> edges(m, vector<lg>(3));
	for (lg i = 0; i < m ; i++)
	{
		cin >> node1 >> node2;
		node1 --; node2 --;
		edges[i][0] = min(population[node1], population[node2]);
		edges[i][1] = node1;
		edges[i][2] = node2;
	}

	cout <<  find_MST_tree(edges, n) << endl;//mlogn

	system("pause");
	return 0;
}