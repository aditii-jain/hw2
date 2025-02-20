#ifndef MYDATASTORE
#define MYDATASTORE
#include "datastore.h"
#include <unordered_map>


class MyDataStore : public DataStore {
    public:
        MyDataStore() noexcept;  // Add constructor declaration
        virtual ~MyDataStore();   // Remove implementation from header

        /**
         * Adds a product to the data store
         */
        void addProduct(Product* p) override;

        /**
         * Adds a user to the data store
         */
        void addUser(User* u) override;

        /**
         * Performs a search of products whose keywords match the given "terms"
         *  type 0 = AND search (intersection of results for each term) while
         *  type 1 = OR search (union of results for each term)
         */
        std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

        /**
         * Reproduce the database file from the current Products and User values
         */
        void dump(std::ostream& ofile) override;

        /**
        * Returns users from the data store
        */
        std::set<User*> getUsers();
    
    private:
        std::set<Product*> products_;  // Store all products
        std::set<User*> users_;        // Store all users
        std::unordered_map<std::string, std::set<Product*>> keyword_to_products_;
};

#endif