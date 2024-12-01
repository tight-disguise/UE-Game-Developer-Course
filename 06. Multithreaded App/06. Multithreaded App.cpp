/* 06. Multithreaded App.cpp
 *
 * Unreal Engine Game Developer Course | Laba.IT
 *
 * Home Assignment No. 6:
 * - implement a simple app following producer-consumer template and using multi-threading and thread synchronization mechanisms
 * - optional: add statistics UI (number of producers, number of consumers, items processed)
 * - optional: add possibility to add/remove producers/consumers dynamically
 * 
 * Code written by Hubert Pitura (hpitura@gmail.com)
 */

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <charconv> // for getInput() function, needs C++20

using namespace std;

mutex mtx;
condition_variable cvConsumers, cvProducers;
queue<int> buffer;

int elementsProcessed { 0 }, bufferSize { 10 };

void producer(size_t threadNo)
{
    int element { 0 };
    
    while (true)
    {
        // Sleep for a while
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000));

        // Lock the mutex
        unique_lock<mutex> lock(mtx);

        // Wait until there's space in the buffer
        cvProducers.wait(lock, [] { return buffer.size() < bufferSize; });
    
        // Produce the value and display buffer state
        buffer.push(rand());
        cout << "<<- Producer thread no.: " << threadNo << endl;
        cout << "Value written: " << buffer.front() << endl;
        cout << "Elements in buffer: " << buffer.size() << '\n' << endl;
        
        // Notify one thread waiting
        cvConsumers.notify_one();
        // Unlock the mutex (not required, would happen anyway)
        lock.unlock();
    }
}

void consumer(size_t threadNo)
{
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(rand()%1000));

        // Lock the mutex
        unique_lock<mutex> lock(mtx);
    
        // Wait until there's something in the buffer
        cvConsumers.wait(lock, [] { return !buffer.empty(); });

        // Consume the value and display buffer state
        cout << "->> Consumer thread no.: " << threadNo << endl;
        cout << "Value read: " << to_string(buffer.front()) << endl;
        buffer.pop();
        cout << "Elements in buffer: " << buffer.size() << endl;
        cout << "Elements processed: " << ++elementsProcessed << '\n' << endl;

        // Notify one thread waiting
        cvProducers.notify_one();
        // Unlock the mutex (not required, would happen anyway)
        lock.unlock();
    }
}

// Helper function to get correct input from user
template<typename T = int>
typename T getInput(const string& prm) requires (is_arithmetic_v<T>);

/* MAIN PROGRAM CODE */
int main()
{
    vector<thread> producerThreads;
    vector<thread> consumerThreads;
    
    // Seed for random generators
    srand(time(nullptr));

    cout << "<<< PRODUCE CONSUME >>>" << '\n'
         << "--> A study into multithreading and producer/consumer pattern.\n" << endl;

    cout << "Produced elements are put into a buffer of definable size, consumers read from it.\n"
            "Program runs indefinitely, can be paused with Ctrl + S, or stopped with Ctrl + C." << endl;

    bool inputOK { false };
    size_t noOfProducerThreads { 0 }, noOfConsumerThreads { 0 };
    
    while (!inputOK)
    {
        noOfProducerThreads = getInput("Enter number of producer threads (1 - 1000): ");
        if (noOfProducerThreads >= 1 && noOfProducerThreads <= 1000)
            inputOK = true;
    }

    inputOK = false;

    while (!inputOK)
    {
        noOfConsumerThreads = getInput("Enter number of consumer threads (1 - 1000): ");
        if (noOfConsumerThreads >= 1 && noOfConsumerThreads <= 1000)
            inputOK = true;
    }

    inputOK = false;

    while (!inputOK)
    {
        bufferSize = getInput("Set buffer size (1 - 1000): ");
        if (bufferSize >= 1 && bufferSize <= 1000)
            inputOK = true;
    }

    cout << endl;
    
    // Create producer threads
    producerThreads.reserve(noOfProducerThreads);
    for (size_t i = 0; i < noOfProducerThreads; ++i)
    {
        producerThreads.emplace_back([i] { producer(i + 1); } );
    }

    // Create consumer threads
    consumerThreads.reserve(noOfConsumerThreads);
    for (size_t i = 0; i < noOfConsumerThreads; ++i)
    {
        consumerThreads.emplace_back([i] { consumer(i + 1); } );
    }

    // Start the show!
    for (auto& thread : producerThreads)
        thread.join();
    for (auto& thread : consumerThreads)
        thread.join();
}

// C++ black magic, not sure how this works, but it works :D
template<typename T = int>
typename T getInput(const string& prm) requires (is_arithmetic_v<T>)
{
    T num {};
    
    for (string inp;;)
    {
        cin.clear();
        cout << prm;
        
        if (getline(cin, inp) && !inp.empty())
        {
            const auto first {find_if(inp.begin(), inp.end(), [](unsigned ch) {return !isspace(ch); })};
            const auto end {find_if(inp.rbegin(), inp.rend(), [](unsigned ch) {return !isspace(ch); }).base()};
            const auto res {from_chars(to_address(first), to_address(end), num)};

            if (res.ec == errc {} && res.ptr == to_address(end))
                return num;
        }

        // cout << "Invalid input. a(n) " << typeid(T).name() << '\n';
        
        cout << "Invalid input. ";
    }    
}
