#include "feeder.h"

Feeder::Feeder() : m_(0), cv_(0), notified_(0), done_(0) {}

Feeder::Feeder(std::mutex *m, std::condition_variable *cv, bool *notified,
               bool *done, std::queue<double> *data)
    : m_(m), cv_(cv), notified_(notified), done_(done), data_(data)
{
    unsigned int seed = 0; // std::random_device{}()
    gen_.seed(seed);
    dist_ = std::uniform_real_distribution<double>(0.0, 1.0);
}

Feeder::~Feeder() {}

void Feeder::run()
{
    for (int i = 0; i < 1000; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::unique_lock<std::mutex> lock(*m_);
        data_->push(dist_(gen_));
        *(this->notified_) = true;
        (this->cv_)->notify_one();
    }

    *(this->done_) = true;
    (this->cv_)->notify_one();
}
