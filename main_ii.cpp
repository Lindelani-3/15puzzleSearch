#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <vector>

// Function to print the board
void printBoard(const std::string& board) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << board[i*4+j];
            if (j != 3) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
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


class BFS {
public:
    int cost;
    int q_count;
    
    BFS() : cost(0), q_count(0) {}
    
    int search(std::string initstate, std::string goalstate) {
        // goalstate = ABCDEFGHIJKLMNO#
        
        std::queue<std::string> q;
        std::unordered_set<std::string> visited;
        cost = 0;
        q_count = 0;
        int max_iterations = 1000000;

        q.push(initstate);
        visited.insert(initstate);

        while(!q.empty()) {
            if (q_count >= max_iterations) {
                return max_iterations; // return placeholder value
            }
            int q_size = q.size();

            for (int j = 0; j < q_size; j++) {
                std::string curr = q.front();
                q.pop();
                q_count++;

                if (curr == goalstate) {return cost;}

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
};



int main() {
    std::string input;
    std::cin >> input;

    std::string goalstate = "ABCDEFGHIJKLMNO#";
    BFS bfs_agent = BFS();
    std::cout << bfs_agent.search(input, goalstate) << '\n';
    // std::cout << bfs_agent.q_count << '\n';

    // printBoard(input);

    return 0;
}
