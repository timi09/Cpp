#include <iostream>
#include <cmath>
#include <set>

using namespace std;

int main()
{
    int n; 
	cin >> n;
	set<int> set;
	for (int i = 1; i <= n; i++)
	{
		set.insert(i); //1
	}
	std::set<int>::iterator it = set.begin();//2
	while(++it != set.end())//3
	{
		std::set<int>::iterator it2 = it;
		it2++;
		while(it2 != set.end())
		{
			if(*it2%*it==0)
			{
				it2 = set.erase(it2);//4
			}
			else
			{
				it2++;
			}
		}
	}
	
	copy(set.rbegin(), set.rend(), ostream_iterator<int>(cout, " "));//5 6
	
    return 0;
}