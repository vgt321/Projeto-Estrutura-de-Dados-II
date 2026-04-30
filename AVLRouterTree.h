#ifndef AVLROUTERTREE_H
#define AVLROUTERTREE_H

#include "PacketRule.h"
#include <algorithm> 
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

    // 🔹 INSERT INTERNO (recursivo)
    Node* insert(Node* node, PacketRule rule) {
        if (!node) return new Node(rule);

        if (rule.id < node->rule.id)
            node->left = insert(node->left, rule);
        else if (rule.id > node->rule.id)
            node->right = insert(node->right, rule);

        return node;
    }

    // 🔹 ALTURA
    int getHeight(Node* n) {
        return n ? n->height : 0;
    }

    // 🔹 ATUALIZA ALTURA
    void updateHeight(Node* n) {
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    }

    // 🔹 FATOR DE BALANCEAMENTO
    int getBalance(Node* n) {
        return getHeight(n->left) - getHeight(n->right);
    }

public:
    // 🔹 INSERT PÚBLICO
    void insert(PacketRule rule) {
        root = insert(root, rule);
    }

    // 🔹 SEARCH (ainda simples)
    PacketRule* search(int id) {
        return nullptr;
    }

    int getRotations() {
        return rotations;
    }
};

#endif