#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace ::std;

// Forward declaration
class Road;
//forward declaration
class GridMap;

class Vehicle
{
protected:
    string id;
    int speed;
    string direction;
    // position on the road & reference to the place
    int x,y ;
    GridMap* map;

public:
    Vehicle(string id, int speed, string direction )
        : id(id), speed(speed), direction(direction) ,x(0),y(0),map(nullptr){}
    Vehicle(string id, int speed, string direction ,int x, int y, GridMap* map)
        : id(id), speed(speed), direction(direction) ,x(x),y(y),map(map){}
    virtual void move() ;
     //{cout << "Vehicle with id " << id << " moved with a speed " << speed << " in " << direction << " direction." << endl;}
    virtual void stop()
    {
        cout << "Vehicle with id " << id << " has stopped." << endl;
    }
    virtual string getid(){
        return id;
    }
    void setMap(GridMap* map) {
        this->map = map;
    }
    virtual ~Vehicle() {}
};

class Car : public Vehicle
{
private:
    int passengerCapacity;

public:
     Car(string id, int speed, string direction, int capacity)
        : Vehicle(id, speed, direction), passengerCapacity(capacity) {}
    Car(string id, int speed, string direction, int capacity,int x,int y,GridMap* map)
        : Vehicle(id, speed, direction, x ,y ,map), passengerCapacity(capacity) {}
    void move() override
    {
        cout << "Car with " << id << " with capacity " << passengerCapacity << " is driving at speed " << speed << " in " << direction << " direction." << endl;
    }
    void honk() {
        cout << "Car with " << id << " is honking!" << endl;
    }
};

class Bus : public Vehicle
{
private:
    int passengerCapacity;

public:
    Bus(string id, int speed, string direction, int capacity)
        : Vehicle(id, speed, direction), passengerCapacity(capacity) {}
    Bus(string id, int speed, string direction, int capacity,int x,int y,GridMap* map)
        : Vehicle(id, speed, direction,x,y,map), passengerCapacity(capacity) {}
    void move() override
    {
        cout << "Bus with " << id << " with capacity " << passengerCapacity << " is driving at speed " << speed << " in " << direction << " direction." << endl;
    }
    void openDoors() {
        cout << "Bus with " << id << " is opening doors!" << endl;
    }
};

class TrafficLight
{
private:
    string location;
    string state; // "red", "yellow", "green"

public:
    TrafficLight(string location, string initialState = "red")
        : location(location), state(initialState) {}
    
    void changeState()
    {
        if (state == "red")
            state = "green";
        else if (state == "green")
            state = "yellow";
        else if (state == "yellow")
            state = "red";
        
        cout << "Traffic light at " << location << " changed to " << state << endl;
    }
    
    string getState()
    {
        return state;
    }
};

class Road
{
protected:
    string roadId;
    int length;
    int lanes;
    vector<Vehicle*> vehicles; // Vector to store vehicles on the road
    TrafficLight* trafficLight; // Traffic light at the end of the road

public:
    Road(string roadId, int length, int lanes)
        : roadId(roadId), length(length), lanes(lanes), trafficLight(nullptr) {}
    
    void addTrafficLight(TrafficLight* light)
    {
        trafficLight = light;
        cout << "Traffic light has been added to the road with id " << roadId << endl;
    }
    
    void addVehicle(Vehicle* vehicle)
    {
        vehicles.push_back(vehicle);
        cout << "Vehicle with id " << vehicle->getid() << " has been added to the road with id " << roadId << endl;
    }
    
    void removeVehicle(Vehicle* vehicle)
    {
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it)
        {
            if (*it == vehicle)
            {
                vehicles.erase(it);
                cout << "Vehicle with id " << vehicle->getid() << " has been removed from the road with id " << roadId << endl;
                return;
            }
        }
        cout << "Vehicle with id " << vehicle->getid() << " is not found on the road with id " << roadId << endl;
    }
    
    void countVehicles()
    {
        cout << "Number of vehicles on the road with id " << roadId << ": " << vehicles.size() << endl;
    }
    
    void displayVehicles()
    {
        cout << "There are " << vehicles.size() 
            << " vehicles on the road with id " << roadId 
            << " and the vehicles are: " << endl;

        for (auto vehicle : vehicles)
        {
            cout << "Vehicle with id " << vehicle->getid() << endl;
        }
    }
    
    void clearVehicles()
    {
        vehicles.clear();
        cout << "All vehicles have been removed from the road with id " << roadId << endl;
    }
    
    string getId() {
        return roadId;
    }
};

class GridMap
{
private:
    int width;
    int height;
    map<pair<int, int>, Road*> roads; // Map to store roads at specific grid coordinates

public:
    GridMap(int width, int height)
        : width(width), height(height) {}
    
    void addRoad(int x, int y, Road* road)
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            roads[make_pair(x, y)] = road;
            cout << "Road with id " << road->getId() << " has been added to the grid at position (" << x << ", " << y << ")" << endl;
        }
        else
        {
            cout << "Invalid grid position (" << x << ", " << y << ")" << endl;
        }
    }
    
    Road* getRoadAt(int x, int y)
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            auto it = roads.find(make_pair(x, y));
            if (it != roads.end())
            {
                return it->second;
            }
        }
        cout << "No road found at position (" << x << ", " << y << ")" << endl;
        return nullptr;
    }
    
    void displayGridInfo()
    {
        cout << "Grid Map Info:" << endl;
        cout << "Width: " << width << ", Height: " << height << endl;
        cout << "Number of roads on the grid: " << roads.size() << endl;
        
        for (const auto& roadPair : roads)
        {
            cout << "Road at position (" << roadPair.first.first << ", " << roadPair.first.second 
                 << "): Road ID " << roadPair.second->getId() << endl;
        }
    }
};
void Vehicle::move()
{
     if (!map)
    {
        cout << "No map assigned to vehicle " << id << ". Cannot move." << endl;
        return;
    }
    int newX = x;
    int newY = y;
    if (direction == "North")
        newY -= speed;
    else if (direction == "South")
        newY += speed;
    else if (direction == "East")
        newX += speed;
    else if (direction == "West")
        newX -= speed;
    
    Road* nextRoad = map->getRoadAt(newX, newY);
    if (nextRoad){
         Road* currentRoad = map->getRoadAt(x, y);
        if (currentRoad) currentRoad->removeVehicle(this);
        nextRoad->addVehicle(this);
        x = newX;
        y = newY;
        cout << "Vehicle with id " << id << " moved to position (" << newX << ", " << newY << ") on the map." << endl;
    } else
    {
        cout << "Vehicle with id " << id << " cannot move to position (" << newX << ", " << newY << ")." << endl;
    }
}

int main()
{
    cout << "=== TRAFFIC SIMULATION SYSTEM INITIALIZATION ===" << endl;
    
    // Create a grid map of the city
    cout << "\n[SYSTEM] Creating city grid map (5x5)..." << endl;
    GridMap cityMap(5, 5);
    
    // Create roads
    cout << "\n[SYSTEM] Creating roads..." << endl;
    Road* mainStreet = new Road("Main_Street", 200, 2);
    Road* broadwayAve = new Road("Broadway_Ave", 150, 3);
    Road* parkRoad = new Road("Park_Road", 100, 1);
    
    // Add roads to the grid map
    cout << "\n[SYSTEM] Adding roads to grid map..." << endl;
    cityMap.addRoad(0, 0, mainStreet);
    cityMap.addRoad(0, 1, broadwayAve);
    cityMap.addRoad(1, 0, parkRoad);
    
    // Create traffic lights
    cout << "\n[SYSTEM] Installing traffic lights..." << endl;
    TrafficLight* mainIntersection = new TrafficLight("Main & Broadway");
    TrafficLight* parkIntersection = new TrafficLight("Park & Main", "green");
    
    // Add traffic lights to roads
    mainStreet->addTrafficLight(mainIntersection);
    parkRoad->addTrafficLight(parkIntersection);
    
    // Create vehicles
    cout << "\n[SYSTEM] Vehicles entering the system..." << endl;
    Car* sedan = new Car("Sedan_01", 60, "East", 5);
    Bus* cityBus = new Bus("Bus_01", 40, "North", 30);
    Car* taxi = new Car("Taxi_01", 55, "West", 4);
    
    // Display grid information
    cout << "\n=== CITY GRID INFORMATION ===" << endl;
    cityMap.displayGridInfo();
    
    // Start simulation
    cout << "\n=== TRAFFIC SIMULATION BEGINS ===" << endl;
    cout << "\n[TIME: 08:00] Morning rush hour traffic..." << endl;
    
    // First scenario - Main Street
    cout << "\n[LOCATION: Main Street Intersection]" << endl;
    cout << "Traffic light state: " << mainIntersection->getState() << endl;
    mainStreet->addVehicle(sedan);
    
    if (mainIntersection->getState() == "red") {
        cout << "Sedan_01 is waiting at the traffic light." << endl;
        cout << "Traffic is building up..." << endl;
        
        cout << "\n[TIME: 08:05] Traffic light changing..." << endl;
        mainIntersection->changeState();
        cout << "Traffic light state: " << mainIntersection->getState() << endl;
        
        cout << "Sedan_01 is now moving through the intersection." << endl;
        sedan->move();
    }
    
    // Second scenario - Park Road
    cout << "\n[LOCATION: Park Road Intersection]" << endl;
    cout << "Traffic light state: " << parkIntersection->getState() << endl;
    parkRoad->addVehicle(cityBus);
    
    if (parkIntersection->getState() == "green") {
        cout << "Bus_01 is moving through the intersection." << endl;
        cityBus->move();
        
        cout << "\n[TIME: 08:15] Traffic light changing..." << endl;
        parkIntersection->changeState();
        cout << "Traffic light state: " << parkIntersection->getState() << endl;
        cout << "Next vehicle must slow down due to yellow light." << endl;
        
        cout << "\n[TIME: 08:16] Traffic light changing..." << endl;
        parkIntersection->changeState();
        cout << "Traffic light state: " << parkIntersection->getState() << endl;
        cout << "New vehicles must stop at the intersection." << endl;
    }
    
    // Third scenario - Broadway Avenue
    cout << "\n[LOCATION: Broadway Avenue]" << endl;
    broadwayAve->addVehicle(taxi);
    cout << "Taxi_01 is moving freely on Broadway Avenue (no traffic light)." << endl;
    taxi->move();
    
    // Access road from grid & check traffic
    cout << "\n[SYSTEM] Traffic monitoring system check..." << endl;
    Road* retrievedRoad = cityMap.getRoadAt(0, 0);
    if (retrievedRoad) {
        cout << "Checking traffic on " << retrievedRoad->getId() << ":" << endl;
        retrievedRoad->displayVehicles();
    }
    //moving car to east 

    Car* march = new Car("Sedan_01", 60, "East", 5 ,0,0, &cityMap);
    mainStreet->addVehicle(sedan);
    sedan->move();
    cout << "Sedan_01 is now moving on Main Street." << endl;
    // Simulation end
    cout << "\n=== TRAFFIC SIMULATION ENDED ===" << endl;
    cout << "\n[SYSTEM] Clearing traffic data..." << endl;
    mainStreet->clearVehicles();
    broadwayAve->clearVehicles();
    parkRoad->clearVehicles();
    
    cout << "\n[SYSTEM] Final city status:" << endl;
    cityMap.displayGridInfo();
    
    // Free memory
    delete sedan;
    delete cityBus;
    delete taxi;
    delete mainIntersection;
    delete parkIntersection;
    delete mainStreet;
    delete broadwayAve;
    delete parkRoad;
    
    return 0;
}
