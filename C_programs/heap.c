#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

struct MinIntegerHeap{
    int quantity;
    int limit;
    int *collection;
    void (*print)(struct MinIntegerHeap*);
    void (*percup)(struct MinIntegerHeap*, int);
    void (*percdown)(struct MinIntegerHeap*, int);
    int (*remove)(struct MinIntegerHeap*);
    void (*add)(struct MinIntegerHeap*, int);
    int (*peek)(struct MinIntegerHeap*);
};


void destroy_MinIntegerHeap(struct MinIntegerHeap* heap){
    if(heap){
        free( heap -> collection);
        free(heap);
    }
}


int peek_MinIntegerHeap(struct MinIntegerHeap* this){
    if( this -> quantity <= 0){
        printf("Error on MinIntegerHeap peek: Heap has no elements!");
        exit(1);
    }
    return this -> collection[ this -> quantity];
}


void percolate_up_MinIntegerHeap(struct MinIntegerHeap* this, int current_index){
    int parent_index = current_index / 2;
    int temp;
    while(current_index > 1 && this -> collection[current_index] < this -> collection[parent_index]){
        temp = this -> collection[current_index];
        this -> collection[current_index] = this -> collection[parent_index];
        this -> collection[parent_index] = temp;
        current_index = parent_index;
        parent_index = current_index / 2;
    }
}


int min_child(struct MinIntegerHeap* heap, int index){
    if((index * 2) + 1 > heap -> quantity){
        return index * 2;
    }else{
        if(heap -> collection[index * 2] < heap -> collection[(index * 2) + 1]){
            return index * 2;
        }else{
            return (index * 2) + 1;
        }
    }
}


void percolate_down_MinIntegerHeap(struct MinIntegerHeap* this, int index){
    int current_index = index;
    int min_child_index;
    int temp;
    while(current_index * 2 < this -> quantity){
        min_child_index = min_child(this,current_index);
        if( this -> collection[current_index] >= this -> collection[min_child_index]){
            temp = this -> collection[current_index];
            this -> collection[current_index] = this -> collection[min_child_index];
            this -> collection[min_child_index] = temp;
        }
        current_index = min_child_index;
    }
}


int delete_MinIntegerHeap(struct MinIntegerHeap* this){
    if( this -> quantity <= 0){
        printf("Error on MinIntegerHeap peek: Heap has no elements!");
        exit(1);
    }
    int return_value = this -> collection[1];
    this -> collection[1] = this -> collection[ this -> quantity];
    this -> quantity = this -> quantity - 1;
    this -> percdown(this,1);
    return return_value;
}


void insert_MinIntegerHeap(struct MinIntegerHeap* this, int value){
    this -> quantity = this -> quantity + 1;
    if( this -> quantity == this -> limit){
        this -> limit = ( this -> limit) * 1.5;
        int *new_array = (int*)calloc( this -> limit, sizeof(int));
        for(int i = 1; i <= this -> quantity; i ++){
            new_array[i] = this -> collection[i];
        }
        this -> collection = new_array;
    }
    this -> collection[ this -> quantity] = value;
    this -> percup(this, this -> quantity);
}


void print_MinIntegerHeap(struct MinIntegerHeap* this){
    printf("    [ Top of Heap -> ");
    for(int i = 1; i <= this -> quantity; i++){
        printf(" | %d", this -> collection[i]);
    }
    printf(" ]\n\n");
}


struct MinIntegerHeap* create_MinIntegerHeap(int new_limit){
    struct MinIntegerHeap* newHeap = (struct MinIntegerHeap*)malloc((new_limit * sizeof(int)) + sizeof(struct MinIntegerHeap));
    if(newHeap){
        newHeap -> limit = new_limit;
        newHeap -> quantity = 0;
        newHeap -> collection = (int*)calloc(new_limit, sizeof(int));
        newHeap -> add = insert_MinIntegerHeap;
        newHeap -> remove = delete_MinIntegerHeap;
        newHeap -> percup = percolate_up_MinIntegerHeap;
        newHeap -> percdown = percolate_down_MinIntegerHeap;
        newHeap -> print = print_MinIntegerHeap;
        newHeap -> peek = peek_MinIntegerHeap;
    }
    return newHeap;
}


void test_insert(struct MinIntegerHeap* heap, int val){
    printf("Insertion operation: \n");
    printf("   pre-insertion-quantity: %d\n", heap -> quantity);
    printf("   pre-insertion-limit: %d\n", heap -> limit);
    heap -> add(heap, val);
    printf("\n");
    printf("   state of heap: \n");
    heap -> print(heap);
    printf("\n");
    printf("   post-insertion-quantity: %d\n", heap -> quantity);
    printf("   post-insertion-limit: %d\n", heap -> limit);
    printf("   Space reserved for array: %lu\n", malloc_usable_size( heap -> collection));
    printf("! end of insertion\n");
    printf("\n\n\n");
}

void test_remove(struct MinIntegerHeap* heap){
    printf("Removal operation: \n");
    printf("   pre-removal-quantity: %d\n", heap -> quantity);
    printf("   pre-removal-limit: %d\n", heap -> limit);
    printf("\n");
    int val = heap -> remove(heap);
    printf("   Value of removal operation: %d\n", val);
    printf("   state of heap: \n");
    heap -> print(heap);
    printf("\n");
    printf("   post-removal-quantity: %d\n", heap -> quantity);
    printf("   post-removal-limit: %d\n", heap -> limit);
    printf("   Space reserved for array: %lu\n", malloc_usable_size( heap -> collection));
    printf("! end of removal\n");
    printf("\n\n\n");
}

void test_peek(struct MinIntegerHeap* heap){
    printf("Peek operation: \n");
    printf("    Value at front: %d\n", heap -> peek(heap));
    printf("! end of peek\n");
    printf("\n");
}

int main(){
    struct MinIntegerHeap* test_heap = create_MinIntegerHeap(5);
    test_heap -> print(test_heap);

    test_insert(test_heap, 5);
    test_insert(test_heap, 3);
    test_insert(test_heap, 4);
    test_insert(test_heap, 1);

    test_remove(test_heap);
    test_remove(test_heap);
    test_remove(test_heap);
    test_remove(test_heap);

    for(int i = 1; i < 10; i ++){
        test_insert(test_heap, i * 2);
    }

    test_insert(test_heap, 3);
    test_insert(test_heap, 9);
    test_insert(test_heap, 11);

    for(int i = 1; i < 10; i ++){
        test_remove(test_heap);
    }

    test_remove(test_heap);
    test_remove(test_heap);

    destroy_MinIntegerHeap(test_heap);
    return 0;
}
