#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;

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
	string serviceCode;
	int cost;
	string garage;
	int miles;
public:
	static int numofService;
	ServiceHistory(string serviceCode, int cost, string garage, int miles)
		: serviceCode(serviceCode), cost(cost), garage(garage), miles(miles) {
		ServiceHistory::numofService++;
	};

	std::string getServiceCode() const { return serviceCode; }
	void setServiceCode(std::string val) { serviceCode = val; }
	int getCost() const { return cost; }
	void setCost(int val) { cost = val; }
	std::string getGarage() const { return garage; }
	void setGarage(std::string val) { garage = val; }
	int getMiles() const { return miles; }
	void setMiles(int val) { miles = val; }
	std::string getServiceID() const { return serviceID; }
	void setServiceID(std::string val) { serviceID = val; }

	void displayTime(string Time) {
		cout << Time[0] << Time[1] << Time[2] << Time[3] << ":"
			<< Time[4] << Time[5] << ":"
			<< Time[6] << Time[7];
	}

	int getServiceTime() {
		if (getServiceCode() == "")
			return 0;
		return stoi(getServiceCode());
	}

	virtual string serviceType() = 0;
	virtual string detailedServiceType() = 0;
	virtual void printInformation() = 0;

	bool operator==(ServiceHistory& b) {
		string car1_str = "";
		string car2_str = "";
		int car1_int = 0;
		int car2_int = 0;
		for (unsigned int i = 0; i < this->getServiceID().size(); i++) {
			if (this->getServiceID()[i] == '_')
				break;
			car1_str += this->getServiceID()[i];
		}

		for (unsigned int i = 0; i < b.getServiceID().size(); i++) {
			if (b.getServiceID()[i] == '_')
				break;
			car2_str += b.getServiceID()[i];
		}
		car1_int = stoi(car1_str);
		car2_int = stoi(car2_str);
		if (car1_int == car2_int)
			return true;
		return false;
	}

	int operator-(ServiceHistory& b) {
		int result = 999;
		if (*this == b) {
			result = abs(this->getMiles() - b.getMiles());
			return result;
		}
		return -999;
	}

	int operator=(ServiceHistory& b) {
		int result = 0;
		if (*this == b) {
			if (this->getMiles() > b.getMiles())
				return 1;
			else if (this->getMiles() < b.getMiles())
				return -1;
			return 0;
		}
		return -999;
	}
};
int ServiceHistory::numofService = 0;

class ServiceEngine : public ServiceHistory {
private:
	bool oilChange = false;
	bool minor = false;
	bool major = false;
public:

	ServiceEngine(string serviceCode, int cost, string garage, int miles)
		: ServiceHistory(serviceCode, cost, garage, miles) {
		if (serviceCode[9] == 'O')
			this->setOilChange(true);
		else if (serviceCode[9] == 'I')
			this->setMinor(true);
		else if (serviceCode[9] == 'A')
			this->setMajor(true);
	}

	bool getOilChange() const { return oilChange; }
	void setOilChange(bool val) { oilChange = val; }
	bool getMinor() const { return minor; }
	void setMinor(bool val) { minor = val; }
	bool getMajor() const { return major; }
	void setMajor(bool val) { major = val; }

	string serviceType() {
		return "Engine";
	}

	string detailedServiceType() {
		if (this->getOilChange())
			return "Oil Change";
		else if (this->getMinor())
			return "Minor";
		else if (this->getMajor())
			return "Major";
		return "Unknown";
	}

	void printInformation() {
		cout << "Engine Service type: " << detailedServiceType();
		cout << "\t";
		cout << "Service time: ";
		this->displayTime(getServiceCode());
		cout << endl;
		cout << "Maintainence cost: " << this->getCost() << endl;
		cout << "Maintainence garage: " << this->getGarage() << endl;
		cout << "Miles traveled at Maintainence time: " << this->getMiles() << endl;
		cout << endl;
	}
};

class ServiceTransmission : public ServiceHistory {
private:
	bool fluidChange = false;
	bool minor = false;
	bool overhaul = false;
public:

	ServiceTransmission(string serviceCode, int cost, string garage, int miles)
		: ServiceHistory(serviceCode, cost, garage, miles) {
		if (serviceCode[9] == 'F')
			this->setFluidChange(true);
		else if (serviceCode[9] == 'M')
			this->setMinor(true);
		else if (serviceCode[9] == 'O')
			this->setOverhaul(true);
	}

	bool getFluidChange() const { return fluidChange; }
	void setFluidChange(bool val) { fluidChange = val; }
	bool getMinor() const { return minor; }
	void setMinor(bool val) { minor = val; }
	bool getOverhaul() const { return overhaul; }
	void setOverhaul(bool val) { overhaul = val; }

	string serviceType() {
		return "Transmission";
	}

	string detailedServiceType() {
		if (this->getFluidChange())
			return "Fluid Change";
		else if (this->getMinor())
			return "Minor";
		else if (this->getOverhaul())
			return "Overhaul";
		return "Unknown";
	}

	void printInformation() {
		cout << "Transmission Service type: " << detailedServiceType();
		cout << "\t";
		cout << "Service time: ";
		this->displayTime(getServiceCode());
		cout << endl;
		cout << "Maintainence cost: " << this->getCost() << endl;
		cout << "Maintainence garage: " << this->getGarage() << endl;
		cout << "Miles traveled at Maintainence time: " << this->getMiles() << endl;
		cout << endl;
	}
};

class ServiceTire : public ServiceHistory {
private:
	bool adjusment = false;
	bool replacement = false;
public:

	ServiceTire(string serviceCode, int cost, string garage, int miles)
		: ServiceHistory(serviceCode, cost, garage, miles) {
		if (serviceCode[9] == 'A')
			this->setAdjusment(true);
		else if (serviceCode[9] == 'R')
			this->setReplacement(true);
	}

	bool getAdjusment() const { return adjusment; }
	void setAdjusment(bool val) { adjusment = val; }
	bool getReplacement() const { return replacement; }
	void setReplacement(bool val) { replacement = val; }

	string serviceType() {
		return "Tire";
	}

	string detailedServiceType() {
		if (this->getAdjusment())
			return "Adjustment";
		else if (this->getReplacement())
			return "Replacement";
		return "Unknown";
	}

	void printInformation() {
		cout << "Tire Service type: " << detailedServiceType();
		cout << "\t";
		cout << "Service time: ";
		this->displayTime(getServiceCode());
		cout << endl;
		cout << "Maintainence cost: " << this->getCost() << endl;
		cout << "Maintainence garage: " << this->getGarage() << endl;
		cout << "Miles traveled at Maintainence time: " << this->getMiles() << endl;
		cout << endl;
	}
};

class Vehicle {
protected:
	string color;
	int year_release;
	vector<ServiceHistory*> serviceRecord;
	int numberOfService;
public:
	static int numOfCars;
	Vehicle(string color, int year_release)
		: color(color), year_release(year_release)
	{
		Vehicle::numOfCars++;
		ServiceHistory::numofService = 0;
		this->setNumberOfService(0);
	};

	Vehicle(ServiceHistory* serviceRecord, string color, int year_release)
		: color(color), year_release(year_release)
	{
		ServiceHistory::numofService = 0;
		this->setNumberOfService(ServiceHistory::numofService);
		Vehicle::numOfCars++;
		this->getServiceRecord().push_back(serviceRecord);
		this->setNumberOfService(1);
	};

	Vehicle(vector<ServiceHistory*> serviceRecord, string color, int year_release)
		: color(color), year_release(year_release)
	{
		this->setNumberOfService(ServiceHistory::numofService);
		ServiceHistory::numofService = 0;
		for (unsigned int i = 0; i < serviceRecord.size(); i++)
			serviceRecord[i]->setServiceID(generateServiceID(serviceRecord[i]));

		this->setServiceRecord(serviceRecord);
		Vehicle::numOfCars++;

		unsigned int i, j;
		for (i = 0; i < this->getServiceRecord().size() - 2; i++) {
			for (j = 0; j < this->getServiceRecord().size() - i - 1; j++) {
				if (this->getServiceRecord()[j]->getMiles() > this->getServiceRecord()[j + 1]->getMiles()) {
					ServiceHistory* temp = this->getServiceHistory(j + 1);
					this->setServiceHistory(this->getServiceHistory(j), j + 1);
					this->setServiceHistory(temp, j);
				}
			}
		}
	};

	std::string getColor() const { return color; }
	void setColor(std::string val) { color = val; }
	int getYear_release() const { return year_release; }
	void setYear_release(int val) { year_release = val; }
	std::vector<ServiceHistory*> getServiceRecord() const { return serviceRecord; }
	void setServiceRecord(std::vector<ServiceHistory*> val) { serviceRecord = val; }
	int getNumberOfService() const { return numberOfService; }
	void setNumberOfService(int val) { numberOfService = val; }

	void setServiceHistory(ServiceHistory* service, int index) { this->serviceRecord[index] = service; }
	ServiceHistory* getServiceHistory(int index) { return this->getServiceRecord()[index]; }

	string generateServiceID(ServiceHistory* serviceHistory) {
		string ID = to_string(Vehicle::numOfCars) + '_';
		ID += serviceHistory->getServiceCode() + '_';
		ID += serviceHistory->getCost() + '_';
		ID += serviceHistory->getGarage() + '_';
		ID += serviceHistory->getMiles();
		return ID;
	}

	static void show_option() {
		cout << "\tDifferent options " << endl;
		cout << "\t\t 1. SUV" << endl;
		cout << "\t\t 2. Sedan" << endl;
		cout << "\t\t 3. luxury car" << endl;
	}

	virtual void printInformation() = 0;

	void showServiceHistory() {
		cout << "Service History: " << endl;
		for (unsigned int i = 0; i < getServiceRecord().size(); i++)
			getServiceRecord()[i]->printInformation();
		cout << "Number of service: " << this->getNumberOfService() << endl;
	}
};
int Vehicle::numOfCars = 0;

class SUV : public Vehicle {
protected:

public:
	SUV(string color, int year_release)
		: Vehicle(color, year_release) {}

	SUV(vector<ServiceHistory*> serviceRecord, string color, int year_release)
		: Vehicle(serviceRecord, color, year_release) {};

	void printInformation() {
		cout << endl << "Rent a " << getColor() << " SUV from " << getYear_release() << endl;
		if (this->getServiceRecord().size() == 0)
			cout << "This car has never been Maintained";
		else
			this->showServiceHistory();
	}
};

class Sedan : public Vehicle {
public:
	Sedan(string color, int year_release)
		: Vehicle(color, year_release) {}

	Sedan(vector<ServiceHistory*> serviceRecord, string color, int year_release)
		: Vehicle(serviceRecord, color, year_release) {}
	void printInformation() {
		cout << endl << "Rent a " << getColor() << " Sedan from " << getYear_release() << endl;
		if (this->getServiceRecord().size() == 0)
			cout << "This car has never been Maintained";
		else
			this->showServiceHistory();
	}
};

class LuxuryCar : public Vehicle {
public:
	LuxuryCar(string color, int year_release)
		: Vehicle(color, year_release) {}

	LuxuryCar(vector<ServiceHistory*> serviceRecord, string color, int year_release)
		: Vehicle(serviceRecord, color, year_release) {};

	void printInformation() {
		cout << endl << "Rent a " << getColor() << " Luxury Car from " << getYear_release() << endl;
		if (this->getServiceRecord().size() == 0)
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

string generateServiceCode(vector<string> serviceTime, vector<string> serviceType);

Vehicle* initVehicle(string carName, string color, int year_release);
Vehicle* initVehicle(vector<ServiceHistory*> serviceHistory, string carName, string color, int year_release);
Driver* initCustomer(string name, string vehicle, string email, string phoneNumber, string driverLicense, string paymentMethod);
ServiceHistory* initService(vector<string> maintanenceTime, vector<string> maintanenceType, vector<string> maintanenceGarage);
vector<ServiceHistory*> initServiceRecord(vector<string> maintanenceTime, vector<string> maintanenceType, vector<string> maintanenceGarage);

int main() {
	srand(time(NULL));
	vector<string> typeService = {
		"EO", "EI", "EA", "TF", "TM", "TO", "WA", "WR"
	};
	vector<string> timeService = {
		"20150508",
		"20160119",
		"20160127",
		"20160222",
		"20160509",
		"20160516",
		"20160812",
		"20160906",
		"20161207",
		"20170125",
		"20170501",
		"20170720",
		"20170915",
		"20170918",
		"20171116",
		"20190122",
		"20190531",
		"20190722",
		"20191011",
		"20191113",
		"20200122",
		"20200608",
		"20200810",
		"20201013",
		"20201125"
	};

	vector<string> garageService = {
		"Paris",
		"NewYork",
		"California",
		"Tokyo",
		"HoChiMinh"
	};

	Vehicle::show_option();

	Driver* driver_1 = initCustomer("Sheldon", "SUV", "0999999", "Sheldon_Copper@bazingga.biz", "pasedenaLicense999", "Credit Card");
	vector<ServiceHistory*> car_1_service = initServiceRecord(timeService, typeService, garageService);
	Vehicle* car_1 = initVehicle(car_1_service, "SUV", "Black", 1994);

	Driver* driver_2 = initCustomer("Leonard", "Sedan", "011111", "Leonard_Hofstadter@bazingga.biz", "pasedenaLicense1", "Credit Card");
	vector<ServiceHistory*> car_2_service = initServiceRecord(timeService, typeService, garageService);
	Vehicle* car_2 = initVehicle(car_2_service, "Sedan", "White", 1969);

	Driver* driver_3 = initCustomer("Penny", "LuxuryCar", "0999999", "Penny_Hofstadter@bazingga.biz", "pasedenaLicense998", "Cash");
	vector<ServiceHistory*> car_3_service = initServiceRecord(timeService, typeService, garageService);
	Vehicle* car_3 = initVehicle("LuxuryCar", "Red", 2021);

	RentalContract* contractSheldon = new RentalContract(driver_1, car_1, 1, "Texas", "02:08:2021", "04:08:2021");
	RentalContract* contractLeonard = new RentalContract(driver_2, car_2, 2, "New Jersey", "03:08:2021", "05:08:2021");
	RentalContract* contractPenny = new RentalContract(driver_3, car_3, 3, "Texas", "10:08:2021", "11:08:2021");

	contractSheldon->printInformation();
	contractLeonard->printInformation();
	contractPenny->printInformation();

	cout << endl << "Number of drivers: " << Driver::numofDrivers;
	cout << endl << "Number of car being rented: " << Vehicle::numOfCars;

	cout << endl << endl << endl;
	int service1 = 2;
	int service2 = 3;
	int miles2Service = *(car_1->getServiceHistory(service2)) - *(car_1->getServiceHistory(service1));
	cout << "Miles between service 2 and 3 of car 1: " << miles2Service << endl;
	cout << "Actual:                                 " << car_1->getServiceHistory(service2)->getMiles() - car_1->getServiceHistory(service1)->getMiles() << endl;
	cout << endl;
	int compasison = *(car_1->getServiceHistory(service1)) = *(car_1->getServiceHistory(service2));
	if (compasison == 1)
		cout << "Service 1 > Service 2";
	else if (compasison == -1)
		cout << "Service 1 < Service 2";
	else if (compasison == 0)
		cout << "Service 1 = Service 2";
	else
		cout << "2 Service not done on the same car";
	cout << endl;
};

Vehicle* initVehicle(string carName, string color, int year_release) {
	Vehicle* newCar;
	if (carName == "SUV")
		newCar = new SUV(color, year_release);
	else if (carName == "Sedan")
		newCar = new Sedan(color, year_release);
	else
		newCar = new LuxuryCar(color, year_release);

	return newCar;
}

Vehicle* initVehicle(vector<ServiceHistory*> serviceHistory, string carName, string color, int year_release) {
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

ServiceHistory* initService(vector<string> maintanenceTime, vector<string> maintanenceType, vector<string> maintanenceGarage) {
	string timeM = generateServiceCode(maintanenceTime, maintanenceType);
	int cost = rand() % 8999 + 1000;
	string garageM = maintanenceGarage[rand() % 5];
	int milesM = stoi(timeM);
	ServiceHistory* newService;
	if (timeM[8] == 'E')
		newService = new ServiceEngine(timeM, cost, garageM, milesM);
	else if (timeM[8] == 'T')
		newService = new ServiceTransmission(timeM, cost, garageM, milesM);
	else
		newService = new ServiceTire(timeM, cost, garageM, milesM);

	return newService;
}

std::vector<ServiceHistory*> initServiceRecord(vector<string> maintanenceTime, vector<string> maintanenceType, vector<string> maintanenceGarage)
{
	vector<ServiceHistory*> serviceRecord;
	for (int i = 0; i < (rand() % 5 + 9); i++)
		serviceRecord.push_back(initService(maintanenceTime, maintanenceType, maintanenceGarage));
	return serviceRecord;
}

string generateServiceCode(vector<string> serviceTime, vector<string> serviceType) {
	string timeE = serviceTime[rand() % 25];
	string typeE = serviceType[rand() % 8];
	return timeE + typeE;
}