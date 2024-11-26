#ifndef _TAHA_H
#define _TAHA_H

#include<iostream>
#include<string>
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
    AdjList *list;
    int vertices;
    public:
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

//================================================================================================


#endif