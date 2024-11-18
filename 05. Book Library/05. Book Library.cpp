/* 05. Book Library.cpp
*
 * Unreal Engine Game Developer Course | Laba.IT
 *
 * Home Assignment No. 5:
 * - create a program simulating book library using class inheritance and data structures from C++ Standard Library
 * - program must support the following operations:
 *   - add book
 *   - delete book
 *   - rent book to a user
 *   - return book
 *   - display state of library
 * 
 * Code written by Hubert Pitura (hpitura@gmail.com)
 */

#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <charconv>
#include "Random Data.h"

using namespace std;

// Some typedefs and max sizes used later for map ids
typedef size_t BookID;
BookID maxBookID = static_cast<BookID>(-1);

typedef size_t UserID;
UserID maxUserID = static_cast<UserID>(-1);

enum class BookStatus
{
    available, unavailable, booked, rented
};

const char* to_string(BookStatus e)
{
    switch (e)
    {
    case BookStatus::available: return "available";
    case BookStatus::unavailable: return "unavailable";
    case BookStatus::booked: return "booked";
    case BookStatus::rented: return "rented";
    default: return "unknown";
    }
}

class Book
{
public:
    Book() = default;

    Book(const string& author, const string& title, const string& publisher, const string& ISBN)
    {
        this->author_ = author;
        this->title_ = title;
        this->publisher_ = publisher;
        this->ISBN_ = ISBN;
    }

    Book(const Book& book)
    {
        this->author_ = book.author_;
        this->title_ = book.title_;
        this->publisher_ = book.publisher_;
        this->ISBN_ = book.ISBN_;
    }

    Book& operator=(const Book& book)
    {
        // Check for self-assignment
        if (this != &book)
        {
            this->author_ = book.author_;
            this->title_ = book.title_;
            this->publisher_ = book.publisher_;
            this->ISBN_ = book.ISBN_;
        }
        
        return *this;
    }

    string getAuthor() const
    {
        return author_;
    }

    void setAuthor(const string& author)
    {
        author_ = author;
    }

    string getTitle() const
    {
        return title_;
    }

    void setTitle(const string& title)
    {
        title_ = title;
    }

    string getPublisher() const
    {
        return publisher_;
    }

    void setPublisher(const string& publisher)
    {
        publisher_ = publisher;
    }

    string getISBN() const
    {
        return ISBN_;
    }

    void setISBN(const string& isbn)
    {
        ISBN_ = isbn;
    }
    
    friend ostream& operator<<(ostream& os, const Book& book);
    
protected:
    string author_;
    string title_;
    string publisher_;
    string ISBN_;
};

ostream& operator<<(ostream& os, const Book& book)
{
    cout << "Author: " << book.author_ << '\n';
    cout << "Title: " << book.title_ << '\n';
    cout << "Publisher: " << book.publisher_ << '\n';
    cout << "ISBN: " << book.ISBN_ << endl;

    return os;
}

class LibraryBook : Book
{
public:
    LibraryBook() = default;

    LibraryBook(const string& author, const string& title, const string& publisher, const string& ISBN)
    {
        this->author_ = author;
        this->title_ = title;
        this->publisher_ = publisher;
        this->ISBN_ = ISBN;
        this->bookStatus_ = BookStatus::available;
        // UserID == 0 when book is not booked or rented
        this->userID_ = static_cast<UserID>(0);
    }

    using Book::getAuthor, Book::setAuthor, Book::getTitle, Book::setTitle, Book::getPublisher, Book::setPublisher, Book::getISBN, Book::setISBN;

    friend ostream& operator<<(ostream& os, const LibraryBook& book);

    BookStatus getBookStatus() const
    {
        return this->bookStatus_;
    }
    
    void setBookStatus(const BookStatus bookStatus, UserID userID = static_cast<UserID>(0))
    {
        // userID == 0 is not a valid user ID
        if ((bookStatus == BookStatus::booked or bookStatus == BookStatus::rented) and userID == static_cast<UserID>(0))
            cout << "Error: You need to provide UserID when booking or renting the book!" << endl;
        else
        {
            this->bookStatus_ = bookStatus;
            this->userID_ = userID;
        }
    }

    UserID getUserID() const
    {
        return this -> userID_;
    }
    
private:
    BookStatus bookStatus_;
    UserID userID_;  
};

ostream& operator<<(ostream& os, const LibraryBook& book)
{
    
    cout << "Author: " << book.author_ << '\n';
    cout << "Title: " << book.title_ << '\n';
    cout << "Publisher: " << book.publisher_ << '\n';
    cout << "ISBN: " << book.ISBN_ << '\n';
    cout << "Book Status: " << to_string(book.getBookStatus());
    cout << endl;

    return os;
}

class User
{
public:
    User() = default;

    User(const string name, const string surname, const string email)
    {
        this->name_ = name;
        this->surname_ = surname;
        this->email_ = email;
    }

    string getName() const
    {
        return name_;
    }

    void setName(const string& name)
    {
        name_ = name;
    }

    string getSurname() const
    {
        return surname_;
    }

    void setSurname(const string& surname)
    {
        surname_ = surname;
    }

    string getEmail() const
    {
        return email_;
    }

    void setEmail(const string& email)
    {
        email_ = email;
    }

    friend ostream& operator<<(ostream& os, const User& user);
    
private:
    string name_;
    string surname_;
    string email_;
};

ostream& operator<<(ostream& os, const User& user)
{
    cout << "Name: " << user.name_ << '\n';
    cout << "Surname: " << user.surname_ << '\n';
    cout << "Email: " << user.email_ << endl;

    return os;
}

class Library
{
public:
    BookID addBook(const LibraryBook& book)
    {
        // add book at new ID (here it's just another available integer in a sequence)
        bool idOK = false;
        // (bookID == 0 is not used, that's why size + 1)
        // BookID bookID = books_.size() + 1;
        BookID bookID = static_cast<BookID>(1);
        
        while(!idOK)
        {
            if(!books_.contains(bookID))
            {
                books_[bookID] = book;
                idOK = true;
            }
            else
                bookID++;
        }

        return bookID;
    }

    void addBookAtID(const LibraryBook& book, BookID bookID)
    {
        if(!books_.contains(bookID))
            books_[bookID] = book;
        else
            cout << "Error: book already exists at the given ID!" << endl;            
    }

    void removeBook(const BookID bookID)
    {
        if (!books_.contains(bookID))
        {
            cout << "Error: Book with given ID does not exist in the library." << endl;
        }
        else if ((books_[bookID].getBookStatus() == BookStatus::booked) or (books_[bookID].getBookStatus() == BookStatus::rented))
        {
            cout << "Error: cannot remove book. The book is booked or rented from the library." << endl;
            printBookInfo(bookID);
        }
        else
        {
            printBookInfo(bookID);
            books_.erase(bookID);
            cout << "\nInfo: Book removed from the library." << endl;
        }
    }

    void setBookStatus(const BookID bookID, const UserID userID, const BookStatus bookStatus)
    {
        if (!books_.contains(bookID))
            cout << "Error: Book with given ID does not exist in the library." << endl;
        else if (!users_.contains(userID))
            cout << "Error: User with given ID does not exist in the library." << endl;
        else if (bookStatus == BookStatus::booked or bookStatus == BookStatus::rented)
            books_[bookID].setBookStatus(bookStatus, userID);
        else
            // User ID will be set to 0
            books_[bookID].setBookStatus(bookStatus);
    }

    BookStatus getBookStatus(const BookID bookID)
    {
        if (!books_.contains(bookID))
        {
            cout << "Error: Book with given ID does not exist in the library." << endl;
            return BookStatus::unavailable;
        }
        else
            return books_[bookID].getBookStatus();
    }

    string getBookTitle(const BookID bookID)
    {
        if (!books_.contains(bookID))
            cout << "Error: Book with given ID does not exist in the library." << endl;
        else
            return books_[bookID].getTitle();
    }

    UserID addUser(const User& user)
    {
        // add user at new ID (here it's just another available integer in a sequence)
        bool idOK = false;
        // (userID == 0 is not used, that's why size + 1)
        // UserID userID = users_.size() + 1;
        UserID userID = static_cast<UserID>(1);
        
        while(!idOK)
        {
            if(!users_.contains(userID))
            {
                users_[userID] = user;
                idOK = true;
            }
            else
                userID++;
        }

        return userID;
    }

    void addUserAtID(const User& user, UserID userID)
    {
        if(!users_.contains(userID))
            users_[userID] = user;
        else
            cout << "Error: user already exists at the given ID!" << endl;            
    }

    string getUserName(const UserID userID)
    {
        if(!users_.contains(userID))
            cout << "Error: User with given ID does not exist!" << endl;
        else
            return users_[userID].getName() + " " + users_[userID].getSurname();
    }

    // Get user ID by book ID (0 is returned if not booked or rented)
    UserID getUserID(const BookID bookID)
    {
        if(!books_.contains(bookID))
            cout << "Error: Book with given ID does not exist!" << endl;
        else
            return books_[bookID].getUserID();
    }

    void removeUser(const UserID userID)
    {
        if (!users_.contains(userID))
        {
            cout << "\nError: User with given ID does not exist in the library." << endl;
        }
        else
        {
            bool removeOK = true;

            cout << '\n';
        
            for (auto e : books_)
            {
                if (e.second.getUserID() == userID)
                {
                    cout << '\"' + e.second.getTitle() + "\" (book ID: " << e.first << ") is still " << to_string(e.second.getBookStatus()) << " by the user." << endl;
                    removeOK = false;
                }
            }
        
            if (!removeOK)
            {
                cout << "\nError: cannot remove user. The user still have book(s) booked or rented from the library." << endl;
            }
            else
            {
                cout << users_[userID];
                users_.erase(userID);
                cout << "\nInfo: User removed from the library." << endl;
            }
        }
    }

    void printBookInfo(const BookID bookID)
    {        
        if (!books_.contains(bookID))
            cout << "\nBook with given ID does not exist in the library." << endl;
        else
        {
            cout << "\nBook ID: " << bookID << '\n' << books_[bookID];

            if (books_[bookID].getBookStatus() == BookStatus::booked)
                cout << "Book is " << to_string(BookStatus::booked) << " by " << getUserName(books_[bookID].getUserID()) << " (user ID: " << books_[bookID].getUserID() << ")" << endl;
            else if (books_[bookID].getBookStatus() == BookStatus::rented)
                cout << "Book is " << to_string(BookStatus::rented) << " by " << getUserName(books_[bookID].getUserID()) << " (user ID: " << books_[bookID].getUserID() << ")" << endl;
        }
    }
    
    void printBooks()
    {
        cout << "<< Displaying all books >>" << endl;
        
        if (books_.empty())
            cout << "\nNo books found." << endl;
        else
            for (auto const [bookID, book] : books_)
            {
                cout << "\nBook ID: " << bookID << '\n' << book;

                if (books_[bookID].getBookStatus() == BookStatus::booked or books_[bookID].getBookStatus() == BookStatus::rented)
                    cout << "Book is " << to_string(books_[bookID].getBookStatus()) << " by " << getUserName(books_[bookID].getUserID()) << " (user ID: " << books_[bookID].getUserID() << ")" << endl;
            }
    }

    void printBooksByStatus(BookStatus status)
    {
        bool found = false;
        
        for (auto const [bookID, book] : books_)
            if (book.getBookStatus() == status)
            {
                cout << "\nBook ID: " << bookID << '\n' << book;
                found = true;

                if (books_[bookID].getBookStatus() == BookStatus::booked or books_[bookID].getBookStatus() == BookStatus::rented)
                    cout << "Book is " << to_string(books_[bookID].getBookStatus()) << " by " << getUserName(books_[bookID].getUserID()) << " (user ID: " << books_[bookID].getUserID() << ")" << endl;
            }

        if (!found)
            cout << "\nNo books found in " << to_string(status) << " status." << endl;
    }

    void printUserInfo(const UserID userID)
    {        
        if (!users_.contains(userID))
            cout << "\nUser with given ID does not exist in the library." << endl;
        else
        {
            cout << '\n' << users_[userID] << endl;

            bool displayBookList = true;
            
            for (auto const [bookID, book] : books_)
            {
                if (book.getUserID() == userID)
                {
                    if (displayBookList)
                    {
                        cout << "User has booked or rented the following book(s):\n";
                        displayBookList = false;
                    }
                    
                    cout << '\"' << book.getTitle() << "\" (book ID: " << bookID << ") is " << to_string(book.getBookStatus()) << endl;
                }
            }

            if (displayBookList)
                cout << "No books are assigned to this user." << endl;
        }
    }
    
    void printUsers()
    {
        cout << "<< Displaying all users >>" << endl;
        if (users_.empty())
            cout << "\nNo users found." << endl;
        else
            for (auto const [userID, user] : users_)
                cout << "\nUser ID: " << userID << '\n' << user;
    }
    
private:
    // bookID is mapped to LibraryBook
    map<BookID, LibraryBook> books_;
    // userID is mapped to User
    map<UserID, User> users_;
};

// Helper functions to create fake stuff :)

// Random generators are external to other classes to keep them generic
// (in the real world nobody's adding fake stuff to a library or create fake ISBNs :))

// Create random International Standard Book Number (ISBN) identifier
static string createFakeISBN()
{
    string ISBN {};
    int num { 0 };

    num = rand() % 1000;

    if (num < 10)
        ISBN += "00";
    else if (num < 100)
        ISBN += "0";

    ISBN += to_string(num) + "-" + to_string(rand() % 10) + "-";

    num = rand() % 100;

    if (num < 10)
        ISBN += "0";

    ISBN += to_string(num) + "-";

    num = rand() % 1000000;

    if (num < 10)
        ISBN += "00000";
    else if (num < 100)
        ISBN += "0000";
    else if (num < 1000)
        ISBN += "000";
    else if (num < 10000)
        ISBN += "00";
    else if (num < 100000)
        ISBN += "0";

    ISBN += to_string(num) + "-" + to_string(rand() % 10);
    
    return ISBN;
}

static Book createFakeBook()
{
    return Book(Names[rand() % Names.size()] + " " + Surnames[rand() % Surnames.size()], bookTitles[rand() % bookTitles.size()], bookPublishers[rand() % bookPublishers.size()], createFakeISBN());
}

static LibraryBook createFakeLibraryBook()
{
    return LibraryBook(Names[rand() % Names.size()] + " " + Surnames[rand() % Surnames.size()], bookTitles[rand() % bookTitles.size()], bookPublishers[rand() % bookPublishers.size()], createFakeISBN());
}

static User createFakeUser()
{
    string name = Names[rand() % Names.size()];
    string surname = Surnames[rand() % Surnames.size()];
    string email = name + surname;

    switch(rand() % 5)
    {
        case 0: email += "@gmail.com"; break;
        case 1: email += "@outlook.com"; break;
        case 2: email += "@yahoo.com"; break;
        case 3: email += "@dark.net"; break;
        case 4: email += "@proton.mail"; break;
    }
    
    return User(name, surname, email);
}

// Helper function to get correct input from user
template<typename T = int>
typename T getInput(const string& prm) requires (is_arithmetic_v<T>);

// Add fake content to the library
static void addFakeContent(Library* library)
{
    bool inputOK = false;
    short input { 0 };

    cout << "<< Creating fake library content >>" << endl;
    cout << "How many fake books do you want to add?" << endl;
    
    while(!inputOK)
    {
        input = getInput("Please select a number between 0 and 100: ");
        if(input >= 0 and input <= 100)
            inputOK = true;
    }

    if (input != 0)
    {
        for (size_t i = 0; i < input; ++i)
            library -> addBook(createFakeLibraryBook());

        cout << input << " fake book(s) have been added to the library.\n" << endl;
    }
    else
        cout << endl;

    inputOK = false;
    input = 0;

    cout << "How many fake users do you want to add?" << endl;
    
    while(!inputOK)
    {
        input = getInput("Please select a number between 0 and 10: ");
        if(input >= 0 and input <= 10)
            inputOK = true;
    }

    if (input != 0)
    {
        for (size_t i = 0; i < input; ++i)
            library -> addUser(createFakeUser());

        cout << input << " fake user(s) have been added to the library." << endl;
    }
}

// Helper functions to communicate with user
// (all user communication is handled outside of Library class)

void addBook(Library* library)
{
    LibraryBook book;
    string input { "" };
        
    cout << "<< Adding a new book >>" << endl;

    bool inputOK = false;
    cin.clear();
            
    while(!inputOK)
    {                    
        cout << "Please enter author's full name: ";
        getline(cin, input);
        if(!input.empty())
            inputOK = true;
    }

    book.setAuthor(input);
    input.clear();
    inputOK = false;
            
    while(!inputOK)
    {                    
        cout << "Please enter book's title: ";
        getline(cin, input);
        if(!input.empty())
            inputOK = true;
    }

    book.setTitle(input);
    input.clear();
    inputOK = false;

    while(!inputOK)
    {                    
        cout << "Please enter book's publisher: ";
        getline(cin, input);
        if(!input.empty())
            inputOK = true;
    }

    book.setPublisher(input);
    input.clear();
    inputOK = false;

    while(!inputOK)
    {
        cout << "Please enter book's ISBN (format: xxx-x-xx-xxxxxx-x): ";
        cin >> input;
        if(!input.empty())
            inputOK = true;
    }
        
    book.setISBN(input);

    book.setBookStatus(BookStatus::available);
        
    // add book at new ID
    BookID bookID = library -> addBook(book);
    cout << "\nBook added at ID: " << bookID << endl;
    library -> printBookInfo(bookID);

    // Clearing the input buffer to ignore the leftover newline character
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void addUser(Library* library)
{
    User user;
    string input { "" };
        
    cout << "<< Adding a new user >>" << endl;
        
    bool inputOK = false;
    cin.clear();

    while(!inputOK)
    {
        cout << "Please enter user name: ";
        getline(cin, input);
        if(!input.empty())
            inputOK = true;
    }

    user.setName(input);
    input.clear();
    inputOK = false;

    while(!inputOK)
    {
        cout << "Please enter user surname: ";
        getline(cin, input);
        if(!input.empty())
            inputOK = true;
    }

    user.setSurname(input);
    input.clear();
    inputOK = false;

    while(!inputOK)
    {
        cout << "Please enter user email: ";
        getline(cin, input);
        if(!input.empty())
            inputOK = true;
    }

    user.setEmail(input);

    // add user at new ID
    UserID userID = library -> addUser(user);
    cout << "\nUser added at ID: " << userID << endl;
        
    // Clearing the input buffer to ignore the leftover newline character
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printBooksInStatus(Library* library)
{
    BookStatus status { BookStatus::available };

    cout << "<< Display books in status >>\n"
            "Select status:"
            "\n1. " << to_string(BookStatus::rented) <<
            "\n2. " << to_string(BookStatus::booked) <<
            "\n3. " << to_string(BookStatus::available) <<
            "\n4. " << to_string(BookStatus::unavailable) << endl;
    
    bool inputOK = false;
    int input { 0 };
    
    while(!inputOK)
    {
        input = getInput("Please select an option (1 - 4): ");
        if(input >= 1 and input <= 4)
            inputOK = true;
    }

    switch(input)
    {
        case 1:
            status = BookStatus::rented;
            break;
        case 2:
            status = BookStatus::booked;
            break;
        case 3:
            status = BookStatus::available;
            break;
        case 4:
            status = BookStatus::unavailable;
            break;
        default:
            status = BookStatus::available;
    }

    library -> printBooksByStatus(status);
}

void rentBook(Library* library)
{
    cout << "<< Renting a book >>" << endl;

    int input = getInput("Please enter book ID: ");
    BookID bookID = static_cast<BookID>(input);
    input = getInput("Please enter user ID: ");
    UserID userID = static_cast<UserID>(input);

    if (library -> getBookStatus(bookID) ==  BookStatus::available)
        library -> setBookStatus(bookID, userID, BookStatus::rented);
    else
        cout << "\nInfo: Requested book is not available to rent." << endl;
    
    library -> printBookInfo(bookID);
}

void bookBook(Library* library)
{
    cout << "<< Booking a book >>" << endl;

    int input = getInput("Please enter book ID: ");
    BookID bookID = static_cast<BookID>(input);
    input = getInput("Please enter user ID: ");
    UserID userID = static_cast<UserID>(input);

    if (library -> getBookStatus(bookID) ==  BookStatus::available)
        library -> setBookStatus(bookID, userID, BookStatus::booked);
    else
        cout << "\nInfo: Requested book is not available to book." << endl;
    
    library -> printBookInfo(bookID);
}

void returnBook(Library* library)
{
    cout << "<< Returning a book >>" << endl;

    int input = getInput("Please enter book ID: ");
    BookID bookID = static_cast<BookID>(input);

    if (library -> getBookStatus(bookID) ==  BookStatus::available)
        cout << "Info: Requested book is already available to book or rent, no need to return it." << endl;
    else if (library -> getBookStatus(bookID) ==  BookStatus::unavailable)
        cout << "Info: Requested book is not available at the moment." << endl;
    else
    {
        library -> setBookStatus(bookID, library -> getUserID(bookID), BookStatus::available);
        cout << "\n\"" << library -> getBookTitle(bookID) << "\" (book ID: " << bookID << ") is now available for book or rent." << endl;
    }
}

/* MAIN PROGRAM CODE */
// TODO: Clean up errors shown when user or book does not exist in the library (sometimes multiple ones are shown)
int main()
{
    Library library;

    // Seed for random generators
    srand(time(nullptr));
    
    // Welcome message
    cout << "~~ HUBERT\'S BOOK LIBRARY ~~\n";
    
    while (true)
    {
        cout << "\n~~MAIN MENU~~\n";
        cout << "General operations:\n";
        cout << "    1: Display all books in the library\n"
                "    2: Display books in status\n" 
                "    3: List users registered in the library\n";
        cout << "Book operations:\n";
        cout << "    4: Display book info\n"
                "    5: Rent a book\n"
                "    6: Book a book\n"
                "    7: Return or unbook a book\n"
                "    8: Add new book to the library\n"
                "    9: Remove a book from the library\n";
        cout << "User operations:\n";
        cout << "   10: Display user info\n"
                "   11: Add new user to the library\n"
                "   12: Remove a user from the library\n";
        cout << "Library operations:\n";
        cout << "   13: Generate fake content\n";
        cout << "    0: Exit" << endl;

        bool inputOK = false;
        int input { 0 };
        
        while(!inputOK)
        {
            input = getInput("Please select an option (1 - 13, 0 to exit): ");
            if(input >= 0 and input <= 13)
                inputOK = true;
        }
        
        switch (input)
        {
            // 1: Display all books in the library
            case 1:
                library.printBooks();
                break;

            // 2: Display books in status
            case 2:
                printBooksInStatus(&library);
                break;

            // 3: List users registered in the library
            case 3:
                library.printUsers();
                break;

            // 4: Display book info
            case 4:                
                cout << "<< Displaying a book by ID >>" << endl;
                library.printBookInfo(getInput("Please enter Book ID: "));
                break;

            // 5: Rent a book
            case 5:
                rentBook(&library);
                break;

            // 6: Book a book
            case 6:
                bookBook(&library);
                break;

            // 7: Return or unbook a book
            case 7:
                returnBook(&library);
                break;
            
            // 8: Add new book to the library
            case 8:
                addBook(&library);
                break;

            // 9: Remove a book from the library
            case 9:
                cout << "<< Removing a book by ID >>" << endl;
                library.removeBook(getInput("Please enter Book ID: "));
                break;

            // 10: Display user info
            case 10:
                cout << "<< Displaying user info by ID >>" << endl;
                library.printUserInfo(getInput("Please enter User ID: "));
                break;
            
            // 11: Add new user to the library
            case 11:
                addUser(&library);
                break;

            // 12: Remove a user from the library
            case 12:
                cout << "<< Removing user by ID >>" << endl;
                library.removeUser(getInput("Please enter User ID: "));
                break;
            
            case 13:
                addFakeContent(&library);
                break;
            
            default:
                return 0;
        }
    }
}

// C++ black magic, not sure how this works, but it works :D
template<typename T = int>
typename T getInput(const string& prm) requires (is_arithmetic_v<T>)
{
    T num {};
    
    for (string inp;;)
    {
        cin.clear();
        cout << prm;
        
        if (getline(cin, inp) && !inp.empty())
        {
            const auto first {find_if(inp.begin(), inp.end(), [](unsigned ch) {return !isspace(ch); })};
            const auto end {find_if(inp.rbegin(), inp.rend(), [](unsigned ch) {return !isspace(ch); }).base()};
            const auto res {from_chars(to_address(first), to_address(end), num)};

            if (res.ec == errc {} && res.ptr == to_address(end))
                return num;
        }

        // cout << "Invalid input. a(n) " << typeid(T).name() << '\n';
        
        cout << "Invalid input. ";
    }    
}