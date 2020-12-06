
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char filename[100];
struct database {
    int id;
    char name[15], email[15];
};

void insert()
{
    struct database e;
    int n, i = 0;
    int fp = open(filename, O_CREAT, S_IRUSR | S_IWUSR);

    close(fp);
    fp = open(filename, O_WRONLY|O_APPEND, S_IRUSR | S_IWUSR);
    if(fp < 0) {
        printf("\nCouldn't open file!\n");
        return;
    }

    printf("\nEnter number of records to be inserted: ");
    scanf("%d", &n);
    while(i < n) {
        printf("\nEnter information for record %d:", i);
        printf("\nEnter database ID:\n");
        scanf("%d", &e.id);
        printf("Enter name:\n");
        scanf("%s", e.name);
        printf("Enter email:\n");
        scanf("%s", e.email);
        write(fp, &e, sizeof(e));
        i++;
    }
    close(fp);
}

void display()  {
    int fp, rd;
    struct database e;
    fp = open(filename, O_RDONLY, S_IRUSR);
    read(fp, &e, sizeof(e));
    printf("\nID\tName\temail");
    do
        printf("\n%d \t %s \t\t %s", e.id, e.name, e.email);
    while(read(fp, &e, sizeof(e)) > 0);
}

void modify() {
    int fp1, fp2, rd, wr, r, flag = 0;
    struct database e;
    fp1 = open(filename, O_EXCL|O_RDONLY);
    fp2 = open("temp.txt", O_CREAT|O_WRONLY);

    printf("\nEnter ID to modify: ");
    scanf("%d", &r);
    read(fp1, &e, sizeof(e));
    
    do {
        if(e.id == r) {
            flag = 1;
            printf("\nEnter modified name: ");
            scanf("%s", e.name);
            printf("\nEnter modified email: ");
            scanf("%s", e.email);
        }
        write(fp2, &e, sizeof(e));
    } while(read(fp1, &e, sizeof(e)) > 0);

    if(flag)
        printf("\nModification done!");
    else    
        printf("\nModification was unsuccessful!");

    close(fp1);
    close(fp2);
    remove(filename);
    rename("temp.txt", filename);
}

void delete() {
    int fp1, fp2, rd, wr, r, flag = 0;
    struct database e;
    fp1 = open(filename, O_EXCL|O_RDONLY);
    fp2 = open("temp.txt", O_CREAT|O_WRONLY);
    printf("\nEnter ID to delete: ");
    scanf("%d", &r);

    read(fp1, &e, sizeof(e));
    do {
        if(e.id != r) {
            flag = 1;
            write(fp2, &e, sizeof(e));
        }
    } while(read(fp1, &e, sizeof(e)) > 0);

    if(flag)
        printf("\nDeletion done!");
    else
        printf("\nDeletion was unsuccessful!");

    close(fp1);
    close(fp2);
    remove(filename);
    rename("temp.txt", filename);
}

int main() {
    int choice;
    printf("\nEnter filename: ");
    scanf("%s", filename);
    
    while(1) {
        printf("\nChoose from the following: ");
        printf("\n1. Insert");
        printf("\n2. Display");
        printf("\n3. Modify");
        printf("\n4. Delete");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                insert();
                break;
            case 2:
                display();
                break;
            case 3:
                modify();
                break;
            case 4:
                delete();
                break;
            case 5:
                return 0;
            default:
                printf("\nEnter valid choice!");
        }
    }
    return 0;
}