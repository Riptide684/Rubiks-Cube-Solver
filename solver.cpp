#include <array>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>


struct Move {
    std::array<uint8_t, 8> corner_pos;
    std::array<uint8_t, 8> corner_ori;
    std::array<uint8_t, 12> edge_pos;
    std::array<uint8_t, 12> edge_ori;

    bool operator==(const Move& other) const noexcept {
        return corner_pos == other.corner_pos &&
               corner_ori == other.corner_ori &&
               edge_pos   == other.edge_pos &&
               edge_ori   == other.edge_ori;
    }
};


constexpr Move IDENTITY = {
    {0,1,2,3,4,5,6,7},
    {0,0,0,0,0,0,0,0},
    {0,1,2,3,4,5,6,7,8,9,10,11},
    {0,0,0,0,0,0,0,0,0,0,0,0}
};

// ----------------------- U ---------------------------

constexpr Move U = {
    {3,0,1,2,4,5,6,7},
    {0,0,0,0,0,0,0,0},
    {3,0,1,2,4,5,6,7,8,9,10,11},
    {1,1,1,1,0,0,0,0,0,0,0,0}
};

constexpr Move U2 = {
    {2,3,0,1,4,5,6,7},
    {0,0,0,0,0,0,0,0},
    {2,3,0,1,4,5,6,7,8,9,10,11},
    {0,0,0,0,0,0,0,0,0,0,0,0}
};

constexpr Move U_ = {
    {1,2,3,0,4,5,6,7},
    {0,0,0,0,0,0,0,0},
    {1,2,3,0,4,5,6,7,8,9,10,11},
    {1,1,1,1,0,0,0,0,0,0,0,0}
};

// ----------------------- D ---------------------------

constexpr Move D = {
    {0,1,2,3,5,6,7,4},
    {0,0,0,0,0,0,0,0},
    {0,1,2,3,4,5,6,7,9,10,11,8},
    {0,0,0,0,0,0,0,0,1,1,1,1}
};

constexpr Move D2 = {
    {0,1,2,3,6,7,4,5},
    {0,0,0,0,0,0,0,0},
    {0,1,2,3,4,5,6,7,10,11,8,9},
    {0,0,0,0,0,0,0,0,0,0,0,0}
};

constexpr Move D_ = {
    {0,1,2,3,7,4,5,6},
    {0,0,0,0,0,0,0,0},
    {0,1,2,3,4,5,6,7,11,8,9,10},
    {0,0,0,0,0,0,0,0,1,1,1,1}
};

// ----------------------- R ---------------------------

constexpr Move R = {
    {0,1,3,7,4,5,2,6},
    {0,0,1,2,0,0,2,1},
    {0,1,2,7,4,5,3,11,8,9,10,6},
    {0,0,0,1,0,0,1,1,0,0,0,1}
};

constexpr Move R2 = {
    {0,1,7,6,4,5,3,2},
    {0,0,0,0,0,0,0,0},
    {0,1,2,11,4,5,7,6,8,9,10,3},
    {0,0,0,0,0,0,0,0,0,0,0,0}
};

constexpr Move R_ = {
    {0,1,6,2,4,5,7,3},
    {0,0,1,2,0,0,2,1},
    {0,1,2,6,4,5,11,3,8,9,10,7},
    {0,0,0,1,0,0,1,1,0,0,0,1}
};

// ----------------------- L ---------------------------

constexpr Move L = {
    {1,5,2,3,0,4,6,7},
    {1,2,0,0,2,1,0,0},
    {0,5,2,3,1,9,6,7,8,4,10,11},
    {0,1,0,0,1,1,0,0,0,1,0,0}
};

constexpr Move L2 = {
    {5,4,2,3,1,0,6,7},
    {0,0,0,0,0,0,0,0},
    {0,9,2,3,5,4,6,7,8,1,10,11},
    {0,0,0,0,0,0,0,0,0,0,0,0}
};

constexpr Move L_ = {
    {4,0,2,3,5,1,6,7},
    {1,2,0,0,2,1,0,0},
    {0,4,2,3,9,1,6,7,8,5,10,11},
    {0,1,0,0,1,1,0,0,0,1,0,0}
};

// ----------------------- F ---------------------------

constexpr Move F = {
    {4,1,2,0,7,5,6,3},
    {2,0,0,1,1,0,0,2},
    {4,1,2,3,8,5,6,0,7,9,10,11},
    {1,0,0,0,1,0,0,1,1,0,0,0}
};

constexpr Move F2 = {
    {7,1,2,4,3,5,6,0},
    {0,0,0,0,0,0,0,0},
    {8,1,2,3,7,5,6,4,0,9,10,11},
    {0,0,0,0,0,0,0,0,0,0,0,0}
};

constexpr Move F_ = {
    {3,1,2,7,0,5,6,4},
    {2,0,0,1,1,0,0,2},
    {7,1,2,3,0,5,6,8,4,9,10,11},
    {1,0,0,0,1,0,0,1,1,0,0,0}
};

// ----------------------- B ---------------------------

constexpr Move B = {
    {0,2,6,3,4,1,5,7},
    {0,1,2,0,0,2,1,0},
    {0,1,6,3,4,2,10,7,8,9,5,11},
    {0,0,1,0,0,1,1,0,0,0,1,0}
};

constexpr Move B2 = {
    {0,6,5,3,4,2,1,7},
    {0,0,0,0,0,0,0,0},
    {0,1,10,3,4,6,5,7,8,9,2,11},
    {0,0,0,0,0,0,0,0,0,0,0,0}
};

constexpr Move B_ = {
    {0,5,1,3,4,6,2,7},
    {0,1,2,0,0,2,1,0},
    {0,1,5,3,4,10,2,7,8,9,6,11},
    {0,0,1,0,0,1,1,0,0,0,1,0}
};


// all possible moves (uses HTM, so half turns allowed, but slices are not)
constexpr std::array<Move, 18> legal_moves = {U, U2, U_, D, D2, D_, R, R2, R_, L, L2, L_, F, F2, F_, B, B2, B_};


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
