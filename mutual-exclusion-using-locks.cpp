#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // Mutex to protect the critical section
int sharedResource = 0;

void criticalSection(int threadId) {
    for (int i = 0; i < 5; ++i) {
        // Entry section - acquire the lock
        mtx.lock();

        // Critical section - the code that needs to be protected
        // std::cout << "Thread " << threadId << " in critical section. Shared resource value: " << sharedResource << std::endl;
        std::cout<<sharedResource<<std::endl;
        ++sharedResource;

        // Exit section - release the lock
        mtx.unlock();

        // Non-critical section - other code outside the critical section
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // Create two threads to demonstrate the critical section problem
    std::thread thread1(criticalSection, 1);
    std::thread thread2(criticalSection, 2);

    // Wait for threads to finish
    thread1.join();
    thread2.join();

    return 0;
}
/*
0
1
2
3
4
5
6
7
8
9
*/
