#include "book.h"
#include "util.h"  
#include <sstream>

// Constructor
Book::Book(const std::string& category, const std::string& name, double price, int qty, 
           const std::string& isbn, const std::string& author)
    : Product(category, name, price, qty), isbn_(isbn), author_(author) {}

// Destructor
Book::~Book() {}

// A product should match a keyword if it appears in the product name or the words in the author’s name should be searchable 
// keywords as well as the book’s ISBN number
// Returns the keywords for this book
std::set<std::string> Book::keywords() const {
    std::set<std::string> keywordSet;

    std::set<std::string> titleWords = parseStringToWords(name_);
    std::set<std::string> authorWords = parseStringToWords(author_);
    
    keywordSet = setUnion(titleWords, authorWords);
    
    keywordSet.insert(isbn_);

    return keywordSet;
}

// Displays book information in a formatted string
std::string Book::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\n"
        << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
        << price_ << " " << qty_ << " left.";
    return oss.str();
}

// Dumps book info in database format
void Book::dump(std::ostream& os) const {
    os << category_ << "\n"
        << name_ << "\n"
        << price_ << "\n"
        << qty_ << "\n"
        << isbn_ << "\n"
        << author_ << std::endl;
}

// Accessors for ISBN and Author
std::string Book::getISBN() const {
    return isbn_;
}

std::string Book::getAuthor() const {
    return author_;
}