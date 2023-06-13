#include "feeder.h"
#include "plotter.h"

int main(int argc, char *argv[])
{
    std::mutex m;
    std::condition_variable cond_var;
    bool done = false;
    bool notified = false;
    std::queue<double> data;

    Feeder *fd = new Feeder(&m, &cond_var, &notified, &done, &data);
    std::thread th(&Feeder::run, fd);

    Plotter *mp = new Plotter(&m, &cond_var, &notified, &done, &data);
    mp->setInstance(mp);
    mp->startPlotter(argc, argv);

    delete fd;
    delete mp;

    return 0;
}
