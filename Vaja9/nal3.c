#include <my_global.h>
#include <mysql.h>

// Ukaz za prevajanje
// gcc program.c -o program `mysql_config --cflags --libs`

MYSQL *con = mysql_init(NULL);
mysql_real_connect(con, "localhost", "root", "geslo", "baza", 0, NULL, 0);
mysql_query(con, "SELECT * FROM tabela");
MYSQL_RES *result = mysql_store_result(con);
int num_fields = mysql_num_fields(result);
MYSQL_ROW row;
row = mysql_fetch_row(result)
    mysql_free_result(result);
mysql_close(con);

return 0;
