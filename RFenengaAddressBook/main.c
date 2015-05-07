//
//  main.c
//  RFenengaAddressBook
//
//  Created by Russ Fenenga on 12/1/14.
//  Copyright (c) 2014 Piratech. All rights reserved.
//

#include <stdio.h>
#include "adress_book.h"
#include <stdbool.h>
#include <string.h>

void tokenString();
char contactInfo[BUFSIZ];
char itemToFind[255];
char *tokenedString[4];
char lastName[255];
char firstName[255];
char email[255];
char phoneNumber[255];
char filePath[255];
FILE *fp;
char valueToChange[255];

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    char inputChar;
    char buf[BUFSIZ];
    int count = 0;
    int location;       //location to insert always before the number
    bool quit = false;
    printf("Ready\n");
    while(!quit){
        inputChar = getchar();
        getchar();  //consumes extra newline left over by getchar.
        switch (inputChar) {
            case 'a':
                location = atoi(gets(buf));
                gets(contactInfo);
                tokenString();
                InsertPerson(location, lastName, firstName, email, phoneNumber);
                
                break;
            case 'd':
                location = atoi(gets(buf));
                DelPerson(location);
                break;
            case 'n':
                count = getCount();
                printf("%d\n",count);
                break;
            case 'g':
                location = atoi(gets(buf));
                getContactData(location);
                break;
            case 'q':
                quit = true;
                printf("Complete\n");
                break;
            case 'f':
                location = atoi(gets(buf));
                gets(itemToFind);
                getField(location,itemToFind);
                break;
            case 's':
                gets(filePath);
                saveToFile(filePath);
                break;
            case 'l':
                gets(filePath);
                loadFile(filePath);
                break;
            case 'e':
                location = atoi(gets(buf));
                gets(itemToFind);
                gets(valueToChange);
                editContact(location, itemToFind,valueToChange);
                break;
            case '0':
            default:
                break;
        }
        
    }
    return 0;
}

void tokenString(){
    char *  p    = strtok (contactInfo, ",");
    int index = 0, i;
    /* split string and append tokens to 'res' */
    while (p) {
        //tokenedString = realloc (tokenedString, sizeof (char*) * ++numberCommas);
        //if (tokenedString == NULL)
        //    exit (-1); /* memory allocation failed */
        tokenedString[++index - 1] = p;
        p = strtok (NULL, ",");
    }
    
    /* realloc one extra element for the last NULL */
    
    //tokenedString = realloc (tokenedString, sizeof (char*) * (numberCommas+1));
    //tokenedString[numberCommas] = 0;
    strcpy(lastName,tokenedString[0]);
    strcpy(firstName,tokenedString[1]);
    strcpy(email,tokenedString[2]);
    strcpy(phoneNumber,tokenedString[3]);
}