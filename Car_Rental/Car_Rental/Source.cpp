#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

tm chronoTPtoTM(const std::chrono::system_clock::time_point& tp) {
	time_t aux = std::chrono::system_clock::to_time_t(tp);
	return *localtime(&aux);
}
std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
tm local_time = chronoTPtoTM(t);

string getCurrentTimeCode()
{
	string finalTime = to_string(local_time.tm_year + 1900);
	if (local_time.tm_mon + 1 < 10)
		finalTime += '0';
	finalTime += to_string(local_time.tm_mon + 1);
	if (local_time.tm_mday < 10)
		finalTime += '0';
	finalTime += to_string(local_time.tm_mday);

	return finalTime;
}
class Garage
{
private:
	string name;
	string address;
	int garageSize;
	string director;
public:
	Garage(string name, string address, int garageSize, string director)
		: name(name), address(address), garageSize(garageSize), director(director)
	{
	};
	std::string getName() const { return name; }
	void setName(std::string val) { name = val; }
	std::string getAddress() const { return address; }
	void setAddress(std::string val) { address = val; }
	int getGarageSize() const { return garageSize; }
	void setGarageSize(int val) { garageSize = val; }
	string getDirector() const { return director; }
	void setDirector(int val) { director = val; }

	void printInformation()
	{
		cout << "Garage name: " << this->getName() << endl;
		cout << "Garage address: " << this->getAddress() << endl;
		cout << "Garage size: " << this->getGarageSize() << endl;
		cout << "Director: " << this->getDirector() << endl;
	}
};
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
class ServiceHistory
{
protected:
	string serviceID;
	string serviceCode;
	int cost;
	Garage* garage;
	int miles;
public:
	static int numofService;

	ServiceHistory(string serviceCode, int cost, Garage* garage, int miles)
		: serviceCode(serviceCode), cost(cost), garage(garage), miles(miles)
	{
		numofService++;
	};
	
	ServiceHistory(string serviceCode)
		: serviceCode(serviceCode)
	{
		numofService++;
	};

	std::string getServiceCode() const { return serviceCode; }
	void setServiceCode(std::string val) { serviceCode = val; }
	int getCost() const { return cost; }
	void setCost(int val) { cost = val; }
	Garage* getGarage() const { return garage; }
	void setGarage(Garage* val) { garage = val; }
	int getMiles() const { return miles; }
	void setMiles(int val) { miles = val; }
	std::string getServiceID() const { return serviceID; }
	void setServiceID(std::string val) { serviceID = val; }

	void displayTime(string Time)
	{
		cout << Time[0] << Time[1] << Time[2] << Time[3] << ":"
			<< Time[4] << Time[5] << ":"
			<< Time[6] << Time[7];
	}

	string getServiceTime()
	{
		if (getServiceCode().empty())
			return "0";
		return getServiceCode();
	}

	virtual string serviceType() = 0;
	virtual string detailedServiceType() = 0;
	virtual void printInformation() = 0;

	bool operator==(ServiceHistory& b)
	{
		string car1_str = "";
		string car2_str = "";
		int car1_int = 0;
		int car2_int = 0;
		for (unsigned int i = 0; i < this->getServiceID().size(); i++)
		{
			if (this->getServiceID()[i] == '_')
				break;
			car1_str += this->getServiceID()[i];
		}

		for (unsigned int i = 0; i < b.getServiceID().size(); i++)
		{
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

	int operator-(ServiceHistory& b)
	{
		int result = 999;
		if (*this == b)
		{
			result = abs(this->getMiles() - b.getMiles());
			return result;
		}
		return -999;
	}

	int operator=(ServiceHistory& b)
	{
		int result = 0;
		if (*this == b)
		{
			if (this->getMiles() > b.getMiles())
				return 1;
			if (this->getMiles() < b.getMiles())
				return -1;
			return 0;
		}
		return -999;
	}
};

int ServiceHistory::numofService = 0;

class ServiceEngine : public ServiceHistory
{
private:
	bool oilChange = false;
	bool minor = false;
	bool major = false;
public:
	ServiceEngine(string serviceCode, int cost, Garage* garage, int miles)
		: ServiceHistory(serviceCode, cost, garage, miles)
	{
		if (serviceCode[9] == 'O')
			this->setOilChange(true);
		else if (serviceCode[9] == 'I')
			this->setMinor(true);
		else if (serviceCode[9] == 'A')
			this->setMajor(true);
	}
	
	ServiceEngine(string serviceCode)
		: ServiceHistory(serviceCode)
	{
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

	string serviceType() override
	{
		return "Engine";
	}

	string detailedServiceType() override
	{
		if (this->getOilChange())
			return "Oil Change";
		if (this->getMinor())
			return "Minor";
		if (this->getMajor())
			return "Major";
		return "Unknown";
	}

	void printInformation() override
	{
		cout << "Engine Service type: " << detailedServiceType();
		cout << "\t";
		cout << "Service time: ";
		this->displayTime(getServiceCode());
		cout << endl;
		cout << "Maintainence cost: " << this->getCost() << endl;
		cout << "Maintainence garage: " << this->getGarage()->getName() << endl;
		cout << "Miles traveled at Maintainence time: " << this->getMiles() << endl;
		cout << endl;
	}
};

class ServiceTransmission : public ServiceHistory
{
private:
	bool fluidChange = false;
	bool minor = false;
	bool overhaul = false;
public:
	ServiceTransmission(string serviceCode, int cost, Garage* garage, int miles)
		: ServiceHistory(serviceCode, cost, garage, miles)
	{
		if (serviceCode[9] == 'F')
			this->setFluidChange(true);
		else if (serviceCode[9] == 'M')
			this->setMinor(true);
		else if (serviceCode[9] == 'O')
			this->setOverhaul(true);
	}
	
	ServiceTransmission(string serviceCode)
		: ServiceHistory(serviceCode)
	{
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

	string serviceType() override
	{
		return "Transmission";
	}

	string detailedServiceType() override
	{
		if (this->getFluidChange())
			return "Fluid Change";
		if (this->getMinor())
			return "Minor";
		if (this->getOverhaul())
			return "Overhaul";
		return "Unknown";
	}

	void printInformation() override
	{
		cout << "Transmission Service type: " << detailedServiceType();
		cout << "\t";
		cout << "Service time: ";
		this->displayTime(getServiceCode());
		cout << endl;
		cout << "Maintainence cost: " << this->getCost() << endl;
		cout << "Maintainence garage: " << this->getGarage()->getName() << endl;
		cout << "Miles traveled at Maintainence time: " << this->getMiles() << endl;
		cout << endl;
	}
};

class ServiceTire : public ServiceHistory
{
private:
	bool adjusment = false;
	bool replacement = false;
public:
	ServiceTire(string serviceCode, int cost, Garage* garage, int miles)
		: ServiceHistory(serviceCode, cost, garage, miles)
	{
		if (serviceCode[9] == 'A')
			this->setAdjusment(true);
		else if (serviceCode[9] == 'R')
			this->setReplacement(true);
	}
	
	ServiceTire(string serviceCode)
		: ServiceHistory(serviceCode)
	{
		if (serviceCode[9] == 'A')
			this->setAdjusment(true);
		else if (serviceCode[9] == 'R')
			this->setReplacement(true);
	}

	bool getAdjusment() const { return adjusment; }
	void setAdjusment(bool val) { adjusment = val; }
	bool getReplacement() const { return replacement; }
	void setReplacement(bool val) { replacement = val; }

	string serviceType() override
	{
		return "Tire";
	}

	string detailedServiceType() override
	{
		if (this->getAdjusment())
			return "Adjustment";
		if (this->getReplacement())
			return "Replacement";
		return "Unknown";
	}

	void printInformation() override
	{
		cout << "Tire Service type: " << detailedServiceType();
		cout << "\t";
		cout << "Service time: ";
		this->displayTime(getServiceCode());
		cout << endl;
		cout << "Maintainence cost: " << this->getCost() << endl;
		cout << "Maintainence garage: " << this->getGarage()->getName() << endl;
		cout << "Miles traveled at Maintainence time: " << this->getMiles() << endl;
		cout << endl;
	}
};

class Vehicle
{
protected:
	string color;
	int year_release;
	vector<ServiceHistory*> serviceRecord;
	int numberOfService;
	string name = "Undefined";
public:
	Vehicle* next;
	static int numOfCars;

	Vehicle(string color, int year_release)
		: color(color), year_release(year_release)
	{
		numOfCars++;
		ServiceHistory::numofService = 0;
		this->setNumberOfService(0);
	};

	Vehicle(ServiceHistory* serviceRecord, string color, int year_release)
		: color(color), year_release(year_release)
	{
		ServiceHistory::numofService = 0;
		this->setNumberOfService(ServiceHistory::numofService);
		numOfCars++;
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
		numOfCars++;

		unsigned int i, j;
		for (i = 0; i < this->getServiceRecord().size() - 2; i++)
		{
			for (j = 0; j < this->getServiceRecord().size() - i - 1; j++)
			{
				if (this->getServiceRecord()[j]->getMiles() > this->getServiceRecord()[j + 1]->getMiles())
				{
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
	std::string getName() const { return name; }
	void setName(std::string val) { name = val; }

	void setServiceHistory(ServiceHistory* service, int index) { this->serviceRecord[index] = service; }
	ServiceHistory* getServiceHistory(int index) { return this->getServiceRecord()[index]; }

	string getLastServiceEngine()
	{
		for (unsigned int i = getServiceRecord().size() - 1; i >= 0; i--)
		{
			if (getServiceHistory(i)->getServiceCode()[8] == 'E')
				return getServiceHistory(i)->getServiceCode();
		}
		return "0";
	}
	
	string getLastServiceTransmission()
	{
		for (unsigned int i = getServiceRecord().size() - 1; i >= 0; i--)
		{
			if (getServiceHistory(i)->getServiceCode()[8] == 'T')
				return getServiceHistory(i)->getServiceCode();
		}
		return "0";
	}
	
	string getLastServiceTires()
	{
		for (unsigned int i = getServiceRecord().size() - 1; i >= 0; i--)
		{
			if (getServiceHistory(i)->getServiceCode()[8] == 'W')
				return getServiceHistory(i)->getServiceCode();
		}
		return "0";
	}

	string generateServiceID(ServiceHistory* serviceHistory)
	{
		string ID = to_string(numOfCars) + '_';
		ID += serviceHistory->getServiceCode() + '_';
		ID += serviceHistory->getCost() + '_';
		ID += serviceHistory->getGarage()->getName() + '_';
		ID += serviceHistory->getMiles();
		return ID;
	}

	void addService(string serviceCode)
	{
		if (serviceCode[8] == 'E')
		{
			if (serviceCode[9] == 'O')
				serviceRecord.push_back(new ServiceEngine(serviceCode));
			else if (serviceCode[9] == 'I')
				serviceRecord.push_back(new ServiceTransmission(serviceCode));
			else if (serviceCode[9] == 'A')
				serviceRecord.push_back(new ServiceTire(serviceCode));
		}
		else if (serviceCode[8] == 'T')
		{
			if (serviceCode[9] == 'F')
				serviceRecord.push_back(new ServiceTransmission(serviceCode));
			else if (serviceCode[9] == 'M')
				serviceRecord.push_back(new ServiceTransmission(serviceCode));
			else if (serviceCode[9] == 'O')
				serviceRecord.push_back(new ServiceTransmission(serviceCode));
		}
		else if (serviceCode[8] == 'W')
		{
			if (serviceCode[9] == 'A')
				serviceRecord.push_back(new ServiceTire(serviceCode));
			else if (serviceCode[9] == 'R')
				serviceRecord.push_back(new ServiceTire(serviceCode));
		}
		numberOfService++;
	}
	
	virtual void printInformation() = 0;

	void showServiceHistory()
	{
		cout << "Service History: " << endl;
		for (unsigned int i = 0; i < getServiceRecord().size(); i++)
			getServiceRecord()[i]->printInformation();
		cout << "Number of service: " << this->getNumberOfService() << endl;
	}
};

int Vehicle::numOfCars = 0;

class SUV : public Vehicle
{
private:
	int numberOfSeats;
public:
	SUV(string color, int year_release, int numberOfSeats)
		: Vehicle(color, year_release), numberOfSeats(numberOfSeats)
	{
		this->setName("SUV");
	}

	SUV(vector<ServiceHistory*> serviceRecord, string color, int year_release, int numberOfSeats)
		: Vehicle(serviceRecord, color, year_release), numberOfSeats(numberOfSeats)
	{
		this->setName("SUV");
	}

	int getNumberOfSeats() const { return numberOfSeats; }
	void setNumberOfSeats(int val) { numberOfSeats = val; }

	void printInformation() override
	{
		cout << "Rent a " << getColor() << " SUV from "
			<< getYear_release() << " with " << this->getNumberOfSeats() << " seats" << endl;
	}
};

class Sedan : public Vehicle
{
private:
	char carClass;
public:
	Sedan(string color, int year_release, char carClass)
		: Vehicle(color, year_release), carClass(carClass)
	{
		this->setName("Sedan");
	}

	char getCarClass() const { return carClass; }
	void setCarClass(char val) { carClass = val; }

	Sedan(vector<ServiceHistory*> serviceRecord, string color, int year_release, char carClass)
		: Vehicle(serviceRecord, color, year_release), carClass(carClass)
	{
		this->setName("Sedan");
	}

	void printInformation() override
	{
		cout << "Rent a class " << this->getCarClass() << " " << getColor()
			<< " Sedan from " << getYear_release() << endl;
	}
};

class LuxuryCar : public Vehicle
{
private:
public:
	LuxuryCar(string color, int year_release)
		: Vehicle(color, year_release)
	{
		this->setName("Luxury car");
	};

	LuxuryCar(vector<ServiceHistory*> serviceRecord, string color, int year_release)
		: Vehicle(serviceRecord, color, year_release)
	{
		this->setName("Luxury car");
	};

	void printInformation() override
	{
		cout << "Rent a " << getColor()
			<< " Luxury Car from " << getYear_release() << endl;
	}
};

class CarFleet
{
private:
	Vehicle* vehicleHead;
	int size = 0;
public:
	CarFleet() { vehicleHead = nullptr; }

	CarFleet(Vehicle* vehicleHead)
		: vehicleHead(vehicleHead)
	{
		size++;
	}

	Vehicle* getVehicleHead() const { return vehicleHead; }
	void setVehicleHead(Vehicle* val) { vehicleHead = val; }
	int getSize() const { return size; }
	void setSize(int val) { size = val; }
	
	void addCar(Vehicle* newVehicle)
	{
		if (!vehicleHead)
			this->vehicleHead = newVehicle;
		else
		{
			Vehicle* head = vehicleHead;
			while (head->next)
				head = head->next;
			head->next = newVehicle;
		}
		size++;
	}

	void popCar()
	{
		if (!vehicleHead)
			return;
		Vehicle* head = vehicleHead;
		if (size == 1)
			delete head;
		else
		{
			while (head->next->next)
				head = head->next;
			Vehicle* deleteCar = head->next;
			head->next = nullptr;
			delete deleteCar;
		}
		size--;
	}

	Vehicle* getCar(int idx)
	{
		if (idx < 0 || idx >= size)
			return nullptr;
		Vehicle* head = this->vehicleHead;
		for (int i = 0; i < idx; i++)
			head = head->next;
		return head;
	}

	void removeCar(int idx)
	{
		if (idx >= size || idx < 0)
		{
			cout << "index unavailable" << endl;
			return;
		}
		if (size == 0)
			return;
		if (idx == size - 1)
			this->popCar();
		else
		{
			Vehicle* head = vehicleHead;
			for (int i = 0; i < size - 1; i++)
				head = head->next;
			Vehicle* deleteCar = head->next;
			head->next = head->next->next;
			delete deleteCar;
		}
		size--;
	}

	void showAllOption()
	{
		Vehicle* head = vehicleHead;
		while (head)
		{
			head->printInformation();
			head = head->next;
		}
	}
};

class Customer
{
protected:
	string customerName;
	Vehicle* customerVehicle;
	string phoneNumber;
	string email;
	string customerLicense;
	string paymentMethod;
	bool isRent = false;

public:
	static int numofCustomers;

	Customer(string customerName, Vehicle* customerVehicle, string phoneNumber, string email, string customerLicense,
	         string paymentMethod)
		: customerName(customerName), customerVehicle(customerVehicle), phoneNumber(phoneNumber), email(email),
		  customerLicense(customerLicense), paymentMethod(paymentMethod)
	{
		numofCustomers++;
	}

	std::string getCustomerName() const { return customerName; }
	void setCustomerName(std::string val) { customerName = val; }
	Vehicle* getCustomerVehicle() const { return customerVehicle; }
	void setCustomerVehicle(Vehicle* val) { customerVehicle = val; }
	std::string getPhoneNumber() const { return phoneNumber; }
	void setPhoneNumber(std::string val) { phoneNumber = val; }
	std::string getEmail() const { return email; }
	void setEmail(std::string val) { email = val; }
	std::string getCustomerLicense() const { return customerLicense; }
	void setCustomerLicense(std::string val) { customerLicense = val; }
	std::string getPaymentMethod() const { return paymentMethod; }
	void setPaymentMethod(std::string val) { paymentMethod = val; }
	bool getIsRental() const { return isRent; }
	void setIsRental(bool val) { isRent = val; }

	void printInformation() const
	{
		cout << endl;
		cout << "Name: " << this->getCustomerName() << endl;
		cout << "Vehicle: " << this->getCustomerVehicle()->getName() << endl;
		cout << "Phone number: " << this->getPhoneNumber() << endl;
		cout << "Email address: " << this->getEmail() << endl;
		cout << "Customer license: " << this->getCustomerLicense() << endl;
		cout << "Payment method: " << this->getPaymentMethod() << endl;
	}
};

int Customer::numofCustomers = 0;



class RentalContract
{
protected:
	Customer* customer;
	int contractID;
	Garage* pickedUp_location;
	Garage* return_location;
	string pickUp_time;
	string return_time;
	int totalCost;
public:
	static int numOfContracts;

	RentalContract(Customer* customer, int contractID, string pickUp_time, string return_time, 
					Garage* pickedUp_location, Garage* return_location, int totalCost)
		: customer(customer), contractID(contractID), pickedUp_location(pickedUp_location),
		  return_location(return_location),
		  pickUp_time(pickUp_time), return_time(return_time), totalCost(totalCost)
	{
		numOfContracts++;
	}

	Customer* getCustomer() const { return customer; }
	void setCustomer(Customer* val) { customer = val; }
	int getContract_ID() const { return contractID; }
	void setContract_ID(int val) { contractID = val; }
	Garage* getPickedUpLocation() const { return pickedUp_location; }
	void setPickedUpLocation(Garage* val) { pickedUp_location = val; }
	Garage* getReturnLocation() const { return return_location; }
	void setReturnLocation(Garage* val) { return_location = val; }
	std::string getPickUp_time() const { return pickUp_time; }
	void setPickUp_time(std::string val) { pickUp_time = val; }
	std::string getReturn_time() const { return return_time; }
	void setReturn_time(std::string val) { return_time = val; }
	int getTotalCost() const { return totalCost; }
	void setTotalCost(int val) { totalCost = val; }

	void printInformation()
	{
		getCustomer()->printInformation();
		cout << "contract ID: " << this->getContract_ID() << endl;
		cout << "Pick up time: " << this->getPickUp_time() << endl;
		cout << "Return time: " << this->getReturn_time() << endl;
		cout << "Picked up location: " << this->getPickedUpLocation()->getName() << endl;
		cout << "Return location: " << this->getReturnLocation()->getName() << endl;
		cout << "Total Cost: " << this->getTotalCost() << endl;
		this->getCustomer()->getCustomerVehicle()->printInformation();
	}
};

int RentalContract::numOfContracts = 0;


class BookAndRent
{
public:
	virtual void bookACar(Customer*) = 0;
	virtual void signContract(RentalContract*) = 0;
	virtual void signContract(Customer* customer, string pickUp_time, string return_time,
	                          Garage* pickUp_location, Garage* return_location, int totalCost) = 0;
};

class CarRentalManagement : public BookAndRent
{
private:
	CarFleet* carFleet;
	vector<Customer*> customers;
	vector<RentalContract*> contracts;
public:
	CarRentalManagement() {}
	CarRentalManagement(CarFleet* carFleet)
		: carFleet(carFleet) {}
	CarRentalManagement(CarFleet* car_fleet, Customer* _customers)
		: carFleet(carFleet) {customers.push_back(_customers);}
	CarRentalManagement(CarFleet* car_fleet, vector<Customer*> customers)
		: carFleet(carFleet), customers(customers) {}

	CarFleet* getCarFleet() const { return carFleet; }
	void setCarFleet(CarFleet* val) { carFleet = val; }
	vector<Customer*> getCustomers() const { return customers; }
	void setCustomers(vector<Customer*> val) { customers = val; }
	vector<RentalContract*> getContracts() const { return contracts; }
	void setContracts(vector<RentalContract*> val) { contracts = val; }
	
	void bookACar(Customer* customer) override { customers.push_back(customer); }

	void signContract(RentalContract* contract) override
	{
		contract->getCustomer()->setIsRental(true);
		contracts.push_back(contract);
	}

	int findCustomerIndex (Customer* customer)
	{
		for (int i = 0; i < customers.size(); i++)
		{
			if (customer->getCustomerName() == customers[i]->getCustomerName())
				return i;
		}
		return -1;
	}
	
	void signContract(Customer* customer, string pickUp_time, string return_time,
	                          Garage* pickUp_location, Garage* return_location, int totalCost) override
	{
		if (findCustomerIndex(customer) == -1)
		{
			cout << "Customer hasn't book a car yet" << endl;
			return;
		}
		customers[findCustomerIndex(customer)]->setIsRental(true);
		contracts.push_back(new RentalContract(customer, RentalContract::numOfContracts + 1, pickUp_time, return_time,
								pickUp_location, return_location, totalCost));
	}
	
	void serviceFleet()
	{
		Vehicle* head = this->carFleet->getVehicleHead();
		for (int i = 0; i < carFleet->getSize(); i++)
		{	// if the last service time is more than 3 month so the car will get service
			if (stoi(getCurrentTimeCode()) - stoi(head->getLastServiceEngine()) > 300)
			{
				head->addService(getCurrentTimeCode() + "EO");
				head->getServiceHistory(head->getNumberOfService() - 1)->setCost(5000);
				head->getServiceHistory(head->getNumberOfService() - 1)->setMiles(stoi(getCurrentTimeCode()));
				head->addService(getCurrentTimeCode() + "EI");
				head->getServiceHistory(head->getNumberOfService() - 1)->setCost(5000);
				head->getServiceHistory(head->getNumberOfService() - 1)->setMiles(stoi(getCurrentTimeCode()));
				head->addService(getCurrentTimeCode() + "EA");
				head->getServiceHistory(head->getNumberOfService() - 1)->setCost(5000);
				head->getServiceHistory(head->getNumberOfService() - 1)->setMiles(stoi(getCurrentTimeCode()));
				cout << "The car has been Service Engine" << endl;
			}
			else if (stoi(getCurrentTimeCode()) - stoi(head->getLastServiceTransmission()) > 300)
			{
				head->addService(getCurrentTimeCode() + "TF");
				head->getServiceHistory(head->getNumberOfService() - 1)->setCost(5000);
				head->getServiceHistory(head->getNumberOfService() - 1)->setMiles(stoi(getCurrentTimeCode()));
				head->addService(getCurrentTimeCode() + "TM");
				head->getServiceHistory(head->getNumberOfService() - 1)->setCost(5000);
				head->getServiceHistory(head->getNumberOfService() - 1)->setMiles(stoi(getCurrentTimeCode()));
				head->addService(getCurrentTimeCode() + "TO");
				head->getServiceHistory(head->getNumberOfService() - 1)->setCost(5000);
				head->getServiceHistory(head->getNumberOfService() - 1)->setMiles(stoi(getCurrentTimeCode()));
				cout << "The car has been Service Transmission" << endl;
			}
			else if (stoi(getCurrentTimeCode()) - stoi(head->getLastServiceTransmission()) > 300)
			{
				head->addService(getCurrentTimeCode() + "WA");
				head->getServiceHistory(head->getNumberOfService() - 1)->setCost(5000);
				head->getServiceHistory(head->getNumberOfService() - 1)->setMiles(stoi(getCurrentTimeCode()));
				head->addService(getCurrentTimeCode() + "WR");
				head->getServiceHistory(head->getNumberOfService() - 1)->setCost(5000);
				head->getServiceHistory(head->getNumberOfService() - 1)->setMiles(stoi(getCurrentTimeCode()));
				cout << "The car has been Service Tire" << endl;
			}
				head = head->next;
			
		}
		
	}
};


string generateServiceCode(vector<string> serviceTime, vector<string> serviceType);

Garage* initGarage(string name, string address, int size, string director);
Customer* initCustomer(string name, Vehicle* vehicle, string email, string phoneNumber, string customerLicense,
                       string paymentMethod);
ServiceHistory* initService(vector<string> maintanenceTime, vector<string> maintanenceType, Garage* garageM);
vector<ServiceHistory*> initServiceRecord(vector<string> maintanenceTime, vector<string> maintanenceType,
                                          Garage* garageM);

int main()
{
	srand(time(nullptr));
	vector<string> typeService = {
		"EO", "EI", "EA", "TF", "TM", "TO", "WA", "WR"
	};

	CarRentalManagement* manager = new CarRentalManagement();
	
	vector<string> timeService = {
		"20150508", "20160119", "20160127", "20160222", "20160509",
		"20160516", "20160812", "20160906", "20161207", "20170125",
		"20170501", "20170720", "20170915", "20170918", "20171116",
		"20190122", "20190531", "20190722", "20191011", "20191113",
		"20200122", "20200608", "20200810", "20201013", "20201125"
	};

	vector<string> garageService = {
		"Airport",
		"District 1",
		"District 10",
		"District Go Vap",
		"Vung Tau city"
	};

	vector<Garage*> garage = {
		initGarage(garageService[0], garageService[0] + "city", 5000, "Hoang Tung"),
		initGarage(garageService[1], garageService[1] + "city", 2000, "Bao Nhi"),
		initGarage(garageService[2], garageService[2] + "city", 1000, "Thai Thong")
	};
	vector<ServiceHistory*> car_1_service = initServiceRecord(timeService, typeService, garage[0]);
	vector<ServiceHistory*> car_2_service = initServiceRecord(timeService, typeService, garage[1]);
	vector<ServiceHistory*> car_3_service = initServiceRecord(timeService, typeService, garage[2]);

	CarFleet* carFleet = new CarFleet();
	carFleet->addCar(new SUV(car_1_service, "Black", 1994, 4));
	carFleet->addCar(new Sedan(car_2_service, "White", 1969, 'B'));
	carFleet->addCar(new LuxuryCar("Red", 2021));
	cout << endl << "Show all available car" << endl;
	carFleet->showAllOption();
	vector<Customer*> customerList;
	customerList.push_back(initCustomer("Sheldon", carFleet->getCar(0), "0999999", "Sheldon_Copper@bazingga.biz",
		"pasedenaLicense999", "Credit Card"));
	customerList.push_back(initCustomer("Leonard", carFleet->getCar(1), "011111",
		"Leonard_Hofstadter@bazingga.biz", "pasedenaLicense1", "MoMo"));
	customerList.push_back(initCustomer("Penny", carFleet->getCar(2), "0999999", "Penny_Hofstadter@bazingga.biz",
		"pasedenaLicense998", "Cash"));
	
	manager->bookACar(customerList[0]);
	manager->bookACar(customerList[1]);
	manager->bookACar(customerList[2]);

	manager->signContract(customerList[0], "02:08:2021", "04:08:2021", garage[1], garage[2], 2000);
	manager->signContract(customerList[1], "03:08:2021", "05:08:2021", garage[2], garage[0], 3000);
	manager->signContract(customerList[2], "10:08:2021", "11:08:2021", garage[0], garage[1], 5000);

	manager->getContracts()[0]->printInformation();
	manager->getContracts()[1]->printInformation();
	manager->getContracts()[2]->printInformation();
	manager->serviceFleet();
	//for (int i = 0; i < 3; i++) {
	//	cout << endl << "Service history of car: " << i << endl;
	//	carFleet->getCar(i)->showServiceHistory();
	//}

	cout << endl << "Number of customers: " << Customer::numofCustomers;
	cout << endl << "Number of car being rented: " << Vehicle::numOfCars << endl;
	cout << endl << endl;

	for (int i = 0; i < 3; i++)
	{
		garage[i]->printInformation();
		cout << endl;
	}

	cout << endl << endl << endl;
	int service1 = 2;
	int service2 = 3;
	int miles2Service = *(carFleet->getCar(0)->getServiceHistory(service2)) - *(carFleet->getCar(0)->
		getServiceHistory(service1));
	cout << "Miles between service 2 and 3 of car 1: " << miles2Service << endl;
	cout << "Actual:                                 " << carFleet->getCar(0)->getServiceHistory(service2)->getMiles() -
		carFleet->getCar(0)->getServiceHistory(service1)->getMiles() << endl;
	cout << endl;
	int compasison = *(carFleet->getCar(0)->getServiceHistory(service1)) = *(carFleet->getCar(0)->
		getServiceHistory(service2));
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

Customer* initCustomer(string name, Vehicle* vehicle, string phoneNumber, string email, string customerLicense,
                       string paymentMethod)
{
	auto customer = new Customer(name, vehicle, phoneNumber, email, customerLicense, paymentMethod);
	return customer;
}

ServiceHistory* initService(vector<string> maintanenceTime, vector<string> maintanenceType, Garage* garageM)
{
	string timeM = generateServiceCode(maintanenceTime, maintanenceType);
	int cost = rand() % 8999 + 1000;
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

std::vector<ServiceHistory*> initServiceRecord(vector<string> maintanenceTime, vector<string> maintanenceType,
                                               Garage* garageM)
{
	vector<ServiceHistory*> serviceRecord;
	for (int i = 0; i < (rand() % 5 + 9); i++)
		serviceRecord.push_back(initService(maintanenceTime, maintanenceType, garageM));
	return serviceRecord;
}

string generateServiceCode(vector<string> serviceTime, vector<string> serviceType)
{
	string timeE = serviceTime[rand() % 25];
	string typeE = serviceType[rand() % 8];
	return timeE + typeE;
}

Garage* initGarage(string name, string address, int size, string director)
{
	return new Garage(name, address, size, director);
}
