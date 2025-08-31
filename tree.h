#include <cmath>


template <typename T, std::size_t N, typename U>


int index(const std::array<T, N>& v, U i) {
    return std::find(v.begin(), v.end(), i) - v.begin();
}

int prefix(const std::vector<int>& x, const std::vector<int>& y) {
    // returns whether x is a prefix of y, and the next int if so
    // length of x is assumed <= length of y
    for (int i=0; i<x.size(); i++) {
        if (x[i] != y[i]) {return 0;}
    }

    return y[x.size()];
}

int apply_move(const Move& move, int cube) {
    // takes cube as int from 0 to 47
    if (cube < 24) {
        // corner cube
        int t = index(move.corner_pos, cube % 8);
        int s = move.corner_ori[t] + floor(cube / 8);
        return (t + 8 * s) % 24;
    } else {
        // edge cube
        int t = index(move.edge_pos, cube % 12);
        int s = move.edge_ori[t] + floor(cube / 12);
        return ((t + 12 * s) % 24) + 24;
    }
}

std::vector<int> two_row(const Move& move) {
    // returns the move permutation in two row notation
    // order by corners then edges, and increasing orientations
    std::vector<int> row;
    for (int i=0; i<48; i++) {
        row.push_back(apply_move(move, i));
    }

    return row;
}


struct Vertex {
    std::array<Vertex*, 48> children;
    Move move;
};


class Tree {
    public:
    Vertex* root;

    Tree(const std::vector<std::vector<int>>& seqs) {
        root = new Vertex();
        for (const std::vector<int>& seq : seqs) {
            insert(seq);
        }
    }

    void insert(const std::vector<int>& seq) {
        Vertex* node = root;

        for (int val : seq) {
            if (!node->children[val]) {
                node->children[val] = new Vertex();
            }
            node = node->children[val];
        }
        // node->move = move;
    }
};