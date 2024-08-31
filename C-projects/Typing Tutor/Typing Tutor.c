#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 256
#define NUM_DIFFICULTY_LEVELS 3
#define NUM_SENTENCES 3

void clearBuffer() {
    while (getchar() != '\n');
}

void displayInstructions() {
    printf("Welcome to the Typing Tutor!\n");
    printf("You will be given a sentence to type as quickly and accurately as possible.\n");
    printf("Press Enter to start...\n");
    clearBuffer();
}

int getDifficultyLevel() {
    int level;
    printf("Select difficulty level (1-3): ");
    scanf("%d", &level);
    clearBuffer();
    return level;
}

void getTypingTest(char *sentence, int difficultyLevel) {
    char sentences[NUM_SENTENCES][MAX_LENGTH] = {
        "The quick brown fox jumps over the lazy dog.",
        "Sphinx of black quartz, judge my vow.",
        "Amazingly few discotheques provide jukeboxes."
    };

    switch (difficultyLevel) {
        case 1:
            strcpy(sentence, sentences[0]);
            break;
        case 2:
            strcpy(sentence, sentences[1]);
            break;
        case 3:
            strcpy(sentence, sentences[2]);
            break;
        default:
            printf("Invalid difficulty level. Using default level.\n");
            strcpy(sentence, sentences[0]);
            break;
    }
}

void displayLeaderboard(char *username, double wpm, double accuracy) {
    FILE *file = fopen("leaderboard.txt", "a");
    if (file == NULL) {
        printf("Error opening leaderboard file.\n");
        return;
    }

    fprintf(file, "%s,%.2f,%.2f%%\n", username, wpm, accuracy * 100.0);
    fclose(file);
}

int main() {
    char sentence[MAX_LENGTH];
    char userInput[MAX_LENGTH];
    char username[MAX_LENGTH];
    clock_t start, end;
    double timeTaken;
    int correctChars = 0;
    int difficultyLevel;

    displayInstructions();

    printf("Enter your username: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    difficultyLevel = getDifficultyLevel();
    getTypingTest(sentence, difficultyLevel);

    printf("\nType the following sentence:\n");
    printf("%s\n", sentence);

    // Start the timer
    start = clock();

    // Read user input
    printf("Your input: ");
    fgets(userInput, MAX_LENGTH, stdin);
    
    // Stop the timer
    end = clock();
    
    // Calculate time taken
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;

    // Remove the newline character from user input
    userInput[strcspn(userInput, "\n")] = 0;

    // Calculate correct characters
    for (int i = 0; i < strlen(sentence); i++) {
        if (sentence[i] == userInput[i]) {
            correctChars++;
        }
    }

    // Calculate accuracy
    double accuracy = (double)correctChars / strlen(sentence);

    // Calculate WPM
    int wordsTyped = strlen(userInput) / 5; // Average word length is considered to be 5 characters
    double wpm = (timeTaken > 0) ? (wordsTyped / (timeTaken / 60)) : 0;

    // Display results
    printf("\nResults:\n");
    printf("Time taken: %.2f seconds\n", timeTaken);
    printf("Correct characters: %d out of %lu\n", correctChars, strlen(sentence));
    printf("Accuracy: %.2f%%\n", accuracy * 100.0);
    printf("Typing speed: %.2f WPM\n", wpm);

    displayLeaderboard(username, wpm, accuracy);

    return 0;
}