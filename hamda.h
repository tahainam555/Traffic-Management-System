#ifndef _HAMDA_H
#define _HAMDA_H
#include "taha.h"
#include <queue>

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

    LinkedList(string p = "", ListNode *h = NULL)
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

my_stack Dijkstra2(Graph &g, char start, char end)
{
    my_stack s;
    int startVertex = vertexHash(start);
    int endVertex = vertexHash(end);
    float *distance = new float[g.vertices];
    bool *visited = new bool[g.vertices];
    char *path = new char[g.vertices];
    for (int i = 0; i < g.vertices; i++)
    {
        distance[i] = 999999;
        visited[i] = false;
        path[i] = ' ';
    }
    distance[startVertex] = 0;
    for (int i = 0; i < g.vertices; i++)
    {
        int minVertex = -1;
        for (int j = 0; j < g.vertices; j++)
        {
            if (!visited[j] && (minVertex == -1 || distance[j] < distance[minVertex]))
            {
                minVertex = j;
            }
        }
        visited[minVertex] = true;
        for (Node *temp = g.list[minVertex].head; temp != NULL; temp = temp->next)
        {
            int adjVertex = vertexHash(temp->vertex);
            if (distance[minVertex] + temp->weight < distance[adjVertex])
            {
                distance[adjVertex] = distance[minVertex] + temp->weight;
                path[adjVertex] = minVertex + 'A';
            }
        }
    }

    // cout << "All possible paths from " << start << " to " << end << " are: " << endl;
    for (int i = 0; i < g.vertices; i++)
    {
        if (i != startVertex && path[i] != ' ')
        {
            cout << "Path:  ";
            char temp = path[i];
            my_stack tempStack;
            while (temp != ' ')
            {
                tempStack.push(temp);
                temp = path[vertexHash(temp)];
            }
            while (!tempStack.isEmpty())
            {
                char top = tempStack.getTop();
                cout << top << " ";
                s.push(top);
                tempStack.pop();
            }
            cout << end << " | Total Weight: " << distance[i] << endl;
        }
    }

    delete[] distance;
    delete[] visited;
    delete[] path;

    return s;
}

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
        if (a == b)
            return;
        // cout << "inserting " << vehicle << endl;
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
            // table[i].display();
        }
    }

    my_stack BFS(Graph &g, char start, char end)
    {
        my_stack path;
        bool *visited = new bool[g.vertices];
        for (int i = 0; i < g.vertices; i++)
        {
            visited[i] = false;
        }

        queue<int> q;
        int *prev = new int[g.vertices];
        for (int i = 0; i < g.vertices; i++)
        {
            prev[i] = -1;
        }

        int startVertex = vertexHash(start);
        int endVertex = vertexHash(end);
        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            if (current == endVertex)
            {
                break;
            }

            for (Node *temp = g.list[current].head; temp != NULL; temp = temp->next)
            {
                int adjVertex = vertexHash(temp->vertex);
                if (!visited[adjVertex])
                {
                    visited[adjVertex] = true;
                    prev[adjVertex] = current;
                    q.push(adjVertex);
                }
            }
        }

        for (int at = endVertex; at != -1; at = prev[at])
        {
            path.push(at + 'A');
        }

        delete[] visited;
        delete[] prev;

        return path;
    }

    void storeData(Vehicles *vehicle, Graph &g)
    {
        for (int i = 1; i < 31; i++)
        {
            cout << "vehicle " << vehicle[i].id << endl;
            // cout << "vehicles : " << vehicle[i].id << " start: " << vehicle[i].start << " end : " << vehicle[i].end << endl;

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
                cout << "start " << start << " end " << end << endl;
                ss.pop();
                insert(start, end, vehicle[i].id);
            }
            start = end;
            end = vehicle[i].end;
            // ss.pop();
            cout << "start " << start << " end " << end << endl;

            insert(start, end, vehicle[i].id);
        }
        count();
    }

    void dfs(Graph &g, int v, bool visited[], char end, my_stack &path, bool &found)
    {
        visited[v] = true;
        path.push(v + 'A');

        if (v == vertexHash(end))
        {
            found = true;
            return;
        }

        for (Node *temp = g.list[v].head; temp != NULL; temp = temp->next)
        {
            int adjVertex = vertexHash(temp->vertex);
            if (!visited[adjVertex])
            {
                dfs(g, adjVertex, visited, end, path, found);
                if (found)
                    return;
            }
        }

        path.pop();
    }

    my_stack DFS(Graph &g, char start, char end)
    {
        my_stack path;
        bool *visited = new bool[g.vertices];
        for (int i = 0; i < g.vertices; i++)
        {
            visited[i] = false;
        }

        bool found = false;
        dfs(g, vertexHash(start), visited, end, path, found);

        delete[] visited;
        return path;
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

void simulation(Graph &g, char a, char b)
{
    my_stack s;
    cout << "All possible paths from " << a << " to " << b << " are: " << endl;
    s = Dijkstra2(g, a, b);
    // while (!s.isEmpty())
    // {
    //     char start = s.getTop();
    //     char end = s.getTop();
    //     s.pop();
    //     // cout<<"Path : "<<start<<" -> c"<<end<<endl;
    //     my_stack path = Dijkstra2(g, start, end);
    //     cout<<endl;
    // }
}
#endif