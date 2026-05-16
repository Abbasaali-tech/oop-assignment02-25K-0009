#include <iostream>
using namespace std;

class Printable {
public:
    virtual void displayInfo() const = 0;

    virtual ~Printable() {}
};

class Engine {
    string fuelType;
    int horsepower;
    string gearbox;
public:
    Engine() {
        fuelType = "Petrol";
        horsepower = 85;
        gearbox = "Manual";
    }
    Engine(string fuel, int hp, string gb) {
        fuelType = fuel;
        horsepower = hp;
        gearbox = gb;
    }
    string getFuelType() const { 
        return fuelType; 
    }
    int getHorsepower() const { 
        return horsepower; 
    }
    string getGearbox() const { 
        return gearbox; 
    }
    void print() const {
        cout << "Fuel: " << fuelType << " HorsePower: " << horsepower << " Gearbox: " << gearbox << endl;
    }
};

class Location {
    string city;
    string area;
public:
    Location() { 
        city = "Unknown";
        area = "Unknown"; 
    }

    Location(string c, string a) { 
        city = c; 
        area = a; 
    }



    string getCity() const { 
        return city; 
    }
    string getArea() const { 
        return area; 
    }
};

class Vehicle :   public Printable {
protected:
    string brand;
    string model;
    int year;
    float mileage;
    string color;
    Engine engine;
    Location location;


public:
    Vehicle(string b, string m, int y, float mil, string col, Engine eng, Location loc) : engine(eng), location(loc) {
        brand = b; 
        model = m; 
        year = y; 
        mileage = mil; 
        color = col;
    }


    string getBrand() const { 
        return brand; 
    }
    string getModel() const { 
        return model; 
    }
    int getYear() const { 
        return year; 
    }
    float getMileage() const { 
        return mileage; 
    }
    bool matchesBrand(string b) const { 
        return brand == b; 
    }
    virtual void displayInfo() const = 0;

    virtual ~Vehicle() {}
};

class Car : public Vehicle {
private:
    string bodyType;
    bool hasAC;
    string regNumber;
public:
    Car(string b, string m, int y, float mil, string col, Engine eng, Location loc,string bt, bool ac, string reg) : Vehicle(b, m, y, mil, col, eng, loc) {
        bodyType = bt; 
        hasAC = ac; 
        regNumber = reg;
    }


    string getRegNumber() const { 
        return regNumber; 
    }
    bool getHasAC() const { 
        return hasAC; 
    }

    void displayInfo() const {
        cout << year << " " << brand << " " << model << " " << color << endl;
        cout << "Mileage: " << mileage << " km Type: " << bodyType << endl;
        cout << "AC: ";


        if (hasAC) { 
            cout << "Yes"; 
        } 
        else { 
            cout << "No"; 
        }

        cout << " | Reg: ";
        
        if (regNumber == "") { 
            cout << "Invalid"; 
        } 
        else { 
            cout << regNumber; 
        }

        cout << endl;
        cout << "Engine: "; engine.print();
        cout << "Location: " << location.getArea() << ", " << location.getCity() << endl;
    }
};

class Bike : public Vehicle {
private:
    string bikeType;
    int engineCC;
public:
    Bike(string b, string m, int y, float mil, string col, Engine eng, Location loc,string bt, int cc): Vehicle(b, m, y, mil, col, eng, loc) {
        bikeType = bt; engineCC = cc;
    }


    string getBikeType() const { 
        return bikeType; 
    }
    int getEngineCC() const { 
        return engineCC; 
    }


    void displayInfo() const {
        cout << year << " " << brand << " " << model << " " << color << endl;
        cout << "Mileage: " << mileage << " km Type: " << bikeType << " CC: " << engineCC << endl;
        cout << "Engine: "; engine.print();
        cout << "Location: " << location.getArea() << ", " << location.getCity() << endl;
    }
};

class Message {
    string fromUser;
    string toUser;
    string text;
    bool isRead;
    friend class Seller;
public:
    Message(string from, string to, string content) {
        fromUser = from; 
        toUser = to; 
        text = content; 
        isRead = false;
    }
    void print() const {
        cout << fromUser << ": " << text << endl;
    }
};

class CmpResult  {
    int car1Wins;
    int car2Wins;
    int ties;
    friend class CarComparator;
public:


    CmpResult() { 
        car1Wins = 0; 
        car2Wins = 0; 
        ties = 0; 
    }
    int getCar1Wins() const { 
        return car1Wins; 
    }

    int getCar2Wins() const { 
        return car2Wins; 
    }

    int getTies() const { 
        return ties; 
    }

    bool operator==(const CmpResult& other) const {
        return car1Wins == other.car1Wins && car2Wins == other.car2Wins && ties == other.ties;
    }
    CmpResult operator+(const CmpResult& other) const {
        CmpResult combined;
        combined.car1Wins = car1Wins + other.car1Wins;
        combined.car2Wins = car2Wins + other.car2Wins;
        combined.ties = ties + other.ties;
        return combined;
    }
};

class Listing : public Printable {
    static int totalListings;
    static const float fee;
    string listingID;
    Vehicle* vehicle;
    long long price;
    string status;
    string datePosted;
    string sellerID;
    friend class CarComparator;
    friend class Admin;
public:
    Listing(string id, Vehicle* v, long long p, string date, string seller) {
        listingID = id; 
        vehicle = v; 
        price = p;
        datePosted = date; 
        sellerID = seller;
        status = "Pending";
        totalListings++;
    }
    ~Listing() { totalListings--; }

    static int getTotalListings() { 
        return totalListings; 
    }

    static float getPlatformFee() { 
        return fee; 
    }

    string getListingID() const { 
        return listingID; 
    }
    long long getPrice() const { 
        return price; 
    }
    Vehicle* getVehicle() const { 
        return vehicle; 
    }
    string getStatus() const { 
        return status; 
    }


    void setPrice(long long p) { 
        price = p; 
    }

    void approve() { 
        status = "Approved"; 
    }


    void reject() { 
        status = "Rejected"; 
    }

    bool isAvailable() const {
        if (status == "Approved") { 
            return true; 
        } 
        else { 
            return false; 
        }

    }


    bool inPriceRange(long long minP, long long maxP) const {
        return price >= minP && price <= maxP;
    }

    bool operator<(const Listing& other) const { 
        return price < other.price; 
    }
    bool operator==(const Listing& other) const { 
        return listingID == other.listingID; 
    }

    void displayInfo() const {
        cout << "ID: " << listingID << " Price: PKR " << price << status << endl;
        cout << "Posted: " << datePosted << endl;
        if (vehicle != nullptr) { 
            vehicle->displayInfo(); 
        }
    }
};

int Listing::totalListings = 0;
const float Listing::fee = 500.0;

class Favorite {
    Listing* savedListing;
    string buyerID;
    string dateSaved;
    friend class Buyer;
public:
    Favorite(Listing* l, string buyer, string date) {
        savedListing = l; 
        buyerID = buyer; 
        dateSaved = date;
    }
    bool isStillAvailable() const {
        if (savedListing != nullptr && savedListing->isAvailable()) { 
            return true;
        } 
        else { 
            return false;
        }
    }
};



class Person : public   Printable {
protected:
    static int totalUsers;
    string personID;
    string name;
    string email;
    string phone;
    string password;
public:
    Person(string id, string n, string e, string ph, string pass) {
        personID = id; 
        name = n; 
        email = e; 
        phone = ph; 
        password = pass;
        totalUsers++;
    }
    virtual ~Person() { 
        totalUsers--; 
    }

    string getPersonID() const { 
        return personID;
    }
    string getName() const { 
        return name;
    }
    static int getTotalUsers() { 
        return totalUsers;
    }

    void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
    }
    virtual string getRole() const { 
        return "Person"; 
    }
};

int Person::totalUsers = 0;

class Seller : public Person {
private:
    Listing* listings[50];
    int listingCount;
    Message* inbox[50];
    int msgCount;
public:
    Seller(string id, string n, string e, string ph, string pass) : Person(id, n, e, ph, pass) {
        listingCount = 0;
        msgCount = 0;
    }
    void addListing(Listing* l) {
        if (listingCount < 50) { 
            listings[listingCount] = l; listingCount++; 
        }
    }
    void receiveMessage(Message* m) {
        if (msgCount < 50) { 
            inbox[msgCount] = m; msgCount++; 
        }
    }
    void viewMessages() {
        if (msgCount == 0) { 
            cout << name << " has no messages." << endl; return; 
        }
        cout << "Inbox:" << endl;
        for (int i = 0; i < msgCount; i++) {
            inbox[i]->print();
            inbox[i]->isRead = true;
        }
    }
    string getRole() const { 
        return "Seller"; 
    }
};

class Buyer : public Person {
private:
    Favorite* favorites[50];
    int favCount;
public:
    long long budget;
    string preferredCity;

    Buyer(string id, string n, string e, string ph, string pass) : Person(id, n, e, ph, pass) {
        favCount = 0; budget = 0; preferredCity = "Any";
    }
    void saveListing(Listing* l, string date) {
        if (favCount < 50) {
            favorites[favCount] = new Favorite(l, personID, date);
            favCount++;
        }
    }
    void showSaved() const {
        cout << name << "'s saved listings:" << endl;
        for (int i = 0; i < favCount; i++) {
            if (favorites[i]->savedListing != nullptr) {
                favorites[i]->savedListing->displayInfo();
            }
        }
    }
    void sendMessage(Seller& seller, string content) {
        Message* msg = new Message(personID, seller.getPersonID(), content);
        seller.receiveMessage(msg);
        cout << name << " messaged " << seller.getName() << endl;
    }
    string getRole() const { 
        return "Buyer"; 
    }
};

class Admin : public Person {
private:
    int totalApprovals;
public:
    Admin(string id, string n, string e, string ph, string pass) : Person(id, n, e, ph, pass) {
        totalApprovals = 0;
    }
    void approveListing(Listing* l) {
        l->approve();
        totalApprovals++;
        cout << "Approved" << endl;
    }
    void rejectListing(Listing* l) {
        l->reject();
        cout << "Rejected" << endl;
    }
    string getRole() const {
        return "Admin"; }
};

class CarComparator {
public:
    CmpResult compare(Listing* l1, Listing* l2) {

        CmpResult result;
        Vehicle* v1 = l1->vehicle;
        Vehicle* v2 = l2->vehicle;

        cout << "\nComparing Cars" << endl;
        cout << "Brand: " << v1->getBrand() << " - " << v2->getBrand() << endl;
        cout << "Model: " << v1->getModel() << " - " << v2->getModel() << endl;
        cout << "Price: " << l1->price << " - " << l2->price << endl;
        cout << "Mileage: " << v1->getMileage() << " - " << v2->getMileage() << endl;

        if (l1->price < l2->price) {
            result.car1Wins++; }
        else if (l2->price < l1->price) { 
            result.car2Wins++; }
        else { 
            result.ties++; }

        if (v1->getMileage() < v2->getMileage()) { 
            result.car1Wins++; }
        else if (v2->getMileage() < v1->getMileage()) { 
            result.car2Wins++; }
        else { 
            result.ties++; }

        double lowerPrice;
        if (l1->price < l2->price){
            lowerPrice = l1->price;
        }
        else{
            lowerPrice = l2->price;
        }
        float lowerMil;
        if (v1->getMileage() < v2->getMileage()){
            lowerMil = v1->getMileage();
        }
        else{
            lowerMil = v2->getMileage();
        }
        cout << "Better Price: " << lowerPrice << endl;
        cout << "Lower Mileage: " << lowerMil << " km" << endl;

        return result;
    }
};

class Marketplace {
private:
    Listing* listings[100];
    int listingCount;
public:
    string name;

    Marketplace(string n) { 
        name = n; 
        listingCount = 0; 
    }

    void addListing(Listing* l) {
        if (listingCount < 100) { 
            listings[listingCount] = l; listingCount++; 
        }
    }

    void updatePrice(string id, long long newPrice) {
        for (int i = 0; i < listingCount; i++) {
            if (listings[i]->getListingID() == id) {
                listings[i]->setPrice(newPrice);
                cout << "Price updated to PKR " << newPrice << endl;
                return;
            }
        }
        cout << "Listing not found" << endl;
    }

    void showApproved() {
        cout << "\nActive listings on " << name << endl;
        for (int i = 0; i < listingCount; i++) {
            if (listings[i]->isAvailable()) { 
                listings[i]->displayInfo(); 
            }
        }
    }

    void searchByBrand(string brand) {
        cout << "\nSearch results for " << brand << ":" << endl;
        bool found = false;
        for (int i = 0; i < listingCount; i++) {
            if (listings[i]->isAvailable() && listings[i]->getVehicle() != nullptr) {
                if (listings[i]->getVehicle()->matchesBrand(brand)) {
                    listings[i]->displayInfo();
                    found = true;
                }
            }
        }
        if (!found) { 
            cout << "Nothing found." << endl; 
        }
    }

    void filterByPrice(long long minP, long long maxP) {
        cout << "\nListings between PKR " << minP << " - " << maxP << ":" << endl;
        bool found = false;
        for (int i = 0; i < listingCount; i++) {
            if (listings[i]->isAvailable()) {
                if (listings[i]->inPriceRange(minP, maxP)) {
                    listings[i]->displayInfo();
                    found = true;
                }
            }
        }
        if (!found) { 
            cout << "Nothing in this range." << endl; 
        }
    }

    void filterByYear(int old, int New) {
        cout << "\nListings from " << old << " to " << New << ":" << endl;
        bool found = false;
        for (int i = 0; i < listingCount; i++) {
            if (listings[i]->isAvailable() && listings[i]->getVehicle() != nullptr) {
                int y = listings[i]->getVehicle()->getYear();
                if (y >= old && y <= New) {
                    listings[i]->displayInfo();
                    found = true;
                }
            }
        }
        if (!found) { 
            cout << "Nothing found." << endl; 
        }
    }

    void filterByMileage(float maxMil) const {
        cout << "\nListings under " << maxMil << " km:" << endl;
        bool found = false;
        for (int i = 0; i < listingCount; i++) {
            if (listings[i]->isAvailable() && listings[i]->getVehicle() != nullptr) {
                if (listings[i]->getVehicle()->getMileage() <= maxMil) {
                    listings[i]->displayInfo();
                    found = true;
                }
            }
        }
        if (!found) { 
            cout << "Nothing found." << endl; 
        }
    }
};

int main() {
    Engine eng1("Petrol", 107, "Automatic");
    Location loc1("Karachi", "Gulshan");
    Car* car1 = new Car("Honda", "City", 2022, 18000.0f, "Pearl White", eng1, loc1, "Sedan", true, "KHI-22-9934");

    Engine eng2("Petrol", 158, "Manual");
    Location loc2("Karachi", "Saddar");
    Car* car2 = new Car("Honda", "Civic", 2020, 47000.0f, "Midnight Black", eng2, loc2, "Sedan", true, "LHR-20-4471");

    Engine eng3("Petrol", 318, "Automatic");
    Location loc3("Karachi", "North Nazimabad");
    Car* car3 = new Car("Toyota", "Land Cruiser", 2018, 85000.0f, "Silver", eng3, loc3, "SUV", true, "ISB-18-0021");

    Engine engB("Petrol", 15, "Manual");
    Location locB("Karachi", "Defence");
    Bike* bike1 = new Bike("Honda", "CD 70", 2021, 12000.0f, "Black", engB, locB, "Standard", 70);

    Seller seller1("S1", "Abbas", "abbas@gmail.com", "03012345678", "abbas123");
    Seller seller2("S2", "Moiz", "moiz@hotmail.com", "03337654321", "moiz999");
    
    
    Buyer buyer1("B1", "Shaheer", "shaheer@gmail.com", "03215566778", "shaheer456");
    buyer1.budget = 5000000;
    buyer1.preferredCity = "Karachi";
    Admin admin1("A1", "Sarim", "admin@pakwheels.pk", "02134567890", "adminpass");

    Listing* l1 = new Listing("LST001", car1, 4850000, "03-01-2025", seller1.getPersonID());
    Listing* l2 = new Listing("LST002", car2, 6200000, "11-02-2025", seller2.getPersonID());
    Listing* l3 = new Listing("LST003", car3, 18500000, "28-03-2025", seller1.getPersonID());
    Listing* l4 = new Listing("LST004", bike1, 150000, "05-04-2025", seller2.getPersonID());

    seller1.addListing(l1); seller1.addListing(l3);
    seller2.addListing(l2); seller2.addListing(l4);

    Marketplace market("Wheels.com");
    market.addListing(l1); market.addListing(l2);
    market.addListing(l3); market.addListing(l4);

    admin1.approveListing(l1); admin1.approveListing(l2);
    admin1.approveListing(l3); admin1.approveListing(l4);

    buyer1.saveListing(l2, "12-02-2025");
    buyer1.sendMessage(seller1, "Bhai City ka koi issue toh nahi?");
    buyer1.sendMessage(seller2, "Civic abhi bhi available hai?");

    seller1.viewMessages();
    seller2.viewMessages();

    market.searchByBrand("Honda");
    market.filterByPrice(4000000, 7000000);
    market.filterByYear(2018, 2022);
    market.filterByMileage(50000.0);
    market.updatePrice("LST001", 4650000);
    market.showApproved();

    buyer1.showSaved();

    cout << "Total Users: " << Person::getTotalUsers() << endl;
    cout << "Total Listings: " << Listing::getTotalListings() << endl;
    cout << "Platform Fee PKR: " << Listing::getPlatformFee() << endl;

    if (*l1 < *l2) { cout << "\nLST001 is cheaper than LST002" << endl; }
    if (!(*l1 == *l2)) { cout << "LST001 and LST002 are different listings." << endl; }

    CarComparator cmp;
    CmpResult result = cmp.compare(l1, l2);
    CmpResult round2 = cmp.compare(l2, l3);
    CmpResult total = result + round2;

    cout << "Combined Car1 Wins: " << total.getCar1Wins() << endl;
    cout << "Combined Car2 Wins: " << total.getCar2Wins() << endl;

    if (result.getCar1Wins() == result.getCar2Wins()) {
        cout << "\nBoth cars are equally matched." << endl;
    } else if (result.getCar1Wins() > result.getCar2Wins()) {
        cout << "\nCar 1 is better overall." << endl;
    } else {
        cout << "\nCar 2 is better overall." << endl;
    }

    delete car1;
    delete car2; 
    delete car3; 
    delete bike1;
    delete l1; 
    delete l2; 
    delete l3; 
    delete l4;

}