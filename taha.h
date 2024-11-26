#ifndef _TAHA_H
#define _TAHA_H

#include<iostream>
#include<string>
using namespace std;

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


#endif