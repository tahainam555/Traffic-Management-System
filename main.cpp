#include <iostream>
#include <string>
#include <fstream>
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
    int priority;
    Vehicles* next;

    Vehicles(){
        priority = 0;
        id = "";
        start = ' ';
        end = ' ';
        current = ' ';
        next = NULL;
    }

    void setVehicles(string id, char start, char end, int priority){
        this->id = id;
        this->start = start;
        this->end = end;
        this->current = start;
        this->priority = priority;
    }
};

class VehiclesPQ{
    public:
        Vehicles *head;
        Vehicles *tail;

        VehiclesPQ(){
            head = NULL;
            tail = NULL;
        }

        void enqueue(string id, char start, char end, int priority){
            Vehicles *newNode = new Vehicles;
            newNode->setVehicles(id, start, end, priority);
            if(head == NULL){
                head = newNode;
                tail = newNode;
                return;
            }
            if(priority < head->priority){
                newNode->next = head;
                head = newNode;
                return;
            }
            Vehicles *temp = head;
            while(temp->next != NULL && temp->next->priority <= priority){
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
            if(newNode->next == NULL){
                tail = newNode;
            }
        }

        Vehicles dequeue(){
            if(head == NULL){
                cout << "Queue is empty" << endl;
                return Vehicles();
            }
            Vehicles *temp = head;
            head = head->next;
            Vehicles v = *temp;
            delete temp;
            return v;
        }

        void display(){
            Vehicles *temp = head;
            while(temp != NULL){
                cout << "Vehicle ID: " << temp->id << " Start: " << temp->start << " End: " << temp->end << " Priority: " << temp->priority << endl;
                temp = temp->next;
            }
        }

        bool isEmpty(){
            return head == NULL;
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
            capacity = 27;
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
        cout << "Adjusting Traffic Signal at " << intersection << endl;
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


void dfsFindPaths(Graph &g, char current, char end, bool visited[], my_stack &pathStack, float currentCost, bool& pathFound) {
    visited[vertexHash(current)] = true;
    pathStack.push(current);

    if (current == end) {
        pathFound = true;
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
        cout << "| Cost: " << currentCost << endl;
    } else {
        Node *neighbor = g.list[vertexHash(current)].head;
        while (neighbor != NULL) {
            if (!visited[vertexHash(neighbor->vertex)]) {
                dfsFindPaths(g, neighbor->vertex, end, visited, pathStack, currentCost + neighbor->weight, pathFound);
            }
            neighbor = neighbor->next;
        }
    }

    visited[vertexHash(current)] = false;
    pathStack.pop();
}

void findAllPaths(Graph &g, char start, char end) {
    bool pathFound = false;
    bool visited[26] = {false};  
    my_stack pathStack;          

    cout << "All possible paths from " << start << " to " << end << " are:\n";
    dfsFindPaths(g, start, end, visited, pathStack, 0, pathFound); 
    if (!pathFound) {
        cout << "No path exists from " << start << " to " << end << endl;
    }
}
//================================================================================================


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
            if (table[i].path == "")
            {
                continue;
            }
            if(table[i].path[0] == ' '){
                continue;
            }
            cout << table[i].path[0] << " to " << table[i].path[1] << " " << countArray[i] << endl;
            // table[i].display();
        }
    }

    void storeData(Vehicles *vehicle, Graph &g, int num)
    {
        for (int i = 1; i < num; i++)
        {
            //cout << "vehicle " << vehicle[i].id << endl;
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
                //cout << "start " << start << " end " << end << endl;
                ss.pop();
                insert(start, end, vehicle[i].id);
            }
            start = end;
            end = vehicle[i].end;
            // ss.pop();
            //cout << "start " << start << " end " << end << endl;

            insert(start, end, vehicle[i].id);
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

//================================================================================================


struct EmergencyVehicle 
{
    string vehicleID;
    char startIntersection;
    char endIntersection;
    string priorityLevel;
    int greenTime;  

    void setVehicle(string id, char start, char end, string priority) 
    {
        vehicleID = id;
        startIntersection = start;
        endIntersection = end;
        priorityLevel = priority;

        if (priorityLevel == "High") 
        {
            greenTime = 10;  
        } 
        else if (priorityLevel == "Medium") 
        {
            greenTime = 20;  
        }
        else if (priorityLevel == "Low") 
        {
            greenTime = 30;  
        } 
        else 
        {
            greenTime = 0; 
        }
    }
};

void readEmergencyVehicles(Graph &g, EmergencyVehicle *E1, int &num)
{
    string str;
    fstream file("data/emergency_vehicles.csv");
    
    num = 0;  
    while (getline(file, str)) 
    {
        num++;
    }
    num--;  
    file.close();
    
    file.open("data/emergency_vehicles.csv");
    int i = 0;
    string id, priority;
    char start, end;
    
    while (getline(file, str)) 
    {
        if (i > 0) 
        {
            id = "";
            start = ' ';
            end = ' ';
            priority = "";
            for (int j = 0; j < str.length(); j++) 
            {
                if (str[j] == ',') {
                    if (start == ' ') 
                    {
                        start = str[j+1];
                    } else if (end == ' ') 
                    {
                        end = str[j+1];
                    } else 
                    {
                        priority = str.substr(j+1);  
                    }
                }
                else 
                {
                    id += str[j];  
                }
            }

            E1[i].setVehicle(id, start, end, priority);
        }
        i++;
    }
    file.close();
}

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
        TrafficSignal* signals;
        int signalCount;
        my_stack S1;
    
    public:
        emergencyRouting(Graph* G1, TrafficSignal* TS, int num)
        {
            graph = G1;
            distance = new float[num];
            visited = new bool[num];
            previous = new char[num];
            P1 = new priorityQ(num);
            signals = TS;
            signalCount = num;

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

        void overrideSignals(char intersection)
        {
            int index = vertexHash(intersection);
            if (index < signalCount)
            {
                signals[index].isGreen = true;
                signals[index].greenTime = 999;
                cout<<"Traffic signal at "<<intersection<<" overridden"<<endl;
            }
        }

        void restoreSignals()
        {
            while (!S1.isEmpty())
            {
                char intersection = S1.getTop();
                S1.pop();
                int index = vertexHash(intersection);
                if (index < signalCount)
                {
                    signals[index].isGreen = false;
                    signals[index].greenTime = 0;
                    cout<<"Traffic signal at "<<intersection<<" restored"<<endl;
                }

            }
        }

        void ASearch(char start, char end) {
            cout << "Emergency vehicle is being routed..." << endl;

            int startVertex = vertexHash(start);
            int endVertex = vertexHash(end);

            for (int i = 0; i < graph->vertices; i++) {
                distance[i] = 99999;
                visited[i] = false;
                previous[i] = ' ';
            }
            distance[startVertex] = 0;
            P1->enqueue(0, start);

            bool pathFound = false;

            while (!P1->isEmpty()) {
                char current = P1->peekIntersection();
                P1->dequeue();

                int currVertex = vertexHash(current);
                if (visited[currVertex]) {
                    continue;
                }
                visited[currVertex] = true;

                if (current == end) {
                    pathFound = true;
                    break;
                }

                Node *neighbour = graph->list[currVertex].head;
                while (neighbour != NULL) {
                    int neighborVertex = vertexHash(neighbour->vertex);
                    if (visited[neighborVertex]) {
                        neighbour = neighbour->next;
                        continue;
                    }

                    float newCost = distance[currVertex] + neighbour->weight;
                    float heuristic = abs(neighborVertex - endVertex); // Heuristic (Manhattan distance)
                    float totalCost = newCost + heuristic;

                    if (newCost < distance[neighborVertex]) {
                        distance[neighborVertex] = newCost;
                        previous[neighborVertex] = current;
                        P1->enqueue(totalCost, neighbour->vertex);
                    }

                    neighbour = neighbour->next;
                }
            }

            if (!pathFound) {
                cout << "No path exists from " << start << " to " << end << "." << endl;
                return; 
            }

            // Construct the path
            char current = end;
            // for(int i=0; i<graph->vertices; i++)
            // {
            //     signals[i].isGreen = false;
            // }
            while (current != start) {
                overrideSignals(current);  
                S1.push(current);
                current = previous[vertexHash(current)];
            }
            overrideSignals(start);
            S1.push(start);

            printPath(start, end);

            restoreSignals(); 
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

void simulateTraffic2(Graph &g, Vehicles *v,VehiclesPQ& vpq, int num, TrafficSignal *signals, priorityQueue &q, emergencyRouting E1) {
    trafficSignal(q, signals, v, num);
    int i=0;
    int j=num-1;
    int count=0;
    while(i!=j){
        if(count%2==0){
            cout << "===============VEHICLE " << count+1 << "==================" << endl;
            cout << "Vehicle " << v[i+1].id << " is moving from " << v[i+1].current << " to " << v[i+1].end << endl;
            moveVehicle2(g, v[i+1], signals);
            i++;
        }
        else{
            cout << "===============VEHICLE " << count+1 << "==================" << endl;
            cout << "Vehicle " << v[j].id << " is moving from " << v[j].current << " to " << v[j].end << endl;
            if(v[j].priority == 0||v[j].priority == 5){
                cout << "Vehicle " << v[j].id << " is an emergency vehicle" << endl;
                Sleep(500);
                Beep(523, 500);
                E1.ASearch(v[j].current, v[j].end);
            }
            else{
                moveVehicle2(g, v[j], signals);
            }
            j--;
        }
        count++;
        Sleep(1000);
    }
    // for (int i = 0, j=num; i < num-1; i++) {
    //     cout << "===============VEHICLE " << i+1 << "==================" << endl;
    //     cout << "Vehicle " << v[i+1].id << " is moving from " << v[i+1].current << " to " << v[i+1].end << endl;
    //     moveVehicle2(g, v[i+1], signals);
    //     if(v[i+1].priority == 0){
    //         E1.ASearch(v[i+1].current, v[i+1].end);
    //     }
    //     Sleep(1000);
    // }
}


int main()
{

    int num = 0;
    string str;
    fstream file("data/road_network.csv");
    while (getline(file, str))
    {
        num++;
    }
    num--;
//    cout << num << endl;
    file.close();

    Graph g(num);
    fstream file2("data/road_network.csv");
    int i = 0;
    while (getline(file2, str))
    {
        if (i > 0)
        {
            char start = str[0];
            char end = str[2];
            float weight = stof(str.substr(4));
            g.addEdge(start, end, weight);
        }
        i++;
    }
    file2.close();

    file.open("data/traffic_signals.csv");
    num = 0;
    while (getline(file, str))
    {
        num++;
    }
    //cout << num << endl;
    file.close();
    priorityQueue pq(num);
    TrafficSignal *signals = new TrafficSignal[num];
    file2.open("data/traffic_signals.csv");
    i = 0;
    while (getline(file2, str))
    {
        if (i > 0)
        {
            char intersection = str[0];
            int time = stoi(str.substr(2));
            pq.enqueue(time, intersection);
            signals[i-1].setTrafficSignal(intersection, time);
        }
        i++;
    }
    file2.close();

    file.open("data/vehicles.csv");
    num = 0;
    while (getline(file, str))
    {
        num++;
    }
    //cout << "this " << num << endl;
    int numOfVehicles = num;
    int num2 = num;
    file.close();
    VehiclesPQ vpq;
    Vehicles *v = new Vehicles[num+50];
    int vehCount = 0;
    file2.open("data/vehicles.csv");
    i = 0;
    string id = "";
    char start = ' ';
    char end = ' ';
    while (getline(file2, str))
    {
        if (i > 0)
        {
            id = "";
            start = ' ';
            end = ' ';
            for (int j = 0; j < str.length(); j++)
            {
                if (str[j] == ',')
                {
                    start = str[j + 1];
                    end = str[j + 3];
                    break;
                }
                id += str[j];
            }
        }
        i++;
        //        cout << id << " " << start << " " << end << endl;
        v[vehCount++].setVehicles(id, start, end, 10);
        //vehCount++;
        //vpq.enqueue(id, start, end, 10);
    }
    file2.close();

    file.open("data/emergency_vehicles.csv");
    num = 0;
    while (getline(file, str))
    {
        num++;
    }
    file.close();
    id = "";
    start = ' ';
    end = ' ';
    string priority = "";
    file2.open("data/emergency_vehicles.csv");
    while(getline(file2, str)){
        if(i > 0){
            id = "";
            start = ' ';
            end = ' ';
            priority = "";
            for(int j = 0; j < str.length(); j++){
                if(str[j] == ','){
                    if(start == ' '){
                        start = str[j+1];
                    }
                    else if(end == ' '){
                        end = str[j+1];
                    }
                    else{
                        priority = str.substr(j+1);
                    }
                }
                else if(start == ' '){
                    id += str[j];
                }
            }
            if(id == ""){
                break;
            }
            //cout << id << " " << start << " " << end << " " << priority << endl;
            if(priority == "High"){
                vpq.enqueue(id, start, end, 0);
                v[vehCount++].setVehicles(id, start, end, 0);
            }
            else if(priority == "Medium"){
                vpq.enqueue(id, start, end, 5);
                v[vehCount++].setVehicles(id, start, end, 5);
            }
        }
    i++;
    }
    file2.close();


    file.open("data/road_closures.csv");
    num = 0;
    while (getline(file, str))
    {
        num++;
    }
    //cout << num << endl;
    file.close();
    myRoads *r = new myRoads[num+5];
    file2.open("data/road_closures.csv");
    i = 0;
    start = ' ';
    end = ' ';
    string status = "";
    while (getline(file2, str))
    {
        if (i > 0 && i < 24)
        {
            start = str[0];
            end = str[2];
            status = str.substr(4);
            if (status == "Blocked")
            {
                r[i - 1].setRoads(start, end, true);
                blockRoad(g, start, end);
            }
            else
            {
                r[i - 1].setRoads(start, end, false);
            }
//            cout << start << " " << end << " " << status << endl;
            
        }
        i++;
    }
    file2.close();

    int counter = 23;

    emergencyRouting E1(&g, signals, num);

    char ch;
    while(1){
        cout << "=============WELCOME TO THE ROAD NETWORK=============" << endl;
        cout << "1: DISPLAY CITY ROAD NETWORK" << endl;
        cout << "2: SHORTEST PATH" << endl;
        cout << "3: TRAFFIC SIGNAL STATUS" << endl;
        cout << "4: CONGESTION STATUS" << endl;
        cout << "5: DISPLAY BLOCKED ROADS" << endl;
        cout << "6: HANDLE EMERGENCY VEHICLE ROUTING" << endl;
        cout << "7: SIMULATE VEHICLE ROUTING" << endl;
        cout << "8: UNBLOCK ROAD" << endl;
        cout << "9: SIMULATE TRAFFIC" << endl;
        cout << "0: EXIT" << endl;
        cout << "====================================================" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        if (ch == '1')
        {
            cout << "=================CITY ROAD NETWORK==================" << endl;
            g.print();
        }
        else if (ch == '2')
        {
            cout << "=================SHORTEST PATH==================" << endl;
            char strt, en;
            cout << "Enter start intersection: ";
            cin >> strt;
            cout << "Enter end intersection: ";
            cin >> en;
            cout << "Shortest path from " << strt << " to " << en << " is: ";
            my_stack s = Dijkstra(g, strt, en);
            cout << endl;
            //simulateTraffic2(g, v, num2, signals, pq);
        }
        else if (ch == '3')
        {
            cout << "=================TRAFFIC SIGNAL STATUS==================" << endl;
            pq.displayQueue();
        }
        else if (ch == '4')
        {
            cout << "=================CONGESTION STATUS==================" << endl;
            HashTable h;
            h.storeData(v, g, num2);
            // cout << "STORED" << endl;
            h.print();
        }
        else if (ch == '5')
        {
            cout << "=================DISPLAY BLOCKED ROADS==================" << endl;
            blockageStatus(g, r, counter);
            char strt, en;
            cout << "Enter start intersection: ";
            cin >> strt;
            cout << "Enter end intersection: ";
            cin >> en;
            // cout << "Shortest path from " << strt << " to " << en << " is: ";
            // my_stack s = Dijkstra(g, strt, en);
            // cout << endl;
            if(counter == num+5){
                cout << "All roads are blocked" << endl;
                continue;
            }
            if(!g.isEdge(strt, en)){
                cout << "Road between " << strt << " and " << en << " does not exist" << endl;
                continue;
            }

            blockRoads(g, r, strt, en, counter);
            r[counter++].setRoads(strt, en, true);
            blockageStatus(g, r, counter);
        }
        else if (ch == '6')
        {
            cout << "=================EMERGENCY ROUTE==================" << endl;
            char start, end;
            cout << "Enter start intersection: ";
            cin >> start;
            cout << "Enter end intersection: ";
            cin >> end;

            
            E1.ASearch(start, end);
        }
        else if (ch == '7')
        {
            cout << "============SIMULATING VEHICLE ROUTING================" << endl;
            char start = '\0', end = '\0';
            cout << "Enter start intersection: ";
            cin >> start;
            cout << "Enter end intersection: ";
            cin >> end;
            //simulation(g, start, end);
            findAllPaths(g, start, end);
        }
        else if (ch == '8')
        {
            cout << "=================UNBLOCK ROAD==================" << endl;
            char strt, en;
            cout << "Enter start intersection: ";
            cin >> strt;
            cout << "Enter end intersection: ";
            cin >> en;
            for(int i = 0; i < counter; i++){
                if(r[i].start == strt && r[i].end == en){
                    unblockRoad(g, r[i], strt, en);
                    cout << "Road between " << strt << " and " << en << " is unblocked" << endl;
                    counter--;
                    break;
                }
            }
        }
        else if (ch == '9')
        {
            simulateTraffic2(g, v, vpq,  vehCount, signals, pq, E1);
        }
        else if (ch == '0')
        {
            cout << "Exiting..." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }


}