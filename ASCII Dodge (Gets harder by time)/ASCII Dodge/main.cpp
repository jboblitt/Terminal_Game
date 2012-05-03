#include "ASCII Dodge.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int main()
{

	//creating a variable to track keystorkes 
	unsigned int key; 

	//This variable hodlds the frequency time for the rain 
	int rain_f; 

	//this is the frequency max vlaue (gets smaller by time)
	int f_max=20; 

	//holds 1 for player 1 and 2 for player 2
	int looser=0; 
	//detects collision 
	bool colide=0; 

	//this variable holds the opsition of the 'X' charachter 
	// that is located at the 24th row 
	int player1_position=40; 
	//this variable is the row number the charachter is going to appear at 
	int player1_row=15; 
	/* initialize random seed: */
  srand ( time(NULL) );

	/*for (int j=0; j<25; j++)
	for(int i=0; i<80;i++)
	cout<<"0"; */
	//creating rows 
	int* rows[25];
	//initializing rows to point at 25 different int arrays made of 80 elements 
	for (int j=0; j<25; j++)
	{
		rows[j]= new int[80];
	}
	//intiializing the individual arrays 
	for (int j=0; j<25; j++)
	{
		for (int i=0; i<80; i++)
		{
			if(i==0 || i==79)
		(rows[j])[i]=1;
			else (rows[j])[i]=0;
			
		}
	}

	//creating player1 
	(rows[player1_row])[player1_position]=2; 

	//printing the lines 
	for (int j=0; j<25; j++) print_line( rows[j] ); 


	//Just for debugging 
	{
		//creating new objects for the 0th line (top one)
	for(int i=1; i<79;i++)
		(rows[0])[i]=rand() % 2; 

	system("cls"); 
	//printing the lines 
	for (int j=0; j<25; j++) print_line( rows[j] ); 


	//resetting x
	
	}


	//setting the frequency value for the first time 
	rain_f=rand() % f_max; 


	int x=0; 
	while(1)
	{
		//keyboard stuff
		//___________________________________
		//sampling keystorke 
		if(kbhit())  key = getch(); 
		else key=NULL; 
		if(key=='a' && player1_position!=0)
		{
			(rows[player1_row])[player1_position]=0;//erasing cursor 
			player1_position-- ;			//repositioning 
			(rows[player1_row])[player1_position]=2;//recreating
		}
		if(key=='d' && player1_position!=79)
		{
			(rows[player1_row])[player1_position]=0;//erasing cursor 
			player1_position++ ;			//repositioning 
			(rows[player1_row])[player1_position]=2;//recreating
		}
		if(key=='w' && player1_row!=0)
		{
			player1_row--; 
		}
		if(key=='s' && player1_row!=24)
		{
			player1_row++; 
		}

		//End of keyboard stuff
		//______________________________________________
		x++; 

		if(x==rain_f )
	{
		//creating new objects for the 0th line (top one)
	for(int i=1; i<79;i++)
		(rows[0])[i]=rand() % 2; 

	system("cls"); 
	//printing the lines 
	for (int j=0; j<25; j++) print_line( rows[j] ); 


	//resetting x
	x=0; 
	//making the game harder by time 
	if(f_max>3) f_max--; 
	//resetting rain frequency value to a new one 
	rain_f=(rand() % f_max) +1; 
	}

//shifting lines from bottom to top 
		for (int j=24; j>0; j--)
			for(int i=1; i<79;i++) 
			{	
				//checking for collision 
				if((rows[j])[i]==2 && (rows[j-1])[i]==1)
				{
					looser=1; 
					colide =1; 
				}

				//clearing the tail 
				

				//copying 
					if((rows[j-1])[i]!=2)(rows[j])[i]=(rows[j-1])[i]; 
					else (rows[j])[i]=0; 
					
			}
		
	//clearing the top line 
		for(int i=1; i<79;i++) (rows[0])[i]=0; 

	//repositioning the cursor 
	(rows[player1_row])[player1_position]=2;//recreating

	system("cls"); 
	//printing the lines 
	for (int j=0; j<25; j++) 
		print_line( rows[j] ); 

	

	
	if(colide) break;
	}

	if(looser==1)
	{
		system("cls"); 
		cout<<"player 1 looses "<<endl; 
	}


	return 0; 
}
