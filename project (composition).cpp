#define MAX 50
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<iostream>
using namespace std;

struct Data
{
	char location[MAX], destination[MAX], bus_name[MAX];
}d;

class User_Admin
{
	public:
		int password();
		void add_record();
		void delete_record(char []);
		int view_requests();
		void delete_req();
};

class User_Guest
{
	public:
		void request();
};

class System
{
	public:
		User_Admin a;
		User_Guest g;
		int use_system();
		int display_all();
};

int main(void)
{
	System s1;
	int choice;
	start:
		system("cls");
		cout<<"\t\tWELCOME TO BUS GUIDE SYSTEM"<<endl;
		cout<<"\tSELECT AN ACCOUNT TO USE: ";
		cout<<"\n\t  1.Admin\t2.Passenger\t3.EXIT";
		cout<<"\n\tCHoice> ";
		cin>>choice;
		if(choice==1)
		{	check:
			if(s1.a.password()==1)
			{
				while(1)
				{
				btp:	
					int admin_op;
					system("cls");
					cout<<"\t\t\tWELCOME ADMINISTRATOR"<<endl;
					cout<<"\n\t\t1.Test the System"<<endl;
					cout<<"\n\t\t2.ADD a Record"<<endl;
					cout<<"\n\t\t3.DELETE a Record"<<endl;
					cout<<"\n\t\t4.Requests to Update DataBase"<<endl;
					cout<<"\n\t\t5.Display the Database"<<endl;
					cout<<"\n\t\t6.Log Out & Back to Main Menu"<<endl;
					cout<<"\t\tChoice> ";
					cin>>admin_op;	
					if(admin_op==1)
					{
						s1.use_system();
						cout<<"\t\t";
						system("pause");
					}
					else if(admin_op ==2)
					{
						do{
							cout<<endl;
							s1.a.add_record();
							cout<<"\t\tDO you Want to Add another Record (y/n)? >";
						}while(getche()=='y');
					}
					else if(admin_op ==3)
					{	
						char BUS[MAX];
						system("cls");
						cout<<"\t\tRECORD DELETION\n"<<endl;
						s1.display_all();
						cout<<"\tPlease Enter Details to Delete the Record: "<<endl;
						cout<<"\tEnter the Bus Name to delete >";
						fflush(stdin);
						gets(BUS);
						s1.a.delete_record(BUS);
						cout<<"\t";
						system("pause");
					}
					else if(admin_op ==4)
					{
						system("cls");
							s1.a.view_requests();
						cout<<"\n\tPress 'y' to delete a Record if Done> ";
						if(getche()=='y')
							s1.a.delete_req();
						cout<<"\n\t\t";
						system("pause");
					}
					else if(admin_op ==5)
					{
						system("cls");
						s1.display_all();
						cout<<"\t";
						system("pause");
					}
					else if(admin_op==6)
						goto start;
					else
					{
						cout<<"\tInvalid Choice, want to try again(y/n)? ";
						if(getch()=='n')
							exit(0);
						goto btp;
					}
				}
			}
			else
			{
				while(1)
				{
					cout<<" --> Wrong Password, Try Again(y/n)? ";
					if(getch()=='y')
						goto check;
					else
						goto start;
				}
			}
		}
		else if(choice==2)
		{
			int guest_op, found;
			system("cls");
			cout<<"\t\t\tWELCOME GUEST"<<endl;
			cout<<"Instruction to Use:"<<endl;
			cout<<"\t\t1.This System is Made for City Karachi Only."<<endl;
			cout<<"\t\t2.You have to Enter your Address and your Destination Respectively."<<endl;
			cout<<"\t\t3.Incase of Error, Kindly Restart the System(Sorry For Inconvenience)"<<endl;
			cout<<"\n\tPRESS ANY KEY TO CONTINUE...";
			getch();
	menu:	system("cls");
			cout<<"\t\t1.System\t2.Display All\t3.Send Request to Add a Record\t4.Back to Main Menu"<<endl;
			cout<<"Choice> ";
			cin>>guest_op;
			if(guest_op==1)
			{
				found=s1.use_system();
				if(found==0)
				{
					cout<<"\tRequest Administrator to Add this Record (y/n)? >";
					if(getche()=='y')
					{
						cout<<endl;
						s1.g.request();
					}
				}
				cout<<"\t\t";
				system("pause");
				goto menu;
			}
			else if(guest_op==2)
			{
				s1.display_all();
				cout<<"\t\t";
				system("pause");
				goto menu;
			}
			else if(guest_op==3)
			{
				s1.g.request();
				cout<<"\t\t";
				system("pause");
				goto menu;
			}
			else if(guest_op==4)
				goto start;
			else
			{
				cout<<"INVALID INPUT!";
				cout<<"\n\t\t";
				system("pause");
				goto menu;
			}
		}
		else if(choice==3)
			exit(0);
		else
		{
			cout<<"\tInvalid Choice, Try Again Later!\n\t";
			getch();
			goto start;
		}
	return 0;
}


//FUNCTIONS DEFINED
						//COMMON FEATURES
//	1.
		int System::use_system()
		{
			ifstream record;
			int counter=0;
			char searchl[MAX], searchdest[MAX];
			
			cout<<"\t\tEnter the Current Location >";
			fflush(stdin);
			gets(d.location);
			cout<<"\t\tEnter the Destination >";
			gets(d.destination);
			strcpy(searchl,d.location);
			strcpy(searchdest,d.destination);
			record.open("data.txt", ios::in | ios::binary);
			if(!record)
				cout<<"\nFile Not Found";
			else
			{
				record.read((char*)&d, sizeof(d));
				while(!record.eof())
				{
					if(!strcmpi(searchl,d.location))
					{	
						if(!strcmpi(searchdest,d.destination))
						{
							cout<<"\n\t\t"<<d.location<<" --> "<<d.destination<<" --> "<<d.bus_name<<endl;
							counter++;
						}
					}
					else if(!strcmpi(searchdest,d.location))
					{
						if(!strcmpi(searchl,d.destination))
						{
							cout<<"\n\t\t"<<searchl<<" --> "<<searchdest<<" --> "<<d.bus_name<<endl;
							counter++;
						}
					}
					record.read((char*)&d, sizeof(d));
				}
				if(counter==0)
				{
					record.close();
					cout<<"\tSorry No Record found for the given Address in DataBase\n";
					return (0);
				}
				
			}
			record.close();
		}
//	2.
		int System::display_all()
		{
			static int n;
			ifstream record;
			record.open("data.txt", ios::in | ios::binary);
			if(!record)
			{
				cout<<"\n\t\tFile Not Found\n";
				return 0;
			}
			n=1;
			cout<<"\t---RECORDS AVAILABLE IN DATABASE---"<<endl;
			cout<<"\t(LOCATION --> DESTINATION --> BUS)"<<endl;
			if(record.read((char*)&d, sizeof(d))==0)
					cout<<"\n\t\tNO RECORD AVAILABLE\n";
			else
				while(!record.eof())
				{
					cout<<"\n\t"<<n++<<". "<<d.location<<" --> "<<d.destination<<" --> "<<d.bus_name<<endl;
					record.read((char*)&d, sizeof(d));
				}
			record.close();
		}
		
		//ADMIN FUNCTIONS
//1.
		int User_Admin::password()
		{
			int i=0;
			char pass, password[26];
			cout<<"\nEnter the Admin Password: (No Backspace) ";
			while(pass!='\r')
			{
				pass=getch();
				if(pass=='\r')			
				{
					password[i]='\0';
					break;
				}
				if(pass=='\b' || pass==127)
				{
					if(i>0)
					{
						cout<<"\b \b";
						i--;
					}
				}
				else
				{
					password[i++]=pass;
					cout<<"*";
				}
			}
			if((strcmp(password,"welcome"))==0)
				return (1);	
			else
				return (0);
		}
//2.
		void User_Admin::add_record()
		{
			cout<<"\t\tEnter the Location >";
			fflush(stdin);
			gets(d.location);
			cout<<"\t\tEnter the Destination >";
			fflush(stdin);
			gets(d.destination);
			cout<<"\t\tEnter the Bus Name: ";
			gets(d.bus_name);
			ofstream record;
			record.open("data.txt", ios::app | ios::binary);
			record.write((char*)&d, sizeof(d));
			record.close();
		}
//	3.
		void User_Admin::delete_record(char BUS[MAX])
		{	
			int count=0;
			ifstream record;
			ofstream rec;
			record.open("data.txt", ios::in | ios::binary);
			if(!record)
				cout<<"\nFile Not Found";
			else
			{
				rec.open("temp.txt", ios::out | ios::binary);
				record.read((char*)&d, sizeof(d));
				while(!record.eof())
				{
					if((strcmpi(BUS,d.bus_name))==0)
						count++;
					else
						rec.write((char*)&d, sizeof(d));
					record.read((char*)&d, sizeof(d));
				}
				record.close();
				rec.close();
				remove("data.txt");
				rename("temp.txt","data.txt");
				if(count==0)
					cout<<"\tRecord Not Found\n";
				else
					cout<<"\tRecord deleted Sucessfully\n";
			}
		}
//	4.
		int User_Admin::view_requests()
		{
			ifstream record;
			record.open("requests.txt", ios::in | ios::binary);
			static int n;
			if(!record)
			{
				cout<<"\n\t\tFile Not Found\n";
				return 0;
			}
			cout<<"\t---REQUESTS AVAILABLE IN DATABASE---"<<endl;
			cout<<"\t(LOCATION --> DESTINATION --> BUS)"<<endl;
			if(record.read((char*)&d, sizeof(d))==0)
					cout<<"\n\t\tNO REQUESTS AVAILABLE\n";
			n=1;
			while(!record.eof())
			{
				cout<<"\n\t"<<n++<<". "<<d.location<<" --> "<<d.destination<<" --> "<<d.bus_name<<endl;
				record.read((char*)&d, sizeof(d));
			}
			record.close();
		}
//	5.
		void User_Admin::delete_req()
		{
			char BuS[MAX]; int count=0;
			cout<<"\n\tEnter the Bus Name > ";
			fflush(stdin);
			gets(BuS);
			//DELETE from FILE
			ifstream record;
			ofstream rec;
			
			record.open("requests.txt", ios::in | ios::binary);
			if(!record)
				cout<<"\nFile Not Found";
			else
			{
				rec.open("tempr.txt", ios::out | ios::binary);
				record.read((char*)&d, sizeof(d));
				while(!record.eof())
				{
					if((strcmpi(BuS,d.bus_name))!=0)
						rec.write((char*)&d, sizeof(d));
					else
						count++;
					record.read((char*)&d, sizeof(d));
				}
				record.close();
				rec.close();
				remove("requests.txt");
				rename("tempr.txt","requests.txt");
				if(count==0)
					cout<<"\tRecord Not Found\n";
				else
					cout<<"\tRecord deleted Sucessfully\n";
			}
		}
					//GUEST FUNCTIONS
//1.
		void User_Guest::request()
		{
			ofstream rec;
			rec.open("requests.txt", ios::app | ios::binary);
			fflush(stdin);
			cout<<"\n\tEnter the Location: ";
			gets(d.location);
			cout<<"\tEnter the Destination: ";
			gets(d.destination);
			cout<<"\n\tEnter the Bus Name (if don't know, leave a question mark): ";
			gets(d.bus_name);
			rec.write((char*)&d, sizeof(d));
			cout<<"\tThank You very much, We'll Update our DataBase Soon :)\n\t";
			rec.close();
		}
