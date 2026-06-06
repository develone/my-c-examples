#include <stdio.h>
/*
Method 2: Pass by Value
gcc -Wall -Werror struct-method2.c -o struct-method2
./struct-method2 
Name: Alice, Age: 21
*/

// Define the structure
struct Car {
    char model[30];
    int year;
};

// Function accepts the entire structure as a value copy
void displayCar(struct Car c) {
    // Use the . operator to access members
    printf("Model: %s\n", c.model);
    printf("Year: %d\n", c.year);
}

int main() {
    struct Car myCar = {"Mustang", 1969};

    // Pass the entire structure variable directly
    displayCar(myCar);

    return 0;
}