#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cinttypes>

using namespace std;

class SmallBlockAllocator
{
public:
    static const unsigned int BLOCK_SIZE{ 32 };

private:
    static const unsigned int NUM_BLOCKS{ 1024 };
    static const unsigned int PAGE_SIZE{ NUM_BLOCKS * BLOCK_SIZE };

    class Page
    {
    private:
        char m_Memory[PAGE_SIZE];
        bool m_Free[NUM_BLOCKS];
        Page* m_pNextPage;

    public:
        Page()
            : m_pNextPage{ nullptr }
        {
            memset(m_Free, 1, NUM_BLOCKS);
        }

        ~Page()
        {
            if (m_pNextPage) {
                delete m_pNextPage;
                m_pNextPage = nullptr;
            }
        }

        void* Alloc()
        {
            void* pMem{ nullptr };
            
            for (unsigned int i{ 0 }; i < NUM_BLOCKS; ++i) {
                if (m_Free[i] == true) {
                    m_Free[i] = false;
                    pMem = &m_Memory[i * BLOCK_SIZE];
                    break;
                }
            }

            if (pMem == nullptr) {
                if (m_pNextPage == nullptr) {
                    m_pNextPage = new Page{};
                }

                pMem = m_pNextPage->Alloc();
            }

            return pMem;
        }

        bool Free(void* pMem)
        {
            bool freed{ false };

            bool inPage{ pMem >= m_Memory && pMem <= &m_Memory[(NUM_BLOCKS * BLOCK_SIZE) - 1] };

            if (inPage) {
                uint64_t index{ (reinterpret_cast<uint64_t>(pMem) - reinterpret_cast<uint64_t>(m_Memory)) / BLOCK_SIZE };

                m_Free[index] = true;
                freed = true;
            }
            else if (m_pNextPage) {
                freed = m_pNextPage->Free(pMem);

                if (freed && m_pNextPage->IsEmpty()) {
                    Page* old = m_pNextPage;
                    m_pNextPage = old->m_pNextPage;
                    old->m_pNextPage = nullptr;
                    delete old;
                }
            }

            return freed;
        }

        bool IsEmpty() const
        {
            bool isEmpty{ true };

            for (unsigned int i{ 0 }; i < NUM_BLOCKS; ++i) {
                if (m_Free[i] == false) {
                    isEmpty = false;
                    break;
                }
            }

            return isEmpty;
        }
    };
    Page m_FirstPage;

public:
    SmallBlockAllocator() = default;

    void* Alloc()
    {
        return m_FirstPage.Alloc();
    }

    bool Free(void* pMem)
    {
        return m_FirstPage.Free(pMem);
    }
};
static SmallBlockAllocator sba;

void* operator new (size_t numBytes, const std::nothrow_t& tag) noexcept
{
    void* pMem{ nullptr };

    if (numBytes <= SmallBlockAllocator::BLOCK_SIZE) {
        pMem = sba.Alloc();
    }
    else {
        pMem = malloc(numBytes);
    }

    return pMem;
}

void* operator new[](size_t numBytes, const std::nothrow_t& tag) noexcept
{
    void* pMem{ nullptr };

    if (numBytes <= SmallBlockAllocator::BLOCK_SIZE) {
        pMem = sba.Alloc();
    }
    else {
        pMem = malloc(numBytes);
    }

    return pMem;
}

void operator delete(void* pMemory) noexcept
{
    if (!sba.Free(pMemory)) {
        free(pMemory);
    }
}

void operator delete[](void* pMemory) noexcept
{
    if (!sba.Free(pMemory)) {
        free(pMemory);
    }
}

#define new new(nothrow_t{})

int main()
{
    const unsigned int NUM_ALLOCS{ 2148 };
    int32_t* pInts[NUM_ALLOCS];

    cout << "[main] ..." << endl;

    for (unsigned int i{ 0 }; i < NUM_ALLOCS; ++i) {
        pInts[i] = new int32_t;
        *pInts[i] = i;
    }

    for (unsigned int i{ 0 }; i < NUM_ALLOCS; ++i) {
        delete pInts[i];
        pInts[i] = nullptr;
    }

    return 0;
}
















//////////////////////////////////////////////////////////////////////////////////////////////////////////
// #include <iostream>
// #include <memory>
// #include <cstdlib>
// #include <chrono>
//
// using namespace std;
//
// unsigned int counter = 0;
//
// void IncreaseCounter()
// {
//     counter += 10;
//     cout << "[IncreaseCounter] counter is " << counter << endl;
// }
//
// void Function()
// {
//     int a = 0;
//     cout << a << endl;
// }
//
//
//
// class MyClass
// {
// public:
//     MyClass()
//     {
//         cout << "Constructor called!" << endl;
//     }
//
//     ~MyClass()
//     {
//         cout << "Destructor called!" << endl;
//     }
// };
//
// class MyClass
// {
// private:
//     static int m_Count;
//     int m_Instance{ -1 };
// public:
//     MyClass()
//         : m_Instance{ m_Count++ }
//     {
//         cout << "Constructor called on " << m_Instance << endl;
//     }
//
//     ~MyClass()
//     {
//         cout << "Destructor called on " << m_Instance << endl;
//     }
// };
// int MyClass::m_Count{ 0 };
//
//
//
// class MyClass
// {
// private:
//     int m_Number{ 0 };
//
// public:
//     MyClass(int value)
//         : m_Number{ value }
//     {
//
//     }
//
//     ~MyClass()
//     {
//         cout << "Destroying " << m_Number << endl;
//     }
//
//     void operator=(const int value)
//     {
//         m_Number = value;
//     }
//
//     int GetNumber() const
//     {
//         return m_Number;
//     }
// };
// using SharedMyClass = shared_ptr<MyClass>;
//
// void ChangeSharedValue(SharedMyClass sharedMyClass)
// {
//     if (sharedMyClass != nullptr) {
//         *sharedMyClass = 100;
//     }
// }
//
//using UniqueMyClass = unique_ptr<MyClass>;
//
// void CreateUniqueObject()
// {
//     UniqueMyClass uniqueMyClass{ make_unique<MyClass>(10) };
// }
//
// void CreateUniqueObject(UniqueMyClass& referenceToUniquePtr)
// {
//     UniqueMyClass uniqueMyClass{ make_unique<MyClass>(10) };
//
//     cout << hex << showbase;
//     cout << "Adress in uniqueMyClass " << uniqueMyClass.get() << endl;
//
//     referenceToUniquePtr.swap(uniqueMyClass);
//
//     cout << "Adress in uniqueMyClass " << uniqueMyClass.get() << endl;
// }
//
//
// class ReferenceCount
// {
// private:
//     int m_Count{ 0 };
//
// public:
//     void Increment()
//     {
//         ++m_Count;
//     }
//
//     int Decrement()
//     {
//         return --m_Count;
//     }
//
//     int GetCount() const
//     {
//         return m_Count;
//     }
// };
//
// template<typename T>
// class SmartPointer
// {
// private:
//     T* m_Object{ nullptr };
//     ReferenceCount* m_ReferenceCount{ nullptr };
//
// public:
//     SmartPointer() = default;
//
//     SmartPointer(T* object)
//         : m_Object{ object }
//         , m_ReferenceCount{ new ReferenceCount() }
//     {
//         m_ReferenceCount->Increment();
//
//         cout << "Create smart pointer! Reference count is " << m_ReferenceCount->GetCount() << endl;
//     }
//
//     virtual ~SmartPointer()
//     {
//         if (m_ReferenceCount) {
//             int decrementCount = m_ReferenceCount->Decrement();
//             cout << "Destroy smart pointer! Reference count is " << decrementCount << endl;
//
//             if (decrementCount == 0) {
//                 delete m_ReferenceCount;
//                 delete m_Object;
//             }
//             m_ReferenceCount = nullptr;
//             m_Object = nullptr;
//         }
//     }
//
//     SmartPointer(const SmartPointer<T>& other)
//         : m_Object{ other.m_Object }
//         , m_ReferenceCount{ other.m_ReferenceCount }
//     {
//         m_ReferenceCount->Increment();
//         cout << "Copied smart pointer! Reference count is " << m_ReferenceCount->GetCount() << endl;
//     }
//
//     SmartPointer<T>& operator=(const SmartPointer<T>& other)
//     {
//         if (this != &other) {
//             if (m_ReferenceCount && m_ReferenceCount->Decrement() == 0) {
//                 delete m_ReferenceCount;
//                 delete m_Object;
//             }
//             m_Object = other.m_Object;
//             m_ReferenceCount = other.m_ReferenceCount;
//             m_ReferenceCount->Increment();
//         }
//
//         cout << "Assigning smart pointer! Reference count is " << m_ReferenceCount->GetCount() << endl;
//
//         return *this;
//     }
//
//     SmartPointer(SmartPointer<T>&& other)
//         : m_Object{ other.m_Object }
//         , m_ReferenceCount{ other.m_ReferenceCount }
//     {
//         other.m_Object = nullptr;
//         other.m_ReferenceCount = nullptr;
//     }
//
//     SmartPointer<T>& operator=(SmartPointer<T>&& other)
//     {
//         if (this != &other) {
//             if (m_ReferenceCount && m_ReferenceCount->Decrement() == 0) {
//                 delete m_ReferenceCount;
//                 delete m_Object;
//             }
//             m_Object = other.m_Object;
//             m_ReferenceCount = other.m_ReferenceCount;
//          
//             other.m_Object = nullptr;
//             other.m_ReferenceCount = nullptr;
//         }
//
//         return *this;
//     }
//
//     T& operator*()
//     {
//         return *m_Object;
//     }
// };
//
// struct MyStruct
// {
// public:
//     int m_Value{ 0 };
//     ~MyStruct()
//     {
//         cout << "Destroying MyStruct object!" << endl;
//     }
// };
// using SmartMyStructPointer = SmartPointer< MyStruct >;
//
// SmartMyStructPointer PassValue(SmartMyStructPointer smartPointer)
// {
//     SmartMyStructPointer returnValue;
//     returnValue = smartPointer;
//     return returnValue;
// }
//
//
//
// struct MemoryHeader
// {
//     const char* m_FileName{ nullptr };
//     int m_Line{ -1 };
// };
//
// void* operator new(size_t size, const char* filename, int line) noexcept
// {
//     void* pMemory{ malloc(size + sizeof(MemoryHeader)) };
//
//     MemoryHeader* pMemoryHeader{ reinterpret_cast<MemoryHeader*>(pMemory) };
//     pMemoryHeader->m_FileName = filename;
//     pMemoryHeader->m_Line = line;
//
//     return reinterpret_cast<void*>(static_cast<char*>(pMemory) + sizeof(MemoryHeader));
// }
//
// void* operator new[](size_t size, const char* filename, int line) noexcept
// {
//     void* pMemory{ malloc(size + sizeof(MemoryHeader)) };
//
//     MemoryHeader* pMemoryHeader{ reinterpret_cast<MemoryHeader*>(pMemory) };
//     pMemoryHeader->m_FileName = filename;
//     pMemoryHeader->m_Line = line;
//
//     return reinterpret_cast<void*>(static_cast<char*>(pMemory) + sizeof(MemoryHeader));
// }
//
// void operator delete(void* pMemory) noexcept
// {
//     char* pMemoryHeaderStart{ reinterpret_cast<char*>(pMemory) - sizeof(MemoryHeader) };
//     MemoryHeader* pMemoryHeader{ reinterpret_cast<MemoryHeader*>(pMemoryHeaderStart) };
//
//     cout << "Deleting memory allocated from: " << pMemoryHeader->m_FileName << ":" << pMemoryHeader->m_Line << endl;
//
//     free(pMemoryHeader);
// }
//
// void operator delete[](void* pMemory) noexcept
// {
//     char* pMemoryHeaderStart{ reinterpret_cast<char*>(pMemory) - sizeof(MemoryHeader) };
//     MemoryHeader* pMemoryHeader{ reinterpret_cast<MemoryHeader*>(pMemoryHeaderStart) };
//
//     cout << "Deleting memory allocated from: " << pMemoryHeader->m_FileName << ":" << pMemoryHeader->m_Line << endl;
//
//     free(pMemoryHeader);
// }
//
// class MyClass
// {
// private:
//     int m_Value{ 1 };
//
// public:
//     void* operator new(size_t size, const char* filename, int line) noexcept
//     {
//         cout << "Allocating memory for MyClass!" << endl;
//         return malloc(size);
//     }
//
//     void operator delete(void* pMemory) noexcept
//     {
//         cout << "Freeing memory for MyClass!" << endl;
//         free(pMemory);
//     }
// };
//
// #define new new(__FILE__, __LINE__)
//
//
//
// void RunTest(unsigned int numberIterations)
// {
//     auto start = chrono::high_resolution_clock::now();
//
//     for (unsigned int i{ 0 }; i < numberIterations; ++i) {
//         unsigned int squared{ i*i*i };
//     }
//
//     auto end = chrono::high_resolution_clock::now();
//     auto difference = end - start;
//
//     cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(difference).count() << " microseconds!" << endl;
// }
//
//
// const int NUM_ROWS{ 10000 };
// const int NUM_COLUMNS{ 1000 };
// int elements[NUM_ROWS][NUM_COLUMNS];
// int *pElements[NUM_ROWS][NUM_COLUMNS];
//
//
int main1()
{
    // counter += 5;
    // cout << "[main] counter is " << counter << endl;
    //
    // IncreaseCounter();
    //
    // int counter = 999;
    // cout << "Local counter is " << counter << endl;
    // IncreaseCounter();
    // cout << "Local counter is " << counter << endl;
    //
    //
    //
    //Function();
    //
    // MyClass myClass1;
    // {
    //     MyClass myClass2;
    //     {
    //         MyClass myClass3;
    //     }
    // }
    //
    //
    //
    // int* pInt{ new int };
    // *pInt = 100;
    //
    // cout << hex << "The address at pInt is " << pInt << endl;
    // cout << dec << "The value at pInt is " << *pInt << endl;
    //
    // delete pInt;
    // pInt = nullptr;
    //
    //
    //
    // const unsigned int NUM_ELEMENTS{ 5 };
    // MyClass* pObjects{ new MyClass[NUM_ELEMENTS] };
    // pObjects[0] = 100;
    // pObjects[1] = 45;
    // pObjects[2] = 31;
    // pObjects[3] = 90;
    // pObjects[4] = 58;
    //
    // delete[] pObjects;
    // pObjects = nullptr;
    //
    // SharedMyClass sharedMyClass{ new MyClass(10) };
    // ChangeSharedValue(sharedMyClass);
    //
    //
    // cout << "Begin Main!" << endl;
    //
    // CreateUniqueObject();
    //
    // cout << "Back in Main!" << endl;
    //
    //
    // cout << "Begin Main!" << endl;
    // UniqueMyClass uniqueMyClass;
    // CreateUniqueObject(uniqueMyClass);
    //
    // cout << "Adress in main's uniqueMyClass " << uniqueMyClass.get() << endl;
    //
    // cout << dec << showbase << "Back in Main!" << endl;
    //
    //
    //
    // SmartMyStructPointer smartPointer{ new MyStruct };
    // (*smartPointer).m_Value = 10;
    // SmartMyStructPointer secondSmartPointer = PassValue(smartPointer);
    //
    //
    //
    // int* pInt{ new int };
    // *pInt = 1;
    // delete pInt;
    //
    // MyClass* pClass{ new MyClass };
    // delete pClass;
    //
    // const unsigned int NUM_ELEMENTS{ 5 };
    // int* pArry{ new int[NUM_ELEMENTS] };
    // delete[] pArry;
    //
    //
    //
    // RunTest(10000000);
    // RunTest(100000000);
    // RunTest(1000000000);
    //
    //
    //
    // for (int i{ 0 }; i < NUM_ROWS; ++i) {
    //     for (int j{ 0 }; j < NUM_COLUMNS; ++j) {
    //         elements[i][j] = i*j;
    //         pElements[i][j] = new int{ elements[i][j] };
    //     }
    // }
    //
    // //
    // auto start = chrono::high_resolution_clock::now();
    //
    // for (int i{ 0 }; i < NUM_ROWS; ++i) {
    //     for (int j{ 0 }; j < NUM_COLUMNS; ++j) {
    //         const int result{ elements[j][i] };
    //     }
    // }
    //
    // auto end = chrono::high_resolution_clock::now();
    // auto difference = end - start;
    //
    // cout << "Time taken for j then i: " << chrono::duration_cast<chrono::microseconds>(difference).count() << " microsecond!" << endl;
    //
    // //
    // start = chrono::high_resolution_clock::now();
    //
    // for (int i{ 0 }; i < NUM_ROWS; ++i) {
    //     for (int j{ 0 }; j < NUM_COLUMNS; ++j) {
    //         const int result{ elements[i][j] };
    //     }
    // }
    //
    // end = chrono::high_resolution_clock::now();
    // difference = end - start;
    //
    // cout << "Time taken for j then i: " << chrono::duration_cast<chrono::microseconds>(difference).count() << " microsecond!" << endl;
    //
    // //
    // start = chrono::high_resolution_clock::now();
    //
    // for (int i{ 0 }; i < NUM_ROWS; ++i) {
    //     for (int j{ 0 }; j < NUM_COLUMNS; ++j) {
    //         const int result{ elements[i][j] };
    //     }
    // }
    //
    // end = chrono::high_resolution_clock::now();
    // difference = end - start;
    //
    // cout << "Time taken for i then j: " << chrono::duration_cast<chrono::microseconds>(difference).count() << " microsecond!" << endl;
    //
    // //
    // start = chrono::high_resolution_clock::now();
    //
    // for (int i{ 0 }; i < NUM_ROWS; ++i) {
    //     for (int j{ 0 }; j < NUM_COLUMNS; ++j) {
    //         const int result{ *(pElements[i][j]) };
    //     }
    // }
    //
    // end = chrono::high_resolution_clock::now();
    // difference = end - start;
    //
    // cout << "Time taken for pointers with i then j: " << chrono::duration_cast<chrono::microseconds>(difference).count() << " microsecond!" << endl;

    return 0;
}