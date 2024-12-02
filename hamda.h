#ifndef _HAMDA_H
#define _HAMDA_H
#include "taha.h"

struct ListNode
{
    ListNode *next;
    string vehicle;

    ListNode(string v = "", ListNode *nxt = NULL)
    {
        vehicle = v;
        next = nxt;
    }
};

class LinkedList
{
public:
    ListNode *head;
    string path;

    LinkedList(string p = " ", ListNode *h = NULL)
    {
        head = h;
        path = p;
    }

    void append(ListNode *add)
    {
        if (head == NULL)
        {
            head = add;
            return;
        }

        ListNode *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = add;
    }

    void display()
    {
        ListNode *temp = head;
        while (temp != NULL)
        {
            cout << temp->vehicle << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class HashTable
{
public:
    LinkedList *table;
    int size;
    int *countArray;

    HashTable(int n = 353)
    {
        table = new LinkedList[n];
        size = n;
        countArray = new int[n];
        // vehicle = v;
        // g = gg;
        for (int i = 0; i < n; i++)
        {
            countArray[i] = 0;
        }
    }

    int HashFunction(char a, char b)
    {
        int ascii1 = a;
        int ascii2 = b;

        int maximum = max(ascii1, ascii2);
        int minimum = min(ascii1, ascii2);

        int index = (minimum * 128 + maximum);
        return index % size;
    }

    string reverseHashFunction(int index)
    {
        int originalIndex = index;
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                int minimum = min(i, j);
                int maximum = max(i, j);
                if ((minimum * 128 + maximum) % size == originalIndex)
                {
                    char temp = i;
                    char temp2 = j;
                    string result = "";
                    result += temp;
                    result += temp2;
                    return result;
                }
            }
        }
        return "";
    }

    void insert(char a, char b, string vehicle)
    {
        cout << "inserting " << vehicle << endl;
        int i = HashFunction(a, b);
        ListNode *add = new ListNode(vehicle);
        if (table[i].head == NULL)
        {
            table[i].path += a;
            table[i].path += b;
        }
        table[i].append(add);
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            // string str = reverseHashFunction(i);
            if (table[i].path == "")
            {
                continue;
            }
            cout << table[i].path[0] << " to " << table[i].path[1] << " " << countArray[i] << endl;
            table[i].display();
        }
    }

    void storeData(Vehicles *vehicle, Graph &g)
    {
        for (int i = 1; i < 31; i++)
        {
            // cout<<"vehicle "<<vehicle[i].id<<endl;
            // cout << "vehicles : " << vehicle[i].id << " start: " << vehicle[i].start << " end : " << vehicle[i].end << endl;

            char a = vehicle[i].start;
            char b = vehicle[i].end;
            my_stack ss;
            ss = Dijkstra(g, a, b);
            cout << "YES" << endl;
            char start = '\0';
            char end = '\0';
            start = ss.getTop();
            end = ss.getTop();
            ss.pop();
            // cout<<"start "<<start<<" end "<<end<<endl;
            while (!ss.isEmpty())
            {
                start = end;
                end = ss.getTop();
                ss.pop();
                insert(start, end, vehicle[i].id);
            }
        }
        count();
    }

    void count()
    {
        for (int i = 0; i < size; i++)
        {
            ListNode *temp = table[i].head;
            while (temp != NULL)
            {
                temp = temp->next;
                countArray[i]++;
            }
        }
    }
};

#endif