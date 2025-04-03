// Sriram Yerramsetty
// Project 1

#include <iomanip>
#include <iostream>
#include <string>
#include "sstream"
#include "AVL.h"
#include <algorithm>

using namespace std;

// prevTODO make the commands work with the inputs

int main(){
    // reminder: do not have any memory management stuff (passing root, nullptrs, etc)

    MyAVLTree tree;

    string num;
    getline(cin, num);
    int commandNum = stoi(num);

    for (int i = 0; i < commandNum; ++i) {
        string line, command, name, id;

        getline(cin, line);
        istringstream in(line);
        in >> command;

        if (command == "insert") {
            // puts name b/w " " into name and id
            getline(in, name, '"');
            getline(in, name, '"');
            in >> id;

            // cout << "inserting " << name << " " << id << endl;
            tree.insert(name, id);

        } else if (command == "remove") {
            in >> id;
            tree.remove(id);

        } else if (command == "search") {
            string searchItem;
            in >> searchItem;
            // remove the "" from the search term, the search function auto checks if it is ID or name
            searchItem.erase(remove( searchItem.begin(), searchItem.end(), '\"' ),searchItem.end());
            tree.search(searchItem, false);

        } else if (command == "printInorder") {
            tree.printInorder();

        } else if (command == "printPreorder") {
            tree.printPreorder();

        } else if (command == "printPostorder") {
            tree.printPostorder();

        } else if (command == "printLevelCount") {
            tree.printLevelCount();

        } else if (command == "removeInorder") {
            int n;
            in >> n;
            tree.removeInorder(n);

        } else {
            // ignore command if typo/dne
            cout << "unsuccessful" << endl;
        }
    }

    return 0;
}
