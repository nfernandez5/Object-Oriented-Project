#ifndef bst_h
#define bst_h

#include <iostream>

/*
* bst class that accepts any data type to be processed and stored into
* a binary search tree
*/
template <typename T>
class bst {

private:
    struct Node { // struct tree linked list
        T value; // value being passed
        Node* left; // stores the address of the left node
        Node* right; // stores the address of the right node
    };
    Node* root; // stores the address of the root node
                // keeps track of starting point of the tree

    void insertSubTree(Node* n);

    //b
    void inorderHelper(std::ostream&, Node*) const;

    //c
    void preorderHelper(std::ostream&, Node*) const;

    //d
    void postorderHelper(std::ostream&, Node*) const;

    //f
    bool removeHelper(Node*, T);

    //i
    void getMinimumHelper(Node*, Node*&) const;

    //j
    void getMaximumHelper(Node*, Node*&) const;
public:
    // constructor
    bst() {
        root = nullptr;
    }
    // destructor
    ~bst();

    //copy constructor
    bst(const T& copy); 

    //assignment operator
    void operator=(const T&);

    // a
    bool insert(const T&);

    //b
    void inorder(std::ostream&) const;

    //c
    void preorder(std::ostream&) const;
    
    //d
    void postorder(std::ostream&) const;

    //e
    bool search(const T&) const;

    //f
    bool remove(const T&);

    //g
    void deleteBinarySearchTree(Node*& subtreeRoot);

    //h
    void copyBinarySearchTree(Node*, Node*&);

    //i
    T getMinimum() const;

    //j
    T getMaximum() const;

    //k
    T getSuccessor(const T&) const;

    //l
    T getPredecessor(const T&) const;

};

//deconstuctor
template <typename T>
bst<T>::~bst() {
    // destructs starting at root
    deleteBinarySearchTree(root);

}

//copy constructor
template<typename T>
bst<T>::bst(const T& copy) {
    root = nullptr;
    root = copyBinarySearchTree(root, copy.root);
}

//assignment operator
template<typename T>
void bst<T>::operator=(const T& copy) {
    if (root != copy) {
        deleteBinarySearchTree(copy);
        copy = copyBinarySearchTree(copy.root);
    }
}

//a insert
template <typename T>
bool bst<T>::insert(const T& val_par) {
    Node* newNode,
        * nodeptr;

    newNode = new Node;
    newNode->value = val_par;
    newNode->right = nullptr;
    newNode->left = nullptr;

    if (!root) {
        root = newNode;
        return true;
    }
    else {
        nodeptr = root;
        while (true) {
            if (val_par < nodeptr->value) { // left
                if (nodeptr->left != nullptr && val_par < nodeptr->left->value) {
                    nodeptr = nodeptr->left;
                    continue;
                }
                newNode->left = nodeptr->left;
                nodeptr->left = newNode;
                return true;
            }// end left
            else if (val_par > nodeptr->value) { //right
                if (nodeptr->right != nullptr && val_par > nodeptr->right->value) {
                    nodeptr = nodeptr->right;
                    continue;
                }
                newNode->right = nodeptr->right;
                nodeptr->right = newNode;
                return true;
            } // end right
            else {// if equal
                return false;
            }
        }// end while
    }// end else

    return false;
}// end function

//b
/*
* prints binary search tree in numerical order
*/
template<typename T>
void bst<T>::inorder(std::ostream& out) const {
    inorderHelper(out, root);
}

/*
* helper function to inorder
*/
template<typename T>
void bst<T>::inorderHelper(std::ostream& out, Node* root) const {
    if (root == NULL)
        return;

    inorderHelper(out, root->left);
    out << root->value << ' ';
    inorderHelper(out, root->right);
}

//c
/*
* prints binary search tree in order of root node, to descending left tree and descending right tree
*/
template <typename T>
void bst<T>::preorder(std::ostream& out) const {
    preorderHelper(out, root);
}

/*
* helper function to preorder
*/
template <typename T>
void bst<T>::preorderHelper(std::ostream& out, Node* root) const {
    if (root != nullptr) {
        out << root->value << ' ';
        preorderHelper(out, root->left);
        preorderHelper(out, root->right);
    }
}

//d
/*
* prints binary search tree in order of left tree ascending, right decesnding, then root node
*/
template<typename T>
void bst<T>::postorder(std::ostream& out) const {
    postorderHelper(out, root);
}

/*
* helper function to postorder
*/
template <typename T>
void bst<T>::postorderHelper(std::ostream& out, Node* root) const {
    if (root == NULL)
        return;
        
    postorderHelper(out, root->left);
    postorderHelper(out, root->right);
    out << root->value << " ";
}

/*
* inserts new numbers wanting to be inserted from .cpp file
*/
template <typename T>
void bst<T>::insertSubTree(Node* n) {
    if (n->left != nullptr) {
        insertSubTree(n->left);
    }
    if (n->right != nullptr) {
        insertSubTree(n->right);
    }
    insert(n->value);
    delete(n);// deletes copies

}

//e
/*
* searches for value within binary search tree
*/
template <typename T>
bool bst<T>::search(const T& val_par) const {
    Node* nodeptr = root; // starts at root

    while (true) {
        if (nodeptr->value == val_par) {
            return true;
        }
        else if (val_par > nodeptr->value && nodeptr->right != nullptr) { // right
            nodeptr = nodeptr->right;
        }
        else if (val_par < nodeptr->value && nodeptr->left != nullptr) { // left

            nodeptr = nodeptr->left;
        }
        else {
            return false;
        }
    }// end while

}

//f
/*
* removes specified value from binary search tree
*/
template<typename T>
bool bst<T>::remove(const T&value) {
    removeHelper(root, value);
    return 1;
}

/*
* helper function to remove
*/
template<typename T>
bool bst<T>::removeHelper(Node* root, T value) {
    Node* nodeptr = root, // starts at root
            * prev = nullptr,
            * temp = nullptr;
    bool is_right;

    while (true) {
        if (nodeptr->value == value) {
            break;
        }
        else if (value > nodeptr->value && nodeptr->right != nullptr) { // right
            prev = nodeptr;
            nodeptr = nodeptr->right;
            is_right = true;
        }
        else if (value < nodeptr->value && nodeptr->left != nullptr) { // left
            prev = nodeptr;
            nodeptr = nodeptr->left;
            is_right = false;
        }
        else {
            return false;
        }
    }// end while

    nodeptr->value = getSuccessor(nodeptr->value);
    
    if (prev == nullptr) {
        temp = nodeptr->right;
        nodeptr->right = temp->right;

        delete prev;
        return true;
    }
    else if (is_right) {
        prev->right = nodeptr->right;
    }
    else {
        prev->left = nodeptr->left;
    }
        
    delete nodeptr;
    
    return true;
}

//g
/*
* deletes entire binary search tree
*/
template <typename T>
void bst<T>::deleteBinarySearchTree(Node*& subtreeRoot) {
    // post order deletion
    if (subtreeRoot->left != nullptr) {
        deleteBinarySearchTree(subtreeRoot->left);
    }
    if (subtreeRoot->right != nullptr) {
        deleteBinarySearchTree(subtreeRoot->right);
    }
    delete (subtreeRoot); // for post order deletion
}

/*
* copies entire binary search tree
*/
template <typename T>
void bst<T>::copyBinarySearchTree(Node* original, Node* &copy) {
    if (original == nullptr)
        copy = nullptr;
    else {
        copy->value = original->value;
        //copys left value
        copyBinarySearchTree(original->left, copy->left);
        //copys right value
        copyBinarySearchTree(original->right, copy->right);
    }
}

//i
/*
* gets minimum value from binary search tree
*/
template <typename T>
T bst<T>::getMinimum() const {
    Node* min;
    getMinimumHelper(root, min);

    return min->value;
}

/*
* helper function to getMinimum
*/
template <typename T>
void bst<T>::getMinimumHelper(Node* subtreeRoot, Node*& min) const {
    if (subtreeRoot->left != nullptr) {
        getMinimumHelper(subtreeRoot->left, min);
    }
    else {
        min = subtreeRoot;
    }
}

//j
/*
* gets maximum value from binary search tree
*/
template<typename T>
T bst<T>::getMaximum() const {
    Node* max;
    getMaximumHelper(root, max);

    return max->value;
}

/*
* helper function to getMaximum
*/
template<typename T>
void bst<T>::getMaximumHelper(Node* node, Node* &max) const{
    if (node->right == nullptr) {
        max = node;
    }
    else {
        getMaximumHelper(node->right, max);
    }
}

//k
/*
* gets successor to specified value in binary search tree
*/
template <typename T>
T bst<T>::getSuccessor(const T& val_par) const {
    Node* nodeptr = root,
        * temp = root; // starts at root

    // search for value
    while (true) {
        if (nodeptr->value == val_par) {
            break;
        }
        else if (val_par > nodeptr->value && nodeptr->right != nullptr) { // right
            nodeptr = nodeptr->right;
            temp = nodeptr;
        }
        else if (val_par < nodeptr->value && nodeptr->left != nullptr) { // left
            if (nodeptr->value < temp->value && nodeptr->value > val_par) {
                temp = nodeptr;
            }
            nodeptr = nodeptr->left;
        }
        else {
            std::cout << "Value not found";
            return false;
        }
    }// end while

    if (nodeptr->right != nullptr) { // goes right at the valpar
        nodeptr = nodeptr->right;
    }
    else if (temp->value > nodeptr->value) {
        return temp->value;
    }
    else {
        return val_par;
    }

    while (true) {
        if (nodeptr->left == nullptr) {
            return nodeptr->value;
        }
        else {
            nodeptr = nodeptr->left;
        }
    }// end while

}

//l
/*
* gets predecessor to specified value in binary search tree
*/
template<typename T>
T bst<T>::getPredecessor(const T& value) const {
    Node* node = root;
    Node* temp = root;

    while (true) {
        if (node->value == value) {
            break;
        }
        else if (value < node->value && node->left != nullptr) {
            temp = node;
            node = node->left;
        }
        else if (value > node->value && node->right != nullptr) {
            temp = node; 
            node = node->right;
        }
        else {
            std::cout << "Value not found";
            return false;
        }
    }

    if (node->left != nullptr) {
        node = node->left;
    }
    else if (temp->value < node->value) {
        return temp->value;
    }
    else {
        return value;
    }

    return node->value;
}
#endif /* bst_h */
