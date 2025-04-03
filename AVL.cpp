#include <iostream>
#include <string>
using namespace std;
#include "AVL.h"
#include <queue>

MyAVLTree::MyAVLTree(){
    root = nullptr;

}

//



int MyAVLTree::convertInt(string id) {
    return stoi(id);
}

// INSERT FUNCTIONS ----------------------------------------------------------------------------------------------------

// Insert function checks if it's a valid and successful insert
bool MyAVLTree::insert(string name, string id) {
    // check conditions to make sure valid
    // 8 digits long
    if (id.length() != 8) {
        cout << "unsuccessful" << endl;
        return false;
    }
    // number
    for (char c : id) {
        if (c < '0' || c > '9') {
            cout << "unsuccessful" << endl;
            return false;
        }
    }

    // unique
    if (search(id, true)) {
        cout << "unsuccessful" << endl;
        return false;
    }

    // names contains only alphabets and spaces
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) {
            cout << "unsuccessful" << endl;
            return false;
        }
    }
    // now call insertIntoAVL to actually insert into the tree and balance if necessary
    this->root = insertIntoAVL(root, name, id);

    cout << "successful" << endl;
    return true;
}

// insertIntoAVL Function - actually inserts the node into the tree according to ID
MyAVLTree::Node* MyAVLTree::insertIntoAVL(Node* node, string name, string id){

    if (node == nullptr) {
        return new Node(name, id);
    }

    if (convertInt(id) < convertInt(node->id)) {
        node->left = insertIntoAVL(node->left, name, id);
    } else if (convertInt(id) > convertInt(node->id)){
        node->right = insertIntoAVL(node->right, name, id);
    }

    // update heights/bal factor
    node->height = 1 + max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);

    // if (getHeight(node->left) > getHeight(node->right))
    //     node->height = getHeight(node->left) + 1;
    // else
    //     node->height = getHeight(node->right) + 1;

    // cout << "balF of " << node->id << " is " << balanceFactor(node) << endl;
    // check if need to preform rotation

    // L-R <= -2 means right heavy
    if (balanceFactor(node) <= -2) {
        if (balanceFactor(node->right) > 0) {
            node = rotateRightLeft(node);
        } else {
            node = rotateLeft(node);
        }
    // L-R >= 2 means left heavy
    } else if (balanceFactor(node) >= 2) {
        if (balanceFactor(node->left) < 0) {
            node = rotateLeftRight(node);
        } else {
            node = rotateRight(node);
        }
    }

    return node;

}

// HEIGHT & BALANCE FACTOR FUNCTIONS -----------------------------------------------------------------------------------

int MyAVLTree::balanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        //return getHeight(node->left) - getHeight(node->right);
        return (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0);
    }
}

//
int MyAVLTree::getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    // checks if the node exists then gets the height
    return 1 + max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
    // return 1 + max(getHeight(node->left), getHeight(node->right));
}


// PRINTING FUNCTIONS --------------------------------------------------------------------------------------------------

vector<string> MyAVLTree::printInorder(){
    vector<Node*> nodeResult;
    vector<string> result;
    printInorderHelper(root, nodeResult);

    // print the result vector
    for (size_t i = 0; i < nodeResult.size(); i++) {
        result.push_back(nodeResult[i]->name);
        cout << nodeResult[i]->name;
        if (i != nodeResult.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    return result;
}

// function for the case 3 test
vector<string> MyAVLTree::printInorderID(){
    vector<Node*> nodeResult;
    vector<string> result;
    printInorderHelper(root, nodeResult);

    for (auto & i : nodeResult) {
        result.emplace_back(i->id);
    }

    // print the result vector
    // for (auto & i : result) {
    //     cout << i << " ";
    // }
    return result;
}

// helper function to print in order
void MyAVLTree::printInorderHelper(Node* node, vector<Node*>& result) {
    if (node != nullptr) {
        printInorderHelper(node->left, result);
        result.emplace_back(node);
        printInorderHelper(node->right, result);
    }
}

vector<string> MyAVLTree::printPreorder(){
    vector<string> result;
    printPreorderHelper(root, result);

    // print the result vector
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i != result.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    return result;
}

void MyAVLTree::printPreorderHelper(Node* node, vector<string>& result) {
    if (node != nullptr) {
        result.emplace_back(node->name);
        printPreorderHelper(node->left, result);
        printPreorderHelper(node->right, result);
    }
}

vector<string> MyAVLTree::printPostorder() {
    vector<string> result;
    printPostorderHelper(root, result);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i != result.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    return result;
}

void MyAVLTree::printPostorderHelper(Node* node, vector<string>& result) {
    if (node != nullptr) {
        printPostorderHelper(node->left, result);
        printPostorderHelper(node->right, result);
        result.emplace_back(node->name);
    }
}

// prints how many levels are in the tree
int MyAVLTree::printLevelCount() {
    if (root == nullptr) {
        cout << "0" << endl;
        return 0;
    }

    cout << getHeight(root) << endl;
    return getHeight(root);
}

// SEARCH & REMOVE -----------------------------------------------------------------------------------------------------

// prevTODO: make it so if find two ids with same name then returns both
bool MyAVLTree::search(string s, bool uniqueCheck) {

    // if we are checking if unique (for insert function) then shouldn't be printing unsuccessful in the beginning if root is null
    if (!uniqueCheck && root == nullptr) {
        cout << "unsuccessful" << endl;
        return false;
    }


    // this means that it is alphabet (or space) so search by NAME
    // return multiple if multiple IDs with that name
    if (isalpha(s[0]) || isspace(s[0])) {

        // create a nodeResult to store ALL nodes of the AVL
        vector<Node*> nodeResult;
        printInorderHelper(root, nodeResult);
        bool foundMatch = false; // keep track if found a match

        // check if any nodes name equal to string s
        for (auto & i : nodeResult) {
            if (s == i->name) {
                cout << i->id << endl;
                foundMatch = true;
            }
        }

        // if we did not find a match then return false
        if (!foundMatch) {
            cout << "unsuccessful" << endl;
            return false;
        }

        return true;

    // this means that it is number so search by ID
    } else if (s[0] >= '0') {
        Node* node = root;
        while (node != nullptr) {
            if (s == node->id) {
                if (!uniqueCheck) {
                    cout << node->name << endl;
                }
                return true;
            } else if (s > node->id) {
                node = node->right;
            } else if (s < node->id) {
                node = node->left;
            }
        }

    } else {
        cout << "unsuccessful" << endl;
        return false;
    }

    // make sure not checking if unique for the insert function when printing unsuccessful
    if (!uniqueCheck) {
        cout << "unsuccessful" << endl;
    }
    return false;
}


bool MyAVLTree::remove(string id){
    Node* node = root;
    Node* parent = nullptr;

    // look for node
    while (node != nullptr) {
        if (id == node->id) {
            break;
        } else if (id > node->id) {
            parent = node;
            node = node->right;
        } else if (id < node->id) {
            parent = node;
            node = node->left;
        }
    }

    // if the node isn't found
    if (node == nullptr) {
        cout << "unsuccessful" << endl;
        return false;
    }

    //cout << node->id << " abd " << node->name << endl;

    // three different cases for deletion
    if (node->left == nullptr && node->right == nullptr) { // no children

        // reassign the parent node first
        if (parent == nullptr) {
            // means node only node so deleting whole tree
            root = nullptr;
        } else if (parent->left == node) {
            parent->left = nullptr;
        } else if (parent->right == node) {
            parent->right = nullptr;
        }

        delete node;

    } else if (node->left != nullptr && node->right != nullptr) { // 2 children

        // prioritize the inorder successor (right subtree leftmost child)
        Node* successor = node->right;
        Node* successorParent = node;

        // go to the left most node
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        // copy successor info to the root node
        node->id = successor->id;
        node->name = successor->name;

        // delete the successor node
        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else if (successorParent->right == successor) {
            successorParent->right = successor->right;
        }
        delete successor;


    } else if (node->left == nullptr && node->right != nullptr) { // 1 child (right child)

        // reassign node child to parent node in appropiat spot
        if (parent == nullptr) {
            root = node->right;
        } else if (parent->left == node) {
            parent->left = node->right;
        } else if (parent->right == node) {
            parent->right = node->right;
        }
        delete node;

    } else if (node->left != nullptr && node->right == nullptr) { // 1 child (left child)

        // reassign node child to parent node in appropiat spot
        if (parent == nullptr) {
            root = node->left;
        } else if (parent->left == node) {
            parent->left = node->left;
        } else if (parent->right == node) {
            parent->right = node->left;
        }
        delete node;

    }

    cout << "successful" << endl;
    return true;
}

bool MyAVLTree::removeInorder(int n) {

    // get in order traversal
    vector<string> inorderID = printInorderID();

    // make sure n not negative
    if (n<0) {
        cout << "unsuccessful" << endl;
        return false;
    }

    // check if nth exists
    if (n > static_cast<int>(inorderID.size())) {
        cout << "unsuccessful" << endl;
        return false;
    } // else remove it using remove ID
    this->remove(inorderID[n]);

    // cout << "successful" << endl; don't need to print bc remove function alr print
    return true;
}



// ROTATION FUNCTIONS --------------------------------------------------------------------------------------------------

MyAVLTree::Node* MyAVLTree::rotateRight(Node* node){
    // cout << "rotating right" << endl;
    Node* grandChild = node->left->right;
    Node* newParent = node->left;
    newParent->right = node;
    node->left = grandChild;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

    return newParent;
}

MyAVLTree::Node* MyAVLTree::rotateLeft(Node* node){
    // cout << "rotating left" << endl;
    Node* grandchild = node->right->left;
    Node* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

    return newParent;
}

MyAVLTree::Node* MyAVLTree::rotateRightLeft(Node* node){
    // cout << "rotating right left" << endl;
    node->right = rotateRight(node->right);
    Node* newParent = rotateLeft(node);
    return newParent;
}

MyAVLTree::Node* MyAVLTree::rotateLeftRight(Node* node){
    // cout << "rotating left right" << endl;
    node->left = rotateLeft(node->left);
    Node* newParent = rotateRight(node);
    return newParent;
}

// NODE ------------ ...

MyAVLTree::Node::Node(string name, string id){
    this->name = name;
    this->id = id;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
}

