#include <iostream>
#include<iomanip>
#include <string>
#include <cmath>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <fstream>

using namespace std;


int cashier();
int invMenu();
int bookInfo(char isnb [], char title [], char author [], char publisher [], char date [], int qty, double wholesale, double retail);
int reports();
void strUpper(char* input);


// Stub Function Prototype For Inventory Database Function
//void lookUpBook(char isnb [], char title [], char author [], char publisher [], char date [], int qty, double wholesale, double retail);]
void lookUpBook();
void addBook();
void editBook();
void deleteBook();


// Stub functions for Reports function
void repListing();
void repWholesale();
void repRetail();
void repQty();
void repCost();
void repAge();

//setters for the BookData members
void setTitle(string *, int);
void setISBN(string*, int);
void setAuthor(string*, int);
void setPub(string*, int);
void setDateAdded(string*, int);
void setQty(int, int);
void setWholesale(double, int);
void setRetail(double, int);
int isEmpty(int);
void removeBook(char[]);