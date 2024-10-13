Here's a README file for your Bug Reporting Tool project, which describes its purpose, features, and usage:

---

# Bug Reporting Tool

This is a **Bug Reporting Tool** written in C, designed to help users report, track, and manage software bugs effectively. It allows users to add bug reports, view them in a list, and see detailed information about each bug. The tool also saves the bug reports to a file for persistent storage and retrieves them upon startup.

## Features

- **Add Bug**: Allows users to input a bug title, description, reporter's name, priority, status, lines of code, function involved, proposed solution, and occurrence context.
- **Display Bugs**: Lists all reported bugs in a tabular format, showing essential details such as title, reporter, priority, and status.
- **View Bug Details**: Provides detailed information about a selected bug, including all the attributes of the bug report.
- **Persistent Storage**: Automatically saves bug reports to a text file and loads them when the application starts, ensuring that data is not lost between sessions.
- **User-Friendly Interface**: Clear and colorful console output for better readability and interaction.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC) installed on your system.
- Basic knowledge of compiling and running C programs.

### Installation

1. Clone or download the repository to your local machine.
2. Navigate to the directory containing the source code.
3. Compile the program using the following command:

   ```bash
   gcc -o bug_report_tool bug_report_tool.c
   ```

4. Run the executable:

   ```bash
   ./bug_report_tool
   ```

### Usage

1. **Add a Bug**: Select option 1 from the menu to add a new bug. Follow the prompts to enter all the required information.
2. **Display Bugs**: Choose option 2 to display a list of all reported bugs.
3. **View Bug Details**: Select option 3 to view detailed information about a specific bug by entering its ID.
4. **Exit**: Choose option 4 to exit the application.

## Code Structure

- **Data Structures**: 
  - `Reporter`: Holds the first and last name of the bug reporter.
  - `Bug`: Represents a bug report with various fields such as title, description, reporter, priority, status, and other relevant details.
  
- **Enums**:
  - `Priority`: Represents the priority level of the bug (LOW, MEDIUM, HIGH).
  - `Status`: Represents the status of the bug (OPEN, IN_PROGRESS, RESOLVED).

- **Functions**:
  - `addBug()`: Adds a new bug to the system.
  - `displayBugs()`: Displays a list of all bugs.
  - `displayDetailedBug(int index)`: Displays detailed information for a specific bug.
  - `saveBugsToFile()`: Saves all bugs to a text file.
  - `loadBugsFromFile()`: Loads bugs from the text file.
  - `getPriorityString(Priority priority)`: Returns the string representation of the bug priority.
  - `getStatusString(Status status)`: Returns the string representation of the bug status.
  - `showMenu()`: Displays the main menu and handles user input.

## Acknowledgments

This project is inspired by the need for effective bug tracking in software development. Contributions and suggestions for improvements are welcome!

---

Feel free to modify any sections to better suit your project's specifics or your preferences!

![Screenshot 2024-10-13 194737](https://github.com/user-attachments/assets/9e42a371-f5b6-4851-a6fc-83368b02cbcb)
![Screenshot 2024-10-13 194722](https://github.com/user-attachments/assets/88233de2-2fc1-484a-8a4f-e11f58c1c86b)
![Screenshot 2024-10-13 194654](https://github.com/user-attachments/assets/ee342b43-2941-4a16-875f-a105c91cc341)
