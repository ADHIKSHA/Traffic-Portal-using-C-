#include<windows.h>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<cstdio>
#include<stdlib.h>
#include<string.h>
#include<cstring>
#include <windows.h>
using namespace std;

struct date{
int dd,mm,yy;
};
void dispdate(date dr)
{
	cout<<dr.dd<<":"<<dr.mm<<":"<<dr.yy;
}
class node{
	public: 
		node(){
			acc_id=0;
		}
		int acc_id;
		string nofp;
		string nofo;
		date dat;
		long license_no;
		string vehicle_no;
		int crime_no;
		int fine;
		string crime;	
		node *next;	

};

class traffic{
	public:
		
		int number;
		char name[200];
		int officers;
		
};
void constforsignals(int total){
	ofstream fout("constsig.txt",ios::out);
	fout<<total;
	fout.close();
}
int read_consts()
{ int t;
	ifstream fin("constsig.txt",ios::in);
	fin>>t;
//	cout<<t;
	return t;
}
int total=read_consts();


void add_signals(int tot){
	traffic tp[tot];
	char namear[200];
	int y=0;
	int no;
	cout<<"\n Enter name of area=";
	cin>>namear;
	ifstream fint;
	fint.open("traffic.txt",ios::in|ios::ate);
	ofstream fout;
	fout.open("new.txt",ios::out|ios::app);
//	cout<<"\n files opened!";
	fint.seekg(0,ios::beg);
	//cout<<"\n get into loop!";
		while(!fint.eof())
	{
		while(y!=tot){
			
		fint.read((char*)&tp[y],sizeof(tp[y]));
//	cout<<"\n tp.name="<<tp[y].name<<"name ar="<<namear;
		 if(strcmp(tp[y].name,namear)==0)
	  {
	  	cout<<"\n Enter the number of officers to be added in "<<namear<<" =";
	  	cin>>no;
	  	tp[y].officers+=no;
	  	//cout<<"\n new record="<<endl;
	  //	cout<<setw(30)<<tp[y].name<<setw(15)<<tp[y].number<<setw(15)<<tp[y].officers<<endl;
	  		fout.write((char*)&tp[y],sizeof(tp[y]));
	  }
	  else{
	  	fout.write((char*)&tp[y],sizeof(tp[y]));
	  }
		//cout<<setw(30)<<tp[y].name<<setw(15)<<tp[y].number<<setw(15)<<tp[y].officers<<setw(15)<<endl;
	
	if (fint.fail()) {
            cout << "Fail bit set. Clearing it for read to resume" << endl;
            fint.clear(); //Clear the fail bit (Warning: this function can also clear the EOF bit if not used properley)
        }
			y++;
	}
	if(y==tot)
	break;
		}
	 
	fout.close();
	fint.close();
	remove("traffic.txt");
	rename("new.txt","traffic.txt");
cout<<"\n Officers have been added!";

}
void show_signals(int tot)
{
	traffic tr[tot];
	int y=0;
	ifstream fin;
	fin.open("traffic.txt",ios::in);
	cout<<"\n the records are:-"<<endl;
	cout<<setw(30)<<"AREA"<<setw(15)<<"SIGNALS"<<setw(15)<<"OFFICERS"<<setw(15)<<endl;
	while(!fin.eof())
	{
		while(y!=tot){
		fin.read((char*)&tr[y],sizeof(tr[y]));
			cout<<setw(30)<<tr[y].name<<setw(15)<<tr[y].number<<setw(15)<<tr[y].officers<<setw(15)<<endl;
	
	if (fin.fail()) {
            cout << "Fail bit set. Clearing it for read to resume" << endl;
            fin.clear(); //Clear the fail bit (Warning: this function can also clear the EOF bit if not used properley)
        }
			y++;
	}
	if(y==tot)
break;
		}
	fin.close();
	}
void traffic_signals(traffic t)
{
ofstream fout;
fout.open("traffic.txt",ios::app|ios::out);					//app helps in adding more records to the file
total++;
fout.write((char*)&t,sizeof(t));
fout.close();

}


class records{
	node *head;
	int total;
	public:
		records()
		{
			head=NULL;
			total=0;
		}
	void create(node );
	void insert(node );
	void insert_in_list(node *);
	void display_records(node*);
	void display(int);
	int calc_fine(node &);
};

int records::calc_fine(node &y)
{
	switch(y.crime_no)
	{
		 case 1:
		 	y.crime="license_not_made";
		 	y.fine=500;
		 	break;
		 case 2:
		 	y.crime="license_not_available_now";
		 	y.fine=200;
		 	break;
		 case 3:
		 	y.crime="without_helmet";
		 	y.fine=500;
		 	break;
		 case 4:
		 	y.crime="no_insurance";
		 	y.fine=1000;
		 	break;
		 case 5:
		 	y.crime="mobile_talking";
		 	y.fine=200;
		 	break;
		 case 6:
		 	y.crime="signal_jump";
		 	y.fine=200;
		 	break;
		 case 7:
		 	y.crime="No_tail_light ";
		 	y.fine=1000;
		 	break;
		 case 8:
		 	 y.crime=" No_vehicle_papers_available";
		 	y.fine=200;
		 	break;
		 case 9:
		 	y.crime="No_seat_belt";
		 	y.fine=200;
		 	break;
		 case 10:
		 	y.crime="Rash_driving";
		 	y.fine=1000;
		 	break;
	}
	return y.fine;
}
void records::create(node s)
{
	node *temp=new node();

	total++;
		if(temp==NULL) 
		{
		cout<<"\n SORRY memory was not allocated! Please try again later!";
	}
	    else {
		temp->acc_id=total;
		temp->license_no=s.license_no;
		temp->dat=s.dat;
		temp->nofo=s.nofo;
		temp->nofp=s.nofp;
		temp->vehicle_no=s.vehicle_no;
		temp->crime_no=s.crime_no;
		temp->fine=s.fine;
		temp->next=NULL;
		insert_in_list(temp);
}

}
void records::insert_in_list(node *dt)
{
	if(head==NULL)
	{
		head=dt;
	}
	else
	{
	node *t;
			t=head;
	while(t->next!=NULL) 
	{
		t=t->next;
    }
	t->next=dt;
	dt->next=NULL;
	}
}
void records::insert(node s)
{
	ofstream fout;
	fout.open("police.dat",ios::binary|ios::in|ios::app);
	fout.write((char*)&s,sizeof(s));
	fout.close();
}  
void records::display_records(node *dt)
{   cout<<"\n THE RECORD IS=";
	cout<<"\n The id            ="<<dt->acc_id;
	cout<<"\n Name of officer   ="<<dt->nofo;
	cout<<"\n Name of person    ="<<dt->nofp;
	cout<<"\n License no        ="<<dt->license_no;
	cout<<"\n Vehicle no        ="<<dt->vehicle_no;
	cout<<"\n Date              =";dispdate(dt->dat);	
	cout<<"\n Crime no          ="<<dt->crime_no;
	cout<<"\n Fine              ="<<dt->fine;
}
void records::display(int license)
{
	ifstream fin;
		int f=0;
		int x=0;
	fin.open("police.dat",ios::binary|ios::out);
	node *t;
	
	while(fin.read(((char*)&t),sizeof(t))){
t=head;
	while(x!=total){
		x++;
		if(t->license_no==license){
			display_records(t);
			f=1;
			t=t->next;
			break;
			}
			if(x==total)
				break;
		t=t->next;
	}
	
		}
	if(f==0)
	cout<<"\n the record not found!";	
}
	
	void welcomepage(){
	
	
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 32;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	for(int i=0;i<12;i++)
	cout<<endl;
	for(int j=0;j<4;j++)
	cout<<"\t";
	std::cout << "                POLICE PORTAL";
		cout<<"\n";
		cfi.dwFontSize.Y = 18; 
		
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	}
bool check(string n,string p){
	char nam[20];
	char pass[20];
	ifstream fin;
	fin.open("users.txt",ios::in);
	while(fin>>nam){
		fin>>pass;
		if(nam==n&&pass==p)
			return 1;
	}
	return 0;
}
string login(){
	string name,password;
	int f=0;
	do{
	cout<<"\n                                                    Please login into your account:-"<<endl;
	cout<<"\n                                                                                                      ENTER YOUR NAME="<<endl;
	cout<<"\n                                                                                                              ";
	cin>>name;
	cout<<"\n                                                                                                      ENTER THE PASSWORD"<<endl;
	cout<<"\n                                                                                                              ";
	cin>>password;
	f=check(name,password);
	if(f==0)
	cout<<"\n                                                     Wrong login details!!";
	}while(f==0);
	return name;
}
void sendmails(node r){
	char mailid[100];
	cin.ignore();
	cout<<"\n enter mailid=";
	cin.getline(mailid,100,'\n');
	fstream file("mail.txt",ios::out);
	file<<"From: User Name <tryonmailtp@gmail.com>";
	file<<"\nTo: "<<r.nofp<<" <"<<mailid<<">";
	file<<"\nSubject: The Fine Charged!";
	file<<"\nHello "<<r.nofp<<" !";
	file<<"\n ======Your Record dated  -  "<<r.dat.dd<<"/"<<r.dat.mm<<"/"<<r.dat.yy<<"  is===========";
	file<<"\n Name of the officer was-"<<r.nofo;
	file<<"\n Date of the accident was-"<<r.dat.dd<<"/"<<r.dat.mm<<"/"<<r.dat.yy;
	file<<"\n Crime done-";
	file<<r.crime;
	file<<"\n Your license Number="<<r.license_no;
	file<<"\n Your Vehicle Number-"<<r.vehicle_no;
	file<<"\n The fine charged was-"<<r.fine;
	file.close();
	cout<<"\n returning it!";
	cout<<"\n retruned!";
	cout<<"\n mail="<<mailid;
	 char command[] = "curl smtp://smtp.gmail.com:587 -v --mail-from \"tryonmailtp@gmail.com\" --mail-rcpt \"";
	char part2[]="\" --ssl -u tryonmailtp@gmail.com:adhiksha@123 -T \"mail.txt\" -k --anyauth";
	strcat(command,mailid);
	strcat(command,part2);
	//cin.get();
    WinExec(command, SW_HIDE);
}


int main(){

welcomepage();
cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
cout<<setw(50)<<"\n Please press ENTER to continue";
cin.get();
system("cls");
string user=login();
//system("cls");
	records r;
	char ch1;
	int f;
	node st;
	int tot;
	int choice;
	char ch;
	cout<<"\n                                     Welcome to the portal - "<<user<<endl;
	do{
		
		cout<<"\n ----------------------------------------------------------------------------------------------------------------------";
		cout<<"\n                                                        MENU"<<endl;
		cout<<"\n ----------------------------------------------------------------------------------------------------------------------";
		cout<<"\n                                         1.If we have any new record to insert"<<endl;
		cout<<"\n                                           2. To display all existing records"<<endl;
		cout<<"\n                                 3.If you want to see the status of traffic signals in your area"<<endl;
		cout<<"\n                              4.If you want to increase the number of officers in a particular area in emergency"<<endl;
		cout<<"\n ----------------------------------------------------------------------------------------------------------------------";
		cout<<"\n                                  Please enter you choice =";
		cin>>choice;
		switch(choice){
			case 1:
				system("cls");
				cout<<"\nPLEASE ENTER THE RECORDS DETAILS="<<endl;
				cout<<"\nInsert the license no="<<endl;
				cin>>st.license_no;
				cout<<"\nInsert the date (12 )="<<endl;
				cin>>st.dat.dd>>st.dat.mm>>st.dat.yy;
				cout<<"\nInsert the name of officer="<<endl;
				cin>>st.nofo;
				cout<<"\nInsert the name of the person="<<endl;
				cin>>st.nofp;
				cout<<"\nInsert the vehicle no="<<endl;
				cin>>st.vehicle_no;
				cout<<"\nInput the crime number =\n (please refer below and enter the number)"<<endl;
				cout<<"\n1.License not made\n2.License not available now\n3.Without helmet\n4.No insurance\n5.Mobile talking\n6.Signal jump\n7.No tail light \n8No vehicle papers available\n9.No seat belt\n10.Rash driving"<<endl;
				cout<<"\n Please enter the number="<<endl;
				cin>>st.crime_no;
				r.create(st);
				r.insert(st);
				f=r.calc_fine(st);
				st.fine=f;
				sendmails(st);
			//	system ("cls");
					for(int i=0;i<12;i++)
						cout<<endl;
				cin.get();
				cout<<"\n ----------------------------------------------------------------------------------------------------------------------";
					cout<<"\n                                                        FINE CHARGED ="<<endl;
				cout<<"\n ----------------------------------------------------------------------------------------------------------------------";
				cout<<"\n                                                   ----------Rs."<<f<<"--------";
				cin.get();
				break;
			case 2:
				system("cls");
				int lic;
				cout<<"\n                                  Enter the license number of the person to be found=";
				cin>>lic;
				r.display(lic);
				break;
			case 3:
				cout<<"\n THE TRAFFIC DETAILS ARE:-";
					//traffic_signals(t);
					constforsignals(total);
					tot=read_consts();
					cin.get();
				//	cout<<"\n total="<<tot;
					show_signals(tot);
					cout<<"\n Please press ENTER to continue";
					cin.get();
					system("cls");
					cout<<"\n Do you want to enter the traffic details of your area int the table??";
					cin>>ch1;
					if(ch1=='y')
					{
					traffic t;
					cout<<"\n ENTER THE NAME OF THE AREA="<<endl;
					cin.ignore();
					cin.getline(t.name,200,'\n');
					cout<<"\n Number of signals="<<endl;
                 	cin>>t.number;
  					cout<<"\n No of ooficers="<<endl;
					cin>>t.officers;
					traffic_signals(t);
					constforsignals(total);
					tot=read_consts();
					}
					cout<<"\n 																			THE NEW RECORDS ARE="<<endl;
					cout<<"\n ----------------------------------------------------------------------------------------------------------------------";
					cout<<"\n THE TOTAL NUMBER OF RECORDS IN THE FILE ARE="<<tot;
					show_signals(tot);
					cin.get();
					break;
			case 4:
				char ch3;
			cout<<"\nDo you want to add any extra police officers in a certain area(bandobast)?";
				cin>>ch3;
			if(ch3=='y'){
				tot=read_consts();
				add_signals(tot);
				}
			break;
			default:
				cout<<"\n YOU HAVE ENTERED A WRONG CHOICE!";
				break;
						}
						//system("cls");
						cout<<"\n Do you want to CONTINUE?";
						cin>>ch;
						system("cls");
	}while(ch=='y');

	return 0;

}

