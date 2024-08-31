#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void displayMenu() {
    printf("\n--- Scientific Calculator ---\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Sine\n");
    printf("6. Cosine\n");
    printf("7. Tangent\n");
    printf("8. Logarithm (base 10)\n");
    printf("9. Square Root\n");
    printf("0. Exit\n");
    printf("-----------------------------\n");
}

int main() {
    int choice;
    double num1, num2, result;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Addition
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                result = num1 + num2;
                printf("Result: %.2lf\n", result);
                break;

            case 2: // Subtraction
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                result = num1 - num2;
                printf("Result: %.2lf\n", result);
                break;

            case 3: // Multiplication
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                result = num1 * num2;
                printf("Result: %.2lf\n", result);
                break;

            case 4: // Division
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                if (num2 != 0) {
                    result = num1 / num2;
                    printf("Result: %.2lf\n", result);
                } else {
                    printf("Error: Division by zero!\n");
                }
                break;

            case 5: // Sine
                printf("Enter an angle in degrees: ");
                scanf("%lf", &num1);
                result = sin(num1 * M_PI / 180.0); // Convert degrees to radians
                printf("Result: %.2lf\n", result);
                break;

            case 6: // Cosine
                printf("Enter an angle in degrees: ");
                scanf("%lf", &num1);
                result = cos(num1 * M_PI / 180.0); // Convert degrees to radians
                printf("Result: %.2lf\n", result);
                break;

            case 7: // Tangent
                printf("Enter an angle in degrees: ");
                scanf("%lf", &num1);
                result = tan(num1 * M_PI / 180.0); // Convert degrees to radians
                printf("Result: %.2lf\n", result);
                break;

            case 8: // Logarithm
                printf("Enter a number: ");
                scanf("%lf", &num1);
                if (num1 > 0) {
                    result = log10(num1);
                    printf("Result: %.2lf\n", result);
                } else {
                    printf("Error: Logarithm of non-positive number!\n");
                }
                break;

            case 9: // Square Root
                printf("Enter a number: ");
                scanf("%lf", &num1);
                if (num1 >= 0) {
                    result = sqrt(num1);
                    printf("Result: %.2lf\n", result);
                } else {
                    printf("Error: Square root of negative number!\n");
                }
                break;

            case 0: // Exit
                printf("Exiting the calculator. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}