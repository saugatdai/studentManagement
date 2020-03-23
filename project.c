#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "record.dat"

void addRecord();
void addBulkRecord();
void listStudents();
void searchStudent();
void handleChoice(int);
void handleRecordChoice(int, int);
void editAndSave(int);
void delete (int);
void displayMarksheet(int);
void fflush_stdin();


typedef struct
{
    int roll;
    char name[50];
    int math, science, english, nepali, social;
    float percentage;
} student;

int main()
{
    int ch;
    while (ch != 5)
    {
        printf("\n*********************************************************************************\n");
        printf("\n\n1. Add a record\n2. Add Bulk Records\n3. List Students\n4. Search Student\n5. Quit\n");
        printf("What is your choice? : ");
        if(scanf("%d",&ch) != 1){
            ch = 0;
        }
        fflush_stdin();
        printf("\n*********************************************************************************\n");
        handleChoice(ch);
    }

    return 0;
}


void fflush_stdin(){
    int c;
	while (((c = getchar()) != '\n') && (c != EOF));
}

void delete (int roll)
{
    FILE *fptr;
    int i = 0, j;
    student *s;

    // Getting list of students
    s = (student *)malloc(sizeof(student));

    fptr = fopen(FILENAME, "rb");

    if (fptr == NULL)
    {
        printf("Can not open the file");
    }
    else
    {
        while (fread((s + i), sizeof(student), 1, fptr))
        {
            ++i;
            s = (student *)realloc(s, (i + 1) * sizeof(student));
        }
        fclose(fptr);
    }
    //Deleting and saving...
    fptr = fopen(FILENAME, "wb");

    if (fptr == NULL)
    {
        printf("Cannot open the file");
    }
    else
    {
        for (j = 0; j < i; j++)
        {
            if ((s + j)->roll != roll)
            {
                fwrite((s + j), sizeof(student), 1, fptr);
            }
        }
        free(s);
        fclose(fptr);
    }
}
void displayMarksheet(int roll) {
    FILE *fptr;
    student temp;
    float percentage;
    char division[20];
    int total ;

    fptr = fopen(FILENAME, "rb");
    
    if(fptr == NULL){
        printf("Can not open the file");
    }else{
        while(fread(&temp, sizeof(student), 1, fptr)){
            if(temp.roll == roll){
		total = (temp.english + temp.science + temp.math + temp.nepali + temp.social);
		printf("\n\n%d\n\n",total);
                percentage = total*100.0/500;
                if(temp.english < 32 || temp.science < 32 || temp.math < 32 ||
                    temp.nepali < 32 || temp.social < 32){
                     strcpy(division,"Fail");       
                }else if(percentage >= 32 && percentage <= 49){
                     strcpy(division,"Third");       
                }else if(percentage >= 50 && percentage <= 59){
                    strcpy(division,"Second");
                }else if(percentage >=60 && percentage <=79){
                    strcpy(division,"First");
                }else if(percentage >= 80 && percentage <= 100  ){
                    strcpy(division,"Distinction");
                }
                printf("\nST. XAVIER'S COLLEGE\n");
                printf("\nSECOND TERM EXAMINATION\n");
                printf("\n*********************************************************************************\n");
                printf("|\tName : %-30s                                 \t|\n",temp.name);
                printf("|\tRoll : %d                                                                |\n", temp.roll);
                printf("*********************************************************************************\n");
                printf("|\tS.N\t|\t\t\tSubjects\t|\tMarks\t\t|");
                printf("\n*********************************************************************************\n");
                printf("|\t1. \t|\t\t\tMathematics\t|\t%02d\t\t|\n",temp.math);
                printf("|\t2. \t|\t\t\tEnglish    \t|\t%02d\t\t|\n",temp.english);
                printf("|\t3. \t|\t\t\tNepali     \t|\t%02d\t\t|\n",temp.nepali);
                printf("|\t4. \t|\t\t\tScience    \t|\t%02d\t\t|\n",temp.science);
                printf("|\t5. \t|\t\t\tSocial     \t|\t%02d\t\t|",temp.social);
                printf("\n*********************************************************************************\n");
                printf("|\t   \t|\t\t\tPercentage \t|\t%02.2f%% \t\t|\n", percentage);
                printf("|\t   \t|\t\t\tDivision   \t|\t%-10s \t|", division);
                printf("\n*********************************************************************************\n");
                printf("\nEND OF RESULT\n");
            }
        }
    }
}

void editAndSave(int roll)
{
    student std;
    FILE *fptr;
    int i = 0, j;
    student *s;

    std.roll = roll;
    printf("\n*********************************************************************************\n");
    printf("\nEnter name : ");
    scanf(" %[^\n]", std.name);
    printf("Enter Marks in Mathematics : ");
    scanf("%d", &std.math);
    printf("Enter Marks in Science : ");
    scanf("%d", &std.science);
    printf("Enter Marks in English : ");
    scanf("%d", &std.english);
    printf("Enter Marks in Nepali : ");
    scanf("%d", &std.nepali);
    printf("Enter Marks in Social : ");
    scanf("%d", &std.social);
    printf("\n*********************************************************************************\n");

    // Getting list of students
    s = (student *)malloc(sizeof(student));

    fptr = fopen(FILENAME, "rb");

    if (fptr == NULL)
    {
        printf("Can not open the file");
    }
    else
    {
        while (fread((s + i), sizeof(student), 1, fptr))
        {
            ++i;
            s = (student *)realloc(s, (i + 1) * sizeof(student));
        }
        fclose(fptr);
    }

    //updating the values

    fptr = fopen(FILENAME, "wb");

    if (fptr == NULL)
    {
        printf("Cannot open the file");
    }
    else
    {
        for (j = 0; j < i; j++)
        {
            if ((s + j)->roll != roll)
            {
                fwrite((s + j), sizeof(student), 1, fptr);
            }
            else
            {
                fwrite(&std, sizeof(student), 1, fptr);
            }
        }
        printf("Record Updated!!\n");
        printf("\n*********************************************************************************\n");
        free(s);
        fclose(fptr);
    }
}

void listStudents()
{
    FILE *fptr;
    int i = 0;
    student *s;

    s = (student *)malloc(sizeof(student));

    fptr = fopen(FILENAME, "rb");

    if (fptr == NULL)
    {
        printf("Can not open the file");
    }
    else
    {
        printf("Roll \t Name\n");
        while (fread((s + i), sizeof(student), 1, fptr))
        {
            printf("%d\t%s\n", (s + i)->roll, (s + i)->name);
            ++i;
            s = (student *)realloc(s, (i + 1) * sizeof(student));
        }
        free(s);
        fclose(fptr);
    }
}

void handleRecordChoice(int roll, int choice)
{
    switch (choice)
    {
    case 1:
        editAndSave(roll);
        break;
    case 2:
        delete (roll);
        break;
    case 3:
        displayMarksheet(roll);
        break;
    default:
        printf("Bye Bye");
        break;
    }
}

void searchStudent()
{
    FILE *fptr;
    int roll;
    student temp;
    int found = 0;
    int choice;

    printf("\nEnter Roll No: ");
    scanf("%d", &roll);

    fptr = fopen(FILENAME, "r");

    if (fptr == NULL)
    {
        printf("Can not open the file");
    }
    else
    {
        while (fread(&temp, sizeof(student), 1, fptr))
        {
            if (temp.roll == roll)
            {
                printf("\n*********************************************************************************\n\n");
                printf("Record Found : \n");
                printf("Student Name : %s\n", temp.name);
                printf("\n*********************************************************************************\n");
                found = 1;
                printf("1. Edit Record\n");
                printf("2. Delete Record\n");
                printf("3. View Marksheet\n");
                printf("4. Quit\n");
                printf("What is your choice? : ");
                scanf("%d", &choice);
                printf("\n*********************************************************************************\n");
                handleRecordChoice(roll, choice);
            }
        }

        if (found == 0)
        {
            printf("Sorry! No record found\n");
        }
    }
}

void addBulkRecord()
{
    student *s;
    int n, i;
    FILE *fptr;

    printf("How many students? : ");
    scanf("%d", &n);
    s = malloc(n * sizeof(student));

    fptr = fopen(FILENAME, "ab");

    if (fptr == NULL)
    {
        printf("Cannot open the file");
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            printf("\n\nEnter information for student %d : \n", i + 1);
            printf("Enter name : ");
            scanf(" %[^\n]", (s + i)->name);
            printf("Enter Roll : ");
            scanf("%d", &(s + i)->roll);
            printf("Enter Marks in Mathematics : ");
            scanf("%d", &(s + i)->math);
            printf("Enter Marks in Science : ");
            scanf("%d", &(s + i)->science);
            printf("Enter Marks in English : ");
            scanf("%d", &(s + i)->english);
            printf("Enter Marks in Nepali : ");
            scanf("%d", &(s + i)->nepali);
            printf("Enter Marks in Social : ");
            scanf("%d", &(s + i)->social);
            fwrite((s + i), sizeof(student), 1, fptr);
            fflush(stdin);
        }
        fclose(fptr);
    }
}

void addRecord()
{
    FILE *fptr;
    student s;

    printf("Enter name : ");
    scanf(" %[^\n]", s.name);
    printf("Enter Roll : ");
    scanf("%d", &s.roll);
    printf("Enter Marks in Mathematics : ");
    scanf("%d", &s.math);
    printf("Enter Marks in Science : ");
    scanf("%d", &s.science);
    printf("Enter Marks in English : ");
    scanf("%d", &s.english);
    printf("Enter Marks in Nepali : ");
    scanf("%d", &s.nepali);
    printf("Enter Marks in Social : ");
    scanf("%d", &s.social);

    fptr = fopen(FILENAME, "ab");

    if (fptr == NULL)
    {
        printf("Couldn't open the file");
    }
    else
    {
        fwrite(&s, sizeof(student), 1, fptr);
        fclose(fptr);
    }
}

void handleChoice(int ch)
{
    switch (ch)
    {
    case 1:
        addRecord();
        break;
    case 2:
        addBulkRecord();
        break;
    case 3:
        listStudents();
        break;
    case 4:
        searchStudent();
        break;
    default:
        printf("Bye Bye!!\n");
        break;
    }
}
