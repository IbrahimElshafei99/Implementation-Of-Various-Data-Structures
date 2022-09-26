#include <iostream>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <bits/stdc++.h>
#define Null 0
using namespace std;
const int Max_Size=1000;
                          ///////////////////////////////////////////////
                                     ///problem 1
template <class DataType>
class List
{
private:
    struct node
    {
        DataType data;
        node *next;
        node *prev;
    };
    node *first;
    node *last;
    int SIZE;
public:

    class Iterator
    {
        friend class List;
    private:
        node *it;
    public:
        void operator++(int)
        {
            if(it->next==Null)
                cout<<"Cannot increment"<<endl;
            else
            {
                Iterator temp=*this;
                it=it->next;
            }
        }
        void operator--(int)
        {
            if(it->prev==Null)
                cout<<"Cannot decrement"<<endl;
            else
            {
                Iterator temp=*this;
                it=it->prev;
            }
        }
    };

    List()
    {
        first=Null;
        last=Null;
        SIZE=0;
    }
    List(DataType value, int initial_size)
    {
        first->data=value;
        first->next=Null;
        first->prev=Null;
        last=first;
        SIZE=initial_size;

    }

    ~List()
    {
        node *temp;
		while (first != NULL)
		{
			temp = first;
			first = first->next;
			delete temp;
		}
		last = NULL;
		SIZE = 0;
    }

    int Size(){return SIZE;}
    void Insert(DataType value, Iterator position)
    {
            node *newNode=new node;
            newNode->data=value;
            //add at first
            if(position.it==first)
            {
                //if list is empty
                if(SIZE==0)
                {
                    first=newNode;
                    last=newNode;
                    newNode->next=Null;
                    newNode->prev=Null;
                }
                //if list not empty
                else
                {
                    newNode->next=first;
                    newNode->prev=Null;
                    first->prev=newNode;
                    first=newNode;
                }
                SIZE++;
            }
            //add at last
            else if(position.it==last)
            {
             //if list is empty
                if(SIZE==0)
                {
                    first=newNode;
                    last=newNode;
                    newNode->next=Null;
                    newNode->prev=Null;
                }
                //if list not empty
                else
                {
                    newNode->next=Null;
                    newNode->prev=last;
                    last->next=newNode;
                    last=newNode;
                }
                SIZE++;
            }
            else
            {
                newNode->next=position.it;
                newNode->prev=position.it->prev;
                position.it->prev->next=newNode;
                position.it->prev=newNode;
                SIZE++;
            }
    }

    Iterator Erase(Iterator position)
    {
        if(first==last)
        {
            delete first;
            last=Null;
            first=Null;
        }
        else if(position.it==first)
        {
            first=first->next;
            first->prev=Null;
            delete position.it;
        }
        else if(position.it==last)
        {
            last=last->prev;
            last->next=Null;
            delete position.it;
        }
        else
        {
            position.it->prev->next=position.it->next;
            position.it->next->prev=position.it->prev;
            delete position.it;
        }
        SIZE--;
    }
    Iterator Begin()
    {
        Iterator F;
        F.it=first;
        return F;
    }
    Iterator End()
    {
        Iterator L;
        L.it=last;
        return L;
    }
    List<DataType> &operator=(List<DataType> another_list)
    {
        if(this==&another_list)
            return *this;
        Iterator i;
        while(another_list.first->next != Null)
        {
            i.it=another_list.first;
            Insert(i.it->data,i);
            another_list.first=another_list.first->next;
        }
        return *this;
    }

    void print()
    {
        if(first==Null)
            cout<<"It is empty"<<endl;
        else
        {
            Iterator temp;
            temp.it=first;
            while(temp.it!=Null)
            {
                cout<<temp.it->data<<" ";
                temp.it=temp.it->next;
            }
        }
        cout<<endl;
    }

};
                          ///////////////////////////////////////////////
                                     ///problem 2
void Swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
int Partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
class TestSorting
{
private:
    int RArr[Max_Size];
    double time_taken;
public:
    TestSorting(){}
    void GenerateRandomList(int Min, int Max, int Size)
    {
        int range=Max - Min +1;
        RArr[Size];
        for(int i=0; i<Size; i++)
        {
            RArr[i]=rand() % range + Min;
        }
        cout<<"Random list: "<<endl;
        printArray(RArr, Size);
    }

    void RunOnce(string sorter, int data[], int Size)
    {
        clock_t start,finish;
        if(sorter == "Selection")
        {
            start = clock();
           int min_idx;
           for (int i = 0; i<Size-1; i++)
           {
               min_idx = i;
               for (int j = i+1; j<Size; j++)
               {
                  if (data[j] < data[min_idx])
                  min_idx = j;
               }
               Swap(&data[min_idx], &data[i]);
            }
            cout<<"Sorted array: "<<endl;
            printArray(data, Size);
            finish = clock();
        }
        else if(sorter == "Quick")
        {
            start = clock();
            int l=0, h=Size-1;
            quickSort(data,l,h);
            cout<<"Sorted array: "<<endl;
            printArray(data,Size);
            finish = clock();
        }

        time_taken=double(finish-start)/double(CLOCKS_PER_SEC/1000);
        cout << "Time taken: " << fixed<< time_taken << setprecision(2);
        cout << " sec " << endl;

    }
    void RunAndAverage(string sorter, int Min, int Max, int Size, int sets_num)
    {
        double Ttime;
        for(int i=0; i<sets_num; i++)
        {
            GenerateRandomList(Min,Max,Size);
            RunOnce(sorter,RArr,Size);
            Ttime+=time_taken;
        }
        double Avgtime=Ttime/sets_num;
        cout<<"Average time = "<<Avgtime<<" sec"<<endl;
    }

    void printArray(int arr[], int s)
    {
    int i;
    for (i=0; i < s; i++)
        cout << arr[i] << " ";
    cout << endl;
    }
};
                          ////////////////////////////////////////////////
                                     ///problem 3

template <class t>
class Stack
{
    int top;
    t item[Max_Size];
public:
    Stack(){top=-1;}///default constructor
    Stack(t value, int Max_Size)///parameterize constructor
    {
        top=-1;
    }
    ~Stack()///destructor
    {
        for(int i=top; i>=0; i--)
        {
            item[i]=0;
        }
        top=-1;
    }
    t &Top(t &z)///top of elements
    {
        if(isEmpty()){}
            //cout<<"Stack empty"<<endl;
        else
        {
            z=item[top];
        }
        return z;
    }
    void push(t element)///push
    {
        if(top >= Max_Size-1)
        {
            cout<<"Stack full"<<endl;
        }
        else
        {
            top++;
            item[top] = element;
        }
    }
    bool isEmpty()
    {
        if(top == -1)
            return 1;
        else
            return 0;
    }
    void pop()///pop
    {
        if(isEmpty())
            cout<<"Stack empty";
        else
            top--;
    }
    int Size()///size
    {
        int counter=0;
        for(int i=0; i<top+1; i++)
            counter+=1;
        return counter;
    }
    void print()
    {
        for(int i=top; i>=0; i--)
        {
            cout<<item[i]<<" "<<endl;
        }
    }


};
                          ////////////////////////////////////////////////
                                     ///problem 4
bool PairedParentheses(char left, char right)
{
    if(left=='(' && right==')')
        return true;
    else if(left=='{' && right=='}')
        return true;
    else if(left=='[' && right==']')
        return true;
    else
        return false;
}
bool BalancedParentheses(string str)
{
    int begining;
    int ending;
    bool value;
    bool cvalue=false;
    Stack<char>m;
    char T;
    for(int i=0; i<str.length(); i++)
    {
        if(str[i]=='(' || str[i]=='{' || str[i]=='[')
        {
            m.push(str[i]);
        }
        else if(str[i]==')' || str[i]=='}' || str[i]==']')
        {
            m.Top(T);
            if(m.isEmpty() || !PairedParentheses(T, str[i]))
                {
                    value=false;
                }
            else
                m.pop();
        }
        else if(str[i]=='/' && str[i+1]=='*')
        {
            begining=i+1;
            m.push(str[i]);
            m.push(str[i+1]);
        }
        else if(str[i]=='*' && str[i+1]=='/')
        {
            ending=i;
            m.Top(T);
            if(m.isEmpty())
                return false;
            if(T==str[i])
            {
                m.pop();
                m.Top(T);
            }
            if(T==str[i+1])
            {
                m.pop();
                cvalue=true;
            }
        }
    }

    char M;
    if(m.isEmpty()==false && value==false)
        {
            if(cvalue==false)
                return false;
            m.Top(M);
            for(int j=ending; j>begining; j--)
            {
                if(M==str[j] && cvalue==true){
                    return true;
                }
                if(str[j]==')' || str[j]=='}' || str[j]==']'){
                    return true;
                }
                else
                    false;
            }
        }
    else return (m.isEmpty());
}
                          /////////////////////////////////////////////////
                                      ///problem 5
class Queue
{
private:
    struct Q
    {
      string v;
      int p;
      Q *last;
    };
    Q *Front;
public:
    Q *current;
    Queue(){Front=Null;}

    void addFirst(string item, int pr)
    {
        Q *temp = new Q;
        temp->v = item;
        temp->p=pr;
        temp->last = Front;
        Front = temp;
    }
    string enqueue(string val, int pri)
    {
        Q *temp = new Q;
        temp->v = val;
        temp->p = pri;
        if(Front == Null || temp->p <= Front->p)
        {
            temp->last = Front;
            Front = temp;
        }
        else
        {
            current = Front;
            while(current->last != Null && current->last->p < temp->p)
            {
                current = current->last;
            }
            temp->last = current->last;
            current->last = temp;
        }
        return Front->v;
    }
    string dequeue()
    {
        string item;
        if(Front == Null)
            cout<<"queue empty"<<endl;
        else
        {
            item = Front->v;
            Q *temp = Front;
            Front = Front->last;
            temp = temp->last = Null;
            delete temp;
        }
        return item;
    }
    void print()
    {
        if(Front==Null)
            cout<<"queue empty"<<endl;
        current = Front;
        while(current!=Null)
        {
            cout<<current->v<<" ";
            current=current->last;
        }
        cout<<endl;
    }
};


int main()
{
    ///problem 1 test
    /*List<int>l;
    List<int>::Iterator itr;
    l.Insert(50,l.Begin());
    l.Insert(60,l.Begin());
    l.Insert(70,l.Begin());
    itr=l.Begin();
    itr++;
    l.Insert(40,itr);
    itr++;
    l.Insert(100,itr);
    l.print();
    l.Erase(itr);
    l.print();
    itr=l.Begin();
    l.Erase(itr);
    l.print();
    //cout<<l.Size()<<endl;
    cout<<"another list: "<<endl;
    List<int>l2(l);
    l2.print();
    //l2=l;
    l.~List();
    l.print();
    //cout<<"another list: "<<endl;
    //List<int>l2(l);
    //l2.print();*/
    ///problem 2 test
    //"Quick"
    //"Selection"
    /*int arr[] = {10, 7, 8, 9, 1, 5};
    TestSorting qs;
    //qs.GenerateRandomList(1,10,4);
    //qs.RunOnce("Quick",arr,6);
    qs.RunAndAverage("Selection",1,10,6,3);*/
    ///problem 3 test
    /*Stack<char>s;
    s.push('a');
    s.push('b');
    s.push('c');
    s.push('d');
    s.push('e');
    s.print();
    s.pop();
    char x;
    int y;
    s.Top(x);
    y=s.Size();
    cout<<"the top is: "<<x<<endl;
    cout<<y<<endl;
    s.~Stack();
    s.print();
    cout<<s.isEmpty();*/
    ///problem 4 test
    /*
    string exp;
    cout<<"Write your exp"<<endl;
    cin>>exp;
    if(BalancedParentheses(exp))
        cout<<"valid"<<endl;
    else
        cout<<"invalid"<<endl;*/
    ///problem 5 test
    /*Queue q;
    q.enqueue("good",10);
    q.enqueue("work",5);
    q.enqueue("should",2);
    q.enqueue("be",3);
    q.enqueue("It",1);
    q.print();
    cout<<"dequeue: "<<q.dequeue()<<endl;
    cout<<"dequeue: "<<q.dequeue()<<endl;
    cout<<"dequeue: "<<q.dequeue()<<endl;
    q.print();*/
    return 0;
}
