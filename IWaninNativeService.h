#ifndef _IWANINNATIVE_SERVICE_H
#define _IWANINNATIVE_SERVICE_H

#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>

namespace android {

class IWaninNativeService : public IInterface {
    public:
        DECLARE_META_INTERFACE(WaninNativeService);
        virtual int32_t RunCommand(const char * szCmd) = 0;
        virtual int32_t SetProperty(const char * szName, const char * szValue) = 0;
        virtual String16 GetProperty(const char * szName) = 0;
    protected:
        enum{
          RUNCOMMAND    = IBinder::FIRST_CALL_TRANSACTION + 0,
          SETPROPERTY   = IBinder::FIRST_CALL_TRANSACTION + 1,
          GETPROPERTY   = IBinder::FIRST_CALL_TRANSACTION + 2,
        };
};
}
#endif //_IWANINNATIVE_SERVICE_H