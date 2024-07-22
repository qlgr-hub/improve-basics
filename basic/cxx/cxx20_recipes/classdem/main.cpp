#include <cinttypes>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

// class Vehicle
// {
// private:
//     uint32_t m_NumberOfWheels;
//
// public:
//     void SetNumberOfWheels(uint32_t numberOfWheels)
//     {
//         m_NumberOfWheels = numberOfWheels;
//     }
//
//     uint32_t GetNumberOfWheels()
//     {
//         return m_NumberOfWheels;
//     }
// };
//
// class Wheel
// {
//
// };
//
// class Vehicle
// {
// private:
//     using Wheels = vector<Wheel>;
//     Wheels m_Wheels;
//
// public:
//     void SetNumberOfWheels(uint32_t numberOfWheels)
//     {
//         m_Wheels.clear();
//         for (uint32_t i = 0; i < numberOfWheels; ++i) {
//             m_Wheels.push_back({});
//         }
//     }
//
//     uint32_t GetNumberOfWheels()
//     {
//         return m_Wheels.size();
//     }
// };
//
// int main(int argc, char* argv[])
// {
//     Vehicle myCar;
//     //myCar.m_NumberOfWheels = 4;
//     myCar.SetNumberOfWheels(4);
//
//     cout << "Number of wheels: " << myCar.GetNumberOfWheels() << endl;
//
//     Vehicle myMotorcycle;
//     myMotorcycle.SetNumberOfWheels(2);
//     cout << "Number of wheels: " << myMotorcycle.GetNumberOfWheels() << endl;
//
//     return 0;
// }
//
// class Vehicle
// {
// private:
//     uint32_t m_NumberOfWheels{};
//
// public:
//     Vehicle() = default;
//
//     Vehicle(uint32_t numberOfWheels)
//         : m_NumberOfWheels{ numberOfWheels }
//     {
//
//     }
//
//     uint32_t GetNumberOfWheels()
//     {
//         return m_NumberOfWheels;
//     }
// };
//
// int main(int argc, char* argv[])
// {
//     //Vehicle myCar;
//     Vehicle myCar{ 4 };
//     cout << "Number of wheels: " << myCar.GetNumberOfWheels() << endl;
//
//     //Vehicle myMotorcycle;
//     Vehicle myMotorcycle{ 2 };
//     cout << "Number of wheels: " << myMotorcycle.GetNumberOfWheels() << endl;
//
//     Vehicle noWheels;
//     cout << "Number of wheels: " << noWheels.GetNumberOfWheels() << endl;
//
//     return 0;
// }
//
//
// class Vehicle
// {
// private:
//     string m_Name;
//     uint32_t m_NumberOfWheels{};
//
// public:
//     Vehicle() = default;
//
//     Vehicle(string name, uint32_t numberOfWheels)
//         : m_Name{ name }
//         , m_NumberOfWheels{ numberOfWheels }
//     {
//
//     }
//
//     ~Vehicle() = default;
//     // ~Vehicle()
//     // {
//     //     cout << m_Name << " is being destroyed!" << endl;
//     // }
//
//     uint32_t GetNumberOfWheels()
//     {
//         return m_NumberOfWheels;
//     }
// };
//
// int main(int argc, char* argv[])
// {
//     Vehicle myCar{ "myCar", 4 };
//     cout << "Number of wheels: " << myCar.GetNumberOfWheels() << endl;
//
//     Vehicle myMotorcycle{ "myMotorcycle", 2 };
//     cout << "Number of wheels: " << myMotorcycle.GetNumberOfWheels() << endl;
//
//     Vehicle noWheels;
//     cout << "Number of wheels: " << noWheels.GetNumberOfWheels() << endl;
//
//     return 0;
// }
//
//
// class Vehicle
// {
// private:
//     string m_Name;
//     uint32_t m_NumberOfWheels{};
//
// public:
//     Vehicle() = default;
//
//     Vehicle(string name, uint32_t numberOfWheels)
//         : m_Name{ name }
//         , m_NumberOfWheels{ numberOfWheels }
//     {
//
//     }
//
//     ~Vehicle()
//     {
//         cout << m_Name << " at " << this << " is being destroyed!" << endl;
//     }
//
//     Vehicle(const Vehicle& other) = default;
//     Vehicle& operator=(const Vehicle& other) = default;
//
//     // Vehicle(const Vehicle& other) = delete;
//     // Vehicle& operator=(const Vehicle& other) = delete;
//
//     uint32_t GetNumberOfWheels()
//     {
//         return m_NumberOfWheels;
//     }
// };
//
// int main(int argc, char* argv[])
// {
//     Vehicle myCar{ "myCar", 4 };
//     cout << "Number of wheels: " << myCar.GetNumberOfWheels() << endl;
//
//     Vehicle myMotorcycle{ "myMotorcycle", 2 };
//     cout << "Number of wheels: " << myMotorcycle.GetNumberOfWheels() << endl;
//
//     Vehicle noWheels;
//     cout << "Number of wheels: " << noWheels.GetNumberOfWheels() << endl;
//
//     Vehicle myCopiedCar{ myCar };
//     cout << "Number of wheels: " << myCopiedCar.GetNumberOfWheels() << endl;
//
//     Vehicle mySecondCopy = myCopiedCar;
//     cout << "Number of wheels: " << mySecondCopy.GetNumberOfWheels() << endl;
//
//     return 0;
// }
//
//
// class Vehicle
// {
// private:
//     char* m_Name{};
//     uint32_t m_NumberOfWheels{};
//
// public:
//     Vehicle() = default;
//
//     Vehicle(const char* name, uint32_t numberOfWheels)
//         : m_NumberOfWheels{ numberOfWheels }
//     {
//         const uint32_t length = strlen(name) + 1;
//
//         m_Name = new char[length]{};
//         strcpy(m_Name, name);
//     }
//
//     ~Vehicle()
//     {
//         delete[] m_Name;
//         m_Name = nullptr;
//     }
//
//     // Vehicle(const Vehicle& other) = default;
//     // Vehicle& operator=(const Vehicle& other) = default;
//
//     Vehicle(const Vehicle& other)
//     {
//         const uint32_t length = strlen(other.m_Name) + 1;
//
//         m_Name = new char[length]{};
//         strcpy(m_Name, other.m_Name);
//
//         m_NumberOfWheels = other.m_NumberOfWheels;
//     }
//
//     Vehicle& operator=(const Vehicle& other)
//     {
//         if (m_Name != nullptr) {
//             delete[] m_Name;
//             m_Name = nullptr;
//         }
//
//         const uint32_t length = strlen(other.m_Name) + 1;
//
//         m_Name = new char[length]{};
//         strcpy(m_Name, other.m_Name);
//
//         m_NumberOfWheels = other.m_NumberOfWheels;
//
//         return *this;
//     }
//
//     char* GetName()
//     {
//         return m_Name;
//     }
//
//     uint32_t GetNumberOfWheels()
//     {
//         return m_NumberOfWheels;
//     }
// };
//
// int main(int argc, char* argv[])
// {
//     Vehicle myAssignedCar;
//     {
//         Vehicle myCar{ "myCar", 4 };
//         cout << "Vehicle name: " << myCar.GetName() << endl;
//         myAssignedCar = myCar;
//         cout << "Vehicle name: " << myAssignedCar.GetName() << endl;
//     }
//    
//     cout << "Vehicle name: " << myAssignedCar.GetName() << endl;
//
//     return 0;
// }
//
//
// class Vehicle
// {
// private:
//     char* m_Name{};
//     uint32_t m_NumberOfWheels{};
//
// public:
//     Vehicle() = default;
//
//     Vehicle(const char* name, uint32_t numberOfWheels)
//         : m_NumberOfWheels{ numberOfWheels }
//     {
//         const uint32_t length = strlen(name) + 1;
//
//         m_Name = new char[length]{};
//         strcpy(m_Name, name);
//     }
//
//     ~Vehicle()
//     {
//         delete[] m_Name;
//         m_Name = nullptr;
//     }
//
//     // Vehicle(const Vehicle& other) = default;
//     // Vehicle& operator=(const Vehicle& other) = default;
//
//     Vehicle(const Vehicle& other)
//     {
//         const uint32_t length = strlen(other.m_Name) + 1;
//
//         m_Name = new char[length]{};
//         strcpy(m_Name, other.m_Name);
//       
//         m_NumberOfWheels = other.m_NumberOfWheels;
//     }
//
//     Vehicle& operator=(const Vehicle& other)
//     {
//         if (m_Name != nullptr) {
//             delete[] m_Name;
//             m_Name = nullptr;
//         }
//
//         const uint32_t length = strlen(other.m_Name) + 1;
//
//         m_Name = new char[length]{};
//         strcpy(m_Name, other.m_Name);
//
//         m_NumberOfWheels = other.m_NumberOfWheels;
//
//         return *this;
//     }
//
//     Vehicle(Vehicle&& other)
//     {
//         m_Name = other.m_Name;
//         other.m_Name = nullptr;
//
//         m_NumberOfWheels = other.m_NumberOfWheels;
//     }
//
//     Vehicle& operator=(Vehicle&& other)
//     {
//         if (m_Name != nullptr) {
//             delete[] m_Name;
//             m_Name = nullptr;
//         }
//
//         m_Name = other.m_Name;
//         other.m_Name = nullptr;
//
//         m_NumberOfWheels = other.m_NumberOfWheels;
//
//         return *this;
//     }
//
//     char* GetName()
//     {
//         return m_Name;
//     }
//
//     uint32_t GetNumberOfWheels()
//     {
//         return m_NumberOfWheels;
//     }
// };
//
// int main(int argc, char* argv[])
// {
//     Vehicle myAssignedCar;
//     {
//         Vehicle myCar{ "myCar", 4 };
//         cout << "Vehicle name: " << myCar.GetName() << endl;
//         myAssignedCar = move(myCar);
//         //cout << "Vehicle name: " << myCar.GetName() << endl;
//         cout << "Vehicle name: " << myAssignedCar.GetName() << endl;
//     }
//    
//     cout << "Vehicle name: " << myAssignedCar.GetName() << endl;
//
//     return 0;
// }


class Invoice
{
public:
    float sub_total;
    void get_sub()
    {
        cin >> sub_total;
    }

    virtual float do_math() = 0;
};

class Discount : public Invoice
{
public:
    float do_math()
    {
        return (sub_total * 1 -(sub_total * .10));
    }
};

class No_Discount : public Invoice
{
public:
    float do_math()
    {
        return (sub_total * 1);
    }
};

int main()
{
    Discount d;
    No_Discount n;

    cout << "Enter subtotal for discount: \n";
    d.get_sub();
    cout << "Discount amount is: " << d.do_math() << endl;

    cout << "Enter subtotal for no discount: \n";
    n.get_sub();
    cout << "No Discount cost is: " << n.do_math() << endl;

    return 0;
}