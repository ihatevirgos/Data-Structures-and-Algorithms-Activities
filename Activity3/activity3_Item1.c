#include <stdio.h>

//getting the greatest element
int maximum (int array[], int size){
    int maxElement = array[0];
    for (int index = 0; index < size; index ++){
        if (array[index] > maxElement){
            maxElement = array[index];
        }
    }

    return maxElement;
}

//getting the least element
int minimum (int array[], int size){
    int minElement = array[0];
    for (int index = 0; index < size; index ++){
        if (array[index] < minElement){
            minElement = array[index];
        }
    }

    return minElement;
}

int main (){

    printf("===MAXIMUM & MINIMUM ELEMENT===\n\n");

    int arraySize;
    printf("Input the numner of elements to be storeed in the array: ");
    scanf("%d", &arraySize);

    int array[arraySize];

    printf("Input %d elements in the array:\n", arraySize);
    for (int index = 0; index < arraySize; index ++){
        printf("element - %d: ", index);
        scanf("%d", &array[index]);
    }

    int maxElement = maximum(array, arraySize);
    int minElement = minimum(array, arraySize);

    printf("Maximum element is: %d\n", maxElement);
    printf("Minimum element is: %d\n", minElement);

    return 0;
}