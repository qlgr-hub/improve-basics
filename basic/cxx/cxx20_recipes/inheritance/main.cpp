#include <cinttypes>
#include <iostream>

using namespace std;
//
// class Vehicle
// {
// private:
//     uint32_t m_NumberOfWheels{};
//
// public:
//     Vehicle(uint32_t numberOfWheels)
//         : m_NumberOfWheels{ numberOfWheels }
//     {
//
//     }
//
//     uint32_t GetNumberOfWheels() const
//     {
//         return m_NumberOfWheels;
//     }
// };
//
// class Car : public Vehicle
// {
// public:
//     Car()
//         :Vehicle(4)
//     {
//
//     }
// };
//
// class Motorcycle : public Vehicle
// {
// public:
//     Motorcycle()
//         :Vehicle(2)
//     {
//
//     }
// };
//
// int main()
// {
//     Car myCar{};
//     cout << "A car has " << myCar.GetNumberOfWheels() << " wheels." << endl;
//
//     Motorcycle myMotorcycle{};
//     cout << "A motorcycle has " << myMotorcycle.GetNumberOfWheels() << " wheels." << endl;
//
//     return 0;
// }
//
//
// class Vehicle
// {
// public:
//     uint32_t m_NumberOfWheels{};
//
//     Vehicle() = default;
// };
//
// class Car : public Vehicle
// {
// public:
//     Car()
//     {
//         m_NumberOfWheels = 4;
//     }
// };
//
// class Motorcycle : public Vehicle
// {
// public:
//     Motorcycle()
//     {
//         m_NumberOfWheels = 2;
//     }
// };
//
// int main()
// {
//     Car myCar{};
//     cout << "A car has " << myCar.m_NumberOfWheels << " wheels." << endl;
//     myCar.m_NumberOfWheels = 3;
//     cout << "A car has " << myCar.m_NumberOfWheels << " wheels." << endl;
//
//     Motorcycle myMotorcycle{};
//     cout << "A motorcycle has " << myMotorcycle.m_NumberOfWheels << " wheels." << endl;
//     myMotorcycle.m_NumberOfWheels = 3;
//     cout << "A motorcycle has " << myMotorcycle.m_NumberOfWheels << " wheels." << endl;
//
//     return 0;
// }
//
//
// class Vehicle
// {
// protected:
//     uint32_t m_NumberOfWheels{};
//
// public:
//     Vehicle() = default;
//
//     uint32_t GetNumberOfWheels() const
//     {
//         return m_NumberOfWheels;
//     }
// };
//
// class Car : public Vehicle
// {
// public:
//     Car()
//     {
//         m_NumberOfWheels = 4;
//     }
// };
//
// class Motorcycle : public Vehicle
// {
// public:
//     Motorcycle()
//     {
//         m_NumberOfWheels = 2;
//     }
// };
//
// int main()
// {
//     Car myCar{};
//     cout << "A car has " << myCar.GetNumberOfWheels() << " wheels." << endl;
//
//     Motorcycle myMotorcycle{};
//     cout << "A motorcycle has " << myMotorcycle.GetNumberOfWheels() << " wheels." << endl;
//
//     return 0;
// }
//
//
// class Vehicle
// {
// public:
//     Vehicle() = default;
//
//     uint32_t GetNumberOfWheels() const
//     {
//         return 0;
//     }
// };
//
// class Car : public Vehicle
// {
// public:
//     Car() = default;
//
//     uint32_t GetNumberOfWheels() const
//     {
//         return 4;
//     }
// };
//
// class Motorcycle : public Vehicle
// {
// public:
//     Motorcycle() = default;
//
//     uint32_t GetNumberOfWheels() const
//     {
//         return 2;
//     }
// };
//
// int main()
// {
//     Car myCar{};
//     cout << "A car has " << myCar.GetNumberOfWheels() << " wheels." << endl;
//
//     Motorcycle myMotorcycle{};
//     cout << "A motorcycle has " << myMotorcycle.GetNumberOfWheels() << " wheels." << endl;
//
//     // 覆盖没有多态性
//     //Vehicle* myMotorcycle1{ &myMotorcycle };
//     //cout << "A motorcycle has " << myMotorcycle1->GetNumberOfWheels() << " wheels." << endl;
//
//     return 0;
// }
//
//
// class Vehicle
// {
// public:
//     Vehicle() = default;
//
//     virtual uint32_t GetNumberOfWheels() const //final 不让重写
//     {
//         return 2;
//     }
// };
//
// class Car : public Vehicle
// {
// public:
//     Car() = default;
//
//     uint32_t GetNumberOfWheels() const final//override
//     {
//         return 4;
//     }
// };
//
// class Motorcycle : public Vehicle
// {
// public:
//     Motorcycle() = default;
// };
//
// class Ferrari : public Car
// {
// public:
//     Ferrari() = default;
//
//     // 不让
//     // uint32_t GetNumberOfWheels() const override
//     // {
//     //     return 5;
//     // }
// };
//
// int main()
// {
//     Vehicle* pVehicle{};
//
//     Vehicle myVehicle{};
//     pVehicle = &myVehicle;
//     cout << "A vehicle has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;
//
//     Car myCar{};
//     pVehicle = &myCar;
//     cout << "A car has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;
//
//     Motorcycle myMotorcycle{};
//     pVehicle = &myMotorcycle;
//     cout << "A motorcycle has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;
//
//     return 0;
// }
//
//
// class Vehicle
// {
// public:
//     Vehicle() = default;
//
//     virtual uint32_t GetNumberOfWheels() const = 0;
// };
//
// class Car : public Vehicle
// {
// public:
//     Car() = default;
//
//     uint32_t GetNumberOfWheels() const override
//     {
//         return 4;
//     }
// };
//
// class Motorcycle : public Vehicle
// {
// public:
//     Motorcycle() = default;
//
//     uint32_t GetNumberOfWheels() const override
//     {
//         return 2;
//     }
// };
//
// int main()
// {
//     Vehicle* pVehicle{};
//
//     Car myCar{};
//     pVehicle = &myCar;
//     cout << "A car has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;
//
//     Motorcycle myMotorcycle{};
//     pVehicle = &myMotorcycle;
//     cout << "A motorcycle has " << pVehicle->GetNumberOfWheels() << " wheels." << endl;
//
//     return 0;
// }
//
//
class Printable
{
public:
    virtual void Print() = 0;
};

class Vehicle
{
public:
    Vehicle() = default;

    virtual uint32_t GetNumberOfWheels() const = 0;
};

class Car 
    : public Vehicle
    , public Printable
{
public:
    Car() = default;

    uint32_t GetNumberOfWheels() const override
    {
        return 4;
    }

    void Print() override
    {
        cout << "A car has " << GetNumberOfWheels() << " wheels." << endl;
    }
};

class Motorcycle
    : public Vehicle
    , public Printable
{
public:
    Motorcycle() = default;

    uint32_t GetNumberOfWheels() const override
    {
        return 2;
    }

    void Print() override
    {
        cout << "A motorcycle has " << GetNumberOfWheels() << " wheels." << endl;
    }
};

int main()
{
    Printable* pPrintable{};

    Car myCar{};
    pPrintable = &myCar;
    pPrintable->Print();

    Motorcycle myMotorcycle{};
    pPrintable = &myMotorcycle;
    pPrintable->Print();

    return 0;
}