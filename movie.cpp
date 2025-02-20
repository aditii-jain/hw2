#include "movie.h"
#include "util.h" 
#include <sstream>

// Constructor
Movie::Movie(const std::string& category, const std::string& name, double price, int qty, 
        const std::string& genre, const std::string& rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating) {}

// Destructor
Movie::~Movie() {}


// Returns the keywords for this movie
std::set<std::string> Movie::keywords() const {

    std::set<std::string> keywordSet = parseStringToWords(name_);
    
    keywordSet.insert(convToLower(genre_));


    return keywordSet;
}

// Displays movie information in a formatted string
std::string Movie::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\n"
        << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
        << price_ << " " << qty_ << " left.";
    return oss.str();
}

// Dumps book info in database format
void Movie::dump(std::ostream& os) const {
    os << category_ << "\n"
        << name_ << "\n"
        << price_ << "\n"
        << qty_ << "\n"
        << genre_ << "\n"
        << rating_ << std::endl;
}

// Accessors for ISBN and Author
std::string Movie::getGenre() const {
    return genre_;
}

std::string Movie::getRating() const {
    return rating_;
}