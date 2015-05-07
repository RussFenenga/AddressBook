//
//  adress_book.c
//  RFenengaAddressBook
//
//  Created by Russ Fenenga on 12/1/14.
//  Copyright (c) 2014 Piratech. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adress_book.h"
Person *pFirst = NULL;
Person *cur = NULL;
int count = 0;
FILE *fp;
char firstLine[BUFSIZ];
char lineInfo[BUFSIZ];
char *tokenedString[4];
char lastName[255];
char firstName[255];
char email[255];
char phoneNumber[255];

int getCount() {
    return count;
}
Person *CreatePerson(char *plastName, char *pfirstName, char *pemail,
                     char *PphoneNumber) {
    Person * pPersonNewPerson = malloc(sizeof(Person));
    if (pPersonNewPerson) {
        strcpy(pPersonNewPerson->lastName, plastName);
        strcpy(pPersonNewPerson->firstName, pfirstName);
        strcpy(pPersonNewPerson->email, pemail);
        strcpy(pPersonNewPerson->phoneNumber, PphoneNumber);
        pPersonNewPerson->pPrev = NULL;
        pPersonNewPerson->pNext = NULL;
    }
    return pPersonNewPerson;
}

Person *InsertPerson(int location, char *plastName, char *pfirstName,
                     char *pemail, char *PphoneNumber) {
    Person *pPersonNew = CreatePerson(plastName, pfirstName, pemail,
                                      PphoneNumber);
    if (pFirst) {           //if this exists then we have something in the list.
        if (location == count) { //we have to be inserting at the end of the list.
            cur = pFirst;
            int i = 0;
            while (++i < location) {          //navigate to last node
                cur = cur->pNext;
            }
            pPersonNew->pNext = NULL;
            pPersonNew->pPrev = cur;
            cur->pNext = pPersonNew;
        } else {
            cur = pFirst;
            if (location != 0) { // inserting in the middle
                int i = 0;
                while (i < location) {             //navigate to location given.
                    cur = cur->pNext;
                    i++;
                }
                cur->pPrev->pNext = pPersonNew;
                pPersonNew->pPrev = cur->pPrev;
                pPersonNew->pNext = cur;
                cur->pPrev = pPersonNew;
            } else { // inserting at the top
                pPersonNew->pNext = cur;
                cur->pPrev = pPersonNew;
                pFirst = pPersonNew;
            }
        }
    } else {              //nothing is in the list so we insert our first item.
        pFirst = pPersonNew;
    }
    count++;
    return pPersonNew;
}
void DelPerson(int location) {
    Person * pPersonDelete = NULL;
    if (pFirst) {
        if (location > count - 1) { //make sure valid location to delete is given
            return;
        } else if (location == 0) {                          //we delete at top.
            pPersonDelete = pFirst;
            if (pPersonDelete->pNext) { //make sure there is a next node in the list
                pFirst = pPersonDelete->pNext;
                pFirst->pPrev = NULL;
                count--;
                free(pPersonDelete);
            } else {  //we are deleting the top with no other nodes in the list.
                pFirst = NULL;
                count--;
                free(pPersonDelete);
            }
        } else {              //we are deleting either at the end or middle now.
            if (location == count - 1) {  //we are deleting the end of the list.
                int i = 0;
                cur = pFirst;
                while (i < location) {
                    cur = cur->pNext;
                    i++;
                }
                pPersonDelete = cur;
                count--;
                free(pPersonDelete);
            } else {      //we are deleting somewhere in the middle of the list.
                int i = 0;
                cur = pFirst;
                while (i < location) {
                    cur = cur->pNext;
                    i++;
                }
                pPersonDelete = cur;
                cur->pPrev->pNext = cur->pNext;
                cur->pNext->pPrev = cur->pPrev;
                count--;
                free(pPersonDelete);
            }
        }
    }
}
void getContactData(int location) {
    if (pFirst) {
        cur = pFirst;
        int i = 0;
        while (i < location) {
            cur = cur->pNext;
            i++;
        }
        printf("%s,%s,%s,%s\n", cur->lastName, cur->firstName, cur->email,
               cur->phoneNumber);
    }
}
void getField(int location, char *itemToFind) {
    if (pFirst) {
        cur = pFirst;
        int i = 0;
        while (i < location) {
            cur = cur->pNext;
            i++;
        }
        int ret = strcmp("lastName", itemToFind);
        int ret2 = strcmp("firstName", itemToFind);
        int ret3 = strcmp("email", itemToFind);
        int ret4 = strcmp("phoneNumber", itemToFind);
        if (ret == 0)
            printf("%s\n", cur->lastName);
        if (ret2 == 0)
            printf("%s\n", cur->firstName);
        if (ret3 == 0)
            printf("%s\n", cur->email);
        if (ret4 == 0)
            printf("%s\n", cur->phoneNumber);
    }
}
void saveToFile(char *filePath) {
    fp = fopen(filePath, "w");
    fprintf(fp,"lastName,firstName,email,phoneNumber\n");
    if (pFirst) {
        cur = pFirst;
        while (cur!=NULL) {
            fprintf(fp, "%s,%s,%s,%s\n", cur->lastName, cur->firstName,
                    cur->email, cur->phoneNumber);
            cur = cur->pNext;
        }
    }
    fclose(fp);
}
void loadFile(char *filePath) {
    Person *contact;
    fp = fopen(filePath, "r");
    fgets(firstLine, BUFSIZ, fp); //get the first line which we don't care about.
    while(fgets(lineInfo, BUFSIZ, fp) != NULL) {
        if(pFirst){
            cur = pFirst;
            //int i = 0;
            //while (i < count) {
            while (cur && (cur->pNext))
                cur = cur->pNext;
            //i++;
            tokenizeString();
            contact = CreatePerson(lastName, firstName, email, phoneNumber);
            cur->pNext = contact;
            contact->pPrev = cur;
            count++;
        } else {
            tokenizeString();
            contact = CreatePerson(lastName, firstName, email, phoneNumber);
            pFirst = contact;
            count++;
        }
    }
}
void tokenizeString() {
    char * p = strtok(lineInfo, ",");
    int index = 0, phoneLen;
    while (p) {
        tokenedString[++index - 1] = p;
        p = strtok(NULL, ",");
    }
    strcpy(lastName, tokenedString[0]);
    strcpy(firstName, tokenedString[1]);
    strcpy(email, tokenedString[2]);
    if ((phoneLen = strlen(tokenedString[3])) >= 2)
        tokenedString[3][phoneLen - 1] = '\0';
    strcpy(phoneNumber, tokenedString[3]);
}
void editContact(int location, char *itemToFind, char *valueToChange){
    if (pFirst) {
        cur = pFirst;
        int i = 0;
        while (i < location) {
            cur = cur->pNext;
            i++;
        }
        int ret = strcmp("lastName", itemToFind);
        int ret2 = strcmp("firstName", itemToFind);
        int ret3 = strcmp("email", itemToFind);
        int ret4 = strcmp("phoneNumber", itemToFind);
        if (ret == 0)
            strcpy(cur->lastName,valueToChange);
        if (ret2 == 0)
            strcpy(cur->firstName,valueToChange);
        if (ret3 == 0)
            strcpy(cur->email,valueToChange);
        if (ret4 == 0)
            strcpy(cur->phoneNumber,valueToChange);
    }
}






