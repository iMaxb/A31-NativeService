#include "IWaninNativeService.h"
#include "WaninNativeService.h"

using namespace android;

int main(int argc, char **argv)
{
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();

    android::WaninNativeService::Instantiate();

    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();

    return 0;
}
