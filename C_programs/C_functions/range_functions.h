#include <stdio.h>

int max_int(int first_val, int second_val){
    if (first_val >= second_val){
        return first_val;
    }else{
        return second_val;
    }
}

int min_int(int first_val, int second_val){
    if (first_val <= second_val){
        return first_val;
    }else{
        return second_val;
    }
}

int length(int arr[]){
    int i;
    int count = 0;
    for(i = 0; arr[i] != '\0'; i++){
        count++;
    }
    return count;
}

int min_of_list(int arr[]){
    int arr_length = length(arr);
    int i;
    if(arr_length == 1){
        return arr[0];
    }else{
        int min = arr[0];
        for(i = 1; i < arr_length; i++){
            if( arr[i] < min){
                min = arr[i];
            }
        }
        return min;
    }
}

int max_of_list(int arr[]){
    int arr_length = length(arr);
    int i;
    if(arr_length == 1){
        return arr[0];
    }else{
        int max = arr[0];
        for(i = 1; i < arr_length; i++){
            if( arr[i] > max){
                max = arr[i];
            }
        }
        return max;
    }
}

int polar_of_list(int (*func)(), int arr[]){
    if(func == max_of_list || func == min_of_list){
        return func(arr);
    }else{
        return -1;
    }
}

double sum_of_list(double arr[]){
    double sum = arr[0];
        for(int i = 1; arr[i] != '\0'; i++){
        if(arr[1] != '\0'){
            printf("%f \n",arr[i]);
            sum += arr[i];
        }
    }
    return sum;
}
