#include<iostream>
#include<string>
#include<fstream>
#include "taha.h"
using namespace std;

int main(){
    
    int num;
    string str;
    fstream file("data/road_network.csv");
    while(getline(file, str)){
        num++;
    }
    num--;
    cout << num << endl;
    file.close();

    Graph g(num);              
    fstream file2("data/road_network.csv");
    int i=0;
    while(getline(file2, str)){
        if(i>0){    
            char start = str[0];
            char end = str[2];
            float weight = stof(str.substr(4));
            g.addEdge(start, end, weight);
        }
        i++;
    }
    file2.close();

    file.open("data/traffic_signals.csv");
    num=0;
    while(getline(file, str)){
        num++;
    }
    cout << num << endl;
    file.close();
    priorityQueue pq(num);
    file2.open("data/traffic_signals.csv");
    i=0;
    while(getline(file2, str)){
        if(i>0){    
            char intersection = str[0];
            int time = stoi(str.substr(2));
            pq.enqueue(time, intersection);
        }
        i++;
    }
    
    
    char ch;
    cout << "=============WELCOME TO THE ROAD NETWORK=============" << endl;
    cout << "1: DISPLAY CITY ROAD NETWORK" << endl;
    cout << "2: FIND SHORTEST PATH" << endl;
    cout << "3: TRAFFIC SIGNAL STATUS" << endl;
    cout << "====================================================" << endl;
    cout << "Enter your choice: ";
    cin >> ch;
    if(ch == '1'){
        cout << "=================CITY ROAD NETWORK==================" << endl;
        g.print();
    }
    else if(ch == '2'){
        
    }
    else if(ch == '3'){
        cout << "=================TRAFFIC SIGNAL STATUS==================" << endl;
        pq.print();
    }
    else{
        cout << "Invalid choice" << endl;
    }
}