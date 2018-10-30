#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

struct vehicle{
    char ID[15];
    char name[20];
    char type[20];
    char brand[20];
    char owner[20];
    char reg[20];
    char owner_age[20];
};

struct vehicle veh;

///This will set the forground color for printing in a console window.
void SetColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawRectangle(){
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < 78; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(78,0);
    printf("%c",187);
    for(i = 1; i < 25; i++){
        gotoxy(78, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(78, 25);
    printf("%c",188);
    for(i = 77; i > 0; i--){
        gotoxy(i,25);
        if(i == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(0,25);
    printf("%c",200);
    for(i = 24; i > 0; i--){
        gotoxy(0,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 1; i < 78; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 25; i++){
        gotoxy(35,i);
        printf("%c",186);
    }

}

void clearWindow(){
    int i,j;
    for(i = 37; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}

void window(){
    drawRectangle();
    gotoxy(28,2);
    SetColor(35);
    printf("TRAFIKVERT VEHICLE REGISTRATION SYSTEM \n");

    gotoxy(45,7);
    SetColor(35);
    printf("Records Available \n");

     FILE *fp;
    char str[MAXCHAR];

    fp = fopen("record.txt", "rb");
    if (fp == NULL){
        printf("Could not open file %s", "records");
        return 1;
    }
    while(fread(&veh,sizeof(veh),1,fp)){
        gotoxy(40,9);
        SetColor(35);
        printf("ID: %s \n",veh.ID);
        gotoxy(43,10);printf("Vehicle Name: %s \n",veh.name);
        gotoxy(43,11);printf("Type: %s \n",veh.type);
        gotoxy(43,12);printf("Brand: %s \n",veh.brand);
        gotoxy(43,13);printf("Reg Number: %s \n",veh.reg);
        gotoxy(43,14);printf("Owner: %s \n",veh.owner);
        gotoxy(43,15);printf("Owner age: %s \n",veh.owner_age);
    }

    fclose(fp);

}


void print_heading(const char st[]){
    SetColorAndBackground(31,28);
    gotoxy(45,8);printf("SRS : %s",st);
    SetColorAndBackground(17,15);
}

int conf_record(char id[]){
   // left for you
   //it checks whether the entered id for
   //new record is already in the database.
}

void add_vehicle(){
    clearWindow();
    print_heading("Add a Vehicle");
    int print = 37;
    FILE *fp;
    fp = fopen("record.txt","ab+");
    SetColor(45);
    if(fp == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    }else{
        fflush(stdin);
        gotoxy(print,10);printf("ID: ");gets(veh.ID);
        //here you can confirms the ID
        gotoxy(print,12);printf("Name: ");gets(veh.name);
        gotoxy(print,14);printf("Type: ");gets(veh.type);
        gotoxy(print,16);printf("Brand: ");gets(veh.brand);
        gotoxy(print,18);printf("Reg Number: ");gets(veh.reg);
        gotoxy(print,20);printf("Vehicle Owner: ");gets(veh.owner);
        gotoxy(print,20);printf("Vehicle Owner's age: ");gets(veh.owner_age);
        fwrite(&veh, sizeof(veh), 1, fp);
        gotoxy(40,22); printf("The record is sucessfully added");
    }
    SetColor(28);
    fclose(fp);
    return;
}

void delete_vehicle(){
    clearWindow();
    print_heading("Delete vehicle Record");
    SetColor(45);
    char s_id[15];
    int isFound = 0, print = 37;
    gotoxy(37,10);printf("Enter Vehicle ID to Delete: ");fflush(stdin);
    gets(s_id);
    FILE *fp, *temp;
    fp = fopen("record.txt","rb");
    temp = fopen("temp.txt", "wb");
    while(fread(&veh, sizeof(veh),1,fp) == 1){
        if(strcmp(s_id, veh.ID) == 0){
            fwrite(&veh,sizeof(veh),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("record.txt");
    rename("temp.txt","record.txt");
    gotoxy(37,12);printf("The Vehicle record is successfully deleted");
    SetColor(28);
    return;
}

//A sort function to be created here
void search_vehicle(){
    clearWindow();
    print_heading("View Vehicle Info");
    SetColor(45);
    char s_id[15];
    int isFound = 0;
    gotoxy(37,10);printf("Enter ID to View: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("record.txt","rb");
    while(fread(&veh,sizeof(veh),1,fp) == 1){
        if(strcmp(s_id,veh.ID) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        gotoxy(37,12);printf("Vehicle Record is Found");
        gotoxy(37,14);printf("ID: %s",veh.ID);
        gotoxy(37,15);printf("Vehicle Name: %s",veh.name);
        gotoxy(37,16);printf("Brand: %s",veh.type);
        gotoxy(37,17);printf("Brand: %s",veh.brand);
        gotoxy(37,18);printf("Reg Number: %s",veh.reg);
        gotoxy(37,19);printf("Owner: %s",veh.owner);
        gotoxy(37,20);printf("Owner age: %s",veh.owner_age);
    }else{
        gotoxy(37,12);printf("Sorry, No record found in the database");
    }
    SetColor(28);
    fclose(fp);
    return;
}

void sort_records(){
    //left for further enhancement
}

void close_program(){
    //left for further enhancement
}

void main_window(){
    int choice;
    SetColor(28);
    int x = 2;
    while(1){
        gotoxy(x,8);printf("1. Add Vehicle");
        gotoxy(x,10);printf("2. Delete Vehicle");
        gotoxy(x,12);printf("3. View Vehicle Record");
        gotoxy(x,14);printf("4. Sort Records");
        gotoxy(x,16);printf("5. Exit");
        gotoxy(x,22);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                add_vehicle();
                break;
            case 2:
                delete_vehicle();
                break;
            case 3:
                search_vehicle();
                break;
            case 4:
                sort_records();
                break;
            case 5:
                close_program();
                break;
            default:
                break;
        }

    }

}

int main(){
    ClearConsoleToColors(17,15);
    SetConsoleTitle("Trafikverket - Veicle Registration");
    window();
    //use_pass_field();
    main_window();
    return 0;
}

