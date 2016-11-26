#ifndef DISPATCH_P_H
#define DISPATCH_P_H

#include <QObject>
#include "Dispatch.h"

namespace Dispatch
{
    class BlockObject: public QObject
    {
        Q_OBJECT
    public:
        BlockObject(QThread *thread)
        {
            moveToThread(thread);
        }

    public slots:
        void run(Dispatch::Block block)
        {
            block();
            deleteLater();
        }
    };
}

#endif // DISPATCH_P_H
