//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA8
// Dictionary.cpp
// Implementation file for Dictionary ADT
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

#define BLACK 0
#define RED 1

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R != nil){
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    // iterate until nil is hit, recursively call for left/right subtrees
    if(R != N){
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    // iterate until nil is hit, recursively call for left/rightsubtrees
    // delete all Nodes
    if(R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    // check for empty tree
    if(R == nil){
        return R;
    }
    // check if current key equals search key
    if(R->key == k){
        return R;
    }
    // if search key is smaller, traverse left
    if(k < R->key){
        return search(R->left, k);
    }
    // if search key is larger, traverse right
    else{
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    // check for empty tree
    if(R == nil){
        return nil;
    }
    // iterate left in the BST until nil encountered
    while(R->left != nil){
        R = R->left;
    }
    // return leftmost node in the subtree
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    // check for empty tree
    if(R == nil){
        return nil;
    }
    // iterate right in the BST until nil encountered
    while(R->right != nil){
        R = R->right;
    }
    // return rightmost node in the subtree
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    // check if N is nil Node
    if(N == nil){
        return nil;
    }
    // check for rightmost Node
    if(N == findMax(root)){
        return nil;
    }
    // check if rightmost Node exists
    if(N->right != nil){
        return findMin(N->right);
    }
    // move up a level in tree
    Node* M = N->parent;
    // check is parent exists and if we came up from right side
    // traverse upward if M has already been visited
    while(M != nil && N == M->right){
        N = M;
        M = M->parent;
    }
    // return the successor
    return M;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    // check if N is nil Node
    if(N == nil){
        return nil;
    }
    // check for leftmost Node
    if(N == findMin(root)){
        return nil;
    }
    // check if leftmost Node exists
    if(N->left != nil){
        return findMax(N->left);
    }
    // move up a level in tree
    Node* M = N->parent;
    // check is parent exists and if we came up from left side
    // traverse upward if M has already been visited
    while(M != nil && N == M->left){
        N = M;
        M = M->parent;
    }
    // return the predecessor
    return M;
}

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    // define arg Node as Node x
    Node*x = N;
    // point to Node x's right child y
    Node* y = x->right;
    x->right = y->left;
    // check if y has a left child
    // if so, set its new parent as x
    if(y->left != nil){
        y->left->parent = x;
    }
    // set y's parent as x's old parent 
    y->parent = x->parent;
    // if x is the root, set y as the root
    if(x->parent == nil){
        root = y;
    }
    // check if x is left child
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    // check if x is right child
    else{
        x->parent->right = y;
    }
    // re-link x as y's left child
    // re-link y as x's parent
    y->left = x;
    x->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
    // define arg Node as Node x
    Node* x = N;
    // point to Node x's left child y
    Node* y = x->left;
    x->left = y->right;
    // check if y has a right child
    // if so, set its new parent as x
    if(y->right != nil){
        y->right->parent = x;
    }
    // set y's parent as x's old parent 
    y->parent = x->parent;
    // if x is the root, set y as the root
    if(x->parent == nil){
        root = y;
    }
    // check if x is left child
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    // check if x is right child
    else{
        x->parent->right = y;
    }
    // re-link x as y's right child
    // re-link y as x's parent
    y->right = x;
    x->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    // check if arg Node's parent is RED which is invalid
    while(N->parent->color == RED){

        // check if parent is a left child 
        if(N->parent == N->parent->parent->left){

            // assign uncle Node
            Node* U = N->parent->parent->right;

            // recolor parent and uncle to BLACK to avoid RED-RED adjacency
            // recolor grandparent to maintain BLACK height
            // move up the tree two levels to check if RED-RED adjacency exists
            if(U->color == RED){
                N->parent->color = BLACK;
                U->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }

            else{
                // check if arg Node is a right child
                // if so, left rotate it to convert triangle into line shape
                if(N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }

                // arg Node is now in line shape
                // recolor parent and grandparent
                // right rotate grandparent to restore tree structure
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }

        // mirror case: check if parent is a right child
        else{

            // assign uncle Node
            Node* U = N->parent->parent->left;

            // recolor parent and uncle to BLACK to avoid RED-RED adjacency
            // recolor grandparent to maintain BLACK height
            // move up the tree two levels to check if RED-RED adjacency exists
            if(U->color == RED){
                N->parent->color = BLACK;
                U->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }

            else{
                // check if arg Node is a left child
                // if so, right rotate it to convert triangle into line shape
                if(N == N->parent->left){
                    N = N->parent;
                    RightRotate(N);
                }

                // arg Node is now in line shape
                // recolor parent and grandparent
                // left rotate grandparent to restore tree structure
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    // set root to BLACK in case algo recolored it
    root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    // check if u is root
    // if so, replace u with v as root
    if(u->parent == nil){
        root = v;
    }
    // check if u is a left child
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    // check if u is a right child
    else{
        u->parent->right = v;
    }
    // set v's parent as u's old parent
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    
}

// RB_Delete()
void RB_Delete(Node* N);

// Class Constructors & Destructors ----------------------------------------

// creates new Node
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
    // sentinel node to represent missing children
    nil = new Node("", 0);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    // sentinel node to represent missing children
    nil = new Node("", 0);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
    // iterate thru arg tree until nil is reached
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete nil;
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    if(search(root, k) != nil){
        return true;
    }
    else{
        return false;
    }
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    // search BST for Node with value k
    Node* N = search(root, k);
    // check for nil Node
    if(N == nil){
        throw std::logic_error("Node containing k not found!");
    }
    // return val associated with k
    return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    if(current != nil){
        return true;
    }
    else{
        return false;
    }
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(hasCurrent()){
        return current->key;
    }
    else{
        throw std::logic_error("Current iterator undefined!");
    }
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(hasCurrent()){
        return current->val;
    }
    else{
        throw std::logic_error("Current iterator undefined!");
    }
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    // search BST for Node with value k
    Node* N = search(root, k);
    // if it exists, overwrite val
    if(N != nil){
        N->val = v;
        return;
    }
    // init traversal pointers
    Node* cur = root;
    Node* par = nil;
    // find insertion location
    // step par down a level, and evaluate cur for traversal direction
    while(cur != nil){
        par = cur;
        if(k < cur->key){
            cur = cur->left;
        }
        else{
            cur = cur->right;
        }
    }
    // create new Node
    Node* ins = new Node(k, v);
    ins->parent = par;
    ins->left = nil;
    ins->right = nil;
    ins->color = RED;
    // check if inserting into empty tree
    if(par == nil){
        root = ins;
    }
    // if non-empty check for insertion left or right
    else if(k < par->key){
        par->left = ins;
    }
    else{
        par->right = ins;
    }
    // increment # of pairs
    num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    // search tree for Node with value k
    Node* N = search(root, k);
    if(N == nil){
        throw std::logic_error("Node containing k not found!");
    }
    // check if current
    if(current == N){
        current = nil;
    }
    // check if leftmost
    if(N->left == nil){
        // check if root
        if(N == root){
            root = N->right;
        }
        // check if on the left 
        else if(N == N->parent->left){
            N->parent->left = N->right;
        }
        // else it is on the right
        else {
            N->parent->right = N->right;
        }
        // reconnect child of Node being deleted to parent of deleted
        if(N->right != nil){
            N->right->parent = N->parent;
        }
    }
    // check if rightmost
    else if(N->right == nil){
        // check if root
        if(N == root){
            root = N->left;
        }
        // check if on the left 
        else if(N == N->parent->left){
            N->parent->left = N->left;
        }
        // else it is on the right 
        else {
            N->parent->right = N->left;
        }
        // reconnect child of Node being deleted to parent of deleted
        if(N->left != nil){
            N->left->parent = N->parent;
        }
    }
    // check if in middle of BST
    else{
        // find successor and overwrite found Node with its info
        Node* S = findMin(N->right);
        N->key = S->key;
        N->val = S->val;
        // check if on the left
        if(S == S->parent->left){
            S->parent->left = S->right;
        }
        // else on the right 
        else {
            S->parent->right = S->right;
        }
        // reconnect child of Node being deleted to parent of deleted
        if(S->right != nil){
            S->right->parent = S->parent;
        }
        // delete successor and decrement # of pairs
        delete S;
        num_pairs--;
        return;
    }
    // delete found Node and decerement # of pairs
    delete N;
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if(root != nil){
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if(root != nil){
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(hasCurrent()){
        current = findNext(current);
    }
    else{
        throw std::logic_error("Next Node undefined!");
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(hasCurrent()){
        current = findPrev(current);
    }
    else{
        throw std::logic_error("Prev Node undefined!");
    }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s;
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s;
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    if(to_string() == D.to_string()){
        return true;
    }
    else{
        return false;
    }
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    stream << D.to_string();
    return stream;
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    if(B.equals(A)){
        return true;
    }
    else{
        return false;
    }
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    // clear contents of input Dictionary
    clear();
    // make copy or arg Dictionary
    Dictionary C = D;         
    // navigate to root
    Node* N = C.findMin(C.root);
    // iterate until nil is hit
    // insert from D into C
    while(N != C.nil){
        setValue(N->key, N->val);
        N = C.findNext(N);
    }
    // return overwritten Dictionary
    return *this;
}