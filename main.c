#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h> // Include for strlen



// Define the maximum number of bugs and maximum length of fields
#define MAX_BUGS 100
#define MAX_TITLE_LEN 50
#define MAX_DESC_LEN 200
#define MAX_NAME_LEN 50

// Define priority levels
typedef enum {
    LOW,
    MEDIUM,
    HIGH
} Priority;

// Define status levels
typedef enum {
    OPEN,
    IN_PROGRESS,
    RESOLVED
} Status;

// Structure to hold reporter's name
typedef struct {
    char FirstName[MAX_NAME_LEN];
    char LastName[MAX_NAME_LEN];
} Reporter;

// Structure to represent a bug
typedef struct {
    char title[MAX_TITLE_LEN];
    char description[MAX_DESC_LEN];
    Reporter reporter;
    Priority priority;
    Status status;
    int linesOfCode;
    char functionInvolved[MAX_NAME_LEN];
    char solution[MAX_DESC_LEN];
    char whenItHappens[MAX_DESC_LEN];
} Bug;

// Global variables
Bug bugList[MAX_BUGS];
int bugCount = 0;

// Function declarations
void addBug();
void displayBugs();
void displayDetailedBug(int index);
void saveBugsToFile();
void loadBugsFromFile();
const char* getPriorityString(Priority priority);
const char* getStatusString(Status status);
void showMenu();

int main() {
    loadBugsFromFile();  // Load bugs from file at startup
    showMenu();
    return 0;


}

void addBug() {
    ClearConsole();
    if (bugCount >= MAX_BUGS) {
        printf("Error: Maximum number of bugs reached.\n");
        return;
    }

    Bug newBug;
    printf("Enter Bug Title: ");
    getchar(); // Consume the newline character left in the buffer
    fgets(newBug.title, sizeof(newBug.title), stdin);
    newBug.title[strcspn(newBug.title, "\n")] = 0; // Remove trailing newline

    printf("Enter Bug Description: ");
    fgets(newBug.description, sizeof(newBug.description), stdin);
    newBug.description[strcspn(newBug.description, "\n")] = 0;

    printf("Enter Reporter First Name: ");
    fgets(newBug.reporter.FirstName, sizeof(newBug.reporter.FirstName), stdin);
    newBug.reporter.FirstName[strcspn(newBug.reporter.FirstName, "\n")] = 0;

    printf("Enter Reporter Last Name: ");
    fgets(newBug.reporter.LastName, sizeof(newBug.reporter.LastName), stdin);
    newBug.reporter.LastName[strcspn(newBug.reporter.LastName, "\n")] = 0;

    printf("Enter Priority (0 = LOW, 1 = MEDIUM, 2 = HIGH): ");
    int priorityInput;
    scanf("%d", &priorityInput);
    newBug.priority = (Priority)priorityInput;

    printf("Enter Status (0 = OPEN, 1 = IN_PROGRESS, 2 = RESOLVED): ");
    int statusInput;
    scanf("%d", &statusInput);
    newBug.status = (Status)statusInput;

    printf("Enter Lines of Code: ");
    scanf("%d", &newBug.linesOfCode);

    printf("Enter Function Involved: ");
    getchar(); // Consume the newline character
    fgets(newBug.functionInvolved, sizeof(newBug.functionInvolved), stdin);
    newBug.functionInvolved[strcspn(newBug.functionInvolved, "\n")] = 0;

    printf("Enter Proposed Solution: ");
    fgets(newBug.solution, sizeof(newBug.solution), stdin);
    newBug.solution[strcspn(newBug.solution, "\n")] = 0;

    printf("Enter Occurs When: ");
    fgets(newBug.whenItHappens, sizeof(newBug.whenItHappens), stdin);
    newBug.whenItHappens[strcspn(newBug.whenItHappens, "\n")] = 0;

    // Add the new bug to the list
    bugList[bugCount++] = newBug;
    printf("Bug added successfully!\n");

    // Automatically save bugs to file after adding
    saveBugsToFile();
}

void displayBugs() {
    ClearConsole();
    if (bugCount == 0) {
        printf("No bugs reported yet.\n");
        return;
    }

    // Set text color to red
    printf("\033[1;31m");
    printf("+-----------------------------------------------------------------------------+\n");
    printf("| ID  | Title           | Reporter                  | Priority | Status       |\n");
    printf("+-----------------------------------------------------------------------------+\n");
    for (int i = 0; i < bugCount; i++) {
        Bug bug = bugList[i];
        char fullName[101]; // Buffer for full name (50 + 50 + 1 for null terminator)
        sprintf(fullName, "%s %s", bug.reporter.FirstName, bug.reporter.LastName); // Combine names

        // Trim the title to avoid excessive spaces
        char trimmedTitle[36]; // 35 chars for title + 1 for null terminator
        strncpy(trimmedTitle, bug.title, sizeof(trimmedTitle) - 1);
        trimmedTitle[sizeof(trimmedTitle) - 1] = '\0'; // Ensure null termination

        // Check if the title is longer than the maximum length
        if (strlen(trimmedTitle) > 35) {
            trimmedTitle[35] = '\0'; // Truncate to fit the column
        }

        printf("| %-3d | %-15s | %-25s | %-8s | %-10s  |\n",
               i + 1, // Bug ID
               trimmedTitle,
               fullName, // Use the combined full name
               getPriorityString(bug.priority),
               getStatusString(bug.status));
        printf("+-----------------------------------------------------------------------------+\n");
    }

    // Reset text color to default
    printf("\033[0m");
}

void ClearConsole() {
    #if defined(_WIN32)
        system("cls"); // For Windows
    #else
        system("clear"); // For Linux and macOS
    #endif
}

void displayDetailedBug(int index) {
    ClearConsole();
    if (index < 0 || index >= bugCount) {
        printf("Invalid bug index.\n");
        return;
    }

    Bug bug = bugList[index];
    printf("\nDetailed Bug Information:\n");
    printf("+---------------------------------------------+\n");
    printf("| %-15s: %-30s |\n", "Title", bug.title);
    printf("| %-15s: %-30s |\n", "Description", bug.description);
    char fullName[101]; // Buffer for full name (50 + 50 + 1 for null terminator)
    sprintf(fullName, "%s %s", bug.reporter.FirstName, bug.reporter.LastName); // Combine names
    printf("| %-15s: %-30s |\n", "Reporter", fullName); // Use the combined full name
    printf("| %-15s: %-30s |\n", "Priority", getPriorityString(bug.priority));
    printf("| %-15s: %-30s |\n", "Status", getStatusString(bug.status));
    printf("| %-15s: %-30d |\n", "Lines of Code", bug.linesOfCode);
    printf("| %-15s: %-30s |\n", "Function", bug.functionInvolved);
    printf("| %-15s: %-30s |\n", "Solution", bug.solution);
    printf("| %-15s: %-30s |\n", "Occurs When", bug.whenItHappens);
    printf("+---------------------------------------------+\n");
}

void saveBugsToFile() {
    FILE *file = fopen("bugs.txt", "w");
    if (file == NULL) {
        printf("Error: Unable to save bugs to file.\n");
        return;
    }

    for (int i = 0; i < bugCount; i++) {
        Bug bug = bugList[i];
        fprintf(file, "%s|%s|%s|%s|%d|%d|%d|%s|%s|%s\n",
                bug.title,
                bug.description,
                bug.reporter.FirstName,
                bug.reporter.LastName,
                bug.priority,
                bug.status,
                bug.linesOfCode,
                bug.functionInvolved,
                bug.solution,
                bug.whenItHappens);
    }

    fclose(file);
    printf("Bugs saved to file successfully.\n");
}

void loadBugsFromFile() {
    FILE *file = fopen("bugs.txt", "r");
    if (file == NULL) {
        printf("No previous bug reports found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d|%[^|]|%[^|]|%[^\n]\n",
                  bugList[bugCount].title,
                  bugList[bugCount].description,
                  bugList[bugCount].reporter.FirstName,
                  bugList[bugCount].reporter.LastName,
                  &bugList[bugCount].priority,
                  &bugList[bugCount].status,
                  &bugList[bugCount].linesOfCode,
                  bugList[bugCount].functionInvolved,
                  bugList[bugCount].solution,
                  bugList[bugCount].whenItHappens) == 10) {
        bugCount++;
        if (bugCount >= MAX_BUGS) {
            printf("Maximum bug limit reached. Stopping load.\n");
            break;
        }
    }

    fclose(file);
    printf("Bugs loaded from file successfully.\n");
}

const char* getPriorityString(Priority priority) {
    switch (priority) {
        case LOW: return "LOW";
        case MEDIUM: return "MEDIUM";
        case HIGH: return "HIGH";
    }
    return "UNKNOWN";
}

const char* getStatusString(Status status) {
    switch (status) {
        case OPEN: return "OPEN";
        case IN_PROGRESS: return "IN_PROGRESS";
        case RESOLVED: return "RESOLVED";
    }
    return "UNKNOWN";
}

void showMenu() {
    int choice;
    ClearConsole();
    do {
        // Stylish Menu Header
        printf("\033[1;34m"); // Blue
        printf("+------------------------------------------------------+\n");
        printf("|               Bug Reporting Tool Menu                |\n");
        printf("+------------------------------------------------------+\n");
        printf("\033[0m"); // Reset color

        // Menu Options
        printf("\033[1;32m"); // Green
        printf("| 1. Add Bug                                           |\n");
        printf("| 2. Display Bugs                                      |\n");
        printf("| 3. View Bug Details                                  |\n");
        printf("| 4. Exit                                              |\n");
        printf("+------------------------------------------------------+\n");
        printf("\033[0m"); // Reset color
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBug();
                break;
            case 2:
                displayBugs();
                break;
            case 3: {
                int index;
                printf("Enter Bug ID to view details: ");
                scanf("%d", &index);
                displayDetailedBug(index - 1); // Adjust for zero-based index
                break;
            }
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("\033[1;31mInvalid choice. Please try again.\033[0m\n"); // Red
        }
    } while (choice != 4);
}
