#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *sql;
   int rc;
   sqlite3_stmt *res;

    rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot Open Database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(0);
    }

    rc = sqlite3_prepare_v2(db, "SELECT SQLITE3_VERSION()", -1, &res, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    rc = sqlite3_step(res);

    if (rc == SQLITE_ROW) {
        printf("%s\n", sqlite3_column_text(res, 0));
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

}