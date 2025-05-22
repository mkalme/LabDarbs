#include <iostream>

class Exception : public std::exception {
public:
    Exception() {
        m_message = 0;
    }

    Exception(const char* message) {
        m_message = message;
    }

    const char* what() const override {
        return m_message;
    }
private:
    const char* m_message;
};

class Vehicle {
public:
    Vehicle() {
        m_reģistrācijas_numurs = "";
        m_valsts_ražotājs = "";
        m_ražošanas_gads = 0;
    }
    
    Vehicle(const char* reģistrācijas_numurs, const char* valsts_ražotājs, int ražošanas_gads) {
        m_reģistrācijas_numurs = reģistrācijas_numurs;
        m_valsts_ražotājs = valsts_ražotājs;
        m_ražošanas_gads = ražošanas_gads;
    }

    virtual ~Vehicle() {
        std::cout << "Deleting a vehicle\n";
    }

    const char* Get_reģistrācijas_numurs() const {
        return m_reģistrācijas_numurs;
    }

    const char* Get_valsts_ražotājs() const {
        return m_valsts_ražotājs;
    }

    int Get_ražošanas_gads() const {
        return m_ražošanas_gads;
    }

    void Set_reģistrācijas_numurs(const char* reģistrācijas_numurs) {
        m_reģistrācijas_numurs = reģistrācijas_numurs;
    }

    void Set_valsts_ražotājs(const char* valsts_ražotājs) {
        m_valsts_ražotājs = valsts_ražotājs;
    }

    void Set_ražošanas_gads(int ražošanas_gads) {
        m_ražošanas_gads = ražošanas_gads;
    }

    friend std::ostream& operator << (std::ostream& stream, const Vehicle& vehicle) {
        stream << "Registration number: " << vehicle.m_reģistrācijas_numurs << ", " << "country of origin: " << vehicle.m_valsts_ražotājs << ", manufacturing year: " << vehicle.m_ražošanas_gads;
        return stream;
    }
private:
    const char* m_reģistrācijas_numurs;
    const char* m_valsts_ražotājs;
    int m_ražošanas_gads;
};

class Car : protected Vehicle {
public:
    Car() : Vehicle() {
        m_jauda = 0;
    }

    Car(const char* reģistrācijas_numurs, const char* valsts_ražotājs, int ražošanas_gads, int jauda) : Vehicle(reģistrācijas_numurs, valsts_ražotājs, ražošanas_gads) {
        m_jauda = jauda;
    }

    ~Car() {
        std::cout << "Deleting a car\n";
    }

    uint32_t Get_jauda() const {
        return m_jauda;
    }

    void Set_jauda(uint32_t jauda) {
        m_jauda = jauda;
    }

    friend std::ostream& operator << (std::ostream& stream, const Car& car) {
        const Vehicle& vehicle = car;
        stream << vehicle;
        stream << ", power: " << car.m_jauda;
        return stream;
    }
private:
    uint32_t m_jauda;
};

class CarPark {
public:
    CarPark() : CarPark(m_default_max_size) {}

    CarPark(int maxSize) {
        m_max_size = maxSize;
        m_current_index = -1;
        m_internal_array = new CarPointer[m_max_size];
    }

    ~CarPark() {
        for (int i = 0; i < m_current_index + 1; i++) {
            delete m_internal_array[i];
        }

        delete m_internal_array;

        std::cout << "Deleting a car park\n";
    }

    uint32_t GetMaxPower() const {
        if (m_current_index < 0) throw Exception("The car park is empty.");
        
        uint32_t output = 0;

        for (int i = 0; i < m_current_index + 1; i++) {
            uint32_t power = m_internal_array[i]->Get_jauda();
            if (power > output) output = power;
        }

        return output;
    }

    friend std::ostream& operator << (std::ostream& stream, const CarPark& car) {
        stream << "Amount of cars: " << (car.m_current_index + 1) << "\n";

        for (int i = 0; i < car.m_current_index + 1; i++) {
            stream << *car.m_internal_array[i];
            stream << "\n";
        }

        return stream;
    }

    void operator += (Car& car) {
        if (m_current_index >= m_max_size - 1) throw Exception("Exceeded the maximum size of the car park.");
        m_internal_array[++m_current_index] = &car;
    }

    void operator += (Car* car) {
        *this += *car;
    }
private:
    const static int m_default_max_size = 2;
    const typedef Car* CarPointer;

    int m_max_size;
    int m_current_index;
    CarPointer* m_internal_array;
};

int main()
{
    Car* car1 = new Car("GB-3441", "JP", 2002, 20000);
    Car* car2 = new Car("AM-9492", "GE", 2014, 500000);
    CarPark* park = new CarPark();

    *park += car1;
    *park += *car2;
    std::cout << *park;

    system("pause");
}