#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    struct node* link;
};

//create new node
struct node* newNode(int data){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node -> data = data;
    node -> link = NULL;
    return node;
}

//insert node at the beginning
void insertAtBeginning(struct node** head, int data){
    struct node* node = newNode(data);
    node -> link = *head;
    *head  = node;
}

//adding two linked lists
struct node* addLinkedList(struct node* list1, struct node* list2){
    struct node temp;
    struct node* current = &temp;
    temp.link = NULL;
    int carry = 0;

    //loop runs while there's still a digit or a carry
    while (list1 != NULL || list2 != NULL || carry != 0){

        //gets the value of the digit
        int digitList1 = (list1 != NULL) ? list1 -> data : 0;
        int digitList2 = (list2 != NULL) ? list2 -> data : 0;

        int sum = digitList1 + digitList2 + carry;
        carry = sum / 10;

        current -> link = newNode(sum % 10);
        current = current -> link;

        //moves to the next digit
        if (list1 != NULL)
            list1 = list1 -> link;
        if (list2 != NULL)
            list2 = list2 -> link;
    }

    return temp.link; //skips the temp node
}

//print list
void printList(struct node* head){
    while (head != NULL){
        printf("%d", head -> data);
        head = head -> link;
    }
    printf("\n");
}

//convert string into reverse linked list to add the digits left to right
struct node* stringConvert(char number[]){
    struct node* head = NULL;
    int length = strlen(number);

    for (int index = 0; index < length; index++){
        if (number[index] >= '0' && number[index] <= '9')
            insertAtBeginning(&head, number[index] - '0');
    }

    return head;
}

//revert the result
struct node* reverseList(struct node* head){
    struct node* prev = NULL;
    struct node* current = head;
    struct node* link = NULL;

    while (current != NULL){
        link = current -> link; //stores next node
        current -> link = prev; //reverse the link
        prev = current; //move the prev forward
        current = link; //move the current forward
    }

    return prev; //new head (prev tail)
}

int main(){ 
    char number1[100], number2[100];

    printf("---LINKED LIST ADDITION---\n\n");

    printf("Enter the first number: ");
    scanf("%s", number1);

    printf("Enter the second number: ");
    scanf("%s", number2);

    //call to convert string to linked list
    struct node* list1 = stringConvert(number1);
    struct node* list2 = stringConvert(number2);

    struct node* result = addLinkedList(list1, list2);

    result = reverseList(result); //revert the result to the correct order

    printf("%s + %s = ", number1, number2);
    printList(result);



    return 0;
}