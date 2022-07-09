#include <iostream>
#include <string>

using namespace std;

template <typename DataType>
class Node;

template <typename T>
class List
{
    friend class Node<T>;
    

public:
    Node<T>* First;

    List()
    {
        First = nullptr;
    }

    void Add(T Element)
    {
        Node<T>* temp = new Node<T>(Element);

        if (First == nullptr)
        {
            First = temp;
            First->Prev = First;
            First->Next = First;
        }
        else
        {
            Node<T>* Last = First->Prev;
            
            Last->Next = temp;
            First->Prev = temp;

            temp->Prev = Last;
            temp->Next = First;
        }
    }

    Node<T>* Remove(Node<T>* Node)
    {
        return Node->Delete();
    }

public:
    
    void ToString()
    {
        Node<T>* Node = First;
        do {
            cout << Node->Data << " ";
            Node = Node->Next;
        } while (Node != First);
        cout << endl;
    }

};

template <typename DataType>
class Node
{
    friend class List<DataType>;
public:
    DataType Data;
    Node<DataType>* Next;
    Node<DataType>* Prev;
    Node(DataType Data = 0)
    {
        this->Data = Data;
        this->Next = nullptr;
        this->Prev = nullptr;
    }

private:
    Node<DataType>* Delete()
    {
        Node<DataType>* Before = Prev;
        Node<DataType>* After = Next;

        if (Before != nullptr)
        {
            Before->Next = After;
        }
        
        if (After != nullptr)
        {
            After->Prev = Before;
        }
        
        delete this;
        return After;
    }
};

int main()
{
    List<int> list;
    for (int i = 2; i <= 100; i++)
    {
        list.Add(i);
    }

    Node<int>* Node1 = list.First;
    do {
        Node<int>* Node2 = Node1->Next;
        
        while (Node2 != list.First)
        {
            if (Node2->Data % Node1->Data == 0)
            {
                Node2 = list.Remove(Node2);
            }
            else
            {
                Node2 = Node2->Next;
            }
        }
        Node1 = Node1->Next;

    } while (Node1 != list.First);

    list.ToString();

    return 0;
}