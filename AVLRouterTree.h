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

    int getHeight(Node* n) {
        return n ? n->height : 0;
    }

    void updateHeight(Node* n) {
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    }

    int getBalance(Node* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    // ROTACAO PARA A DIREITA
    Node* rotateRight(Node* y) {
        rotations++;

        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // ROTACAO PARA A ESQUERDA
    Node* rotateLeft(Node* x) {
        rotations++;

        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insert(Node* node, PacketRule rule) {
        if (!node) return new Node(rule);

        if (rule.id < node->rule.id)
            node->left = insert(node->left, rule);
        else if (rule.id > node->rule.id)
            node->right = insert(node->right, rule);
        else
            return node;

        updateHeight(node);

        int balance = getBalance(node);

        // Caso esquerda-esquerda
        if (balance > 1 && rule.id < node->left->rule.id)
            return rotateRight(node);

        // Caso direita-direita
        if (balance < -1 && rule.id > node->right->rule.id)
            return rotateLeft(node);

        // Caso esquerda-direita
        if (balance > 1 && rule.id > node->left->rule.id) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Caso direita-esquerda
        if (balance < -1 && rule.id < node->right->rule.id) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

public:
    void insert(PacketRule rule) {
        root = insert(root, rule);
    }

    PacketRule* search(int id) {
        return nullptr;
    }

    int getRotations() {
        return rotations;
    }
};

#endif