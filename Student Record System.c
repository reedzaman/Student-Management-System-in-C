#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#define gap 330



void adjust(char *string_p, int length);
void prompt(char *str,char *base);
void add_student();
int  query();
int  show(int star_loc);



struct{
        char name[51];
        char db[11];
        char blood[5];
        char dept[5];
        char id[11];
        char address[201];
        char phone[21];
        char email[31];
}student;



void cut_string(char *str){
    /* to cut the access spaces that we've used to
    adjust the strings  */
    int i = strlen(str)-1;
    while(str[i]==' '){
        if(i<=0)break;
        str[i]='\0';
        i--;
    }
}



void adjust(char *string_p, int target_length){
    /* adjusts the string by occupying the full
    size of the string using spaces */
    while(strlen(string_p)<target_length) strcat(string_p," ");
}



void prompt(char *str,char *base){
    /* scans a string */
    printf(str);
    gets(base);
}

void print_hello(){
    printf(" Hello ");
}

void add_student(){
    system("cls");
    /* to add members */
    FILE *file;
    if((file=fopen("info.dat","a"))==NULL){
        printf("Error opening file");
        exit(1);
    }
    for(;;){

        // taking all the info using the prompt() function
        prompt("Name (press enter to exit) :",student.name);
        if(*student.name == '\0')break;
        prompt("Date of birth: ",student.db);
        prompt("Blood group: ",student.blood);
        prompt("Department:",student.dept);
        prompt("ID number:",student.id);
        prompt("Address:",student.address);
        prompt("Phone no.:",student.phone);
        prompt("Email address:",student.email);

        //adjusting them with their string length
        adjust(student.name,50);
        adjust(student.db,10);
        adjust(student.blood,4);
        adjust(student.dept,4);
        adjust(student.id,10);
        adjust(student.address,200);
        adjust(student.phone,20);
        adjust(student.email,30);

        //saving it to the file
        fprintf(file,"%s%s%s%s%s%s%s%s\n",student.id,student.name,student.db,student.blood,student.dept,student.address,student.phone,student.email);
    }
    if(fclose(file)){
        printf("Error closing file...");
        exit(1);
    }
}



void remove_student(char *id){
    FILE *file;
    FILE *t_file;
    int loc_set;
    char ch;

    loc_set = query(id);

    if(loc_set != -1){
        /* Open all files as needed */
        if((file = fopen("info.dat","r"))==NULL){
            printf("Error opening file...");
            exit(1);
        }
        if((t_file = fopen("temp.dat","w"))==NULL){
            printf("Error opening file...");
            exit(1);
        }
        while(!feof(file)){
            if(ftell(file) == loc_set) fseek(file,gap,SEEK_CUR);
            ch = fgetc(file);
            if(!feof(file)) fputc(ch,t_file);
        }
        fclose(file);
        fclose(t_file);

        if((file = fopen("info.dat","w"))==NULL){
            printf("Error opening file... ");
            exit(1);
        }
        if((t_file = fopen("temp.dat","r"))==NULL){
            printf("Error opening file... ");
            exit(1);
        }
        while(!feof(t_file)){
                ch = fgetc(t_file);
                if(!feof(t_file)) fputc(ch,file);
        }
        fclose(file);
        fclose(t_file);
        printf("Student removed");
        getch();
    }
    else {
        printf("Not found");
        getch();
    }
}



int query(char *id_string){
    
    /* to search for the location of the record in the record file 
    it returns an integer value that is the position of the found record .
    if not found it returns -1  ......................................*/
        
    FILE *file;
    int i , last_loc , loc=0;
    char name_ch[51];
    char id_ch[11];

    if((file = fopen("info.dat","r"))==NULL){
        printf("Error opening file..");
        exit(1);
    }
    fseek(file,0L,SEEK_END);
    last_loc = ftell(file) - 1;

    /* this is tricky. this starts from the 0th position, and increament by length of one full record 
    untill it reaches the end */
    for(fseek(file,0,SEEK_SET);ftell(file)<last_loc;fseek(file,loc += gap,SEEK_SET)){
            
            /* this part takes the first 10 bytes off the record and compares it with the id that we are looking for
            if found then it returns the starting point of the record ...........................................*/
            for(i=0;i<10;i++) id_ch[i]=fgetc(file);
            id_ch[i] = '\0';
            cut_string(id_ch);
            if(!strcmp(id_string,id_ch)) return ftell(file)-(ftell(file)%gap);
            

    }
    fclose(file);
    return -1;
}



int show(int start_loc){
    
    /* this func takes the starting position of a record. which can be found by the query function
    if the arg is -1 that means id not found . Else it outputs all the records accordingly */
        
    int i;
    if(start_loc == -1) printf("\n\n\tNot found");
    else {
        printf("\n\n\n\tFound\n");

        FILE *file;
        if((file = fopen("info.dat", "r"))==NULL){
            printf("Error opening file...");
            exit(1);
        }

        fseek(file,start_loc,SEEK_SET);
        for( i = 0 ; i<10  ; i++ ) student.id[i]      = fgetc(file);
        for( i = 0 ; i<50  ; i++ ) student.name[i]    = fgetc(file);
        for( i = 0 ; i<10  ; i++ ) student.db[i]      = fgetc(file);
        for( i = 0 ; i< 4  ; i++ ) student.blood[i]   = fgetc(file);
        for( i = 0 ; i< 4  ; i++ ) student.dept[i]    = fgetc(file);
        for( i = 0 ; i<200 ; i++ ) student.address[i] = fgetc(file);
        for( i = 0 ; i<20  ; i++ ) student.phone[i]   = fgetc(file);
        for( i = 0 ; i<30  ; i++ ) student.email[i]   = fgetc(file);

        cut_string(student.id);
        cut_string(student.name);
        cut_string(student.db);
        cut_string(student.blood);
        cut_string(student.dept);
        cut_string(student.address);
        cut_string(student.phone);
        cut_string(student.email);  br

        printf("\t\t\t ID         : ");
        printf(student.id);         br
        printf("\t\t\t Name       : ");
        printf(student.name);       br
        printf("\t\t\t Birth      : ");
        printf(student.db);         br
        printf("\t\t\t Blood      : ");
        printf(student.blood);      br
        printf("\t\t\t Department : ");
        printf(student.dept);       br
        printf("\t\t\t Address    : ");
        printf(student.address);    br
        printf("\t\t\t Phone      : ");
        printf(student.phone);      br
        printf("\t\t\t Email      : ");
        printf(student.email); br   br
    }
    printf("\n\n\tPress any key to go back\n");

    getch();

}



void print_search(){
    /* An utility function to show the search page */
    system("cls");
    char id[11];
    prompt("Enter ID for query: ",id);
    show(query(id));
}



void print_remove(){
    /* An utility function to show the record deleting page */
    system("cls");
    char id[11];
    prompt("Enter ID to remove: ",id);
    remove_student(id);
}



int print_home(){
    /* function to print the home page. pretty basic */
    int i ;
    char choice[1];
    printf("\n\n\n\n\n\t\t\t   1. Search Student \n");
    printf("\t\t\t   2. Add Student \n");
    printf("\t\t\t   3. Remove Student \n");
    printf("\t\t\t   4. Exit \n");
    printf("\n\n\t\t\tPlease Enter Your Choice :");

    gets(choice);
    i = atoi(choice);
    return i;
}



int main(){
    int choice;
    do{
        system("cls");
        choice = print_home();
        switch(choice){
            case 1:
            print_search();
            break;

            case 2:
            add_student();
            break;

            case 3:
            print_remove();
            break;
        }
    }while(choice != 4);
    return 0;
}
