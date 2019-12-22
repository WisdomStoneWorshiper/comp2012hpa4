#include "avl.h"
#include <QDebug>
AVL::AVL()
{

}

AVL::~AVL(){
    delete root;
}

AVLNode * AVL::rotateLeft(AVLNode * upperleft){
    AVLNode * right=upperleft->right;
    upperleft->right=right->left;
    right->left=upperleft;
    calcalateHeight(upperleft);
    calcalateHeight(right);
    return right;
}

AVLNode * AVL::rotateRight(AVLNode * upperright){
    AVLNode * left=upperright->left;
    upperright->left=left->right;
    left->right=upperright;
    calcalateHeight(upperright);
    calcalateHeight(left);
    return left;
}

int AVL::height(AVLNode * target){
    return target!=nullptr? target->height:-1;
}

void AVL::calcalateHeight(AVLNode * target){
    int lHeight=height(target->left);
    int rHeight=height(target->right);
    target->height=(lHeight>rHeight?lHeight:rHeight)+1;
}



int AVL::balanceFactor(AVLNode * target){
    return height(target->right)-height(target->left);
}

AVLNode * AVL::balance(AVLNode * target){
    calcalateHeight(target);
    if (balanceFactor(target)>=2){
        if (balanceFactor(target->right)<0)
            target->right=rotateRight(target->right);
        return rotateLeft(target);
    }
    if (balanceFactor(target)<=-2){
        if (balanceFactor(target->left)>0)
            target->left=rotateLeft(target->left);
        return rotateRight(target);
    }
    return target;
}

AVLNode * AVL::insert(AVLNode * root, Vertex* target, int d){
    if (root==nullptr)
        return new AVLNode(target,d);
    if (d==root->distance)
        root->content.push_back(target);
    else if (d<root->distance)
        root->left=insert(root->left,target,d);
    else if (d>root->distance){
        root->right=insert(root->right,target,d);
        qDebug()<<"Before balance";
        print();
    }
    return balance(root);
}

void AVL::insert(Vertex * target,int d){
    root=insert(root,target,d);
}

AVLNode * AVL::findMin(AVLNode * root){
    qDebug()<<"findMin:"<<root->distance<<(root->left==nullptr);
    return (root->left==nullptr)?root:findMin(root->left);
}

AVLNode * AVL::removeMin(AVLNode * root){
    if (root->left==nullptr)
        return root->right;
    root->left=removeMin(root->left);
    return balance(root);
}

AVLNode * AVL::remove(AVLNode * root, Vertex* target, int d){
    if (root==nullptr)
        return nullptr;
    if (d<root->distance)
        root->left=remove(root->left,target,d);
    else if (d>root->distance)
        root->right=remove(root->right,target,d);
    else{
        if (root->content.size()>1){
            root->content.remove(target);
            return root;
        }
        else{
            AVLNode* leftSubtree=root->left;
            AVLNode* rightSubtree=root->right;
            //root->content.clear();
            delete root;
            root=nullptr;
            if(rightSubtree==nullptr) return leftSubtree;
            AVLNode* rightSubtreeMin=findMin(rightSubtree);
            rightSubtreeMin->right=removeMin(rightSubtree);
            rightSubtreeMin->left=leftSubtree;
            return balance(rightSubtreeMin);
        }
    }
    return balance(root);
}

void AVL::remove(Vertex *target,int d){
    root=remove(root,target,d);
}

bool AVL::is_empty(){
    return (root==nullptr);
}

Vertex* AVL::removeShortest(){
    //Vertex* temp=findMin(root)->content.front();
    AVLNode* nodeTemp=findMin(root);
    Vertex* vertexTemp=nodeTemp->content.front();
    qDebug()<<"min:"<<nodeTemp->content.front()->getId()<<nodeTemp->distance;
    remove(nodeTemp->content.front(),nodeTemp->distance);
    //removeMin(root);
    return vertexTemp;
}

void AVL::print(AVLNode *target, int depth){
    if (target==nullptr)
        return;
    print(target->right,depth+1);
    QString p;
    for(int j=0; j<depth; j++) // Print the node value
        p=p+'\t';
    p=p+"distance"+QString::number(target->distance)+":";
    for (list<Vertex*>::iterator i= target->content.begin();i!=target->content.end();++i){
        p=p+QString::number((*i)->getId())+" ";
    }
    qDebug()<<p;
    print(target->left, depth+1);
}

void AVL::print(){
    print(root,0);
}
