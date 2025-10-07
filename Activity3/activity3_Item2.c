#include <stdio.h>

void delete(int array[], int size, int deletePosition){
    deletePosition -= 1;

    //shift
    for (int index = deletePosition; index < size; index ++){
        array[index] = array[index + 1];
    }

    size--; 
    

    //print
    printf("Updated list:\n");
    for (int index = 0; index < size; index ++){
        printf("%d\t", array[index]);
    }

}

int main (){
     printf("===MAXIMUM AND MINIMUM ELEMENT===\n\n");

    int arraySize;
    printf("Input the numner of elements to be storeed in the array: ");
    scanf("%d", &arraySize);

    int array[arraySize];

    printf("Input %d elements in the array:\n", arraySize);
    for (int index = 0; index < arraySize; index ++){
        printf("element - %d: ", index);
        scanf("%d", &array[index]);
    }

    
    int deletePosition;
    printf("\nInput the position where to delete: ");
    scanf("%d", &deletePosition);

    //checks if input is valid
    if (deletePosition < 1 || deletePosition > arraySize){
        printf("Invalid position. Please enter a valid position (1 - %d)\n", arraySize);
        return 1;
    }

    delete(array, arraySize, deletePosition);

    return 0;
}