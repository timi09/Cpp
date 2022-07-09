#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>

using namespace std;

int main()
{
	set<string> v1 = { "BBB","BCB","BZA", "ABA", "AAD", "DAD", "CCC", "CAA"};
	vector<string> v2 = { "CACD", "BBA","BAA", "AFAB", "DD", "ZZB", "ADBZ", "DZ"};

	multimap<char, string> m;
	for (int i = v2.size()-1; i >= 0; i--)
	{
		m.insert(pair<char, string>(v2[i][v2[i].size()-1], v2[i]));//1
	}
	
	vector<vector<string>> v;

	for (auto it = v1.begin(); it != v1.end(); it++)
	{
		char c = (*it)[0];

		auto r = m.equal_range(c);//2
		for (auto it2 = r.first; it2 != r.second; it2++)
		{
			v.push_back(vector<string>({ *it, it2->second }));
		}
	}

	m.clear();//3
	
	for (size_t i = 0; i < v.size(); i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	
    return 0;
}