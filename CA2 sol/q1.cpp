#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#define INT_MAX 1e9

vector<int> find_div(int n)
{
	vector<int> a;
	for (int i = 1; i <= sqrt(n); i++)
		if (n%i == 0)
		{
			if (n / i == i)
				a.push_back(i);

			else
			{
				a.push_back(n / i);
				a.push_back(i);
			}
		}

	return a;
}

int main()
{
	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<int>> ant(n);
	vector<vector<int>> sum(n+1);

	for (int i = 0; i < n; i++)
		for (int j = 0; j <= m ; j++)
		{
			if (j != m)
			{
				ant[i].push_back(0);
				cin >> ant[i][j];
			}
			sum[i].push_back(0);
		}

	for (int j = 0; j <= m; j++)
		sum[sum.size() - 1].push_back(0);

	for (int i = 1 ; i <= n ; i++)
		for (int j = 1; j <= m; j++)
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j] + ant[i-1][j-1] - sum[i - 1][j - 1];
		

	int ans = INT_MAX;
	for(int t = k ; t <= m*n ; t++)
	{
		vector<int> div = find_div(t);
		for (int d = 0 ; d < div.size() ; d++)
			for (int i = t / div[d] ; i <= n  ; i++)//up and down
				for (int j = div[d] ; j <= m  ; j++)//left and right
				{
					int new_ans = sum[i][j] - sum[i - (t / div[d])][j] - sum[i][j - div[d]] + sum[i-(t / div[d])][j- div[d]];
					ans = (ans < new_ans) ? ans : new_ans;
					//cout << div[d] << " " << t / div[d] <<" " << i << j << ans << endl;
				}
	}

	
	cout << ans << endl;
	system("pause");
	return 0;
}