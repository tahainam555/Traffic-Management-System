# Smart Traffic Management System Simulator  

🚦 **Version**: 1.0  
📅 **Due Date**: December 8, 2024  

---

## 📖 Introduction  

The **Smart Traffic Management System Simulator** is a C++ project designed to model and simulate real-world traffic flow. It utilizes advanced data structures and algorithms to optimize urban traffic, resolve congestion, and handle emergencies in real-time.  

---

## 🚀 Features  

### City Traffic Network  
- Graph-based representation of intersections and roads.  
- Dynamic addition and removal of roads and intersections.  
- Visualization of the road network in text or graphical form.  

### Vehicle Routing  
- Shortest path calculation using **Dijkstra’s Algorithm**.  
- Dynamic route recalculation based on traffic conditions.  
- Vehicle tracking across the network.  

### Traffic Signal Management  
- Adjust green signal durations dynamically based on traffic density.  
- Emergency overrides for critical scenarios.  

### Congestion Monitoring  
- Real-time vehicle count tracking using **Hash Tables**.  
- Detect and resolve congestion zones with **BFS/DFS**.  

### Emergency Vehicle Handling  
- Fastest route calculation using **A* Search Algorithm**.  
- Traffic flow restoration post-emergency.  

### Accident & Road Closure Simulation  
- Dynamic handling of disruptions.  
- Re-routing and impact analysis during accidents or closures.  

---

## 📜 System Workflow  

1. **Initialization**: Load data for roads, vehicles, and signals from CSV files.  
2. **Traffic Simulation**: Dynamically route vehicles and monitor traffic flow.  
3. **Signal Management**: Adjust signals based on real-time traffic density.  
4. **Emergency Handling**: Clear paths and optimize routes for emergency vehicles.  
5. **Monitoring & Logging**: Log vehicle movements, congestion levels, and system actions.  

---

## 🛠️ Technology Stack  

- **Programming Language**: C++  
- **Data Structures**: Graphs, Priority Queue, Min-Heap, Hash Table  
- **Algorithms**: Dijkstra’s Algorithm, A* Search, BFS/DFS  

---

## 📂 Project Setup  

### Clone the Repository  
```bash  
git clone <repository_url>  
cd <repository_name>  
```  

### Compile the Code  
Use any C++ compiler (e.g., GCC):  
```bash  
g++ -o traffic_simulator main.cpp  
```  

### Run the Program  
```bash  
./traffic_simulator  
```  

### Input Files  
Ensure the following files are in the working directory:  
- `road_network.csv`  
- `vehicles.csv`  
- `traffic_signal_timings.csv`  
- `emergency_vehicles.csv`  

---

## 📊 Sample Outputs  

### Graph Visualization  
```  
Intersection A -> B (Travel Time: 5 mins)  
Intersection B -> C (Travel Time: 8 mins)  
```  

### Real-Time Traffic Updates  
```  
Congestion Alert: Intersection A -> B  
Rerouting vehicles...  
```  

---

## 📦 Deliverables  

- **Source Code**: Well-documented and modularized.  
- **Simulation Scenarios**:  
    - Normal traffic flow.  
    - Peak-hour congestion.  
    - Emergency vehicle routing.  
    - Accident or closure handling.  
- **Performance Metrics**:  
    - Average vehicle travel time.  
    - Efficiency of signal adjustments.  

---

## 🌟 Bonus Task  

Implement real-time route optimization based on changing traffic conditions using dynamic programming. Visualize the best routes and congested areas with color-coded indicators.  

---

## 👨‍💻 Contributors  

This project is developed by **Hamda Shahid , Minahil Rizwan and Muhammad Taha** under the guidance of instructors at the **National University of Computer & Emerging Sciences, Islamabad Campus**.  

---

## 📢 License  

This project is for educational purposes only and adheres to the Honor Policy of the institution.  

