#ifndef _HAMDA_H
#define _HAMDA_H
#include "taha.h"

struct LinkedListNode
{
    LinkedListNode *next;
    string vehicle;

    LinkedListNode(string v = "", LinkedListNode *nxt = NULL)
    {
        vehicle = v;
        next = nxt;
    }
};

class LinkedList
{
public:
    LinkedListNode *head;

    void append(LinkedListNode *add)
    {
        if (head == NULL)
        {
            head = add;
            return;
        }

        LinkedListNode *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = add;
    }

    void display()
    {
        LinkedListNode *temp = head;
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
    int *count;
    Vehicles *vehicle;
    // Graph g;

    HashTable(int n = 353)
    {
        table = new LinkedList[n];
        size = n;
        count = new int[n];
        // vehicle = v;
        // g = gg;
        for (int i = 0; i < n; i++)
        {
            count[i] = 0;
        }
    }

    int HashFunction(char a, char b)
    {
        int ascii1 = a;
        int ascii2 = b;

        int max = max(ascii1, ascii2);
        int min = min(ascii1, ascii2);

        int index = (min * 128 + max);
        return index % size;
    }

    string reverseHashFunction(int index)
    {
        int originalIndex = index;
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                int min = min(i, j);
                int max = max(i, j);
                if ((min * 128 + max) % size == originalIndex)
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
        int i = HashFunction(a, b);
        LinkedListNode *add = new LinkedListNode(vehicle);
        table[i].append(add);
    }

    void count()
    {
        for (int i = 0; i < size; i++)
        {
            LinkedListNode *temp = table[i].head;
            while (temp != NULL)
            {
                temp = temp->next;
                count[i]++;
            }
        }
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            string str = reverseHashFunction(i);
            if (str == "")
            {
                continue;
            }
            cout << str[0] << " to " << str[1] << count[i] << endl;
        }
    }

    void storeData(Graph g, Vehicles *vehicle)
    {
        for (int i = 0; i < 31; i++)
        {
            char a = vehicle[i].start;
            char b = vehicle[i].end;
            my_stack ss;
            ss = Dijkstra(g, a, b);
            char start = '\0';
            char end = '\0';
            start = ss.getTop();
            end = ss.getTop();
            ss.pop();
            while (!ss.isEmpty())
            {
                start = end;
                end = ss.getTop();
                ss.pop();
                insert(start, end, vehicle[i].id);
            }
        }
    }
};

#endif
// okayy end