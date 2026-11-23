#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Student{
    char name[100];
    int roll;
    float cgpa;
    struct Student* link;
} Student;


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

int add_student(Student **s){
    Student **root = search_roll(*s);

    Student *temp = *root;

    *root = malloc(sizeof(Student));
    if(*root == NULL) return 0;


    printf("Enter the name: ");
    scanf(" %[^\n]", (*root)->name);
    printf("Enter the roll: ");
    scanf("%d", &(*root)->roll);
    printf("Enter the CGPA: ");
    scanf("%f", &(*root)->cgpa);
    (*root)->link = temp;
    return 1;
}

int add_after_finding(Student *current){
    int roll;
    printf("Enter the roll: ");
    scanf("%d", &roll);
    Student *next = current->link;

    while(current != NULL){
        if(roll <= next->roll && roll >= current->roll){
            Student *root = malloc(sizeof(Student));
            if(root == NULL) return 0;


            printf("Enter the name: ");
            scanf(" %[^\n]", root->name);
            root->roll = roll;
            printf("Enter the CGPA: ");
            scanf("%f", &root->cgpa);

            root->link = next;
            current->link = root;
            return 1;
        }
        current = current->link;
        next = current->link;
    }
    return 0;
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
        return 1;
    }
    return 0;
}

int main(){
    int choice;
    Student *temp = malloc(sizeof(Student));
    Student *a = temp;
    do{
        Student *s = a;

        char name[100];
        printf("Name: ");
        scanf("%s", name);
        strcpy(s->name, name);

        printf("Roll: ");
        scanf("%d", &s->roll);

        printf("CGPA: ");
        scanf("%f", &s->cgpa);

        a = malloc(sizeof(Student));

        printf("Do you want to add more?(1/0)");
        scanf("%d", &choice);
        if(choice == 0) s->link = NULL;
        else s->link = a;
        
        s = a;
    }while(choice != 0);

    if(add_student(&temp)) printf("Student added successfully!\n");
    else printf("Failed to add student!\n");

    if(add_after_finding(temp)) printf("Student added successfully!\n");
    else printf("Failed to add student!\n");

    if(remove_student(temp)) printf("Student removed successfully!\n");
    else printf("Failed to remove student!\n");

    while(temp != NULL){
        display_student_info(temp);
        temp = temp->link;
    }

    return 0;
}