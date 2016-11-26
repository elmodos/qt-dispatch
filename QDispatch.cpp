#include "QDispatch.h"
#include <QMutexLocker>
#include <QMap>

namespace QDispatch
{
    static QMutex mutex;
    static QThread *threadBackground = nullptr;

    QThread *getThread(QDispatch::Thread threadId);
}


QThread *QDispatch::getThread(QDispatch::Thread threadId)
{
    QMutexLocker scopedLock(&QDispatch::mutex);
    QThread *thread = nullptr;
    switch (threadId)
    {
        case Main:
        {
            thread = QCoreApplication::instance()->thread();
            break;
        }
        case Background:
        {
            if (QDispatch::threadBackground == nullptr)
            {
                QDispatch::threadBackground = new QThread();
                QDispatch::threadBackground->start(QThread::NormalPriority);
            }
            thread = QDispatch::threadBackground;
            break;
        }
        default: break;
    }
    return thread;
}

void QDispatch::async(QDispatch::Thread thread, QDispatch::Block block)
{
    qRegisterMetaType<QDispatch::Block>("QDispatch::Block");
    QThread *threadInstance = QDispatch::getThread(thread);

    QDispatch::BlockObject *worker = new QDispatch::BlockObject(threadInstance);
    QMetaObject::invokeMethod(worker, "run", Qt::QueuedConnection, Q_ARG(QDispatch::Block, block));
}

void QDispatch::sync(QDispatch::Thread thread, QDispatch::Block block)
{
    qRegisterMetaType<QDispatch::Block>("QDispatch::Block");
    QThread *threadInstance = QDispatch::getThread(thread);

    QDispatch::BlockObject *worker = new QDispatch::BlockObject(threadInstance);
    QMetaObject::invokeMethod(worker, "run", Qt::BlockingQueuedConnection, Q_ARG(QDispatch::Block, block));
}

