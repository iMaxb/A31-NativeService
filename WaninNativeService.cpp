#include "WaninNativeService.h"
#include <utils/Log.h>
#include <sys/system_properties.h>

#define MOD_LOG_TAG "WaninNativeService"
#define _WANIN_LOG_
#ifdef  _WANIN_LOG_
    #include <android/log.h>
    #define LOG (...)  __android_log_print(ANDROID_LOG_DEBUG, MOD_LOG_TAG, __VA_ARGS__) 
    #define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,MOD_LOG_TAG, __VA_ARGS__) 
    #define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,MOD_LOG_TAG, __VA_ARGS__)
#else
    #define LOG (...)  
    #define LOGI(...)  
    #define LOGE(...)  
#endif

namespace android {
    
class BpWaninNativeService : public BpInterface<IWaninNativeService> {
    public:
    BpWaninNativeService(const sp<IBinder>& impl) : BpInterface<IWaninNativeService>(impl)
    {
    }
    virtual int32_t RunCommand(const char * szCmd)
    {
         Parcel data, reply;
         data.writeInterfaceToken(IWaninNativeService::getInterfaceDescriptor());
         data.writeString16(String16(szCmd));
         remote()->transact(RUNCOMMAND, data, &reply);
         return reply.readInt32();
    }

    virtual int32_t SetProperty(const char * szName, const char * szValue)
    {
         Parcel data, reply;
         data.writeInterfaceToken(IWaninNativeService::getInterfaceDescriptor());
         data.writeString16(String16(szName));
         data.writeString16(String16(szValue));
         remote()->transact(SETPROPERTY, data, &reply);
         return reply.readInt32();
    } 

    virtual String16 GetProperty(const char * szName)
    {
         Parcel data, reply;
         data.writeInterfaceToken(IWaninNativeService::getInterfaceDescriptor());
         data.writeString16(String16(szName));
         remote()->transact(GETPROPERTY, data, &reply);
         return reply.readString16();
    } 
};

IMPLEMENT_META_INTERFACE(WaninNativeService, "com.wanin.IWnNativeService");

status_t BnWaninNativeService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    reply->writeInt32(0);
    switch(code)
    {
        case RUNCOMMAND:
        {
            CHECK_INTERFACE(IWaninNativeService, data, reply);
            String16 str16 = data.readString16();
            String8 str8 = String8(str16);
            int32_t ret = RunCommand(str8.string());
            reply->writeInt32(ret);
            return NO_ERROR;
        }
        case SETPROPERTY:
        {
            CHECK_INTERFACE(IWaninNativeService, data, reply);
            String16 strN16 = data.readString16();
            String8 strN8 = String8(strN16);
            String16 strV16 = data.readString16();
            String8 strV8 = String8(strV16);
            int ret = SetProperty(strN8, strV8);
            reply->writeInt32(ret);
            return NO_ERROR;
        }
        case GETPROPERTY:
        {
            CHECK_INTERFACE(IWaninNativeService, data, reply);
            String16 str16 = data.readString16();
            String8 str8 = String8(str16);
            String16 ret = GetProperty(str8);
            reply->writeString16(ret);
            return NO_ERROR;
        }
        default:
        {
            return BBinder::onTransact(code, data, reply, flags);
        }
    }
}

WaninNativeService::WaninNativeService()
{
    LOGI("constructor of WaninNativeService");
}

WaninNativeService::~WaninNativeService()
{
    LOGI("destructor of WaninNativeService");
}

int32_t WaninNativeService::RunCommand(const char * szCmd)
{
    //LOGI("WaninNativeService::RunCommand, cmd: %s", szCmd);
    return system(szCmd);
}

int32_t WaninNativeService::SetProperty(const char * szName, const char * szValue)
{
    //LOGI("WaninNativeService::SetProperty, szName: %s, value = %s", szName, szValue);

    __system_property_set(szName, szValue);

    return 0;
}

String16 WaninNativeService::GetProperty(const char * szName)
{
    //LOGI("WaninNativeService::GetProperty, szName: %s", szName);
    char szValue[128] = {0};
    __system_property_get(szName, szValue);

    return String16(szValue);
}

void WaninNativeService::Instantiate()
{
    //LOGI("WaninNativeService:ServiceManager: start\n");
    defaultServiceManager()->addService(String16("WnNativeService"), new android::WaninNativeService());
}
}