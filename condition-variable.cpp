/*
 * The thread support libraries
 *      - thread
 *      - mutex
 *      - condition_variable
 *      - unique_lock
 * 
 * are introduced in C++11.
 * 
 * scoped_lock is introduced in C++17.
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>

std::queue<std::string> strings;
std::condition_variable cv;
std::mutex m;

static int i = 0;

void consumer()
{
    while (true) {
        std::unique_lock l{m};  // template argument can be omitted in C++17
        cv.wait(l, [] {
            std::cout << "Waiting: " << i << '\n';
            return !strings.empty();
        });
        std::cout << strings.front() << '\n';
        strings.pop();
        l.unlock();
    }
}

void producer()
{
    while (true) {
        std::string s{"Produced: " + std::to_string(++i)};
        std::scoped_lock l{m};
        strings.push(s);
        cv.notify_one();
    }
}

int main()
{
    std::thread t1{consumer};
    std::thread t2{producer};

    t1.join();
    t2.join();
}