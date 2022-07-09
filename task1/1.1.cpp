#include <iostream>
#include <string>

using namespace std;

enum Level { easy, normal, hard };
string LvlToStr(Level lvl)
{
	switch (lvl)
	{
	case 0: return "easy";
	case 1: return "normal";
	case 2: return "hard";
	}
}

class Task
{
private:
	int Num;
	string Text;

public:
	Task(int Num, string Text)
	{
		this->Num = Num;
		this->Text = string(Text);

		cout << "Create Task obj " + to_string(this->Num) << endl;
	}

	Task(const Task& CopyObj)
	{
		this->Num = CopyObj.Num;
		this->Text = string(CopyObj.Text);
		cout << "Copy Task obj " + to_string(this->Num) << endl;
	}

	~Task()
	{
		cout << "Destruct Task obj " + to_string(this->Num) << endl;
	}

public:
	void Print()
	{
		cout << " " + to_string(this->Num);
		cout << ". " + this->Text << endl;
	}
};

class LabWork
{
private:
	int Num;
	string Name;
	Level Lvl;

	Task** Tasks;
	int TaskCount;

public:
	LabWork(int Num, string Name, Level Lvl, Task** Tasks, int
		TaskCount)
	{
		cout << "Create LabWork obj with params" << endl;

		this->Num = Num;
		this->Name = string(Name);
		this->Lvl = Lvl;
		CopyTasks(Tasks, TaskCount);
	}

	LabWork() : Num(1), Name("Some lab name"), Lvl(easy),

		Tasks(nullptr), TaskCount(0)
	{
		cout << "Create default LabWork obj" << endl;
	}

	LabWork(const LabWork& CopyObj) : Num(CopyObj.Num),

		Name(CopyObj.Name), Lvl(CopyObj.Lvl)
	{
		cout << "Copy LabWork obj from another obj" << endl;
		CopyTasks(CopyObj.Tasks, CopyObj.TaskCount);
	}

	~LabWork()
	{
		if (Tasks != nullptr)
		{
			cout << "Destruct LabWork obj " + to_string(this->Num) <<

				endl;

			for (int i = 0; i < TaskCount; i++)
			{

				delete Tasks[i];
			}
			delete[] Tasks;

			Tasks = nullptr;
		}

	}

	void Print()
	{
		cout << endl;
		cout << " Laboratory work " + to_string(this->Num) <<

			endl;

		cout << " Title: " + this->Name << endl;
		cout << "Level: " + LvlToStr(this->Lvl) << endl;
		cout << "Tasks: " << endl;

		for (int i = 0; i < TaskCount; i++)
		{
			this->Tasks[i]->Print();
		}
		cout << endl;
	}

private:
	void CopyTasks(Task** tasks, int tasksCount)
	{
		this->Tasks = new Task * [tasksCount];
		for (int i = 0; i < tasksCount; i++)
		{
			Tasks[i] = new Task(*tasks[i]);
		}

		this->TaskCount = tasksCount;
	}
};

int main()
{
	int taskCount = 3;
	Task** tasks = new Task * [taskCount];
	for (int i = 0; i < taskCount; i++)
	{
		tasks[i] = new Task(i + 1, "Some text for task");
		tasks[i]->Print();
	}

	LabWork lab1 = LabWork();
	lab1.Print();

	LabWork lab2 = LabWork(2, "Name of lab 2", normal, tasks,
		taskCount);
	lab2.Print();

	LabWork lab3 = LabWork(lab2);
	lab3.Print();

	cout << "delete tasks" << endl;
	for (int i = 0; i < taskCount; i++)
	{
		delete tasks[i];
	}
	delete[] tasks;
	cout << endl;

	cout << "delete lab3 (copy of lab 2)" << endl;

	lab3.~LabWork();
	cout << endl;
}