#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#define readerDelay 1
#define writerDelay 500
#define readers 100
#define writers 20
#define repeat 4

std::mutex w, r, mutex1, mutex2;
int value = 0;
uint32_t readcount = 0, writecount = 0;

void reder()
{
    r.lock();
    mutex1.lock();
    ++readcount;
    if (readcount == 1)
        w.lock();
    mutex1.unlock();
    r.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(readerDelay));
    std::cout << "read " << value << '\n';

    mutex1.lock();
    --readcount;
    if (readcount == 0)
        w.unlock();
    mutex1.unlock();
}

void writer()
{
    mutex2.lock();
    ++writecount;
    if (writecount == 1)
        r.lock();
    mutex2.unlock();

    w.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(writerDelay));
    srand(value);
    value = rand();
    std::cout << "write " << value << '\n';
    w.unlock();

    mutex2.lock();
    --writecount;
    if (writecount == 0)
        r.unlock();
    mutex2.unlock();
}

void fillW(std::vector<std::thread>& th_vec_w)
{
    for(int i = 0; i < writers; ++i)
        th_vec_w.emplace_back(writer);
}

void fillR(std::vector<std::thread>& th_vec_r)
{
    for(int i = 0; i < readers; ++i)
        th_vec_r.emplace_back(reder);
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