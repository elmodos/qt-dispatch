#include "Dispatch.h"
#include "Dispatch_p.h"

#include <QCoreApplication>
#include <QHash>
#include <QMetaObject>
#include <QMutexLocker>
#include <QThread>

namespace Dispatch
{
    static QMutex mutex;

    static QHash<Thread, QThread *> threads;

    QThread *getThread(Dispatch::Thread threadId);
    void syncMain(Dispatch::Thread thread, Qt::ConnectionType connectionType, const Dispatch::Block &block);
}


QThread *Dispatch::getThread(Dispatch::Thread threadId)
{
    QMutexLocker scopedLock(&Dispatch::mutex);
    QThread *thread = Dispatch::threads.value(threadId, nullptr);

    if (thread == nullptr)
    {
        if (threadId == Main)
        {
            thread = QCoreApplication::instance()->thread();
        }
        else
        {
            thread = new QThread();
            thread->start(static_cast<QThread::Priority>(threadId));
        }
        Dispatch::threads[threadId] = thread;
    }

    return thread;
}

void Dispatch::syncMain(Dispatch::Thread thread, Qt::ConnectionType connectionType, const Dispatch::Block &block)
{
    QThread *threadInstance = Dispatch::getThread(thread);

    if (connectionType == Qt::BlockingQueuedConnection && threadInstance == QThread::currentThread())
    {
        block();
    }
    else
    {
        static int value = qRegisterMetaType<Dispatch::Block>("Dispatch::Block");
        Q_UNUSED(value);

        Dispatch::BlockObject *worker = new Dispatch::BlockObject(threadInstance);
        QMetaObject::invokeMethod(worker, "run", connectionType, Q_ARG(Dispatch::Block, block));
    }
}

void Dispatch::async(Dispatch::Thread thread, const Dispatch::Block &block)
{
    Dispatch::syncMain(thread, Qt::QueuedConnection, block);
}

void Dispatch::sync(Dispatch::Thread thread, const Block &block)
{
    Dispatch::syncMain(thread, Qt::BlockingQueuedConnection, block);
}

