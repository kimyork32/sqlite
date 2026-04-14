#include <stdio.h>
#include "sqlite3.h"

int main(int argc, char **argv) {
    sqlite3 *db; /* Database connection */
    sqlite3_stmt *pStmt; /* One SQL statement */
    int nCol; /* Number of columns in the result set */

    if (sqlite3_open(argv[1], &db) != SQLITE_OK) {
        fprintf(stderr, "Failed in open DB\n");
        return 1;
    }

    if (sqlite3_prepare_v2(db, argv[2], -1, &pStmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed in compiling: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    nCol = sqlite3_column_count(pStmt);

    while(sqlite3_step(pStmt) == SQLITE_ROW) {
        int i;
        printf("Row:\n");
        for(i = 0; i < nCol; i++) {
            printf(" %s = %s\n",
                sqlite3_column_name(pStmt, i),
                sqlite3_column_text(pStmt, i)
            );
        }
    }

    sqlite3_finalize(pStmt);
    sqlite3_close(db);
    
    return 0;
}
