#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define  reset resetColor()
#define FILE_NAME "users.dat"
typedef struct
{
    char username[50];
    char password[50];
} User;




void signUp()
{
    reset;
    FILE *file = fopen(FILE_NAME, "ab"); // Open file in append binary mode
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Check if the file already contains data (i.e., if a user has already signed up)
    fseek(file, 0, SEEK_END);  // Move to the end of the file
    long file_size = ftell(file);  // Get the current size of the file

    if (file_size > 0)
    {
        color(4);
        printf("\nSign-up not allowed. A user has already signed up.\n");
        reset;
        fclose(file);
        return;
    }

    color(9);
    User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);

    // Write the user data to the file
    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);
    reset;

    color(13);
    printf("Sign-up successful! You can now log in.\n");
    reset;

}



int logIn()
{
    FILE *file = fopen(FILE_NAME, "rb"); // Open file in read binary mode
    if (file == NULL)
    {
        color(4);
        printf("Error opening file or no users found. Please sign up first.\n");

        return;
    }

    char username[50], password[50];
    User user;
    int found = 0;

    color(9);
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // Read user data from the file and check credentials
    while (fread(&user, sizeof(User), 1, file))
    {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(file);

    reset;

    if (found)
    {
        system("cls");
        color(13);
        printf("\nLogin successful! Welcome, %s.\n\n", username);
        reset;

        return found ;

    }
    else
    {
        color(4);
        printf("Invalid username or password. Please try again.\n");
        reset;
        return found;

    }


}

int Switch()
{

    printf("\n\n");

    color(11);
    printf("  Enter Your Choice \n");
    printf(" 1. Win Checker \n");
    printf(" 2. Add Prize Bond Number \n");
    printf(" 3. Delete data\n");
    printf(" 4. View store Data \n");
    printf(" 5. See the draw date \n");
    printf(" 6. Exit \n");
    reset;
    color(15);
    printf("\nPress any key to continue ...\n");
    reset;
    int n;
    scanf("%d",&n);
    switch(n)
    {
    case 1:
    {
        win("data.txt");

        break;

    }
    case 2:
    {

        add("data.txt");
        break;
    }
    case 3:
    {
        delete("data.txt");
        break;
    }
    case 4:
    {
        show_data("data.txt");
        break;
    }
    case 5:
    {
        color(13);
        printf("\nThe draw date is below \n");
        printf("1. January 31\n");
        printf("2. April 30\n");
        printf("3. July 31\n");
        printf("4. October 30\n");
        reset;
        break;
    }
    case 6:
    {
        system("cls");
        printf("Thank You ");
        sleep(2);
        return 0;
    }
    default:
        color(4);
        printf("Invalid choice. Please enter (1-6).\n");
        reset;

    }



    Switch();

}


void win(const char *filename)
{
    char input[100];
    char str[100];
    int found = 0;

    // Open the file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file '%s' for reading.\n", filename);
        return;
    }

    // Prompt the user to enter the string to search
    color(3);
    printf("Enter the prize bond number(AB12345) to search: ");
    scanf("%s", input);
    reset;

    // Check each line in the file
    while (fgets(str, sizeof(str), file))
    {
        // Remove trailing newline character
        str[strcspn(str, "\n")] = 0;

        // Compare input with the current line
        if (strcmp(str, input) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(file);

    // Display result
    if (found)
    {
        printf("\nWin! The data '%s' was found in the file.\n\n", input);
    }
    else
    {
        color(12);
        printf("\n Data not found.\n\n");
        reset;
    }
}



void add(const char *filename)
{
    FILE *file;
    int num_entries, i;
    char str[100];  // Buffer for storing the string
    // int number;

    // Open the file in write mode
    // file = fopen(filename, "w");
    file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }

    // Ask the user for the number of entries

    color(3);
    printf("Enter the number of data entries: ");
    scanf("%d", &num_entries);

    // Loop to collect and write data
    for (i = 0; i < num_entries; i++)
    {
        // printf("Entry %d:\n", i + 1);

        // Get the string input
        printf("Enter a Prize Bond Number (AB12345): ");
        scanf("%s", str);

        // Get the integer input
//        printf("Enter an integer: ");
//        scanf("%d", &number);

        // Write the data to the file
        fprintf(file, "%s\n", str);
    }
    reset;
    // Close the file
    fclose(file);

    color(13);
    printf("\n\nData successfully stored in '%s'.\n\n", filename);
    reset;
}

// Function to display the data from the file
void show_data(const char *filename)
{
    char str[100];
    int number;

    // Open the file in read mode
    FILE *read_file = fopen(filename, "r");
    if (read_file == NULL)
    {
        printf("Error: Could not open file '%s' for reading.\n", filename);
        return;
    }

    //printf("Data in '%s':\n", filename);
    color(13);
    printf("Data stored in the system :\n");
    reset;

    color(3);
    while (fscanf(read_file, "%[^,]\n", str) != EOF)
    {
        printf("%s\n", str);
    }
    reset;
    fclose(read_file);
}


void delete(const char *filename)
{
    char str[100];
    char input[100];
    int found = 0;

    // Open the original file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file '%s' for reading.\n", filename);
        return;
    }

    // Create a temporary file to store non-deleted entries
    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL)
    {
        printf("Error: Could not create temporary file.\n");
        fclose(file);
        return;
    }

    // Prompt the user to enter the data to delete
    color(9);
    printf("Enter the data to delete: ");
    scanf("%s", input);
    reset;
    // Read each line from the original file
    while (fgets(str, sizeof(str), file))
    {
        // Remove trailing newline character
        str[strcspn(str, "\n")] = 0;

        // If the current line does not match the input, write it to the temporary file
        if (strcmp(str, input) != 0)
        {
            fprintf(temp_file, "%s\n", str);
        }
        else
        {
            found = 1; // Mark that the data was found
        }
    }

    // Close both files
    fclose(file);
    fclose(temp_file);

    // Replace the original file with the temporary file
    if (found)
    {
        remove(filename);             // Delete the original file
        rename("temp.txt", filename); // Rename temp file to original file name
        color(13);
        printf("\nData '%s' deleted successfully.\n", input);
        reset;
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file
        color(4);
        printf("\nData '%s' not found in the file.\n", input);
        reset;
    }
}

void color(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); // 7 is the default color (light gray)
}


int main()
{
    int choice,f=0;



    color(10);

    printf("|------------------------------------------------------------------------|\n");
    printf("| ********************************************************************** |\n");
    printf("| *                                                                    * |\n");
    printf("| *           Welcome to Prize Bond Winner Checker System              * |\n");
    printf("| *                                                                    * |\n");
    printf("| ********************************************************************** |\n");
    printf("|------------------------------------------------------------------------|\n");
    printf("\n\n");
    reset;

    color(11);
    printf("\n--- Login and Sign-Up System ---\n\n");
    printf("1. Sign Up\n");
    printf("2. Log In\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    reset;

    while(scanf("%d", &choice))
    {

        switch (choice)
        {
        case 1:
            signUp();
            break;
        case 2:
            if( logIn())
            {
                goto end;
            }

            break;

        case 3:
            printf("Exiting the system. Goodbye!\n");
            sleep(5);
            return 0;
            break;
        default:
            color(4);
            printf("Invalid choice. Please try again.\n");
            reset;
        }
    }

end :

    color(14);

    printf("|------------------------------------------------------------------------|\n");
    printf("| ********************************************************************** |\n");
    printf("| *                                                                    * |\n");
    printf("| *           Welcome to Prize Bond Winner Checker System              * |\n");
    printf("| *                                                                    * |\n");
    printf("| ********************************************************************** |\n");
    printf("|------------------------------------------------------------------------|\n");
    printf("\n");
    reset;

    Switch();


}
