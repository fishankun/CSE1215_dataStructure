#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[100];
    int roll;
    float cgpa;
} Student;

void display();
void display_student_info(Student *s);
int search_roll(Student *s[], int n);
int update_student_info(Student *s[], int n);
int add_student(Student *s[], int n);
int remove_student(Student *s[], int n);
int file_open(Student *s[], int n);
void save_students(Student *s[], int n);
void free_students(Student *s[], int n);

int main(){
    Student *s[100];
    int total = 0;
    total = file_open(s, total);
    
    int option;
    do{
        display();
        printf("Enter an option: ");
        scanf("%d", &option);
        switch(option){
            case 1: for(int i = 0; i < total; i++){
                        display_student_info(s[i]);
                    }
                    printf("\n");
                    break;

            case 2: if(update_student_info(s, total)) printf("Student info updated successfully!\n ");
                    else printf("Student info not updated!\n\n");
                    break;
            case 3: if(total < 100){
                        s[total] = malloc(sizeof(Student));
                        if(!s[total]) break;
                        total = add_student(s, total);
                        printf("Student added successfully!\n\n");
                    }
                    else printf("Student list is full!\n\n");
                    break;
            case 4: total = remove_student(s, total);
                    break;
        }

    }while(option != 0);

    free_students(s, total);
}

void display(){
    printf("Student Info Manager\n");
    printf("1. Display student info.\n");
    printf("2. Update student info.\n");
    printf("3. Add a new student.\n");
    printf("4. Remove a student.\n");
    printf("0. Exit\n\n");
}

void display_student_info(Student *s){
    printf("Name: %s\n", s->name);
    printf("Roll: %d\tCGPA: %.2f\n", s->roll, s->cgpa);
}

int search_roll(Student *s[], int n){
    int roll, i;

    printf("Enter the roll: ");
    scanf("%d", &roll);

    for(i = 0; i < n; i++)
        if(roll == s[i]->roll) return i;
    return -1;
}

int update_student_info(Student *s[], int n){
    int i = search_roll(s, n);
    
    if(i >= 0){
        printf("Student found!\n");
        display_student_info(s[i]);
    }
    else{
        printf("Student not found\n");
        return 0;
    }

    int options;
    printf("What do you want to update?\n");
    printf("1. Name\n2. Roll\n3. CGPA\n");
    scanf("%d", &options);

    int flag = 0;
    char name[100];
    switch(options){
        case 1: printf("Enter the name: ");
                scanf(" %[^\n]", name);
                strcpy(s[i]->name, name);
                flag = 1;
                break;

        case 2: printf("Enter the roll: ");
                scanf("%d", &s[i]->roll);
                flag = 1;
                break;

        case 3: printf("Enter the CGPA: ");
                scanf("%f", &s[i]->cgpa);
                flag = 1;
                break;
    }

    if(flag){
        save_students(s, n);
        return 1;
    }
    else return 0;
}

int add_student(Student *s[], int n){
    printf("Enter the name: ");
    scanf(" %[^\n]", s[n]->name);
    printf("Enter the roll: ");
    scanf("%d", &s[n]->roll);
    printf("Enter the CGPA: ");
    scanf("%f", &s[n]->cgpa);
    n++;
    save_students(s, n);
    return n;
}

int remove_student(Student *s[], int n){
    int choose;
    int index = search_roll(s, n);
    if(index == -1){
        printf("Student not found\n");
        return n;
    }

    display_student_info(s[index]);
    printf("Are you sure you want to remove this student? (1/0): ");
    scanf("%d", &choose);

    if(choose){
        free(s[index]);
        for(int i = index; i < n - 1; i++) s[i] = s[i + 1];
        n--;
        save_students(s, n);
        printf("Student removed successfully!\n\n");
    }
    return n;
}

int file_open(Student *s[], int n){
    FILE *fp = fopen("info.txt", "r");
    if(!fp) return 0;

    fscanf(fp, "%d", &n);
    
    for(int i = 0; i < n; i++){
        s[i] = malloc(sizeof(Student));
        if(!s[i]) continue;
        fscanf(fp, " %[^\n]", s[i]->name);
        fscanf(fp, "%d %f", &s[i]->roll, &s[i]->cgpa);
    }
    fclose(fp);
    return n;
}

void save_students(Student *s[], int n){
    FILE *fp = fopen("info.txt", "w");
    if(!fp) return;

    fprintf(fp, "%d\n", n);
    for(int i = 0; i < n; i++){
        fprintf(fp, "%s\n", s[i]->name);
        fprintf(fp, "%d %.2f\n", s[i]->roll, s[i]->cgpa);
    }

    fclose(fp);
}

void free_students(Student *s[], int n){
    for(int i = 0; i < n; i++) free(s[i]);
}