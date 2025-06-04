#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono> // For std::chrono::milliseconds
#include <random> // For random number generation

const int MAX_BUFFER_SIZE = 5;
std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cv_producer; // Condition variable for producers
std::condition_variable cv_consumer; // Condition variable for consumers

// Function for producer threads
void producer(int id) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count() + id);
    std::uniform_int_distribution<int> distribution(100, 1000);

    for (int i = 0; i < 10; ++i) { // Each producer produces 10 items
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if the buffer is full
        cv_producer.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; });

        int item = distribution(generator); // Generate a random item
        buffer.push(item);
        std::cout << "Producer " << id << " produced: " << item << " (Buffer size: " << buffer.size() << ")" << std::endl;

        lock.unlock(); // Explicitly unlock before notifying to avoid contention
        cv_consumer.notify_one(); // Notify one waiting consumer
        std::this_thread::sleep_for(std::chrono::milliseconds(distribution(generator) / 10)); // Simulate work
    }
}

// Function for consumer threads
void consumer(int id) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count() + id + 1000); // Different seed
    std::uniform_int_distribution<int> distribution(100, 1000);

    for (int i = 0; i < 10; ++i) { // Each consumer consumes 10 items
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if the buffer is empty
        cv_consumer.wait(lock, [] { return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed: " << item << " (Buffer size: " << buffer.size() << ")" << std::endl;
        
        lock.unlock(); // Explicitly unlock before notifying
        cv_producer.notify_one(); // Notify one waiting producer
        std::this_thread::sleep_for(std::chrono::milliseconds(distribution(generator) / 10)); // Simulate work
    }
}

int main() {
    std::cout << "Starting Producer-Consumer simulation..." << std::endl;

    std::thread producers[2];
    std::thread consumers[2];

    // Create producer threads
    for (int i = 0; i < 2; ++i) {
        producers[i] = std::thread(producer, i + 1);
    }

    // Create consumer threads
    for (int i = 0; i < 2; ++i) {
        consumers[i] = std::thread(consumer, i + 1);
    }

    // Join threads (wait for them to finish)
    for (int i = 0; i < 2; ++i) {
        producers[i].join();
    }
    for (int i = 0; i < 2; ++i) {
        consumers[i].join();
    }

    std::cout << "Producer-Consumer simulation finished." << std::endl;

    return 0;
}