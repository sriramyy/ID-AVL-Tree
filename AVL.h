#include <iostream>
#include <string>
#include <vector>
using namespace std;
#pragma once

class MyAVLTree {

    struct Node {
        // structure of each node

        string name;               // Name
        string id;                   // ID
        int height;
        Node* left;                // left pointer
        Node* right;               // right pointer
        Node(string Name, string id);
    };


public:
    MyAVLTree();

    // Inorder functions
    vector<string> printInorder();
    void printInorderHelper(Node* node, vector<Node*>& result);
    vector<string> printInorderID(); // function to print Inorder ID int for case 3 test

    // preorder functions
    vector<string> printPreorder();
    void printPreorderHelper(Node* node, vector<string>& result);

    // post order functions
    vector<string> printPostorder();
    void printPostorderHelper(Node* node, vector<string>& result);

    // convert ID string to int
    int convertInt(string id);

    // insert functions
    bool insert(string name, string id);
    Node* insertIntoAVL(Node* root, string name, string id);

    // find the balance factor & height & print level count
    int balanceFactor(Node* root);
    int getHeight(Node* node);
    int printLevelCount();

    // remove functions
    bool remove(string id);
    bool removeInorder(int n);

    // search function
    bool search(string s, bool uniqueCheck);

    // root of the tree
    Node* root;

    // rotation functions
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* rotateLeftRight(Node* node);

};