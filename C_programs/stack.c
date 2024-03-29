#include <stdlib.h>
#include <stdio.h>
#include <malloc.h> //for malloc_usable_size

/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---*/
/* stack.c is an implementation of a stack abstract datatype using an array as
 * the collection object. This implementation uses dynamic memory allocation
 * where the amount of memory allocated is based on the current quantity (size)
 * of the stack. The multiplier used is defined within the push_IntegerStack
 * function.
 *
 * This implementation is also an attempt at supplying basic object-oriented
 * functionality. Method calling and attribute access is present here; an
 * attempt at data encapsulation via the IntegerStack struct. This struct
 * contains storage for a quantity and limit measure in addition to a pointer
 * to an array that acts as the collection of items present. The remaining
 * pointers are to functions that provide the stack its behavior and can be
 * enacted upon as though they were object methods. I.e.,
 *      stack -> pop(stack)
 *      stack -> peek(stack)
 *      stack -> push(stack,val)
 *      stack -> print(stack)
 * Where the first parameter to each of these methods allows for self-reference.
 *
 * The functions create_IntegerStack and destroy_IntegerStack act as a
 * constructor and destructor, respecitvely. The set of test subroutines given
 * in the main method of this file show this 'object' in use! */
//- Alan McKay
/* --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---*/

struct IntegerStack{
    int quantity;
    int limit;
    int *collection;
    void (*print)(struct IntegerStack*);
    int (*pop)(struct IntegerStack*);
    void (*push)(struct IntegerStack*, int);
    int (*peek)(struct IntegerStack*);
};


void destroy_IntegerStack(struct IntegerStack* obj){
    if (obj){
        free(obj);
    }
}


int peek_IntegerStack(struct IntegerStack* this){
    if( this -> quantity <= 0){
        printf("Error on IntegerStack peek: Stack has no elements!");
        exit(1);
    }
    return this -> collection[ this -> quantity - 1];
}


void push_IntegerStack(struct IntegerStack* this, int new_item){
    this -> collection[ this -> quantity] = new_item;
    this -> quantity = ( this -> quantity) + 1;
    if( this -> quantity == this -> limit){
        this -> limit = ( this -> limit) * 1.5;
        int *new_array = (int*)calloc( this->limit, sizeof(int));
        for(int i = 0; i < this->quantity; i++){
            new_array[i] = this -> collection[i];
        }
        this -> collection = new_array;
    }
}


int pop_IntegerStack(struct IntegerStack* this){
    if( this -> quantity <= 0){
        printf("Error on IntegerStack pop: Stack has no elements!");
        exit(1);
    }
    this -> quantity = this -> quantity - 1;
    return this -> collection[ this -> quantity];
}


void print_IntegerStack(struct IntegerStack* this){
    printf("    ___  Top   ___ \n");
    for(int i = this -> quantity - 1; i >= 0; i--){
        printf("      %d \n", this -> collection[i]);
    }
    printf("    ___ Bottom ___\n");
}


struct IntegerStack* create_IntegerStack(int new_limit){
    struct IntegerStack* newStack = (struct IntegerStack*)malloc((new_limit * sizeof(int)) + sizeof(struct IntegerStack) );
    if (newStack){
        newStack -> limit = new_limit;
        newStack -> quantity = 0;
        newStack -> collection = (int*)calloc(new_limit, sizeof(int));
        newStack -> print = print_IntegerStack;
        newStack -> peek = peek_IntegerStack;
        newStack -> pop = pop_IntegerStack;
        newStack -> push = push_IntegerStack;
    }
    return newStack;
}

void test_push(struct IntegerStack* stack, int val){
    printf("Push operation: \n");
    printf("   pre-push-quantity: %d\n", stack -> quantity);
    printf("   pre-push-limit: %d\n", stack -> limit);
    stack -> push(stack, val);
    printf("\n");
    printf("   state of stack: \n");
    stack -> print(stack);
    printf("\n");
    printf("   post-push-quantity: %d\n", stack -> quantity);
    printf("   post-push-limit: %d\n", stack -> limit);
    printf("   Space reserved for array: %lu\n", malloc_usable_size( stack -> collection));
    printf("! end of push\n");
    printf("\n\n\n");

}

void test_pop(struct IntegerStack* stack){
    printf("Push operation: \n");
    printf("   pre-push-quantity: %d\n", stack -> quantity);
    printf("   pre-push-limit: %d\n", stack -> limit);
    printf("\n");
    int val = stack -> pop(stack);
    printf("   Value of pop operation: %d\n", val);
    printf("   state of stack: \n");
    stack -> print(stack);
    printf("\n");
    printf("   post-push-quantity: %d\n", stack -> quantity);
    printf("   post-push-limit: %d\n", stack -> limit);
    printf("   Space reserved for array: %lu\n", malloc_usable_size( stack -> collection));
    printf("! end of pop\n");
    printf("\n\n\n");
}

void test_peek(struct IntegerStack* stack){
    printf("Peek operation: \n");
    printf("    Value on top: %d\n", stack -> peek(stack));
    printf("! end of peek\n");
    printf("\n");
}

int main(){
    struct IntegerStack* test_stack = create_IntegerStack(5);
    test_stack -> print(test_stack);

    test_push(test_stack,3);
    test_push(test_stack,10);
    test_peek(test_stack);
    test_pop(test_stack);
    test_push(test_stack,12);
    test_push(test_stack,15);
    test_push(test_stack,18);
    test_push(test_stack,21);
    test_push(test_stack,34);
    test_push(test_stack,42);
    test_push(test_stack,50);
    test_push(test_stack,51);
    test_push(test_stack,52);
    test_peek(test_stack);

    printf("--- --- --- Intiating consecutive pops: \n");
    test_pop(test_stack);
    test_pop(test_stack);
    test_pop(test_stack);
    test_pop(test_stack);
    test_pop(test_stack);
    test_pop(test_stack);
    test_pop(test_stack);
    test_pop(test_stack);
    test_pop(test_stack);
    test_pop(test_stack);
    //printf("Empty stack - empty pop: ");
    //test_pop(test_stack);
    destroy_IntegerStack(test_stack);
    return 0;
}
