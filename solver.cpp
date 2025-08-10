#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_set>
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
    std::vector<int> layer_sizes;
    std::vector<Move> layer;
    std::unordered_set<Move, MoveHash, MoveEqual> seen;

    Solver(const Move& start) : goal(start) {
        layer_sizes.push_back(1);
        layer.push_back(IDENTITY);
        seen.insert(IDENTITY);
    }

    void next_layer(int i) {
        // populates layer i
        std::vector<Move> new_layer;
        layer_sizes.push_back(0);
        new_layer.reserve(layer.size() * legal_moves.size());

        for (const Move& perm : layer) {
            for (const Move& move : legal_moves) {
                Move new_perm;
                compose(perm, move, new_perm);
                if (seen.find(new_perm) == seen.end()) {
                    new_layer.push_back(new_perm);
                    layer_sizes[i]++;
                    seen.insert(new_perm);
                }
            }   
        }

        layer = new_layer;
    }

    void perft(int depth) {
        std::cout << "Starting performance test: \n" << std::endl;

        for (int i=1; i<=depth; i++) {
            auto start = std::chrono::system_clock::now();
            next_layer(i);
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << layer_sizes[i] << " positions in layer " << i << "\n\n";
            std::cout << "Exploring layer " << i << " took " << elapsed.count() << " ms\n" << std::endl;
        }

        std::cout << "Performance test completed!" << std::endl;
    }
};


int main() {
    Solver solver(IDENTITY);
    solver.perft(5);
    return 0;
}
