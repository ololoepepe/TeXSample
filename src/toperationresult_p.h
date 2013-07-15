#ifndef TOPERATIONRESULT_P_H
#define TOPERATIONRESULT_P_H

#include "toperationresult.h"
#include "tglobal.h"

#include <BeQtGlobal>
#include <BeQtCore/private/bbase_p.h>

/*============================================================================
================================ TOperationResultPrivate =====================
============================================================================*/

class TSMP_EXPORT TOperationResultPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TOperationResult)
public:
   explicit TOperationResultPrivate(TOperationResult *q);
    ~TOperationResultPrivate();
public:
    void init();
public:
    bool success;
    TOperationResult::Error error;
private:
    Q_DISABLE_COPY(TOperationResultPrivate)
};

#endif // TOPERATIONRESULT_P_H
