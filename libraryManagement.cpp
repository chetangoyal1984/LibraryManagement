#include <iostream>
#include <set>
#include <stdlib.h>
#include <string.h>
#define NAMESIZE 50
#define MAXBOOKS 5
using namespace std;

class book {
 char name[NAMESIZE];
 char author[NAMESIZE];
 char currUser[NAMESIZE];
 bool avaiable;
 public:
 book(char pname[]) {
     //name = pname;
     strncpy(name, pname, strlen(pname));
     //cout<<"final book name"<<name<<endl;
     author[0] = 0;
     avaiable = 1;
     currUser[0] = 0;
 }
 
 book(char pname[], char pauthor[]) {
     strncpy(name, pname, strlen(pname));
     avaiable = 1;
     currUser[0] = 0;
 }
 
 char* getName() {
     return name;
 }
 
 bool getAvailability() {
     return avaiable;
 }
 
 void setAvailability(bool avail) {
     avaiable = avail;
 }
 
 void setCurrUser(char user[]) {
     strncpy(currUser, user, strlen(user));
     avaiable = false;
 }
 
 char* getCurrUser() {
     return currUser;
 }
   
};

class user {
 char name[NAMESIZE];
 int totalBooks;
 int maxBooks;
 
 public:
 user(char pname[]) {
     strncpy(name, pname, strlen(pname));
     totalBooks = 0;
     maxBooks = MAXBOOKS;
 }
 
 char* getName() {
     return name;
 }
 
 void issueNewBook() {
     totalBooks++;
 }
 
 void returnBook() {
     totalBooks--;
 }
 
 bool isAllowed() {
    return (totalBooks<maxBooks?1:0);    
 }
 
 void setLimit(int limit) {
     maxBooks = limit;
 }
 
};


class BookStore {
static int count;
set<book*> *books;
set<user*> *users; 

public:
BookStore() {
	books = new set<book*>;
	users = new set<user*>;
}

void addBook(char bookName[]) {
    //cout<<"adding new book:"<<bookName<<endl;
    book* newbook = new book(bookName);    
    books->insert(newbook);
}

void addUser(char userName[]) {
    user* newUser = new user(userName);    
    users->insert(newUser);
}
void lendBooks(char bookName[], char userName[]);
void returnBook(char bookName[]);
void createLimit(char userName[], int totalBooks);
void searchBook(char bookName[]);
void searchUser(char userName[]);
};

void BookStore::searchUser(char userName[]) {
    set<user*>::iterator it1;
    for (it1=users->begin(); it1!=users->end(); ++it1) {
         if(strcmp((*it1)->getName(),userName) == 0) {
             cout<<"user has been found"<<endl;
             return;
         }
    }
    cout<<"No User has been found with name:" <<userName;
}
void BookStore::searchBook(char bookName[]) {
    set<book*>::iterator it;
    for (it=books->begin(); it!=books->end(); ++it) {
        if(strcmp((*it)->getName(),bookName) == 0) {
            cout<<"book has been found in the library"<<endl;
            return;
        }
    }
    cout<<"No book has been found with name:" <<bookName;
}

void BookStore::createLimit(char userName[], int totalBooks) {
    set<user*>::iterator it1;
    for (it1=users->begin(); it1!=users->end(); ++it1) {
         if(strcmp((*it1)->getName(),userName) == 0) {
             (*it1)->setLimit(totalBooks);
             break;
         }
    }
}

void BookStore::lendBooks(char bookName[], char userName[]) {
    set<user*>::iterator it1;
    for (it1=users->begin(); it1!=users->end(); ++it1) {
         if(strcmp((*it1)->getName(),userName) == 0) {
             if((*it1)->isAllowed()) {
                 break;
             } else {
                 cout<<"No more books can be issued to this user"<<endl;
                 return;
             }
         }
    }
    if(it1 == users->end()) {
        cout<<"user name is not valid"<<endl;
        return;
    }
    
    set<book*>::iterator it;
    for (it=books->begin(); it!=books->end(); ++it) {
        if(strcmp((*it)->getName(),bookName) == 0) {
            if((*it)->getAvailability()) {
                (*it)->setCurrUser(userName);
                (*it1)->issueNewBook();
                return;
            } else {
                cout<<"This book has been already issued"<<endl;
            }
        }
    }
    cout<<"This book name is not valid"<<endl;
  
}

void BookStore::returnBook(char bookName[]) {
    char userName[NAMESIZE];
    set<book*>::iterator it;
    for (it=books->begin(); it!=books->end(); ++it) {
        if(strcmp((*it)->getName(),bookName) == 0) {
            if((*it)->getAvailability()) {
                cout<<"This book is not issued to anyone"<<endl;
                return;
            }
            strncpy(userName,(*it)->getCurrUser(), strlen((*it)->getCurrUser()));
            (*it)->setAvailability(true);
            break;
        }
    }
    
    if(it == books->end()) {
        cout<<"book name is not valid"<<endl;
        return;
    }
    
    set<user*>::iterator it1;
    for (it1=users->begin(); it1!=users->end(); ++it1) {
         if(strcmp((*it1)->getName(),userName) == 0) {
            (*it1)->returnBook();
         }
    }
}

int main() {
    BookStore bookstore;
    char choice;
    char bookName[NAMESIZE];
    char userName[NAMESIZE];
    int totalBooks;
    cout<<"please choose 1 of the following options:"<<endl;
        cout<< "1. add books to the lib."<<endl;
        cout<< "2. add users to the lib."<<endl;
        cout<< "3. lend books to users."<<endl;
        cout<< "4. Ability to return books to the library."<<endl;
        cout<< "5. limit the number of books borrowed by user" <<endl;
        cout<< "6. search book with title" <<endl;
        cout<< "7. search user with name" <<endl;
        cout<< "9. End"<<endl;
    while(1) {
        
        cin>>choice;
        switch(choice) {
            cout<<"choice is: "<<choice<<endl;
            case '1' :
            //add new book
                cin>>bookName;
                bookstore.addBook(bookName);
                break;
            case '2' :
            //add new user
                 cin>>userName;
                 bookstore.addUser(userName);
                 break;
            case '3' :
            //lend a book
                 cin>>bookName;
                 cin>>userName;
                 bookstore.lendBooks(bookName,userName);
                 break;
            case '4' :
            //return the book
                cin>>bookName;
                bookstore.returnBook(bookName);
                break;
            case '5' :
            //limit of max book for a particular user
                cin>>userName;
                cin>>totalBooks;
                bookstore.createLimit(userName, totalBooks);
                break;
            case '6' :
            //search book with given name
                cin>>bookName;
                bookstore.searchBook(bookName);
                break;
            case '7' :
            //search user with given name
                cin >> userName;
                bookstore.searchUser(userName);
                break;
            case '9' :
                break;
        }
        if(choice =='9') {
            break;
        }
    }
}

