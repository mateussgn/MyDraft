#include <stdio.h>
#include <stdlib.h>

#define DONT_FIND "Data tidak ada"

//montar avore AVL depois percorrer a partir do menor valor em um nó até achar o nó procurado
//e retornar o indice desse nó caso ele estivesse em uma lista ordenada crescentemente

typedef struct node {
    int key_node;
    int height;
    struct node *left_node;
    struct node *right_node;
} TREE_NODE;

TREE_NODE *create_node(TREE_NODE *new_node, int key){
    new_node = (TREE_NODE *) malloc (sizeof(TREE_NODE));
    new_node->key_node = key;
    new_node->left_node = NULL;
    new_node->right_node = NULL;
    return new_node;
}

int height(TREE_NODE *root){
    if(root == NULL)
        return -1;
    else
        return root->height;
}

int max_height(int left_height, int right_height){
    if(left_height > right_height)
        return left_height;
    else
        return right_height;
}

int balanceAVL(TREE_NODE *root){
    if(root == NULL)
        return 0;
    else
        return height(root->left_node) - height(root->right_node);
}

TREE_NODE *rightRotate(TREE_NODE *root){
    TREE_NODE *left = root->left_node;
    TREE_NODE *leftRight = left->right_node;
    left->right_node = root;
    root->left_node = leftRight;
    root->height = max_height(height(root->left_node), height(root->right_node)) + 1;
    left->height = max_height(height(left->left_node),height(left->right_node)) + 1;
    return left;
}

TREE_NODE *leftRotate(TREE_NODE *root){
    TREE_NODE *right = root->right_node;
    TREE_NODE *rightLeft = right->left_node;
    right->left_node = root;
    root->right_node = rightLeft;
    root->height = max_height(height(root->left_node), height(root->right_node)) + 1;
    right->height = max_height(height(right->left_node),height(right->right_node)) + 1;
    return right;
}

TREE_NODE *AVL_insert_node(TREE_NODE *root, int key){
    int balance_factor = 0;
    if(root == NULL){
        return create_node(root);
    }else if(root->key_node > key   )
        root->left_node = AVL_insert_node(root->left_node, key);
    else
        root->right_node = AVL_insert_node(root->right_node, key);

    root->height = 1 + max_height(height(root->left_node), height(root->right_node));
    balance_factor = balanceAVL(root);
    if((balance_factor > 1) && (key < root->left_node->key_node))
        return rightRotate(root);
    if((balance_factor < -1) && (key >= root->right_node->key_node))
        return leftRotate(root);
    if((balance_factor > 1) && (key >= root->left_node->key_node)){
        root->left_node = leftRotate(root->left_node);
        return rightRotate(root);
    }
    if((balance_factor < -1) && (key < root->right_node->key_node)){
        root->right_node = rightRotate(root->right_node);
        return leftRotate(root);
    }
    return root;
}

void inOrderThree(TREE_NODE *root, int in[], int i){
    i++;
    if(root != NULL){
        inOrderThree(root->right_node, in, i);
        in[i] = root->key_node;
        inOrderThree(root->left_node, in, i);
    }
}

int main() {
    int i = 0,
        number_of_queries = 0,
        include1_search2 = 0,
        values[] = {0};
    TREE_NODE *root_node = NULL;

    scanf("%d", &number_of_queries);
    for(i = 0; i < number_of_queries; i++){
        scanf("%d %d", &include1_search2, values[i]);
        if(include1_search2 == 1){
            //inserir values[i] na arvore avl
            root_node = AVL_insert_node(root_node, values[i]);
        } else{
            //procurar valor na arvore avl
            printf(DONT_FIND"\n");
        }

    }
    return 0;
}