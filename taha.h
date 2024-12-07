#ifndef _TAHA_H
#define _TAHA_H

#include<iostream>
#include<string>
#include<windows.h>
using namespace std;


//================================================================================================

class StackNode{
    public:
        char data;
        StackNode *next;
};

class my_stack{
    public:
        StackNode *top;
        my_stack(){
            top = NULL;
        }
        void push(char ch){
            StackNode *newNode = new StackNode;
            newNode->data = ch;
            newNode->next = top;
            top = newNode;
        }
        void pop(){
            if(top == NULL){
                cout << "Stack is empty" << endl;
                return;
            }
            StackNode *temp = top;
            top = top->next;
            delete temp;
        }
        char getTop(){
            if(top == NULL){
                cout << "Stack is empty" << endl;
                return ' ';
            }
            return top->data;
        }
        bool isEmpty(){
            return top == NULL;
        }
};



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

        bool isEdge(char ch, char ch2){
            int i = vertexHash(ch);
            Node *temp = list[i].head;
            while(temp != NULL){
                if(temp->vertex == ch2){
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }

        float getWeight(char ch, char ch2){
            int i = vertexHash(ch);
            Node *temp = list[i].head;
            while(temp != NULL){
                if(temp->vertex == ch2){
                    return temp->weight;
                }
                temp = temp->next;
            }
            return -1;
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


my_stack Dijkstra(Graph &g, char start, char end){
    my_stack s;
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
    if (distance[endVertex] == 999999) {
        cout << "No path exists" << endl;
        s.top = NULL;
        return s;
    }
    cout << end;
    char temp = path[endVertex];
    while(temp != ' '){
        cout << " <- " << temp;
        s.push(temp);
        temp = path[vertexHash(temp)];
    }
    cout << endl;
    cout << "Total Distance: " << distance[endVertex] << endl;
    return s;
}


void moveVehicle(Graph &g, Vehicles &v){
    if(v.current == v.end){
        return;
    }
    my_stack s = Dijkstra(g, v.current, v.end);
    if(s.isEmpty()){
        cout << "Can't move vehicle " << v.id << " from " << v.current << " to " << v.end << endl;
        return;
    }
    v.current = v.end;
    cout << "Vehicle " << v.id << " has reached " << v.current << endl;
}

void simulateTraffic(Graph &g, Vehicles *v, int num){
    for(int i = 1; i < num; i++){
        cout << "===============VEHICLE " << i << "==================" <<  endl;
        cout << "Vehicle " << v[i].id << " is moving from " << v[i].current << " to " << v[i].end << endl;
        moveVehicle(g, v[i]);
        Sleep(1000);
    }
}

//================================================================================================

void resetVehileCount(int *vehicleCount, int num){
    for(int i = 0; i < num; i++){
        vehicleCount[i] = 0;
    }
}

void updateVehicleCount(int *vehicleCount, Vehicles *v, int num){
    resetVehileCount(vehicleCount, num);
    for(int i = 0; i < num; i++){
        int index = vertexHash(v[i].current);
        vehicleCount[index]++;
    }
}

int vehicleDensity(char intersection, Vehicles *v, int num){
    int count = 0;
    for(int i = 0; i < num; i++){
        if(v[i].current == intersection){
            count++;
        }
    }
    return count;
}

//================================================================================================


class priorityQueueNode{
    public:
        char intersection;
        int density;
};

class priorityQueue{
    public:
        priorityQueueNode *data;
        int size;
        int capacity;
        priorityQueue(int num){
            data = new priorityQueueNode[num+1];
            size = 1;
            capacity = num;
        }

        void enqueue(int density, char intersection){
            if(size == capacity){
                cout << "Queue is full" << endl;
                return;
            }
            data[size].density = density;
            data[size].intersection = intersection;
            int i = size;
            size++;
            while(i > 1){
                int parent = i/2;
                if(data[parent].density > data[i].density){
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
                if(left < size && data[left].density < data[minIndex].density){
                    minIndex = left;
                }
                if(right < size && data[right].density < data[minIndex].density){
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
            for(int i = 1; i < size; i++){
                cout << data[i].intersection << " : " << data[i].density << endl;
            }
        }
};

struct TrafficSignal{
    char intersection;
    int greenTime; 
    bool isGreen;

    TrafficSignal(){
        intersection = ' ';
        greenTime = 0;
        isGreen = true;
    }

    void setTrafficSignal(char intersection, int time){
        this->intersection = intersection;
        greenTime = time;
    }

};

void trafficSignal(priorityQueue &q, TrafficSignal *t,Vehicles* v, int num){
    for (int i = 0; i < num; i++) {
        int density = vehicleDensity(t[i].intersection, v, num);
        q.enqueue(density, t[i].intersection);
    }

    while (q.size > 1) {
        char intersection = q.data[1].intersection;
        int density = q.data[1].density;
        cout << "Adjusting Traffic Signal at " << intersection << " for " << density << " vehicles" << endl;
        t[intersection - 'A'].greenTime = density; 
        t[intersection - 'A'].isGreen = true; 
        q.dequeue();
    }
}

void moveVehicle2(Graph &g, Vehicles &v, TrafficSignal *signals) {
    if (v.current == v.end) {
        return;
    }

    if (!signals[vertexHash(v.current)].isGreen) {
        cout << "Vehicle " << v.id << " is waiting at red signal at " << v.current << endl;
        Sleep(1000);
        signals[vertexHash(v.current)].isGreen = true;
    }

    my_stack s = Dijkstra(g, v.current, v.end);
    if(s.isEmpty()){
        cout << "Can't move vehicle " << v.id << " from " << v.current << " to " << v.end << endl;
        return;
    }
    cout << "Vehicle " << v.id << " is moving from " << s.getTop() << " to " << v.end << endl;
    while(!s.isEmpty()){
        v.current = s.getTop();
        s.pop();
        cout << "Vehicle " << v.id << " has reached " << v.current << endl;
        if(s.isEmpty()){
            break;
        }
        Sleep(g.getWeight(v.current, s.getTop()) * 100);
    //moveVehicle2(g, v, signals);
    }
    Sleep(g.getWeight(v.current, v.end) * 100);
    cout << "Vehicle " << v.id << " has reached " << v.end << endl;
}

void simulateTraffic2(Graph &g, Vehicles *v, int num, TrafficSignal *signals, priorityQueue &q) {
    trafficSignal(q, signals, v, num);
    for (int i = 0; i < num-1; i++) {
        cout << "===============VEHICLE " << i+1 << "==================" << endl;
        cout << "Vehicle " << v[i+1].id << " is moving from " << v[i+1].current << " to " << v[i+1].end << endl;
        moveVehicle2(g, v[i+1], signals);
        Sleep(1000);
    }
}

//================================================================================================

struct myRoads{
    char start;
    char end;
    bool isBlocked;

    myRoads(){
        start = ' ';
        end = ' ';
        isBlocked = false;
    }

    void setRoads(char start, char end, bool status){
        this->start = start;
        this->end = end;
        isBlocked = status;
    }
};

void blockageStatus(Graph& g, myRoads *r, int num){
    for(int i = 0; i < num; i++){
        if(r[i].isBlocked){
            cout << "Road between " << r[i].start << " and " << r[i].end << " is blocked" << endl;
            g.deleteEdge(r[i].start, r[i].end);
            g.deleteEdge(r[i].end, r[i].start);
        }
    }

}

// If user wants to block the road
void blockRoads(Graph& g, myRoads *r, char start, char end, int num){
    for(int i = 0; i < num; i++){
        if(r[i].start == start && r[i].end == end){
            r[i].isBlocked = true;
            g.deleteEdge(start, end);
            g.deleteEdge(end, start);
            //cout << "Road between " << start << " and " << end << " is blocked" << endl;
            break;
        }
    }
}

void blockRoad(Graph& g, char start, char end){
    g.deleteEdge(start, end);
    g.deleteEdge(end, start);
}

void unblockRoad(Graph& g, myRoads r, char start, char end){
    r.isBlocked = false;
    g.addEdge(start, end, 1);
    g.addEdge(end, start, 1);
}

//================================================================================================


void dfsFindPaths(Graph &g, char current, char end, bool visited[], my_stack &pathStack) {
    visited[vertexHash(current)] = true;
    pathStack.push(current);

    if (current == end) {
        cout << "Path: ";
        my_stack tempStack;

        while (!pathStack.isEmpty()) {
            char top = pathStack.getTop();
            tempStack.push(top);
            pathStack.pop();
        }
        while (!tempStack.isEmpty()) {
            char top = tempStack.getTop();
            cout << top << " ";
            pathStack.push(top); 
            tempStack.pop();
        }
        cout << endl;
    } else {
        Node *neighbor = g.list[vertexHash(current)].head;
        while (neighbor != NULL) {
            if (!visited[vertexHash(neighbor->vertex)]) {
                dfsFindPaths(g, neighbor->vertex, end, visited, pathStack);
            }
            neighbor = neighbor->next;
        }
    }

    visited[vertexHash(current)] = false;
    pathStack.pop();
}

void findAllPaths(Graph &g, char start, char end) {
    bool visited[26] = {false}; 
    my_stack pathStack;                 
    cout << "All possible paths from " << start << " to " << end << " are:\n";
    dfsFindPaths(g, start, end, visited, pathStack);
}

#endif