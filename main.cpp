#include <iostream>

using namespace std;
//-----------------------------person-----------------------------
class Person {
public:
    string firstname, lastname , gender;
    int birthyear, nationalid;

    // Parameterized constructor
    Person(string firstname2, string lastname2, int nationalid2, int birthyear2, string gender2)
            : firstname(firstname2), lastname(lastname2), nationalid(nationalid2), birthyear(birthyear2), gender(gender2) {}

    //Destructor
    ~Person() {}

    void showInfo() {
        cout << "First Name: " << firstname << "\nLast Name: " << lastname
             << "\nNational ID: " << nationalid << "\nBirth Year: " << birthyear
             << "\nGender: " << gender << endl;
    }
};
//-----------------------------Customer-----------------------------
class Customer : public Person {
public:
    string province , city ;
    int customerid;
    // Default constructor
    Customer() : Person("", "", 0, 0, ""), customerid(0), province(""), city("") {}
    // Parameterized constructor
    Customer(string firstname2, string lastname2, int nationalid2, int birthyear2, string gender2, int customerid2, string province2, string city2)
            : Person(firstname2, lastname2, nationalid2, birthyear2, gender2), customerid(customerid2), province(province2), city(city2) {
    }
    //Destructor
    ~Customer() {}

    void showInfo() {
        Person::showInfo();
        cout << "Customer ID: " << customerid << "\nProvince: " << province << "\nCity: " << city << endl;
    }
};
//-----------------------------Product-----------------------------
class Product {
public:
    int productid;
    string name, brand;
    double price, weight;
    // Default constructor
    Product() : productid(0), name(""), price(0.0), brand(""), weight(0.0) {}
    // Parameterized constructor
    Product(int productid2, string name2, double price2 , string brand2, double weight2)
            : productid(productid2), name(name2), price(price2), brand(brand2), weight(weight2) {}
    //Destructor
    ~Product() {}

    void showInfo() {
        cout << "Product ID: " << productid << "\nName: " << name << "\nPrice: " << price
             << "\nBrand: " << brand << "\nWeight: " << weight << endl;
    }
};
//-----------------------------Dealer-----------------------------
class Dealer {
public:
    int dealerid, establishmentyear;
    string name, economicode, ownerfirstname, ownerlastname, province, city;
    // Default constructor
    Dealer() : dealerid(0), establishmentyear(0), name(""), economicode(""),
               ownerfirstname(""), ownerlastname(""), province(""), city("") {}
    // Parameterized constructor
    Dealer(int dealerid2, string name2 , int establishmentyear2, string economicode2, string ownerfirstname2, string ownerlastname2 , string province2 , string city2)
            : dealerid(dealerid2), name(name2), establishmentyear(establishmentyear2), economicode(economicode2),
              ownerfirstname(ownerfirstname2), ownerlastname(ownerlastname2), province(province2), city(city2) {}
    //Destructor
    ~Dealer() {}

    void showInfo() {
        cout << "\nDealer ID: " << dealerid << "\nName: " << name
             << "\nEstablishment Year: " << establishmentyear << "\nEconomic Code: " << economicode
             << "\nOwner: " << ownerfirstname << " " << ownerlastname << "\nLocation: " << province << " - " << city;
    }
};
//-----------------------------Purchase-----------------------------
class Purchase {
public:
    Customer *customer; Product *product ; Dealer *dealer;
    int quantity; string purchasedate;
    // Default constructor
    Purchase() : customer(nullptr), product(nullptr), dealer(nullptr), quantity(0), purchasedate("") {}
    // Parameterized constructor
    Purchase(Customer* Customer2, Product* Product2, Dealer* Dealer2, int quantity2, string purchasedate2)
            : customer(Customer2), product(Product2), dealer(Dealer2), quantity(quantity2 > 0 ? quantity2 : 1), purchasedate(purchasedate2) {}
    //Destructor
    ~Purchase() {}

    void showInfo() {
        if (customer) customer->showInfo();
        if (product) product->showInfo();
        if (dealer) dealer->showInfo();
        cout << "Quantity: " << quantity << "\nPurchase Date: " << purchasedate ;
    }
};
// Customer management variables:
Customer** customers = nullptr;  // Pointer to array of customer pointers (initially null)
int customerCount = 0;          // Current number of customers in the system
int customerCapacity = 100;     // Maximum capacity of customers array

// Product management variables:
Product** products = nullptr;   // Pointer to array of product pointers (initially null)
int productCount = 0;           // Current number of products in the system
int productCapacity = 100;      // Maximum capacity of products array

// Dealer management variables:
Dealer** dealers = nullptr;     // Pointer to array of dealer pointers (initially null)
int dealerCount = 0;            // Current number of dealers in the system
int dealerCapacity = 100;       // Maximum capacity of dealers array

// Purchase management variables:
Purchase** purchases = nullptr; // Pointer to array of purchase pointers (initially null)
int purchaseCount = 0;          // Current number of purchases in the system
int purchaseCapacity = 100;     // Maximum capacity of purchases array
//-----------------------------1. Add a Product-----------------------------
void addProduct() {
    if (productCount >= productCapacity) {
        cout << "Product capacity is full!"<<endl;
        return;
    }

    int productid;
    string name, brand;
    double price, weight;
    cout << "Product ID: "; cin >> productid;
    //Check duplicate id
    for (int i = 0; i < productCount; ++i)
        if (products[i]->productid == productid) {
            cout << " Product ID already entered."<<endl;
            return;
        }

    cout << "Name: "; cin >> name;

    while (true) {
        cout << "price (> 0) 0=cancel: ";
        cin >> price;
        if (price > 0) break;
        else if (price == 0)return;
            cout << "Invalid."<<endl;

    }
    cout << "Brand: "; cin >> brand;

    while (true) {
        cout << "weight (> 0) 0=cancel: "; cin >> weight;
        if (weight > 0) break;
        else if (weight == 0)return;
        cout << "Invalid."<<endl;
    }
    //new product
    products[productCount++] = new Product(productid, name, price, brand, weight);
    cout << "Product added."<<endl;
}
//-----------------------------2. Remove a Product-----------------------------
void removeProduct() {
    int id;
    cout << "Product ID: "; cin >> id;
    //find the product
    int indexToRemove = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i]->productid == id) {
            indexToRemove = i;
            break;
        }
    }
    if (indexToRemove == -1) {
        cout << "Not found!"<<endl;
        return;
    }
    // delete related purchases
    for (int i = 0; i < purchaseCount;) {
        if (purchases[i]->product != nullptr && purchases[i]->product->productid == id) {
            delete purchases[i];
            for (int j = i; j < purchaseCount - 1; j++)
                purchases[j] = purchases[j + 1];
            purchaseCount--;
        } else {
            i++;
        }
    }
    //delete product
    delete products[indexToRemove];
    for (int i = indexToRemove; i < productCount - 1; i++)
        products[i] = products[i + 1];
    productCount--;

    cout << "Product and related purchases removed."<<endl;
}
//-----------------------------3. Add a Customer-----------------------------
void addCustomer() {
    if (customerCount >= customerCapacity) {
        cout << "Customer capacity is full!"<<endl;
        return;
    }
    string firstName, lastName, gender, province, city;
    int birthYear, nationalID, customerID;
    cout << "Enter National ID: "; cin >> nationalID;
    //Check duplicate id
    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->nationalid == nationalID) {
            cout << "National ID already entered."<<endl;
            return;
        }
    }

    cout << "Customer ID: "; cin >> customerID;
    cout << "First Name: "; cin >> firstName;
    cout << "Last Name: "; cin >> lastName;
    cout << "Gender: "; cin >> gender;

    while (true) {
        cout << "Birth Year (1300< 1403>): "; cin >> birthYear;
        if (birthYear >= 1300 && birthYear <= 1403) break;
        cout << "Invalid."<<endl;
    }

    cout << "Province: "; cin >> province;
    cout << "City: "; cin >> city;

    customers[customerCount++] = new Customer(firstName, lastName, nationalID, birthYear, gender, customerID, province, city);
    cout << "Customer added."<<endl;
}
//-----------------------------4. Remove a Customer-----------------------------
void removeCustomer() {
    int nationalID;
    cout << "National ID: "; cin >> nationalID;
    //find the Customer
    int indexToRemove = -1;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->nationalid == nationalID) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1) {
        cout << "Not found!"<<endl;
        return;
    }
    // delete related purchases
    for (int i = 0; i < purchaseCount;) {
        if (purchases[i]->customer != nullptr && purchases[i]->customer->nationalid == nationalID) {
            delete purchases[i];
            for (int j = i; j < purchaseCount - 1; j++)
                purchases[j] = purchases[j + 1];
            purchaseCount--;
        } else {
            i++;
        }
    }

    // delete customer
    delete customers[indexToRemove];
    for (int i = indexToRemove; i < customerCount - 1; i++)
        customers[i] = customers[i + 1];

    customerCount--;
    cout << "Customer and related purchases removed."<<endl;
}
//-----------------------------5. Add a Dealer-----------------------------
void addDealer() {
    if (dealerCount >= dealerCapacity) {
        cout << "Dealer capacity is full!"<<endl;
        return;
    }

    int dealerID, establishmentYear;
    string name, economicCode, ownerFirstName, ownerLastName, province, city;
    cout << "Dealer ID: "; cin >> dealerID;
    //Check duplicate id
    for (int i = 0; i < dealerCount; i++) {
        if (dealers[i]->dealerid == dealerID) {
            cout << "ID already entered."<<endl;
            return;
        }
    }

    cout << "Name: "; cin >> name;
    while (true) {
        cout << "Establishment Year (1300-1404): "; cin >> establishmentYear;
        if (establishmentYear >= 1300 && establishmentYear <= 1404) break;
        cout << "Invalid year. Try again."<<endl;
    }

    cout << "Economic Code: "; cin >> economicCode;
    cout << "Owner First Name: "; cin >> ownerFirstName;
    cout << "Owner Last Name: "; cin >> ownerLastName;
    cout << "Province: "; cin >> province;
    cout << "City: "; cin >> city;
    //new dealer
    dealers[dealerCount++] = new Dealer(dealerID, name, establishmentYear, economicCode, ownerFirstName, ownerLastName, province, city);
    cout << "Dealer added."<<endl;
}
//-----------------------------6. Remove a Dealer-----------------------------
void removeDealer() {
    int id;
    cout << "Enter Dealer ID to remove: "; cin >> id;

    int indexToRemove = -1;
    for (int i = 0; i < dealerCount; i++) {
        if (dealers[i]->dealerid == id) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1) {
        cout << "Error: Dealer ID not found!"<<endl;
        return;
    }

    // delete related purchases
    for (int i = 0; i < purchaseCount;) {
        if (purchases[i]->dealer != nullptr && purchases[i]->dealer->dealerid == id) {
            delete purchases[i];
            for (int j = i; j < purchaseCount - 1; j++)
                purchases[j] = purchases[j + 1];
            purchaseCount--;
        } else {
            i++;
        }
    }
    // delete dealer
    delete dealers[indexToRemove];
    for (int i = indexToRemove; i < dealerCount - 1; i++)
        dealers[i] = dealers[i + 1];
    dealerCount--;

    cout << "Dealer and related purchases removed."<<endl;
}
// Find customer by national ID
Customer* findCustomerByNationalID(const int& nationalID) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->nationalid == nationalID)
            return customers[i];
    }
    return nullptr;
}

// Find product by ID
Product* findProductByID(int productID) {
    for (int i = 0; i < productCount; i++) {
        if (products[i]->productid == productID)
            return products[i];
    }
    return nullptr;
}

// Find dealer by ID
Dealer* findDealerByID(int dealerID) {
    for (int i = 0; i < dealerCount; i++) {
        if (dealers[i]->dealerid == dealerID)
            return dealers[i];
    }
    return nullptr;
}
//-----------------------------7. Record a Purchase-----------------------------
void recordPurchase() {
    // Check if purchase list is full
    if (purchaseCount >= purchaseCapacity) {
        cout << "Purchase list is full!"<<endl;
        return;
    }

    string purchaseDate;
    int productID, dealerID, quantity, nationalID;

    // Get customer national ID and verify existence
    cout << "Customer National ID: "; cin >> nationalID;
    Customer* cust = findCustomerByNationalID(nationalID);
    if (!cust) { cout << "Not found!"<<endl; return; }

    // Get product ID and verify existence
    cout << "Product ID: "; cin >> productID;
    Product* prod = findProductByID(productID);
    if (!prod) { cout << "Not found!"<<endl; return; }

    // Get dealer ID and verify existence
    cout << "Dealer ID: "; cin >> dealerID;
    Dealer* deal = findDealerByID(dealerID);
    if (!deal) { cout << "Not found!"<<endl; return; }

    // Get and validate quantity (must be positive)
    while(true) {
        cout << "Quantity (>0): ";
        cin >> quantity;
        if (quantity > 0) break;
        else if (quantity == 0) return;  // Exit if quantity is 0
        else cout << "Invalid." << endl;
    }

    // Get purchase date
    cout << "Purchase Date (YYYY/MM/DD): "; cin >> purchaseDate;

    // Create new purchase and add to purchases array
    purchases[purchaseCount++] = new Purchase(cust, prod, deal, quantity, purchaseDate);
    cout << "Purchase recorded."<<endl;
}
//-----------------------------8. Total Purchase of Customer-----------------------------
void totalPurchaseOfCustomer() {
    int nationalID;
    cout << "Customer National ID: "; cin >> nationalID;

    double total = 0;
    bool found = false;  // Flag to check if any purchases were found

    // Iterate through all purchases
    for (int i = 0; i < purchaseCount; i++) {
        // Check if purchase has valid customer and product pointers
        if (purchases[i]->customer != nullptr && purchases[i]->product != nullptr) {
            // Check if current purchase belongs to the requested customer
            if (purchases[i]->customer->nationalid == nationalID) {
                // Add (price * quantity) to the total
                total += purchases[i]->product->price * purchases[i]->quantity;
                found = true;  // Mark that we found at least one purchase
            }
        }
    }

    // Display results based on whether purchases were found
    if (found)
        cout << "Total purchase amount: " << total << endl;
    else
        cout << "No purchases found!" << endl;
}
//-----------------------------9. List of Customers of a Product-----------------------------
void listCustomersOfProduct() {
    int productID;
    cout << "Product ID: "; cin >> productID;

    int uniqueCustomers[100], uniqueCount = 0;
    bool found = false;
    // Search through all purchases
    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->product != nullptr && purchases[i]->customer != nullptr) {
            if (purchases[i]->product->productid == productID) {
                int custID = purchases[i]->customer->nationalid;
                // Check if customer is already in our unique list
                bool alreadyExists = false;
                for (int j = 0; j < uniqueCount; j++) {
                    if (uniqueCustomers[j] == custID) {
                        alreadyExists = true;
                        break;
                    }
                }
                // If new customer, add to list and show their info
                if (!alreadyExists) {
                    uniqueCustomers[uniqueCount++] = custID;
                    purchases[i]->customer->showInfo();
                    found = true;
                }
            }
        }
    }

    if (!found)
        cout << "No customers found!" << productID << endl;
}
//-----------------------------10. Products Sold by a Dealer-----------------------------
void listProductsOfDealer() {
    // Get dealer ID from user
    int dealerID;
    cout << "Dealer ID: "; cin >> dealerID;

    // Arrays to track unique products and count
    int uniqueProducts[100], uniqueCount = 0;
    bool found = false;  // Flag to check if any products were found

    // Search through all purchases
    for (int i = 0; i < purchaseCount; i++) {
        // Check for valid dealer and product pointers
        if (purchases[i]->dealer != nullptr && purchases[i]->product != nullptr) {
            // Check if purchase matches requested dealer
            if (purchases[i]->dealer->dealerid == dealerID) {
                int prodID = purchases[i]->product->productid;

                // Check for duplicate products
                bool duplicate = false;
                for (int j = 0; j < uniqueCount; j++) {
                    if (uniqueProducts[j] == prodID) {
                        duplicate = true;
                        break;
                    }
                }

                // Add new unique product to list
                if (!duplicate) {
                    uniqueProducts[uniqueCount++] = prodID;
                    found = true;
                }
            }
        }
    }

    // Exit if no products found
    if (!found) {
        cout << "No products found!" << endl;
        return;
    }

    // Display all unique products
    cout << "\nProducts sold by dealer ID " << dealerID << ":"<<endl;
    for (int i = 0; i < uniqueCount; i++) {
        // Find and display each product's info
        for (int j = 0; j < productCount; j++) {
            if (products[j]->productid == uniqueProducts[i]) {
                products[j]->showInfo();
                break;
            }
        }
    }
}
//-----------------------------11. Number of Sales of a Product-----------------------------
// Calculates and displays total sales quantity for a specific product
void countSalesOfProduct() {
    // Get product ID from user input
    int productID;
    cout << "Product ID: "; cin >> productID;

    int totalQuantity = 0;  // Accumulator for total sales quantity
    bool found = false;     // Flag to track if product was found in any purchase

    // Iterate through all purchases
    for (int i = 0; i < purchaseCount; i++) {
        // Check if purchase has a valid product reference
        if (purchases[i]->product != nullptr) {
            // Check if current purchase matches the requested product
            if (purchases[i]->product->productid == productID) {
                totalQuantity += purchases[i]->quantity;  // Add to total
                found = true;  // Mark product as found
            }
        }
    }

    // Display results
    if (found)
        cout << "Total sales quantity: " << totalQuantity << endl;
    else
        cout << "No sales found for this product" << endl;
}
//-----------------------------12. Products Purchased by a Customer-----------------------------
// Lists all products purchased by a specific customer
void listPurchasesOfCustomer() {
    // Get customer's national ID from user input
    int nationalID;
    cout << "Customer National ID: "; cin >> nationalID;

    bool found = false;  // Flag to track if any purchases were found
    cout << "Products purchased by customer " << nationalID << ":" << endl;

    // Iterate through all purchases
    for (int i = 0; i < purchaseCount; i++) {
        // Check if purchase has valid customer and product references
        if (purchases[i]->customer != nullptr && purchases[i]->product != nullptr) {
            // Check if current purchase matches the requested customer
            if (purchases[i]->customer->nationalid == nationalID) {
                // Display product information and quantity
                purchases[i]->product->showInfo();
                cout << "Quantity: " << purchases[i]->quantity << endl;
                found = true;  // Mark that at least one purchase was found
            }
        }
    }

    // Display message if no purchases were found
    if (!found)
        cout << "No purchases found!" << endl;
}
//-----------------------------13.Sales Report by Dealer-----------------------------
// Generates a sales report showing total sales for each dealer
void salesReportByDealer() {
    // Loop through all dealers
    for (int i = 0; i < dealerCount; i++) {
        double totalSales = 0;  // Initialize sales accumulator for current dealer

        // Check all purchases to find those associated with this dealer
        for (int j = 0; j < purchaseCount; j++) {
            // Verify purchase has valid dealer and product references
            if (purchases[j]->dealer != nullptr &&
                purchases[j]->product != nullptr &&
                // Check if purchase belongs to current dealer
                purchases[j]->dealer->dealerid == dealers[i]->dealerid) {
                // Calculate and add to total sales (price × quantity)
                totalSales += purchases[j]->product->price * purchases[j]->quantity;
            }
        }

        // Print dealer information and their total sales
        cout << "Dealer: " << dealers[i]->name
             << " (ID: " << dealers[i]->dealerid << ")" << endl;
        cout << "Total Sales: " << totalSales << endl;
    }
}

// Frees all dynamically allocated memory in the system
void freeMemory() {
    // Delete all individual Customer objects
    for (int i = 0; i < customerCount; i++)
        delete customers[i];  // Free each Customer object

    // Delete all individual Product objects
    for (int i = 0; i < productCount; i++)
        delete products[i];   // Free each Product object

    // Delete all individual Dealer objects
    for (int i = 0; i < dealerCount; i++)
        delete dealers[i];    // Free each Dealer object

    // Delete all individual Purchase objects
    for (int i = 0; i < purchaseCount; i++)
        delete purchases[i];  // Free each Purchase object

    // Free the memory allocated for the arrays of pointers
    delete[] customers;   // Free Customer pointer array
    delete[] products;    // Free Product pointer array
    delete[] dealers;     // Free Dealer pointer array
    delete[] purchases;   // Free Purchase pointer array

    // Set all pointers to nullptr to prevent dangling references
    customers = nullptr;
    products = nullptr;
    dealers = nullptr;
    purchases = nullptr;

    // Note: Count variables are not reset here as the function is typically called before program termination
}
void showInfo() {
    cout << "----------Menu----------"<<endl;
    cout << "1. Add Product"<<endl;
    cout << "2. Remove Product"<<endl;
    cout << "3. Add Customer"<<endl;
    cout << "4. Remove Customer"<<endl;
    cout << "5. Add Dealer"<<endl;
    cout << "6. Remove Dealer"<<endl;
    cout << "7. Record Purchase"<<endl;
    cout << "8. Total Purchase of Customer"<<endl;
    cout << "9. List Customers of Product"<<endl;
    cout << "10. List Products of Dealer"<<endl;
    cout << "11. Number of Sales of a Product"<<endl;
    cout << "12. List Purchases of Customer"<<endl;
    cout << "13. Sales Report by Dealer"<<endl;
    cout << "14. Exit"<<endl;
    cout << "Enter your choice: ";
}
int main() {
    // Initialize system capacities and create empty arrays for all entities

// Set customer capacity and allocate memory for customer array
    customerCapacity = 100;
    customers = new Customer*[customerCapacity];

// Set product capacity and allocate memory for product array
    productCapacity = 100;
    products = new Product*[productCapacity];

// Set dealer capacity and allocate memory for dealer array
    dealerCapacity = 100;
    dealers = new Dealer*[dealerCapacity];

// Set purchase capacity and allocate memory for purchase array
    purchaseCapacity = 100;
    purchases = new Purchase*[purchaseCapacity];

// Initialize all counters to zero (no entries yet)
    customerCount = productCount = dealerCount = purchaseCount = 0;
    int choice;
    while (true) {
        showInfo();
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: addCustomer(); break;
            case 4: removeCustomer(); break;
            case 5: addDealer(); break;
            case 6: removeDealer(); break;
            case 7: recordPurchase(); break;
            case 8: totalPurchaseOfCustomer(); break;
            case 9: listCustomersOfProduct(); break;
            case 10: listProductsOfDealer(); break;
            case 11: countSalesOfProduct(); break;
            case 12: listPurchasesOfCustomer(); break;
            case 13: salesReportByDealer(); break;
            case 14:cout << "Exiting program."<<endl;
                freeMemory();
                return 0;
            default:cout << "Invalid choice, please try again."<<endl;
        }
    }
}
