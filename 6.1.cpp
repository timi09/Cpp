#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

class exeption
{
	public:
	string message;
	exeption(string Message)
	{
		this->message = Message;
	}
};

class incorrect_id: public exeption
{
	public:
	incorrect_id(string Message): exeption(Message){}
};

class Sensor
{
	friend class RelationsManager;
	int Id;
	string Name;

	public:
	Sensor(int Id, string Name) 
	{
		if (!(Id>=100 && Id<=999))
		{
			throw incorrect_id("sensor ID must be a three-digit number");
		}
		this->Id = Id;
		this->Name = Name;
	}
};

class System
{
	friend class RelationsManager;
	int Id;
	string Name;

	public:
	System(int Id, string Name)
	{
		if (!(Id >= 10 && Id <= 99))
		{
			throw incorrect_id("system ID must be a two-digit number");
		}
		this->Id = Id;
		this->Name = Name;
	}

};

class list_contains_sensor : public exeption
{
	public:
	list_contains_sensor(string Message) : exeption(Message){}
};

class list_contains_system : public exeption
{
	public:
	list_contains_system(string Message) : exeption(Message){}
};

class list_not_contains_sensor : public exeption
{
	public:
	list_not_contains_sensor(string Message) : exeption(Message) {}
};

class list_not_contains_system : public exeption
{
	public:
	list_not_contains_system(string Message) : exeption(Message) {}
};

class sensor_already_included : public exeption
{
	public:
		sensor_already_included(string Message) : exeption(Message) {}
};

class RelationsManager
{
	class IndxsPair
	{
		friend class RelationsManager;
		private:
		int SystemIndx;
		int SensorIndx;
		IndxsPair(int SystemIndx, int SensorIndx):SystemIndx(SystemIndx), SensorIndx(SensorIndx){};
	};

	list<Sensor> Sensors;
	list<System> Systems;
	list<IndxsPair> Relations;

public:

	int FindSensor(int SensorId)
	{
		int i = 0;
		list<Sensor>::iterator it = this->Sensors.begin();
		for (; it != this->Sensors.end(); it++, i++)
		{
			if ((*it).Id == SensorId)
			{
				return i;
			}
		}
		return -1;
	}

	int FindSystem(int SystemId)
	{
		int i = 0;
		list<System>::iterator it = this->Systems.begin();
		for (; it != this->Systems.end(); it++, i++)
		{
			if ((*it).Id == SystemId)
			{
				return i;
			}
		}
		return -1;
	}

	void AddSensor(Sensor Sensor)
	{
		int indx = FindSensor(Sensor.Id);
		
		if (indx == -1)
		{
			this->Sensors.push_back(Sensor);
		}
		else
		{
			throw list_contains_sensor("list already contains a sensor with ID " + to_string(Sensor.Id));
		}
	}

	void AddSystem(System System)
	{
		int indx = FindSystem(System.Id);

		if (indx == -1)
		{
			this->Systems.push_back(System);
		}
		else
		{
			throw list_contains_system("list already contains a system with ID " + to_string(System.Id));
		}
	}

	void IncludeSensorToSystem(int SensorId, int SystemId)
	{
		int SensorIndx = FindSensor(SensorId);
		int SystemIndx = FindSystem(SystemId);

		if (SensorIndx == -1)
		{
			throw list_not_contains_sensor("list not contains a sensor with ID " + to_string(SensorId));
		}

		if (SystemIndx == -1)
		{
			throw list_not_contains_system("list not contains a system with ID " + to_string(SystemId));
		}

		for (list<IndxsPair>::iterator it = this->Relations.begin(); it != this->Relations.end(); it++)
		{
			if ((*it).SensorIndx == SensorIndx)
			{
				throw sensor_already_included("sensor with ID " + to_string(SensorId) + " already included in other system");
			}
		}

		this->Relations.push_back(IndxsPair(SystemIndx, SensorIndx));
	}

	void ExcludeSensorFromSystem(int SensorId)
	{
		int SensorIndx = FindSensor(SensorId);

		if (SensorIndx == -1)
		{
			throw list_not_contains_sensor("list not contains a sensor with ID " + to_string(SensorId));
		}

		for (list<IndxsPair>::iterator it = this->Relations.begin(); it != this->Relations.end(); it++)
		{
			if ((*it).SensorIndx == SensorIndx)
			{
				this->Relations.erase(it);
				break;
			}
		}
	}

	void RemoveSystem(int SystemId)
	{
		int indx = FindSystem(SystemId);

		if (indx == -1)
		{
			throw list_not_contains_system("list not contains a system with ID " + to_string(SystemId));
		}

		list<System>::iterator it = this->Systems.begin();
		advance(it, indx);

		/*for (; it != this->Systems.end(); it++)
		{
			if ((*it).Id == SystemId)
			{
				it = this->Systems.erase(it);
				break;
			}
		}*/

		it = this->Systems.erase(it);

		ClearRelations(indx);
	}
	void ClearSensors()
	{
		int i = 0;
		list<Sensor>::iterator it1 = this->Sensors.begin();
		for (; it1 != this->Sensors.end(); )
		{
			bool clear = true;
			for (list<IndxsPair>::iterator it2 = this->Relations.begin(); it2 != this->Relations.end(); it2++)
			{
				//delete equal
				if (i == (*it2).SensorIndx)
				{
					clear = false;
					break;
				}
			}

			if (clear)
			{
				it1 = this->Sensors.erase(it1);
				for (list<IndxsPair>::iterator it2 = this->Relations.begin(); it2 != this->Relations.end(); it2++)
				{
					//shift greter indxs
					if ((*it2).SensorIndx > i)
					{
						(*it2).SensorIndx--;
					}
				}
			}
			else
			{
				it1++;
				i++;
			}
		}
	}
	private:
	void ClearRelations(int SystemIndx)
	{
		for (list<IndxsPair>::iterator it = this->Relations.begin(); it != this->Relations.end(); )
		{
			//delete equal
			if ((*it).SystemIndx == SystemIndx)
			{
				it = this->Relations.erase(it);
			}//shift greter indxs
			else 
			{
				if ((*it).SystemIndx > SystemIndx)
				{
					(*it).SystemIndx -= 1;
				}
				it++;
			}
		}
	}

	public:
	

	void PrintSensors(int SystemId)
	{
		int SystemIndx = FindSystem(SystemId);
		if (SystemIndx == -1)
		{
			throw list_not_contains_system("list not contains a system with ID " + to_string(SystemId));
		}
		list<System>::iterator it2 = this->Systems.begin();
		advance(it2, SystemIndx);
		cout << (*it2).Name<<": ";
		for (list<IndxsPair>::iterator it = this->Relations.begin(); it != this->Relations.end(); it++)
		{
			if ((*it).SystemIndx == SystemIndx)
			{
				list<Sensor>::iterator it1 = this->Sensors.begin();
				advance(it1, (*it).SensorIndx);
				cout << (*it1).Name<<" ";
			}
		}
		cout<< endl;
	}

};

int main()
{
	RelationsManager Rm;

	//Add sensors
	cout << "Add sensors" << endl;
	try
	{
		Rm.AddSensor(Sensor(11, "A1"));
	}
	catch (incorrect_id ex)
	{
		cout << ex.message<<endl;
	}

	Rm.AddSensor(Sensor(100, "A0"));
	Rm.AddSensor(Sensor(101, "A1"));
	Rm.AddSensor(Sensor(102, "A2"));
	Rm.AddSensor(Sensor(103, "A3"));
	Rm.AddSensor(Sensor(104, "A4"));
	Rm.AddSensor(Sensor(105, "A5"));
	Rm.AddSensor(Sensor(106, "A6"));
	Rm.AddSensor(Sensor(107, "A7"));
	Rm.AddSensor(Sensor(108, "A8"));
	Rm.AddSensor(Sensor(109, "A9"));
	

	try
	{
		Rm.AddSensor(Sensor(109, "A10"));
	}
	catch (list_contains_sensor ex)
	{
		cout << ex.message << endl;
	}


	//Add systems
	cout << "Add systems" << endl;
	try
	{
		Rm.AddSystem(System(112, "B1"));
	}
	catch (incorrect_id ex)
	{
		cout << ex.message << endl;
	}

	Rm.AddSystem(System(10, "B0"));
	Rm.AddSystem(System(11, "B1"));
	Rm.AddSystem(System(12, "B2"));
	Rm.AddSystem(System(13, "B3"));

	try
	{
		Rm.AddSystem(System(12, "B1"));
	}
	catch (list_contains_system ex)
	{
		cout << ex.message << endl;
	}


	cout << "Include sensors to systems" << endl;
	//1
	Rm.IncludeSensorToSystem(100, 10);
	Rm.IncludeSensorToSystem(101, 10);
	Rm.IncludeSensorToSystem(102, 10);
	//2
	Rm.IncludeSensorToSystem(103, 11);
	Rm.IncludeSensorToSystem(104, 11);
	Rm.IncludeSensorToSystem(105, 11);
	Rm.IncludeSensorToSystem(106, 11);
	//3
	Rm.IncludeSensorToSystem(107, 12);
	Rm.IncludeSensorToSystem(108, 12);
	//4
	Rm.IncludeSensorToSystem(109, 13);

	//print
	Rm.PrintSensors(10);
	Rm.PrintSensors(11);
	Rm.PrintSensors(12);
	Rm.PrintSensors(13);

	try
	{
		Rm.IncludeSensorToSystem(100, 12);
	}
	catch (sensor_already_included ex)
	{
		cout << ex.message << endl;
	}

	try
	{
		Rm.IncludeSensorToSystem(111, 12);
	}
	catch (list_not_contains_sensor ex)
	{
		cout << ex.message << endl;
	}

	try
	{
		Rm.IncludeSensorToSystem(100, 15);
	}
	catch (list_not_contains_system ex)
	{
		cout << ex.message << endl;
	}

	cout << "Exclude sensors from systems" << endl;

	Rm.ExcludeSensorFromSystem(101);
	Rm.ExcludeSensorFromSystem(104);
	Rm.ExcludeSensorFromSystem(107);

	//print
	Rm.PrintSensors(10);
	Rm.PrintSensors(11);
	Rm.PrintSensors(12);
	Rm.PrintSensors(13);

	try
	{
		Rm.ExcludeSensorFromSystem(777);
	}
	catch (list_not_contains_sensor ex)
	{
		cout << ex.message << endl;
	}

	cout << "Clear sensors" << endl;
	Rm.ClearSensors();
	//print
	Rm.PrintSensors(10);
	Rm.PrintSensors(11);
	Rm.PrintSensors(12);
	Rm.PrintSensors(13);

	cout << "Remove system" << endl;
	Rm.RemoveSystem(10);
	try
	{
		//print
		Rm.PrintSensors(10);
	}
	catch (list_not_contains_system ex)
	{
		cout << ex.message << endl;
	}
	Rm.PrintSensors(11);
	Rm.PrintSensors(12);
	Rm.PrintSensors(13);


	return 0;
}