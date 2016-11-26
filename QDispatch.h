#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QCoreApplication>
#include <QMetaObject>
#include <QObject>
#include <QThread>
#include <functional>

namespace QDispatch // Public
{
    //
    enum Thread
    {
        Main = 0,
        Background
    };

    //
    typedef std::function<void()> Block;

    //
    void async(Thread thread, Block block);
    void sync(Thread thread, Block block);
}

namespace QDispatch // Private
{
    //
    class BlockObject: public QObject
    {
        Q_OBJECT
    public:
        BlockObject(QThread *thread) { moveToThread(thread); }

    public slots:
        void run(QDispatch::Block block) { block(); }
    };
}

#endif // DISPATCHER_H
