#include <stdio.h>
#include <string.h>
#define n 2

struct person
{
    char number[15];
    char name[15];
    char surname[15];
};

void add_caller();
void show_caller();
void search_caller();

void get_menu() {
    printf("Select\n");
    printf("1: Show callers\n");
    printf("2: Add callers\n");
    printf("3: Search callers\n");
    printf("5: Exit\n");
    printf("->");
}

void add_caller(struct person person[n])
{
  char name[15], surname[15], number[15];
  int num;
  printf("Enter ID which is empty\n");
  scanf("%d",&num);
  printf("Enter Name: ");
  scanf("%s", name);
  printf("Enter Surname: ");
  scanf("%s", surname);
  printf("Enter Tel.number: ");
  scanf("%s", number);
  for (int i = num;;)
  {
      strcpy(person[i].name, name),
      strcpy(person[i].surname, surname),
      strcpy(person[i].number, number);
      printf("Пользователь был добавлен\n\n");
      break;
  }
}


void search_caller(struct person person[n])
{
  char search[10];
  int i=0;

  printf("Enter search name: \n");
  scanf("%s",search);

  for(int i=0; i<n; i++)
    if(strcmp(person[i].name, search) == 0)
      {
        printf("ID %d.   Name: %s\n",i,person[i].name);
        printf("\tSurname: %s\n",person[i].surname);
        printf("\tTel.number: %s\n\n",person[i].number);
        break;
      }
}


void show_caller(struct person person[n])
{
  for(int i=0;i<n;i++)
    {
      printf("ID %d.   Name: %s\n",i,person[i].name);
      printf("\tSurname: %s\n",person[i].surname);
      printf("\tTel.number: %s\n\n",person[i].number);
    }
}

int main(void)
{
    int value;
    struct person person[n];

    do{
    get_menu();
    scanf("%d",&value);

    switch (value) {
      case 1:
            show_caller(person);
            break;
      case 2:
            add_caller(person);
            break;
      case 3:
            search_caller(person);
            break;
    }
} while(value!=5);

return 0;
}
