#include "clothing.h"
#include "util.h"  // Assuming a helper function for string parsing
#include <sstream>

// Constructor
Clothing::Clothing(const std::string& category, const std::string& name, double price, int qty, 
           const std::string& brand, const std::string& size)
    : Product(category, name, price, qty), brand_(brand), size_(size) {}

// Destructor
Clothing::~Clothing() {}


// Returns the keywords for this Clothing
std::set<std::string> Clothing::keywords() const {
    std::set<std::string> keywordSet;

    std::set<std::string> titleWords = parseStringToWords(name_);
    std::set<std::string> BrandWords = parseStringToWords(brand_);
    
    keywordSet = setUnion(titleWords, BrandWords);

    return keywordSet;
}

// Displays Clothing information in a formatted string
std::string Clothing::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\n"
        << "Size: " << size_ << " Brand: " << brand_ << "\n"
        << price_ << " " << qty_ << " left.";
    return oss.str();
}

// Dumps Clothing info in database format
void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n"
        << name_ << "\n"
        << price_ << "\n"
        << qty_ << "\n"
        << size_ << "\n"
        << brand_ << std::endl;
}

// Accessors for Brand and Size
std::string Clothing::getBrand() const {
    return brand_;
}

std::string Clothing::getSize() const {
    return size_;
}