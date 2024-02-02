#include <iostream>
#include <thread>
#include <semaphore.h>

sem_t semaphore;  // Semaphore to control access to the critical section
int sharedResource = 0;

void criticalSection(int threadId) {
    for (int i = 0; i < 5; ++i) {
        // Wait on the semaphore (decrement)
        sem_wait(&semaphore);

        // Critical section - the code that needs to be protected
        // int currentValue = sharedResource;
        // std::cout << "Thread " << threadId << " in critical section. Shared resource value: " << currentValue << std::endl;
        ++sharedResource;

        // Signal the semaphore (increment)
        sem_post(&semaphore);

        // Non-critical section - other code outside the critical section
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // Initialize semaphore with an initial value of 1
    sem_init(&semaphore, 0, 1);

    // Create two threads to demonstrate the critical section problem
    std::thread thread1(criticalSection, 1);
    std::thread thread2(criticalSection, 2);

    // Wait for threads to finish
    thread1.join();
    thread2.join();
    std::cout<<sharedResource<<std::endl;
    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}
/*
10
*/
