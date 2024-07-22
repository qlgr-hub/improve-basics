#include <iostream>
#include <thread>
#include <cstdlib>
#include <stack>
#include <vector>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <future>
#include <cassert>

using namespace std;

// void ThreadTask()
// {
//     for (unsigned int i{ 0 }; i < 20; ++i) {
//         cout << "Output from thread" << endl;
//     }
// }
//
//
// class MyManagedObject
// {
// private:
//     static const unsigned int MAX_OBJECTS{ 8 };
//    
//     using MyManagedObjectCollection = vector< MyManagedObject >;
//     static MyManagedObjectCollection s_ManagedObjects;
//    
//     static stack<unsigned int> s_FreeList;
//
//     static mutex s_Mutex;
//
//     // static thread_local const unsigned int MAX_OBJECTS;
//     //
//     // using MyManagedObjectCollection = vector< MyManagedObject >;
//     // static thread_local MyManagedObjectCollection s_ManagedObjects;
//     //
//     // static thread_local stack<unsigned int> s_FreeList;
//
//     unsigned int m_Value{ 0xFFFFFFFF };
//
// public:
//     MyManagedObject() = default;
//
//     MyManagedObject(unsigned int value)
//         : m_Value{ value }
//     {
//
//     }
//
//     void* operator new(size_t numBytes)
//     {
//         lock_guard<mutex> lock{ s_Mutex };
//
//         void* objectMemory{};
//
//         //s_Mutex.lock();
//
//         if (s_ManagedObjects.capacity() < MAX_OBJECTS) {
//             s_ManagedObjects.reserve(MAX_OBJECTS);
//         }
//
//         if (numBytes == sizeof(MyManagedObject) && s_ManagedObjects.size() < s_ManagedObjects.capacity()) {
//             unsigned int index{ 0xFFFFFFFF };
//             if (s_FreeList.size() > 0) {
//                 index = s_FreeList.top();
//                 s_FreeList.pop();
//             }
//
//             if (index == 0xFFFFFFFF) {
//                 s_ManagedObjects.push_back({});
//                 index = s_ManagedObjects.size() - 1;
//             }
//
//             objectMemory = s_ManagedObjects.data() + index;
//         }
//         else {
//             objectMemory = malloc(numBytes);
//         }
//
//         //s_Mutex.unlock();
//
//         return objectMemory;
//     }
//
//     void operator delete(void* pMem)
//     {
//         lock_guard<mutex> lock{ s_Mutex };
//         //s_Mutex.lock();
//
//         const intptr_t index{ (static_cast<MyManagedObject*>(pMem) - s_ManagedObjects.data()) / static_cast<intptr_t>(sizeof(MyManagedObject)) };
//
//         if (0 <= index && index < static_cast<intptr_t>(s_ManagedObjects.size())) {
//             s_FreeList.emplace(static_cast<unsigned int>(index));
//         }
//         else {
//             free(pMem);
//         }
//
//         //s_Mutex.unlock();
//     }
// };
//
// mutex MyManagedObject::s_Mutex;
// MyManagedObject::MyManagedObjectCollection MyManagedObject::s_ManagedObjects{};
// stack<unsigned int> MyManagedObject::s_FreeList{};
// // thread_local const unsigned int MyManagedObject::MAX_OBJECTS{ 8 };
// // thread_local MyManagedObject::MyManagedObjectCollection MyManagedObject::s_ManagedObjects{};
// // thread_local stack<unsigned int> MyManagedObject::s_FreeList{};
//
// void ThreadTask()
// {
//     MyManagedObject* pObject4{ new MyManagedObject(5) };
//     cout << "pObject4: " << pObject4 << endl;
//
//     MyManagedObject* pObject5{ new MyManagedObject(6) };
//     cout << "pObject5: " << pObject5 << endl;
//
//     delete pObject4;
//     pObject4 = nullptr;
//
//     MyManagedObject* pObject6{ new MyManagedObject(7) };
//     cout << "pObject6: " << pObject6 << endl;
//
//     pObject4 = new MyManagedObject(8);
//     cout << "pObject4: " << pObject4 << endl;
//
//     delete pObject5;
//     pObject5 = nullptr;
//
//     delete pObject6;
//     pObject6 = nullptr;
//
//     delete pObject4;
//     pObject4 = nullptr;
// }
//
// using ProducerQueue = vector< unsigned int >;
//
// void ThreadTask(
//     reference_wrapper<condition_variable> condition,
//     reference_wrapper<mutex> queueMutex,
//     reference_wrapper<ProducerQueue> queueRef,
//     reference_wrapper<bool> die)
// {
//     ProducerQueue& queue{ queueRef.get() };
//
//     while (!die.get() || queue.size()) {
//         unique_lock<mutex> lock{ queueMutex.get() };
//
//         function<bool()> predicate {
//             [&queue]()
//             {
//                 return !queue.empty();
//             }
//         };
//
//         condition.get().wait(lock, predicate);
//
//         unsigned int numberToCreate{ queue.back() };
//         queue.pop_back();
//
//         cout << "Creating " << numberToCreate << " objects on thread " << this_thread::get_id() << endl;
//
//         for (unsigned int i{ 0 }; i < numberToCreate; ++i) {
//             MyManagedObject* pObject{ new MyManagedObject(i) };
//         }
//     }
// }
//
//
//
// using FactorialPromise = promise< long long >;
//
// long long Factorial(unsigned int value)
// {
//     //this_thread::sleep_for(chrono::seconds(2));
//     cout << "ThreadTask thread: " << this_thread::get_id() << endl;
//     return value == 1 ? 1 : value * Factorial(value - 1);
// }
//
//
//
class RunningTotal
{
private:
    int m_Value{ 0 };
    bool m_Finished{ false };

public:
    RunningTotal& operator+=(int value)
    {
        m_Value += value;
        return *this;
    }

    RunningTotal& operator-=(int value)
    {
        m_Value -= value;
        return *this;
    }

    RunningTotal& Finish()
    {
        m_Finished = true;
        return *this;
    }

    int operator *() const //throw(int) // C++17 开始不支持这个了
    {
        if (!m_Finished) {
            throw m_Value;
        }

        return m_Value;
    }
};

template<typename T>
class MessageQueue
{
private:
    using Queue = vector< T >;
    using QueueIterator = typename Queue::iterator;

    Queue m_A;
    Queue m_B;

    Queue* m_Producer{ &m_A };
    Queue* m_Consumer{ &m_B };

    QueueIterator m_ConsumerIterator{ m_B.end() };

    condition_variable& m_MessageCondition;
    condition_variable m_ConsumptionFinished;

    mutex m_MutexProducer;
    mutex m_MutexConsumer;

    unsigned int m_SwapCount{ 0 };

public:
    MessageQueue(condition_variable& messageCondition)
        : m_MessageCondition{ messageCondition }
    {

    }

    unsigned int GetCount() const
    {
        return m_SwapCount;
    }

    void Add(T&& operation)
    {
        unique_lock<mutex> lock{ m_MutexProducer };
        m_Producer->insert(m_Producer->end(), std::move(operation));
    }

    void BeginConsumption()
    {
        m_MutexConsumer.lock();
    }

    T Consume()
    {
        T operation;

        if (m_Consumer->size() > 0) {
            operation = *m_ConsumerIterator;
            m_ConsumerIterator = m_Consumer->erase(m_ConsumerIterator);
            assert(m_ConsumerIterator == m_Consumer->begin());
        }

        return operation;
    }

    void EndConsumption()
    {
        assert(m_Consumer->size() == 0);
        m_MutexConsumer.unlock();
        m_ConsumptionFinished.notify_all();
    }

    unsigned int Swap()
    {
        unique_lock<mutex> lockB{ m_MutexConsumer };
        m_ConsumptionFinished.wait(
            lockB,
            [this]()
            {
                return m_Consumer->size() == 0;
            }
        );

        unique_lock<mutex> lockA{ m_MutexProducer };

        Queue* temp{ m_Producer };
        m_Producer = m_Consumer;
        m_Consumer = temp;
        
        m_ConsumerIterator = m_Consumer->begin();
        
        m_MessageCondition.notify_all();
        
        return m_SwapCount++;
    }
};

using RunningTotalOperation = function< RunningTotal&() >;
using RunningTotalMessageQueue = MessageQueue< RunningTotalOperation >;

int Task(reference_wrapper<mutex> messageQueueMutex,
    reference_wrapper<condition_variable> messageCondition,
    reference_wrapper<RunningTotalMessageQueue> messageQueueRef)
{
    int result{ 0 };

    RunningTotalMessageQueue& messageQueue = messageQueueRef.get();
    unsigned int currentSwapCount{ 0 };

    bool finished{ false };
    while (!finished) {
        unique_lock<mutex> lock{ messageQueueMutex.get() };
        messageCondition.get().wait(
            lock,
            [&messageQueue, &currentSwapCount]()
            {
                return currentSwapCount != messageQueue.GetCount();
            }
        );

        messageQueue.BeginConsumption();
        currentSwapCount = messageQueue.GetCount();
        while (RunningTotalOperation operation{ messageQueue.Consume() }) {
            RunningTotal& runningTotal = operation();

            try {
                result = *runningTotal;
                finished = true;
                break;
            }
            catch (int param) {
                cout << "Total not yet finished, current is: " << param << endl;
            }
        }
        messageQueue.EndConsumption();
    }

    return result;
}

int main()
{
    // const unsigned int numberOfProcessors{ thread::hardware_concurrency() };
    //
    // cout << "This system can run " << numberOfProcessors << " concurrent tasks" << endl;
    //
    // if (numberOfProcessors > 1) {
    //     thread myThread{ ThreadTask };
    //     cout << "Output from main" << endl;
    //
    //     //myThread.join();
    //     myThread.detach();
    // }
    // else {
    //     cout << "CPU does not have multiple cores." << endl;
    // }
    //
    //
    //
    // cout << hex << showbase;
    //
    // thread myThread{ ThreadTask };
    //
    // MyManagedObject* pObject1{ new MyManagedObject(1) };
    // cout << "pObject1: " << pObject1 << endl;
    //
    // MyManagedObject* pObject2{ new MyManagedObject(2) };
    // cout << "pObject2: " << pObject2 << endl;
    //
    // delete pObject1;
    // pObject1 = nullptr;
    //
    // MyManagedObject* pObject3{ new MyManagedObject(3) };
    // cout << "pObject3: " << pObject3 << endl;
    //
    // pObject1 = new MyManagedObject(4);
    // cout << "pObject1: " << pObject1 << endl;
    //
    // delete pObject2;
    // pObject2 = nullptr;
    //
    // delete pObject3;
    // pObject3 = nullptr;
    //
    // delete pObject1;
    // pObject1 = nullptr;
    //
    // myThread.join();
    //
    //
    //
    // condition_variable condition;
    // mutex queueMutex;
    // ProducerQueue queue;
    // bool die{ false };
    //
    // thread myThread1{ ThreadTask, ref(condition), ref(queueMutex), ref(queue), ref(die) };
    // thread myThread2{ ThreadTask, ref(condition), ref(queueMutex), ref(queue), ref(die) };
    //
    // queueMutex.lock();
    // queue.emplace_back(300000);
    // queue.emplace_back(400000);
    // queueMutex.unlock();
    // condition.notify_all();
    //
    // this_thread::sleep_for( 10ms );
    // while (!queueMutex.try_lock()) {
    //     cout << "Main waiting for queue access!" << endl;
    //     this_thread::sleep_for( 100ms );
    // }
    //
    // queue.emplace_back(100000);
    // queue.emplace_back(200000);
    //
    // this_thread::sleep_for( 1000ms );
    //
    // condition.notify_one();
    //
    // this_thread::sleep_for( 1000ms );
    //
    // condition.notify_one();
    //
    // this_thread::sleep_for( 1000ms );
    //
    // queueMutex.unlock();
    //
    // die = true;
    //
    // cout << "main waiting for join!" << endl;
    //
    // myThread1.join();
    // myThread2.join();
    //
    //
    //
    // FactorialPromise promise;
    // future<long long> taskFuture{ promise.get_future() };
    //
    // //cout << "before " << taskFuture.get() << endl; //会阻塞
    // promise.set_value(Factorial(3));
    // cout << "Factorial result was " << taskFuture.get() << endl;
    //
    //
    //
    // packaged_task<long long(unsigned int)> task{ Factorial };
    // future<long long> taskFuture{ task.get_future() };
    //
    // thread taskThread{ std::move(task), 3 };
    //
    // while (taskFuture.wait_until(chrono::system_clock::now() + chrono::seconds(1)) != future_status::ready) {
    //     cout << "Still Waiting!" << endl;
    // }
    //
    // cout << "Factorial result was " << taskFuture.get() << endl;
    //
    // taskThread.join();
    //
    //
    //
    // cout << "main thread: " << this_thread::get_id() << endl;
    //
    // auto taskFuture1 = async(Factorial, 3);
    // cout << "Factorial result was " << taskFuture1.get() << endl;
    //
    // auto taskFuture2 = async(launch::async, Factorial, 3);
    // cout << "Factorial result was " << taskFuture2.get() << endl;
    //
    // auto taskFuture3 = async(launch::deferred, Factorial, 3);
    // cout << "Factorial result was " << taskFuture3.get() << endl;
    //
    // auto taskFuture4 = async(launch::async | launch::deferred, Factorial, 3);
    // cout << "Factorial result was " << taskFuture4.get() << endl;
    //
    //
    //
    RunningTotal runningTotal;

    mutex messageQueueMutex;
    condition_variable messageQueueCondition;
    RunningTotalMessageQueue messageQueue{ messageQueueCondition };

    auto myFuture = async(launch::async,
        Task,
        ref(messageQueueMutex),
        ref(messageQueueCondition),
        ref(messageQueue));

    messageQueue.Add(bind(&RunningTotal::operator+=, &runningTotal, 3));
    messageQueue.Swap();

    messageQueue.Add(bind(&RunningTotal::operator-=, &runningTotal, 100));
    messageQueue.Add(bind(&RunningTotal::operator+=, &runningTotal, 100000));
    messageQueue.Add(bind(&RunningTotal::operator-=, &runningTotal, 256));
    messageQueue.Swap();

    messageQueue.Add(bind(&RunningTotal::operator-=, &runningTotal, 100));
    messageQueue.Add(bind(&RunningTotal::operator+=, &runningTotal, 100000));
    messageQueue.Add(bind(&RunningTotal::operator-=, &runningTotal, 256));
    messageQueue.Swap();

    messageQueue.Add(bind(&RunningTotal::Finish, &runningTotal));
    messageQueue.Swap();

    cout << "The final total is: " << myFuture.get() << endl;

    return 0;
}