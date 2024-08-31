#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 15
#define DATA_FILE "school_billing_records.txt"

// Structure to hold billing information
typedef struct BillingRecord {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char role; // 'S' for Student, 'T' for Teacher
    float amount;
    struct BillingRecord *next;
} BillingRecord;

// Function prototypes
void addRecord(BillingRecord **head);
void editRecord(BillingRecord *head);
void deleteRecord(BillingRecord **head);
void displayRecords(BillingRecord *head);
void freeRecords(BillingRecord *head);
void saveRecordsToFile(BillingRecord *head);
void loadRecordsFromFile(BillingRecord **head);
float calculateTotalAmount(BillingRecord *head);

int main() {
    BillingRecord *head = NULL;
    loadRecordsFromFile(&head); // Load records from file at startup
    int choice;

    do {
        printf("\nSchool Billing System\n");
        printf("1. Add Record\n");
        printf("2. Edit Record\n");
        printf("3. Delete Record\n");
        printf("4. Display All Records\n");
        printf("5. Calculate Total Amount\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                addRecord(&head);
                break;
            case 2:
                editRecord(head);
                break;
            case 3:
                deleteRecord(&head);
                break;
            case 4:
                displayRecords(head);
                break;
            case 5:
                printf("Total Amount: %.2f\n", calculateTotalAmount(head));
                break;
            case 6:
                saveRecordsToFile(head); // Save records to file before exit
                freeRecords(head);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to add a record
void addRecord(BillingRecord **head) {
    BillingRecord *newRecord = (BillingRecord *)malloc(sizeof(BillingRecord));
    if (!newRecord) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter ID: ");
    fgets(newRecord->id, MAX_ID_LENGTH, stdin);
    newRecord->id[strcspn(newRecord->id, "\n")] = 0; // Remove newline character
    printf("Enter Name: ");
    fgets(newRecord->name, MAX_NAME_LENGTH, stdin);
    newRecord->name[strcspn(newRecord->name, "\n")] = 0; // Remove newline character
    printf("Enter Role (S for Student, T for Teacher): ");
    scanf(" %c", &newRecord->role);
    printf("Enter Amount: ");
    scanf("%f", &newRecord->amount);
    newRecord->next = *head; // Insert at the beginning
    *head = newRecord;

    printf("Record added successfully!\n");
}

// Function to edit a record
void editRecord(BillingRecord *head) {
    char id[MAX_ID_LENGTH];
    printf("Enter ID of the record to edit: ");
    fgets(id, MAX_ID_LENGTH, stdin);
    id[strcspn(id, "\n")] = 0; // Remove newline character

    BillingRecord *current = head;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            printf("Editing Record ID: %s\n", current->id);
            printf("Enter New Name: ");
            fgets(current->name, MAX_NAME_LENGTH, stdin);
            current->name[strcspn(current->name, "\n")] = 0; // Remove newline character
            printf("Enter New Role (S for Student, T for Teacher): ");
            scanf(" %c", &current->role);
            printf("Enter New Amount: ");
            scanf("%f", &current->amount);
            printf("Record updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Record not found.\n");
}

// Function to delete a record
void deleteRecord(BillingRecord **head) {
    char id[MAX_ID_LENGTH];
    printf("Enter ID of the record to delete: ");
    fgets(id, MAX_ID_LENGTH, stdin);
    id[strcspn(id, "\n")] = 0; // Remove newline character

    BillingRecord *current = *head;
    BillingRecord *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            if (previous == NULL) {
                *head = current->next; // Deleting the first record
            } else {
                previous->next = current->next; // Bypass the current record
            }
            free(current);
            printf("Record deleted successfully!\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Record not found.\n");
}

// Function to display all records
void displayRecords(BillingRecord *head) {
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }

    BillingRecord *current = head;
    printf("\nAll Records:\n");
    while (current != NULL) {
        printf("ID: %s, Name: %s, Role: %c, Amount: %.2f\n", current->id, current->name, current->role, current->amount);
        current = current->next;
    }
}

// Function to calculate total amount billed
float calculateTotalAmount(BillingRecord *head) {
    float total = 0.0;
    BillingRecord *current = head;
    while (current != NULL) {
        total += current->amount;
        current = current->next;
    }
    return total;
}

// Function to save records to a file
void saveRecordsToFile(BillingRecord *head) {
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    BillingRecord *current = head;
    while (current != NULL) {
        fprintf(file, "%s,%s,%c,%.2f\n", current->id, current->name, current->role, current->amount);
        current = current->next;
    }

    fclose(file);
    printf("Records saved to file successfully!\n");
}

// Function to load records from a file
void loadRecordsFromFile(BillingRecord **head) {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("No existing records found.\n");
        return;
    }

    while (!feof(file)) {
        BillingRecord *newRecord = (BillingRecord *)malloc(sizeof(BillingRecord));
        if (fscanf(file, "%[^,],%[^,],%c,%f\n", newRecord->id, newRecord->name, &newRecord->role, &newRecord->amount) == 4) {
            newRecord->next = *head; // Insert at the beginning
            *head = newRecord;
        } else {
            free(newRecord); // Free memory if reading fails
        }
    }

    fclose(file);
    printf("Records loaded from file successfully!\n");
}

// Function to free all records
void freeRecords(BillingRecord *head) {
    BillingRecord *current = head;
    while (current != NULL) {
        BillingRecord *temp = current;
        current = current->next;
        free(temp);
    }
}