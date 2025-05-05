#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    if (new == NULL) return NULL;
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return;
    TreeNode * aux = tree->root;
    TreeNode * parent = NULL;
    while (aux != NULL)
    {
        parent = aux;
        if (tree->lower_than(key, aux->pair->key) == 0 && tree->lower_than(aux->pair->key, key) == 0) return;
        if (tree->lower_than(key, aux->pair->key)) aux = aux->left;
        else aux = aux->right;
    }
    TreeNode * new = createTreeNode(key, value);
    if (new == NULL) return;
    new->parent = parent;
    if (parent == NULL)
    {
        tree->root = new;
    }
    else if (tree->lower_than(key, parent->pair->key))
    {
        parent->left = new;
    }
    else parent->right = new;
    tree->current = new;

}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;
    while (x->left != NULL) x = x->left;
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (tree == NULL || node == NULL) return;
    if (node->left == NULL && node->right == NULL)
    {
        if (node->parent == NULL) tree->root = NULL;
        else if (node->parent->left == node) node->parent->left = NULL;
        else node->parent->right = NULL;
        free(node);
    }
    else if (node->left == NULL || node->right == NULL)
    {
        TreeNode* child = (node->left != NULL) ? node->left : node->right;
        child->parent = node->parent;
        if (node->parent == NULL) tree->root = child;
        else if (node->parent->left == node) node->parent->left = child;
        else node->parent->right = child;
        free(node);
    }
    else
    {
        TreeNode* minRight = minimum(node->right);
        node->pair->key = minRight->pair->key;
        node->pair->value = minRight->pair->value;
        removeNode(tree, minRight);
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * current = tree->root;
    while (current != NULL)
    {
        if (tree->lower_than(key, current->pair->key) == 0 && tree->lower_than(current->pair->key, key) == 0)
        {
            tree->current = current;
            return current-> pair;
        }
        if (tree->lower_than(key, current->pair->key)) current = current->left;
        else current = current->right;
    }


    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
