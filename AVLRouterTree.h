#ifndef AVLROUTERTREE_H
#define AVLROUTERTREE_H

#include "PacketRule.h"
using namespace std;

class AVLRouterTree {

private:
    struct Node {
        PacketRule rule;
        Node* left;
        Node* right;
        int height;

        Node(PacketRule r) : rule(r), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root = nullptr;
    int rotations = 0;

public:
    void insert(PacketRule rule) {}
    PacketRule* search(int id) { return nullptr; }

    int getRotations() {
        return rotations;
    }
};

#endif