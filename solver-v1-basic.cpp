#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

typedef std::vector<std::vector<int>> perm;
typedef std::vector<int> cycle;


class Game {
    public:
    std::vector<int> cube

    void make_move(std::string move) {
        const std::map<std::string, perm moves = {
            {"U": [[0, 9, 17, 25], [1, 10, 18, 26], [2, 11, 20, 29], [36, 38, 44, 42], [37, 41, 43, 39]]},
            {"U'": inverse(moves["U"])},
            {"U2": compose(moves["U"])},

            {"D": [[0, 9, 17, 25], [1, 10, 18, 26], [2, 11, 20, 29], [36, 38, 44, 42], [37, 41, 43, 39]]},
            {"D'": inverse(moves["D"])},
            {"D2": compose(moves["D"])},

            {"R": [[0, 9, 17, 25], [1, 10, 18, 26], [2, 11, 20, 29], [36, 38, 44, 42], [37, 41, 43, 39]]},
            {"R'": inverse(moves["R"])},
            {"R2": compose(moves["R"])},
                        
            {"L": [[0, 9, 17, 25], [1, 10, 18, 26], [2, 11, 20, 29], [36, 38, 44, 42], [37, 41, 43, 39]]},
            {"L'": inverse(moves["L"])},
            {"L2": compose(moves["L"])},
                        
            {"F": [[0, 9, 17, 25], [1, 10, 18, 26], [2, 11, 20, 29], [36, 38, 44, 42], [37, 41, 43, 39]]},
            {"F'": inverse(moves["F"])},
            {"F2": compose(moves["F"])},
                        
            {"B": [[0, 9, 17, 25], [1, 10, 18, 26], [2, 11, 20, 29], [36, 38, 44, 42], [37, 41, 43, 39]]},
            {"B'": inverse(moves["B"])},
            {"B2": compose(moves["B"])},
                        
            {"M": [[0, 9, 17, 25], [1, 10, 18, 26], [2, 11, 20, 29], [36, 38, 44, 42], [37, 41, 43, 39]]},
            {"M'": inverse(moves["M"])},
            {"M2": compose(moves["M"])},
                        
            {"E": [[0, 9, 17, 25], [1, 10, 18, 26], [2, 11, 20, 29], [36, 38, 44, 42], [37, 41, 43, 39]]},
            {"E'": inverse(moves["E"])},
            {"E2": compose(moves["E"])},
                        
            {"S": [[0, 9, 17, 25], [1, 10, 18, 26], [2, 11, 20, 29], [36, 38, 44, 42], [37, 41, 43, 39]]},
            {"S'": inverse(moves["S"])},
            {"S2": compose(moves["S"])},
        };
    }
}


class Solver {
    public:
    Game game;
    
    Solver(std::vector<int> start) {
        game.cube = start;
    }
}


int main() {
    Solver solver;
    return 0;
}