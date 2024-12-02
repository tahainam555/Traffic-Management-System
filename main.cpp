#include <iostream>
#include <string>
#include <fstream>
#include "taha.h"
#include "minahil.h"
#include "hamda.h"
using namespace std;

int main()
{

    int num=0;
    string str;
    fstream file("data/road_network.csv");
    while (getline(file, str))
    {
        num++;
    }
    num--;
    cout << num << endl;
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
    cout << num << endl;
    file.close();
    priorityQueue pq(num);
    file2.open("data/traffic_signals.csv");
    i = 0;
    while (getline(file2, str))
    {
        if (i > 0)
        {
            char intersection = str[0];
            int time = stoi(str.substr(2));
            pq.enqueue(time, intersection);
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
    cout << "this " << num << endl;
    file.close();
    Vehicles *v = new Vehicles[num];
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
        v[i - 1].setVehicles(id, start, end);
    }

    char ch;
    cout << "=============WELCOME TO THE ROAD NETWORK=============" << endl;
    cout << "1: DISPLAY CITY ROAD NETWORK" << endl;
    cout << "2: SIMULATE TRAFFIC" << endl;
    cout << "3: TRAFFIC SIGNAL STATUS" << endl;
    cout << "4: CONGESTION STATUS" << endl;
    cout << "5: DISPLAY BLOCKED ROADS" << endl;
    cout << "6: HANDLE EMERGENCY VEHICLE ROUTING" << endl;
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
        cout << "=================TRAFFIC SIMULATION==================" << endl;
        simulateTraffic(g, v, num);
    }
    else if (ch == '3')
    {
        cout << "=================TRAFFIC SIGNAL STATUS==================" << endl;
        pq.displayQueue();
    }
    else if (ch == '4')
    {
        cout << "=================CONGESTION STATUS==================" << endl;
        HashTable h(num);
        h.storeData(v, g);
        cout << "STORED" << endl;
        h.print();
    }
    else if(ch == '5'){
        cout << "=================DISPLAY BLOCKED ROADS==================" << endl;
    }
    else if (ch == '6')
    {
        cout << "=================EMERGENCY ROUTE==================" << endl;
        char start, end;
        cout << "Enter start intersection: ";
        cin >> start;
        cout << "Enter end intersection: ";
        cin >> end;

        emergencyRouting E1(&g, num);
        E1.ASearch(start, end);
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}