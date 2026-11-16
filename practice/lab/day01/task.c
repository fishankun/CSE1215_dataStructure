#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Student{
    char name[100];
    int roll;
    float cgpa;
    struct Student* link;
} Student;

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

    while(temp != NULL){
        printf("Name: %s\n", temp->name);
        printf("Roll: %d\n", temp->roll);
        printf("CGPA: %.2f\n\n", temp->cgpa);

        temp = temp->link;
    }

    return 0;
}