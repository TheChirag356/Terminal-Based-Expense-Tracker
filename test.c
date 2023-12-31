#include <stdio.h>

int main() {
    double myDouble = 3.14159; // Replace this with your double value
    char myString[20]; // Adjust the size based on your requirements

    // Format the double value into a string
    sprintf(myString, "%f", myDouble);

    // Print the string
    printf("The double value as a string: %s\n", myString);

    return 0;
}
