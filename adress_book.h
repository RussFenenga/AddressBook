//
//  adress_book.h
//  RFenengaAddressBook
//
//  Created by Russ Fenenga on 12/1/14.
//  Copyright (c) 2014 Piratech. All rights reserved.
//

#ifndef RFenengaAddressBook_adress_book_h
#define RFenengaAddressBook_adress_book_h
typedef struct person Person;
struct person {
    char lastName[255];
    char firstName[255];
    char email[255];
    char phoneNumber[255];
    Person *pPrev;
    Person *pNext;
    
};

Person *CreatePerson(char *lasName, char *firstName, char *email, char *phoneNumber);
Person *FindPerson(Person *pPerson, char *name);
Person *InsertPerson(int location, char *lasName, char *firstName, char *email, char *phoneNumber);
void DelPerson(int location);
int getCount();
void getContactData(int location);
void getField(int location, char *itemToFind);
void saveToFile(char *filePath);
void loadFile(char *filePath);
void editContact(int location, char *itemToFind, char *valueToChange);
void tokenizeString();

extern Person *pFirst;
extern Person *cur;
#endif