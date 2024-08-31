#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define DATA_FILE "billing_records.txt"

// Structure to hold billing information
typedef struct BillingRecord {
    int id;
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    float amount;
    struct BillingRecord *next;
} BillingRecord;

// Function prototypes
void addRecord(BillingRecord **head);
void editRecord(BillingRecord *head);
void searchRecord(BillingRecord *head);
void deleteRecord(BillingRecord **head);
void displayRecords(BillingRecord *head);
void freeRecords(BillingRecord *head);
void saveRecordsToFile(BillingRecord *head);
void loadRecordsFromFile(BillingRecord **head);
void sortRecords(BillingRecord **head);
float calculateTotalAmount(BillingRecord *head);
void searchByName(BillingRecord *head);

int main() {
    BillingRecord *head = NULL;
    loadRecordsFromFile(&head); // Load records from file at startup
    int choice;

    do {
        printf("\nTelecom Billing System\n");
        printf("1. Add Record\n");
        printf("2. Edit Record\n");
        printf("3. Search Record by ID\n");
        printf("4. Search Record by Name\n");
        printf("5. Delete Record\n");
        printf("6. Display All Records\n");
        printf("7. Sort Records\n");
        printf("8. Calculate Total Amount\n");
        printf("9. Exit\n");
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
                searchRecord(head);
                break;
            case 4:
                searchByName(head);
                break;
            case 5:
                deleteRecord(&head);
                break;
            case 6:
                displayRecords(head);
                break;
            case 7:
                sortRecords(&head);
                break;
            case 8:
                printf("Total Amount Billed: %.2f\n", calculateTotalAmount(head));
                break;
            case 9:
                saveRecordsToFile(head); // Save records to file before exit
                freeRecords(head);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

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
    scanf("%d", &newRecord->id);
    getchar(); // Consume newline character
    printf("Enter Name: ");
    fgets(newRecord->name, MAX_NAME_LENGTH, stdin);
    newRecord->name[strcspn(newRecord->name, "\n")] = 0; // Remove newline character
    printf("Enter Phone: ");
    fgets(newRecord->phone, MAX_PHONE_LENGTH, stdin);
    newRecord->phone[strcspn(newRecord->phone, "\n")] = 0; // Remove newline character
    printf("Enter Amount: ");
    scanf("%f", &newRecord->amount);
    newRecord->next = *head; // Insert at the beginning
    *head = newRecord;

    printf("Record added successfully!\n");
}

// Function to edit a record
void editRecord(BillingRecord *head) {
    int id;
    printf("Enter ID of the record to edit: ");
    scanf("%d", &id);
    getchar(); // Consume newline character

    BillingRecord *current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Editing Record ID: %d\n", current->id);
            printf("Enter New Name: ");
            fgets(current->name, MAX_NAME_LENGTH, stdin);
            current->name[strcspn(current->name, "\n")] = 0; // Remove newline character
            printf("Enter New Phone: ");
            fgets(current->phone, MAX_PHONE_LENGTH, stdin);
            current->phone[strcspn(current->phone, "\n")] = 0; // Remove newline character
            printf("Enter New Amount: ");
            scanf("%f", &current->amount);
            printf("Record updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Record not found.\n");
}

// Function to search for a record by ID
void searchRecord(BillingRecord *head) {
    int id;
    printf("Enter ID of the record to search: ");
    scanf("%d", &id);

    BillingRecord *current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Record Found:\n");
            printf("ID: %d\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Phone: %s\n", current->phone);
            printf("Amount: %.2f\n", current->amount);
            return;
        }
        current = current->next;
    }
    printf("Record not found.\n");
}

// Function to search for a record by Name
void searchByName(BillingRecord *head) {
    char name[MAX_NAME_LENGTH];
    printf("Enter Name of the record to search: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character

    BillingRecord *current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("Record Found:\n");
            printf("ID: %d\n", current->id);
            printf("Phone: %s\n", current->phone);
            printf("Amount: %.2f\n", current->amount);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("Record not found.\n");
    }
}

// Function to delete a record
void deleteRecord(BillingRecord **head) {
    int id;
    printf("Enter ID of the record to delete: ");
    scanf("%d", &id);

    BillingRecord *current = *head;
    BillingRecord *previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
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
        printf("ID: %d, Name: %s, Phone: %s, Amount: %.2f\n", current->id, current->name, current->phone, current->amount);
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

// Function to sort records by ID
void sortRecords(BillingRecord **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // No need to sort
    }

    BillingRecord *current, *next;
    int swapped;

    do {
        swapped = 0;
        current = *head;

        while (current->next != NULL) {
            next = current->next;
            if (current->id > next->id) {
                // Swap records
                int tempID = current->id;
                char tempName[MAX_NAME_LENGTH];
                char tempPhone[MAX_PHONE_LENGTH];
                float tempAmount = current->amount;

                strcpy(tempName, current->name);
                strcpy(tempPhone, current->phone);

                current->id = next->id;
                strcpy(current->name, next->name);
                strcpy(current->phone, next->phone);
                current->amount = next->amount;

                next->id = tempID;
                strcpy(next->name, tempName);
                strcpy(next->phone, tempPhone);
                next->amount = tempAmount;

                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
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
        fprintf(file, "%d,%s,%s,%.2f\n", current->id, current->name, current->phone, current->amount);
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
        if (fscanf(file, "%d,%49[^,],%14[^,],%f\n", &newRecord->id, newRecord->name, newRecord->phone, &newRecord->amount) == 4) {
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