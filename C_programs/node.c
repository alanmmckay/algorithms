#include <stdlib.h>
#include <stdio.h>

struct IntegerNode {
    int data;
    struct IntegerNode *next;
    void (*set_next)(struct IntegerNode*, struct IntegerNode*);
    struct IntegerNode* (*get_next)(struct IntegerNode*);
    void (*set_data)(struct IntegerNode*, int);
    int (*get_data)(struct IntegerNode*);
};

void set_next_IntegerNode(struct IntegerNode* this, struct IntegerNode* new_node){
    this -> next = new_node;
}

struct IntegerNode* get_next_IntegerNode(struct IntegerNode* this){
    return this -> next;
}

void set_data_IntegerNode(struct IntegerNode* this, int new_data){
    this -> data = new_data;
}

int get_data_IntegerNode(struct IntegerNode* this){
    return this -> data;
}

struct IntegerNode* create_IntegerNode(int new_data){
    struct IntegerNode* newNode = (struct IntegerNode*)malloc(sizeof( struct IntegerNode));
    if (newNode){
        newNode -> data = new_data;
        newNode -> set_next = set_next_IntegerNode;
        newNode -> get_next = get_next_IntegerNode;
        newNode -> set_data = set_data_IntegerNode;
        newNode -> get_data = get_data_IntegerNode;
    }
    return newNode;
}

void destroy_IntegerNode( struct IntegerNode* obj){
    if (obj){
        free(obj);
    }
}

int main(){
    struct IntegerNode* test_node_1 = create_IntegerNode(1);
    struct IntegerNode* test_node_2 = create_IntegerNode(2);
    test_node_1 -> set_next(test_node_1,test_node_2);
    printf("Value for test_node_1's next: %d \n", test_node_1 -> next -> data);
    test_node_2 -> set_data(test_node_2, 3);
    printf("New value for test_node_2: %d \n", test_node_1 -> next -> data);
    struct IntegerNode* next_node = test_node_1 -> get_next(test_node_1);
    printf("Value for test_node_1's next: %d \n", next_node -> get_data(next_node));

    destroy_IntegerNode(test_node_1);
    destroy_IntegerNode(test_node_2);
    //destroy_IntegerNode(next_node); //Unneeded - next_node **is** test_node_2!
    return 0;
}
