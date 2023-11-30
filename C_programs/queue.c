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


void destroy_IntegerQueue(struct IntegerQueue* queue){
    if (queue){
        free( queue -> collection);
        free(queue);
    }
}


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
        printf("Error on IntegerQueue peek: Queue has no elements!");
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
    if( this -> quantity <= 0){
        this -> front = 0;
        this -> rear = -1;
    }
    //return this -> collection[( this -> front) - 1]
    return value;
}


void print_IntegerQueue(struct IntegerQueue* this){
    printf("Front -> ");
    if( this -> quantity > 0){
        int val;
        for(int i = this -> front; i % ( this -> limit) != this -> rear; i++){
            val = this -> collection[i % ( this -> limit)];
            printf("%d, ", val);
        }
        if( this -> quantity > 0){
            printf("%d", this -> collection[ this -> rear]);
        }
    }
    printf(" <- Rear\n");
}

void print_collection(struct IntegerQueue* this){
    printf("[ Begin Array |");
    for(int i = 0; i < this -> limit; i++){
        if(i == this -> front){
            printf("Front -> ");
        }
        if(i == this -> rear){
            printf("Rear -> ");
        }
        printf("%d | ", this -> collection[i]);
    }
    printf(" End Array ]\n\n");
}

struct IntegerQueue* create_IntegerQueue(int new_limit){
    struct IntegerQueue* newQueue = (struct IntegerQueue*)malloc
                    ((new_limit * sizeof(int)) + sizeof(struct IntegerQueue) );
    if (newQueue){
        newQueue -> limit = new_limit;
        newQueue -> quantity = 0;
        newQueue -> front = 0;
        newQueue -> rear = -1;
        newQueue -> collection = (int*)calloc(new_limit,sizeof(int));
        newQueue -> print = print_IntegerQueue;
        newQueue -> dequeue = dequeue_IntegerQueue;
        newQueue -> enqueue = enqueue_IntegerQueue;
        newQueue -> peek = peek_IntegerQueue;
    }
    return newQueue;
}


void test_enqueue(struct IntegerQueue* queue, int val){
    printf("Enqueue operation: \n");
    printf("   pre-enqueue-quantity: %d\n", queue -> quantity);
    printf("   pre-enqueue-limit: %d\n", queue -> limit);
    queue -> enqueue(queue, val);
    printf("\n");
    printf("   state of queue: \n");
    queue -> print(queue);
    printf("\n");
    printf("    state of collection: \n");
    print_collection(queue);
    printf("\n");
    printf("   post-enqueue-quantity: %d\n", queue -> quantity);
    printf("   post-enqueue-limit: %d\n", queue -> limit);
    printf("   Space reserved for array: %lu\n", malloc_usable_size( queue -> collection));
    printf("! end of enqueue\n");
    printf("\n\n\n");
}

void test_dequeue(struct IntegerQueue* queue){
    printf("Dequeue operation: \n");
    printf("   pre-dequeue-quantity: %d\n", queue -> quantity);
    printf("   pre-dequeue-limit: %d\n", queue -> limit);
    printf("\n");
    int val = queue -> dequeue(queue);
    printf("   Value of dequeue operation: %d\n", val);
    printf("   state of queue: \n");
    queue -> print(queue);
    printf("\n");
    printf("    state of collection: \n");
    print_collection(queue);
    printf("\n");
    printf("   post-dequeue-quantity: %d\n", queue -> quantity);
    printf("   post-dequeue-limit: %d\n", queue -> limit);
    printf("   Space reserved for array: %lu\n", malloc_usable_size( queue -> collection));
    printf("! end of dequeue\n");
    printf("\n\n\n");
}

void test_peek(struct IntegerQueue* queue){
    printf("Peek operation: \n");
    printf("    Value at front: %d\n", queue -> peek(queue));
    printf("! end of peek\n");
    printf("\n");
}

int main(){
    struct IntegerQueue* test_queue = create_IntegerQueue(5);
    test_queue -> print(test_queue);

    test_enqueue(test_queue, 10);
    test_peek(test_queue);
    test_enqueue(test_queue, 20);
    test_peek(test_queue);
    test_enqueue(test_queue, 30);
    test_peek(test_queue);
    test_enqueue(test_queue, 40);
    test_peek(test_queue);

    test_dequeue(test_queue);
    test_dequeue(test_queue);
    test_dequeue(test_queue);


    test_enqueue(test_queue, 10);
    test_enqueue(test_queue, 20);
    test_enqueue(test_queue, 30);

    for(int i = 1; i <= 15; i++){
        if(i % 2 == 0){
            test_dequeue(test_queue);
        }
        test_enqueue(test_queue,i*10);
    }

    for(int i = 1; i <= 12; i ++){
        test_dequeue(test_queue);
    }

    test_enqueue(test_queue,1);
    test_enqueue(test_queue,2);
    destroy_IntegerQueue(test_queue);
    return 0;
}
