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
    // increment rear
    // place value
    // increment quantity
    // check size
}

int dequeue_IntegerQueue(struct IntegerQueue* this){
    if( this -> quantity <= 0){
        printf("Error in IntegerQueue dequeue: Queue has no elements!");
        exit(1);
    }
    // remember value at front
    // increment front
    // decrement quantity
    // return remembered value
    return 0;
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
        //newQueue -> print =
        newQueue -> dequeue = dequeue_IntegerQueue;
        newQueue -> enqueue = enqueue_IntegerQueue;
        newQueue -> peek = peek_IntegerQueue;
    }
    return newQueue;
}


int main(){

    return 0;
}
