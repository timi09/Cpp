#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
    int n, elem, absMin(0); 
	cin >> n;
	vector<int> vector;
	for (int i = 0; i < n; i++)
	{
		cin >> elem;
		vector.push_back(elem); //1

		if(i == 0 || abs(elem) < absMin )
		{
			absMin = elem;
		}
	}


	bool LeftMin, RightMin, WriteMessage(true);
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) //2
	{
		LeftMin = false;
		RightMin = false;

		if(it == vector.begin())
		{
			LeftMin = true;
		}
		else if(*(it - 1) < *it)
		{
			LeftMin = true;
		}
		

		if (it == vector.end() - 1)
		{
			RightMin = true;
		}
		else if (*(it + 1) < *it)
		{
			RightMin = true;
		}

		if (LeftMin && RightMin)
		{
			WriteMessage = false;
			it = vector.insert(it, absMin); //3
			it++;
		}
	}

	if (WriteMessage)
	{
		cout << "Hasn't local maximums";
	}
	else
	{
		for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it)
		{
			cout << *it << " ";
		}
	}
	

    return 0;
}