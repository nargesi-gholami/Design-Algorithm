#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
int m = 0;

int find_max(vector<vector<int>>& dp, vector<int> M, vector<int> V,int k, int num, int diff)
{
	if (num == -1)
	{
		if (!diff)
			return 0;
		else
			return -1e9;
	}

	if (dp[num][diff+m/2] != 0)
		return dp[num][diff+m/2];

	int ans1 = find_max(dp, M, V, k, num - 1, diff);
	int ans2 = M[num] + find_max(dp, M, V, k, num - 1, diff + M[num] - V[num]*k);

	dp[num][diff+m/2] = (ans1 > ans2) ? ans1 : ans2;

	return dp[num][diff+m/2];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	int k;
	cin >> n >> k;

	vector<int> M(n);
	vector<int> V(n);


	
	for (int s = 0; s < n; s++)
	{
		cin >> M[s] >> V[s];
		m += M[s];
	}

	vector<vector<int>> dp(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			dp[i].push_back(0);
	
	cout << find_max(dp,M,V,k,n-1,0) << endl;

	system("pause");
	return 0;
}