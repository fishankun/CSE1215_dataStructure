#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student{
    char name[100];
    int roll;
    float cgpa;
    struct Student *link;
} Student;

void display();
void display_student_info(Student *s);
Student **search_roll(Student *s);
int update_student_info(Student *s);
int add_student(Student *s);
int remove_student(Student *s);
void file_open(Student **root);
void save_students(Student *s);
void free_students(Student *s);
Student *create_student_list(FILE *fp);

int main(){
    Student *root = NULL;
    file_open(&root);
    
    int option;
    do{
        display();
        printf("Enter an option: ");
        scanf("%d", &option);
        switch(option){
            case 1: Student *parent = root;    
                    while(parent != NULL){
                        display_student_info(parent);
                        parent = parent->link;
                    }
                    printf("\n");
                    break;

            case 2: parent = root;
                    if(update_student_info(parent)) printf("Student info updated successfully!\n ");
                    else printf("Student info not updated!\n\n");
                    break;

            case 3: parent = root;
                    int flag = add_student(parent);
                    if(flag) printf("Student added successfully!\n\n");
                    else printf("Failed!!!\n\n");
                    
                    break;

            case 4: parent = root;
                    flag = remove_student(parent);
                    if(flag) printf("Student removed successfully!\n\n");
                    else printf("Failed!!!\n\n");
                    break;
        }

    }while(option != 0);

    free_students(root);
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

Student **search_roll(Student *s){
    int roll;
    printf("Enter the roll: ");
    scanf("%d", &roll);

    Student **current = &s;
    while(*current != NULL){
        if(roll == (*current)->roll) return current;
        current = &(*current)->link;
    }
    return NULL;
}

int update_student_info(Student *s){
    Student **found_student = search_roll(s);
    
    if(found_student != NULL){
        printf("Student found!\n");
        display_student_info(*found_student);
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
                strcpy((*found_student)->name, name);
                flag = 1;
                break;

        case 2: printf("Enter the roll: ");
                scanf("%d", &(*found_student)->roll);
                flag = 1;
                break;

        case 3: printf("Enter the CGPA: ");
                scanf("%f", &(*found_student)->cgpa);
                flag = 1;
                break;
    }

    if(flag){
        save_students(s);
        return 1;
    }
    else return 0;
}

int add_student(Student *s){
    Student *root = s;

    while(s->link != NULL) s = s->link;

    s->link = malloc(sizeof(Student));
    if(s->link == NULL) return 0;

    s = s->link;

    printf("Enter the name: ");
    scanf(" %[^\n]", s->name);
    printf("Enter the roll: ");
    scanf("%d", &s->roll);
    printf("Enter the CGPA: ");
    scanf("%f", &s->cgpa);
    s->link = NULL;

    save_students(root);
    return 1;
}

int remove_student(Student *s){
    int choose;
    Student **found = search_roll(s);

    if(found == NULL){
        printf("Student not found\n");
        return 0;
    }

    display_student_info(*found);
    printf("Are you sure you want to remove this student? (1/0): ");
    scanf("%d", &choose);

    if(choose){
        Student *current = *found;
        *found = current->link;
        free(current);

        save_students(s);
        return 1;
    }
    return 0;
}

void file_open(Student **root){
    FILE *fp = fopen("info.txt", "r");
    if(!fp) return;

    *root = create_student_list(fp);
    fclose(fp);
}

Student *create_student_list(FILE *fp){
    Student *root = malloc(sizeof(Student));
    Student *parent = root;
    Student *child;
    char name[100];

    while(fscanf(fp, " %99[^\n]", name) != EOF){
        child = parent;

        strcpy(child->name, name);

        fscanf(fp, "%d", &child->roll);
        fscanf(fp, "%f", &child->cgpa);

        child->link = malloc(sizeof(Student));
        parent = child->link;
    }
    free(child->link);
    child->link = NULL;

    return root;
}   

void save_students(Student *s){
    FILE *fp = fopen("info.txt", "w");
    if(!fp) return;

    while(s->link != NULL){
        fprintf(fp, "%s\n", s->name);
        fprintf(fp, "%d %.2f\n", s->roll, s->cgpa);
        fprintf(fp, "%p", s->link);

        s = s->link;
    }

    fclose(fp);
}

void free_students(Student *s){
    if(s == NULL){
        free(s);
        return;
    }
    free_students(s->link);
    free(s);
}