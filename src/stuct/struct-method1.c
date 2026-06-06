#include <stdio.h>
/*
Method 1: Pass by Reference (Recommended)
gcc -Wall -Werror struct-method1.c -o struct-method1
./struct-method1 
Name: Alice, Age: 21
*/
// Define the structure
struct Student {
    char name[50];
    int age;
};

// Function accepts a pointer to the structure
void updateStudent(struct Student *s) {
    s->age = 21; // Use the -> operator to modify members through a pointer
}

int main() {
    struct Student s1 = {"Alice", 20};

    // Pass the address of s1 using the & operator
    updateStudent(&s1);

    // Output will reflect the change: 21
    printf("Name: %s, Age: %d\n", s1.name, s1.age);

    return 0;
}