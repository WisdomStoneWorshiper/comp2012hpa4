#ifndef AVL_H
#define AVL_H

#include "vertex.h"
#include <list>
class AVL;

struct AVLNode
{
    list<Vertex *> content;
    int distance;
    int height;
    AVLNode *left;
    AVLNode *right;
    AVLNode(Vertex *v, const int &d) : distance(d), height(0)
    {
        content.push_back(v);
        left = nullptr;
        right = nullptr;
    }
};

class AVL
{
public:
    AVL();
    ~AVL();
    void insert(Vertex *, const int &);
    void remove(Vertex *, const int &);
    Vertex *removeShortest();
    bool is_empty();

private:
    AVLNode *root{nullptr};
    int height(AVLNode *);
    int balanceFactor(AVLNode *);
    void calcalateHeight(AVLNode *);
    AVLNode *rotateLeft(AVLNode *);
    AVLNode *rotateRight(AVLNode *);
    AVLNode *balance(AVLNode *);
    AVLNode *insert(AVLNode *, Vertex *, const int &);
    AVLNode *remove(AVLNode *, Vertex *, const int &);
    AVLNode *findMin(AVLNode *);
    AVLNode *removeMin(AVLNode *);
};

#endif // AVL_H
