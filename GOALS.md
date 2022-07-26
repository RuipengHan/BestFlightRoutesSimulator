# Project Goals
In this project, we will write a program that deals with aireports, airline, and routes data from [OpenFlights](https://openflights.org/data.html) and ultimately determine preferred routes by implementing the shortest path algorithm using the airport data. 

Users are expected to give some constraints passed as arguments to the program in order to retrieve the best routes. For instance, users must at least provide an airport name as the starting point to take off and a destination airport. Our program will also allow users to give other constraints such as specific airlines. 

We will output the result in both command line consoles and through a text file (result.txt).

## Algorithm we use to find shortest path in the graph
We will use the **Dijkstra’s algorithm** to determine the shortest path between two nodes. The graph will be directed (by the routes) and the weighted (by the distance between airports). In Dijkstra’s we will put accumulative weight of node (after relaxation) in a priority queue and find the min distance. 

If the user didn't specify the constraint of shortest path, then we will do a BFS traversal to present all possible paths from the starting point to the destination.

We will also implement the Landmark Path algorithm (shortest path from a to b through c) as the user can provide an intermediate point between starting and ending points which the route must pass through.

## Dataset Format
All of our data, including airports, airlines, and routes, will be in the straightforward CSV format, where each entry belongs to a specific category. 
As an example, the data will look like something as follows;
507, "London Heathrow Airport", "London","United Kingdom", " LHR", "EGLL",  51.4706, -0.461941, 83, 0, "E", "Europe/London", "airport", "OurAirports"
## Our Source:
OPEN FLIGHTS:
SOURCE: https://openflights.org/data.html, or click [here](https://openflights.org/data.html).

