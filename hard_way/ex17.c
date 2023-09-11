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
    /**
     * size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
     * fread 用于从文件中读取数据，并将数据存储到内存中。它接受四个参数：要存储数据的内存位置（ptr）、每个元素的大小（size）、
     * 要读取的元素数量（count）以及文件指针（stream）。函数返回成功读取的元素数量。通常用于读取二进制数据。
     */
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

    /**
     * FILE *fopen(const char *filename, const char *mode);
     * fopen 用于打开一个文件，并返回一个指向文件的指针（FILE *）。
     * 它接受两个参数：文件名（filename）和打开模式（mode）。打开模式可以是 "r"（只读）、
     * "w"（写入，如果文件存在则截断，如果不存在则创建）、"a"（追加，如果文件不存在则创建）、
     * "rb"（二进制读取）等等。函数成功打开文件时返回一个指向文件的指针，失败时返回 NULL。
     */
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
            /**
             * int fclose(FILE *stream);
             * fclose 用于关闭文件。它接受一个文件指针（stream），并将文件关闭。
             * 在完成文件操作后，通常应该调用 fclose 来确保文件被正确关闭，释放资源并刷新缓冲区。
             */
            fclose(conn->file);
        }
        if(conn->db){
            free(conn->db);
        }
        free(conn);
    }
}

void Database_write(Connection *conn){
    /**
     * void rewind(FILE *stream);
     * rewind 用于将文件指针（stream）重新定位到文件的开头。这使得你可以重新读取文件的内容
     */
    rewind(conn->file);

    /**
     * size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
     * fwrite 用于将数据从内存写入到文件中。
     * 它接受四个参数：要写入的数据的内存位置（ptr）、每个元素的大小（size）、要写入的元素数量（count）
     * 以及文件指针（stream）。函数返回成功写入的元素数量。通常用于写入二进制数据。
     */
    int rc = fwrite(conn->db, sizeof(Database), 1, conn->file);
    if(rc != 1){
        die("Failed to write database.");
    }

    /**
     * int fflush(FILE *stream);
     * fflush 用于将输出缓冲区的内容刷新到文件中。通常，C标准库会自动进行缓冲以提高性能，
     * 但在某些情况下，你可能需要强制刷新缓冲区以确保数据被写入文件。
     */
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
    // 这里如果不使用&取地址，则代表的是局部栈上，并没有真正的设置成功
    Address addr = conn->db->rows[id];
    if(addr.set){
        die("Already set, delete it first");
    }

    addr.set = 1;
    char* res = strncpy(addr.name, name, MAX_DATA);
    if(!res){
        die("Name copy failed");
    }

    res = strncpy(addr.email, email, MAX_DATA);
    if(!res){
        die("Email copy failed");
    }

    conn->db->rows[id] = addr; // 使用栈的方式需要最后这里再重新设置一遍
}

void Database_get(Connection *conn, int id){
    Address addr = conn->db->rows[id];
    if(addr.set){
        Address_print(&addr);
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
        Address addr = conn->db->rows[i];
        if(addr.set){
            Address_print(&addr);
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