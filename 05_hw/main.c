#include "stack.h"

#include <stdio.h>

int main() {
    Stack stack;
    initStack(&stack);

    push(&stack, "a");
    push(&stack, 30);
    push(&stack, "");
    push(&stack, 100);
    push(&stack, 20);

    printf("After pushing elements:\n");
    traverseStack(&stack);

    pop(&stack);

    printf("After popping an element:\n");
    traverseStack(&stack);

    if (searchByValue(&stack, 20) != NULL) {
        printf("Element with value 20 found.\n");
    }
    else {
        printf("Element with value 20 not found.\n");
    }

    const Node* topElement = getTop(&stack);
    if (topElement != NULL) {
        printf("Top element: %d\n", topElement->data);
    }

    return 0;
}


