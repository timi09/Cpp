#include <iostream>
#include <string>

using namespace std;

template <typename DataType>
class Node;

template <typename T>
class List
{
    Node<T>* First; 
    Node<T>* Last;
    int Count = 0;

public:
    int getCount()
    {
        return Count;
    }

    List()
    {
        First = Last = nullptr;
    }

    List(T* Array, int Count)
    {
        for (size_t i = 0; i < Count; i++)
        {
            Add(Array[i]);
        }
    }

    List(List<T>& ListObj)
    {
        int Count = ListObj.getCount();
        for (size_t i = 0; i < Count; i++)
        {
            Add(ListObj.At(i));
        }
    }

    void Add(T Element)
    {
        Node<T>* temp = new Node<T>(Element);

        if (First == nullptr)
        {
            First = temp;
            Last = temp;
        }
        else
        {
            Last->Next = temp;
            temp->Prev = Last;
            Last = temp;
        }
        Count++;
    }

    private: Node<T>* NodeAt(int Indx)
    {
        Node<T>* Elem = First;
        for (size_t i = 0; i < Indx; i++)
        {
            Elem = Elem->Next;
        }
        return Elem;
    }

    public:
    T At(int Indx)
    {
        NodeAt(Indx)->Data;
    }

    void Remove(int Indx)
    {
        Node<T>* Elem = NodeAt(Indx);
        Node<T>* Before = Elem->Prev;
        Node<T>* After = Elem->Next;

        if (Before != nullptr)
        {
            Before->Next = After;
        }
        else
        {
            First = After;
        }

        if (After != nullptr)
        {
            After->Prev = Before;
        }
        else
        {
            Last = Before;
        }

        delete Elem;
        Count--;
    }

    bool IsEmpty()
    {
        if (First == nullptr)
        {
            return true;
        }
        return false;
    }

    void ToString()
    {
        Node<T>* Elem = First;
        while (Elem != nullptr)
        {
            cout << Elem->Data << endl;
            Elem = Elem->Next;
        }
    }

    void operator-(int Num)
    {
        Remove(1);
    }
};

template <typename DataType>
class Node 
{ 
    friend class List<DataType>;
    DataType Data;
    Node* Next;
    Node* Prev;
    Node(DataType Data = 0)
    {
        this->Data = Data;
        this->Next = nullptr;
        this->Prev = nullptr;
    }
};

int main()
{
    List<int> list1;

    cout << "List(empty): " << endl;
    list1.ToString();
    cout << "Is empty: " + to_string(list1.IsEmpty())<< endl;
    
    cout << "List(add 3 elem): " << endl;
    list1.Add(5);
    list1.Add(2);
    list1.Add(3);
    
    list1.ToString();
    cout << "Is empty: " + to_string(list1.IsEmpty()) << endl;

    cout << "List(remove 2nd elm): " << endl;
    list1.Remove(1);

    list1.ToString();
    cout << "Is empty: " + to_string(list1.IsEmpty()) << endl;

    cout << "List(remove all): " << endl;
    while(!list1.IsEmpty())
    {
        list1.Remove(0);
    }
    list1.ToString();
    cout << "Is empty: " + to_string(list1.IsEmpty()) << endl;

    cout << "List(from array): " << endl;

    string* Array = new string[3];
    Array[0] = "aaa";
    Array[1] = "bbb";
    Array[2] = "ccc";

    List<string> list2(Array, 3);
    list2.ToString();

    cout << "List(copy): " << endl;
    List<string> list3(list2);
    list3.ToString();

    cout << "operator \"-\": " << endl;
    list3-0;
    list3.ToString();

    return 0;
}
