#include <chrono>
#include <iostream>
#include <thread>

auto printElapsedTime(std::chrono::time_point<std::chrono::high_resolution_clock> startTime)
    -> void {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto tElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "Time elapsed since scheduler-call: " << tElapsed.count() << std::endl;
}

auto anotherFunction() -> void { std::cout << "Another thread printed me!" << std::endl; }

template <typename f>
auto schedule(int sleeptime, f callback) -> void {
    std::thread([sleeptime, callback]() {
        std::chrono::milliseconds sleepDuration(sleeptime);
        std::this_thread::sleep_for(sleepDuration);
        callback();
    })
        .detach();
}
template <>
auto schedule(int sleeptime,
              void (*printElapsedTime)(std::chrono::time_point<std::chrono::high_resolution_clock>))
    -> void {
    std::thread([sleeptime, printElapsedTime]() {
        std::chrono::milliseconds sleepDuration(sleeptime);
        auto startTime = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(sleepDuration);
        printElapsedTime(startTime);
    })
        .detach();
}

int main() {
    // note that the scheduled thread can outlive the main-tread
    // main thread should live longer then the schedduled thread
    schedule(500, printElapsedTime);
    schedule(300, anotherFunction);

    // helper function to keep the main tread alive for a bit
    std::chrono::milliseconds sleepDuration(2000);
    std::this_thread::sleep_for(sleepDuration);
    return 0;
}
