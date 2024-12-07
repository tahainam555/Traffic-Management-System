#include <iostream>
#include <string>
#include <fstream>
#include "taha.h"
#include "minahil.h"
#include "hamda.h"
using namespace std;

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
            h.storeData(v, g);
            // cout << "STORED" << endl;
            h.print();
        }
        else if (ch == '5')
        {
            cout << "=================DISPLAY BLOCKED ROADS==================" << endl;
            blockageStatus(g, r, num);
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

            blockRoads(g, r, strt, en, num);
            r[counter++].setRoads(strt, en, true);
            blockageStatus(g, r, num);
        }
        else if (ch == '6')
        {
            cout << "=================EMERGENCY ROUTE==================" << endl;
            char start, end;
            cout << "Enter start intersection: ";
            cin >> start;
            cout << "Enter end intersection: ";
            cin >> end;

            emergencyRouting E1(&g, signals, num);
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
            for(int i = 0; i < num; i++){
                if(r[i].start == strt && r[i].end == en){
                    unblockRoad(g, r[i], strt, en);
                    break;
                }
            }
        }
        else if (ch == '9')
        {
            simulateTraffic2(g, v, num2, signals, pq);
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