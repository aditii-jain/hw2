#include "mydatastore.h"
#include "util.h" 
#include "product.h"

// Destructor
MyDataStore::~MyDataStore() {}

/**
* Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p) {
    products_.insert(p);
    for (std::string keyword : p->keywords()) {
        keyword_to_products_[keyword].insert(p);
    }
}

/**
* Adds a user to the data store
*/
void MyDataStore::addUser(User* u) {
    users_.insert(u);
}

/**
* Returns users from the data store
*/
std::set<User*> MyDataStore::getUsers() {
    return users_;
}

/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> searchResults;
    bool firstTerm = true;
    bool foundAny = false;

    for (std::string& term : terms) {
        if (keyword_to_products_.find(term) != keyword_to_products_.end()) {
            foundAny = true;
            
            if (type == 0) { // AND search
                if (firstTerm) {
                    searchResults = keyword_to_products_[term];
                    firstTerm = false;
                } else {
                    searchResults = setIntersection(searchResults, keyword_to_products_[term]);
                }
            } else { // OR search
                searchResults = setUnion(searchResults, keyword_to_products_[term]);
            }
        } else if (type == 0) {
            return {}; // Early exit for AND search if any term is missing
        }
    }
    
    if (!foundAny) return {}; // Return empty result if no OR terms were found
    return std::vector<Product*>(searchResults.begin(), searchResults.end());
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for (Product* p : products_) {
        p->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    for (User* u : users_) {
        u->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

