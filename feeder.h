#ifndef FEEDER_H
#define FEEDER_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

class Feeder {
public:
    Feeder();
    Feeder(std::mutex *m, std::condition_variable *cv, bool *notified,
           bool *done, std::queue<double> *data);
    ~Feeder();
    void run();

private:
    std::mutex *m_;
    std::condition_variable *cv_;
    bool *notified_, *done_;
    std::queue<double> *data_;
    std::mt19937 gen_;
    std::uniform_real_distribution<double> dist_;
};

#endif
