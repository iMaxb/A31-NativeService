#ifndef _WANINNATIVE_SERVICE_H
#define _WANINNATIVE_SERVICE_H

#include <utils/Log.h>
#include "IWaninNativeService.h"

namespace android {

class BnWaninNativeService : public BnInterface<IWaninNativeService> {
    public:
        virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags); 
};

class WaninNativeService : public BnWaninNativeService {
    public:
        WaninNativeService();
        ~WaninNativeService();

        virtual int32_t RunCommand(const char * szCmd);
        virtual int32_t SetProperty(const char * szName, const char * szValue);
        virtual String16 GetProperty(const char * szName);

        static void Instantiate();
};

}
#endif // _WANINNATIVE_SERVICE_H