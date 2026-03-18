#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int heap[MAX_SIZE]; //fixed max size of the heap (100)
int heap_size = 0; //current number of elements in the heap

void swap(int* first, int* second){
    int temp = *first;
    *first = *second;
    *second = temp;
}


void up_heapify(int childIndex){
    if (childIndex == 0) //base case: if child is root
        return;

    int parentIndex = (childIndex - 1) / 2;

    if (heap[parentIndex] > heap[childIndex]){
        swap(&heap[parentIndex], &heap[childIndex]);
        up_heapify(parentIndex);
    }
}

void down_heapify(int parentIndex){
    int leftChildIndex = (2 * parentIndex) + 1;
    int rightChildIndex = (2 * parentIndex) + 2;    
    int smallestIndex = parentIndex; //assume parent is the minimum value

    //compare left child
    if (leftChildIndex < heap_size && heap[leftChildIndex] < heap[smallestIndex]){
        smallestIndex = leftChildIndex;
    }

    //compare right child
    if (rightChildIndex < heap_size && heap[rightChildIndex] < heap[smallestIndex]){
        smallestIndex = rightChildIndex;
    }

    //if parent is not the smallest, swap and continue heapifying
    if (smallestIndex != parentIndex){
        swap(&heap[smallestIndex], &heap[parentIndex]);
        down_heapify(smallestIndex);
    }
}


int find_minimum(){
    return heap[0]; //returns the root
}

void heap_insert(int child){
    //when number of elements reached maximum size (100)
    if (heap_size == MAX_SIZE){
        printf("Heap is full!\n");
        return;
    }

    heap[heap_size] = child;
    heap_size++;
    up_heapify(heap_size - 1);

    printf("Value inserted successfully!\n");
}

void delete_root(){
    if (heap_size == 0){
        printf("Heap is empty!\n");
        return;
    }

    heap[0] = heap[heap_size - 1];
    heap_size--;
    down_heapify(0);

    printf("Minimum value deleted successfully!\n");
}

void display_heap(){

    printf("\n");

    if (heap_size == 0){
        printf("Heap is empty!\n");
        return;
    }
    printf("--- Displaying Min-Heap ---\n");
    printf("Heap elements: ");
    for (int i = 0; i < heap_size; i++){
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main (){ 
    int choice, value;

    while (1){
        printf("\n===== MIN HEAP MENU =====\n");
        printf("1. Insert\n");
        printf("2. Delete Minimum\n");
        printf("3. Find Minimum\n");
        printf("4. Display Heap\n");
        printf("5. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                heap_insert(value);
                break;
            case 2:
                delete_root();
                break;
            case 3:
                if (heap_size > 0)
                    printf("Minimum value: %d\n", find_minimum());
                else
                    printf("Heap is empty!\n");
                break;
            case 4: 
                display_heap();
                break;
            case 5:
                printf("Exiting... Thank you for using the program ! !\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}