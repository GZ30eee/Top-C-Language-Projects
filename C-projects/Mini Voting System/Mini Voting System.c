#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // For _getch() to hide input

#define MAX_CANDIDATES 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int votes;
} Candidate;

Candidate candidates[MAX_CANDIDATES];
int candidateCount = 0;

// Function prototypes
void addCandidate();
void editCandidate();
void viewResults();
void displayCandidates();
void vote();
int adminLogin();

int main() {
    int option;

    while (1) {
        printf("\n--- Mini Voting System ---\n");
        printf("1. Admin\n");
        printf("2. User\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);
        getchar(); // Consume newline character

        switch (option) {
            case 1:
                if (adminLogin()) {
                    int adminOption;
                    while (1) {
                        printf("\n--- Admin Menu ---\n");
                        printf("1. Add Candidate\n");
                        printf("2. Edit Candidate\n");
                        printf("3. View Results\n");
                        printf("0. Logout\n");
                        printf("Select an option: ");
                        scanf("%d", &adminOption);
                        getchar(); // Consume newline character

                        switch (adminOption) {
                            case 1:
                                addCandidate();
                                break;
                            case 2:
                                editCandidate();
                                break;
                            case 3:
                                viewResults();
                                break;
                            case 0:
                                printf("Logging out...\n");
                                goto main_menu; // Go to the main menu
                            default:
                                printf("Invalid option! Please try again.\n");
                        }
                    }
                }
                break;

            case 2:
                vote();
                break;

            case 0:
                printf("Exiting the voting system. Goodbye!\n");
                exit(0);

            main_menu:
            default:
                printf("Invalid option! Please try again.\n");
        }
    }

    return 0;
}

// Function to handle admin login with masked password input
int adminLogin() {
    const char *password = "admin123"; // Password for admin
    char inputPassword[20];
    int i = 0;
    char ch;

    printf("Enter admin password: ");
    while (1) {
        ch = _getch(); // Get character without echoing
        if (ch == '\r') { // Enter key
            inputPassword[i] = '\0'; // Null-terminate the string
            break;
        } else if (ch == '\b') { // Backspace key
            if (i > 0) {
                i--;
                printf("\b \b"); // Move back, print space, move back again
            }
        } else {
            inputPassword[i++] = ch;
            printf("*"); // Print asterisk for each character
        }
    }
    printf("\n");

    if (strcmp(inputPassword, password) == 0) {
        printf("Login successful!\n");
        return 1; // Login successful
    } else {
        printf("Incorrect password! Access denied.\n");
        return 0; // Login failed
    }
}

// Function to add a candidate
void addCandidate() {
    if (candidateCount >= MAX_CANDIDATES) {
        printf("Maximum number of candidates reached!\n");
        return;
    }
    printf("Enter candidate name: ");
    scanf("%s", candidates[candidateCount].name);
    candidates[candidateCount].votes = 0; // Initialize votes to 0
    candidateCount++;
    printf("Candidate added successfully!\n");
}

// Function to edit a candidate
void editCandidate() {
    int id;
    printf("Enter candidate ID to edit (1 to %d): ", candidateCount);
    scanf("%d", &id);
    getchar(); // Consume newline character

    if (id < 1 || id > candidateCount) {
        printf("Invalid candidate ID!\n");
        return;
    }

    printf("Enter new name for candidate %d: ", id);
    scanf("%s", candidates[id - 1].name);
    printf("Candidate updated successfully!\n");
}

// Function to view voting results
void viewResults() {
    printf("\n--- Voting Results ---\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s: %d votes\n", i + 1, candidates[i].name, candidates[i].votes);
    }
}

// Function to display candidates
void displayCandidates() {
    printf("\n--- Candidates ---\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }
}

// Function to vote for a candidate with masked input
void vote() {
    displayCandidates();
    int id;
    printf("Enter the candidate ID you want to vote for: ");
    scanf("%d", &id);
    getchar(); // Consume newline character

    if (id < 1 || id > candidateCount) {
        printf("Invalid candidate ID!\n");
        return;
    }

    candidates[id - 1].votes++;
    printf("Vote cast for %s!\n", candidates[id - 1].name);
}