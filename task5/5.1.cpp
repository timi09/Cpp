#include <iostream>
#include <string>

using namespace std;

template <typename DataType>
class Node;

template <typename T>
class List
{
    friend class Node<T>;
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
        First = nullptr;
        Last = nullptr;
    }

    List(T* Array, int Count): List()
    {
        for (size_t i = 0; i < Count; i++)
        {
            Add(Array[i]);
        }
    }

    List(List<T>& ListObj): List()
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
        return NodeAt(Indx)->Data;
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
        Node<T>* Elem = this->First;
        while (Elem != nullptr)
        {
            cout << Elem->Data << " ";
            Elem = Elem->Next;
        }
        cout << endl;
    }

    List<T>* operator & (List<T> List2)
    {
        List<T> newList;
        Node<T>* Node1 = this->First;
        for (int i = 0; i < this->Count; i++)
        {
            Node<T>* Node2 = List2.First;
            for (int j = 0; j < List2.Count; j++)
            {
                if(Node1->Data == Node2->Data)
                {
                    newList.Add(Node1->Data);
                }
                Node2 = Node2->Next;
            }
            Node1 = Node1->Next;
        }
        return &newList;
    }

    List<T>* operator | (List<T> List2)
    {
        List<T> newList(*this);

        Node<T>* Node1 = List2.First;
        for (int i = 0; i < List2.Count; i++)
        {
            bool Contains = false;
            Node<T>* Node2 = this->First;
            for (int j = 0; j < this->Count; j++)
            {
                if (Node1->Data == Node2->Data)
                {
                    Contains = true;
                    break;
                }
                Node2 = Node2->Next;
            }

            if(!Contains)
            {
                newList.Add(Node1->Data);
            }

            Node1 = Node1->Next;
        }
        return &newList;
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
    int* arr1 = new int[5]{ 1, 2, 3, 4, 5 };
    int* arr2 = new int[6]{ 4, 5, 6, 7, 8, 9 };

    List<int> list1(arr1, 5);
    List<int> list2(arr2, 6);

    cout << "list 1: ";
    list1.ToString();

    cout << "list 2: ";
    list2.ToString();
    
    List<int>* ListAnd = list1 & list2;
    cout << "list & : ";
    ListAnd->ToString();


    List<int>* ListOr = list1 | list2;
    cout << "list | : ";
    ListOr->ToString();

    return 0;
}