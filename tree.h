#include <cmath>
#include <optional>


template <typename Container, typename T>
int index(const Container& container, const T& value) {
    for (size_t i = 0; i < container.size(); ++i) {
        if (container[i] == value) {
            return static_cast<int>(i);
        }
    }
    throw std::out_of_range("Element not found in container");
}

template <typename T, size_t N>
int index(const T (&array)[N], const T& value) {
    for (size_t i = 0; i < N; ++i) {
        if (array[i] == value) {
            return static_cast<int>(i);
        }
    }
    throw std::out_of_range("Element not found in array");
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

std::vector<int> inverse(const std::vector<int>& x) {
    std::vector<int> y;

    for (int i=0; i<48; i++) {
        y.push_back(index(x, i));
    }

    return y;
}

template <typename K, typename V>
int index(const std::map<K, V>& m, const K& key) {
    auto it = m.find(key);
    if (it == m.end()) {
        throw std::out_of_range("Key not found in map");
    }
    return std::distance(m.begin(), it);
}


struct Vertex {
    std::map<int, Vertex*> children;
    Vertex* parent;
    std::optional<Move> move;
};


class Tree {
    public:
    Vertex* root;

    Tree(const std::vector<Move>& moves) {
        root = new Vertex();
        for (const Move& move : moves) {
            insert(move);
        }
    }

    void insert(const Move& move) {
        const std::vector<int> seq = two_row(move);
        Vertex* node = root;

        for (int val : seq) {
            if (!node->children.count(val)) {
                node->children[val] = new Vertex();
                node->children[val]->parent = node;
            }
            node = node->children[val];
        }
        node->move = move;
    }

    Vertex* smallest_leaf(const std::vector<int>& order, Vertex* start) {
        // traverses tree wrt given order
        Vertex* node = start;
        Vertex* child;

        while (!node->move) {
            node = node->children.begin()->second;
        }

        return node;
    }

    Vertex* next_leaf(const std::vector<int>& order, Vertex* leaf) {
    //     // traverses tree wrt given order to find next leaf
    //     Vertex* node = leaf;
    //     int letter;

    //     while (true) {
    //         if (!node->parent) {return nullptr;}

    //         letter = index(node->parent->children, node);

    //         for (int i=index(order, letter)+1; i<48; i++) {
    //             if (node->parent->children[i]) {
    //                 node = node->parent->children[i];
    //                 break;
    //             }
    //         }

    //         node = node->parent;
    //     }

    //     return smallest_leaf(order, node);
        return new Vertex();
    }
};