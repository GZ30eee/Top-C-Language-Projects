#include <stdio.h>

void convertLength();
void convertWeight();
void convertTemperature();
void convertVolume();

int main() {
    int option;

    while (1) {
        printf("\n--- Unit Converter ---\n");
        printf("1. Length Conversion\n");
        printf("2. Weight Conversion\n");
        printf("3. Temperature Conversion\n");
        printf("4. Volume Conversion\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                convertLength();
                break;
            case 2:
                convertWeight();
                break;
            case 3:
                convertTemperature();
                break;
            case 4:
                convertVolume();
                break;
            case 0:
                printf("Exiting the unit converter. Goodbye!\n");
                return 0;
            default:
                printf("Invalid option! Please try again.\n");
        }
    }
}

// Function to convert length
void convertLength() {
    int choice;
    double value, result;

    printf("\n--- Length Conversion ---\n");
    printf("1. Meters to Kilometers\n");
    printf("2. Kilometers to Meters\n");
    printf("3. Miles to Kilometers\n");
    printf("4. Kilometers to Miles\n");
    printf("5. Feet to Meters\n");
    printf("6. Meters to Feet\n");
    printf("Select a conversion: ");
    scanf("%d", &choice);

    printf("Enter the value to convert: ");
    scanf("%lf", &value);

    switch (choice) {
        case 1:
            result = value / 1000;
            printf("%.2lf Meters = %.2lf Kilometers\n", value, result);
            break;
        case 2:
            result = value * 1000;
            printf("%.2lf Kilometers = %.2lf Meters\n", value, result);
            break;
        case 3:
            result = value * 1.60934;
            printf("%.2lf Miles = %.2lf Kilometers\n", value, result);
            break;
        case 4:
            result = value / 1.60934;
            printf("%.2lf Kilometers = %.2lf Miles\n", value, result);
            break;
        case 5:
            result = value * 0.3048;
            printf("%.2lf Feet = %.2lf Meters\n", value, result);
            break;
        case 6:
            result = value / 0.3048;
            printf("%.2lf Meters = %.2lf Feet\n", value, result);
            break;
        default:
            printf("Invalid option!\n");
    }
}

// Function to convert weight
void convertWeight() {
    int choice;
    double value, result;

    printf("\n--- Weight Conversion ---\n");
    printf("1. Kilograms to Grams\n");
    printf("2. Grams to Kilograms\n");
    printf("3. Pounds to Kilograms\n");
    printf("4. Kilograms to Pounds\n");
    printf("5. Ounces to Grams\n");
    printf("6. Grams to Ounces\n");
    printf("Select a conversion: ");
    scanf("%d", &choice);

    printf("Enter the value to convert: ");
    scanf("%lf", &value);

    switch (choice) {
        case 1:
            result = value * 1000;
            printf("%.2lf Kilograms = %.2lf Grams\n", value, result);
            break;
        case 2:
            result = value / 1000;
            printf("%.2lf Grams = %.2lf Kilograms\n", value, result);
            break;
        case 3:
            result = value * 0.453592;
            printf("%.2lf Pounds = %.2lf Kilograms\n", value, result);
            break;
        case 4:
            result = value / 0.453592;
            printf("%.2lf Kilograms = %.2lf Pounds\n", value, result);
            break;
        case 5:
            result = value * 28.3495;
            printf("%.2lf Ounces = %.2lf Grams\n", value, result);
            break;
        case 6:
            result = value / 28.3495;
            printf("%.2lf Grams = %.2lf Ounces\n", value, result);
            break;
        default:
            printf("Invalid option!\n");
    }
}

// Function to convert temperature
void convertTemperature() {
    int choice;
    double value, result;

    printf("\n--- Temperature Conversion ---\n");
    printf("1. Celsius to Fahrenheit\n");
    printf("2. Fahrenheit to Celsius\n");
    printf("3. Celsius to Kelvin\n");
    printf("4. Kelvin to Celsius\n");
    printf("5. Fahrenheit to Kelvin\n");
    printf("6. Kelvin to Fahrenheit\n");
    printf("Select a conversion: ");
    scanf("%d", &choice);

    printf("Enter the value to convert: ");
    scanf("%lf", &value);

    switch (choice) {
        case 1:
            result = (value * 9/5) + 32;
            printf("%.2lf Celsius = %.2lf Fahrenheit\n", value, result);
            break;
        case 2:
            result = (value - 32) * 5/9;
            printf("%.2lf Fahrenheit = %.2lf Celsius\n", value, result);
            break;
        case 3:
            result = value + 273.15;
            printf("%.2lf Celsius = %.2lf Kelvin\n", value, result);
            break;
        case 4:
            result = value - 273.15;
            printf("%.2lf Kelvin = %.2lf Celsius\n", value, result);
            break;
        case 5:
            result = (value - 32) * 5/9 + 273.15;
            printf("%.2lf Fahrenheit = %.2lf Kelvin\n", value, result);
            break;
        case 6:
            result = (value - 273.15) * 9/5 + 32;
            printf("%.2lf Kelvin = %.2lf Fahrenheit\n", value, result);
            break;
        default:
            printf("Invalid option!\n");
    }
}

// Function to convert volume
void convertVolume() {
    int choice;
    double value, result;

    printf("\n--- Volume Conversion ---\n");
    printf("1. Liters to Milliliters\n");
    printf("2. Milliliters to Liters\n");
    printf("3. Gallons to Liters\n");
    printf("4. Liters to Gallons\n");
    printf("5. Quarts to Liters\n");
    printf("6. Liters to Quarts\n");
    printf("Select a conversion: ");
    scanf("%d", &choice);

    printf("Enter the value to convert: ");
    scanf("%lf", &value);

    switch (choice) {
        case 1:
            result = value * 1000;
            printf("%.2lf Liters = %.2lf Milliliters\n", value, result);
            break;
        case 2:
            result = value / 1000;
            printf("%.2lf Milliliters = %.2lf Liters\n", value, result);
            break;
        case 3:
            result = value * 3.78541;
            printf("%.2lf Gallons = %.2lf Liters\n", value, result);
            break;
        case 4:
            result = value / 3.78541;
            printf("%.2lf Liters = %.2lf Gallons\n", value, result);
            break;
        case 5:
            result = value * 0.946353;
            printf("%.2lf Quarts = %.2lf Liters\n", value, result);
            break;
        case 6:
            result = value / 0.946353;
            printf("%.2lf Liters = %.2lf Quarts\n", value, result);
            break;
        default:
            printf("Invalid option!\n");
    }
}