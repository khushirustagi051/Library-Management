#include <iostream>
#include <string>

using namespace std;

class Book;

class LibraryUser 
{
private:
    string name;
    int lateDays;
    float fineRate;
    float maxFine;

public:
    LibraryUser(string userName = "Guest", int daysLate = 0, float rate = 2.0, float maxFineAmt = 100.0) 
        : name(userName), lateDays(daysLate), fineRate(rate), maxFine(maxFineAmt) {}

    ~LibraryUser() 
    {}

    float calculateFine() const
    {
        float totalFine = lateDays * fineRate;
        return (totalFine > maxFine) ? maxFine : totalFine;
    }

    void displayReceipt() const
    {
        cout << "\n**** FINE RECEIPT ****\n";
        cout << "Name: " << name << endl;
        cout << "Late by: " << lateDays << " days\n";
        cout << "Total Fine: " << calculateFine() << " rupees\n";
        cout << "**********************\n";
    }
    
    void input() 
    {
        cout << "*** USER DETAILS ***\n";
        cout << "ENTER NAME: ";
        getline(cin, name);
        cout << "ENTER THE NUMBER OF DAYS LATE: ";
        cin >> lateDays;
        if (lateDays < 0) 
        {
            cout << "INVALID INPUT. Setting days late to 0.\n";
            lateDays = 0;
        }
        cin.ignore();
    }
};

class Book 
{
private:
    int ISBN;
    string title;
    string author;
    float rating;
    int quantity;
    
public:
    Book() : ISBN(0), title(""), author(""), rating(0.0), quantity(0) {}

    Book(long id, const string& t, const string& a, float r, int q) 
        : ISBN(id), title(t), author(a), rating(r), quantity(q) {}
    
    ~Book() 
    {}

    void input() 
    {
        cout << "\n--- ENTER BOOK DETAILS ---\n";
        cout << "ENTER ISBN No.: ";
        cin >> ISBN;
        while (ISBN <= 0) {
            cout << "Invalid ISBN. Enter again: ";
            cin >> ISBN;
        }
        cin.ignore();
        cout << "ENTER BOOK TITLE: ";
        getline(cin, title);
        while (title.empty()) {
            cout << "Title cannot be empty. Enter again: ";
            getline(cin, title);
        }
        cout << "ENTER AUTHOR NAME: ";
        getline(cin, author);
        while (author.empty()) {
            cout << "Author cannot be empty. Enter again: ";
            getline(cin, author);
        }
        cout << "ENTER BOOK RATING (0-5): ";
        cin >> rating;
        if (rating < 0.0 || rating > 5.0)
        {
           cout << "INVALID RATING. Setting to 0.0.\n";
           rating = 0.0;
        }
        cout << "ENTER QUANTITY: ";
        cin >> quantity;
        while (quantity < 0) {
            cout << "Quantity cannot be negative. Enter again: ";
            cin >> quantity;
        }
    }

    void display() const
    {
        cout << "\n*---- BOOK DETAILS ----*\n";
        cout << "ISBN No.: " << ISBN << "\n";
        cout << "BOOK TITLE: " << title << "\n";
        cout << "AUTHOR NAME: " << author << "\n";
        cout << "RATING: " << rating << "\n";
        cout << "QUANTITY: " << quantity << "\n";
    }

	long getISBN() const { return ISBN; }
	string getTitle() const { return title; }

    bool search(long searchISBN) const
    {
        return ISBN == searchISBN;
    }

    bool search(const string& searchTitle) const
    {
        return title == searchTitle;
    }
    
    bool search(const string& searchAuthor, const string& searchTitle) const
    {
        return author == searchAuthor && title == searchTitle;
    }

    Book operator-(int num) const
    {
        Book temp = *this;
        temp.quantity -= num;
        if (temp.quantity < 0) 
        {
            temp.quantity = 0;
        }
        return temp;
    }
    
    Book operator+(int numCopies) const
    {
        Book temp = *this;
        temp.quantity += numCopies;
        return temp;
    }
    
    Book operator+(const Book& b) const
    {
        Book temp;
        if (ISBN == b.ISBN && title == b.title) 
        {
            temp.ISBN = ISBN;
            temp.title = title;
            temp.author = author;
            temp.quantity = quantity + b.quantity;
            temp.rating = (rating + b.rating) / 2;
            cout << "Books merged successfully!\n";
        } 
        else 
        {
            cout << "Error: Cannot merge books with different ISBN or title.\n";
            temp = *this;
        }
        return temp;
    }

    friend void compareRatings(const Book& b1, const Book& b2);
};

void compareRatings(const Book& b1, const Book& b2) 
{
    cout << "\nComparing ratings... \n";
    if (b1.rating > b2.rating) 
    {
        cout << "Book with higher rating: \n";
        b1.display();
    } 
    else if (b2.rating > b1.rating) 
    {
        cout << "Book with higher rating: \n";
        b2.display();
    } 
    else 
    {
        cout << "Both books have the same rating.\n";
    }
}

class UsageLog 
{
public: 
    string day;
    int logins;
    
    UsageLog(string d = "", int l = 0) : day(d), logins(l) {}

    void input() 
    {
        cout << "Enter day: ";
        getline(cin, day);
        
        while (day.empty()) 
        {
            cout << "Day cannot be empty. Please re-enter: ";
            getline(cin, day);
        }        
        cout << "Enter number of logins: ";
        cin >> logins;
        while(logins < 0)
        {
            cout << "Logins cannot be negative. Please re-enter: ";
            cin >> logins;
        }
    }

    static double averageLogins(const UsageLog logs[], int n) 
    {
        int sum = 0;
        for (int i = 0; i < n; i++) 
        {
            sum += logs[i].logins;
        }
        return (double)sum / n;
    }
    
    static UsageLog busiestDay(const UsageLog logs[], int n) 
    {
        UsageLog maxDay = logs[0];
        for (int i = 1; i < n; i++) 
        {
            if (logs[i].logins > maxDay.logins) 
            {
                maxDay = logs[i];
            }
        }
        return maxDay;
    }

    static void compareWeeks(const UsageLog week1[], int n1, const UsageLog week2[], int n2) 
    {
        int total1 = 0, total2 = 0;
        for (int i = 0; i < n1; i++) total1 += week1[i].logins;
        for (int i = 0; i < n2; i++) total2 += week2[i].logins;
        cout << "\nTotal logins Week 1: " << total1;
        cout << "\nTotal logins Week 2: " << total2;
        if (total1 > total2)
            cout << "\nWeek 1 was busier.\n";
        else if (total2 > total1)
            cout << "\nWeek 2 was busier.\n";
        else
            cout << "\nBoth weeks had equal logins.\n";
    }
};

class Member 
{
protected:
    int memberID;
    string name, contact;
public:
    void inputMember() 
    {
        cout << "Enter Member ID: ";
        cin >> memberID;
        while (memberID < 0) 
        {
            cout << "Invalid. Enter again: ";
            cin >> memberID;
        }
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        while (name.empty()) 
        {
            cout << "Invalid. Enter again: ";
            getline(cin, name);
        }
        cout << "Enter Contact Info (10 digits): ";
        getline(cin, contact);
        while (contact.empty() || contact.length() != 10) 
        {
            cout << "Invalid. Enter again (10 digits): ";
            getline(cin, contact);
        }
    }
    void displayMember() const
    {
        cout << "\n----- Member Details -----\n";
        cout << "Member ID: " << memberID << endl;
        cout << "Name: " << name << endl;
        cout << "Contact Number: " << contact << endl;
    }
    void updateContact() 
    {
        cout << "Enter new Contact Number: ";
        getline(cin, contact);
        while (contact.empty() || contact.length() != 10) 
        {
            cout << "Invalid. Enter again (10 digits): ";
            getline(cin, contact);
        }
        cout << "Contact updated successfully.\n";
    }
};

class Student : public Member 
{
protected:
    int rollNo, sem, borrowed;
    string course;
public:
    void inputStudent() 
    {
        cout << "Enter Student Roll Number: ";
        cin >> rollNo;
        while (rollNo < 0) 
        {
            cout << "Invalid. Enter again: ";
            cin >> rollNo;
        }
        cout << "Enter Semester: ";
        cin >> sem;
        while (sem <= 0) 
        {
            cout << "Invalid. Enter again: ";
            cin >> sem;
        }
        cin.ignore();
        cout << "Enter Course: ";
        getline(cin, course);
        while (course.empty()) 
        {
            cout << "Invalid. Enter again: ";
            getline(cin, course);
        }
        cout << "Enter number of books borrowed: ";
        cin >> borrowed;
        while (borrowed < 0) 
        {
            cout << "Invalid. Enter again: ";
            cin >> borrowed;
        }
        cin.ignore();
    }

    void displayStudent() const
    {
        cout << "\n----- Student Details -----\n";
        cout << "Roll Number: " << rollNo << endl;
        cout << "Course: " << course << endl;
        cout << "Semester: " << sem << endl;
        cout << "Books Borrowed: " << borrowed << endl;
    }
    
    void checkBorrowEligibility() const
    {
        if (borrowed < 5)
            cout << "Eligible to borrow more books.\n";
        else
            cout << "Not eligible to borrow more books.\n";
    }
};

class Researcher 
{
protected:
    string thesis, guide, area;
public:
    void inputResearch() 
    {
        cout << "Enter Thesis Title: ";
        getline(cin, thesis);
        while (thesis.empty()) 
        {
            cout << "Thesis cannot be empty. Enter again: ";
            getline(cin, thesis);
        }
        cout << "Enter Research Area: ";
        getline(cin, area);
        while (area.empty()) 
        {
            cout << "Research Area cannot be empty. Enter again: ";
            getline(cin, area);
        }
        cout << "Enter Research Guide: ";
        getline(cin, guide);
        while (guide.empty()) 
        {
            cout << "Guide cannot be empty. Enter again: ";
            getline(cin, guide);
        }
    }
    void displayResearch() const
    {
        cout << "\n--- Research Details ---\n";
        cout << "Thesis Title: " << thesis << endl;
        cout << "Research Area: " << area << endl;
        cout << "Guide: " << guide << endl;
    }
};

class ResearchScholar : public Student, public Researcher 
{
public:
    void inputScholar() 
    {
        cout << "\n=== Enter Research Scholar Details ===\n";
        inputMember();
        inputStudent();
        inputResearch();
    }

    void displayScholar() const
    {
        displayMember();
        displayStudent(); 
        displayResearch(); 
    }
    
    void checkJournalEligibility() const

    {
        if (borrowed >= 5 || sem <= 3)
            cout << "Not eligible for journal access.\n";
        else
            cout << "Eligible for journal access.\n";
    }
};

class LibraryManagementSystem 
{
private:
    static const int MAX_BOOKS = 100;
    static const int MAX_SCHOLARS = 50;

    Book books[MAX_BOOKS];
    int bookCount;

    ResearchScholar scholars[MAX_SCHOLARS];
    int scholarCount;

public:
	    LibraryManagementSystem() 
		{
        bookCount = 0;
        scholarCount = 0;
        }

    void run() 
    {
        int choice;
        do 
        {
            cout << "\n\n===== MASTER LIBRARY SYSTEM =====\n";
            cout << "1. Manage Books\n";
            cout << "2. Manage Research Scholars\n";
            cout << "3. Calculate Fines\n";
            cout << "4. Analyze Usage Logs \n";
            cout << "5. Compare Book Ratings \n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) 
            {
                case 1:
                    manageBooks();
                    break;
                case 2:
                    manageScholars();
                    break;
                case 3:
                    calculateFine();
                    break;
                case 4:
                    analyzeUsage();
                    break;
                case 5:
                    compareBookRatings();
                    break;
                case 6:
                    cout << "Exiting program. Thank you for using the system!\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } while (choice != 6);
    }
    
private:
    void manageBooks() 
    {
        int choice;
        do 
        {
            cout << "\n--- BOOK MANAGEMENT ---\n";
            cout << "1. Add a new book\n";
            cout << "2. Search for a book\n";
            cout << "3. Display all books\n";
            cout << "4. Issue a copy (- operator)\n";
            cout << "5. Restock a book (+ operator)\n";
            cout << "6. Merge books (+ operator)\n";
            cout << "7. Back to main menu\n";
            cout << "Enter your choice: ";
            cin >> choice;
            
            switch (choice)
            {
                case 1:
                    if (bookCount < MAX_BOOKS)
                    {
                        books[bookCount].input();
                        bookCount++;
                    } else {
                        cout << "Maximum book capacity reached.\n";
                    }
                    break;
                case 2:
                    searchBook();
                    break;
                case 3:
                    if (bookCount == 0)
                    {
                        cout << "No books in the library.\n";
                    }
                    else
                    {
                        for (int i = 0; i < bookCount; ++i)
                        {
                            books[i].display();
                        }
                    }
                    break;
                case 4:
                {
                    long isbn;
                    cout << "Enter ISBN of book to issue: ";
                    cin >> isbn;
                    for (int i = 0; i < bookCount; ++i)
                    {
                        if (books[i].search(isbn))
                        {
                            books[i] = books[i] - 1;
                            cout << "One copy issued. Current quantity:\n";
                            books[i].display();
                            return;
                        }
                    }
                    cout << "Book not found.\n";
                    break;
                }
                case 5:
                {
                    long isbn;
                    int num;
                    cout << "Enter ISBN of book to restock: ";
                    cin >> isbn;
                    cout << "Enter number of copies to add: ";
                    cin >> num;
                    for (int i = 0; i < bookCount; ++i)
                    {
                        if (books[i].search(isbn))
                        {
                            books[i] = books[i] + num;
                            cout << "Copies restocked. Current quantity:\n";
                            books[i].display();
                            return;
                        }
                    }
                    cout << "Book not found.\n";
                    break;
                }
                case 6:
                {
                    long isbn1, isbn2;
                    cout << "Enter ISBN of the first book to merge: ";
                    cin >> isbn1;
                    cout << "Enter ISBN of the second book to merge: ";
                    cin >> isbn2;
                    Book *b1 = 0, *b2 = 0;
                    for (int i = 0; i < bookCount; ++i)
                    {
                        if (books[i].search(isbn1)) b1 = &books[i];
                        if (books[i].search(isbn2)) b2 = &books[i];
                    }

                    if (b1 && b2)
					{
					    if (b1->getISBN() == b2->getISBN() && b1->getTitle() == b2->getTitle()) 
					    {
					        *b1 = *b1 + *b2;
                            for (int i = 0; i < bookCount; ++i) {
                                if (&books[i] == b2) {
                                    for (int j = i; j < bookCount - 1; ++j) {
                                        books[j] = books[j+1];
                                    }
                                    bookCount--;
                                    break;
                                }
                            }
                        } else {
                            cout << "Books cannot be merged due to different titles.\n";
                        }
                    } else {
                        cout << "One or both books not found.\n";
                    }
                    break;
                }
                case 7:
                    return;
                default:
                    cout << "Invalid choice.\n";
                    break;
            }
        } while (choice != 7);
    }
    
    void searchBook() 
    {
        int searchChoice;
        cout << "\n--- BOOK SEARCH ---\n";
        cout << "1. Search by ISBN\n";
        cout << "2. Search by Title\n";
        cout << "3. Search by Author and Title\n";
        cout << "Enter your choice: ";
        cin >> searchChoice;
        
        bool found = false;
        cin.ignore();
        
        switch (searchChoice) 
        {
            case 1:
            {
                long isbn;
                cout << "Enter ISBN: ";
                cin >> isbn;
                for (int i = 0; i < bookCount; ++i) 
                {
                    if (books[i].search(isbn)) 
                    {
                        books[i].display();
                        found = true;
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                string title;
                cout << "Enter Title: ";
                getline(cin, title);
                for (int i = 0; i < bookCount; ++i) 
                {
                    if (books[i].search(title)) 
                    {
                        books[i].display();
                        found = true;
                    }
                }
                break;
            }
            case 3:
            {
                string author, title;
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter Title: ";
                getline(cin, title);
                for (int i = 0; i < bookCount; ++i) 
                {
                    if (books[i].search(author, title)) 
                    {
                        books[i].display();
                        found = true;
                        break;
                    }
                }
                break;
            }
            default:
                cout << "Invalid search choice.\n";
        }
        if (!found && searchChoice >= 1 && searchChoice <= 3)
        {
            cout << "Book not found.\n";
        }
    }
    
    void manageScholars() 
    {
        int choice;
        do 
        {
            cout << "\n--- SCHOLAR MANAGEMENT ---\n";
            cout << "1. Add a new scholar\n";
            cout << "2. Display all scholars\n";
            cout << "3. Update scholar contact\n";
            cout << "4. Check scholar borrow eligibility\n";
            cout << "5. Check scholar journal access eligibility\n";
            cout << "6. Back to main menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    if (scholarCount < MAX_SCHOLARS)
                    {
                        scholars[scholarCount].inputScholar();
                        scholarCount++;
                    } else {
                        cout << "Maximum scholar capacity reached.\n";
                    }
                    break;
                case 2:
                    if (scholarCount == 0)
                    {
                        cout << "No scholars to display.\n";
                    }
                    else
                    {
                        for (int i = 0; i < scholarCount; ++i)
                        {
                            scholars[i].displayScholar();
                        }
                    }
                    break;
                case 3:
                {
                    int index;
                    cout << "Enter scholar index (1 to " << scholarCount << "): ";
                    cin >> index;
                    if (index > 0 && index <= scholarCount)
                    {
                        cin.ignore();
                        scholars[index - 1].updateContact();
                    }

                    else
                    {
                        cout << "Invalid index.\n";
                    }
                    break;
                }
                case 4:
                {
                    int index;
                    cout << "Enter scholar index (1 to " << scholarCount << "): ";
                    cin >> index;
                    if (index > 0 && index <= scholarCount)
                    {
                        scholars[index - 1].checkBorrowEligibility();
                    }
                    else
                    {
                        cout << "Invalid index.\n";
                    }
                    break;
                }
                case 5:
                {
                    int index;
                    cout << "Enter scholar index (1 to " << scholarCount << "): ";
                    cin >> index;
                    if (index > 0 && index <= scholarCount)
                    {
                        scholars[index - 1].checkJournalEligibility();
                    }
                    else
                    {
                        cout << "Invalid index.\n";
                    }
                    break;
                }
                case 6:
                    return;
                default:
                    cout << "Invalid choice.\n";
                    break;
            }
        } while (choice != 6);
    }
    
    void calculateFine() 
    {
        LibraryUser user;
        char choice;
        do 
        {
            user.input();
            user.displayReceipt();
            cout << "\nDo you wish to continue? (y/n): ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
    }
    
    void analyzeUsage() 
    {
        int n1, n2;
        cout << "Enter number of days for Week 1 (max 7): ";
        cin >> n1;
        UsageLog week1[7];
        for (int i = 0; i < n1; i++) 
        {
            cout << "\n--- Enter details for Day " << i + 1 << " (Week 1) ---\n";
            week1[i].input();
        }

        cout << "\nEnter number of days for Week 2 (max 7): ";
        cin >> n2;
        UsageLog week2[7];
        for (int i = 0; i < n2; i++) 
        {
            cout << "\n--- Enter details for Day " << i + 1 << " (Week 2) ---\n";
            week2[i].input();
        }

        cout << "\n=== Week 1 Analysis ===";
        cout << "\nAverage logins (Week 1): " << UsageLog::averageLogins(week1, n1);
        UsageLog busy1 = UsageLog::busiestDay(week1, n1);
        cout << "\nBusiest day (Week 1): " << busy1.day << " with " << busy1.logins << " logins.";
        
        cout << "\n\n=== Week 2 Analysis ===";
        cout << "\nAverage logins (Week 2): " << UsageLog::averageLogins(week2, n2);
        UsageLog busy2 = UsageLog::busiestDay(week2, n2);
        cout << "\nBusiest day (Week 2): " << busy2.day << " with " << busy2.logins << " logins.";
        
        cout << "\n\n=== Week Comparison ===\n";
        UsageLog::compareWeeks(week1, n1, week2, n2);
    }

    void compareBookRatings() 
    {
        if (bookCount < 2) 
        {
            cout << "You need to add at least two books to compare their ratings.\n";
            return;
        }
        
        long isbn1, isbn2;
        cout << "Enter ISBN of the first book: ";
        cin >> isbn1;
        cout << "Enter ISBN of the second book: ";
        cin >> isbn2;

        Book *b1 = NULL, *b2 = NULL;
        for (int i = 0; i < bookCount; ++i)
        {
            if (books[i].search(isbn1)) b1 = &books[i];
            if (books[i].search(isbn2)) b2 = &books[i];
        }

        if (b1 && b2)
        {
            compareRatings(*b1, *b2);
        } else {
            cout << "One or both books not found.\n";
        }
    }
};

int main() 
{
    LibraryManagementSystem system;
    system.run();
    return 0;
}
