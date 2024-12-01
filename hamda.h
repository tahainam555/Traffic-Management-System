#ifndef _HAMDA_H
#define _HAMDA_H
#include "taha.h"

struct Node
{
    Node *next;
    string vehicle;

    Node(string v = "", Node *nxt = NULL)
    {
        vehicle = v;
        next = nxt;
    }
};

class List
{
public:
    Node *head;

    void append(Node *add)
    {
        if (head == NULL)
        {
            head = add;
            return;
        }

        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = add;
    }

    void display()
    {
        Node *temp = head;
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
    List *table;
    int size;
    int *count;

    HashTable(int n = 353)
    {
        table = new List[n];
        size = n;
        count = new int[n];
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
        Node *add = new Node(vehicle);
        table[i].append(add);
    }

    void count()
    {
        for (int i = 0; i < size; i++)
        {
            Node *temp = table[i].head;
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
};

#endif