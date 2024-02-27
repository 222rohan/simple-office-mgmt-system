//ADD AGE CHECKING where cond.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct user {
    	char userID[10];
	char name[20];
	int age;
	char registerDate[15];
} newUser;

int fieldCount = 0;

void printAttributes(char *fileName,char attributes[][30]){
    FILE *fp;
    fp = fopen(fileName, "r");
    printf("\n| SL.NO. ");
    for(int i=0;i<fieldCount;i++){
        if(strcmp(attributes[i],"userid")==0){
            printf("| USER ID   ");
        } else if(strcmp(attributes[i],"name")==0){
            printf("| Name                 ");
        } else if(strcmp(attributes[i],"age")==0){
            printf("| Age ");
        } else if(strcmp(attributes[i],"registerdate")==0){
            printf("| Register Date ");
        }
    }
    printf("|\n");

    printf("|--------");
    for(int i=0;i<fieldCount;i++){
        if(strcmp(attributes[i],"userid")==0){
            printf("|-----------");
        } else if(strcmp(attributes[i],"name")==0){
            printf("|----------------------");
        } else if(strcmp(attributes[i],"age")==0){
            printf("|-----");
        } else if(strcmp(attributes[i],"registerdate")==0){
            printf("|---------------");
        }
    }
    printf("|\n");

    int count = 0;
    while(fscanf(fp,"%10[^ -] - %20[^ -] - %d - %s\n", newUser.userID, newUser.name, &newUser.age, newUser.registerDate) != EOF){
        count++;
        printf("| %-6d ",count);
        for(int i=0;i<fieldCount;i++){
            if(strcmp(attributes[i],"userid")==0){
            printf("| %-4s ", newUser.userID);
            } else if(strcmp(attributes[i],"name")==0){
                printf("| %-20s ", newUser.name);
            } else if(strcmp(attributes[i],"registerdate")==0){
                printf("| %-13s ",newUser.registerDate);
            }else if(strcmp(attributes[i],"age")==0){
                printf("| %-3d ",newUser.age);
            }
        }
        printf("|\n");
    }
    if(!count){
        printf(" NO RECORDS EXIST.\n");
    }
}

void printCondition(char *fileName, char *attribute, char *op ,char* value){
    printf("%s",op);
    FILE *fp;
    fp = fopen(fileName, "r");
    int count = 0;
    printf("\n| SL.NO. | USER ID   | Name                 | Age | Register Date |\n");
    printf("|--------|-----------|----------------------|-----|---------------|\n");
    while(fscanf(fp,"%s - %s - %d - %s\n", newUser.userID, newUser.name, &newUser.age, newUser.registerDate) != EOF){
        if(strcmp(attribute, "userid")==0){
            if(strcmp(op, "=")==0){
                if(strcmp(value,newUser.userID)==0){
                    ++count;
                     printf("| %-6d | %-4s | %-20s | %-3d | %-13s |\n", count,newUser.userID, newUser.name, newUser.age, newUser.registerDate);
                }
            }
        } else if(strcmp(attribute, "name")==0){
            if(strcmp(op, "=")==0){
                if(strcmp(value,newUser.name)==0){
                    ++count;
                     printf("| %-6d | %-4s | %-20s | %-3d | %-13s |\n", count,newUser.userID, newUser.name, newUser.age, newUser.registerDate);
                }
            }
        } else if(strcmp(attribute, "registerdate")==0){
            if(strcmp(op, "=")==0){
                if(strcmp(value,newUser.registerDate)==0){
                    ++count;
                     printf("| %-6d | %-4s | %-20s | %-3d | %-13s |\n", count,newUser.userID, newUser.name, newUser.age, newUser.registerDate);
                }
            }
        } else if(strcmp(attribute, "age")==0){
            int compAge = atoi(value);
            if(strcmp(op, "=")==0){
                if(compAge == newUser.age){
                    ++count;
                     printf("| %-6d | %-4s | %-20s | %-3d | %-13s |\n", count,newUser.userID, newUser.name, newUser.age, newUser.registerDate);
                }
            } else if(strcmp(op, "<")==0){
                if(compAge > newUser.age){
                    ++count;
                     printf("| %-6d | %-4s | %-20s | %-3d | %-13s |\n", count,newUser.userID, newUser.name, newUser.age, newUser.registerDate);
                }
            }  else if(strcmp(op, ">")==0){
                if(compAge < newUser.age){
                    ++count;
                     printf("| %-6d | %-4s | %-20s | %-3d | %-13s |\n", count,newUser.userID, newUser.name, newUser.age, newUser.registerDate);
                }
            } else if(strcmp(op, "<=")==0){
                if(compAge >= newUser.age){
                    ++count;
                     printf("| %-6d | %-4s | %-20s | %-3d | %-13s |\n", count,newUser.userID, newUser.name, newUser.age, newUser.registerDate);
                }
            } else if(strcmp(op, ">=")==0){
                if(compAge <= newUser.age){
                    ++count;
                     printf("| %-6d | %-4s | %-20s | %-3d | %-13s |\n", count,newUser.userID, newUser.name, newUser.age, newUser.registerDate);
                }
            }
        }
    }
    if(!count){
            printf(" NO RECORDS EXIST.\n");
        }
}

void printAll(char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "r");
    int count = 0;
    printf("\n| SL.NO. | USER ID   | Name                 | Age | Register Date |\n");
    printf("|--------|-----------|----------------------|-----|---------------|\n");
    while(fscanf(fp,"%s - %s - %d - %s\n", newUser.userID, newUser.name, &newUser.age, newUser.registerDate) != EOF){
        count++;
        printf("| %-6d | %-4s | %-20s | %-3d | %-13s |\n", count,newUser.userID, newUser.name, newUser.age, newUser.registerDate);
    }
    if(!count) {
        printf(" NO RECORDS EXIST.\n");
    }
    fclose(fp);
}
	
void commandCheck(int argc, char argv[][30]) {
    
    if(argc >= 4 && (strcmp(argv[1], "SELECT")==0) && (strcmp(argv[3], "from")==0)) { 
    	char fileName[30];
    	strcpy(fileName, argv[4]);
    	
    	char attributes[5][30];
    	char *token = strtok(argv[2], ",");
    	while(token != NULL){
    		strcpy(attributes[fieldCount], token);
    		token = strtok(NULL, ",");
    		fieldCount++;
    	}  	

        for(int i=0;i<fieldCount;i++){
            if((strcmp(attributes[i],"*")!=0) &&(strcmp(attributes[i],"userid")!=0 && strcmp(attributes[i],"name")!=0 && strcmp(attributes[i],"age")!=0 && strcmp(attributes[i],"registerdate")!=0)){
                printf("\n attribute(s) does not exist\n");
                return;
            }
            
        }
        FILE *fp;
        fp = fopen(fileName, "r");
        if(fp == NULL) {
            printf("\nERROR: table does not exist.\n");
            return;
        }
        fclose(fp);

        if(argc==5 && fieldCount == 1 && (strcmp(attributes[0], "*") == 0)){
            printAll(fileName);

        }  else if(argc == 9 && (strcmp(argv[5], "where") == 0)) {
            
            char attribute[20];
            char op[3];
            char value[30];
            strcpy(attribute, argv[6]);
            strcpy(op, argv[7]);
            strcpy(value, argv[8]);

            printCondition(fileName, attribute, op ,value);
        } else if(argc == 5 && fieldCount >= 1){ 
            
            printAttributes(fileName, attributes);
        }    

        return;
    }

    printf("\nInvalid Usage.\nCorrect Usage: %s <double quotes>SELECT [* <OR> {attributes separated by ,}] from <table_name><double quotes>\n", argv[0]);
}

int main(int argc, char **argv){

    //there are some issues with special characters like *,>,<, etc. 
    //so taking command line args as a single string solves this issue
    	char args[20][30];
        strcpy(args[0],argv[0]);

    	char *token = strtok(argv[1], " ");
        int argsCount = 1;
    	while(token != NULL){
    		strcpy(args[argsCount++], token);
    		token = strtok(NULL, " ");
    	} 

    commandCheck(argsCount, args);	
    return 0;
}