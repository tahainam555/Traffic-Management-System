#ifndef MINAHIL_H
#define MINAHIL_H
#include<iostream>
#include"taha.h"
using namespace std;

struct priorityQNode 
{
    int time;         
    char intersection; 
};

class priorityQ 
{
    private:
        priorityQNode *data;
        int size;
        int capacity;
    public:
        priorityQ(int num) 
        {
            data = new priorityQNode[num+1];
            size = 1;
            capacity = num;
        }

        int getSize() 
        {
            return size;
        }

        void enqueue(int time, char intersection) 
        {
            if (size == capacity) 
            {
                cout<<"Queue is full"<<endl;
                return;
            }
            data[size].time = time;
            data[size].intersection = intersection;
            int i = size;
            size++;
            while (i > 1) 
            {
                int parent = i / 2;
                if (data[parent].time > data[i].time) 
                {
                    priorityQNode temp = data[parent];
                    data[parent] = data[i];
                    data[i] = temp;
                    i = parent;
                }
                else {
                    break;
                }
            }
        }

        void dequeue() 
        {
            if (size == 1) 
            {
                cout<<"Queue is empty"<<endl;
                return;
            }
            data[1] = data[size-1];
            size--;
            int i = 1;
            while (i < size) 
            {
                int left = 2 * i;
                int right = 2 * i + 1;
                int minIndex = i;
                if (left < size && data[left].time < data[minIndex].time) 
                {
                    minIndex = left;
                }
                if (right < size && data[right].time < data[minIndex].time) 
                {
                    minIndex = right;
                }
                if (minIndex == i) 
                {
                    break;
                }
                priorityQNode temp = data[i];
                data[i] = data[minIndex];
                data[minIndex] = temp;
                i = minIndex;
            }
        }

        bool isEmpty() 
        {
            return size == 1; 
        }

        void displayQueue() 
        {
            while (size > 1) 
            {
                cout<<data[1].intersection<<" Green Time "<<data[1].time<<"\n";
                dequeue();
            }
        }
        void print() 
        {
            for (int i = 1; i < size; i++) 
            {
                cout<<data[i].intersection<<" Green Time "<<data[i].time<<endl;
            }
        }

        char peekIntersection() 
        {
            if (size > 1) 
            {
                return data[1].intersection;
            }
            
            return ' ';
    }
};

class emergencyRouting
{
    private:
        float *distance;      
        bool *visited;    
        char *previous;      
        priorityQ *P1;
        Graph *graph;
    
    public:
        emergencyRouting(Graph* G1, int num)
        {
            graph = G1;
            distance = new float[num];
            visited = new bool[num];
            previous = new char[num];
            P1 = new priorityQ(num);

            for (int i = 0; i<num; i++)
            {
                distance[i] = 999999;
                visited[i] = false;
                previous[i] = ' ';
            }

        }

        ~emergencyRouting() 
        {
            delete[] distance;
            delete[] visited;
            delete[] previous;
            delete P1;
        }

        void ASearch(char start, char end)
        {
            cout<<"Emergency vehicle is being routed..."<<endl;

            int startVertex = vertexHash(start);
            int endVertex = vertexHash(end);    

            distance[startVertex] = 0;
            P1->enqueue(0, start);

            while (!P1->isEmpty()) 
            {
                char current = P1->peekIntersection();
                P1->dequeue();

                int currVertex = vertexHash(current);
                if (visited[currVertex]) 
                {
                    continue;
                }
                visited[currVertex] = true;

                if (current == end) 
                {
                    break;
                }

                Node* neighbour = graph->list[currVertex].head;
                while (neighbour != NULL) 
                {
                    int neighborVertex = vertexHash(neighbour->vertex);
                    if (visited[neighborVertex]) 
                    {
                        neighbour = neighbour->next;
                        continue;
                    }

                    float newCost = distance[currVertex] + neighbour->weight;
                    float heuristic = abs(neighborVertex - endVertex); 
                    float totalCost = newCost + heuristic;

                    if (newCost < distance[neighborVertex]) 
                    {
                        distance[neighborVertex] = newCost;
                        previous[neighborVertex] = current;
                        P1->enqueue(totalCost, neighbour->vertex);
                    }

                    neighbour = neighbour->next;
                }
            }

            printPath(start, end);

        }

        void printPath(char start, char end) 
        {
            cout<<"Emergency Vehicle path: ";
            char path[100];
            int index = 0;

            char current = end;
            while (current != start) 
            {
                path[index++] = current;
                current = previous[vertexHash(current)];
            }
            path[index++] = start;

            for (int i = index - 1; i >= 0; i--) 
            {
                cout<<path[i]<<" ";
            }
            cout<<endl;
        }

};

#endif 