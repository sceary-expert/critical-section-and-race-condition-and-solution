#include <iostream>
#include <thread>
#include <atomic>
using namespace std;
std::atomic<int> sharedResource(0);

void criticalSection(int threadId) {
    for (int i = 0; i < 5; ++i) {
        // Entry section - value before critical section
        int beforeValue = sharedResource.load();
        // std::cout << "Thread " << threadId << " before critical section. Shared resource value: " << beforeValue << std::endl;
        cout<<beforeValue<<endl;

        // Critical section - atomic operation to update shared resource
        sharedResource.fetch_add(1);

        // Exit section - value after critical section
        int afterValue = sharedResource.load();
        // std::cout << "Thread " << threadId << " after critical section. Shared resource value: " << afterValue << std::endl;
        cout<<afterValue<<endl;

        // Simulate some work in the critical section
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
0
2
2
23

4
44

5
6
66

7
8
8
89

10
*/
