#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node(){}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void clear(Node<Key, Value>* node_to_delete);
    bool isBalancedHelper(Node<Key, Value>* node, int& h) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (current_ != rhs.current_);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    // right child
    if(current_->getRight() != nullptr){
        current_ = current_->getRight();
        while(current_->getLeft() != nullptr){
            current_ = current_->getLeft();
        }
    }
    // no right child
    else{
        while((current_->getParent() != nullptr) && (current_->getParent()->getLeft() != current_)){
            current_ = current_->getParent();
        }
        current_ = current_->getParent();
    }
    return (*this);
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() : root_(nullptr)
{
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    Node<Key, Value> *nnode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);

    bool left = 0;
    Node<Key, Value> *temp_node = root_;
    Node<Key, Value> *temp_parent = nullptr;
    if(empty()){
        root_ = nnode;
        temp_node = root_;
    } else{
        while(temp_node != nullptr){
            if(temp_node->getKey() < nnode->getKey()){
                temp_parent = temp_node;
                temp_node = temp_node->getRight();
                left = 0;
            } else if(temp_node->getKey() > nnode->getKey()){
                temp_parent = temp_node;
                temp_node = temp_node->getLeft();
                left = 1;
            } else{
                temp_node->setValue(nnode->getValue());
                delete nnode;
                return;
            }
        }
        // pointers
        temp_node = nnode;
        temp_node->setParent(temp_parent);
        temp_node->setRight(nullptr);
        temp_node->setLeft(nullptr);
        if(left){
            temp_parent->setLeft(temp_node);
        } else{
            temp_parent->setRight(temp_node);
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value> *rnode = internalFind(key);
    if(rnode == nullptr){
        return;
    }

    // two Children
    if((rnode->getLeft() != nullptr) && (rnode->getRight() != nullptr)){
        Node<Key, Value> *pre = predecessor(rnode);
        if(rnode->getParent() == nullptr){
            nodeSwap(pre, rnode);
            root_ = pre;
        } else {
            nodeSwap(pre, rnode);
        } 
    }

    // Zero Children
    if((rnode->getLeft() == nullptr) && (rnode->getRight() == nullptr)){
        // root node
        if(rnode == root_){
            root_ = nullptr;
        } else if(rnode->getParent()->getLeft() == rnode){
          // left node
            rnode->getParent()->setLeft(nullptr);
        } else if(rnode->getParent()->getRight() == rnode){
          // right node
            rnode->getParent()->setRight(nullptr);
        }
        delete rnode;  
    } else if((rnode->getLeft() == nullptr) || (rnode->getRight() == nullptr)){
        // one child
        // root node
        if(rnode == root_){
            // has a right child
            if(rnode->getRight() != nullptr){
                root_ = rnode->getRight();
                root_->setParent(nullptr);
            } else if(rnode->getLeft() != nullptr){
              // left 
                root_ = rnode->getLeft();
                root_->setParent(nullptr);
            }
        } else if(rnode->getParent()->getLeft() == rnode){
            // left child 
            // has left child
            if(rnode->getLeft() != nullptr){
                rnode->getParent()->setLeft(rnode->getLeft());  
                rnode->getLeft()->setParent(rnode->getParent()); 
            } else if(rnode->getRight() != nullptr){
              // right
                rnode->getParent()->setLeft(rnode->getRight());  
                rnode->getRight()->setParent(rnode->getParent()); 
            }
        } else if(rnode->getParent()->getRight() == rnode){
            // right child
            // has left child
            if(rnode->getLeft() != nullptr){
                rnode->getParent()->setRight(rnode->getLeft()); 
                rnode->getLeft()->setParent(rnode->getParent()); 
            } else if(rnode->getRight() != nullptr){
              // right
                rnode->getParent()->setRight(rnode->getRight());  
                rnode->getRight()->setParent(rnode->getParent());
            }
        }
        delete rnode;
    }
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current) {
    if (current == nullptr) {
      return nullptr;
    }
    // right most of left 
    if (current->getLeft() != nullptr) {
        Node<Key, Value>* p = current->getLeft();
        while (p->getRight() != nullptr) {
            p = p->getRight();
        }
        return p;
    }
    // left most in right
    Node<Key, Value>* parent = current->getParent();
    while ((parent != nullptr) && (current == parent->getLeft())) {
        current = parent;
        parent = parent->getParent();
    }
    return parent;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clear(root_);
    root_ = nullptr;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value> *temp_node = root_;
    if(root_ == nullptr){
        return nullptr;
    }
    while(temp_node->getLeft() != nullptr){
        temp_node = temp_node -> getLeft();
    }
    return temp_node;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value> *temp_node = root_;
    if(!empty()){
        while(temp_node != nullptr){
          if(temp_node->getKey() == key){
                return temp_node;
          }
          if(temp_node->getKey() > key){
            temp_node = temp_node->getLeft();
          } else if(temp_node->getKey() < key){
              temp_node = temp_node->getRight();
          }
        }
    }
    return nullptr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    int h = 1;
    return isBalancedHelper(root_, h);
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);
    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear(Node<Key, Value>* node_to_delete){
    //Base Case
    if(node_to_delete == nullptr){
        return;
    }
    clear(node_to_delete->getLeft());
    clear(node_to_delete->getRight());
    delete node_to_delete;
    node_to_delete = nullptr;
}

//Helper function for isBalanced recursion
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* node, int& h) const{
    if(node == nullptr){
        return true;
    }
    int l = h + 1;
    int r = h + 1;
    bool bl = isBalancedHelper(node->getLeft(), l);
    bool br = isBalancedHelper(node->getRight(), r);
    h = std::max(l, r);
    return (bl && br && (abs(l-r) < 2));
}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
