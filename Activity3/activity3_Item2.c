#include <stdio.h>

int validatePosition(int position, int size){
    if (position < 1 || position > size){
        printf("Invalid position. Please enter a valid position (1 - %d)\n", size);
        return 0;
    }
    return 1;
}

void delete(int array[], int size, int deletePosition){
    deletePosition -= 1; //making the position 0-based

    //shift elements to the left 
    for (int index = deletePosition; index < size; index ++){
        array[index] = array[index + 1];
    }

    size--; //reduce array size
    

    //print udpated list
    printf("Updated list:\n");
    for (int index = 0; index < size; index ++){
        printf("%d\t", array[index]);
    }

}

int main (){
    printf("===ARRAY ELEMENT DELETION===\n\n");

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

    if (!validatePosition(deletePosition, arraySize)){
        return 0;
    }
    
    delete(array, arraySize, deletePosition);

    return 0;
}