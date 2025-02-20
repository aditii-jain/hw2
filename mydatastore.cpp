#include "mydatastore.h"
#include "util.h" 
#include "product.h"

MyDataStore::MyDataStore() noexcept {
    // Constructor implementation (can be empty if no initialization needed)
}

MyDataStore::~MyDataStore() {
    // Clean up any allocated memory
    for(Product* p : products_) {
        delete p;
    }
    for(User* u : users_) {
        delete u;
    }
}

/**
* Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p) {
    products_.insert(p);
    std::set<std::string> keywords = p->keywords();
    for(const std::string& keyword : keywords) {
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
    std::set<Product*> results;
    bool first = true;

    for(const std::string& term : terms) {
        if(keyword_to_products_.find(term) != keyword_to_products_.end()) {
            if(type == 0) { // AND search
                if(first) {
                    results = keyword_to_products_[term];
                    first = false;
                } else {
                    std::set<Product*> temp;
                    for(Product* p : results) {
                        if(keyword_to_products_[term].find(p) != keyword_to_products_[term].end()) {
                            temp.insert(p);
                        }
                    }
                    results = temp;
                }
            } else { // OR search
                results.insert(keyword_to_products_[term].begin(), keyword_to_products_[term].end());
            }
        } else if(type == 0) { // AND search with missing term
            return std::vector<Product*>();
        }
    }

    return std::vector<Product*>(results.begin(), results.end());
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for(Product* p : products_) {
        p->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    
    ofile << "<users>" << std::endl;
    for(User* u : users_) {
        u->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

