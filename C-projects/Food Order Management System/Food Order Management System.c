#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOOD_ITEMS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
} FoodItem;

FoodItem menu[MAX_FOOD_ITEMS];
int foodCount = 0;

void addFoodItem() {
    if (foodCount >= MAX_FOOD_ITEMS) {
        printf("Menu is full! Cannot add more items.\n");
        return;
    }
    printf("Enter food item name: ");
    scanf("%s", menu[foodCount].name);
    printf("Enter food item price: ");
    scanf("%f", &menu[foodCount].price);
    foodCount++;
    printf("Food item added successfully!\n");
}

void displayMenu() {
    printf("\n--- Food Menu ---\n");
    for (int i = 0; i < foodCount; i++) {
        printf("%d. %s - $%.2f\n", i + 1, menu[i].name, menu[i].price);
    }
    printf("------------------\n");
}

void placeOrder() {
    int choice;
    float totalCost = 0.0;
    char orderSummary[500] = "Order Summary:\n";

    while (1) {
        displayMenu();
        printf("Select food item by number (0 to finish): ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        } else if (choice < 1 || choice > foodCount) {
            printf("Invalid choice! Please try again.\n");
        } else {
            totalCost += menu[choice - 1].price;
            strcat(orderSummary, menu[choice - 1].name);
            strcat(orderSummary, "\n");
            printf("Added %s to your order.\n", menu[choice - 1].name);
        }
    }

    printf("\n%sTotal Cost: $%.2f\n", orderSummary, totalCost);
}

int main() {
    int option;

    while (1) {
        printf("\n--- Food Order Management System ---\n");
        printf("1. Add Food Item\n");
        printf("2. Display Menu\n");
        printf("3. Place Order\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addFoodItem();
                break;
            case 2:
                displayMenu();
                break;
            case 3:
                placeOrder();
                break;
            case 0:
                printf("Exiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid option! Please try again.\n");
        }
    }

    return 0;
}