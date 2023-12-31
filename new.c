#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>


// defining clear screen command for windows and linux
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif


void addExpense(sqlite3* db);
void addIncome(sqlite3* db);
void checkTransactions(sqlite3* db);


int main(int argc, char *argv[])
{
    // Clearing the terminal screen.....
    system(CLEAR_SCREEN);

    int choice;
    char option;
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);

    // Checks the return code (rc) from the sqlite3_open function.
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot Open Database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return (0);
    }

    printf("This is a terminal based expense manager made in C.\n");

    do
    {
        option = 'y';

        printf("-----------------------------------------\n");
        printf("Please choose your option:\n1. Add Expense\n2. Add income\n3. Check your transactions\n");
        printf("-----------------------------------------\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addExpense(db);
            break;

        case 2:
            addIncome(db);
            break;
        
        case 3:
            checkTransactions(db);
            break;

        default:
            printf("\n\nPlease choose from the given options.\n\n");
            break;
        }

        printf("Do you want to continue (y/Y): ");
        scanf(" %c", &option); // In " %c" the space consumes the whitespace characters left in the input buffer.

    } while (option == 'y' || option == 'Y');

    printf("Exiting...\n");
    sleep(3);

    sqlite3_close(db);
    return 0;
}

void addExpense(sqlite3* db) {
    char title[100];
    float amount;

    printf("\nTitle: ");
    scanf(" %s", title);

    printf("\nAmount: ");
    scanf("%f", &amount);

    char sql[500];
    sprintf(sql, "INSERT INTO TRANSACTIONS ('TITLE', 'AMOUNT', 'TYPE') VALUES ('%s', '%.2f', 'Expense');", title, amount);

    int rc = sqlite3_exec(db, sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Data inserted successfully.\n");
    }
}


void addIncome(sqlite3* db) {
    char title[100];
    float amount;

    printf("\nTitle: ");
    scanf(" %s", title);

    printf("\nAmount: ");
    scanf(" %f", &amount);

    char sql[500];
    sprintf(sql, "INSERT INTO TRANSACTIONS ('TITLE', 'AMOUNT', 'TYPE') VALUES ('%s', '%.2f', 'Income');", title, amount);

    int rc = sqlite3_exec(db, sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Data inserted successfully.\n");
    }
}


void checkTransactions(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM TRANSACTIONS;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("Transaction ID\tTitle\tAmount\tType\tTimestamp\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%d\t%s\t%d\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_int(stmt, 2));
    }

    sqlite3_finalize(stmt);
}