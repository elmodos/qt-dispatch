#ifndef DISPATCH_H
#define DISPATCH_H

#include <functional>
#include <QThread>

namespace Dispatch
{
    //
    enum Thread
    {
        Main = -1,
        BackgroundIdle = QThread::IdlePriority,
        BackgroundLow  = QThread::LowPriority,
        Background     = QThread::NormalPriority,
        BackgroundHigh = QThread::HighPriority
    };

    //
    typedef std::function<void()> Block;

    //
    void async(Thread thread, const Block &block);
    void sync(Thread thread, const Block &block);
}

#endif // DISPATCH_H
