#include <iostream>
#include <thread>

bool flag = false;
int sharedResource = 0;

void criticalSection(int threadId) {
    for (int i = 0; i < 5; ++i) {
        // Wait until the flag is cleared (other thread has finished its critical section)
        while (flag)
            std::this_thread::yield();

        // Set the flag to indicate entering the critical section
        flag = true;

        // Critical section - the code that needs to be protected
        // int currentValue = sharedResource;
        // std::cout << "Thread " << threadId << " in critical section. Shared resource value: " << currentValue << std::endl;
        ++sharedResource;

        // Clear the flag to indicate leaving the critical section
        flag = false;

        // Non-critical section - other code outside the critical section
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // Create two threads to demonstrate the critical section problem
    std::thread thread1(criticalSection, 1);
    std::thread thread2(criticalSection, 2);
    // std::cout<<sharedResource<<std::endl;
    // Wait for threads to finish
    thread1.join();
    thread2.join();
    std::cout<<sharedResource<<std::endl;

    return 0;
}
/*
10
*/
