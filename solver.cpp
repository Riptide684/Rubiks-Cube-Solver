#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <map>
#include "constants.h"
#include "tree.h"


typedef std::pair<Move, Move> MovePair;
typedef std::tuple<Vertex*, Move, std::vector<int>> VertexTuple;


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

Move scramble(std::vector<Move> actions) {
    Move cube = IDENTITY;
    for (Move& action : actions) {
        Move tmp;
        compose(action, cube, tmp);
        cube = tmp;
    }
    
    return cube;
}


class Solver {
    public:
    const Move goal;
    std::vector<int> layer_sizes;
    std::vector<Move> layer;
    std::unordered_map<Move, seq, MoveHash, MoveEqual> seen;

    Solver(const Move& start) : goal(start) {
        layer_sizes.push_back(1);
        layer.push_back(IDENTITY);
        seen.emplace(IDENTITY, seq {});
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
                    seq path = seen[perm];
                    path.push_back(move.name);
                    seen.emplace(new_perm, path);
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

    void solve() {
        std::cout << "Starting solver: \n" << std::endl;

        // generate all 5-moves
        std::cout << "Computing 5-moves\n" << std::endl;

        for (int i=1; i<=5; i++) {next_layer(i);}
        
        std::vector<Move> five_moves;
        five_moves.reserve(seen.size());

        for (const auto& move_map : seen) {
            Move move = move_map.first;
            two_row(move);
            five_moves.push_back(move);
        }

        // put 5-moves into a trie
        std::cout << "Creating move tree\n" << std::endl;

        Tree five_moves_tree(five_moves);


        // initialise 10-moves and queue
        std::map<Move, MovePair> ten_moves;
        std::map<Move, VertexTuple> queue;

        std::cout << "Computing 10-moves" << std::endl;

        std::vector<int> order;
        Vertex* x;
        Move res;

        for (Move y : five_moves) {
            order = inverse(y);
            x = five_moves_tree.smallest_leaf(order, five_moves_tree.root);
            compose(y, *x->move, res);
            two_row(res);
            queue.emplace(res, std::make_tuple(x, y, order));
        }

        std::cout << "init done" << std::endl;


        // generate all 10-moves
        VertexTuple smallest;
        Move y;
        VertexTuple next;
        uint64_t count = 0;
        uint64_t big = 0;
        uint64_t step = floor(queue.size() * queue.size() / 1000);
        while (!queue.empty()) {
            smallest = queue.begin()->second;
            x = std::get<0>(smallest);
            y = std::get<1>(smallest);
            order = std::get<2>(smallest);
            ten_moves.emplace(queue.begin()->first, std::make_pair(*x->move, y));
            queue.erase(queue.begin());

            while (true) {
                x = five_moves_tree.next_leaf(order, x);
                count++;
                if (count >= (big+1)*step) {
                    std::cout << big << std::endl;
                    big++;
                }
                if (!x) {break;}
                compose(y, *x->move, res);
                two_row(res);
                if (!queue.count(res)) {
                    next = {x, y, order};
                    //queue.emplace(res, next);
                    break;
                }
            }
        }

        std::cout << ten_moves.size() << std::endl;

        std::cout << "10-moves computed" << std::endl;
    }
};


int main() {
    Solver solver(IDENTITY);
    solver.solve();
    return 0;
}
