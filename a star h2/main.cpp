#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>

const std::string goalstate = "ABCDEFGHIJKLMNO#";

struct Node {
    std::string state;
    int g_start_to_curr;
    int h_curr_to_goal;
};

int manhattan_distance(const std::string& state) {
    int cost = 0;
    for (int i = 0; i < 16; ++i) {
        if (state[i] != '#') {
            int goal_pos = goalstate.find(state[i]);
            int x_distance = abs((i % 4) - (goal_pos % 4));
            int y_distance = abs((i / 4) - (goal_pos / 4));
            cost += x_distance + y_distance;
        }
    }
    return cost;
}

struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.g_start_to_curr + a.h_curr_to_goal > b.g_start_to_curr + b.h_curr_to_goal;
    }
};

void add_neighbor(std::priority_queue<Node, std::vector<Node>, Compare>& pq, const Node& current, const std::string& neighbor, std::unordered_set<std::string>& visited) {
    if(visited.count(neighbor)) return;
    int g = current.g_start_to_curr + 1;
    int h = manhattan_distance(neighbor);
    pq.push({neighbor, g, h});
}

void generate_neighbors(std::priority_queue<Node, std::vector<Node>, Compare>& pq, const Node& current, std::unordered_set<std::string>& visited) {
    std::string state = current.state;
    int pos = state.find('#');

    int x = pos % 4;
    int y = pos / 4;

    if (y > 0) {
        std::string neighbor = state;
        std::swap(neighbor[pos], neighbor[pos - 4]);
        add_neighbor(pq, current, neighbor, visited);
    }

    if (y < 3) {
        std::string neighbor = state;
        std::swap(neighbor[pos], neighbor[pos + 4]);
        add_neighbor(pq, current, neighbor, visited);
    }

    if (x > 0) {
        std::string neighbor = state;
        std::swap(neighbor[pos], neighbor[pos - 1]);
        add_neighbor(pq, current, neighbor, visited);
    }

    if (x < 3) {
        std::string neighbor = state;
        std::swap(neighbor[pos], neighbor[pos + 1]);
        add_neighbor(pq, current, neighbor, visited);
    }
}

int a_star_manhattan_distance(const std::string& startstate){
    std::priority_queue<Node, std::vector<Node>, Compare> pq;
    std::unordered_set<std::string> visited;

    pq.push({startstate, 0, manhattan_distance(startstate)});
    visited.insert(startstate);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.state == goalstate) {
            std::cout << current.g_start_to_curr << std::endl;
            return current.g_start_to_curr;
        }

        generate_neighbors(pq, current, visited);
    }

    std::cout << "No solution" << std::endl;
    return -1;
}

int main() {
    std::string start;
    std::cin >> start;

    std::cout << a_star_manhattan_distance(start) << std::endl;
}
