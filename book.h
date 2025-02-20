#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book : public Product {
public:
    // Constructor
    Book(const std::string& category, const std::string& name, double price, int qty, 
         const std::string& isbn, const std::string& author);
    
    // Destructor
    virtual ~Book();

    // Returns keywords associated with this book (title words + author name)
    std::set<std::string> keywords() const override;

    // Displays book information
    std::string displayString() const override;

    // Dumps book info in database format
    void dump(std::ostream& os) const override;

    // Accessors
    std::string getISBN() const;
    std::string getAuthor() const;

private:
    std::string isbn_;
    std::string author_;
};

#endif