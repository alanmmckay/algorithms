#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

struct MinIntegerHeap{
    int quantity;
    int limit;
    int *collection;
};

void percup(struct MinIntegerHeap* this, int current_index){
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

void percdown(struct MinIntegerHeap* this, int index){
    bool exit_switch = false;
    int current_index = index;
    int min_child_index;
    int temp;
    while((current_index * 2 <= this -> quantity) && (exit_switch == false)){
        min_child_index = min_child(this,current_index);
        if( this -> collection[current_index] >= min_child_index){
            temp = this -> collection[current_index];
            this -> collection[current_index] = this -> collection[min_child_index];
            this -> collection[min_child_index] = temp;
            current_index = min_child_index;
        }else{
            exit_switch = true;
        }
    }
}

int delete_min(struct MinIntegerHeap* this){
    int return_value = this -> collection[1];
    this -> collection[1] = this -> collection[ this -> quantity];
    this -> quantity = this -> quantity - 1;
    percdown(this,1);
    return return_value;
}

void insert(struct MinIntegerHeap* this, int value){
    this -> quantity = this -> quantity + 1;
    this -> collection[ this -> quantity] = value;
    percup(this, this -> quantity);
}

int main(){
    printf("%d\n", 5 / 2);
    return 0;
}
