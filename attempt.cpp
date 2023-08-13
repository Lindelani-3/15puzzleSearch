#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>

int bfs(std::string initstate, std::string goalstate) {
    // goalstate = ABCDEFGHIJKLMNO#
    std::string goalstate = "ABCDEFGHIJKLMNO#";
    std::queue<std::string> q;
    std::unordered_set<std::string> visited;
    int cost = 0;

    q.push(initstate);
    visited.insert(initstate);

    while(!q.empty()) {
        int q_size = q.size();

        for (int j = 0; j < q_size; j++) {
            std::string curr = q.front();
            q.pop();

            if (curr._Equal(goalstate)) {return cost;}

            std::array moves = get_moves(curr);    // string array
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

int main() {
    std::queue<std::string> q;
    std::unordered_set<std::string> visited;

    // Add a board string to the queue and hash set
    std::string board = "1234#5678";
    std::string board2 = "23415#876";
    std::string board3 = "31#246587";

    q.push(board);
    q.push(board3);

    visited.insert(board);

    // Check if a board string is in the hash set
    if (visited.count(board2) > 0) {
        std::cout << "Board string " << board2 << " is in the hash set\n";
    } else {
        std::cout << "Board string " << board2 << " is not in the hash set\n";
    }

    // Process the next board string in the queue
    while (!q.empty()) {
        std::string nextBoard = q.front();
        q.pop();
        std::cout << "Processing board string " << nextBoard << "\n";
    }

    return 0;
}
