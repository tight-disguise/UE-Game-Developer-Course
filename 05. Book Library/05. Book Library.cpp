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
    
    void setBookStatus(const BookStatus& bookStatus, UserID userID = static_cast<UserID>(0))
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
        return this->userID_;
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

    if (book.getBookStatus() == BookStatus::booked or book.getBookStatus() == BookStatus::rented)
        cout << " by " << "TODO GET USER NAME FROM ID HERE";

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
    Library() = default;

    void addBook()
    {
        LibraryBook book;
        string input { "" };
        
        cout << "<< Adding a new book >>" << endl;

        bool inputOK = false;
        cin.clear();
        //cin.ignore(INT_MAX, '\n');
            
        while(!inputOK)
        {                    
            cout << "Please enter author's name: ";
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
        
        // add book at new ID (here it's just another available integer in a sequence)
        addBook(book);
    }

    void addBook(const LibraryBook& book)
    {
        // add book at new ID (here it's just another available integer in a sequence)
        bool idOK = false;
        // (bookID == 0 is not used, that's why size + 1)
        BookID bookID = books_.size() + 1;
        
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
        }
        else
        {
            books_.erase(bookID);
            cout << "Info: Book removed from the library." << endl;
        }
    }

    void addUser()
    {
        User user;
        string input { "" };
        
        cout << "<< Adding a new user >>" << endl;
        
        bool inputOK = false;
        cin.clear();
        cin.ignore(INT_MAX, '\n');

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

        // add user at new ID (here it's just another available integer in a sequence)
        addUser(user);
    }

    void addUser(const User& user)
    {
        // add user at new ID (here it's just another available integer in a sequence)
        bool idOK = false;
        // (userID == 0 is not used, that's why size + 1)
        UserID userID = users_.size() + 1;
        
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
    }

    void addUserAtID(const User& user, UserID userID)
    {
        if(!users_.contains(userID))
            users_[userID] = user;
        else
            cout << "Error: user already exists at the given ID!" << endl;            
    }

    void removeUser(const UserID userID)
    {
        if (!users_.contains(userID))
        {
            cout << "Error: User with given ID does not exist in the library." << endl;
        }
        
        bool removeOK = true;
        
        for (auto e : books_)
        {
            if (e.second.getUserID() == userID)
            {
                cout << "Info: \"" + e.second.getTitle() + "\" book is still " + to_string(e.second.getBookStatus()) + " by the user." << endl;
                removeOK = false;
            }
        }
        
        if (!removeOK)
        {
            cout << "Error: cannot remove user. The user still have books booked or rented from the library." << endl;
        }
        else
        {
            users_.erase(userID);
            cout << "Info: User removed from the library." << endl;
        }
    }

    void printBookInfo(const BookID bookID)
    {
        if (!books_.contains(bookID))
            cout << "Book with given ID does not exist in the library." << endl;
        else
            cout << "\nBook ID: " << bookID << '\n' << books_[bookID];
    }
    
    void printBooks()
    {
        if (books_.empty())
            cout << "No books found." << endl;
        else
            for (auto const [bookID, book] : books_)
                cout << "\nBook ID: " << bookID << '\n' << book;
    }

    void printUsers()
    {
        if (users_.empty())
            cout << "No users found." << endl;
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

/* MAIN PROGRAM CODE */

// helper functions used in menu and defined below main()

BookID getBookID();

int main()
{
    Library library;

    // Seed for random generators
    srand(time(nullptr));
    
    // Welcome message
    cout << "~~ Book Library ~~\n";
    
    while (true)
    {
        cout << "\nWhat do you want to do?\n";
        cout << "General operations:\n";
        // 001. RENT A BOOK
        // 002. BOOK A BOOK
        cout << "    1: Display books in the library\n"
                "    2: List users registered in the library\n";
        cout << "Book operations:\n";
        cout << "    3: Display book info\n"
                "    4: Add new book to the library\n"
                "    5: Remove a book from the library\n";
        cout << "User operations:\n";
        cout << "    6: Display user info\n"
                "    7: Add new user to the library\n"
                "    8: Remove a user from the library\n";
        cout << "Library operations:\n";
        cout << "    9: Generate fake content\n";
        cout << "    0: Exit" << endl;

        bool inputOK = false;
        short input { 0 };
        
        while(!inputOK)
        {
            input = getInput("Please select an option (1 - 9, 0 to exit): ");
            if(input >= 0 and input <= 9)
                inputOK = true;
        }
        
        switch (input)
        {
            case 1:
                library.printBooks();
                break;

            case 2:
                library.printUsers();
                break;

            case 3:
                library.printBookInfo(getInput("Please enter Book ID: "));
                break;

            case 4:
                library.addBook();
                break;

            case 5:
                library.removeBook(getInput("Please enter Book ID: "));
                break;
            
            case 9:
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