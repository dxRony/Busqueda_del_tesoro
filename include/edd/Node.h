#ifndef NODE_H
#define NODE_H

// Definición de la plantilla de la clase Node
template<typename T>
class Node {
private:
    T data;
    Node<T> *next;
    Node<T> *prev;
    Node<T> *up;
    Node<T> *down;
    Node<T> *left;
    Node<T> *right;

public:
    // Constructor
    explicit Node(const T data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
        up = nullptr;
        down = nullptr;
        left = nullptr;
        right = nullptr;
    }

    // Destructor
    ~Node() {
    }

    // Getters
    T getData() const {
        return data;
    }

    Node<T> *getNext() const {
        return next;
    }

    Node<T> *getPrev() const {
        return prev;
    }

    Node<T> *getUp() const {
        return up;
    }

    Node<T> *getDown() const {
        return down;
    }

    Node<T> *getLeft() const {
        return left;
    }

    Node<T> *getRight() const {
        return right;
    }

    // Setters
    void setData(const T data) {
        this->data = data;
    }

    void setNext(Node<T> *next) {
        this->next = next;
    }

    void setPrev(Node<T> *prev) {
        this->prev = prev;
    }

    void setUp(Node<T> *up) {
        this->up = up;
    }

    void setDown(Node<T> *down) {
        this->down = down;
    }

    void setLeft(Node<T> *left) {
        this->left = left;
    }

    void setRight(Node<T> *right) {
        this->right = right;
    }
};

#endif // NODE_H
