#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName);
void checkTransactions(db);
static void addExpense(sqlite3 *db);

int main(int argc, char *argv[])
{
    system("clear");

    // Initializing a database pointer instance.
    sqlite3 *db;
    int rc;
    int choice;
    char option;

    rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot Open Database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return (0);
    }

    // Asking for input
    printf("This is a small terminal based expense manager made in C.");
    printf("Please choose your option:\n1. Add Expense\n2. Add income\n3. Check your transactions\n");
    printf("-----------------------------------------\n");
    scanf("%d", &choice);

    do {
        if (choice == 1)
        {
            addExpense(db);
        }
        else if (choice == 2)
        {
            // addIncome(db);
        }
        else if (choice == 3)
        {
            checkTransactions(db);
        }
        else
        {
            printf("Please choose from the given options.\n");
        }
        printf("Do you want to ");
    } while (option == 'y' || option == 'Y');


    sqlite3_close(db);
    return 0;
}

void checkTransactions(db)
{
    char *zErrMsg = 0;
    char *sql;
    int rc;
    const char *data = "Callback function called";

    sql = "SELECT * from TRANSACTIONS";

    rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Operation done successfully\n");
    }
}

static void addExpense(sqlite3 *db)
{
    char *zErrMsg;
    char title[50];
    float amount;
    int rc;
    // char *sql_stmt[100];

    printf("Title: ");
    scanf("%s", title);

    printf("Amount: ");
    scanf("%f", &amount);

    char sql_stmt[500];
    snprintf(sql_stmt, sizeof(sql_stmt), "INSERT INTO TRANSACTIONS (TITLE, AMOUNT, TYPE) VALUES ('%s', %f, 'Expense');", title, amount);

    rc = sqlite3_exec(db, sql_stmt, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}