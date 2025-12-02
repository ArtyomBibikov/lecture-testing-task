#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
        printf("Cannot create a null node");
    }

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initStack(Stack* stack) {
    stack->top = NULL;
}

void destroyStack(Stack* stack) {
    Node* current = stack->top;
    while (current != NULL) {
        Node* tmp = current;
        current = current->next;
	    free(tmp);
    }
    stack->top = NULL;
}

void push(Stack* stack, int data) {
    Node* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

void pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Cannot pop an empty stack\n");
        return;
    }
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
}

Node* searchByValue(Stack* stack, int value) {
    Node* current = stack->top;
    if (current != NULL) {
        if (current->data == value) {
            return current;
        }
        else
            return NULL;
    }
    else {
        printf("Attempting to search an empty stack\n");
        return NULL;
    }
}

Node* searchByIndex(Stack* stack, int index) {
    Node* current = stack->top;
    int count = 0;
    while (current != NULL) {
        if (count == index) {
            return current;
        }
        count++;
        current = current->next;
    }
    return NULL;
}

Node* getTop(Stack* const stack) {
    return stack->top;
}

void traverseStack(Stack* stack) {
    Node* current = stack->top;
    printf("Stack elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

bool isEmpty(Stack* const stack) {
    return stack->top == NULL;
}

