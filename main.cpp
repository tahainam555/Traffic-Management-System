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
    
    
    char ch;
    cout << "=============WELCOME TO THE ROAD NETWORK=============" << endl;
    cout << "1: DISPLAY CITY ROAD NETWORK" << endl;
    cout << "2: FIND SHORTEST PATH" << endl;
    cout << "3: EXIT" << endl;
    cout << "====================================================" << endl;
    cout << "Enter your choice: ";
    cin >> ch;
    if(ch == '1'){
        g.print();
    }
    else if(ch == '2'){
        
    }
    else if(ch == '3'){
        return 0;
    }
    else{
        cout << "Invalid choice" << endl;
    }
}