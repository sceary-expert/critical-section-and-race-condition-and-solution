#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;  // Mutex for protecting the critical section
std::condition_variable cv;  // Condition variable for synchronization
bool flag1 = false;
bool flag2 = false;
int sharedResource = 0;

void criticalSection(int threadId, bool& flag, bool& otherFlag) {
    for (int i = 0; i < 5; ++i) {
        {
            std::unique_lock<std::mutex> lock(mtx);

            // Wait until the other thread has finished its critical section
            cv.wait(lock, [&otherFlag] { return !otherFlag; });

            // Set the flag to indicate entering the critical section
            flag = true;

            // Critical section - the code that needs to be protected
            // int currentValue = sharedResource;
            // std::cout << "Thread " << threadId << " in critical section. Shared resource value: " << currentValue << std::endl;
            ++sharedResource;

            // Clear the flag to indicate leaving the critical section
            flag = false;

            // Notify the waiting thread (if any) that the critical section is finished
            cv.notify_one();
        }

        // Non-critical section - other code outside the critical section
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // Create two threads to demonstrate the critical section problem
    std::thread thread1(criticalSection, 1, std::ref(flag1), std::ref(flag2));
    std::thread thread2(criticalSection, 2, std::ref(flag2), std::ref(flag1));

    // Wait for threads to finish
    thread1.join();
    thread2.join();
    
    std::cout << "Final shared resource value: " << sharedResource << std::endl;

    return 0;
}
/*
Final shared resource value: 10
*/
