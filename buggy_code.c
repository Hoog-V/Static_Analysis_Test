#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int shared_counter = 0; // Onjuist gedeelde variabele zonder synchronisatie (Race Condition)

void *race_condition(void *arg) {
    for (int i = 0; i < 1000; i++) {
        shared_counter++; // Geen mutex, race condition mogelijk
    }
    return NULL;
}

void buffer_overflow() {
    char buffer[10];
    strcpy(buffer, "Dit is een veel te lange string!"); // Buffer overflow
    printf("Buffer: %s\n", buffer);
}

void null_pointer_dereference() {
    int *ptr = NULL;
    *ptr = 42; // Null pointer dereference
}

void memory_leak() {
    int *leak = (int *)malloc(100 * sizeof(int));
    // Geheugen wordt nooit vrijgegeven (memory leak)
}

void double_free() {
    int *data = (int *)malloc(sizeof(int));
    free(data);
    free(data); // Dubbele vrijgave (double free)
}

void use_after_free() {
    int *data = (int *)malloc(sizeof(int));
    free(data);
    *data = 10; // Gebruik na free (use-after-free)
}

void integer_overflow() {
    unsigned int max = 4294967295; // Max waarde van unsigned int
    max = max + 1; // Integer overflow
    printf("Integer Overflow Result: %u\n", max);
}

void stack_overflow(int count) {
    int large_array[10000]; // Grote array op de stack
    printf("Stack overflow test: %d\n", count);
    stack_overflow(count + 1); // Oneindige recursie leidt tot stack overflow
}

void format_string_vuln() {
    char user_input[100];
    printf("Voer een string in: ");
    scanf("%99s", user_input);
    printf(user_input); // Format string kwetsbaarheid (printf zonder format specifier)
}

void uninitialized_variable() {
    int x;
    printf("Ongeïnitialiseerde variabele: %d\n", x); // Mogelijk ongedefinieerde waarde
}

void create_race_condition() {
    // Threads starten zonder synchronisatie → Race condition
    pthread_t t1, t2;
    pthread_create(&t1, NULL, race_condition, NULL);
    pthread_create(&t2, NULL, race_condition, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Race Condition Result: %d\n", shared_counter);
}

int main() {
    printf("Start van het programma\n");
    create_race_condition();
    buffer_overflow();
    null_pointer_dereference(); // Zal crashen
    memory_leak();
    double_free();
    use_after_free();
    integer_overflow();
    stack_overflow(1); // LET OP: Dit veroorzaakt een crash
    format_string_vuln();
    uninitialized_variable();

    printf("Einde van het programma\n");
    return 0;
}
