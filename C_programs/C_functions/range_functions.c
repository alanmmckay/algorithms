 
#include "range_functions.h"
#include <stdio.h>

int main(){
    int max_result = max_int(3,4);
    printf("Maximum int: %d between %d and %d \n", max_result, 3, 4);

    int arr1[8] = {1,2,3,4,5,6,7};
    int len_result_1 = length(arr1);
    printf("Size of arr: %d \n", len_result_1);

    int arr2[8] = {1,2,3,4,5,6};
    int len_result_2 = length(arr2);
    printf("Size of arr: %d \n", len_result_2);

    int arr3[6] = {47,23,42,10,15};
    printf("Min of arr: %d \n", min_of_list(arr3));

    printf("Max of arr: %d \n", max_of_list(arr3));

    printf("Max Polar of arr: %d \n", polar_of_list(max_of_list,arr3));
    printf("Min Polar of arr: %d \n", polar_of_list(min_of_list,arr3));

    printf("Null Polar of arr: %d \n", polar_of_list(length,arr3));

    double arr4[6] = {47.0, 23.0, 42.0, 10.0, 15.0};
    printf("Sum of arr: %f \n", sum_of_list(arr4));

}

