#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include <queue>

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    std::map<std::string, std::queue<Product*>> carts;
    std::set<User*> users = ds.getUsers();
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            /*  Add support for other commands here */
            else if (cmd == "ADD") {
                string username;
                size_t hit_result_index;
                ss >> username >> hit_result_index;
                // Check for missing or invalid inputs
                if (ss.fail() || hit_result_index > hits.size() || hit_result_index < 1) {
                    cout << "Invalid request" << endl;
                    continue;
                }

                // Find user by username
                bool found = false;
                for (User* u : users) {
                    if (convToLower(u->getName()) == convToLower(username)) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Invalid request" << endl;
                    continue;
                }

                username = convToLower(username);
                // Check if the user exists in the cart
                if (carts.find(username) == carts.end()) {
                    carts[username] = std::queue<Product*>();  
                }
                // Add the product to the user's cart
                carts[username].push(hits[hit_result_index - 1]); 

                // cout << "Product added to " << username << "'s cart." << endl;
            } else if (cmd == "VIEWCART") {
            // VIEWCART username command which should print the products in username's cart at the current time. 
            // The items should be printed with some ascending index number so it is easy to tell how many items 
            // are in the cart. 
            // If the username provided is invalid, print Invalid username 
                string username;
                ss >> username;

                if (ss.fail() || carts.find(convToLower(username)) == carts.end()) {
                    cout << "Invalid username" << endl;
                    continue;
                }
                username = convToLower(username);

                std::queue<Product*> prods = carts[username];

                std::queue<Product*> tempQueue = prods; // Preserve original queue
                int index = 0;
                while (!tempQueue.empty()) {
                    index++;
                    cout << "Item " << index << endl << tempQueue.front()->displayString() << endl; // Access front element
                    tempQueue.pop(); // Remove processed element
                }
            } else if (cmd == "BUYCART") {
                string username;
                ss >> username;

                if (ss.fail()) {
                    cout << "Invalid username" << endl;
                    continue;
                }
                User* user = nullptr;
                
                for (User* u : users) {
                    if (convToLower(u->getName()) == username) {
                        user = u;
                        break;
                    }
                }
                
                if (user == nullptr) {
                    cout << "Invalid username" << endl;
                    continue;
                }
                

                if (carts.find(convToLower(username)) == carts.end()) {
                    cout << "Invalid request" << endl;
                    continue;
                }
                username = convToLower(username);   

                std::queue<Product*> user_cart = carts[username];
                std::queue<Product*> tempQueue;
                

                while (!user_cart.empty()) {
                    Product* front = user_cart.front();
                    user_cart.pop();
                    if (front->getQty() > 0 && user->getBalance() >= front->getPrice()) {
                        front->subtractQty(1);
                        user->deductAmount(front->getPrice());
                    } else {
                        tempQueue.push(front);  // Keep items that couldn't be purchased
                    }
                }

                carts[username] = tempQueue;
            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
