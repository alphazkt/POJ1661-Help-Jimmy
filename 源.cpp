#include <iostream>
#include<algorithm>
using namespace std;
#define MAX 1000
#define INFINITE 100000
struct Platform{
	int Lx, Rx, h;
	bool operator< (const Platform &p2)const{
		return h > p2.h;
	}
};
Platform platforms[MAX + 10];
int leftMin[MAX + 10];
int rightMin[MAX + 10];
int t;
int n, x, y, hMax;

int main()
{
	cin >> t;
	while (t--)
	{
		cin >> n >> x >> y >> hMax;
		platforms[0].Lx = x;
		platforms[0].Rx = x;
		platforms[0].h = y;
		for (int i = 1; i <= n; i++)
			cin >> platforms[i].Lx >> platforms[i].Rx >> platforms[i].h;

		sort(platforms, platforms + n - 1);

		for (int i = 1; i < n; i++)
			for (int j = i + 1; j <= n;j++)
				if (platforms[i].h < platforms[j].h)
				{
					Platform p = platforms[i];
					platforms[i] = platforms[j];
					platforms[j] = p;
				}

		for (int i = n; i >=0; i--)
		{
			int j;
			for (j = i + 1; j <= n; j++)
			{
				if (platforms[i].Lx <= platforms[j].Rx
					&& platforms[i].Lx >= platforms[j].Lx)
					break;
			}
			if (j > n)
			{
				if (platforms[i].h > hMax)
					leftMin[i] = INFINITE;
				else
					leftMin[i] = platforms[i].h;
			}
			else{
				int height = platforms[i].h - platforms[j].h;
				if (height > hMax)
					leftMin[i] = INFINITE;
				else
					leftMin[i] = height + min(
					leftMin[j] + platforms[i].Lx - platforms[j].Lx,
					rightMin[j] + platforms[j].Rx - platforms[i].Lx);
			}

			for (j = i + 1; j <= n; j++)
			{
				if (platforms[i].Rx <= platforms[j].Rx
					&& platforms[i].Rx >= platforms[j].Lx)
					break;
			}
			if (j > n)
			{
				if (platforms[i].h > hMax)
					rightMin[i] = INFINITE;
				else
					rightMin[i] = platforms[i].h;
			}
			else{
				int height = platforms[i].h - platforms[j].h;
				if (height > hMax)
					rightMin[i] = INFINITE;
				else
					rightMin[i] = height + min(
					leftMin[j] + platforms[i].Rx - platforms[j].Lx,
					rightMin[j] + platforms[j].Rx - platforms[i].Rx);
			}
		}

		cout << min(leftMin[0], rightMin[0]) << endl;
	}
	return 0;
}