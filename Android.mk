LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(TARGET_BUILD_TYPE),debug)
LOCAL_CFLAGS += -DDEBUG
endif

LOCAL_PRELINK_MODULE := false

#Binder Proxy
LOCAL_MODULE := libWnNativeService
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := WaninNativeService.cpp 
LOCAL_SHARED_LIBRARIES := libbinder libutils liblog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
# WnNativeService
LOCAL_MODULE := WnNativeService
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := Main.cpp 
LOCAL_PRELINK_MODULE := false
LOCAL_SHARED_LIBRARIES := libbinder libutils libWnNativeService
include $(BUILD_EXECUTABLE)