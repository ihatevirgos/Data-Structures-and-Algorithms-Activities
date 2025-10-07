#include <stdio.h>

void bubbleSort(int array[], int size){
    for (int index = 0; index < size; index ++){
        for (int index2 = 0; index2 < (size - 1 - index); index2 ++){
            if (array[index2] > array[index2 + 1]){
                int temp = array[index2];
                array[index2] = array[index2 + 1];
                array[index2 + 1] = temp;
            }
        }
    }

    //print
    printf("Elements of array sorted in ascending order (via bubble sorting):\n");
    for (int index = 0; index < size; index ++){
        printf("%d\t", array[index]);
    }


}

int main (){

    printf("===ARRAY SORTING===\n\n");

    int arraySize;
    printf("Input the numner of elements to be storeed in the array: ");
    scanf("%d", &arraySize);

    int array[arraySize];

    printf("Input %d elements in the array:\n", arraySize);
    for (int index = 0; index < arraySize; index ++){
        printf("element - %d: ", index);
        scanf("%d", &array[index]);
    }

    bubbleSort(array, arraySize);


    return 0;
}