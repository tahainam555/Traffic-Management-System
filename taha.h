#ifndef _TAHA_H
#define _TAHA_H

#include<iostream>
#include<string>
#include<windows.h>
using namespace std;

//================================================================================================

int vertexHash(char ch){
    return ch - 'A';
}

struct Node{
    float weight;
    char vertex;
    Node *next;
};

class AdjList{
    public:
        Node* head;
        AdjList(){
            head = NULL;
        }
        void insert(char vertex, float weight){
            Node *newNode = new Node;
            newNode->vertex = vertex;
            newNode->weight = weight;
            newNode->next = head;
            head = newNode;
        }
        void print(){
            Node *temp = head;
            while(temp != NULL){
                cout << "(" << temp->vertex << " , " << temp->weight << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
};

class Graph{
    public:
        AdjList *list;
        int vertices;
        Graph(int num){
            vertices = num;
            list = new AdjList[num];
        }
        void addEdge(char ch, char ch2, float weight){
            int i = vertexHash(ch);
            int j = vertexHash(ch2);
            list[i].insert(ch2, weight);
            list[j].insert(ch, weight);
        }

        void updateEdge(char ch, char ch2, float weight){
            int i = vertexHash(ch);
            Node *temp = list[i].head;
            while(temp != NULL){
                if(temp->vertex == ch2){
                    temp->weight = weight;
                    break;
                }
                temp = temp->next;
            }
            int j = vertexHash(ch2);
            temp = list[j].head;
            while(temp != NULL){
                if(temp->vertex == ch){
                    temp->weight = weight;
                    break;
                }
                temp = temp->next;
            }
        }

        void deleteEdge(char ch, char ch2){
            int i = vertexHash(ch);
            Node *temp = list[i].head;
            Node *prev = NULL;
            while(temp != NULL){
                if(temp->vertex == ch2){
                    if(prev == NULL){
                        list[i].head = temp->next;
                    }
                    else{
                        prev->next = temp->next;
                    }
                    delete temp;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
            int j = vertexHash(ch2);
            temp = list[j].head;
            prev = NULL;
            while(temp != NULL){
                if(temp->vertex == ch){
                    if(prev == NULL){
                        list[j].head = temp->next;
                    }
                    else{
                        prev->next = temp->next;
                    }
                    delete temp;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
        }
        void print(){
            for(int i = 0; i < vertices; i++){
                char ch = i + 'A';
                if(list[i].head == NULL){
                    continue;
                }
                cout << ch << ") => ";
                list[i].print();
            }
        }
};

//================================================================================================

struct Vehicles{
    string id;
    char start;
    char end;
    char current;

    Vehicles(){
        id = "";
        start = ' ';
        end = ' ';
        current = ' ';
    }

    void setVehicles(string id, char start, char end){
        this->id = id;
        this->start = start;
        this->end = end;
        this->current = start;
    }
};


void Dijkstra(Graph &g, char start, char end){
    int startVertex = vertexHash(start);
    int endVertex = vertexHash(end);
    float *distance = new float[g.vertices];
    bool *visited = new bool[g.vertices];
    char *path = new char[g.vertices];
    for(int i = 0; i < g.vertices; i++){
        distance[i] = 999999;
        visited[i] = false;
        path[i] = ' ';
    }
    distance[startVertex] = 0;
    for(int i = 0; i < g.vertices; i++){
        int minVertex = -1;
        for(int j = 0; j < g.vertices; j++){
            if(!visited[j] && (minVertex == -1 || distance[j] < distance[minVertex])){
                minVertex = j;
            }
        }
        visited[minVertex] = true;
        for(Node *temp = g.list[minVertex].head; temp != NULL; temp = temp->next){
            if(distance[minVertex] + temp->weight < distance[vertexHash(temp->vertex)]){
                distance[vertexHash(temp->vertex)] = distance[minVertex] + temp->weight;
                path[vertexHash(temp->vertex)] = minVertex + 'A';
            }
        }
    }
    cout << "Shortest Path from " << start << " to " << end << " is: ";
    cout << end;
    char temp = path[endVertex];
    while(temp != ' '){
        cout << " <- " << temp;
        temp = path[vertexHash(temp)];
    }
    cout << endl;
    cout << "Total Distance: " << distance[endVertex] << endl;
}
void moveVehicle(Graph &g, Vehicles &v){
    Dijkstra(g, v.current, v.end);
    v.current = v.end;
    cout << "Vehicle " << v.id << " has reached " << v.current << endl;
}

void simulateTraffic(Graph &g, Vehicles *v, int num){
    for(int i = 0; i < num; i++){
        moveVehicle(g, v[i]);
        Sleep(2);
    }
}

//================================================================================================


class priorityQueueNode{
    public:
        char intersection;
        int time;
};

class priorityQueue{
    priorityQueueNode *data;
    int size;
    int capacity;
    public:
        priorityQueue(int num){
            data = new priorityQueueNode[num+1];
            size = 1;
            capacity = num;
        }

        void enqueue(int time, char intersection){
            if(size == capacity){
                cout << "Queue is full" << endl;
                return;
            }
            data[size].time = time;
            data[size].intersection = intersection;
            int i = size;
            size++;
            while(i > 1){
                int parent = i/2;
                if(data[parent].time > data[i].time){
                    priorityQueueNode temp = data[parent];
                    data[parent] = data[i];
                    data[i] = temp;
                    i = parent;
                }
                else{
                    break;
                }
            }
        }

        void dequeue(){
            if(size == 1){
                cout << "Queue is empty" << endl;
                return;
            }
            data[1] = data[size-1];
            size--;
            int i = 1;
            while(i < size){
                int left = 2*i;
                int right = 2*i + 1;
                int minIndex = i;
                if(left < size && data[left].time < data[minIndex].time){
                    minIndex = left;
                }
                if(right < size && data[right].time < data[minIndex].time){
                    minIndex = right;
                }
                if(minIndex == i){
                    break;
                }
                priorityQueueNode temp = data[i];
                data[i] = data[minIndex];
                data[minIndex] = temp;
                i = minIndex;
            }
        }

        void displayQueue(){
            while(size > 1){
                cout << data[1].intersection << " Green Time " << data[1].time << "\n";
                dequeue();
            }
        }

        void print(){
            for(int i = 1; i < size; i++){
               cout << data[i].intersection << " Green Time " << data[i].time << endl;
            }
        }
};
#endif