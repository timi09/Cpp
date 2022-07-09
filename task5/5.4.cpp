#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Worker
{
private:

	string Name;
	int ReportCard;
	float PricePerHour;
	int WorkedHours;

	//property getters
public:
	string getName()
	{
		return this->Name;
	}
	int getReportCard()
	{
		return this->ReportCard;
	}
	float getPricePerHour()
	{
		return this->PricePerHour;
	}
	int getWorkedHours()
	{
		return this->WorkedHours;
	}

	//property setters
public:
	void setName(string Name)
	{
		this->Name = Name;
	}
	void setReportCard(int ReportCard)
	{
		this->ReportCard = ReportCard;

	}
	void setPricePerHour(float PricePerHour)
	{
		this->PricePerHour = PricePerHour;
	}
	void setWorkedHours(int WorkedHours)
	{
		this->WorkedHours = WorkedHours;
	}

public:
	Worker(string Name, int ReportCard, float PricePerHour = 100, int
		WorkedHours = 10)
	{
		setName(Name);
		setReportCard(ReportCard);
		setPricePerHour(PricePerHour);
		setWorkedHours(WorkedHours);
	}

	void Print()
	{
		cout << this->Name << " ";
		cout << this->ReportCard << " ";
		cout << to_string(this->PricePerHour) << " ";
		cout << to_string(this->WorkedHours) << endl;
	}

	Worker operator = (int I)
	{
		this->ReportCard = I;
		return *this;
	}
};

int main()
{
	vector<Worker> workers = {
		Worker("A", -100, 130, -15),
		Worker("B", 120, 140, 10),
		Worker("C", -100, -10, 30),
		Worker("D", -10, 14, 170),
		Worker("E", 320, -20, -5),
		Worker("F", 4, 23, 60),
		Worker("G", -3, 12, 73),
		Worker("H", -333, 6, 8)
	};

	replace_if(workers.begin(), workers.begin()+workers.size()/2, [&](Worker x) {return x.getReportCard() < 0; }, -1);
	replace_if(workers.begin() + workers.size() / 2, workers.end(), [&](Worker& x) {return x.getReportCard() > 0;  }, 1);

	for (auto x : workers) {
		x.Print();
	}

    return 0;
}