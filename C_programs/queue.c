#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

struct IntegerQueue{
    int quantity;
    int limit;
    int front;
    int rear;
    int *collection;
    void (*print)(struct IntegerQueue*);
    int (*dequeue)(struct IntegerQueue*);
    void (*enqueue)(struct IntegerQueue*, int);
    int (*peek)(struct IntegerQueue*);
};

//   f       r
// [ 3 5 6 7 0 x x x x x ]
//             f       r
// [ x x x x x 3 5 6 9 0 ]
//         f       r
// [ x x x 2 3 4 5 7 x x ]
//       r[2]    f[6]
// [ 2 3 4 x x x 2 0 9 8 ] a[0] = (f + 0) % len(a); a[5] = (f + 5) % len(a)
//   f                 r
// [ 2 3 5 6 4 2 3 4 5 6 ]
//   r f                        f                 r
// [ 2 3 5 6 4 2 3 4 6 5 ] -> [ 3 5 6 4 2 3 4 6 5 2 x x x x x x x x]

int peek_IntegerQueue(struct IntegerQueue* this){
    if( this -> quantity <= 0){
        printf("Error on IntegerQueue peek: Stack has no elements!");
        exit(1);
    }
    return this -> collection[ this -> front];
}


void enqueue_IntegerQueue(struct IntegerQueue* this, int new_item){
    this -> rear = (( this -> rear) + 1) % ( this -> limit);
    this -> collection[ this -> rear] = new_item;
    this -> quantity = this -> quantity + 1;
    if( this -> quantity >= this -> limit){
        this -> limit = ( this -> limit) * 1.5;
        int *new_array = (int*)calloc( this -> limit, sizeof(int));
        //Fill the first value of the new_array:
        new_array[0] = this -> collection[ this -> front];
        //Grab the next logical index:
        int c_index = ( this -> front) + 1;
        //Set the next index of the new array:
        int n_index = 1;
        //Cycle through the current set of logical indeces: I.e.,
        //      r  f                  f              r
        // [ 50 60 10 20 30 40 ] -> [ 10 20 30 40 50 60 x x x]
        while(c_index != this -> front){
            new_array[n_index] = this -> collection[c_index];
            c_index = (c_index + 1) % ( this -> quantity);
            n_index += 1;
        }
        //Point the collection to the new_array:
        this -> collection = new_array;
        //reset the front and rear pointers:
        this -> front = 0;
        this -> rear = ( this -> quantity) - 1;
    }
}


int dequeue_IntegerQueue(struct IntegerQueue* this){
    if( this -> quantity <= 0){
        printf("Error in IntegerQueue dequeue: Queue has no elements!");
        exit(1);
    }
    int value = this -> collection[ this -> front];
    this -> front = (( this -> front) + 1) % ( this -> limit);
    this -> quantity = ( this -> quantity) - 1;
    //return this -> collection[( this -> front) - 1]
    return value;
}


void print_IntegerQueue(struct IntegerQueue* this){
    printf("Front -> ");
    int val;
    for(int i = this -> front; i % ( this -> limit) != this -> rear; i++){
        val = this -> collection[i % ( this -> limit)];
        printf("%d, ", val);
    }
    printf("%d", this -> collection[ this -> rear]);
    printf(" <- Rear\n");
}


struct IntegerQueue* create_IntegerQueue(int new_limit){
    struct IntegerQueue* newQueue = (struct IntegerQueue*)malloc
                    ((new_limit * sizeof(int)) + sizeof(struct IntegerQueue) );
    if (newQueue){
        newQueue -> limit = new_limit;
        newQueue -> quantity = 0;
        newQueue -> front = 0;
        newQueue -> rear = 0;
        newQueue -> collection = (int*)calloc(new_limit,sizeof(int));
        newQueue -> print = print_IntegerQueue;
        newQueue -> dequeue = dequeue_IntegerQueue;
        newQueue -> enqueue = enqueue_IntegerQueue;
        newQueue -> peek = peek_IntegerQueue;
    }
    return newQueue;
}


int main(){

    return 0;
}
