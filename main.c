#include <stdio.h>
#include <stdlib.h>
#include<windows.h>/*this library because console title*/
/*Define two pointers to files*/
FILE*first=NULL;
FILE*second=NULL;
/*[Description]
 *This function give the user type of mismatch like(additional,missed,mismatch)character in the INPUT_2.txt
 */
void option_one()
{
    /*Define 4 locations two for each file one for the current character and second for next character*/
    char current_ch1,current_ch2,next_ch1,next_ch2;
    /*Define 3 flags:-
     *1)flag =1 if the two files are identical
     *2)flag1=1 to read the character from INPUT_1.txt
     *3)flag2=1 to read the character from INPUT_2.txt
     */
    char flag=1,flag1=1,flag2=1;
    /*Define two variables
     *line: to count number of lines
     *i: to count number of character in the line
     */
     char choice;
    long line=1,i=1;
    /*clear screen before start showing the output*/
    system("cls");

/*open the two files and make the mode r mean that we will read only from them*/
first=fopen("INPUT_1.txt","r");
second=fopen("INPUT_2.txt","r");
/*If there is no files in the same location exit the program*/
  if(first==NULL)
     {
         printf("Can't find INPUT_1.txt\n");
         printf("Do you want to read another text file instead of making INPUT_1?{Y/N}\n");
         choice=getch();
         if(choice=='y'||choice=='Y')
         {
             char *file_name=(char*)malloc(100*sizeof(char));
             printf("Enter the name of the file and don't forget the extension-->Ex:mido.txt\n");
             scanf("%s",file_name);

             file_name=realloc(file_name,strlen(file_name)+1);
             file_name[strlen(file_name)]='\0';
             printf("%c",file_name[strlen(file_name)]);
             first=fopen(file_name,"r");
             if(first==NULL)
                printf("EEROR");

         }
         system("pause");
         //exit(1);
     }
   else if(second==NULL)
     {
         printf("Can't find INPUT_2.txt\n");
         system("pause");
         exit(1);
     }
/*take first two characters from the two files*/
fscanf(first,"%c",&current_ch1);
fscanf(second,"%c",&current_ch2);

do{
    /*Here this flag to check whether i will read the next character or no from INPUT_1.txt*/
    if(flag1)
       {
          if(fscanf(first,"%c",&next_ch1)==EOF)
          {
              next_ch1='\n';
          }
       }
    /*Here this flag to check whether i will read the next character or no from INPUT_2.txt*/
    if(flag2)
       {
          if(fscanf(second,"%c",&next_ch2)==EOF)
          {
              next_ch2='\n';
          }
       }
    /*If the two characters is matched then jump to the next characters and make the flags equal one to read the two next characters*/
    if(current_ch1==current_ch2)
    {
        current_ch2=next_ch2;
        current_ch1=next_ch1;
        flag1=1;
        flag2=1;
    }
   /*If the two characters is not matched then see the options */
    else if(current_ch1!=current_ch2)
    {
         /*[Option one]
         *1)see if the next character in the INPUT_2 same as the current character in INPUT_1 and current character in INPUT_2 not equal \n (to make every line independent)
         *  This means that the current character in INPUT_2 is additional and if it didn't exist the files will be matched
         *(((OR)))
         *2)if the current character in the INPUT_1 equals \n
         *  the program will stop reading from INPUT_1 and print all next characters from INPUT_2 by magenta color because they are additional in INPUT_2
         */
        if(((next_ch2==current_ch1)&&(current_ch2!='\n')&&next_ch1!=next_ch2)||(current_ch1=='\n'))
        {
            printf("\033[35mThere is an additional character at INPUT_2.txt at line %d in the cell %d\033[0m\n",line,i);
            /*After printing the message we will move the current character in INPUT_2 to the next*/
            current_ch2=next_ch2;
            /*Then make the flag1=0 to prevent reading a new character from INPUT_1 to be synchronized with INPUT_2*/
            flag1=0;
            /*Make flag2=1 to read the next character from INPUT_2*/
            flag2=1;
        }

        /*[Option two]
        * 1)see if the next character in the INPUT_1 same as the current character in INPUT_2 and current character in INPUT_1 not equal \n (to make every line independent)
        *   This means that there is a missed character in INPUT_2 and if it exists the files will be matched
        *(((OR)))
        *2)if the current character in the INPUT_2 equals \n
        *  the program will stop reading from INPUT_2 and print all next characters from INPUT_1 by yellow color because they are missed in INPUT_2
        *
        */
       else if(((next_ch1==current_ch2)&&(current_ch1!='\n')&&next_ch1!=next_ch2)||(current_ch2=='\n'))
        {
            printf("\033[33mThere is a missing character at INPUT_2.txt at the line %d in the cell %d\n\033[0m",line,i);
            /*After printing the message we will move the current character in INPUT_1 to the next*/
            current_ch1=next_ch1;
            /*Then make the flag2=0 to prevent read a new character from INPUT_2 to be synchronized with INPUT_1*/
            flag2=0;
            /*Make flag1=1 to read the next character from INPUT_1*/
            flag1=1;
        }
        /*Option three: if the character do not match and the next don't match*/
       else
       {
           printf("\033[31mThere is a mismatch at line %d in the character %d\033[0m\n",line,i);
           /*moving the current character in INPUT_1 to the next*/
           current_ch2=next_ch2;
           /*moving the current character in INPUT_2 to the next*/
           current_ch1=next_ch1;
           /*Make flag1=1 to read the next character from INPUT_1*/
           flag1=1;
           /*Make flag2=1 to read the next character from INPUT_2*/
           flag2=1;
       }
           /*Then make the flag=0 to prevent printing identical after the scanning finished*/
            flag=0;
    }
/*This part to detect new line and increment line variable and begin i again from -1 why? one increment after the if makes i=0 and the second increment done by every new line \n*/
 if(current_ch2=='\n'&&current_ch1=='\n')
    {
        line++;
        i=-1;
    }

i++;

/*This section to print rest of file INPUT_1 by yellow if INPUT_2 reaches the end and INPUT_1 not*/
  if(feof(second)&&!feof(first)&&current_ch1!=next_ch1&&current_ch2!=next_ch2)
 {
    do{
           if(current_ch1=='\n')
            {
              line++;
              i=0;
            }
            else
            {
                 if(current_ch1==next_ch1&&current_ch2==next_ch2)/*This condition to fix a bug when INPUT_2=asdq and INPUT_1=asddq*/
                 {
                     /*do nothing*/
                 }
                 else
                 printf("\033[33mThere is a missing character at INPUT_2.txt at the line %d in the cell %d\n\033[0m",line,i);
            }
           i++;
      }
      while(fscanf(first,"%c",&current_ch1)!=EOF);

    flag=0;
 }
/*This section to print rest of file INPUT_2 by magenta if INPUT_1 reaches the end and INPUT_2 not*/
else if(!feof(second)&&feof(first)&&current_ch1!=next_ch1&&current_ch2!=next_ch2)
 {
    do{

        if(current_ch2=='\n')
         {
            line++;
            i=0;
         }
         else
         {
             if(current_ch1==next_ch1&&current_ch2==next_ch2)/*This condition to fix a bug when INPUT_1=asdq and INPUT_2=asddq*/
             {
                 /*do nothing*/
             }
             else
             printf("\033[35mThere is an additional character at INPUT_2.txt at line %d in the cell %d\033[0m\n",line,i);
         }
           i++;
      }
      while(fscanf(second,"%c",&current_ch2)!=EOF);
    flag=0;
 }


}
while(!feof(second)||!feof(first));/*Checking if end of any file is reached or not*/

/*Closing the two files*/
fclose(first);
fclose(second);

/*Here printing Identical if all characters are matched*/
if(flag)
{
    printf("Identical\n");
}

printf("\033[34mFinished scanning press any key to return to main menu\033[0m");

getch();
}
void option_two()
{
/*Define 4 locations two for each file one for the current character and second for next character*/
char current_ch1,current_ch2,next_ch1,next_ch2;
/*Define 2 flags:-
     *1)flag1=1 to read the character from INPUT_1.txt
     *2)flag2=1 to read the character from INPUT_2.txt
     */
char flag1=1,flag2=1;

/*clear screen before start showing the output*/
system("cls");

/*open the two files and make the mode r mean that we will read only from them*/
first=fopen("INPUT_1.txt","r");
second=fopen("INPUT_2.txt","r");
/*If there is no files in the same location exit the program*/
  if(first==NULL)
     {
         printf("Can't find INPUT_1.txt\n");
         system("pause");
         exit(1);
     }
   else if(second==NULL)
     {
         printf("Can't find INPUT_2.txt\n");
         system("pause");
         exit(1);
     }

/*take first two characters from the two files*/
fscanf(first,"%c",&current_ch1);
fscanf(second,"%c",&current_ch2);

do{
/*Here this flag to check whether i will read the next character or no from INPUT_1.txt*/
    if(flag1)
       {
          if(fscanf(first,"%c",&next_ch1)==EOF)
          {
              next_ch1='\n';
          }
       }
/*Here this flag to check whether i will read the next character or no from INPUT_2.txt*/
    if(flag2)
       {
          if(fscanf(second,"%c",&next_ch2)==EOF)
          {
              next_ch2='\n';
          }
       }
/*If the two characters is matched then jump to the next characters and make the flags equal one to read the two next characters*/
    if(current_ch1==current_ch2)
    {
        printf("%c",current_ch2);
        if(next_ch2!=current_ch2)
        current_ch2=next_ch2;
        if(next_ch1!=current_ch1)
        current_ch1=next_ch1;
        flag1=1;
        flag2=1;
    }
/*If the two characters is not matched then see the options */
    else if(current_ch1!=current_ch2)
    {
        /*[Option one]
         *1)see if the next character in the INPUT_2 same as the current character in INPUT_1 and current character in INPUT_2 not equal \n (to make every line independent)
         *  This means that the current character in INPUT_2 is additional and if it didn't exist the files will be matched
         *(((OR)))
         *2)if the current character in the INPUT_1 equals \n
         *  the program will stop reading from INPUT_1 and print all next characters from INPUT_2 by magenta color because they are additional in INPUT_2
         */
        if(((next_ch2==current_ch1)&&(current_ch2!='\n')&&next_ch1!=next_ch2)||(current_ch1=='\n'))
        {
         /*Printing the character and it's background colored by magenta*/
         printf("\033[45m%c\033[0m",current_ch2);
         /*After printing the character by magenta we will move the current character in INPUT_2 to the next*/
         current_ch2=next_ch2;
         /*Then make the flag1=0 to prevent reading a new character from INPUT_1 to be synchronized with INPUT_2*/
         flag1=0;
         /*Make flag2=1 to read the next character from INPUT_1*/
         flag2=1;
        }
        /*[Option two]
        * 1)see if the next character in the INPUT_1 same as the current character in INPUT_2 and current character in INPUT_1 not equal \n (to make every line independent)
        *   This means that there is a missed character in INPUT_2 and if it exists the files will be matched
        *(((OR)))
        *2)if the current character in the INPUT_2 equals \n
        *  the program will stop reading from INPUT_2 and print all next characters from INPUT_1 by yellow color because they are missed in INPUT_2
        *
        */
       else if(((next_ch1==current_ch2)&&(current_ch1!='\n')&&next_ch1!=next_ch2)||(current_ch2=='\n'))
        {
            /*Printing the character and it's background colored by yellow*/
            printf("\033[43m%c\033[0m",current_ch1);
            /*After printing the character by yellow we will move the current character in INPUT_1 to the next*/
            current_ch1=next_ch1;
            /*Then make the flag2=0 to prevent reading a new character from INPUT_2 to be synchronized with INPUT_1*/
            flag2=0;
            /*Make flag1=1 to read the next character from INPUT_1*/
            flag1=1;
        }
       /*Option three: if the character do not match and the next don't match*/
       else
       {
           /*Printing the character and it's background colored by red*/
           printf("\033[41m%c\033[0m",current_ch2);
           /*moving the current character in INPUT_2 to the next*/
           current_ch2=next_ch2;
           /*moving the current character in INPUT_1 to the next*/
           current_ch1=next_ch1;
           /*Make flag1=1 to read the next character from INPUT_1*/
           flag1=1;
           /*Make flag2=1 to read the next character from INPUT_1*/
           flag2=1;
       }

    }
/*This section to print rest of file INPUT_1 by yellow if INPUT_2 reaches the end and INPUT_1 not*/
 if(feof(second)&&!feof(first)&&current_ch1!=next_ch1&&current_ch2!=next_ch2)
 {
    do{
            printf("\033[43m%c\033[0m",current_ch1);
      }
      while(fscanf(first,"%c",&current_ch1)!=EOF);
 }
/*This section to print rest of file INPUT_2 by magenta if INPUT_1 reaches the end and INPUT_2 not*/
 else if(!feof(second)&&feof(first)&&current_ch1!=next_ch1&&current_ch2!=next_ch2)
 {
    do{
          printf("\033[45m%c\033[0m",current_ch2);
      }
      while(fscanf(second,"%c",&current_ch2)!=EOF);
 }


}
while(!feof(second)||!feof(first));/*Checking if end of the any file is reached or not*/

/*Closing the two files*/
fclose(first);
fclose(second);

printf("\n\033[34mFinished scanning press any key to return to main menu\033[0m");

getch();

}
/*Declaration of two functions that will be used under the main function*/
char main_menu();
void How_program_works();

int main()
{
/*Define a variable called option to get the option that user want*/
char option='N';
/*Change the console title name*/
SetConsoleTitle("Difference");

   while(1)
  {
      /*Clear the screen at the beginning of every loop*/
       system("cls");

       printf("Welcome to Difference Program\n1)Run\n2)How it works\n");
       /*get the option that user want*/
       option=getch();
/*If the input ='1' then go to main menu function*/
   if(option=='1')
    {
      option=main_menu();
      /*According to the option selected in main menu the program will jump*/
         if(option=='1')
         {
          option_one();
         }
         else if(option=='2')
         {
          option_two();
         }
    }
/*If the input='2' then go to how program works function*/
    else if(option=='2')
    {
      How_program_works();
    }

   }

    return 0;
}
/*[Description]
 *This function has two option only
 *First to enter option one function
 *Second to enter option two function
 */
char main_menu()
{
    system("cls");
    printf("Enter the option you want\n1)get the location of the error only\n2)print INPUT_2.txt and highlight the different from INPUT_1.txt\n\n\n\n\033[34m**Press any key else to go back**\033[0m");
    return getch();
}
/*[Description]
 *This function explain how the program works to the user
 */
void How_program_works()
{
    system("cls");
    printf("1.You should create Two Text Files in the same location of the program and name them INPUT_1 and INPUT_2 respectively\n");
    printf("2.Put the text you want to check in the two files\n");
    printf("3.The program compare INPUT_2.txt with INPUT_1.txt so you should put in INPUT_1 the original text\n");
    printf("4.If the cell was red like this \033[41m%c\033[0m this means that this character do not match with the character in INPUT_1.txt\n",'$');
    printf("Example:-\nINPUT_1.txt:--->mido is a good boy\nINPUT_2.txt:--->mido is a gaod boy\nResult:-------->mido is a g\033[41m%c\033[0mod boy\n\n",'a');
    printf("5.If the cell was yellow like this \033[43m%c\033[0m this means that INPUT_2.txt needs the character inside the cell to make the two \nfiles identical after this character and until a miss match occur\n",'$');
    printf("Example:-\nINPUT_1.txt:--->mido is a good boy\nINPUT_2.txt:--->mido s a good boy\nResult:-------->mido \033[43m%c\033[0ms a good boy\n\n",'i');
    printf("6.If the cell was magenta like this \033[45m%c\033[0m this means that INPUT_2.txt has additional character inside the cell if it removed\nfiles will be identical after this character and until a miss match occur\n",'$');
    printf("Example:-\nINPUT_1.txt:--->mido is a good boy\nINPUT_2.txt:--->mido is a goood boy\nResult:-------->mido is a goo\033[45m%c\033[0md boy\n\n",'o');
    printf("\033[41mNote:\033[0mThis program sensitive to characters in each line\n     Thats mean if there is two mismatched characters or more beside each others\n     This will lead to a shift and may the rest of the line not be accurate\n\n");
    system("pause");
}
