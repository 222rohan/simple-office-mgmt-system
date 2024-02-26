//CS22B1060 ROHAN RADHESH SHENOY

//a office management database system done using file handling
//has features to add, update, delete, list records and transactions of users.
//has txt files to 1. store user records 2. user transactions
//has a formatted txt file with full user, userid list.

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//user record attributes' declarations for user and transaction.

struct user {
	char registerDate[15];
	char userID[10];
	char name[20];
	char dob[15];
	int age;
	char address[25];
	char contact[15];
	char position[30];
	float salary;
} newUser;

struct transactions {
	char userID[10];
	char name[20];
	char date[15];
	char project[30];
	float hours;
} newT;

long int size = sizeof(newUser);
long int transactionSize = sizeof(newT);

//function declaration.

void mainMenu();	
void registration();	
void updateUser();	
void transactions();
void userDetails(); 
void removeUser(); 
void viewDirectory(); 
struct user searchUser();

//main

int main(){
	FILE *fp;		//just to create and check if main file used opens.
	fp = fopen("officedata.txt", "ab+");
	if(fp == NULL){
		printf("ERROR: file could not be opened.");
		exit(0);
	}
	fclose(fp);

	mainMenu();
	return 0;
}

//menu for the prog

void mainMenu() {
	int num;
	
	while(1){
		printf("\n\nMAIN MENU\n");
		printf("1. User Registration\n");
		printf("2. Update User Information\n");
		printf("3. Work Transaction\n");
		printf("4. User Details\n");
		printf("5. Remove User\n");
		printf("6. View Office Portal Directory\n");
		printf("7. Exit\n");
		printf("\nEnter your choice: ");
		scanf("%d", &num);
		
		switch(num) {
			case 1:
				registration();
				break;
			case 2:
				updateUser();
				break;
			case 3:
				transactions();
				break;
			case 4:
				userDetails();
				break;
			case 5:
				removeUser();
				break;
			case 6:
				viewDirectory();
				break;
			case 7:
				printf("Exiting program..\n");
				return;
				break;
			default:
				printf("\ninvalid input\n");				
				break;
		}
	}
}

//adds a new user record to officedata.txt and formatted version to formattedData.txt

void registration(){
	FILE *fp;
	FILE *ff;
	fp = fopen("officedata.txt", "rb+");
	ff = fopen("formattedData.txt", "a+");

	if(fp == NULL || ff == NULL) {		//checks for errors in file creation.
		printf("ERROR: file could not be opened.\n");
		exit(0);
		}
	
	printf("\nAdd a new user\n");
	char newUserID[10];
	
	printf("\nEnter user ID: ");
	scanf("%s",newUserID);
	
rewind(fp);	//sets cursor to start
while(fread(&newUser, size, 1, fp) == 1){		//checking if user already exists, then returns if true
	if(strcmp(newUser.userID, newUserID) == 0){
		printf("\nUser ID already exists.");
		fclose(ff);
		fclose(fp);
		return;
	}
}
	strcpy(newUser.userID, newUserID);		//otherwise assigns user id to new user struct variable(acts as buffer). (and other details)
	printf("\nEnter the details,\n");
	printf("\nRegistration Date(dd/mm/yyyy):");
    scanf("%s",newUser.registerDate);
	printf("\nName:");
    scanf("%s",newUser.name);
	printf("\nDate of Birth(dd/mm/yyyy):");
    scanf("%s",newUser.dob);
	printf("\nAge:");
    scanf("%d",&newUser.age);
	printf("\nAddress:");
    scanf("%s",newUser.address);
    printf("\nContact:");
    scanf("%s",newUser.contact);
	printf("\nPosition:");
    scanf("%s",newUser.position);
	printf("\nSalary:");
    scanf("%f",&newUser.salary);

	fseek(fp,0,SEEK_END);		// sets cursor to the end
	fwrite(&newUser,size,1,fp);		//uses newUser struct user variable as buffer and writes the contents in the txt file

	fprintf(ff,"%s - %s - %d - %s\n", newUser.userID, newUser.name, newUser.age, newUser.registerDate);	//formatted version adding id,name
	fclose(ff);
	
	printf("\nNew User successfully created.");
	fclose(fp);
}

void updateUser(){		//changes contact or sports pref if user id exists.
	FILE *fp;
	fp = fopen("officedata.txt", "rb+");
	rewind(fp);

	char searchUserID[20];
	printf("\nUpdate User Information\n");
	printf("\nEnter User ID: ");
	scanf("%s", searchUserID);

	while(fread(&newUser, size, 1, fp) == 1){		//uses newUser variable as buffer and reads the sportsdata file
		if(strcmp(newUser.userID, searchUserID) == 0){		//if  search by id matches, update choices are displayed
			printf("\nUser found!\n1. Change contact number\n2. Change position\n3. Change Salary");
			printf("\nEnter your choice: ");
			int choice = 0;
			scanf("%d", &choice);
			if(choice == 1) {
				printf("\nEnter new contact information: ");
				scanf("%s", newUser.contact);
			} else if (choice == 2) {
				printf("\nEnter new position: ");
				scanf("%s", newUser.position);
			} else if (choice == 3) {
				printf("\nEnter new salary: ");
				scanf("%f", &newUser.salary);
			} else { 
				printf("\nInvalid input");
				fclose(fp);
				return;
			}
			fseek(fp, -size, SEEK_CUR);		//moves the cursor behind by one structure's size to move cursor to the required searched user
			fwrite(&newUser, size , 1, fp);		//rewrite data on the same structure data using newUser as buffer
			printf("Updated Information Successfully");
			fclose(fp);	//closing the file
			return;
		}	
	}
	printf("User not found.");	//if not found, directly print user not found
	fclose(fp);
	return;
}

//fetch user details by using userID or user name

void userDetails(){
	FILE *fp;
	fp = fopen("officedata.txt","rb");
	if(fp == NULL){
		printf("ERROR: cannot open file (terminating program)");

		exit(0);
	}

	printf("\nSearch User details by,\n 1. Username\n 2. User ID\n Enter your choice: ");
	int choice = 0;
	char searchString[20];
	scanf("%d", &choice);
	if(choice == 1){
		printf("Enter username: ");
		scanf("%s", searchString);
		while(fread(&newUser,size,1,fp) == 1){		//using newUser as buffer to search for searchstring  matching with user name 
			if(strcmp(searchString,newUser.name) == 0){
				fseek(fp, -size, SEEK_CUR);		//if matches, we move cursor by 1 user structure size
				printf("\nFor username %s,", newUser.name);	//printing all details
				printf(" User ID: %s\nDate Registered: %s\nDate of Birth: %s\nAge: %d\nAddress: %s\nContact No.: %s\nPosition: %s", newUser.userID, newUser.registerDate, newUser.dob, newUser.age, newUser.address, newUser.contact, newUser.position);
				fclose(fp);
				return;
			}
		}
		printf("\nusername does not exist.");
	} else if (choice == 2) {		//similarly for userID
		printf("Enter user ID: ");
		scanf("%s",searchString);
		while(fread(&newUser,size,1,fp) == 1){
			if(strcmp(searchString,newUser.userID) == 0){
				fseek(fp, -size, SEEK_CUR);
				printf("\nFor user ID %s,", newUser.userID);
				printf(" Username: %s\nDate Registered: %s\nDate of Birth: %s\nAge: %d\nAddress: %s\nContact No.: %s\nPosition: %s", newUser.name, newUser.registerDate, newUser.dob, newUser.age, newUser.address, newUser.contact, newUser.position);
				fclose(fp);
				return;
			}
		}
		printf("\nUser ID does not exist.");
	} else {
		printf("invalid input.");
		fclose(fp);
		return;
	}
	fclose(fp);

}

//removing user from the sports data file.
//we make use of 2 files - an original and an updated	

void removeUser(){
	FILE *fOriginal, *fRemoved;
	FILE *ff;
	ff = fopen("formattedData.txt", "w");
	fOriginal = fopen("officedata.txt", "rb");
	fRemoved = fopen("userRemoved.txt", "wb");	//file which will contain updated content
	if(fOriginal == NULL || fRemoved == NULL){
		printf("ERROR: cannot open file (terminating program)");
		exit(0);
	}

	char searchID[20];
	printf("\nEnter the User ID to be deleted: ");		//search id input
	scanf("%s", searchID);

	int flag = 0;

	while(fread(&newUser, size, 1 ,fOriginal)==1){
		if(strcmp(newUser.userID, searchID) != 0) {		//if search string doesnt match with the buffer (newUser),
			fwrite(&newUser,size,1,fRemoved);			//we add it to the file (both sportsdata and formatted)
			fprintf(ff,"%s - %s - %d - %s\n", newUser.userID, newUser.name, newUser.age, newUser.registerDate);
		} else {
			flag = 1;		//if search string matches with the userid, then we set flag 1 indicating user was found
		}
	}
	fclose(fOriginal);
	fclose(fRemoved);
	fclose(ff);
	remove("officedata.txt");
	rename("userRemoved.txt", "officedata.txt");

	if(flag){
		printf("\nUser successfully removed.");	//flag 1 - user was found and deleted from the database
	} else {
		printf("\nUser ID does not exist.");
	}
}

//prints all users in the database along with some of their personal information

void viewDirectory(){
	FILE *fp;
	fp = fopen("officedata.txt", "rb");

	fseek(fp, 0, SEEK_END); // goto end of file
	if (ftell(fp) == 0)	//ftell gives current value, we check if current value is zero which implies no data is added onto thr file
	{
		printf("No records exist.");
		fclose(fp);
		return;
		//file empty
	}
	
	fseek(fp, 0, SEEK_SET); //fseek sets the cursor to the desired postion, here seek_set means start position
	
	int count = 0;
	float sumSalary = 0;
	printf("\nSL. NO, USER ID, USERNAME, AGE, POSITIONS\n\n");
	while(fread(&newUser,size,1,fp) == 1){	//printing all users' info while file has content
		count++;	//tracks amount of users printed
		sumSalary = sumSalary + newUser.salary;
		printf("%d. \t%s\t %s\t %d\t %s",count,newUser.userID, newUser.name, newUser.age, newUser.position);
		printf("\n");
	}
	printf("\n(%d user(s) found.)",count);
	if(count){
		printf("\nAverage Salary: %f", sumSalary/count);
	}
		
	fclose(fp);
}

//a linear search function to find a specified user
//we use the formatted file as it contains lesser data => its faster

struct user searchUser() {
		//return type user variable
	FILE *ff;
	ff = fopen("formattedData.txt", "r");
	if(ff == NULL){
		printf("\nERROR opening file(does not exist)");
	}
	
	struct user foundUser;
	strcpy(foundUser.userID, "-1"); // assigning -1 to userID means user does not exist 

	char searchID[20];
	printf("\nEnter the user ID: ");	
	scanf("%s", searchID);

	while(fscanf(ff,"%s - %s - %d - %s\n", newUser.userID, newUser.name, &newUser.age, newUser.registerDate) != EOF){		//search the formatted file until EOF - end of file
		if(strcmp(searchID, newUser.userID) == 0){	//check if search string matches userid
			foundUser = newUser;	//copy buffer user (who is found) to foundUser
		}
	}
	
	fclose(ff);
	return foundUser;	//return the user
}

//function to find add,display transaction history of a user

void transactions(){
	struct user foundUser = searchUser();		//we call search user to search a user and store it
	if(strcmp(foundUser.userID,"-1") == 0){		//-1 means user id doesnt exist
		printf("\n user not found.");
		return;
	}
	
	int choice = 0;
	printf("\n1. Add transaction\n2. Display Transaction history\nEnter your choice: ");
	scanf("%d",&choice);
	if(choice == 1){	//add transaction
		FILE *ft = fopen("officeTransactions.txt", "ab+");	//a separate file to track transaction

		printf("Enter the project: ");
		scanf("%s", newT.project);
		printf("Enter the date: ");
		scanf("%s", newT.date);
		printf("Enter the work hours: ");
		scanf("%f", &newT.hours);

		strcpy(newT.name, foundUser.name);	//copying user data to transaction structure variable
		strcpy(newT.userID, foundUser.userID);

		fwrite(&newT, transactionSize, 1, ft);	//write on the transaction file 

		fclose(ft);
		printf("\nSuccessfully added new transaction!");
		return;
		
	} else if(choice == 2){ 	//display
		FILE *ft = fopen("officeTransactions.txt", "rb");
		printf("\nDisplaying %s's transaction history ", foundUser.name);
		printf("(User ID: %s),", foundUser.userID);

		if(ft == NULL){
			printf("\nNo transactions exist.");		//if a file is not created, no transactions exist
		}
		int eventsCount = 0;
		float hoursCount = 0;	//tracks no. of events a user has taken part in
		while(fread(&newT, transactionSize, 1, ft) == 1 ){	//searching transaction file
			if((strcmp(newT.userID, foundUser.userID) == 0) && (strcmp(newT.name, foundUser.name)==0) ){	//check if given user matches with transaction file user
				eventsCount++;
				hoursCount += newT.hours;
				printf("\n%d.",eventsCount);
				fseek(ft,-transactionSize,SEEK_CUR);	//printing
				printf("\nProject: %s\nDate of work: %s\nHours worked: %f\n", newT.project, newT.date, newT.hours);
				fseek(ft,transactionSize,SEEK_CUR);	//moving cursor to go to the next transaction variable stored
				if(feof(ft)){	//break if end of file is reached
					break;
				}
			}
		}
		if(eventsCount) {
			printf("(%f total hour(s) worked.)", hoursCount);
		} else {
			printf("\nthis user has not worked yet.");
		}

		fclose(ft);
		return;
	} else {
		printf("\nInvalid choice.");
	}
}