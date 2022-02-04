#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int w,l;
	cin >> w;
	cin >> l;

	vector<int> rock(w);
	

	for (int i = 0; i < w - 1; i++)
		cin >> rock[i];

	int min = 0;
	for (int j = 0; j < l; j++)
		min += rock[j];

	int sum = min;
	for (int j = l ; j < w - 1 ; j ++)
	{
		sum = sum - rock[j-l] + rock[j];
		if (sum < min)
			min = sum;		
	}

	cout << min << endl;

	return 0;
}