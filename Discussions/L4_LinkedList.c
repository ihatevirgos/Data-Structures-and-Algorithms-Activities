#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;           //the data
    struct node* next;  //the pointer to the next node
};

// type alias for  better readability
typedef struct node node;

typedef struct {
    node* head;     //pointer to the first node
    int size;       //number of nodes in the list
} LinkedList;


//create linked list
LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL){
        printf("Memory allocation failed! \n");
        exit(1);
    }
    list -> head = NULL;
    list -> size = 0;
    return list;
}

void insertAtBeginning(LinkedList* list, int data){
    //create new node
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL){
        printf("Memory allocation failed! \n");
        return;
    }

    //initialize new node
    newNode -> data = data;
    newNode -> next = list -> head;     //point to the current first node

    //update lit head size
    list -> head = newNode;
    list -> size++;
}

void insertAtEnd(LinkedList* list, int data){
    //create new node
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL){
        printf("Memory allocation failed\n");
        return;
    }
    newNode -> data = data;
    newNode -> next = NULL;

    //CONNECT NEWNODE
    //if list is empty, new node becomes head
    if (list -> head == NULL){
        list -> head = newNode;
    } else {
        //traverse to the last node
        node* current = list -> head;
        while (current -> next != NULL){
            current = current -> next; 
        }
        current -> next = newNode; //link to the last node
    }
    list -> size++;
}

void insertAtPosition(LinkedList* list, int data, int position){
    //validate position
    if (position < 0 || position > list -> size){
        printf("Invalid position! Position should be between 0 and %d\n", list -> size);
        return;
    }

    if (position == 0){
        insertAtBeginning(list, data); //function call because this is insertion at the beginning
        return;
    }
    
    //create node
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL){
        printf("Memory allocation failed!\n");
        return;
    }
    newNode -> data = data;

    //traverse to the node before the target position
    node* current = list-> head;
    for (int index = 0; index < position -1; index++){
        current = current -> next;
    }

    //insert new node
    newNode -> next = current -> next;
    current -> next = newNode;
    list -> size++;
}

void deleteFromBeginning(LinkedList* list){
    if (list -> head  == NULL){
        printf("List is empty! cannot delete.\n");
        return;
    }

    node* temp = list -> head;              //saves the current head
    list -> head = list -> head -> next;    //next node will be the new head
    free(temp);                             //delete old head
    list -> size--;
}

void deleteFromEnd(LinkedList* list){
    if(list -> head == NULL){
        printf("List is empty! cannot delete.\n");
        return;
    }

    if (list -> head -> next == NULL){      //if list has one node (head only)
        free(list -> head);
        list -> head = NULL;
    } else {
        //traverse to the 2nd to the last node
        node* current = list -> head;
        while (current -> next -> next != NULL){
            current = current -> next;
        }

        //free the last node
        free(current -> next);
        current -> next = NULL;
    }

    list -> size--;
}

void deleteFromPosition(LinkedList* list, int position){
    //validate
    if (list -> head == NULL){
        printf("List is empty! cannot delete.\n");
        return;
    }

    if (position < 0 || position >= list -> size){
        printf("Invalid position! Position should be between 0 and %d\n", list -> size - 1); //if position is outside the margin
        return; 
    }

    //if there's only one node (head node)
    if (position == 0){
        deleteFromBeginning(list);
        return;
    }

    //traverse node to the node before the position
    node* current = list -> head;
    for (int index = 0; index < position; index ++){
        current = current -> next;
    }

    // freeing
    node* temp = current -> next;
    current -> next = temp -> next;
    free(temp);
    list -> size--;
}

//searching
node* search(LinkedList* list, int key){
    node* current = list -> head;

    while (current != NULL){
        if (current -> data == key){
            return current; //key found
        }

        current = current -> next; //traverse
    }

    return NULL; //not found
}

//display
void display(LinkedList* list){
    if (list -> head == NULL){
        printf("List is empty\n");
        return;
    }

    node* current = list -> head;
    printf("HEAD -> ");
    while (current != NULL){
        printf("%d -> ", current -> data);
        current = current -> next; //traverse to next node
    }
    printf("NULL\n");
}

//delete the whole list
void freeLinkedList(LinkedList* list){
    node* current = list -> head;
    node* next;

    //free all node
    while (current != NULL){
        next = current -> next;
        free(current);
        current = next;
    }

    free(list);
}

//get size
int  getSize(LinkedList* list){
    return list -> size;
}


int main() {  
    
    printf("=== LINKED LIST DEMO ===\n\n");

    //creating a new linked list
    LinkedList* myList = createLinkedList();
    printf("Created a new linked list\n");

    //insertion operations
    printf("\n--- INSERTION OPERATIONS ---\n");

    insertAtBeginning(myList, 10);

    /*
        tinamad nako maglagay sa main basahin niyo nalang ung function hahahaha
    */

    return 0;
}