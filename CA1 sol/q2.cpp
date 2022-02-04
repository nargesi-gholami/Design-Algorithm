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

	int min = 1e9;
	for (int j = 0 ; j < w - l ; j ++)
	{
		int sum = 0;
		for (int i = j ; i < j + l ; i++)
			sum += rock[i];
		
		if (sum < min)
			min = sum;		
	}

	int k = 0;
	for (int i = w - l; i < w ; i++)
		k += rock[i];

	int ans = (min < k) ? min : k;

	cout << min << endl;

	return 0;
}