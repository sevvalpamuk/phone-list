#include <stdio.h>
#include <string.h>

typedef struct PersonList {
    char name[20];
    char number[15];  // Telefon numarasını string olarak saklıyoruz
} Person;

void info();
int addphone(Person* person);
int deletephone(char* num);
void writelist();

int main() {
    int choice;
    info();
    scanf("%d", &choice);

    while (choice != 3) {
        Person person;
        char num[15];
        
        switch (choice) {
        case 1:
            printf("Name:\n ");
            scanf("%s", person.name);
            printf("Phone number:\n");
            scanf("%s", person.number);

            if (addphone(&person)) {
                printf("Added number and name.\n");
            }
            printf("New list: \n");
             writelist();

            
            break;
        case 2:
            printf("Please enter the phone number you want to delete: ");
            scanf("%s", num);
            if (deletephone(num)) {
                printf("Deleted number and name.\n");
            }
             printf("New list: \n");
             writelist();
            break;
        default:
            printf("Please enter a number between 1 and 3.\n");
            break;
        }
        info();
        scanf("%d", &choice);
    }
    printf("End of program.\n");
    return 0;
}

void info() {
    printf("Please enter the number of your choice: \n");
    printf("1 - Add a number\n");
    printf("2 - Delete a number\n");
    printf("3 - Exit\n");
    printf("Your choice:\n");
}

int addphone(Person* person) {
    FILE* myfile = fopen("PhoneList.txt", "a");
    if (myfile == NULL) {
        printf("File could not be opened.\n");
        return 0;
    }
    
    fprintf(myfile, "%s %s\n", person->name, person->number);
    fclose(myfile);
    return 1;
}

int deletephone(char* num) {
    Person p;
    FILE* mainfile = fopen("PhoneList.txt", "r");
    FILE* copiedfile = fopen("Recorded.txt", "w");

    if (mainfile == NULL || copiedfile == NULL) {
        printf("File could not be opened.\n");
        return 0;
    }

    while (fscanf(mainfile, "%s %s", p.name, p.number) != EOF) {
        if (strcmp(p.number, num) != 0) {
            fprintf(copiedfile, "%s %s\n", p.name, p.number);
        }
    }
    fclose(mainfile);
    fclose(copiedfile);

    remove("PhoneList.txt");
    rename("Recorded.txt", "PhoneList.txt");

    return 1;
}
void writelist(){
    FILE *file=fopen("PhoneList.txt","r");
    char data[50];
    while(fgets(data,50,file)){
        printf("%s",data);
    }
}