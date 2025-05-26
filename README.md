# Traffic Simulator

This project simulates traffic flow in a city grid using C++. It models roads, traffic lights, vehicles (cars and buses), and their interactions within a grid-based map.

## 🚀 Features

✅ Object-oriented design with:
- `Vehicle`, `Car`, and `Bus` classes
- `Road` and `TrafficLight` classes
- `GridMap` to hold roads and their positions

✅ Supports:
- Adding/removing vehicles to/from roads
- Moving vehicles in directions (`North`, `South`, `East`, `West`)
- Traffic light state changes (`red`, `yellow`, `green`)
- Displaying current traffic and grid info

✅ Includes a sample simulation in `main()`.

## 🛠️ Build & Run

1️⃣ **Compile the C++ code:**

```bash
g++ -o traffic_simulator traffic_simulator.cpp
2️⃣ Run the simulation:

bash
Copier
Modifier
./traffic_simulator
📁 Project Structure
bash
Copier
Modifier
traffic_simulator.cpp  # Main program file with all classes and the simulation
⚙️ Simulation Overview
The city is represented as a 5x5 grid map.

Roads are added at specific positions.

Vehicles (cars and buses) move on roads, following traffic light rules.

The simulation shows how traffic lights change states and how vehicles respond.

🔍 Example Simulation Flow
✅ Create grid map
✅ Add roads and traffic lights
✅ Add vehicles to roads
✅ Simulate traffic light changes
✅ Move vehicles based on light states
✅ Display current traffic on roads
✅ Clear all vehicles at the end

📢 Note
The simulation logic is implemented directly in main().

Extend the simulation by adding more vehicles, roads, or custom logic!
