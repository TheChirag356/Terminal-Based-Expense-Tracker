#include <stdio.h>
#include <stdlib.h>

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

static void addExpense(int rc, sqlite3 *db, char *zErrMsg)
{
    char title[50];
    double amount;
    char * sql_stmt;

    printf("Title: ");
    fgets(title, sizeof(title), stdin);

    printf("Amount: ");
    scanf("%s", &amount);

    snprintf(sql_stmt, sizeof(sql_stmt), "INSERT INTO TRANSACTIONS (TITLE, AMOUNT, TYPE) VALUES (%s, %f, 'Expense');", title, amount);

    rc = sqlite3_exec(db, sql_stmt, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }
}