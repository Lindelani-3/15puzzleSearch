#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_set>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

class Searcher {
    // Add your searcher class definition here
public:
    // Make sure to define your bfs, A*-h1 and A*-h2 methods
    // int count = 0;
    // The goal state
    const std::string goalstate = "ABCDEFGHIJKLMNO#";

    Searcher(): count(0) {}

    // Define the node structure for A* algorithm
    struct Node {
        std::string state;  // The current state
        int g_start_to_curr;  // The actual cost from the start state to this state
        int h_curr_to_goal;  // The heuristic cost from this state to the goal state
    };

    // Calculate the heuristic cost (manhattan distance)
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

    // Define the comparison function for the priority queue
    struct Compare {
        bool operator()(const Node& a, const Node& b) {
            return a.g_start_to_curr + a.h_curr_to_goal > b.g_start_to_curr + b.h_curr_to_goal;
        }
    };

    // Add a valid neighboring state to the priority queue
    void add_neighbor(std::priority_queue<Node, std::vector<Node>, Compare>& pq, const Node& current, const std::string& neighbor) {
        int g = current.g_start_to_curr + 1;
        int h = manhattan_distance(neighbor);
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


    // Function to perform the action on the board
    std::string do_action(std::string board, const std::string& action) {
        int pos = board.find("#");
        int x = pos / 4, y = pos % 4;
        char temp;
        
        if (action == "UP" && x > 0) {
            temp = board[pos];
            board[pos] = board[pos - 4];
            board[pos - 4] = temp;
        } else if (action == "DOWN" && x < 3) {
            temp = board[pos];
            board[pos] = board[pos + 4];
            board[pos + 4] = temp;
        } else if (action == "LEFT" && y > 0) {
            temp = board[pos];
            board[pos] = board[pos - 1];
            board[pos - 1] = temp;
        } else if (action == "RIGHT" && y < 3) {
            temp = board[pos];
            board[pos] = board[pos + 1];
            board[pos + 1] = temp;
        }

        return board;
    }

    std::vector<std::string> get_actions(const std::string& board) {
        std::vector<std::string> actions;
        int pos = board.find("#");
        int x = pos / 4, y = pos % 4;

        if (x > 0) {
            actions.push_back("UP");
        }
        if (x < 3) {
            actions.push_back("DOWN");
        }
        if (y > 0) {
            actions.push_back("LEFT");
        }
        if (y < 3) {
            actions.push_back("RIGHT");
        }

        return actions;
    }


    int bfs_search(std::string initstate, int& count) {
        // goalstate = ABCDEFGHIJKLMNO#
        
        std::queue<std::string> q;
        std::unordered_set<std::string> visited;
        int cost = 0;
        count = 0;
        int max_iterations = 1000000;

        q.push(initstate);
        visited.insert(initstate);

        while(!q.empty()) {
            if (count >= max_iterations) {
                return max_iterations; // return placeholder value
            }
            int q_size = q.size();

            for (int j = 0; j < q_size; j++) {
                std::string curr = q.front();
                q.pop();
                count++;

                if (curr == goalstate) {
                    std::cout << cost << '\n';
                    std::cout << count << '\n';
                    std::cout << "---------" << '\n' ;
                    return cost;}

                std::vector<std::string> moves = get_actions(curr);    // string array
                for (int i = 0; i < moves.size(); i++) {
                    std::string childstate = do_action(curr, moves[i]);
                    
                    if (visited.count(childstate) == 0) {
                        q.push(childstate);
                        
                        visited.insert(childstate);
                    }
                }
            }

            cost++;
        }

        return -1;
    }


    int a_star_misplaced_tiles(const std::string& startstate){
        std::priority_queue<Node, std::vector<Node>, Compare> pq;
        std::unordered_set<std::string> visited;

        // Push the start state to the priority queue
        pq.push({startstate, 0, manhattan_distance(startstate)});

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();
            count++;
            // std::cout<<current.state<<std::endl;

            if (current.state == goalstate) {
                // Found the goal state, print the cost and return
                // std::cout << current.g_start_to_curr << std::endl;
                std::cout << current.g_start_to_curr << '\n';
                std::cout << count << '\n';
                std::cout << "---------" << '\n' ;
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
};

int main() {
    std::ifstream infile("puzzles.txt");
    std::ofstream outfile("results.csv");

    outfile << "Puzzle, Solution, BFS, A*-h1, A*-h2\n";

    std::string start;
    std::map<int, std::vector<int>> solution_length_data;

    while (infile >> start) {
        int nodes_expanded_bfs = 0;
        int nodes_expanded_astar_h1 = 0;
        int nodes_expanded_astar_h2 = 0;

        int solution_length_bfs = bfs_search(start, nodes_expanded_bfs);
        int solution_length_astar_h1 = a_star(start, 1, nodes_expanded_astar_h1);
        int solution_length_astar_h2 = a_star(start, 2, nodes_expanded_astar_h2);

        outfile << start << ", " << solution_length_bfs << ", " << nodes_expanded_bfs << ", " << nodes_expanded_astar_h1 << ", " << nodes_expanded_astar_h2 << "\n";

        // Aggregate data for the same solution lengths
        solution_length_data[solution_length_bfs].push_back(nodes_expanded_bfs);
        solution_length_data[solution_length_astar_h1].push_back(nodes_expanded_astar_h1);
        solution_length_data[solution_length_astar_h2].push_back(nodes_expanded_astar_h2);
    }

    // Optional: Compute the average node expansion for each solution length
    std::ofstream avg_file("average_results.csv");
    avg_file << "Solution Length, Average BFS, Average A*-h1, Average A*-h2\n";
    for (const auto& pair : solution_length_data) {
        int solution_length = pair.first;
        const auto& nodes_expanded = pair.second;
        int avg_bfs = std::accumulate(nodes_expanded.begin(), nodes_expanded.end(), 0) / nodes_expanded.size();
        avg_file << solution_length << ", " << avg_bfs << "\n"; // Continue this pattern for other algorithms if needed
    }

    infile.close();
    outfile.close();
    avg_file.close();

    std::cout << "Results saved to results.csv\n";
    return 0;
}
