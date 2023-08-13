#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>

// The goal state
const std::string goalstate = "ABCDEFGHIJKLMNO#";

// Define the node structure for A* algorithm
struct Node {
    std::string state;  // The current state
    int g_start_to_curr;  // The actual cost from the start state to this state
    int h_curr_to_goal;  // The heuristic cost from this state to the goal state
};

// Calculate the heuristic cost (number of misplaced tiles)
int misplaced_tiles(const std::string& state) {
    int cost = 0;
    for (int i = 0; i < 16; ++i) {
        if (state[i] != '#' && state[i] != goalstate[i]) {
            ++cost;
        }
    }
    return cost;
}

// Define the comparison function for the priority queue
struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.g_start_to_curr + a.h_curr_to_goal > b.g_start_to_curr + b.h_curr_to_goal;
    }
};

// Add a valid neighboring state to the priority queue
void add_neighbor(std::priority_queue<Node, std::vector<Node>, Compare>& pq, const Node& current, const std::string& neighbor) {
    int g = current.g_start_to_curr + 1;
    int h = misplaced_tiles(neighbor);
    pq.push({neighbor, g, h});
}

// Generate all valid neighboring states and add them to the priority queue
void generate_neighbors(std::priority_queue<Node, std::vector<Node>, Compare>& pq, const Node& current) {
    std::string state = current.state;
    int pos = state.find('#');  // Find the position of the blank space

    int x = pos % 4;  // Column of the blank space
    int y = pos / 4;  // Row of the blank space

    // If the blank space can be moved up, generate the corresponding neighbor
    if (y > 0) {
        std::string neighbor = state;
        std::swap(neighbor[pos], neighbor[pos - 4]);
        add_neighbor(pq, current, neighbor);
    }

    // If the blank space can be moved down, generate the corresponding neighbor
    if (y < 3) {
        std::string neighbor = state;
        std::swap(neighbor[pos], neighbor[pos + 4]);
        add_neighbor(pq, current, neighbor);
    }

    // If the blank space can be moved left, generate the corresponding neighbor
    if (x > 0) {
        std::string neighbor = state;
        std::swap(neighbor[pos], neighbor[pos - 1]);
        add_neighbor(pq, current, neighbor);
    }

    // If the blank space can be moved right, generate the corresponding neighbor
    if (x < 3) {
        std::string neighbor = state;
        std::swap(neighbor[pos], neighbor[pos + 1]);
        add_neighbor(pq, current, neighbor);
    }
}



int a_star_misplaced_tiles(const std::string& startstate){
    std::priority_queue<Node, std::vector<Node>, Compare> pq;
    std::unordered_set<std::string> visited;

    // Push the start state to the priority queue
    pq.push({startstate, 0, misplaced_tiles(startstate)});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        // std::cout<<current.state<<std::endl;

        if (current.state == goalstate) {
            // Found the goal state, print the cost and return
            // std::cout << current.g_start_to_curr << std::endl;
            return current.g_start_to_curr;
        }

        if (visited.count(current.state)) {
            // This state has been visited before, skip it
            continue;
        }

        visited.insert(current.state);

        // Generate all valid neighboring states and add them to the priority queue
        generate_neighbors(pq, current);

    }

    std::cout << "No solution" << std::endl;
    return -1;
}



int main() {
    std::string start;
    std::cin >> start;

    std::cout << a_star_misplaced_tiles(start) << std::endl;
}
