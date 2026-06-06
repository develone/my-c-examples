#include <stdio.h>
#include <stdint.h>

int main() {
    long long my_number = 42LL;
    
    // 1. Declare and initialize a pointer to a long long
    long long *ptr = &my_number;
    
    // 2. Cast the pointer to a 64-bit unsigned integer
    // uintptr_t guarantees the integer is the exact same size as the pointer
    uintptr_t address_val = (uintptr_t)ptr;
    
    // 3. Print the results
    printf("Value of my_number: %lld\n", *ptr);
    printf("Size of pointer: %zu bytes\n", sizeof(ptr));
    printf("Address (in hex): %p\n", (void *)ptr);
    printf("Address (as 64-bit integer): 0x%016llx\n", (unsigned long long)address_val);
    
    return 0;
}