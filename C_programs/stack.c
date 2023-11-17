#include <stdlib.h>
#include <stdio.h>


struct IntegerStack{
    int quantity;
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


int peek_IntegerStack(struct IntegerStack* this){
    if( this -> quantity <= 0){
        printf("Error on IntegerStack peek: Stack has no elements!");
        exit(1);
    }
    return this -> collection[this -> quantity - 1];
}


void push_IntegerStack(struct IntegerStack* this, int new_item){
    this -> collection[this -> quantity] = new_item;
    this -> quantity = this -> quantity + 1;
    if(this -> quantity == this -> limit - 1){
        // !!! Rework !!!
    }
}


int pop_IntegerStack(struct IntegerStack* this){
    if( this -> quantity <= 0){
        printf("Error on IntegerStack pop: Stack has no elements!");
        exit(1);
    }
    this -> quantity = this -> quantity - 1;
    return this -> collection[this -> quantity];
}


void print_IntegerStack(struct IntegerStack* this){
    printf("___ Bottom ___\n");
    for(int i = 0; i < this -> quantity; i++){
        printf("  %d \n",this -> collection[i]);
    }
    printf("___  Top   ___ \n");
}


struct IntegerStack* create_IntegerStack(int new_limit){
    struct IntegerStack* newStack = (struct IntegerStack*)malloc(new_limit * sizeof(struct IntegerStack) );
    if (newStack){
        newStack -> limit = new_limit;
        newStack -> quantity = 0;
        newStack -> collection = (int*)malloc(new_limit * sizeof(int));
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
    printf("Size: %d \n",test_stack->quantity);
    //push_IntegerStack(test_stack,20);
    test_stack -> push(test_stack, 20);
    printf("Limit: %d \n",test_stack->limit);
    printf("Size: %d \n",test_stack->quantity);
    printf("Peeking: %d \n",test_stack -> peek(test_stack) /*peek_IntegerStack(test_stack)*/);

    //push_IntegerStack(test_stack,30);
    test_stack -> push(test_stack, 30);
    printf("Limit: %d \n",test_stack->limit);
    printf("Size: %d \n",test_stack->quantity);
    //push_IntegerStack(test_stack,50);
    test_stack -> push(test_stack,50);
    test_stack -> push(test_stack,51);
    test_stack -> push(test_stack,52);
    test_stack -> push(test_stack,53);
    test_stack -> push(test_stack,54);
    test_stack -> push(test_stack,55);
    test_stack -> push(test_stack,56);
    test_stack -> push(test_stack,57);
    test_stack -> push(test_stack,58);
    test_stack -> push(test_stack,59);
    test_stack -> push(test_stack,60);
    printf("Limit: %d \n",test_stack->limit);
    printf("Size: %d \n",test_stack->quantity);
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
