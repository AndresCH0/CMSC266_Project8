#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>
#include "mainmenu.h"


//using namespace std;

// Function Prototypes
// int cashier();
// int invMenu();
// int bookInfo();
// int reports();

// Struct to create new books
struct BookData{
    // C-Strings to store the book titles, isbn, authour
    // publisher, date
    char bookTitle[51];
    char isbn[14];
    char author[31];
    char publisher[31];
    char dateAdded[11];

    // Numeric arrays to hold qty, whole and retail value
    int qtyOnHand[20];
    double wholesale[20];
    double retail[20];
};


// Define Global BookData array to hold 20 BookData Struct variables
// BookData bookData [20];


// Define global fstream object to handel file operations
// Using input, output, and binary flag mode

// Function to test file bits
void testBits(fstream &test){
    cout << endl << "eof(): " << test.eof() << endl;
    cout << "good(): " << test.good() << endl;
    cout << "bad(): " << test.bad() << endl;
    cout << "fail(): " << test.fail() << endl << endl;
}

int main() {



    // Used to hold the user menu input
    int userSelection = 0;

    // Loop will continue until userSelection is 4
    // the loop will be used to display the main menu selections

   while(userSelection != 4){
    // Main Menu display
        cout << endl;
        cout << setw(36) << "\nSerendipity Booksellers\n";
        cout << setw(29) << "Main Menu\n\n";
        cout << setw(28) << "Cashier Module\n";
        cout << setw(39) << "Inventory Database Module\n";
        cout << setw(27) << "Report Module\n";
        cout << setw(19) << "Exit\n\n";

        cout << setw(30) << "Enter Your Choice: ";
        cin >> userSelection;
        cout << endl << endl;

        /*if(userSelection > 4 || userSelection < 1){
            cout << setw(55) << "Please enter a number in the range 1 - 4\n\n";
        }*/
       
        while(userSelection > 4 || userSelection < 1){
            cout << setw(52) << "Please enter a number in the range 1 - 4\n\n";
            break;
        }

        switch(userSelection){
            case 1:{
                // cout << setw(36) << "You have selected item 1\n";
                cashier();
                break;
            }
            case 2:{
                // cout << setw(36) << "You have selected item 2\n";
                invMenu();
                break;
            }
            case 3:{
                // cout << setw(36) << "You have selected item 3\n";
                reports();
                break;
            }
            case 4:{
                //cout << setw(36) << "You have selected item 4\n";
                exit(0);
                //break;
            }
        }
    }
    return 0;
}



// Stub Functions to Test Invertory Database 
void lookUpBook(){
    // File object
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    
    //Empty book object to read into 
    BookData holderData = {};

    // fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    // fileHandler.clear();
    //testBits(fileHandler); Debuh: check file error flags
    char search [51];
    int index = 0;
    cout << "You selected Look Up Book.\n";
    cout << "Enter the book's title: ";
    cin.ignore(1,'\n');
    cin.getline(search, 51);
    
    while (fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData))){

        // convert user input to all caps
        strUpper(search);
        
        // compare title entered by user to the current title read into holderData
        if(strstr(holderData.bookTitle, search)){
            // Display match
            bookInfo(holderData.isbn, holderData.bookTitle, 
                    holderData.author, holderData.publisher,
                    holderData.dateAdded, *holderData.qtyOnHand,
                    *holderData.wholesale, *holderData.retail);
            fileHandler.close();
            return;
        }
        else index++;
    }
    cout << "No match was found.\n";
    fileHandler.close();
    return;
}

void addBook(){
    // Flag to cause confirm a book was added to the file
    bool bookAdded = false;

    // Variable to hold the posistion of the empty read position
    long filePointerPosition;

    // BookData object used to hold the read values from the file
    BookData holderData = {};

    // fstream object 
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    
    // Test fileHandler bits
    // testBits(fileHandler);

    // check if the file opened correctly
    // if file doesn't exist then create it
    if(fileHandler.fail()){
        cout << "error could not open file";
        fileHandler.open("inventory.dat", ios::out);
        fileHandler.close();
        return;
    }
    
    // read the first chunk of memory associated with
    // a BookData object
    // fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData));

    // Indicate user selection
    cout << "You selected Add Book.\n";


    do{
        //fileHandler.clear();
        
        
        //fileHandler.clear();
        filePointerPosition = fileHandler.tellg();

        // Test fileHandler bits
        // testBits(fileHandler);

        // Debugger to check where the read and write pointers are at
        cout << endl << fileHandler.tellg() << endl;
        cout << fileHandler.tellp() << endl;
        fileHandler.clear();

        // Find the next empty section to write to
        if (holderData.bookTitle[0] == '\0'){
            cout << "Book Title: ";
            cin.ignore(1, '\n');
            cin.getline(holderData.bookTitle,51);
            strUpper(holderData.bookTitle);
            cout << "ISBN Number: ";
            cin.getline(holderData.isbn,14);
            strUpper(holderData.isbn);
            cout << "Author's Name: ";
            cin.getline(holderData.author,31);
            strUpper(holderData.author);
            cout << "Publisher's Name: ";
            cin.getline(holderData.publisher,31);
            strUpper(holderData.publisher);
            cout << "The date the book was added to the inventory: ";
            cin.getline(holderData.dateAdded, 11);
            cout << "The quantity of the book being added: ";
            cin >> *holderData.qtyOnHand;
            cout << "The wholesale price of the book: ";
            cin >> *holderData.wholesale;
            cout << "The retail price of the book: ";
            cin >> *holderData.retail;
            fileHandler.seekp(filePointerPosition, ios::beg);
            
            // Test fileHandler bits
            // testBits(fileHandler);

            //Debug: check the read and write position of the file
            // cout << "Read Position (.tellg()) " << fileHandler.tellg() << endl;
            // cout << "Write Position (.tellp()) " << fileHandler.tellp() << endl;
            fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));

            // testBits(fileHandler);
            fileHandler.flush();
            bookAdded = true;
            break;
        }
    }while (fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData)));
    if(!bookAdded){
        cout << "There is no more space to add this book\n";
    }
    fileHandler.clear();
    fileHandler.close();
    // Test fileHandler bits
    // testBits(fileHandler);
    cout << endl;
    return;
}

void editBook(){
    // Variables need for element indexing 
    // and string used in the array search
    char search [51];
    int index = 0;
    int editChoice = 0;

    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    long currentPointerPosition = fileHandler.tellg();
    BookData holderData = {};

    // Promt user to input the books title
    cout << "You have selected Edit Book.\n";
    cout << "Enter Book's Title: ";
    cin.ignore(1, '\n');
    cin.getline(search, 51);
    strUpper(search);
    
    // Step through array to find a match to user input
    do{
        fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData));
        //testBits(fileHandler); Debug tool
        if(strstr(holderData.bookTitle, search)){
            
            // display the matching books information
            bookInfo(holderData.isbn, holderData.bookTitle, 
                    holderData.author, holderData.publisher, 
                    holderData.dateAdded, *holderData.qtyOnHand, 
                    *holderData.wholesale, *holderData.retail);

            // find current pointer position of match
            currentPointerPosition = fileHandler.tellg();

            // subtract the size of BookData to move back to the begining of the match
            currentPointerPosition -= sizeof(BookData);
            break;
        }
        else{
            
            //fileHandler.close();
            cout << "No Match Was Found, Reenter Title: ";
            
            cin.getline(search, 51);
            fileHandler.clear();
            fileHandler.seekg(0, ios::beg);
        }
        
    }while(!fileHandler.eof());
    fileHandler.clear();
    // Promt user for which book attribute they would like to edit
    while(!(editChoice == -1)){
        fileHandler.clear();
        cout << "What attribute would you like to edit (1-7) "
            << "\nEnter -1 to end editing: ";
        cin >> editChoice;
        // Allow users to edit specified object member values 

        // Edit ISBN Member
        if (editChoice == 1){
            cout << "Enter new ISBN: ";
            cin.ignore(1,'\n');
            cin.getline(holderData.isbn, 14);
            fileHandler.clear();
            fileHandler.seekp(currentPointerPosition, ios::beg);
            fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
            
            // testBits(fileHandler);
        }

        // Edit Title
        else if (editChoice == 2){
            cout << "Enter new Title: ";
            cin.ignore(1,'\n');
            cin.getline(holderData.bookTitle, 51);
            fileHandler.clear();
            fileHandler.seekp(currentPointerPosition, ios::beg);
            fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
            fileHandler.close();
            // testBits(fileHandler);
        }

        // Edit 
        else if (editChoice == 3){
            cout << "Enter new Author: ";
            cin.ignore(1,'\n');
            cin.getline(holderData.author, 31);
            fileHandler.clear();
            fileHandler.seekp(currentPointerPosition, ios::beg);
            fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
            ;
            // testBits(fileHandler);
        }

        else if (editChoice == 4){
            cout << "Enter new Publisher: ";
            cin.ignore(1,'\n');
            cin.getline(holderData.publisher, 31);
            fileHandler.clear();
            fileHandler.seekp(currentPointerPosition, ios::beg);
            fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
            ;
            // testBits(fileHandler);
        }
        else if (editChoice == 5){
            cout << "Enter new Quantity: ";
            cin >> *holderData.qtyOnHand;
            fileHandler.seekp(currentPointerPosition, ios::beg);
            // testBits(fileHandler);
            fileHandler.clear();
            fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
            // testBits(fileHandler);
        }
        else if (editChoice == 6){
            cout << "Enter new Wholesale cost: ";
            cin >> *holderData.wholesale;
            fileHandler.clear();
            fileHandler.seekp(currentPointerPosition, ios::beg);
            fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
            ;
            // testBits(fileHandler);
        }
        else if (editChoice == 7){
            cout << "Enter new Retail cost: ";
            cin >> *holderData.retail;
            fileHandler.clear();
            fileHandler.seekp(currentPointerPosition);
            fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
            ;
            // testBits(fileHandler);
        }
        else if (editChoice == -1){
            fileHandler.close();
            // testBits(fileHandler);
            return;
        }
        bookInfo(holderData.isbn,
                holderData.bookTitle,
                holderData.author,
                holderData.publisher, 
                holderData.dateAdded,
                *holderData.qtyOnHand,
                *holderData.wholesale,
                *holderData.retail
                );
    }
    fileHandler.close();
    // testBits(fileHandler);
}

void deleteBook(){
    char search [51];
    int index = 0;
    char confirm;

    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    BookData holderData = {};

    // Promt user to input the books title
    cout << "You have selected Delete Book.\n";
    cout << "Enter Book's Title: ";
    cin.ignore(1, '\n');
    cin.getline(search,51);
    
    // Find match in array
    while(fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData))){
    strUpper(search);
    if(strstr(holderData.bookTitle, search)){
        // bookInfo(bookData[index].isbn,
        //         bookData[index].bookTitle,
        //         bookData[index].author,
        //         bookData[index].publisher, 
        //         bookData[index].dateAdded,
        //         *bookData[index].qtyOnHand,
        //         *bookData[index].wholesale,
        //         *bookData[index].retail
        //         );
        removeBook(search);
        break;
    }
    }

    // Confirm user wishes to delete book
    cout << "Are you sure you want to delete " << search << " y/n: ";
    cin >> confirm;
    if(tolower(confirm) == 'y'){
        *holderData.isbn = '\0';
        *holderData.bookTitle = '\0';
        *holderData.author = '\0';
        *holderData.publisher = '\0';
        *holderData.dateAdded = '\0';
        *holderData.qtyOnHand = 0;
        *holderData.wholesale = 0;
        *holderData.retail = 0;
    }
    else {
        fileHandler.close();
        return;
    }
}


// Stub Functions to Test Report Function
void repListing(){
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    BookData holderData;
    while (fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData))){
        if(*holderData.bookTitle != '\0'){
            cout << holderData.bookTitle << endl << holderData.isbn << endl << holderData.author <<  endl;
            cout << holderData.publisher << endl << holderData.dateAdded << endl;
            cout << *holderData.qtyOnHand << endl << *holderData.wholesale << endl << *holderData.retail << endl;
            cout << "------------------------------------------------------\n";
        }
    }
    fileHandler.close();
    return;
}

void repWholesale(){
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    BookData holderData;
    double totalWholesale = 0;
    while(fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData))){
        if(*holderData.bookTitle != '\0'){
            cout << holderData.bookTitle << endl << holderData.isbn << endl << holderData.author <<  endl;
            cout << holderData.publisher << endl << holderData.dateAdded << endl;
            cout << holderData.qtyOnHand << endl << holderData.wholesale << endl << holderData.retail << endl;
            cout << "------------------------------------------------------\n";
            totalWholesale += static_cast<double>(*holderData.qtyOnHand * *holderData.wholesale);
        }
    }
    cout << "Total Wholesale Value: " << setprecision(12) << totalWholesale << endl << endl;
    fileHandler.close();
    return;
}

void repRetail(){
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    BookData holderData;
    fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    double totalRetail = 0;
    for (int index = 0; index < 19; index++){
        if(*holderData.bookTitle != '\0'){
            cout << holderData.bookTitle << endl << holderData.isbn << endl << holderData.author <<  endl;
            cout << holderData.publisher << endl << holderData.dateAdded << endl;
            cout << holderData.qtyOnHand << endl << holderData.wholesale << endl << holderData.retail << endl;
            cout << "------------------------------------------------------\n";
            totalRetail += static_cast<double>(*holderData.qtyOnHand * *holderData.retail);
        }
    }
    cout << "Total Retail Value: " << totalRetail << endl << endl;
    fileHandler.close();
    return;
}

void repQty(){
    vector <BookData> bookData;
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    BookData holder;
    int minIndex;
    char stringHolder[51];
    int intHolder;
    double floatHolder;


    while(fileHandler.read(reinterpret_cast<char*>(&holder), sizeof(BookData))){
        bookData.push_back(holder);
    }

    for(int i = 0; i < bookData.size()-1; i++){
        int minIndex = i;
        if(bookData[i].isbn[0] == '\0'){
            continue;
        }
        for(int j = i+1; j < bookData.size(); j++){
            if(*bookData[j].isbn != '\0' && bookData[j].qtyOnHand > bookData[j].qtyOnHand){
                minIndex = j;
            }
            
        }
        if(minIndex != i && *bookData[minIndex].isbn != '\0'){    
            // Swap bookTitle array values
            strncpy(stringHolder,bookData[minIndex].bookTitle, 51);
            strncpy(bookData[minIndex].bookTitle, bookData[i].bookTitle, 51);
            strncpy(bookData[i].bookTitle,stringHolder, 51);

            // Swap ISBN Array values
            strncpy(stringHolder, bookData[minIndex].isbn, 14);
            strncpy(bookData[minIndex].isbn, bookData[i].isbn, 14);
            strncpy(bookData[i].isbn, stringHolder, 14);

            // Swap Author Array Values
            strncpy(stringHolder, bookData[minIndex].author, 31);
            strncpy(bookData[minIndex].author, bookData[i].author, 31);
            strncpy(bookData[i].author, stringHolder, 31);

            // publisher
            strncpy(stringHolder, bookData[minIndex].publisher, 31);
            strncpy(bookData[minIndex].publisher, bookData[i].publisher, 31);
            strncpy(bookData[i].publisher, stringHolder, 31);

            //date added
            strncpy(stringHolder, bookData[minIndex].dateAdded, 11);
            strncpy(bookData[minIndex].dateAdded, bookData[i].dateAdded, 11);
            strncpy(bookData[i].dateAdded, stringHolder, 11);

            //qtyOnHand
            intHolder = *bookData[minIndex].qtyOnHand;
            *bookData[minIndex].qtyOnHand = *bookData[i].qtyOnHand;
            *bookData[i].qtyOnHand = intHolder;

            //WholeSale
            floatHolder = *bookData[minIndex].wholesale;
            *bookData[minIndex].wholesale = *bookData[i].wholesale;
            *bookData[i].wholesale = floatHolder;
            
            //Retail
            floatHolder = *bookData[minIndex].retail;
            *bookData[minIndex].retail = *bookData[i].retail;
            *bookData[i].retail = floatHolder;
        }
        repListing();
    }
    fileHandler.close();
    return;
}

void repCost(){
    vector <BookData> bookData;
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    BookData holder;
    int minIndex;
    char stringHolder[51];
    int intHolder;
    double floatHolder;

    while(fileHandler.read(reinterpret_cast<char*>(&holder), sizeof(BookData))){
        bookData.push_back(holder);
    }


    for(int i = 0; i < bookData.size()-1; i++){
        int minIndex = i;
        if(*bookData[i].isbn == '\0'){
            continue;
        }
        for(int j = i+1; j < bookData.size(); j++){
            if(*bookData[j].isbn != '\0' && bookData[j].retail > bookData[minIndex].retail){
                minIndex = j;
            }
        }
        if(minIndex != i && *bookData[minIndex].isbn != '\0'){    
            // Swap bookTitle array values
 // Swap bookTitle array values
                        // Swap bookTitle array values
            strncpy(stringHolder,bookData[minIndex].bookTitle, 51);
            strncpy(bookData[minIndex].bookTitle, bookData[i].bookTitle, 51);
            strncpy(bookData[i].bookTitle,stringHolder, 51);

            // Swap ISBN Array values
            strncpy(stringHolder, bookData[minIndex].isbn, 14);
            strncpy(bookData[minIndex].isbn, bookData[i].isbn, 14);
            strncpy(bookData[i].isbn, stringHolder, 14);

            // Swap Author Array Values
            strncpy(stringHolder, bookData[minIndex].author, 31);
            strncpy(bookData[minIndex].author, bookData[i].author, 31);
            strncpy(bookData[i].author, stringHolder, 31);

            // publisher
            strncpy(stringHolder, bookData[minIndex].publisher, 31);
            strncpy(bookData[minIndex].publisher, bookData[i].publisher, 31);
            strncpy(bookData[i].publisher, stringHolder, 31);

            //date added
            strncpy(stringHolder, bookData[minIndex].dateAdded, 11);
            strncpy(bookData[minIndex].dateAdded, bookData[i].dateAdded, 11);
            strncpy(bookData[i].dateAdded, stringHolder, 11);

            //qtyOnHand
            intHolder = *bookData[minIndex].qtyOnHand;
            *bookData[minIndex].qtyOnHand = *bookData[i].qtyOnHand;
            *bookData[i].qtyOnHand = intHolder;

            //WholeSale
            floatHolder = *bookData[minIndex].wholesale;
            *bookData[minIndex].wholesale = *bookData[i].wholesale;
            *bookData[i].wholesale = floatHolder;
            
            //Retail
            floatHolder = *bookData[minIndex].retail;
            *bookData[minIndex].retail = *bookData[i].retail;
            *bookData[i].retail = floatHolder;
        }
        repListing();
    }
    fileHandler.close();
    return;
}

void repAge(){
    vector <BookData> bookData;
    BookData holder;
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    int maxIndex;
    char stringHolder [51];
    int intHolder;
    double floatHolder;

    while(fileHandler.read(reinterpret_cast<char*>(&holder), sizeof(BookData))){
        bookData.push_back(holder);
    }

    // Sort the books by dateAdded (oldest first)
    for (int i = 0; i < bookData.size()-1; i++) {
        if (*bookData[i].isbn == '\0') 
            continue; // Skip empty entries

        maxIndex = i;
        for (int j = i + 1; j < bookData.size(); j++) {
            if (*bookData[j].isbn != '\0') { //check that the element accessed isn't empty
                
                int year1 = atoi(&bookData[maxIndex].dateAdded[6]);
                int year2 = atoi(&bookData[j].dateAdded[6]);

                if (year2 < year1 || (year2 == year1 && atoi(&bookData[j].dateAdded[0]) < atoi(&bookData[maxIndex].dateAdded[0])) ||
                    (year2 == year1 && atoi(&bookData[j].dateAdded[0]) == atoi(&bookData[maxIndex].dateAdded[0]) &&
                     atoi(&bookData[j].dateAdded[3]) < atoi(&bookData[maxIndex].dateAdded[3]))) {
                    maxIndex = j;
                }
            }
        }

        // Swap all associated data between book at index 'i' and 'maxIndex'
        if (maxIndex != i) {
                        // Swap bookTitle array values
            strncpy(stringHolder,bookData[maxIndex].bookTitle, 51);
            strncpy(bookData[maxIndex].bookTitle, bookData[i].bookTitle, 51);
            strncpy(bookData[i].bookTitle,stringHolder, 51);

            // Swap ISBN Array values
            strncpy(stringHolder, bookData[maxIndex].isbn, 14);
            strncpy(bookData[maxIndex].isbn, bookData[i].isbn, 14);
            strncpy(bookData[i].isbn, stringHolder, 14);

            // Swap Author Array Values
            strncpy(stringHolder, bookData[maxIndex].author, 31);
            strncpy(bookData[maxIndex].author, bookData[i].author, 31);
            strncpy(bookData[i].author, stringHolder, 31);

            // publisher
            strncpy(stringHolder, bookData[maxIndex].publisher, 31);
            strncpy(bookData[maxIndex].publisher, bookData[i].publisher, 31);
            strncpy(bookData[i].publisher, stringHolder, 31);

            //date added
            strncpy(stringHolder, bookData[maxIndex].dateAdded, 11);
            strncpy(bookData[maxIndex].dateAdded, bookData[i].dateAdded, 11);
            strncpy(bookData[i].dateAdded, stringHolder, 11);

            //qtyOnHand
            intHolder = *bookData[maxIndex].qtyOnHand;
            *bookData[maxIndex].qtyOnHand = *bookData[i].qtyOnHand;
            *bookData[i].qtyOnHand = intHolder;

            //WholeSale
            floatHolder = *bookData[maxIndex].wholesale;
            *bookData[maxIndex].wholesale = *bookData[i].wholesale;
            *bookData[i].wholesale = floatHolder;
            
            //Retail
            floatHolder = *bookData[maxIndex].retail;
            *bookData[maxIndex].retail = *bookData[i].retail;
            *bookData[i].retail = floatHolder;
        }
    }
    repListing();
    fileHandler.close();
    return;
}


// Cashier Function

int cashier() {
    const double TAX_RATE = 0.06;
    double subtotal = 0, tax = 0;
    string date, ISBN;
    char repeatTransaction, addABook;
    vector<int> quantities;  // Stores quantities for each book in the transaction
    vector<BookData> purchasedBooks; // Store details of books in the transaction

    // Print header for cashier module
    cout << "Serendipity Booksellers\n" << setw(17) << "Cashier Module\n\n";
    cout << "Date: ";
    getline(cin, date);
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    // Begin transaction loop
    do {
        bool bookFound = false;
        BookData currentBook;
        int quantity = 0;

        cout << "ISBN: ";
        getline(cin, ISBN);

        // Open the file to search for the ISBN
        
        if (!fileHandler) {
            cerr << "Error opening file for reading.\n";
            return -1;
        }

        // Search for book by ISBN in the file
        while (fileHandler.read(reinterpret_cast<char*>(&currentBook), sizeof(BookData))) {
            if (ISBN == currentBook.isbn) {
                bookFound = true;
                break;
            }
        }
        fileHandler.close();

        // If book is found, proceed with purchase process
        if (bookFound) {
            cout << "How Many Books Are Being Purchased: ";
            cin >> quantity;
            cin.ignore();

            if (*currentBook.qtyOnHand >= quantity) {
                // Update quantity on hand for book in file
                *currentBook.qtyOnHand -= quantity;
                purchasedBooks.push_back(currentBook);  // Store the book for transaction summary
                quantities.push_back(quantity);

                // Update the file with new qtyOnHand
                fstream updateFile("inventory.dat", ios::in | ios::out | ios::binary);
                if (!updateFile) {
                    cerr << "Error opening file for updating.\n";
                    return -1;
                }
                updateFile.seekp(-static_cast<int>(sizeof(BookData)), ios::cur);
                updateFile.write(reinterpret_cast<char*>(&currentBook), sizeof(BookData));
                updateFile.close();
            } else {
                cout << "Not enough stock available.\n";
            }
        } else {
            cout << "Error: Could not find a match\n";
            cout << "Would you like to try again [y/n]: ";
            cin >> addABook;
            cin.ignore();
            if (addABook == 'n') break;
        }

        // Ask if another book should be added to the transaction
        cout << "\nWould you like to add another book to the transaction [Y/N]: ";
        cin >> repeatTransaction;
        cin.ignore(1, '\n');

    } while (repeatTransaction == 'Y' || repeatTransaction == 'y');

    // Display sales slip
    cout << "\n\nDate: " << date << "\n\n";
    cout << "Qty  ISBN             Title                   Price    Total\n";
    cout << string(61, '-') << "\n";

    for (size_t i = 0; i < purchasedBooks.size(); ++i) {
        double total = quantities[i] * *purchasedBooks[i].retail;
        subtotal += total;

        cout << left << setw(4) << quantities[i]
                  << setw(15) << purchasedBooks[i].isbn
                  << setw(20) << purchasedBooks[i].bookTitle
                  << "$" << fixed << setprecision(2) << setw(8) << purchasedBooks[i].retail
                  << "$" << fixed << setprecision(2) << total << "\n";
    }

    // Calculate and display tax and total
    tax = subtotal * TAX_RATE;
    double totalCost = subtotal + tax;

    cout << "\n" << setw(20) << "Subtotal" << setw(35) << "$ " << subtotal << "\n";
    cout << setw(15) << "Tax" << setw(40) << "$ " << tax << "\n";
    cout << setw(17) << "Total" << setw(38) << "$ " << totalCost << "\n";

    return 0;
}








// Inventory Menu Function
int invMenu(){
    int userSelection = 2;
    while(userSelection != 5){
        cout << setw(38) << "Serendipity Booksellers\n";
        cout << setw(37) << "Inventory Database\n\n";

        cout << setw(31) << "Look Up a Book\n";
        cout << setw(27) << "Add a Book\n";
        cout << setw(37) << "Edit a Book's Record\n";
        cout << setw(30) << "Delete a Book\n";
        cout << setw(41) << "Return to the Main Menu\n\n";

        cout << setw(32) << "Enter Your Choice: ";
        cin >> userSelection;
        // if(userSelection > 5 || userSelection < 1){
        //     cout << setw(55) << "Please enter a number in the range 1 - 5\n\n";
        // }
        while(userSelection > 5 || userSelection < 1){
            // cout << setw(55) << "Please enter a number in the range 1 - 5\n\n";

            break;
        }
        switch(userSelection){
            case 1:{
                // cout << setw(36) << "You have selected item 1\n";
                lookUpBook();
                break;
            }
            case 2:{
                // cout << setw(36) << "You have selected item 2\n";
                addBook();
                break;
            }
            case 3:{
                // cout << setw(36) << "You have selected item 3\n";
                editBook();
                break;
            }
            case 4:{
                // cout << setw(36) << "You have selected item 4\n";
                deleteBook();
                break;
            }
            case 5:{
                cout << setw(36) << "You have selected item 5\n";
                break;
            }
        }
    }
    return 0;
}








// Book Information function
int bookInfo(char isbn[51], char title[14], char author[31], char publisher[31], char date[11], int qty, double wholesale, double retail){
    cout << left << "Serendipity Booksellers\n";
    cout << left << "Book Information\n\n";

    cout << fixed << left << "ISBN: " << isbn << endl;
    cout << left << setw(1) << "Title: " << title << endl;
    cout << left << setw(1) << "Author: " << author << endl;
    cout << left << setw(10) << "Publisher: " << publisher << endl;
    cout << left << setw(10) << "Quantity-On-Hand: " << qty << endl;
    cout << left << setw(10) << "Wholesale Cost: " << setprecision(2) << wholesale << endl;
    cout << left << setw(10) << "Retail Price: " << setprecision(2) << retail;

    cout << endl << endl;
    return 0;
    
}







// Reports function
int reports() {
    int userSelection = 0;
    while(userSelection != 7){
        cout << setw(33) << "Serendipity Booksellers\n";
        cout << setw(25) << "Reports\n\n";
        
        cout << setw(29) << "Inventory Listing\n";
        cout << setw(37) << "Inventory Wholesale Value\n";
        cout << setw(34) << "Inventory Retail Value\n";
        cout << setw(31) << "Listing by Quantity\n";
        cout << setw(27) << "Listing by Cost\n";
        cout << setw(26) << "Listing by Age\n";
        cout << setw(35) << "Returning to Main Menu\n\n";

        cout << setw(27) << "Enter Your Choice: ";

        cin >> userSelection;
        /*if(userSelection > 7 || userSelection < 1){
            cout << setw(55) << "Please enter a number in the range 1 - 7\n\n";
        }*/

        while(userSelection > 7 || userSelection < 1){
            cout << setw(55) << "Please enter a number in the range 1 - 7\n\n";
            break;
        }
        switch(userSelection){
            case 1:{
                // cout << setw(36) << "You have selected item 1\n";
                repListing();
                break;
            }
            case 2:{
                // cout << setw(33) << "You have selected item 2\n";
                repWholesale();
                break;
            }
            case 3:{
                // cout << setw(33) << "You have selected item 3\n";
                repRetail();
                break;
            }
            case 4:{
                // cout << setw(33) << "You have selected item 4\n";
                repQty();
                break;
            }
            case 5:{
                // cout << setw(33) << "You have selected item 5\n";
                repCost();
                break;
            }
            case 6:{
                // cout << setw(33) << "You have selected item 6\n";
                repAge();
                break;
            }
            case 7:{
                cout << setw(33) << "You have selected item 7\n";
                break;
            }
        }
    }
    return 0;
}

void strUpper (char* input){
    for (int i = 0; input[i] != '\0'; i++){
        input[i] = toupper(input[i]);
    }
}


// Setter functions to set the 
// values for the member variables 
// in the BookData struct

void setTitle(string* title, int index){
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    BookData holderData;
    strncpy(holderData.bookTitle, title->c_str(), 51);
    fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    fileHandler.close();
    return;
}

void setISBN (string* isbn, int index){
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    BookData holderData;
    strncpy(holderData.isbn, isbn->c_str(), 14);
    fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    fileHandler.close();
    return;
}

void setAuthor(string* author, int index){
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    BookData holderData;
    strncpy(holderData.author, author->c_str(), 31);
    fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    fileHandler.close();
    return;
}

void setPub (string* publisher, int index){
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    BookData holderData;
    strncpy(holderData.publisher, publisher->c_str(), 31);
    fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    fileHandler.close();
    return;
}

void setDateAdded (string* date, int index){
    BookData holderData;
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    strncpy(holderData.dateAdded, date->c_str(), 11);
    fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    fileHandler.close();
    return;
}

void setQty(int qty, int index ){
    BookData holderData;
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    *holderData.qtyOnHand = qty;
    fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    fileHandler.close();
    return;
}

void setWholesale(double wholesale, int index){
    BookData holderData;
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    *holderData.wholesale = wholesale;
    fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    fileHandler.close();
    return;
}

void setRetail (double retail, int index){
    BookData holderData;
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    *holderData.retail = retail;
    fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    fileHandler.close();
    return;
}

int isEmpty(int index){
    BookData holderData;
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    if (holderData.bookTitle[0] != '\0'){
        fileHandler.close();
        return 1;
    }
    else
        return 0;
}

void removeBook(char search[]){
    // Original File
    fstream fileHandler("inventory.dat", ios::in | ios::out | ios::binary);
    
    //Temp file to store everything except the specified title
    fstream  tempFile("Temp.dat", ios::in | ios::out | ios::binary);

    // Blank BookData struct to read into
    BookData holderData = {};

    // Read all data from original file and save it to holderData
    while(fileHandler.read(reinterpret_cast<char*>(&holderData), sizeof(BookData))){
        
        //testBits(fileHandler); Debug Tool to check file flag state

        // Comparing the titles if equal to 0 its a match
        // if not a match write its values to the file;
        if(strcmp(holderData.bookTitle, search) != 0){
            tempFile.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
        }
    }

    // Delete orginal file and rename holder file
    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    fileHandler.close();
    tempFile.close();
    // fileHandler.clear();
    // fileHandler.seekp(-sizeof(BookData), ios::cur);
    // fileHandler.write(reinterpret_cast<char*>(&holderData), sizeof(BookData));
    // //testBits(fileHandler);
    // fileHandler.close();
    // //testBits(fileHandler);`
}
