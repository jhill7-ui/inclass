/*
    Ronin: main && part C
    Mau: main && part A
    Jerimaiah: main && part B
*/

#include <stdio.h>

#define MAX_BOOKS 30
#define MAX_LOANS 50

typedef struct {
    int id;
    char title[50];
    int totalCopies;
    int availableCopies;
    int reservedBy;
} Book;
typedef struct {
    int bookId;
    int borrowerId;
    int active;
} Loan;

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int addBook(Book books[], int *count, int id, const char title[], int copies) {
    // Check for exceeding MAX_BOOKS
    if (*count >= MAX_BOOKS) {
        return 0; 
    }
    // Check for invalid copy count
    if (copies <= 0) {
        return -2;
    }
    // Check for duplicate ID
    for (int i = 0; i < *count; i++) {
        if (books[i].id == id) {
            return -1; 
        }   
    }
    // Populate the new book struct at the current count index
    books[*count].id = id;
    strncpy(books[*count].title, title, sizeof(books[*count].title) - 1);
    books[*count].title[sizeof(books[*count].title) - 1] = '\0'; // Ensure null-termination
    books[*count].totalCopies = copies;
    books[*count].availableCopies = copies;
    books[*count].reservedBy = -1; // -1 indicates no active reservation
    (*count)++; // Increment the total book count
    return 1;
}

int borrowBook(Book books[], int bookCount, Loan loans[], int *loanCount, int bookId, int borrowerId) {
    int exists = 0;
    int index;
    for (int i = 0; i < bookCount; i++) {
        if(books[i].id == bookId) {
            exists = 1;
            index = i;
            break;
        }
    }
    if (!exists) {
        printf("No such book exists in library!\n");
        return 0;
    }
    if (books[index].availableCopies <= 0) {
        printf("No copies left!\n");
        return 0;
    }
    for (int i = 0; i < *loanCount; i++) {
        if(loans[i].bookId == bookId && loans[i].borrowerId == borrowerId) {
            if (loans[i].active) {
                printf("User %d already has an active loan for this book!\n", borrowerId);
                return 0;
            } else {
                books[index].availableCopies--;
                loans[i].active = 1;
                return 1;
            }
        }
    }
    Loan newLoan = {bookId, borrowerId, 1};
    loans[*loanCount] = newLoan;
    (*loanCount)++;
    return 1;
}

int main(void) {
    Book books[MAX_BOOKS];
    Loan loans[MAX_LOANS];
    int bookCount = 0;
    int loanCount = 0;
    int choice;
    char inputVerificiation;
    int keepLooping = 1;
    printf("===== LIBRARY MANAGEMENT SYSTEM =====\n1. Add a book\n2. Display all books\n3. Borrow a book\n4. Return a book\n5. Reserve a book\n6. Display active loans\n7. Display library statistics\n0. Exit\nEnter your choice:");
    do {
        if(scanf("%d%c", &choice, &inputVerificiation) != 2 || inputVerificiation != '\n') {
            printf("ERROR: Please enter an integer\n");
            clearInput();
        } else if (choice < 0 || choice > 7) {
            printf("ERROR: Invalid range, expected (0-7)\n");
        } else {
            switch (choice) {
                case 0:
                    keepLooping = 0;
                    break;
                case 1:
                     if (bookCount >= MAX_BOOKS) {
                        printf("ERROR: Library Full!\n");
                        break;
                    }
                    int id;
                    int copies;
                    char title[50];
                    printf("Enter Book ID: ");
                    if (scanf("%d", &id) != 1) {
                        printf("ERROR: Invalid ID.\n");
                        clearInput();
                        break;
                    }
                    printf("Enter Book Title: ");
                    if (fgets(title, sizeof(title), stdin) != NULL) {
                        title[strcspn(title, "\n")] = '\0';
                    }
                    printf("Enter Number of Copies: ");
                    if (scanf("%d", &copies) != 1) {
                        printf("ERROR: Invalid copy count.\n");
                        clearInput();
                        break;
                    }
                    int result = addBook(books, &bookCount, id, title, copies);
                    if (result == 1) {
                        printf("Book '%s' added successfully!\n", title);
                    } else if (result == -1) {
                        printf("ERROR: A book with ID %d already exists.\n", id);
                    } else if (result == -2) {
                        printf("ERROR: Number of copies must be greater than 0.\n");
                    }
                    break;
                case 2:
                    //display
                    break;
                case 3:
                    int bookId, borrowerId;
                    int validated = 0;
                    do {
                        printf("Enter Book Id");
                        if(scanf("%d%c", &bookId, &inputVerificiation) != 2 || inputVerificiation != '\n') {
                        } else if (bookId < 0 || bookId > 7) {
                            printf("ERROR: Invalid range, expected > 0\n");
                        } else {
                            validated = 1;
                        }
                    } while (!validated);
                    validated = 0;
                    do {
                        printf("Enter Borrower Id");
                        if(scanf("%d%c", &borrowerId, &inputVerificiation) != 2 || inputVerificiation != '\n') {
                        } else if (borrowerId < 0 || borrowerId > 7) {
                            printf("ERROR: Invalid range, expected > 0\n");
                        } else {
                            validated = 1;
                        }
                    } while (!validated);
                    borrowBook(books, bookCount, loans, &loanCount, bookId, borrowerId);
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
            }
        }
    } while (keepLooping);
}

