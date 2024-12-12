#ifndef KEYVALUEARBOLAVL_HPP
#define KEYVALUEARBOLAVL_HPP

#include <stdexcept> // For std::out_of_range
#include <iostream>  // For std::cout
#include <vector>    // For std::vector


template <typename Key, typename Value>
struct KeyValueAVLNode
{
    Key key;                /**< The key of the node. */
    Value value;            /**< The value of the node. */
    int height;             /**< The height of the node. */
    KeyValueAVLNode *left;  /**< Pointer to the child node on the left side. */
    KeyValueAVLNode *right; /**< Pointer to the child node on the right side.
                             */
    
    
    KeyValueAVLNode(const Key &k, const Value &v)
    {
        key = k;
        value = v;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
    
    
    KeyValueAVLNode(Key &&k, Value &&v)
    {
        key = std::move(k);
        value = std::move(v);
        left = nullptr;
        right = nullptr;
    }
};


template <typename Key, typename Value>
class KeyValueAVLTree
{
public:
    /**
     * Constructs an empty search tree.
     */
    KeyValueAVLTree() = default;
    
    
    KeyValueAVLTree(KeyValueAVLNode<Key, Value> *r)
    {
        root_ = r;
    }
    /**
     * Class destructor.
     */
    ~KeyValueAVLTree()
    {
        clear();
    }
    
    
    const KeyValueAVLNode<Key, Value> *root() const
    {
        return root_;
    }
    
    
    unsigned long long size() const
    {
        return size(root_);
    }
    
    
    const KeyValueAVLNode<Key, Value> *find_min() const
    {
        return find_min(root_);
    }
    
    
    const KeyValueAVLNode<Key, Value> *find_max() const
    {
        return find_max(root_);
    }
    /**
     * Clears the AVL tree.
     */
    void clear()
    {
        clear(root_);
        root_ = nullptr;
    }
    
    
    KeyValueAVLNode<Key, Value> *find(const Key &key) const
    {
        return find(root_, key);
    }
    
    
    void insert(const Key &key, const Value &value)
    {
        root_ = insert(root_, key, value);
    }
    /**
     * Erases the node with the specified key from the AVL tree.
     *
     * @param[in] key The key to delete.
     */
    void erase(const Key &key)
    {
        root_ = erase(root_, key);
    }
    /**
     * Prints the contents of the AVL tree in preorder.
     */
    void print_preorder() const
    {
        print_preorder(root_);
    }
    /**
     * Prints the contents of the AVL tree in inorder.
     */
    void print_inorder() const
    {
        print_inorder(root_);
    }
    /**
     * Prints the contents of the AVL tree in postorder.
     */
    void print_postorder() const
    {
        print_postorder(root_);
    }
    /**
     * Prints the AVL tree in a graphical way.
     */
    void print_tree() const
    {
        print_tree(root_);
    }
    
    
    std::vector<std::pair<Key, Value>> preorder_traversal() const
    {
        std::vector<std::pair<Key, Value>> res;
        preorder_traversal(root_, res);
        return res;
    }
    
    
    std::vector<std::pair<Key, Value>> inorder_traversal() const
    {
        std::vector<std::pair<Key, Value>> res;
        inorder_traversal(root_, res);
        return res;
    }
    
    
    std::vector<std::pair<Key, Value>> postorder_traversal() const
    {
        std::vector<std::pair<Key, Value>> res;
        postorder_traversal(root_, res);
        return res;
    }

private:
    
    
    unsigned long long size(KeyValueAVLNode<Key, Value> *node) const
    {
        if (node == nullptr)
            return 0;
        return 1 + size(node->left) + size(node->right);
    }
    
    
    void clear(KeyValueAVLNode<Key, Value> *node)
    {
        if (node == nullptr)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
    
    int height(KeyValueAVLNode<Key, Value> *node) const
    {
        return node ? node->height : 0;
    }
    
    
    void update_height(KeyValueAVLNode<Key, Value> *node)
    {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
    
    
    int calculate_balance_factor(KeyValueAVLNode<Key, Value> *node) const
    {
        return node ? height(node->right) - height(node->left) : 0;
    }
    
    
    
    KeyValueAVLNode<Key, Value> *find_min(KeyValueAVLNode<Key, Value> *node) const
    {
        if (node == nullptr)
            throw std::out_of_range("The tree is empty.");
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    
    
    KeyValueAVLNode<Key, Value> *find_max(KeyValueAVLNode<Key, Value> *node) const
    {
        if (node == nullptr)
            throw std::out_of_range("The tree is empty.");
        while (node->right != nullptr)
            node = node->right;
        return node;
    }
    
    
    KeyValueAVLNode<Key, Value> *find(KeyValueAVLNode<Key, Value> *node, const Key &
                                                                             key) const
    {
        if ((node == nullptr) || (key == node->key))
            return node;
        else if (key < node->key)
            return find(node->left, key);
        else
            return find(node->right, key);
    }
    
    
    KeyValueAVLNode<Key, Value> *insert(KeyValueAVLNode<Key, Value> *node, const Key &key, const Value &value)
    {
        if (node == nullptr)
            node = new KeyValueAVLNode<Key, Value>(key, value);
        else if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            return node;
        // Update height and balance the node
        update_height(node);
        return balance(node);
    }
    
    
    KeyValueAVLNode<Key, Value> *erase(KeyValueAVLNode<Key, Value> *node, const Key &key)
    {
        if (node == nullptr)
            return node;
        if (key < node->key)
        {
            node->left = erase(node->left, key); // The key is in the left subtree
        }
        else if (key > node->key)
        {
            node->right = erase(node->right, key); // The key is in the right subtree
        }
        else
        {
            if (node->left == nullptr || node->right == nullptr)
            {
                // The node has one child or no children
                KeyValueAVLNode<Key, Value> *temp = node->left ? node->left : node -> right;
                delete node;
                return temp;
            }
            else
            {
                // The node has two children
                KeyValueAVLNode<Key, Value> *temp = find_max(node->left);
                node->key = temp->key;
                node->value = temp->value;
                node->left = erase(node->left, temp->key);
            }
        }
        // Update height and balance the node
        update_height(node);
        return balance(node);
    }
    
    
    KeyValueAVLNode<Key, Value> *rotate_left(KeyValueAVLNode<Key, Value> *node)
    {
        KeyValueAVLNode<Key, Value> *newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        // Update heights
        update_height(node);
        update_height(newRoot);
        return newRoot;
    }
    
    
    KeyValueAVLNode<Key, Value> *rotate_right(KeyValueAVLNode<Key, Value> *node)
    {
        KeyValueAVLNode<Key, Value> *newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        // Update heights
        update_height(node);
        update_height(newRoot);
        return newRoot;
    }
    
    
    KeyValueAVLNode<Key, Value> *rotate_left_right(KeyValueAVLNode<Key, Value> *
                                                       node)
    {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    
    
    KeyValueAVLNode<Key, Value> *rotate_right_left(KeyValueAVLNode<Key, Value> *
                                                       node)
    {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    
    
    KeyValueAVLNode<Key, Value> *balance(KeyValueAVLNode<Key, Value> *node)
    {
        int bf = calculate_balance_factor(node);
        // Rotation to the left
        if (bf == 2)
        {
            if (calculate_balance_factor(node->right) >= 0)
                return rotate_left(node);
            else
                return rotate_right_left(node);
        }
        // Rotation to the right
        else if (bf == -2)
        {
            if (calculate_balance_factor(node->left) <= 0)
                return rotate_right(node);
            else
                return rotate_left_right(node);
        }
        return node;
    }
    
    
    void print_preorder(KeyValueAVLNode<Key, Value> *node) const
    {
        if (node == nullptr)
            return;
        std::cout << "(" << node->key << ", " << node->value << ") ";
        print_preorder(node->left);
        print_preorder(node->right);
    }
    
    
    void print_inorder(KeyValueAVLNode<Key, Value> *node) const
    {
        if (node == nullptr)
            return;
        print_inorder(node->left);
        std::cout << "(" << node->key << ", " << node->value << ") ";
        print_inorder(node->right);
    }
    
    
    void print_postorder(KeyValueAVLNode<Key, Value> *node) const
    {
        if (node == nullptr)
            return;
        print_postorder(node->left);
        print_postorder(node->right);
        std::cout << "(" << node->key << ", " << node->value << ") ";
    }
    
    
    void print_tree(KeyValueAVLNode<Key, Value> *node, std::string indent = "",
                    bool isRight = true) const
    {
        if (node == nullptr)
            return;
        print_tree(node->right, indent + (isRight ? " " : " | "),
                   true);
        std::cout << indent;
        if (isRight)
        {
            std::cout << " /";
        }
        else
        {
            std::cout << " \\";
        }
        std::cout << "----- ";
        std::cout << "(" << node->key << ", " << node->value << ")" << "(bf=" << calculate_balance_factor(node) << ")" << std::endl;
        print_tree(node->left, indent + (isRight ? " | " : " "),
                   false);
    }
    
    
    void preorder_traversal(KeyValueAVLNode<Key, Value> *node,
                            std::vector<std::pair<Key, Value>> &traversal) const
    {
        if (node == nullptr)
            return;
        traversal.push_back(std::make_pair(node->key, node->value));
        preorder_traversal(node->left, traversal);
        preorder_traversal(node->right, traversal);
    }
    
    
    void inorder_traversal(KeyValueAVLNode<Key, Value> *node,
                           std::vector<std::pair<Key, Value>> &traversal) const
    {
        if (node == nullptr)
            return;
        inorder_traversal(node->left, traversal);
        traversal.push_back(std::make_pair(node->key, node->value));
        inorder_traversal(node->right, traversal);
    }
    
    
    void postorder_traversal(KeyValueAVLNode<Key, Value> *node,
                             std::vector<std::pair<Key, Value>> &traversal) const
    {
        if (node == nullptr)
            return;
        postorder_traversal(node->left, traversal);
        postorder_traversal(node->right, traversal);
        traversal.push_back(std::make_pair(node->key, node->value));
    }
    KeyValueAVLNode<Key, Value> *root_{nullptr}; /**< Pointer to the root node
  of the AVL tree. */
};
#endif