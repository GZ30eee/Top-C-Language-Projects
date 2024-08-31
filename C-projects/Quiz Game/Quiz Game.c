#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 10
#define MAX_QUESTION_LENGTH 256
#define MAX_OPTION_LENGTH 100
#define MAX_CATEGORY_LENGTH 50

typedef struct {
    char question[MAX_QUESTION_LENGTH];
    char options[4][MAX_OPTION_LENGTH]; // Four options (A, B, C, D)
    char answer; // Correct answer
} Question;

typedef struct {
    char name[MAX_CATEGORY_LENGTH];
    Question questions[MAX_QUESTIONS];
    int questionCount;
} QuizCategory;

// Function prototypes
void displayMenu();
void playQuiz(QuizCategory *category);
void displayScore(int score, int totalQuestions);
void loadQuestions(QuizCategory *category);
void clearBuffer();

int main() {
    QuizCategory category;
    strcpy(category.name, "General Knowledge");
    category.questionCount = 0;

    loadQuestions(&category); // Load questions into the category

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer(); // Consume newline character

        switch (choice) {
            case 1:
                playQuiz(&category);
                break;
            case 2:
                printf("Exiting the game. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 2);

    return 0;
}

// Function to display the main menu
void displayMenu() {
    printf("\n--- Quiz Game ---\n");
    printf("1. Play Quiz\n");
    printf("2. Exit\n");
}

// Function to load questions into the quiz category
void loadQuestions(QuizCategory *category) {
    // Sample questions for the quiz
    category->questions[0] = (Question) {
        "What is the capital of France?",
        {"A) Berlin", "B) Madrid", "C) Paris", "D) Rome"},
        'C'
    };
    category->questions[1] = (Question) {
        "Which planet is known as the Red Planet?",
        {"A) Earth", "B) Mars", "C) Jupiter", "D) Saturn"},
        'B'
    };
    category->questions[2] = (Question) {
        "What is the largest mammal in the world?",
        {"A) Elephant", "B) Blue Whale", "C) Giraffe", "D) Great White Shark"},
        'B'
    };
    category->questions[3] = (Question) {
        "Who wrote 'Romeo and Juliet'?",
        {"A) Mark Twain", "B) Charles Dickens", "C) William Shakespeare", "D) J.K. Rowling"},
        'C'
    };
    category->questions[4] = (Question) {
        "What is the chemical symbol for water?",
        {"A) O2", "B) H2O", "C) CO2", "D) NaCl"},
        'B'
    };
    category->questionCount = 5; // Total questions loaded
}

// Function to play the quiz
void playQuiz(QuizCategory *category) {
    int score = 0;
    char userAnswer;

    printf("\n--- Welcome to the %s Quiz ---\n", category->name);
    for (int i = 0; i < category->questionCount; i++) {
        printf("\nQuestion %d: %s\n", i + 1, category->questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%s\n", category->questions[i].options[j]);
        }
        printf("Your answer (A/B/C/D): ");
        scanf(" %c", &userAnswer);
        clearBuffer(); // Consume newline character

        if (userAnswer == category->questions[i].answer) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong! The correct answer is %c)\n", category->questions[i].answer);
        }
    }

    displayScore(score, category->questionCount);
}

// Function to display the score
void displayScore(int score, int totalQuestions) {
    printf("\n--- Quiz Completed ---\n");
    printf("Your Score: %d out of %d\n", score, totalQuestions);
}

// Function to clear the input buffer
void clearBuffer() {
    while (getchar() != '\n');
}