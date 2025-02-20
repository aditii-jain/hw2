#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"

class Movie : public Product {
public:
    // Constructor
    Movie(const std::string& category, const std::string& name, double price, int qty, 
         const std::string& genre, const std::string& rating);
    
    // Destructor
    virtual ~Movie();

    // Returns keywords associated with this movie (title words + genre)
    std::set<std::string> keywords() const override;

    // Displays movie information
    std::string displayString() const override;

    // Dumps movie info in database format
    void dump(std::ostream& os) const override;

    // Accessors
    std::string getGenre() const;
    std::string getRating() const;

private:
    std::string genre_;
    std::string rating_;
};

#endif