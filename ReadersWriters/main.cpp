#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#define delay 800
#define readers 100
#define writers 20
#define repeat 10

std::mutex w, r;

int value = 0, readcount = 0, writecount = 0;

void reder()
{
    r.lock();
    ++readcount;
    if (readcount == 1)
        w.lock();
    r.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    std::cout << "read " << value << '\n';

    --readcount;
    if (readcount == 0)
        w.unlock();
}

void writer()
{
    ++writecount;
    if (writecount == 1)
        r.lock();

    w.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    srand(value);
    value = rand();
    std::cout << "write " << value << '\n';
    w.unlock();

    --writecount;
    if (writecount == 0)
        r.unlock();
}

void fillW(std::vector<std::thread>& th_vec_w)
{
    for(int i = 0; i < writers; ++i)
        th_vec_w.push_back(std::thread(writer));
}

void fillR(std::vector<std::thread>& th_vec_r)
{
    for(int i = 0; i < readers; ++i)
        th_vec_r.push_back(std::thread(reder));
}

int main() {
    std::vector<std::thread> th_vec_w;
    std::vector<std::thread> th_vec_r;

    for(int i, k = 0; k < repeat; ++k)
    {
        std::thread r(fillR, std::ref(th_vec_r));
        std::thread w(fillW, std::ref(th_vec_w));

        r.join();
        w.join();

        for(i = 0; i < readers; ++i)
            th_vec_r[i].join();
        for(i = 0; i < writers; ++i)
            th_vec_w[i].join();

        value = 0;
        th_vec_r.clear();
        th_vec_w.clear();
        std::cout << "\n\n--------------------------------\n\n";
    }
    return 0;
}
