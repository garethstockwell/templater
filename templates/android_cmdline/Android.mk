LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	main.c

LOCAL_STATIC_LIBRARIES :=
#LOCAL_C_INCLUDES +=
#LOCAL_CFLAGS +=

LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)

LOCAL_MODULE_TAGS := debug

LOCAL_MODULE := {{PROJECT}l}

include $(BUILD_EXECUTABLE)

