#include "plotter.h"

Plotter *Plotter::instance = 0;

Plotter::Plotter() : m_(0), cv_(0), notified_(0), done_(0), data_(0) {}

Plotter::Plotter(std::mutex *m, std::condition_variable *cv, bool *notified,
                 bool *done, std::queue<double> *data)
    : m_(m), cv_(cv), notified_(notified), done_(done), data_(data)
{
}

Plotter::~Plotter() {}

void Plotter::setInstance(Plotter *mp) { instance = mp; }
void Plotter::displayWrapper() { instance->display(); }
void Plotter::reshapeWrapper(int w, int h) { instance->reshape(w, h); }

void Plotter::idleWrapper()
{
    glutPostRedisplay();

    std::unique_lock<std::mutex> lock((*instance->m_));

    while (!(*(instance->notified_))) { // loop to avoid spurious wakeups
        (instance->cv_)->wait(lock);
    }
    instance->getNewData();
    *(instance->notified_) = false;

    if (*(instance->done_)) {
        glutDestroyWindow(glutGetWindow());
    }
}

void Plotter::mouseWrapper(int button, int state, int x, int y)
{
    instance->mouse(button, state, x, y);
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        instance->print();
}

void Plotter::motionWrapper(int x, int y) { instance->motion(x, y); }
void Plotter::passiveWrapper(int x, int y) { instance->passivemotion(x, y); }

void Plotter::keyboardWrapper(unsigned char key, int x, int y)
{
    instance->keyboard(key, x, y);
    if (key == 'r') {
        if (instance->is_run == 0) {
            instance->is_run = 1;
        }
        else {
            instance->is_run = 0;
        }
    }
}

void Plotter::startPlotter(int argc, char *argv[])
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutCreateWindow(100, 100, 800, 600);
    glutSetWindowTitle("C++ real time plot");

    // Function callbacks
    glutDisplayFunc(displayWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutMotionFunc(motionWrapper);
    glutMouseFunc(mouseWrapper);
    glutPassiveMotionFunc(passiveWrapper);
    glutKeyboardFunc(keyboardWrapper);

    // Loops
    glutIdleFunc(idleWrapper); // The program run loop
    glutMainLoop();            // Start the main GLUT thread
}

void Plotter::DISPLAY()
{
    // plot
    title("press r to run and stop");
    plot(x, z);
    xlabel("x - samples");
    ylabel("y - random noise");
    grid(1);
}

void Plotter::getNewData()
{
    static uint64_t cnt = 0;
    int N = 50;
    if (is_run) {
        while (!data_->empty()) {
            x.push_back(cnt + 1);
            z.push_back(data_->front());
            if (x.size() > N) {
                x.erase(x.begin(), x.end() - N + 1);
                z.erase(z.begin(), z.end() - N + 1);
            }
            data_->pop();
            cnt++;
        }
    }
}
