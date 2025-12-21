#include <stdio.h>
#include "stack.h"
#include <assert.h>
#include <stdlib.h>

void testPush() {
    Stack stack;
    initStack(&stack);
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    assert(getTop(&stack)->data == 3);
    printf("testPush passed.\n");
}

void testPop() {
    Stack stack;
    initStack(&stack);
    push(&stack, 1);
    push(&stack, 2);
	int val;
    pop(&stack, &val);
    assert(getTop(&stack)->data == 1);
    pop(&stack, &val);
    assert(isEmpty(&stack));
    printf("testPop passed.\n");
}

void testSearchByValue() {
    Stack stack;
    initStack(&stack);
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    assert(searchByValue(&stack, 2) != NULL);
    assert(searchByValue(&stack, 4) == NULL);
    printf("testSearchByValue passed.\n");
}

void testSearchByIndex() {
    Stack stack;
    initStack(&stack);
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    assert(searchByIndex(&stack, 0)->data == 3);
    assert(searchByIndex(&stack, 1)->data == 2);
    assert(searchByIndex(&stack, 2)->data == 1);
    assert(searchByIndex(&stack, 3) == NULL);
    printf("testSearchByIndex passed.\n");
}

void testDestroyStack() {
    Stack stack;
    initStack(&stack);
    push(&stack, 1);
    push(&stack, 2);
    destroyStack(&stack);
    assert(isEmpty(&stack));
    printf("testDestroyStack passed.\n");
}

void testIsEmpty() {
    Stack stack;
    initStack(&stack);
    assert(isEmpty(&stack));
    push(&stack, 1);
    assert(!isEmpty(&stack));
	int val;
    pop(&stack, &val);
    assert(isEmpty(&stack));
    printf("testIsEmpty passed.\n");
}

void testGetTop() {
    Stack stack;
    initStack(&stack);
    assert(getTop(&stack) == NULL);
    push(&stack, 42);
    assert(getTop(&stack)->data == 42);
    push(&stack, 99);
    assert(getTop(&stack)->data == 99);
    printf("testGetTop passed.\n");
}

void testTraverseStack() {
    Stack stack;
    initStack(&stack);
    printf("Expected output: Stack elements: \nActual output: ");
    traverseStack(&stack);

    push(&stack, 5);
    push(&stack, 10);
    push(&stack, 15);

    printf("Expected output: Stack elements: 15 10 5\nActual output: ");
    traverseStack(&stack);
    printf("testTraverseStack passed.\n");
}


int main() {
    testPush();
    testPop();
    testSearchByValue();
    testSearchByIndex();
    testDestroyStack();
    testIsEmpty();
    testGetTop();
    testTraverseStack();
    printf("All tests passed!\n");
    return 0;
}