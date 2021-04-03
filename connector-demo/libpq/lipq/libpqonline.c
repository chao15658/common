#include <stdio.h>
#include <stdlib.h>
#include "libpq-fe.h"
#include<string.h>
#include <stdbool.h>
#include <errno.h>

static void exit_nicely(PGconn *conn)
{
    printf("exit success\n");   
    PQfinish(conn);
    exit(1);

}


static void displayRowsOrderByDesc(PGconn ** conn, PGresult   **res,char *selecttbsql)
{
    int	nFields;
    int	i,j;
    // Start a transaction block */
    *res = PQexec(*conn, "BEGIN");
    if (PQresultStatus(*res) != PGRES_COMMAND_OK)
    {
    	fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(*conn));
    	PQclear(*res);
    	exit_nicely(*conn);
    }
    PQclear(*res);
    char selectTb[100] = "DECLARE myportal CURSOR FOR  ";
    strcat(selectTb,selecttbsql);  
    *res = PQexec(*conn, selectTb);
    if (PQresultStatus(*res) != PGRES_COMMAND_OK)
    {
    	fprintf(stderr, "DECLARE CURSOR failed: %s", PQerrorMessage(*conn));
    	PQclear(*res);
    	exit_nicely(*conn);
    }
    PQclear(*res);
    *res = PQexec(*conn, "FETCH ALL in myportal");
    if (PQresultStatus(*res) != PGRES_TUPLES_OK)
    {
    	fprintf(stderr, "FETCH ALL failed: %s", PQerrorMessage(*conn));
    	PQclear(*res);
    	exit_nicely(*conn);
    }
    /* first, print out the attribute names */
    nFields = PQnfields(*res);
    for (i = 0; i < nFields; i++)
    	printf("|%-5s ", PQfname(*res, i));
    printf("\n");
    for (i = 0; i < nFields; i++)
        printf("--------");
    printf("\n");
    /* next, print out the rows */
    for (i = 0; i < PQntuples(*res); i++)
    {
    	for (j = 0; j < nFields; j++)
          printf("|%-5s ", PQgetvalue(*res, i, j));
        printf("\n");
    }
    PQclear(*res);
    /* close the portal ... we don't bother to check for errors ... */
    *res = PQexec(*conn, "CLOSE myportal");
    PQclear(*res);   
    /* end the transaction */
    *res = PQexec(*conn, "END");
    PQclear(*res);

}


static void insertTb(PGconn ** conn, PGresult   **res,char *insertsql)
{
    int	nFields;
    int	i,j;
    *res = PQexec(*conn, insertsql);
    if (PQresultStatus(*res) != PGRES_COMMAND_OK)
    {
    	fprintf(stderr, "insert failed: %s", PQerrorMessage(*conn));
    	PQclear(*res);
    	exit_nicely(*conn);
    } else 
    {
        printf("insert success\n");
    } 
    PQclear(*res);
}


static void updateTb(PGconn ** conn, PGresult   **res,char *updatetbsql)
{
    int	nFields;
    int	i,j;
    *res = PQexec(*conn, updatetbsql);
    if (PQresultStatus(*res) != PGRES_COMMAND_OK)
    {
    	fprintf(stderr, "update failed: %s", PQerrorMessage(*conn));
    	PQclear(*res);
    	exit_nicely(*conn);
    } else 
    {
        printf("update success\n");
    }
    PQclear(*res);
}


static void deleteTb(PGconn ** conn, PGresult   **res,char *deletesql)
{
    *res = PQexec(*conn, deletesql);
    if (PQresultStatus(*res) != PGRES_COMMAND_OK)
    {
    	fprintf(stderr, "update failed: %s", PQerrorMessage(*conn));
    	PQclear(*res);
    	exit_nicely(*conn);
    } else 
    {
        printf("delete success\n");
    }
    PQclear(*res);
}


static void createTb(PGconn ** conn, PGresult  **res,char *createtbsql)
{
    *res = PQexec(*conn, createtbsql);
    if (PQresultStatus(*res) != PGRES_COMMAND_OK)
    {
    	fprintf(stderr, "update failed: %s", PQerrorMessage(*conn));
    	PQclear(*res);
    	exit_nicely(*conn);
    } else 
    {
        printf("create table success\n");
    }
    PQclear(*res);
}


int main(int argc, char **argv)
{
  const char *conninfo;
  PGconn	   *conn;
  PGresult   *res;
  /*
   * If the user supplies a parameter on the command line, use it as the
   * conninfo string; otherwise default to setting dbname=postgres and using
   * environment variables or defaults for all other connection parameters.
   */
  if (argc > 1)
      conninfo = argv[1];
  else
      conninfo = "host=localhost port=6868 dbname=txdb_default connect_timeout=10";
  /* Make a connection to the database */
  conn = PQconnectdb(conninfo);
  
  /* Check to see that the backend connection was successfully made */
  if (PQstatus(conn) != CONNECTION_OK)
  {
      fprintf(stderr, "Connection to database failed: %s",PQerrorMessage(conn));
      exit_nicely(conn);
  }
  printf("welcome to use OCI interface!\n");
  printf("connection information is: %s\n",conninfo);
  char input[200];
  int selector=-1;
  do {
     printf("please input your operation, support operation is: 0(CREATE TABLE), 1(INSERT), 2(UPDATE), 3(DELETE), 4(SELECT), 5(quit): ");
     scanf("%d",&selector);
     getchar();
     if(selector!=5) 
     {
         printf("please input your sql according to your choice:\n");
         scanf("%[^\n]",&input);
 
     }
     switch(selector) 
     {
     case 0:
        createTb(&conn,&res,input);
        break;
     case 1:
        insertTb(&conn,&res,input);
        break;
     case 2:
        updateTb(&conn,&res,input);
        break;
     case 3:
        deleteTb(&conn,&res,input);
        break;
     case 4: 
        displayRowsOrderByDesc(&conn,&res,input);
        break;
     case 5:
        exit_nicely(conn);
     default: 
        printf("input is invalid for %d\n",selector);
     }
  } while(1);
  /* close the connection to the database and cleanup */
  PQfinish(conn);
  return 0;
}
