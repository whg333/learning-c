#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 4

typedef struct {            // 4+4+512+512 = 1032 byte
    int id;                 // 4 byte = 32 bit
    int set;                // 4 byte = 32 bit
    char name[MAX_DATA];    // 1 byte * 512 = 512 byte = 4096 bit
    char email[MAX_DATA];   // 1 byte * 512 = 512 byte = 4096 bit
} Address;

typedef struct {
    Address rows[MAX_ROWS]; //1032byte * 100 = 103200 byte
} Database;

typedef struct {
    FILE *file;
    Database *db;
} Connection;

void die(const char *message){
    if(errno){
        perror(message);
    }else{
        printf("ERROR:%s\n", message);
    }
    exit(1);
}

void Address_print(Address *addr){
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_read(Connection *conn){
    int rc = fread(conn->db, sizeof(Database), 1, conn->file);
    if(rc != 1){
        die("Failed to load databases.");
    }
}

Connection* Database_open(const char *filename, char mode){
    Connection *conn = malloc(sizeof(Connection));
    if(!conn){
        die("conn Memory error");
    }

    conn->db = malloc(sizeof(Database));
    if(!conn->db){
        die("db Memory error");
    }

    if(mode == 'c'){
        conn->file = fopen(filename, "w");
    }else{
        conn->file = fopen(filename, "r+");
        if(conn->file){
            Database_read(conn);
        }
    }

    if(!conn->file){
        die("Failed to open the file");
    }
    return conn;
}

void Database_close(Connection *conn){
    if(conn){
        if(conn->file){
            fclose(conn->file);
        }
        if(conn->db){
            free(conn->db);
        }
        free(conn);
    }
}

void Database_write(Connection *conn){
    rewind(conn->file);
    int rc = fwrite(conn->db, sizeof(Database), 1, conn->file);
    if(rc != 1){
        die("Failed to write database.");
    }

    rc = fflush(conn->file);
    if(rc == -1){
        die("Cannot flush database.");
    }
}

void Database_create(Connection *conn){
    for(int i=0;i<MAX_ROWS;i++){
        Address addr = {i, 0};
        conn->db->rows[i] = addr; // 直接局部的栈上分配，而不是malloc的堆上分配
    }
}

void Database_set(Connection *conn, int id, const char *name, const char *email){
    Address *addr = &conn->db->rows[id];
    if(addr->set){
        die("Already set, delete it first");
    }

    addr->set = 1;
    char* res = strncpy(addr->name, name, MAX_DATA);
    if(!res){
        die("Name copy failed");
    }

    res = strncpy(addr->email, email, MAX_DATA);
    if(!res){
        die("Email copy failed");
    }
}

void Database_get(Connection *conn, int id){
    Address *addr = &conn->db->rows[id];
    if(addr->set){
        Address_print(addr);
    }else{
        die("ID is not set");
    }
}

void Database_delete(Connection *conn, int id){
    Address addr = {id, 0};
    conn->db->rows[id] = addr;
}

void Database_list(Connection *conn){
    for(int i=0;i<MAX_ROWS;i++){
        Address *addr = &conn->db->rows[i];
        if(addr->set){
            Address_print(addr);
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc < 3){
        die("USAGE: ./ex17 <dbfile><action> [action params]");
    }

    char *filename = argv[1];
    char action = argv[2][0];

    Connection *conn = Database_open(filename, action);
    int id = 0;

    if(argc > 3){
        id = atoi(argv[3]);
    }
    if(id >= MAX_ROWS){
        die("There's not that many records.");
    }

    switch(action){
        case 'c':
            Database_create(conn);
            Database_write(conn);
            printf("create database %s success!\n", filename);
            break;
        case 'g':
            if(argc != 4){
                die("Need id to get");
            }
            Database_get(conn, id);
            break;
        case 's':
            if(argc != 6){
                die("Need id, name, email to set");
            }
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            printf("set id=%d success!\n", id);
            break;
        case 'd':
            if(argc != 4){
                die("Need id to delete");
            }
            Database_delete(conn, id);
            Database_write(conn);
            printf("delete id=%d success!\n", id);
            break;
        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}