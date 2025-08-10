#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "constants.h"


inline void compose(const Move& p, const Move& q, Move& r) {
    // composes the moves p and q into r = p o q

    for (int i = 0; i < 8; ++i) {
        uint8_t old_pos = p.corner_pos[i];
        r.corner_pos[i] = q.corner_pos[old_pos];
        r.corner_ori[i] = (p.corner_ori[i] + q.corner_ori[old_pos]) % 3;
    }

    for (int i = 0; i < 12; ++i) {
        uint8_t old_pos = p.edge_pos[i];
        r.edge_pos[i] = q.edge_pos[old_pos];
        r.edge_ori[i] = (p.edge_ori[i] + q.edge_ori[old_pos]) % 2;
    }
}

void display(const Move& move) {
    for (uint8_t i : move.corner_pos) {
        std::cout << static_cast<int>(i) << ", ";
    }
    std::cout << "\n\n";

    for (uint8_t i : move.corner_ori) {
        std::cout << static_cast<int>(i) << ", ";
    }
    std::cout << "\n\n";

    for (uint8_t i : move.edge_pos) {
        std::cout << static_cast<int>(i) << ", ";
    }
    std::cout << "\n\n";

    for (uint8_t i : move.edge_ori) {
        std::cout << static_cast<int>(i) << ", ";
    }
}


class Solver {
    public:
    const Move goal;
    std::vector<std::vector<Move>> layers;

    Solver(const Move& start) : goal(start) {
        layers.push_back({IDENTITY});
    }

    bool already_searched(const Move& move, int i) {
        for (int j=0; j<=i; j++) {
            std::vector<Move>& layer = layers.at(j);
            if (std::find(layer.begin(), layer.end(), move) != layer.end()) {
                return true;
            }
        }

        return false;
    }

    void next_layer(int i) {
        // populates layer i
        layers.push_back({});

        for (const Move& perm : layers.at(i-1)) {
            for (const Move& move : legal_moves) {
                Move new_perm;
                compose(perm, move, new_perm);
                // use set for fast lookup
                std::vector<Move>& new_layer = layers.at(i);
                if (!already_searched(new_perm, i)) {
                    new_layer.push_back(new_perm);
                }
            }   
        }
    }

    void perft(int depth) {
        std::cout << "Starting performance test: \n" << std::endl;

        for (int i=1; i<=depth; i++) {
            auto start = std::chrono::system_clock::now();
            next_layer(i);
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << layers.at(i).size() << " positions in layer " << i << "\n\n";
            std::cout << "Exploring layer " << i << " took " << elapsed.count() << " ms\n" << std::endl;
        }

        std::cout << "Performance test completed!" << std::endl;
    }
};


int main() {
    Solver solver(IDENTITY);
    solver.perft(4);
    return 0;
}
