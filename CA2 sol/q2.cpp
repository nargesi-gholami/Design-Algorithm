#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

#define INT_MAX 1e9

#define NEIGHBOR 0
#define TELEPORT_RIGHT 1
#define TELEPORT_LEFT 2

string s;
string t;


void print(vector<vector<int>> dp)
{
	cout << "__________" << endl;

	for (int i = 0; i < s.size(); i++)
	{
		for (int j = 0; j < t.size(); j++)
			cout << dp[i][j] << " ";
		cout << '\n';
	}
}

bool check_dp(int pre_s, int i_s, int type)
{
		if (type == NEIGHBOR)
		{
			if (pre_s + 1 == i_s || pre_s - 1 == i_s)
				return true;
		}
		else if (type == TELEPORT_RIGHT)
		{
			if (i_s + 1 <= s.size() && s[i_s + 1] == s[pre_s])
				return true;
		}
		else if (type == TELEPORT_LEFT)
		{
			if (i_s - 1 >= 0 && s[i_s - 1] == s[pre_s])
				return true;
		}

	return false;
}

void change_dp(vector<vector<int>>& dp, int& check,int pre_s, int i_s, int t_index, int c)
{
	check = 1;
	if (c == 1)
		c = (pre_s < i_s) ? 2 : 0;
	else if(c == -1)
		c = (pre_s < i_s) ? 0 : 2;

	if (dp[i_s][t_index] != -1)
	{
		if (dp[i_s][t_index] > (dp[pre_s][t_index - 1] + abs(pre_s - i_s ) + c))
			dp[i_s][t_index] = dp[pre_s][t_index - 1] + abs(pre_s - i_s) + c ;
	}
	else
		dp[i_s][t_index] = dp[pre_s][t_index - 1] + abs(pre_s - i_s ) + c ;
}

void min_time(vector<vector<int>> dp)
{
	int check = 0;
	for (int t_index = 1 ; t_index < t.size() ; t_index++)
	{
		check = 0;
		for (int pre_s = 0 ; pre_s < s.size() ; pre_s++)
			if (dp[pre_s][t_index - 1] != -1)
				for (int i_s = 0 ; i_s < s.size() ; i_s++)
					if (s[i_s] == t[t_index] && i_s != pre_s)
					{
						if (check_dp(pre_s, i_s, NEIGHBOR))
							change_dp(dp, check, pre_s, i_s , t_index,0);

						if(check_dp(pre_s, i_s, TELEPORT_RIGHT))
							change_dp(dp, check, pre_s , i_s , t_index , 1);

						if (check_dp(pre_s, i_s, TELEPORT_LEFT))
							change_dp(dp, check, pre_s, i_s , t_index , -1);
					}
		//print(dp);
	}

	int min = INT_MAX;
	if (check)
	{
		for (int i = 0; i < s.size(); i++)
			if(dp[i][t.size() - 1] != -1)
				if (dp[i][t.size() - 1] < min)
					min = dp[i][t.size() - 1];
		cout << min << endl;
	}
	else
		cout << -1 << endl;

	return;
}

int pre_check()
{
	if (s.size() == 1)
	{
		if (t.size() == 1)
			return t[0] == s[0];
		else
			return false;
	}
	
	if (t.size() == 1)
		for (int i = 0; i < s.size() ; i++)
			if (s[i] == t[0])
				return true;
	return 0;
}

int main()
{
	int s_size;
	int t_size;
	cin >> s_size >> t_size;
	cin >> s;
	cin >> t;

	if (pre_check())
	{
		cout << 0 << endl;
		system("pause");
		return 0;
	}

	vector<vector<int>> dp;
	for (int i = 0; i < s_size; i++)
	{
		vector<int> temp;
		dp.push_back(temp);
		for (int j = 0; j < t_size; j++)
		{
			dp[i].push_back(-1);
			if (j == 0 && s[i] == t[j])
				dp[i][j] = 0;
		}
	}

	min_time(dp);

	system("pause");
	return 0;
}