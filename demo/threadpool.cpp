#include <thread>
#include <iostream>
#include <chrono>
#include <vector>
#include <ThreadPool.h>
#include <mutex>

using namespace std;
// initializing the number of threads

int count_threads = thread::hardware_concurrency();

int main()
{
    ThreadPool pool(16);
    std::vector< std::future<int> > results;

    mutex m;

    for (int i = 0; i < 8; ++i) {
        //results.emplace_back(
        pool.enqueue([i] {
            std::cout << "hello " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "world " << i << std::endl;
            return i * i;
            });
        //);
    }

    /*for (auto&& result : results)
        std::cout << result.get() << '-';
    std::cout << std::endl;

    //cout << results.size() << endl;
    */


	return 0;
}