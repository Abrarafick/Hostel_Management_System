#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2
#define MAX_ROOMS 2

struct Student {
    char id[20];        // ID now string
    char name[50];
    char email[50];
    int age;
    int room_number;
    int fee_paid; // 1 = Paid, 0 = Not Paid
};

struct Complain {
    char student_id[20];   // student id also string
    char issue_type[30];
    char description[100];
    char status[20]; // Pending, Resolved 
};

// Function methods
void addStudent();
void updateStudent();
void deleteStudent();
void allocateRoom();
void reallocateRoom();
void trackPayments();
void reportComplain();
void viewComplains();
int login();
int isRoomAvailable(int room);
void showRoomStatus();

// Global file names
const char *studentFile = "students.txt";
const char *complainFile = "complains.txt";

int main() {
    int choice;
    if (!login())
    {
        printf("\nAccess Denied. Only university emails allowed.\n");
        return 0;
    }

    do {
        printf("\n===== Hostel Management Menu =====\n");
        printf("1. Add Student\n2. Update Student\n3. Delete Student\n4. Allocate Room\n5. Reallocate Room\n6. Track Payments\n7. Report Complaint\n8. View Complaints\n9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: allocateRoom(); break;
            case 5: reallocateRoom(); break;
            case 6: trackPayments(); break;
            case 7: reportComplain(); break;
            case 8: viewComplains(); break;
            case 9: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 9);

    return 0;
}

int login()
{
    char email[50];
    printf("Enter university email: ");
    scanf("%s", email);
    return strstr(email, "@diu.edu.bd") != NULL;
}

void addStudent()
{
    struct Student s;
    FILE *fp = fopen(studentFile, "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%s", s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Email: ");
    scanf("%s", s.email);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    showRoomStatus();
    do {
        printf("Enter Room Number to allocate: ");
        scanf("%d", &s.room_number);
        if (!isRoomAvailable(s.room_number)) 
        {
            printf("Room is full. Choose another room.\n");
        }
    } while (!isRoomAvailable(s.room_number));

    printf("Fee Paid? (1 = Yes, 0 = No): ");
    scanf("%d", &s.fee_paid);

    fprintf(fp, "%s,%s,%s,%d,%d,%d\n", s.id, s.name, s.email, s.age, s.room_number, s.fee_paid);
    fclose(fp);
    printf("Student added successfully!\n");
}

void updateStudent() {
    char id[20];
    int found = 0;
    struct Student s;
    FILE *fp = fopen(studentFile, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Student ID to update: ");
    scanf("%s", id);

    while (fscanf(fp, "%19[^,],%49[^,],%49[^,],%d,%d,%d\n",
                  s.id, s.name, s.email, &s.age, &s.room_number, &s.fee_paid) == 6) {
        if (strcmp(s.id, id) == 0) {
            found = 1;
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Email: ");
            scanf("%s", s.email);
            printf("Enter New Age: ");
            scanf("%d", &s.age);
            printf("Enter New Room: ");
            scanf("%d", &s.room_number);
            printf("Fee Paid? (1 = Yes, 0 = No): ");
            scanf("%d", &s.fee_paid);
        }
        fprintf(temp, "%s,%s,%s,%d,%d,%d\n", s.id, s.name, s.email, s.age, s.room_number, s.fee_paid);
    }

    fclose(fp);
    fclose(temp);
    remove(studentFile);
    rename("temp.txt", studentFile);

    if (found)
        printf("Student updated successfully.\n");
    else
        printf("Student not found.\n");
}

void deleteStudent() {
    char id[20];
    struct Student s;
    FILE *fp = fopen(studentFile, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter ID to delete: ");
    scanf("%s", id);

    while (fscanf(fp, "%19[^,],%49[^,],%49[^,],%d,%d,%d\n",
                  s.id, s.name, s.email, &s.age, &s.room_number, &s.fee_paid) == 6) {
        if (strcmp(s.id, id) != 0)
            fprintf(temp, "%s,%s,%s,%d,%d,%d\n", s.id, s.name, s.email, s.age, s.room_number, s.fee_paid);
    }

    fclose(fp);
    fclose(temp);
    remove(studentFile);
    rename("temp.txt", studentFile);
    printf("Student deleted.\n");
}

void allocateRoom() {
    char id[20];
    int new_room, found = 0;
    struct Student s;

    FILE *fp = fopen(studentFile, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Student ID for allocation: ");
    scanf("%s", id);

    while (fscanf(fp, "%19[^,],%49[^,],%49[^,],%d,%d,%d\n",
                  s.id, s.name, s.email, &s.age, &s.room_number, &s.fee_paid) == 6) {
        if (strcmp(s.id, id) == 0) {
            found = 1;
            printf("Current Room: %d\n", s.room_number);
            showRoomStatus();
            do {
                printf("Enter Room Number to allocate: ");
                scanf("%d", &new_room);
                if (!isRoomAvailable(new_room)) {
                    printf("Room is full. Choose another room.\n");
                }
            } while (!isRoomAvailable(new_room));
            s.room_number = new_room;
        }
        fprintf(temp, "%s,%s,%s,%d,%d,%d\n",
                s.id, s.name, s.email, s.age, s.room_number, s.fee_paid);
    }

    fclose(fp);
    fclose(temp);
    remove(studentFile);
    rename("temp.txt", studentFile);

    if (found)
        printf("Room allocated successfully!\n");
    else
        printf("Student not found.\n");
}


void reallocateRoom() {
    char id[20];
    int new_room, found = 0;
    struct Student s;
    FILE *fp = fopen(studentFile, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Student ID for reallocation: ");
    scanf("%s", id);

    while (fscanf(fp, "%19[^,],%49[^,],%49[^,],%d,%d,%d\n",
                  s.id, s.name, s.email, &s.age, &s.room_number, &s.fee_paid) == 6) {
        if (strcmp(s.id, id) == 0) {
            found = 1;
            printf("Current Room: %d\n", s.room_number);
            showRoomStatus();
            do {
                printf("Enter New Room Number: ");
                scanf("%d", &new_room);
                if (!isRoomAvailable(new_room)) {
                    printf("Room is full. Choose another room.\n");
                }
            } while (!isRoomAvailable(new_room));
            s.room_number = new_room;
        }
        fprintf(temp, "%s,%s,%s,%d,%d,%d\n", s.id, s.name, s.email, s.age, s.room_number, s.fee_paid);
    }

    fclose(fp);
    fclose(temp);
    remove(studentFile);
    rename("temp.txt", studentFile);
    if (found)
        printf("Room reallocated.\n");
    else
        printf("Student not found.\n");
}

void trackPayments() {
    struct Student s;
    FILE *fp = fopen(studentFile, "r");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }
    printf("\nPayment Status:\n");
    while (fscanf(fp, "%19[^,],%49[^,],%49[^,],%d,%d,%d\n",
                  s.id, s.name, s.email, &s.age, &s.room_number, &s.fee_paid) == 6) {
        printf("ID: %s, Name: %s, Fee Paid: %s\n", s.id, s.name, s.fee_paid ? "Yes" : "No");
    }
    fclose(fp);
}

void reportComplain() {
    struct Complain c;
    FILE *fp = fopen(complainFile, "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%s", c.student_id);
    getchar(); // clear leftover newline from input buffer

    printf("Enter Issue Type (e.g., Fan, Light, Water): ");
    fgets(c.issue_type, sizeof(c.issue_type), stdin);
    c.issue_type[strcspn(c.issue_type, "\n")] = 0;

    printf("Enter Description: ");
    fgets(c.description, sizeof(c.description), stdin);
    c.description[strcspn(c.description, "\n")] = 0;

    strcpy(c.status, "Pending");

    fprintf(fp, "%s,%s,%s,%s\n", c.student_id, c.issue_type, c.description, c.status);
    fclose(fp);

    printf("Complain reported.\n");
}

void viewComplains() {
    struct Complain c;
    FILE *fp = fopen(complainFile, "r");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nComplains:\n");
    while (fscanf(fp, "%19[^,],%29[^,],%99[^,],%19[^\n]",
                  c.student_id, c.issue_type, c.description, c.status) == 4) {
        printf("Student ID: %s\nIssue: %s\nDescription: %s\nStatus: %s\n\n",
               c.student_id, c.issue_type, c.description, c.status);
    }

    fclose(fp);
}

int isRoomAvailable(int room) {
    struct Student s;
    int count = 0;
    FILE *fp = fopen(studentFile, "r");
    if (!fp) return 1;
    while (fscanf(fp, "%19[^,],%49[^,],%49[^,],%d,%d,%d\n",
                  s.id, s.name, s.email, &s.age, &s.room_number, &s.fee_paid) == 6) {
        if (s.room_number == room) count++;
    }
    fclose(fp);
    return count < 4;
}

void showRoomStatus() {
    int room_counts[MAX_ROOMS] = {0};
    struct Student s;
    FILE *fp = fopen(studentFile, "r");
    if (!fp) {
        return;
    }
    while (fscanf(fp, "%19[^,],%49[^,],%49[^,],%d,%d,%d\n",
                  s.id, s.name, s.email, &s.age, &s.room_number, &s.fee_paid) == 6) {
        if (s.room_number < MAX_ROOMS) room_counts[s.room_number]++;
    }
    fclose(fp);

    printf("\nRoom Status (Room No : Occupied Seats)\n");
    for (int i = 1; i < MAX_ROOMS; i++) {
        if (room_counts[i] > 0)
            printf("Room %d : %d students\n", i, room_counts[i]);
    }
}
