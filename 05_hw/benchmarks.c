#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "stack.h"

#define SMALL_SIZE     100
#define MEDIUM_SIZE    1000
#define LARGE_SIZE     10000

typedef struct {
    clock_t start;
    clock_t end;
} Timer;

static void timer_start(Timer* t) {
    t->start = clock();
}

static void timer_stop(Timer* t) {
    t->end = clock();
}

static double timer_elapsed_ms(Timer* t) {
    return ((double)(t->end - t->start) / CLOCKS_PER_SEC) * 1000.0;
}

static double timer_elapsed_us(Timer* t) {
    return ((double)(t->end - t->start) / CLOCKS_PER_SEC) * 1000000.0;
}

void benchmark_push_single() {
    printf("\nBenchmark: Single Push\n");

    Stack s;
    initStack(&s);

    Timer timer;
    timer_start(&timer);

    if (!push(&s, 42)) {
        fprintf(stderr, "Push failed!\n");
        return;
    }

    timer_stop(&timer);

    printf("Time: %.3f microseconds\n", timer_elapsed_us(&timer));
    printf("Result: %s\n", (s.top != NULL && s.top->data == 42) ? "OK" : "FAIL");

    destroyStack(&s);
}

void benchmark_push_multiple(int num_elements) {
    printf("\nBenchmark: Push %d elements\n", num_elements);

    Stack s;
    initStack(&s);

    Timer timer;
    timer_start(&timer);

    for (int i = 0; i < num_elements; i++) {
        if (!push(&s, i)) {
            fprintf(stderr, "Push failed at iteration %d\n", i);
            destroyStack(&s);
            return;
        }
    }

    timer_stop(&timer);

    double total_time_ms = timer_elapsed_ms(&timer);
    double avg_time_us = (total_time_ms * 1000.0) / num_elements;

    printf("Total elements: %d\n", num_elements);
    printf("Total time: %.3f ms\n", total_time_ms);
    printf("Average time per push: %.3f µs\n", avg_time_us);

    int count = 0;
    Node* current = s.top;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("Actual elements in stack: %d\n", count);
    printf("Verification: %s\n", (count == num_elements) ? "PASS" : "FAIL");

    destroyStack(&s);
}

void benchmark_pop_single() {
    printf("\nBenchmark: Single Pop\n");

    Stack s;
    initStack(&s);
    push(&s, 42);

    Timer timer;
    timer_start(&timer);

    int value;
    if (!pop(&s, &value)) {
        fprintf(stderr, "Pop failed!\n");
        destroyStack(&s);
        return;
    }

    timer_stop(&timer);

    printf("Operation: pop single element\n");
    printf("Time: %.3f microseconds\n", timer_elapsed_us(&timer));
    printf("Popped value: %d (expected: 42)\n", value);
    printf("Stack empty after pop: %s\n", isEmpty(&s) ? "YES" : "NO");

    destroyStack(&s);
}

void benchmark_pop_multiple(int num_elements) {
    printf("\nBenchmark: Pop %d elements\n", num_elements);
    Stack s;
    initStack(&s);

    for (int i = 0; i < num_elements; i++) {
        push(&s, i);
    }

    Timer timer;
    timer_start(&timer);

    int value;
    int successful_pops = 0;
    for (int i = 0; i < num_elements; i++) {
        if (pop(&s, &value)) {
            successful_pops++;
            if (value != num_elements - i - 1) {
                printf("Warning: Unexpected value %d at pop %d (expected %d)\n",
                    value, i, num_elements - i - 1);
            }
        }
        else {
            fprintf(stderr, "Pop failed at iteration %d\n", i);
            break;
        }
    }

    timer_stop(&timer);

    double total_time_ms = timer_elapsed_ms(&timer);
    double avg_time_us = (total_time_ms * 1000.0) / successful_pops;

    printf("Attempted pops: %d\n", num_elements);
    printf("Successful pops: %d\n", successful_pops);
    printf("Total time: %.3f ms\n", total_time_ms);
    printf("Average time per pop: %.3f µs\n", avg_time_us);
    printf("Stack empty after all pops: %s\n", isEmpty(&s) ? "YES" : "NO");

    destroyStack(&s);
}


int main() {
    printf("\nStarting benchmarks...\n");
    benchmark_push_single();
    benchmark_pop_single();
    benchmark_push_multiple(SMALL_SIZE);
    benchmark_pop_multiple(SMALL_SIZE);
    benchmark_push_multiple(MEDIUM_SIZE);
    benchmark_pop_multiple(MEDIUM_SIZE);
    benchmark_push_multiple(LARGE_SIZE);
    benchmark_pop_multiple(LARGE_SIZE);
    return 0;
}
