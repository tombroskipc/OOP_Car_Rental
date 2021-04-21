#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BookAndRent {
public:
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
	vector<string> serviceHistory;

public:
	ServiceHistory() {};
	ServiceHistory(vector<string> serviceHistory)
		: serviceHistory(serviceHistory) {};
	void displayTime(string Time) {
		cout << Time[0] << Time[1] << Time[2] << Time[3] << ":"
			<< Time[4] << Time[5] << ":"
			<< Time[6] << Time[7];
	}

	std::vector<std::string> getServiceHistory() const { return serviceHistory; }
	void setServiceHistory(std::vector<std::string> val) { serviceHistory = val; }

	void showLastestService(vector<string> m_serviceHistory) {
		if (m_serviceHistory.size() > 0) {
			cout << "Latest Maintainence: ";
			this->displayTime(m_serviceHistory[m_serviceHistory.size() - 1]);
			cout << endl;
		}
		else
			cout << "This car has never been Maintainence" << endl;
	}
	virtual void printInformation() {
		cout << "Service history: " << endl;
		if (serviceHistory.size() > 0) {
			for (unsigned int i = 0; i < serviceHistory.size(); i++) {
				this->displayTime(serviceHistory[i]);
				cout << endl;
			}
		}
		else
			cout << "This car has never been Maintainence" << endl;
	}

	virtual void addService(string serviceCode) {
		serviceHistory.push_back(serviceCode);
	}
	virtual void addServiceVector(vector<string> v) {
		for (unsigned int i = 0; i < v.size(); i++)
			this->addService(v[i]);
	}
};

class ServiceEngine : public ServiceHistory {
private:
	vector<string> oilChange;
	vector<string> minor;
	vector<string> major;
public:

	ServiceEngine() {};

	ServiceEngine(vector<string> serviceEngine) {
		this->addServiceVector(serviceEngine);
	};

	void addService(string serviceCode) {
		this->serviceHistory.push_back(serviceCode);
		if (serviceCode[9] == 'O')
			this->oilChange.push_back(serviceCode);
		else if (serviceCode[9] == 'I')
			this->minor.push_back(serviceCode);
		else if (serviceCode[9] == 'A')
			this->major.push_back(serviceCode);
		else
			cout << "WRONG ENGINE SERVICE CODE" << endl;
	}

	void printInformation() {
		cout << "Engine Service history: " << endl;
		if (this->serviceHistory.size() > 0) {
			for (unsigned int i = 0; i < this->serviceHistory.size(); i++) {
				this->displayTime(this->serviceHistory[i]);
				cout << endl;
			}
		}
		else
			cout << "This car has never been Maintainence Engine" << endl;
	}
};

class ServiceTransmission : public ServiceHistory {
private:
	vector<string> fluidChange;
	vector<string> minor;
	vector<string> overhaul;
public:
	ServiceTransmission() {};
	ServiceTransmission(vector<string> m_serviceHistory) {
		this->addServiceVector(m_serviceHistory);
	}

	void addService(string serviceCode) {
		this->serviceHistory.push_back(serviceCode);
		if (serviceCode[9] == 'F')
			this->fluidChange.push_back(serviceCode);
		else if (serviceCode[9] == 'M')
			this->minor.push_back(serviceCode);
		else if (serviceCode[9] == 'O')
			this->overhaul.push_back(serviceCode);
		else
			cout << "WRONG TRANSMISSION SERVICE CODE" << endl;
	}

	void printInformation() {
		cout << "Engine Service history: " << endl;
		if (this->serviceHistory.size() > 0) {
			for (unsigned int i = 0; i < this->serviceHistory.size(); i++) {
				this->displayTime(this->serviceHistory[i]);
				cout << endl;
			}
		}
		else
			cout << "This car has never been Maintainence Transmission" << endl;
	}
};

class ServiceTire : public ServiceHistory {
private:
	vector<string> adjusment;
	vector<string> replacement;
public:
	ServiceTire() {};

	ServiceTire(vector<string> m_serviceHistory) {
		this->addServiceVector(m_serviceHistory);
	}

	void addService(string serviceCode) {
		this->serviceHistory.push_back(serviceCode);
		if (serviceCode[9] == 'A')
			this->adjusment.push_back(serviceCode);
		else if (serviceCode[9] == 'R')
			this->replacement.push_back(serviceCode);
		else
			cout << "WRONG TRANSMISSION SERVICE CODE" << endl;
	}

	void printInformation() {
		vector<string> serviceTransmission = this->getServiceHistory();
		cout << "Engine Tire history: " << endl;
		if (serviceTransmission.size() > 0) {
			for (unsigned int i = 0; i < serviceTransmission.size(); i++) {
				this->displayTime(serviceTransmission[i]);
				cout << endl;
			}
		}
		else
			cout << "This car has never been Maintainence Tire" << endl;
	}
};

class Vehicle {
protected:
	string color;
	int year_release;
	ServiceHistory* serviceHistory;
	ServiceEngine* serviceEngineHistory = new ServiceEngine();
	ServiceTransmission* serviceTransmissionHistory = new ServiceTransmission();
	ServiceTire* serviceTireHistory = new ServiceTire();

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
		sort(serviceHistory.begin(), serviceHistory.end());
		this->serviceHistory = new ServiceHistory(serviceHistory);
		organizeService(serviceHistory);
		Vehicle::numOfCars++;
	};

	virtual void printInformation() {
		cout << endl << "You haven't picked your car." << endl;
	}

	static void show_option() {
		cout << "\tDifferent options " << endl;
		cout << "\t\t 1. SUV" << endl;
		cout << "\t\t 2. Sedan" << endl;
		cout << "\t\t 3. luxury car" << endl;
	}

	void organizeService(vector<string> serviceRecord) {
		for (unsigned int i = 0; i < serviceRecord.size(); i++) {
			if (serviceRecord[i][8] == 'E')
				serviceEngineHistory->addService(serviceRecord[i]);
			else if (serviceRecord[i][8] == 'T')
				serviceTransmissionHistory->addService(serviceRecord[i]);
			else if (serviceRecord[i][8] == 'W')
				serviceTireHistory->addService(serviceRecord[i]);
		}
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
		if (serviceHistory == nullptr)
			cout << "This car has never been Maintained";
		else
			serviceHistory->printInformation();
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
		if (serviceHistory == nullptr)
			cout << "This car has never been Maintained";
		else
			serviceHistory->printInformation();
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
		if (serviceHistory == nullptr)
			cout << "This car has never been Maintained";
		else
			serviceHistory->printInformation();
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
	if (carName == "SUV") {
		SUV* newCar = new SUV(color, year_release);
		return newCar;
	}
	else if (carName == "Sedan") {
		Sedan* newCar = new Sedan(color, year_release);
		return newCar;
	}
	else if (carName == "LuxuryCar") {
		LuxuryCar* newCar = new LuxuryCar(color, year_release);
		return newCar;
	}
	Vehicle* newCar = new Vehicle(color, year_release);
	return newCar;
}

Vehicle* initVehicle(vector<string> serviceHistory, string carName, string color, int year_release) {
	if (carName == "SUV") {
		SUV* newCar = new SUV(serviceHistory, color, year_release);
		return newCar;
	}
	else if (carName == "Sedan") {
		Sedan* newCar = new Sedan(serviceHistory, color, year_release);
		return newCar;
	}
	else if (carName == "LuxuryCar") {
		LuxuryCar* newCar = new LuxuryCar(serviceHistory, color, year_release);
		return newCar;
	}
	Vehicle* newCar = new Vehicle(serviceHistory, color, year_release);
	return newCar;
}

Driver* initCustomer(string name, string vehicle, string phoneNumber, string email, string driverLicense, string paymentMethod) {
	Driver* driver = new Driver(name, vehicle, phoneNumber, email, driverLicense, paymentMethod);
	return driver;
}