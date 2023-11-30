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
};

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

int min_child(struct MinIntegerHeap* this, int index){
    if((index * 2) + 1 > this -> quantity){
        return index * 2;
    }else{
        if(this -> collection[index * 2] < this -> collection[(index * 2) + 1]){
            return index * 2;
        }else{
            return (index * 2) + 1;
        }
    }
}

void percolate_down_MinIntegerHeap(struct MinIntegerHeap* this, int index){
    bool exit_switch = false;
    int current_index = index;
    int min_child_index;
    int temp;
    while((current_index * 2 < this -> quantity) && (exit_switch == false)){
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
    int return_value = this -> collection[1];
    this -> collection[1] = this -> collection[ this -> quantity];
    this -> quantity = this -> quantity - 1;
    this -> percdown(this,1);
    return return_value;
}

void insert_MinIntegerHeap(struct MinIntegerHeap* this, int value){
    this -> quantity = this -> quantity + 1;
    this -> collection[ this -> quantity] = value;
    this -> percup(this, this -> quantity);
}

void print_MinIntegerHeap(struct MinIntegerHeap* this){
    for(int i = 1; i <= this -> quantity; i++){
        printf("    %d \n", this -> collection[i]);
    }
    printf("\n\n\n");
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
    }
    return newHeap;
}

int main(){
    struct MinIntegerHeap* test_heap = create_MinIntegerHeap(12);
    test_heap -> add(test_heap, 5);
    test_heap -> print(test_heap);
    test_heap -> add(test_heap, 3);
    test_heap -> print(test_heap);
    test_heap -> add(test_heap, 4);
    test_heap -> print(test_heap);
    test_heap -> add(test_heap, 1);
    test_heap -> print(test_heap);
    printf("remove: %d\n",test_heap -> remove(test_heap));
    test_heap -> print(test_heap);
    printf("remove: %d\n",test_heap -> remove(test_heap));
    test_heap -> print(test_heap);
    printf("remove: %d\n",test_heap -> remove(test_heap));
    test_heap -> print(test_heap);
    printf("remove: %d\n",test_heap -> remove(test_heap));
    test_heap -> print(test_heap);

    for(int i = 1; i < 10; i ++){
        test_heap -> add(test_heap, i * 2);
        test_heap -> print(test_heap);
    }

    test_heap -> add(test_heap, 3);
    test_heap -> print(test_heap);
    test_heap -> add(test_heap, 9);
    test_heap -> print(test_heap);
    for(int i = 1; i < 10; i ++){
        printf("removed: %d\n",test_heap -> remove(test_heap));
        test_heap -> print(test_heap);

    }
        printf("removed: %d\n",test_heap -> remove(test_heap));
        test_heap -> print(test_heap);
        printf("removed: %d\n",test_heap -> remove(test_heap));
        test_heap -> print(test_heap);
    return 0;
}
