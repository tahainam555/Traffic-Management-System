#include<iostream>
#include<string>
#include<fstream>
#include "taha.h"
using namespace std;

int main(){
    Graph g(5);
    g.addEdge('A', 'B', 1);
    g.addEdge('A', 'C', 2);
    g.addEdge('B', 'D', 3);
    g.addEdge('C', 'E', 4);
    g.addEdge('D', 'E', 5);
}