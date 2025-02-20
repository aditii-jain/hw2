#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product {
public:
    // Constructor
    Clothing(const std::string& category, const std::string& name, double price, int qty, 
         const std::string& brand, const std::string& size);
    
    // Destructor
    virtual ~Clothing();

    // Returns keywords associated with this clothing (title words + brand)
    std::set<std::string> keywords() const override;

    // Displays clothing information
    std::string displayString() const override;

    // Dumps clothing info in database format
    void dump(std::ostream& os) const override;

    // Accessors
    std::string getBrand() const;
    std::string getSize() const;

private:
    std::string brand_;
    std::string size_;
};

#endif