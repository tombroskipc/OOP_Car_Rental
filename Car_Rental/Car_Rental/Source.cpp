#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class BookAndRent {
	virtual string serviceType() = 0;
	virtual string detailedServiceType() = 0;
	virtual void printInformation() = 0;
};

class Driver {
protected:
	string customerName;
	string customerVehicle;
	string phoneNumber;
	string email;
	string driverLicense;
	string paymentMethod;

public:
	static int numofDrivers;

	Driver(string customerName, string customerVehicle, string phoneNumber, string email, string driverLicense, string paymentMethod)
		: customerName(customerName), customerVehicle(customerVehicle), phoneNumber(phoneNumber), email(email), driverLicense(driverLicense), paymentMethod(paymentMethod) {
		Driver::numofDrivers++;
	}

	string getUserName() { return customerName; }

	string getVehicleType() { return customerVehicle; }

	string getPhoneNumber() { return phoneNumber; }

	string getEmail() { return email; }

	string getDriverLicense() { return driverLicense; }

	void printInformation() {
		cout << endl;
		cout << "Name: " << this->customerName << endl;
		cout << "Vehicle: " << this->customerVehicle << endl;
		cout << "Phone number: " << this->phoneNumber << endl;
		cout << "Email address: " << this->email << endl;
		cout << "Driver license: " << this->driverLicense << endl;
		cout << "Payment method: " << this->paymentMethod << endl;
	}
};

int Driver::numofDrivers = 0;

/**Service code
 * 0123 - year
 * 45 - month
 * 67 - day
 * 8 and 9 service code
 * 8th (E - Engine, T - Transmission, W - Tires(Wheels))
 * 9th Engine(O - oil change, I - minor, A - major)
 * 9th Transmission (F - fluid change, M - minor, O - Overhaul)
 * 9th Tires (A - adjustment, R - replacement)
 */

class ServiceHistory {
protected:
	string serviceID;
public:
	

	ServiceHistory(string serviceID)
		: serviceID(serviceID) {};

	void displayTime(string Time) {
		cout << Time[0] << Time[1] << Time[2] << Time[3] << ":"
			<< Time[4] << Time[5] << ":"
			<< Time[6] << Time[7];
	}

	int getServiceTime() {
		if (serviceID == "")
			return 0;
		return stoi(serviceID);
	}

	std::string getServiceID() const { return serviceID; }
	void setServiceID(std::string val) { serviceID = val; }

	virtual string serviceType() {
		return "None";
	}
	virtual string detailedServiceType() {
		return "None";
	}
	virtual void printInformation() {
		cout << "No Service found";
	}
};

class ServiceEngine : public ServiceHistory {
private:
	bool oilChange = false;
	bool minor = false;
	bool major = false;
public:


	ServiceEngine(string serviceID)
		: ServiceHistory(serviceID) {
		if (serviceID[9] == 'O')
			this->oilChange = true;
		else if (serviceID[9] == 'I')
			this->minor = true;
		else if (serviceID[9] == 'A')
			this->major = true;
	}
	
	string serviceType() {
		return "Engine";
	}

	string detailedServiceType() {
		if (this->oilChange)
			return "Oil Change";
		else if (this->minor)
			return "Minor";
		else if (this->major)
			return "Major";
		return "Unknown";
	}

	void printInformation() {
		cout << "Engine Service type: " << detailedServiceType();
		cout << endl;
		cout << "Service time: ";
		this->displayTime(serviceID);
		cout << endl;
	}

};

class ServiceTransmission : public ServiceHistory {
private:
	bool fluidChange = false;
	bool minor = false;
	bool overhaul = false;
public:
	
	ServiceTransmission(string serviceID)
		: ServiceHistory(serviceID) {
		if (serviceID[9] == 'F')
			this->fluidChange = true;
		else if (serviceID[9] == 'M')
			this->minor = true;
		else if (serviceID[9] == 'O')
			this->overhaul = true;
	}

	string serviceType() {
		return "Transmission";
	}

	string detailedServiceType() {
		if (this->fluidChange)
			return "Fluid Change";
		else if (this->minor)
			return "Minor";
		else if (this->overhaul)
			return "Overhaul";
		return "Unknown";
	}

	void printInformation() {
		cout << "Transmission Service type: " << detailedServiceType();
		cout << endl;
		cout << "Service time: ";
		this->displayTime(serviceID);
		cout << endl;
	}
};

class ServiceTire : public ServiceHistory {
private:
	bool adjusment = false;
	bool replacement = false;
public:

	ServiceTire(string serviceID)
		: ServiceHistory(serviceID) {
		if (serviceID[9] == 'A')
			this->adjusment = true;
		else if (serviceID[9] == 'R')
			this->replacement = true;
	}

	string serviceType() {
		return "Tire";
	}

	string detailedServiceType() {
		if (this->adjusment)
			return "Adjustment";
		else if (this->replacement)
			return "Replacement";
		return "Unknown";
	}

	void printInformation() {
		cout << "Tire Service type: " << detailedServiceType();
		cout << endl;
		cout << "Service time: ";
		this->displayTime(serviceID);
		cout << endl;
	}
};

class Vehicle {
protected:
	string color;
	int year_release;
	vector<ServiceHistory*> serviceRecord;

public:
	static int numOfCars;
	Vehicle(string color, int year_release)
		: color(color), year_release(year_release)
	{
		Vehicle::numOfCars++;
	};
	Vehicle(vector<string> serviceHistory, string color, int year_release)
		: color(color), year_release(year_release)
	{
		organizeService(serviceHistory);
		Vehicle::numOfCars++;
	};



	static void show_option() {
		cout << "\tDifferent options " << endl;
		cout << "\t\t 1. SUV" << endl;
		cout << "\t\t 2. Sedan" << endl;
		cout << "\t\t 3. luxury car" << endl;
	}

	void organizeService(vector<string> serviceVector) {
		for (unsigned int i = 0; i < serviceVector.size(); i++) {
			if (serviceVector[i][8] == 'E') {
				ServiceEngine* newData = new ServiceEngine(serviceVector[i]);
				serviceRecord.push_back(newData);
			}
			else if (serviceVector[i][8] == 'T') {
				ServiceTransmission* newData = new ServiceTransmission(serviceVector[i]);
				serviceRecord.push_back(newData);
			}
			else if (serviceVector[i][8] == 'W') {
				ServiceTire* newData = new ServiceTire(serviceVector[i]);
				serviceRecord.push_back(newData);
			}
		}
	}

	virtual void printInformation() = 0;


	void showServiceHistory() {
		cout << "Service History: " << endl;
		for (unsigned int i = 0; i < serviceRecord.size(); i++)
			serviceRecord[i]->printInformation();
	}
};
int Vehicle::numOfCars = 0;

class SUV : public Vehicle {
protected:

public:
	SUV(string color, int year_release)
		: Vehicle(color, year_release) {}

	SUV(vector<string> serviceHistory, string color, int year_release)
		: Vehicle(serviceHistory, color, year_release) {}

	void printInformation() {
		cout << endl << "Rent a " << color << " SUV from " << year_release << endl;
		if (this->serviceRecord.size() == 0)
			cout << "This car has never been Maintained";
		else
			this->showServiceHistory();
	}
};

class Sedan : public Vehicle {
public:
	Sedan(string color, int year_release)
		: Vehicle(color, year_release) {}

	Sedan(vector<string> serviceHistory, string color, int year_release)
		: Vehicle(serviceHistory, color, year_release) {}
	void printInformation() {
		cout << endl << "Rent a " << color << " Sedan from " << year_release << endl;
		if (this->serviceRecord.size() == 0)
			cout << "This car has never been Maintained";
		else
			this->showServiceHistory();
	}
};

class LuxuryCar : public Vehicle {
public:
	LuxuryCar(string color, int year_release)
		: Vehicle(color, year_release) {}

	LuxuryCar(vector<string> serviceHistory, string color, int year_release)
		: Vehicle(serviceHistory, color, year_release) {};

	void printInformation() {
		cout << endl << "Rent a " << color << " Luxury Car from " << year_release << endl;
		if (this->serviceRecord.size() == 0)
			cout << "This car has never been Maintained";
		else
			this->showServiceHistory();
	}
};

class RentalContract {
protected:
	Driver* driver;
	int contract_ID;
	string pickedUp_location;
	Vehicle* customerVehicle;
	string pickUp_time;
	string return_time;

public:
	static int numOfContracts;

	RentalContract(Driver* driver, Vehicle* customerVehicle, int contract_ID, string pickedUp_location, string pickUp_time, string return_time)
		:driver(driver), customerVehicle(customerVehicle), contract_ID(contract_ID), pickedUp_location(pickedUp_location), pickUp_time(pickUp_time), return_time(return_time) {
		RentalContract::numOfContracts++;
	}

	int getContract_ID() { return contract_ID; }

	string getPickUp_location() { return pickedUp_location; }

	string getPickUp_time() { return pickUp_time; }

	string getReturn_time() { return return_time; }

	void printInformation() {
		driver->printInformation();
		cout << "contract ID: " << contract_ID << endl;
		cout << "Pick up time: " << pickUp_time << endl;
		cout << "Picked up location: " << pickedUp_location << endl;
		customerVehicle->printInformation();
		cout << endl << endl;
	}

	void printVehicleInformation() {
		customerVehicle->printInformation();
	}
};
int RentalContract::numOfContracts = 0;

Vehicle* initVehicle(string carName, string color, int year_release);
Vehicle* initVehicle(vector<string> serviceHistory, string carName, string color, int year_release);
Driver* initCustomer(string name, string vehicle, string email, string phoneNumber, string driverLicense, string paymentMethod);

int main() {
	vector<string> car_1_service = {
		"20190105EO",
		"20190106TO",
		"20201230WR",
		"20070105EI",
		"20060107TF",
		"20201230WA"
	};

	vector<string> car_2_service = {
		"20070105EI",
		"20060107TF",
		"20201230WA"
	};

	vector<string> car_3_service = {
		"20190105EA",
		"20190106TM",
		"20201230WR"
	};

	Vehicle::show_option();
	Driver* driver_1 = initCustomer("Sheldon", "SUV", "0999999", "Sheldon_Copper@bazingga.biz", "pasedenaLicense999", "Credit Card");
	Vehicle* car_1 = initVehicle(car_1_service, "SUV", "Black", 1994);
	Driver* driver_2 = initCustomer("Leonard", "Sedan", "011111", "Leonard_Hofstadter@bazingga.biz", "pasedenaLicense1", "Credit Card");
	Vehicle* car_2 = initVehicle(car_2_service, "Sedan", "White", 1969);
	Driver* driver_3 = initCustomer("Sheldon", "LuxuryCar", "0999999", "Penny_Hofstadter@bazingga.biz", "pasedenaLicense998", "Cash");
	Vehicle* car_3 = initVehicle("LuxuryCar", "Red", 2021);

	RentalContract* contractSheldon = new RentalContract(driver_1, car_1, 1, "Texas", "02:08:2021", "04:08:2021");
	RentalContract* contractLeonard = new RentalContract(driver_2, car_2, 2, "New Jersey", "03:08:2021", "05:08:2021");
	RentalContract* contractPenny = new RentalContract(driver_3, car_3, 3, "Texas", "10:08:2021", "11:08:2021");

	contractSheldon->printInformation();
	contractLeonard->printInformation();
	contractPenny->printInformation();

	cout << endl << "Number of drivers: " << Driver::numofDrivers;
	cout << endl << "Number of car being rented: " << Vehicle::numOfCars;
};

Vehicle* initVehicle(string carName, string color, int year_release) {

	Vehicle* newCar;
	if (carName == "SUV")
		newCar = new SUV(color, year_release);
	else if (carName == "Sedan") {
		newCar = new Sedan(color, year_release);
	}
	else
		newCar = new LuxuryCar(color, year_release);

	return newCar;
}

Vehicle* initVehicle(vector<string> serviceHistory, string carName, string color, int year_release) {
	Vehicle* newCar;
	if (carName == "SUV")
		newCar = new SUV(serviceHistory, color, year_release);
	else if (carName == "Sedan")
		newCar = new Sedan(serviceHistory, color, year_release);
	else
		newCar = new LuxuryCar(serviceHistory, color, year_release);

	return newCar;
}

Driver* initCustomer(string name, string vehicle, string phoneNumber, string email, string driverLicense, string paymentMethod) {
	Driver* driver = new Driver(name, vehicle, phoneNumber, email, driverLicense, paymentMethod);
	return driver;
}