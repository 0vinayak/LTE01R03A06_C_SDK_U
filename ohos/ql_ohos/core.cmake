if(CONFIG_QUEC_PROJECT_FEATURE_OHOS)

if(CONFIG_QUEC_PROJECT_FEATURE_OHOS_XTS)
set(OHOS_XTS_LIBS   hctest
                    module_ActsUtilsFileTest
                    module_ActsParameterTest
                    )
endif()

set(OHOS_BOOT_LIBS  bootstrap
                    broadcast
                    )

set(OHOS_APP_LIBS   hilog_lite
                    hiview_lite
                    samgr
                    samgr_source
                    samgr_adapter
                    sec_static
                    hievent_lite
                    hidumper_mini
                    blackbox
                    utils_kv_store
                    sysparam
                    hal_sysparam
                    native_file
                    hal_file_static
                    cjson_static
                    hal_iothardware
                    )

set(OHOS_IOT_LIBS   hal_iothardware)

set(QL_OHOS_XTS_LIBS ${OHOS_XTS_LIBS} CACHE INTERNAL "ql ohos xts library")
set(QL_OHOS_BOOT_LIBS ${OHOS_BOOT_LIBS} CACHE INTERNAL "ql ohos boot library")
set(QL_OHOS_APP_LIBS ${OHOS_APP_LIBS} CACHE INTERNAL "ql ohos app library")
set(QL_OHOS_IOT_LIBS ${OHOS_IOT_LIBS} CACHE INTERNAL "ql ohos iot library")

print("${QL_OHOS_XTS_LIBS}")
print("${QL_OHOS_BOOT_LIBS}")
print("${QL_OHOS_APP_LIBS}")
print("${QL_OHOS_IOT_LIBS}")

endif()