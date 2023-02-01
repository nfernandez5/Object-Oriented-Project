/*
* Solution to Binary Search Tree
* Solution written by Dory Apollon and Nathaniel Fernandez
*/

#include <iostream>
#include "bst.h"

using namespace std;


int main() {
    bst<int>node;
    
    /*
    * inserts specified values into binary search tree
    */
    node.insert(50);
    node.insert(30);
    node.insert(70);
    node.insert(20);
    node.insert(40);
    node.insert(60);
    node.insert(80);

    /*
    * places values inorder and prints
    */
    cout << "Inorder: ";
    node.inorder(cout);
    cout << endl;
    
    /*
    * places values preorder and prints
    */
    cout << "Preorder: ";
    node.preorder(cout);
    cout << endl;

    /*
    * places values postorder and prints
    */
    cout << "Postorder: ";
    node.postorder(cout);
    cout << endl;

    /*
    * searches for specified values and determines whether they are in the binary search tree or not
    */
    if (node.search(80)) {
        cout << "Value found\n";
    }
    else {
        cout << "Value not found\n";
    }

    if (node.search(10)) {
        cout << "Value found\n";
    }
    else {
        cout << "Value not found\n";
    }

    /*
    * gets minimum value from binary search tree
    */
    cout << "Minimum: ";
    cout << node.getMinimum() << endl;

    /*
    * gets successor of specified value from binary search tree
    */
    cout << "Successor of 19: " << node.getSuccessor(20) << endl;
    
    /*
    */
    cout << "Maximum: " << node.getMaximum() << endl;

    /*
    * gets predecessor of specified value from binary search tree
    */
    cout << "Predecessor of 59: " << node.getPredecessor(75) << endl;

    /*
    * initializes new node for original bst to be copied to, copys the bst to the new node, and prints the 
    * new node using the inorder function
    */
    bst<int>node2(node);
    bst<int>* copy = new bst<int>();
    *copy = node2.operator=(node);
    cout << "Copy of BST: ";
    copy->inorder(cout);
    cout << endl;

    /*
    * prints out the bst before modification
    */
    cout << "Before modify: ";
    node.inorder(cout);
    cout << endl;

    /*
    * removes specified number and prints the new bianry search tree using the inorder function
    */
    node.remove(50);
    cout << "After modify: ";
    node.inorder(cout);

    cout << "\nEnd!\n";

    return 0;
}