#include<iostream>
#include <string>
using namespace std;



class Vehicle{
protected:
    string Brand;
    string color;
    int Seats;
    Vehicle* next;
    friend class Car_fleet;
public:
    Vehicle(){
        Brand = "none";
        color = "none";
        Seats = 4;
        next = nullptr;
    }


    virtual void serviceEngine()=0;
    virtual void serviceTransmission()=0;
    virtual void serviceTires()=0;
    virtual void display()=0;
};

class Truck: public Vehicle{
public:
    int Distance;
    int Carry ;
    int Oil_change_times = 0;
    int Minor_times = 0;
    int Major_times = 0;
    int Fluid_change_times = 0;
    int Overhault_times = 0;
    int Adjustment_times = 0;
    int Replacent_times = 0;
    Truck(){
        color = "Red";
        Seats = 2;
        Brand = "Toyota";
        Distance = 0;
        Carry = 200;
        Vehicle* next = nullptr;
    }
    Truck(int Distance){
        this->Distance = Distance;
        color = "Red";
        Seats = 2;
        Brand = "Toyota";
        Carry = 200;
        Vehicle* next = nullptr;
    }
    void serviceEngine() override{

        if (Distance > 30000){
            cout << "This car need to be serviced Engine\n";

            Oil_change_times++;
            Major_times++;
            Minor_times++;

            cout << "Oil changes times: " << Oil_change_times << endl;
            cout << "Minor times: " << Minor_times << endl;
            cout << "Major times: " << Major_times << endl;
        }
    }
    void serviceTransmission() override{

        if (Distance > 1000){
            cout << "This car need to be serviced Transmission\n";

            Fluid_change_times++;
            Overhault_times++;
            Minor_times++;

            cout << "Fluid change times: " << Fluid_change_times << endl;
            cout << " Overhault times: " <<  Overhault_times << endl;
            cout << "Minor times: " << Minor_times << endl;

        }
    }
    void serviceTires() override{
        if(Distance>5000){
            cout << "This car need to be serviced Tires\n";

            Adjustment_times++;
            Replacent_times++;

            cout << " Adjustment times: " <<  Adjustment_times << endl;
            cout << " Replacent times: " <<  Replacent_times << endl;
        }
    }
    void display() override{
        cout << "Color: " << color << ", ";
        cout << "Number of seats: " << Seats << ", ";
        cout << "Brand: " << Brand << ", ";
        cout << "Carry: " <<Carry << " ";
        cout << endl;
    }
};

class Lexus : public Vehicle{
    int Distance;
    int Oil_change_times = 0;
    int Minor_times = 0;
    int Major_times = 0;
    int Fluid_change_times = 0;
    int Overhault_times = 0;
    int Adjustment_times = 0;
    int Replacent_times = 0;

    void serviceEngine() override{

        if (Distance > 100000){
            cout << "This car need to be serviced Engine\n";

            Oil_change_times++;
            Major_times++;
            Minor_times++;

            cout << "Oil changes times: " << Oil_change_times << endl;
            cout << "Minor times: " << Minor_times << endl;
            cout << "Major times: " << Major_times << endl;
        }
    }
    void serviceTransmission() override{

        if (Distance > 2000){
            cout << "This car need to be serviced Transmission\n";

            Fluid_change_times++;
            Overhault_times++;
            Minor_times++;

            cout << "Fluid change times: " << Fluid_change_times << endl;
            cout << " Overhault times: " <<  Overhault_times << endl;
            cout << "Minor times: " << Minor_times << endl;

        }
    }
    void serviceTires() override{
        if(Distance>8000){
            cout << "This car need to be serviced Tires\n";

            Adjustment_times++;
            Replacent_times++;

            cout << " Adjustment times: " <<  Adjustment_times << endl;
            cout << " Replacent times: " <<  Replacent_times << endl;
        }
    }
    void display() override{
        cout << "Color: " << color << ", ";
        cout << "Number of seats: " << Seats << ", ";
        cout << "Brand: " << Brand << " ";
        cout << endl;
    }

public:
    Lexus(int Distance){
        this->Distance = Distance;
        color = "White";
        Seats = 4;
        Brand = "Honda";
        Distance = 0;
        Vehicle* next = nullptr;
    }

    Lexus(){
        color = "White";
        Seats = 4;
        Brand = "Honda";
        Distance = 0;
        Vehicle* next = nullptr;
    }
};

class SUV : public Vehicle{
    int Distance;
    int Oil_change_times = 0;
    int Minor_times = 0;
    int Major_times = 0;
    int Fluid_change_times = 0;
    int Overhault_times = 0;
    int Adjustment_times = 0;
    int Replacent_times = 0;

    void serviceEngine() override{
        if (Distance > 200000){
            cout << "This car need to be serviced Engine\n";

            Oil_change_times++;
            Major_times++;
            Minor_times++;

            cout << "Oil changes times: " << Oil_change_times << endl;
            cout << "Minor times: " << Minor_times << endl;
            cout << "Major times: " << Major_times << endl;

        }
    }
    void serviceTransmission() override{

        if (Distance > 1500){
            cout << "This car need to be serviced Transmission\n";

            Fluid_change_times++;
            Overhault_times++;
            Minor_times++;

            cout << "Fluid change times: " << Fluid_change_times << endl;
            cout << " Overhault times: " <<  Overhault_times << endl;
            cout << "Minor times: " << Minor_times << endl;


        }
    }
    void serviceTires() override{
        if(Distance>10000){
            cout << "This car need to be serviced Tires\n";

            Adjustment_times++;
            Replacent_times++;

            cout << " Adjustment times: " <<  Adjustment_times << endl;
            cout << " Replacent times: " <<  Replacent_times << endl;


        }
    }
    void display() override{
        cout << "Color: " << color << ", ";
        cout << "Number of seats: " << Seats << ", ";
        cout << "Brand: " << Brand << " ";
        cout << endl;
    }

public:
    SUV(int Distance){
        this->Distance = Distance;
        color = "Gray";
        Seats = 4;
        Brand = "Ford";
        Distance = 0;
        Vehicle* next = nullptr;
    }

    SUV(){
        color = "Gray";
        Seats = 4;
        Brand = "Ford";
        Distance = 0;
        Vehicle* next = nullptr;
    }
};

class Car_fleet{
protected:
    Vehicle* head;

public:
    Car_fleet(){
        head  = nullptr;
    }
   void AddCar(Vehicle* car1)
    {
        if(head == nullptr)
        {
            head = car1;
        }
        else
        {
            Vehicle* temp = head;
            while(temp->next)
                temp = temp->next;
            temp->next = car1;
        }
    }

    void DelHead(){
        if(head == nullptr){
            cout << "No car in the fleet\n";
        }
        else{
            head = head->next;
        }
    }

    void DelTail(){
        if (head == NULL || head->next == NULL){
            return DelHead();
        }
        Vehicle* temp;
        while(temp->next->next != nullptr){
            temp = temp->next;
        }
        temp->next = temp->next->next;
    }

    void DelAtPosition(int position){
        if(position == 0 || head == nullptr || head->next == nullptr){
            DelHead();
        }
        else{
            int k = 1;
            Vehicle* p = head;
            while(p->next->next != NULL && k != position){
                p = p->next;
                ++k;
            }
            if(k != position){
                cout << "No car to delete\n";
            }
            else{
                p->next = p->next->next;
            }
        }
    }

    Vehicle* Get_car(int posistion){
        int k = 0;
        Vehicle* temp = head;
        while(temp->next  && k!= posistion-1){
            ++k;
            temp = temp->next;
        }
        return temp;
    }

    void Check(){
        Vehicle* temp = head;
        while(temp){
            temp->serviceEngine();
            temp->serviceTires();
            temp->serviceTransmission();
            temp = temp->next;
        }
    }

    void Display(){
        int i =1;
        Vehicle* temp = head;
        while(temp){
            cout << i <<" ";
            temp->display();
            temp = temp->next;
            i++;
        }
    }
};

class Customer{
public:
    string Name;
    int Age;
    double Driver_Lisence;
    string Email;
public:
    Customer(){
        Name = "None";
        Age = 0;
        Driver_Lisence = 0;
        Email = "None";
    }
    Customer(string g, int a, double dl, string e){
        Name = g;
        Age = a;
        Driver_Lisence = dl;
        Email = e;
    }
    void Display(){
        cout << "Name: " << Name << ", ";
        cout << "Age: " << Age << ", ";
        cout << "Driver lisence: " << Driver_Lisence << ", ";
        cout << "Email: " << Email << " ";
        cout <<endl;


    }
};
Customer* initCustomer();
class Garage{
public:
    string Location;
    string Name;
    string Size;
    string Director;
public:
    Garage(){
        Location = "none";
        Name = "none";
        Size ="none";
        Director = "none";
    }
    Garage(string l, string n, string s, string d){
        Location = l;
        Name = n;
        Size = s;
        Director = d;
    }
};

class FlyTicket{
public:
    string APLoca;
    string Dtime;
    string Ftime;
public:
    FlyTicket(){
        this->APLoca="none";
        this->Dtime="none";
        this->Ftime="none";
    }
    FlyTicket(string a, string d, string f){
        this->APLoca=a;
        this->Dtime=d;
        this->Ftime=f;
    }
};

class RentalContract{
public:
    string PickLoca;
    string DropLoca;
    string TimePick;
    string TimeDrop;
    double Price;
    string Pay_method;
    Customer* User;
    Garage* Garg;
public:
    RentalContract(){
        PickLoca = "none";
        DropLoca = "none";
        /*Price = 0;*/
        TimeDrop = "none";
        TimePick = "none";
        Pay_method = "none";
        Price = 0;
        User = nullptr;
        Garg = nullptr;
    }
    RentalContract(FlyTicket a, double p, string pm, Customer *u){
        PickLoca = a.APLoca;
        DropLoca = a.APLoca;
        TimeDrop = a.Ftime;
        TimePick = a.Dtime;
        Price = p;
        Pay_method = pm;
        User = u;

    }
    RentalContract(Garage a, string tp, string td, double p, string pm, Customer *u){
        PickLoca = a.Location;
        DropLoca = a.Location;
        TimeDrop = td;
        TimePick = tp;
        Price = p;
        Pay_method = pm;
        User = u;
    }
    RentalContract(Garage a, Garage b, string tp, string td, double p, string pm, Customer *u){
        PickLoca = a.Location;
        DropLoca = b.Location;
        TimeDrop = td;
        TimePick = tp;
        Price = p;
        Pay_method = pm;
        User = u;
    }
    RentalContract(string PickLoca, string DropLoca, string TimePick, string TimeDrop, double Price, string Pay_method, Customer *u){
        this->PickLoca = PickLoca;
        this->DropLoca = DropLoca;
        this->TimeDrop = TimeDrop;
        this->TimePick = TimePick;
        this->Price = Price;
        this->Pay_method = Pay_method;
        this->User = u;
    }


};

class BookAndRent{
public:
    virtual void bookACar() = 0;
    virtual void signAContract(int i, int j) = 0;
    virtual ~BookAndRent() {};
};

class CaRentalMagmt: public BookAndRent{
public:
    Car_fleet* Cf;
    Customer* user;
public:
    CaRentalMagmt(){
        Cf = nullptr;
        user = nullptr;
    }
    CaRentalMagmt(Car_fleet* v): Cf(v){}

    void serviceFleet(){
        Cf->Check();
    }

    void bookACar() override{
        string answer;
        int i;
        int j;
        user = initCustomer();
        for(int i = 0; i<6; i++){
            cout << i <<" ";
            user[i].Display();
        }
        cout << "Who are you, please choose a number: \n";
        cin >> j;
        cout << "You are: \n";
        user[j].Display();
        cout << "Do you want to book a car: Answer Yes or No" << endl;
        cin >> answer;
        if(answer == "No"){return;}
        else{
            Cf->Display();
            cout << "What car do you want to rent : Enter a number from 1-8\n";
            cin >>i;
            cout << "You choose: \n";
            Cf->Get_car(i)->display();
            cout << "Do you to sign a contract : Please answer Yes or No\n";
            cin >> answer;
            if(answer == "No"){return;}
            else{
                signAContract(j, i);
            }

        }

    }

    void signAContract(int i, int j) override{
        int d;
        cout << "How much you want to deposit($): \n";
        cin >> d;
        cout << "***************Contract**************\n";
        cout << "Name :     " << user[i].Name << endl;
        cout << "Driver license:     " << user[i].Driver_Lisence << endl;
        cout << "Age  :     " << user[i].Age << endl;
        cout << "Email:     " << user[i].Email << endl;
        cout << "Rent a car with: \n";
        Cf->Get_car(j)->display();
        cout << "With deposit: " << d << endl;




    }
};

Car_fleet*initCarfleet(){
    Truck a(900);
    Lexus b(300);
    SUV c(400);
    Truck d(500);
    Lexus e(200);
    SUV f(400);
    Truck g(600);
    Lexus h(700);

    Car_fleet l;
    l.AddCar(&a);
    l.AddCar(&b);
    l.AddCar(&c);
    l.AddCar(&d);
    l.AddCar(&e);
    l.AddCar(&f);
    l.AddCar(&g);
    l.AddCar(&h);


    return &l;

}
Customer* initCustomer() {
    static Customer Clist[6];
    Customer a("Sasa",32,12354,"sasalala@gmail.com");
    Customer b("Tuan",23,22345,"Taun@gmail.com");
    Customer c("Lelouch",42,22346,"ll@gmail.com");
    Customer d("Hikami",30,32452,"sHKM@gmail.com");
    Customer e("Edward",22,23462,"ED@gmail.com");
    Customer f("Harry",44,25678,"Harry@gmail.com");
    Clist[0] = a;
    Clist[1] = b;
    Clist[2] = c;
    Clist[3] = d;
    Clist[4] = e;
    Clist[5] = f;

    return Clist;
}

int main(){

    Truck a(900);
    Lexus b(300);
    SUV c(400);
    Truck d(500);
    Lexus e(200);
    SUV f(400);
    Truck g(600);
    Lexus h(700);

    Car_fleet l;
    l.AddCar(&a);
    l.AddCar(&b);
    l.AddCar(&c);
    l.AddCar(&d);
    l.AddCar(&e);
    l.AddCar(&f);
    l.AddCar(&g);
    l.AddCar(&h);


    CaRentalMagmt crm (&l);
    crm.bookACar();
    /*
    int j;
    Customer* user;
    user = initCustomer();
    for(int i = 0; i<6; i++){
        cout << i <<" ";
        user[i].Display();
    }
    cout << "Who are you, please choose a number: \n";
    cin >> j;
    cout << "You are: ";
    user[j].Display();
    */


    return 0;
}