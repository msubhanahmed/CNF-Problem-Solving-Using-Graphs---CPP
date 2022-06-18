#include<iostream>
#include<Windows.h>

using namespace std;

template<typename T>
struct linklistnode //linklist node class with name of vertex , weight and next ptr
{
public:
    T data;
    int weight;
    linklistnode<T>* next;

    linklistnode(T input = 0, int www = INT_MAX)   //intialize with weight equal to INT_MAX
    {
        weight = www;
        data = input;
        next = NULL;
    }
};

template<typename T>
class linkedlist
{
private:
    linklistnode<T>* head;
public:
    linkedlist(linklistnode<T>* input = NULL)
    {
        head = input;
    }
    linklistnode<T>* gethead() { return head; }
    //check if empty
    bool isEmpty()
    {
        if (!head)
        {
            return true;
        }
        return false;
    }
    //insert in list
    void insert(T data, int weight)
    {
        if (!head)
        {
            head = new linklistnode<T>(data);
        }
        else
        {
            linklistnode<T>* curr = head;
            while (curr->next)
                curr = curr->next;
            curr->next = new linklistnode<T>(data, weight);
        }
    }
    void show()
    {
        if (!isEmpty())
        {
            linklistnode<T>* curr = head;
            while (curr->next)
            {
                cout << curr->data << "->";
                curr = curr->next;
            }
            cout << curr->data << "\n";
        }
    }
    ~linkedlist()
    {

    }
};

template <typename T>
struct graphnode                //adjacency list
{
    T vertexname;               //vertex name
    graphnode<T>* next;         //next vertex
    linkedlist<T> neighbours;   //its neighbours

    graphnode(T name)
    {
        vertexname = name;
        next = NULL;
    }
};

template<typename T>
class Graph
{
private:
    graphnode<T>* head;
public:
    Graph()
    {
        head = NULL;
    }
    graphnode<T>* gethead() { return head; }
    //insert node in graph simple list insertion
    void insertnode(T vertexname)
    {
        if (!head)
        {
            head = new graphnode<T>(vertexname);
        }
        else
        {
            graphnode<T>* curr = head;
            while (curr->next)
            {
                curr = curr->next;
            }
            curr->next = new graphnode<T>(vertexname);
        }
    }
    //insert edge in graph find the source vertex , make a new edge with given weight
    bool insertedge(T vertex, T edge, int ww)
    {
        if (head == NULL)
        {
            return false;
        }
        else
        {
            graphnode<T>* curr2 = head;
            while (curr2 && curr2->vertexname != vertex)
            {
                curr2 = curr2->next;
            }
            if (curr2)
            {
                curr2->neighbours.insert(edge, ww);
                return true;
            }
        }
        return false;
    }
    //show graph adjacency list
    void show()
    {
        if (head == NULL)
        {
            return;
        }
        else
        {
            graphnode<T>* trav = head;
            while (trav)
            {
                cout << trav->vertexname << "==>    ";
                trav->neighbours.show();
                cout << '\n';
                trav = trav->next;
            }

        }
    }
    //fucntion to get required vertex name in graph
    graphnode<T>* returnvertex2(int number)  //return vertex name based on count provided (count starts from 0 ) 0 == first node
    {
        graphnode<T>* curr = head;
        for (int i = 0; i < number; i++)
        {
            curr = curr->next;
        }
        return curr;
    }
};