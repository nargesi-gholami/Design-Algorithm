#include <iostream>
#include <vector>

using namespace std;

void print(vector <int> d)
{
	for (int i = 0; i < d.size(); i++)
		cout << d[i] << " ";
	cout << endl << "########" << endl;
}

int main()
{
	int n, k;

	int min_time = 0;

	cin >> n >> k;
	vector <int> d(n);
	vector <int> l(n);

	for (int i = 0; i < n; i++)
	{
		cin >> d[i];
		min_time += d[i];
	}

	for (int j = 0; j < n; j++)
		cin >> l[j];

	vector <int> next(n,-1);
	for (int i = 0; i < n; i++)
		for (int j = i+1 ; j < n; j++)
		{
			if (l[i] < l[j])
			{
				next[i] = j;
				break;
			}
		}

	vector<int> energy(n + 1, 0);
	for (int i = 1; i <= n ; i++)
		energy[i] = energy[i - 1] + l[i - 1] - d[i - 1];
		

	//print(distance);
	//print(fuel);
	//print(next);
	int capacity = 0;
	int i = 0;
	while(i != n)
	{
		int c = (next[i] != -1) ? next[i] : n;
		int need = capacity + energy[c] - energy[i];
		while (need < 0)
		{
			min_time += k;
			capacity += l[i];
			need += l[i];
		}
		capacity += energy[c] - energy[i];
		i = c;
	}

	cout << min_time << endl;
	system("pause");
	return 0;
}
