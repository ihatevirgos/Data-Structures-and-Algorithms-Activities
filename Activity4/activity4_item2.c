#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* link;
};

//create a circular linked list
struct node* createCircularList(int size){
    struct node *head = NULL, *temp = NULL, *newNode = NULL;
    int value;

    if (size <= 0){
        printf("Number of nodes must be greater than zero.\n");
        return NULL;
    }

    //create first node
    printf("Input data for node 1: ");
    scanf("%d", &value);

    head = (struct node*)malloc(sizeof(struct node));
    head -> data = value;
    head -> link = head; //first node points to itself
    temp = head;

    //create remaining nodes
    for (int index = 2; index <= size; index++){
        newNode = (struct node*)malloc(sizeof(struct node));
        printf("Input data for node %d: ", index);
        scanf("%d", &value);

        newNode -> data = value;
        newNode -> link = head; //new node points to head
        temp -> link = newNode; //prev node links to new node
        temp = newNode; //move temp to new node
    }

    return head;
}

//print the circular linked list
void printCircularList(struct node* head){
    struct node* temp = head;

    printf("Data entered in the list are: \n");

    if (head == NULL){
        printf("List is empty. :(");
        return;
    }

    printf("\nCircular Linked List: ");
    int count = 1;
    do {
        printf("data %d = %d\n", count, temp -> data);
        temp = temp -> link;
        count++;
    } while (temp != head); //stops when return to head
    printf("\n");

}


int main(){ 
    printf("---Circular List---\n\n"); 
    
    struct node* head = NULL;
    int nodeSize;

    printf("Enter the number of nodes: ");
    scanf("%d", &nodeSize);

    head = createCircularList(nodeSize);
    printCircularList(head);
    
    return 0; 
}