#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "stack.h"

#define SMALL_SIZE     100
#define MEDIUM_SIZE    1000
#define LARGE_SIZE     10000

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    bool running;

public:
    Timer() : running(false) {}

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
        running = true;
    }

    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
        running = false;
    }

    double elapsed_ms() const {
        auto end = running ? std::chrono::high_resolution_clock::now() : end_time;
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start_time);
        return duration.count() / 1000.0;
    }

    int64_t elapsed_us() const {
        auto end = running ? std::chrono::high_resolution_clock::now() : end_time;
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start_time).count();
    }

    int64_t elapsed_ns() const {
        auto end = running ? std::chrono::high_resolution_clock::now() : end_time;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start_time).count();
    }
};

void benchmark_push_single() {
    printf("\n=== Benchmark: Single Push ===\n");

    Stack s;
    initStack(&s);

    Timer timer;
	timer.start()

    if (!push(&s, 42)) {
        fprintf(stderr, "Push failed!\n");
        return;
    }

    timer.stop()
	double timer_ms = timer.elapsed_ms()

    printf("Operation: push single element\n");
    printf("Time taken to complete benchmark: %.5f seconds\n", timer_ms);
    printf("Result: %s\n", (s.top != NULL && s.top->data == 42) ? "OK" : "FAIL");

    destroyStack(&s);
}

void benchmark_push_multiple(int num_elements) {
    printf("\n=== Benchmark: Push %d elements ===\n", num_elements);

    Stack s;
    initStack(&s);


    for (int i = 0; i < num_elements; i++) {
        if (!push(&s, i)) {
            fprintf(stderr, "Push failed at iteration %d\n", i);
            destroyStack(&s);
            return;
        }
    }

    printf("Total elements: %d\n", num_elements);

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
    printf("\n=== Benchmark: Single Pop ===\n");

    Stack s;
    initStack(&s);
    push(&s, 42);

    int value;
    if (!pop(&s, &value)) {
        fprintf(stderr, "Pop failed!\n");
        destroyStack(&s);
        return;
    }


    printf("Operation: pop single element\n");
    printf("Popped value: %d (expected: 42)\n", value);
    printf("Stack empty after pop: %s\n", isEmpty(&s) ? "YES" : "NO");

    destroyStack(&s);
}

void benchmark_pop_multiple(int num_elements) {
    printf("\n=== Benchmark: Pop %d elements ===\n", num_elements);
    Stack s;
    initStack(&s);

    for (int i = 0; i < num_elements; i++) {
        push(&s, i);
    }

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

    printf("Attempted pops: %d\n", num_elements);
    printf("Successful pops: %d\n", successful_pops);
    printf("Stack empty after all pops: %s\n", isEmpty(&s) ? "YES" : "NO");

    destroyStack(&s);
}

void benchmark_push_pop_alternating(int num_operations) {
    printf("\n=== Benchmark: Alternating Push/Pop (%d ops) ===\n", num_operations);

    Stack s;
    initStack(&s);

    int value;
    int push_count = 0;
    int pop_count = 0;

    for (int i = 0; i < num_operations; i++) {
        if (i % 2 == 0) {
            if (push(&s, i)) {
                push_count++;
            }
        }
        else {
            if (pop(&s, &value)) {
                pop_count++;
            }
        }
    }
	
    printf("Total operations: %d\n", num_operations);
    printf("  Push operations: %d\n", push_count);
    printf("  Pop operations: %d\n", pop_count);
	
    int remaining = 0;
    while (!isEmpty(&s)) {
        pop(&s, &value);
        remaining++;
    }
    printf("Remaining elements cleared: %d\n", remaining);

    destroyStack(&s);
}

void benchmark_push_pop_sequence(int sequence_size, int repetitions) {
    printf("\n=== Benchmark: Push/Pop Sequence (size=%d, reps=%d) ===\n",
        sequence_size, repetitions);

    Stack s;
    initStack(&s);

    int value;
    int total_operations = 0;

    for (int rep = 0; rep < repetitions; rep++) {
        for (int i = 0; i < sequence_size; i++) {
            push(&s, i + rep * sequence_size);
            total_operations++;
        }

        for (int i = 0; i < sequence_size; i++) {
            pop(&s, &value);
            total_operations++;
        }
    }

    printf("Sequence size: %d\n", sequence_size);
    printf("Repetitions: %d\n", repetitions);
    printf("Total operations: %d\n", total_operations);
    printf("Stack empty at end: %s\n", isEmpty(&s) ? "YES" : "NO");

    destroyStack(&s);
}

void benchmark_empty_stack_operations() {
    printf("\n=== Benchmark: Empty Stack Operations ===\n");

    Stack s;
    initStack(&s);

    int value;
    int iterations = 1000000;
    int failed_pops = 0;
	
    for (int i = 0; i < iterations; i++) {
        if (!pop(&s, &value)) {
            failed_pops++;
        }
    }

    printf("Operations: pop from empty stack\n");
    printf("Iterations: %d\n", iterations);
    printf("Failed pops (expected): %d\n", failed_pops);
    destroyStack(&s);
}

void benchmark_small_stacks() {
    printf("\n=== Benchmark: Small Stacks ===\n");

    int sizes[] = { 1, 2, 5, 10, 20, 50, 100 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];

        Stack s;
        initStack(&s);

        for (int j = 0; j < size; j++) {
            push(&s, j);
        }

        int value;
        for (int j = 0; j < size; j++) {
            pop(&s, &value);
        }

        destroyStack(&s);
    }
}

int main() {
    printf("========================================\n");
    printf("        STACK BENCHMARK SUITE\n");
    printf("========================================\n");

    printf("\nSystem information:\n");
    printf("Clock ticks per second: %ld\n", CLOCKS_PER_SEC);
    printf("sizeof(Node): %zu bytes\n", sizeof(Node));
    printf("sizeof(Stack): %zu bytes\n", sizeof(Stack));
    printf("\nWarming up...\n");
    Stack warmup;
    initStack(&warmup);
    for (int i = 0; i < 1000; i++) {
        push(&warmup, i);
        int val;
        pop(&warmup, &val);
    }
    destroyStack(&warmup);
    printf("\nStarting benchmarks...\n");
    benchmark_push_single();
    benchmark_pop_single();
    benchmark_push_multiple(SMALL_SIZE);
    benchmark_pop_multiple(SMALL_SIZE);
    benchmark_push_multiple(MEDIUM_SIZE);
    benchmark_pop_multiple(MEDIUM_SIZE);
    benchmark_push_multiple(LARGE_SIZE);
    benchmark_pop_multiple(LARGE_SIZE);
    benchmark_push_pop_alternating(SMALL_SIZE * 2);
    benchmark_push_pop_sequence(100, 100);
    benchmark_empty_stack_operations();
    benchmark_small_stacks();

    printf("\n========================================\n");
    printf("        BENCHMARK COMPLETE\n");
    printf("========================================\n");

    return 0;
}
