/*
  ------- Student Management System -----------

  Created by 137114- MATTHEW CHOMBA MUCHANGI

  ---------------------------------------------
*/

#include<stdio.h>
#include<windows.h>
#include<dos.h>
#include<stdlib.h>
#include <iostream>
#include<time.h>
#include<conio.h>
#include<string>
#include <mysql.h>
#include <sstream>

using namespace std;

/*This part of the code used for cursor movement and functionalilities*/

static int x=1;
#define pos gotoxy(33,x++)
#define ln  printf(".......................");
 COORD coord={0,0};
 void gotoxy(int x,int y);
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//A Void for Delay

void delay(unsigned int mseconds)
{
    clock_t goal=mseconds+clock();
    while(goal>clock());
}
void setcolor(int ForgC) //function to change setcolor
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
 }


int c=0;
string username;
string userpass;
void about();
void addstudent();
void viewstudent();
void deletestudent();

//Box for the interface

void box(int x,int y,int l,int b)
{
    int i,m;
    gotoxy(x,y); printf("%c",201);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,y);
        printf("%c",205);
    }
    gotoxy(i,y); printf("%c",187);

    for (m=y+1;m<b;m++)
    {
        gotoxy(x,m);
        for(i=x;i<l;i++)
        {
            if(i==x||i==l-1)
            {
                gotoxy(i,m); printf("%c",186);
            }

        }

    }

    gotoxy(x,m); printf("%c",200);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,m);
        printf("%c",205);
    }
    gotoxy(i,m); printf("%c",188);
}

//Connection to MySQL Server

MYSQL_RES* Perform_Query(MYSQL* connection, const char* query)
{
// send the query to the database
if (mysql_query(connection, query))
{
cout << "MySQL query error : %s\n" << mysql_error(connection) << endl;
exit(1);
}
return mysql_use_result(connection);
}



//Display Table from "Students" Database

viewstudents(MYSQL* connect){

MYSQL_ROW row;
MYSQL_RES* res;
if(connect){
    int qstate = mysql_query(connect, "SELECT * FROM students");
    if(!qstate){
        res = mysql_store_result(connect);
        int count = mysql_num_fields(res);
        while (row = mysql_fetch_row(res)){
                cout<<"        "<<endl;
            for(int i=0; i<count; i++){
                cout<<"        "<<row[i];
            }
            cout << "\n";
            cout<<"\t------------------------------------------------------------------------------------------------------------";
            cout<<endl;
        }
    }
    else{cout<<"Failed to Fetch.";}
}



}

/* Main Function Starts Here : */

int main()
{

	int choice;

    time_t t;
    time(&t);
    x=1;
    system("cls");
    pos;
    setcolor(90) ;
    printf("--- Student Management System --- ");
    pos;
    pos;
    ln pos;
    cout<<"\n\n";
    if(c==0)
       {
           setcolor(36) ;
           printf(" Enter Username : ");
           setcolor(7);
        cin >> username;
        setcolor(36) ;
         printf(" Enter Userpass : ");
         setcolor(7);
        cin >> userpass;
        if(username == "Matt" && userpass == "1234"){
		system("cls");
       c++;
       setcolor(90) ;
    printf("\n\t\t\t\t --- Student Management System --- ");
    pos;
    pos;ln pos;
     setcolor(90) ;
        printf("-- Menu --");
        pos;
        ln
        pos;
        setcolor(36) ;
        printf("1 - Add a Student");
        pos;
        printf("2 - View Students");
        pos;
        printf("3 - Delete a Student");
        pos;
        printf("4 - About");
        pos;
        printf("0 - Logout");
        pos;
        printf("Enter Your Choice::");
        setcolor(7);
        scanf("%d",&choice);
        pos;
        switch(choice)
        {
		    case 1:addstudent();break;
            case 2:viewstudent();break;
            case 3:deletestudent();break;
            case 4:about();break;
            case 0:exit(1);
            default:main();
        }
 getch();

	}else if(username == "Matt" && userpass != "1234"){
		cout<<"\n";
		cout<<"Password is incorrect!!!";
	}else if(userpass == "1234" && username != "Matt"){
		cout<<"\n";
		cout<<"Username is incorrect!!!";
	}else{
		cout<<"\n";
		cout<<"Details are incorrect, kindly try again!";
	}
}
}
void deletestudent()
{

	box(0,0,70,15);
    delay(200);
   	system("cls");
   	int choice;

    MYSQL* connect;
    connect = mysql_init(0);
    connect = mysql_real_connect(connect, "localhost", "root", "", "student_management_system", 3306, NULL, 0);

    if(connect){
        //cout<<"Connection Successful"<<endl;
   	string id;
   	int statement = 0;
   	int si;
  	setcolor(90) ;
    cout<<"\n\n";
  	cout << "-- Enter Student Details --";
  	cout<<"\n\n";
  	cout <<"Enter Student ID (as integer value) : ";
  	cin >> id;
  	cout<<endl;
  	if(!statement){
    string deletes = "DELETE FROM `students` WHERE `Student_ID` = '"+ id +"'";
  	const char* d = deletes.c_str();
  	statement = mysql_query(connect, d);
        cout<<"Student Successfully Deleted!!!"<<endl;
  	}

    else{

        cout<<"Student Details Failed to be Deleted."<<endl;

        }
        cout<<endl;
        pos;
		++x;
		pos;
		printf(" 1.  Delete another Student");
		pos;
		printf(" 2. Menu ");
		printf(" Enter your choice:: ");
		scanf("%d",&choice);
		switch(choice)
		{
		      case 1:deletestudent();break;//recursive call
		      case 2:main();
		}
}
}

void addstudent(){

    	box(0,0,70,15);
    delay(200);
   	system("cls");
   	int choice;

    MYSQL* connect;
    connect = mysql_init(0);
    connect = mysql_real_connect(connect, "localhost", "root", "", "student_management_system", 3306, NULL, 0);

    if(connect){
        //cout<<"Connection Successful"<<endl;


   	string id, dob, fname, lname, gender, email, cname, ccode;
   	int statement = 0;
   	int si;
   	int tr = 0;
  	setcolor(90) ;
    cout<<"\n\n";
  	cout << "-- Enter Student Details --";
  	cout<<"\n\n";
  	cout <<"Enter Student ID (as integer value) : ";
  	setcolor(7);
  	cin >> id;
  	cout << "\n";
  	setcolor(90) ;
  	cout << "Enter Student First Name : ";
  	setcolor(7) ;
  	cin >> fname;
  	cout << "\n";
  	setcolor(90) ;
  	cout <<"Enter Student Last Name : ";
  	setcolor(7) ;
  	cin >> lname;
  	cout << "\n";
  	setcolor(90) ;
  	cout <<"Enter Student Gender : ";
  	setcolor(7) ;
  	cin >> gender;
  	cout << "\n";
  	setcolor(90) ;
  	cout <<"Enter Student Date of Birth (in format dd/MM/YYYY) : ";
  	setcolor(7) ;
  	cin >> dob;
  	cout << "\n";
  	setcolor(90) ;
  	cout <<"Enter Student Email : ";
  	setcolor(7) ;
  	cin >> email;
  	cout << "\n";
  	setcolor(90) ;
	cout <<"Enter Course Name : ";
	setcolor(7) ;
  	cin >> cname;
  	cout << "\n";
  	setcolor(90) ;
  	cout <<"Enter Course Code : ";
  	setcolor(7) ;
  	cin >> ccode;
  	cout<<endl;

  	string insert = "INSERT INTO `students`(`Student_ID`, `First_Name`, `Last_Name`, `Gender`, `Date_of_Birth`, `Email`, `Course_Name`, `Course_Code`) VALUES ('"+ id +"','"+ fname +"','"+ lname +"','"+ gender +"','"+ dob +"','"+ email +"','"+ cname +"','"+ ccode +"')";
  	const char* i = insert.c_str();
  	statement = mysql_query(connect, i);
  	if(!statement){
        cout<<"Student Successfully Added!!!"<<endl;
        cout<<"\n";
  	}

    else{

        cout<<"Student Details Failed to be Added."<<endl;
        cout<<"\n";
    }
        pos;
		++x;
		pos;
		printf(" 1.  Add another Student");
		pos;
		printf(" 2. Menu ");
		printf(" Enter your choice:: ");
		setcolor(7) ;
		scanf("%d",&choice);
		switch(choice)
		{
		      case 1:addstudent();break;//recursive call
		      case 2:main();
		}
    }
}

void about()
{       system("cls");
    gotoxy(7,7);
    cout<<"\t\t\t --- About ---"<<endl;
    printf(" - Many schools and educational institutions still use physical records of students. \n Which has concluded being un-efficient and time consuming. By introducing the student management system teachers, lectures, etc will now be able to keep track of student records and be able to add, delete, and modify student data without having to go through many files looking for a certain record.");
       cout<<endl;
       printf("\t\t\t Thank you for using the Student Management System, Matthew Chomba Muchangi (137114).");
       getch();
       main();
}

void viewstudent(){


    string mainServer="127.0.0.1";
    string mainDbUser="root";
    string mainDbPass="";
    MYSQL *connect;
    connect=mysql_init(NULL);

    if(!connect)
    printf("Could not connect.\n");
    else if (mysql_real_connect(connect, mainServer.c_str(), mainDbUser.c_str(), mainDbPass.c_str(),
    "student_management_system" ,0,NULL,0))
    {
    printf("Could connect to the MYSQL Server.\n");
    }
    pos;

int back;
   system("cls");
                setcolor(14) ;
                printf("-- View Students --");
                cout<<endl<<"\n";
                setcolor(9) ;
                 cout<<"\tStudent ID - First Name - Last Name - Gender - Date of Birth -  Email Address -  Course Name -  Course Code\n";
                 cout<<"\t------------------------------------------------------------------------------------------------------------";
                 cout<<endl<<"\t";
                 viewstudents(connect);
                 cout<<"\n\n\n";
                printf("Click on 1 to go back to the Main Menu : ");
                scanf("%d",&back);
                switch(back){
                case 1:main();break;
		        default:pos;printf(" Wrong choice! ");pos;
				main();
                }
                }

