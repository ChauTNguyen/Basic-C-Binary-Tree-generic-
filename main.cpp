// http://math.hws.edu/eck/cs225/s03/binary_trees/
//https://en.wikipedia.org/wiki/Tree_traversal

#include <iostream>
#include <queue>

template<typename T>
struct TreeNode {
    T item;
    TreeNode *left;
    TreeNode *right;

    TreeNode(T newItem, TreeNode *newLeft, TreeNode *newRight)
            : item(newItem), left(newLeft), right(newRight) { }

    TreeNode(T newItem)
            : item(newItem), left(nullptr), right(nullptr) { }

    bool hasLeft() {
        if (left != nullptr) return true;
        else return false;
    }

    bool hasRight() {
        if (right != nullptr) return true;
        else return false;
    }

    void setLeft(TreeNode<T> *o) {
        left = o;
    }

    void setRight(TreeNode<T> *o) {
        right = o;
    }
};

template<typename T>
int countNodes(TreeNode<T> *root);

template<typename T>
void preorderPrint(TreeNode<T> *root);

template<typename T>
void postorderPrint(TreeNode<T> *root);

template<typename T>
void inorderPrint(TreeNode<T> *root);

template<typename T>
void levelOrderPrint(TreeNode<T> *root);

template<typename T>
bool binaryTreeSearch(TreeNode<T> *root, T key);

template<typename T>
void insert(TreeNode<T> *root, T value);

int main() {
    // preorderPrint
    TreeNode<int> *n1 = new TreeNode<int>(5, nullptr, nullptr);
    std::cout << "n1.item = " << n1->item << std::endl;

    n1->left = new TreeNode<int>(2, nullptr, nullptr);
    n1->left->left = new TreeNode<int>(0, nullptr, nullptr);
    n1->left->right = new TreeNode<int>(9, nullptr, nullptr);
    n1->left->left->left = new TreeNode<int>(12, nullptr, nullptr);

    n1->right = new TreeNode<int>(3, nullptr, nullptr);
    n1->right->left = new TreeNode<int>(4, nullptr, nullptr);
    n1->right->right = new TreeNode<int>(5, nullptr, nullptr);

    std::cout << n1->left->item << std::endl;
    std::cout << "Number of Nodes = " << countNodes(n1) << std::endl;

    // Print the tree through three different traversals.
    preorderPrint(n1);
    std::cout << std::endl;
    postorderPrint(n1);
    std::cout << std::endl;
    inorderPrint(n1);
    std::cout << std::endl;
    levelOrderPrint(n1);
    std::cout << std::endl;

    // Inorder traversal should print this properly...
    TreeNode<int> *binaryTreeRoot = new TreeNode<int>(
            4,
            new TreeNode<int>(2, new TreeNode<int>(1, nullptr, nullptr), new TreeNode<int>(3, nullptr, nullptr)),
            new TreeNode<int>(6,
                              new TreeNode<int>(5, nullptr, nullptr),
                              new TreeNode<int>(9, new TreeNode<int>(7, nullptr, nullptr),
                                                new TreeNode<int>(10, nullptr, nullptr)))
    );

    inorderPrint(binaryTreeRoot);
    std::cout << std::endl;
    std::cout << "Find 1; Expect True: " << std::boolalpha << binaryTreeSearch<int>(binaryTreeRoot, 1) << std::endl;
    std::cout << "Find 2; Expect True: " << std::boolalpha << binaryTreeSearch<int>(binaryTreeRoot, 2) << std::endl;
    std::cout << "Find 4; Expect True: " << std::boolalpha << binaryTreeSearch<int>(binaryTreeRoot, 4) << std::endl;
    std::cout << "Find 5; Expect True: " << std::boolalpha << binaryTreeSearch<int>(binaryTreeRoot, 5) << std::endl;
    std::cout << "Find 7; Expect False: " << std::boolalpha << binaryTreeSearch<int>(binaryTreeRoot, 7) << std::endl;
    std::cout << "Find 9; Expect True: " << std::boolalpha << binaryTreeSearch<int>(binaryTreeRoot, 9) << std::endl;
    std::cout << "Find 10; Expect True: " << std::boolalpha << binaryTreeSearch<int>(binaryTreeRoot, 10) << std::endl;
    std::cout << "Find 12; Expect False: " << std::boolalpha << binaryTreeSearch<int>(binaryTreeRoot, 12) << std::endl;
    std::cout << "Find 13; Expect False: " << std::boolalpha << binaryTreeSearch<int>(binaryTreeRoot, 13) << std::endl;

    TreeNode<std::string> *binaryTreeRootString = new TreeNode<std::string>(
            "Dan",
            new TreeNode<std::string>("Bob", new TreeNode<std::string>("Ace"), new TreeNode<std::string>("Carla")),
            new TreeNode<std::string>("Farah", new TreeNode<std::string>("Emily"), new TreeNode<std::string>("Garlik"))
    );

    std::cout << std::endl;
    inorderPrint(binaryTreeRootString);
    std::cout << std::endl;
    std::cout << "Find Ace; Expect True: " << std::boolalpha <<
    binaryTreeSearch<std::string>(binaryTreeRootString, "Ace") << std::endl;
    std::cout << "Find Bob; Expect True: " << std::boolalpha <<
    binaryTreeSearch<std::string>(binaryTreeRootString, "Bob") << std::endl;
    std::cout << "Find Jessica; Expect False: " << std::boolalpha <<
    binaryTreeSearch<std::string>(binaryTreeRootString, "Jessica") << std::endl;

    std::cout << std::endl;
    insert<std::string>(binaryTreeRootString, "Jenkins");
    inorderPrint(binaryTreeRootString);
    std::cout << std::endl;
    insert<std::string>(binaryTreeRootString, "Azer");
    inorderPrint(binaryTreeRootString);
    std::cout << std::endl;
    insert<std::string>(binaryTreeRootString, "Jacobs");
    inorderPrint(binaryTreeRootString);
    return 0;
}

template<typename T>
int countNodes(TreeNode<T> *root) {
    if (root == nullptr) {
        return 0;
    } else {
        int count = 1;
        count += countNodes(root->left);
        count += countNodes(root->right);
        return count;
    }
}

/*
 * Prints all the items in the tree to which root points.
 *
 * The item in the root is printed first, followed by the
 * items in the left subtree (all left elements first)
 * and then the items in the right tree (all the left elements first).
 *
 * For example:
 * In the preorderPrint test case above, the tree is structured as follows:
 *            5
 *          2   3
 *         0 9 4 5
 *      12
 *
 * The way preorderPrint will then work is as follows:
 * Print root: 5
 * preorderPrint(root->left)
 * Print 2, then 0, then 12. These are all the leftmost elements and will be accessed first
 * because of our recursive implementation.
 * Print 9 because the function then starts printing the right elements
 * (preorderPrint(root->right)).
 *
 * The entire recursive process for root->left is now done so now
 * preorderPrint(root->right) will execute and print
 * 3 4 5.
 */
template<typename T>
void preorderPrint(TreeNode<T> *root) {
    if (root != nullptr) {
        std::cout << root->item << " ";
        preorderPrint(root->left);
        preorderPrint(root->right);
    }
}

/*
 * Print all the items in the tree to which root points.
 *
 * The items in the left subtree are printed first, followed
 * by the items in the right subtree and then the item in the
 * root node.
 *
 * Because the print statement is now at the end, the root node will always be
 * printed last. However, this also has a lot of other effects.
 * Because postorderPrint(root->left) is first in the function, we will always move
 * to the lowest leftmost node before printing (it also checks if that root has its own children
 * too before switching back). We then revert back to the stack before (the ancestor of that root),
 * and then execute postorderPrint(root->right) to access the right child.
 *
 * After accessing all the lower elements, we go back up print that go back up print that.
 *
 * After all that is settled, we're back at the top level where we now access
 * postorderPrint(root->right) to access the main right tree and we repeat the same process
 * we went through in the main left tree.
 *
 * Eventually we print the root element's data and we're done.
 */
template<typename T>
void postorderPrint(TreeNode<T> *root) {
    if (root != nullptr) {
        postorderPrint(root->left);
        postorderPrint(root->right);
        std::cout << root->item << " ";
    }
}

/*
 * Print all the items in the tree to which root points.
 *
 * The items in the left subtree are printed first, followed by the item in the
 * root node, followed by the items in the right tree.
 *
 * Because the print statement is now in the middle, the order of printing changes
 * significantly once again. Firstly, we access the lowest leftmost element and print that
 * (we're ignoring the nullptr cases), then after the stack settles we move back to the parent
 * of the lowest element, print that, and access the right subtree through inorderPrint(root->right)
 * and repeat (print lowest left elements, then the parent, then the right).
 *
 * After the left tree is processed, we print the root element's data, access the right tree,
 * and repeat.
 */
template<typename T>
void inorderPrint(TreeNode<T> *root) {
    if (root != nullptr) {
        inorderPrint(root->left);
        std::cout << root->item << " ";
        inorderPrint(root->right);
    }
}

// bft
template<typename T>
void levelOrderPrint(TreeNode<T> *root) {
    std::queue<TreeNode<T> *> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode<T> *curr = q.front();
        q.pop();
        if (curr != nullptr) {
            std::cout << curr->item << " ";
            q.push(curr->left);
            q.push(curr->right);
        }
    }
}

template<typename T>
bool binaryTreeSearch(TreeNode<T> *root, T key) {
    TreeNode<T> *curr = root;

    while (curr != nullptr) {
        if (curr->item == key) return true;
        else if (key < curr->item) curr = curr->left;
        else curr = curr->right;
    }

    return false;
}

template<typename T>
void insert(TreeNode<T> *root, T value) {
    TreeNode<T> *curr = root;

    if (binaryTreeSearch(root, value)) {
        std::cout << "Duplicate value." << std::endl;
    } else {
        while ((value < curr->item && curr->hasLeft()) ||
                (value > curr->item && curr->hasRight())) {
            if (value < curr->item) curr = curr->left;
            else curr = curr->right;
        }
    }

    if (value > curr->item) curr->setRight(new TreeNode<T>(value));
    else curr->setLeft(new TreeNode<T>(value));
}

