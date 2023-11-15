#include <stdlib.h>
#include <stdio.h>


struct IntegerStack{
    int size;
    int limit;
    int *collection;
    void (*print)(struct IntegerStack*);
    int (*pop)(struct IntegerStack*);
    void (*push)(struct IntegerStack*, int);
    int (*peek)(struct IntegerStack*);
};


void destroy_IntegerStack( struct IntegerStack* obj){
    if (obj){
        free(obj);
    }
}


int peek_IntegerStack(struct IntegerStack* s){
    if( s -> size <= 0){
        printf("Error on IntegerStack peek: Stack has no elements!");
        exit(1);
    }
    return s -> collection[s -> size - 1];
}


void push_IntegerStack(struct IntegerStack* s, int new_item){
    s -> collection[s -> size] = new_item;
    s -> size = s -> size + 1;
    if(s -> size == s -> limit - 1){
        s -> limit = s -> limit * 2;
        s -> collection = realloc(s -> collection, s -> limit);
    }
}


int pop_IntegerStack(struct IntegerStack* s){
    if( s -> size <= 0){
        printf("Error on IntegerStack pop: Stack has no elements!");
        exit(1);
    }
    s -> size = s -> size - 1;
    return s -> collection[s -> size];
}


void print_IntegerStack(struct IntegerStack* s){
    printf("___ Bottom ___\n");
    for(int i = 0; i < s -> size; i++){
        printf("  %d \n",s -> collection[i]);
    }
    printf("___  Top   ___ \n");
}


struct IntegerStack* create_IntegerStack(int new_size){
    struct IntegerStack* newStack = (struct IntegerStack*)malloc(new_size * sizeof( struct IntegerStack));
    if (newStack){
        newStack -> limit = new_size;
        newStack -> size = 0;
        newStack -> collection = (int*) malloc(new_size * sizeof(int));
        newStack -> print = print_IntegerStack;
        newStack -> peek = peek_IntegerStack;
        newStack -> pop = pop_IntegerStack;
        newStack -> push = push_IntegerStack;
    }
    return newStack;
}


int main(){
    struct IntegerStack* test_stack = create_IntegerStack(5);

    //printf("%d", test_stack -> limit);
    //push_IntegerStack(test_stack,3);
    test_stack -> push(test_stack, 3);
    //push_IntegerStack(test_stack,10);
    test_stack -> push(test_stack, 10);
    //push_IntegerStack(test_stack,4);
    test_stack -> push(test_stack, 4);
    printf("Limit: %d \n",test_stack->limit);
    printf("Size: %d \n",test_stack->size);
    //push_IntegerStack(test_stack,20);
    test_stack -> push(test_stack, 20);
    printf("Limit: %d \n",test_stack->limit);
    printf("Size: %d \n",test_stack->size);
    printf("Peeking: %d \n",test_stack -> peek(test_stack) /*peek_IntegerStack(test_stack)*/);

    //push_IntegerStack(test_stack,30);
    test_stack -> push(test_stack, 30);
    printf("Limit: %d \n",test_stack->limit);
    printf("Size: %d \n",test_stack->size);
    //push_IntegerStack(test_stack,50);
    test_stack -> push(test_stack,50);
    printf("Limit: %d \n",test_stack->limit);
    printf("Size: %d \n",test_stack->size);
    //print_IntegerStack(test_stack);
    test_stack -> print(test_stack);

    printf("Peeking: %d \n", test_stack -> peek(test_stack)/*peek_IntegerStack(test_stack)*/);
    printf("Popping: %d \n", test_stack -> pop(test_stack)/*pop_IntegerStack(test_stack)*/);
    print_IntegerStack(test_stack);
    printf("Popping: %d \n", test_stack -> pop(test_stack)/*pop_IntegerStack(test_stack)*/);
    printf("Popping: %d \n", test_stack -> pop(test_stack)/*pop_IntegerStack(test_stack)*/);
    printf("Popping: %d \n", test_stack -> pop(test_stack)/*pop_IntegerStack(test_stack)*/);
    printf("Popping: %d \n", test_stack -> pop(test_stack)/*pop_IntegerStack(test_stack)*/);
    printf("Popping: %d \n", test_stack -> pop(test_stack)/*pop_IntegerStack(test_stack)*/);
    printf("Popping: %d \n", test_stack -> pop(test_stack)/*pop_IntegerStack(test_stack)*/);

    destroy_IntegerStack(test_stack);
    return 0;
}
