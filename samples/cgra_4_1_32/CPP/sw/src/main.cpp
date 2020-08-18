#include <main.h>

int main(int argc, char *argv[]) {

    short data_in_cpu0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    short data_out_cpu0[10];

    short data_in_cgra0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    short data_out_cgra0[10];

    int data_size_bytes = sizeof(short) * 10;

    auto df = new DataFlow(0, "test");
    auto in0 = new InputStream(0, &data_in_cpu0[0], 10);
    auto out0 = new OutputStream(2, &data_out_cpu0[0], 10);
        auto addi = new Addi(1, 10);

    df->connect(in0, addi, addi->getPortA());
    df->connect(addi, out0, out0->getPortA());

    df->toDOT("teste.dot");
    df->toJSON("teste.json");
    df->compute();

    std::cout << "DATA IN CPU:" << std::endl;
    for (auto d : data_in_cpu0) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
    std::cout << "DATA OUT CPU:" << std::endl;
    for (auto d : data_out_cpu0) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    auto cgraArch = new CgraArch(0, 4, 1, 1, 2, 0, 4);
    auto cgraHw = new Cgra();
    auto scheduler = new Scheduler(cgraArch);

    scheduler->addDataFlow(df, 0, 0);

    int r = scheduler->scheduling();

    if (r == SCHEDULE_SUCCESS) {

        cgraHw->loadCgraProgram(cgraArch->getCgraProgram());
        cgraHw->setCgraProgramInputStreamByID(0, 0, data_in_cgra0, data_size_bytes);
        cgraHw->setCgraProgramOutputStreamByID(0, 2, data_out_cgra0, data_size_bytes);
        cgraHw->syncExecute(0);
        auto cgraExecTime = cgraHw->getTimeExec();

        printf("Time(ms) CGRA: %5.2lf\n", cgraExecTime);

        std::cout << "DATA IN CGRA:" << std::endl;
        for (auto d : data_in_cgra0) {
            std::cout << d << " ";
        }
        std::cout << std::endl;
        std::cout << "DATA OUT CGRA:" << std::endl;
        for (auto d : data_out_cgra0) {
            std::cout << d << " ";
        }
        std::cout << std::endl;
    } else {
        printf("Scheduler Error: %d\n", r);
    }

    delete df;
    delete cgraArch;
    delete cgraHw;
    delete scheduler;

    return 0;
}
