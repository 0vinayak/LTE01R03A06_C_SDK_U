
/**  @file
  ql_api_qthsdk.h

  @brief
  TODO

*/

/*================================================================
  Copyright (c) 2021 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
=================================================================*/
/*=================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN              WHO         WHAT, WHERE, WHY
------------     -------     -------------------------------------------------------------------------------

=================================================================*/
                
#ifndef __QL_API_QTHSDK_H__
#define __QL_API_QTHSDK_H__

typedef unsigned char      quint8_t;
typedef char               qint8_t;
typedef unsigned short     quint16_t;
typedef short              qint16_t;
typedef unsigned int       quint32_t;
typedef int                qint32_t;
typedef unsigned long long quint64_t;
typedef long long          qint64_t;
typedef bool               qbool;
typedef unsigned long int   pointer_t;

enum
{
    QIOT_ATEVENT_TYPE_AUTH = 1,     /* Bootstrap Authentication Event */
    QIOT_ATEVENT_TYPE_CONN = 2,     /* Access Event */
    QIOT_ATEVENT_TYPE_SUBCRIBE = 3, /* Subscription Event */
    QIOT_ATEVENT_TYPE_SEND = 4,     /* Data Sending Event */
    QIOT_ATEVENT_TYPE_RECV = 5,     /* Data Receiving Event */
    QIOT_ATEVENT_TYPE_LOGOUT = 6,   /* De-registration Event */
    QIOT_ATEVENT_TYPE_OTA = 7,      /* OTA Event */
    QIOT_ATEVENT_TYPE_SERVER = 8,   /* Developer Center Event */
    QIOT_ATEVENT_TYPE_UNAUTH = 10,  /* Deregistration Event */
    QIOT_ATECENT_TYPE_DATACOLL = 30,/* big data send value event(大数据上传事件) */
};
enum
{
    QIOT_AUTH_SUCC = 10200,                /* Successful device authentication */
    QIOT_AUTH_ERR_UNKNOWN = 10300,         /* Other errors */
    QIOT_AUTH_ERR_DMP_INSIDE = 10404,      /* Error occurs when Developer Center calls the API */
    QIOT_AUTH_ERR_DMP_STATIC_DEV    = 10421, /* The device with static authentication as the authentication type cannot be authenticated. */
    QIOT_AUTH_ERR_DONE = 10422,            /* The device is authenticated (Connection failed) */
    QIOT_AUTH_ERR_PKPS_INVALID = 10423,    /* Failed to query the product information (Connection failed) */
    QIOT_AUTH_ERR_PAYLOAD_INVALID = 10424, /* Failed to decode PAYLOAD (Connection failed) */
    QIOT_AUTH_ERR_SIGN_INVALID = 10425,    /* Signature verification failed (Connection failed) */
    QIOT_AUTH_ERR_HASH_INVALID = 10427,    /* The hash information is illegal (Connection failed) */
    QIOT_AUTH_ERR_DK_ILLEGAL = 10431,      /* DK is illegal (Connection failed) */
    QIOT_AUTH_ERR_FLAG = 10433,            /* Flag is illegal. */
    QIOT_AUTH_ERR_CLIENTID = 10434,        /* ClientID is not matched with password (password contains ClientID related information) */
    QIOT_AUTH_ERR_SUBDEV_NO_ASSOCIATION = 10440,/* The gateway is not associated with the sub-device */
    QIOT_AUTH_ERR_DEVICE_INSIDE = 10450,   /* Device internal error (Connection failed). */
    QIOT_AUTH_ERR_FAIL = 10500,            /* The device authentication to Developer Center failed (Unknown error in system) */
};
enum
{
    QIOT_CONN_SUCC = 10200,                 /* Register successfully */
    QIOT_CONN_ERR_DMP_INSIDE = 10404,       /* Error occurs when Developer Center calls the API */
    QIOT_CONN_ERR_DS_INVALID = 10430,       /* The DeviceSecret is wrong (Connection failed) */
    QIOT_CONN_ERR_FLAG = 10433,             /* Flag is illegal. */
    QIOT_CONN_ERR_CLIENTID = 10434,         /* ClientID is not matched with password (password contains ClientID related information) */
    QIOT_CONN_ERR_DS = 10437,               /* Device DS error */
    QIOT_CONN_SUBDEV_ERR_ALREADY = 10441,  /* Sub-device is connected (Connected successfully) */
    QIOT_CONN_ERR_DEVICE_INSIDE = 10450,    /* Device internal error (Connection failed). */
    QIOT_CONN_ERR_VERSION_NOTFOUND = 10471, /* The implementation version is not supported (Connection failed) */
    QIOT_CONN_ERR_PING = 10473,             /* Access heartbeat error (Connection timeout) */
    QIOT_CONN_ERR_NET = 10474,              /* Network error (Connection timeout) */
    QIOT_CONN_ERR_SERVER_CHANGE = 10475,    /* Server changed. */
    QIOT_CONN_ERR_AP = 10476,               /* AP connection error */
    QIOT_CONN_ERR_DEVICE_FORBID = 10477,    /* No use*/
    QIOT_CONN_ERR_UNKNOW = 10500,           /* Registration failed (Unknown error in system) */
};
enum
{
    QIOT_SUBCRIBE_SUCC = 10200, /* Successful subscription */
    QIOT_SUBCRIBE_ERR = 10300,  /* Failed subscription. */
};
enum
{
    QIOT_SEND_SUCC_TRANS = 10200,    /* Send transparent transmission data successfully */
    QIOT_SEND_SUCC_PHYMODEL = 10210, /* Send TSL data successfully*/
    QIOT_SEND_SUCC_LOC = 10220,      /* Send positioning data successfully */
    QIOT_SEND_SUCC_STATE = 10230,    /* Send device status data successfully */
    QIOT_SEND_SUCC_INFO = 10240,     /* Send device info data successfully */
    QIOT_SEND_SUCC_NTP  = 10250,     /* Send network time successfully */
    QIOT_SEND_ERR_TRANS = 10300,     /* Failed to send transparent transmission data */
    QIOT_SEND_ERR_PHYMODEL = 10310,  /* Failed to send TSL data */
    QIOT_SEND_ERR_FAIL_LOC = 10320,  /* Failed to send positioning data */
    QIOT_SEND_ERR_STATE = 10330,     /* Failed to send device status data */
    QIOT_SEND_ERR_INFO = 10340,      /* Failed to send device info data */
    QIOT_SEND_ERR_NTP  = 10350,      /* Failed to send network time */
};
enum
{
    QIOT_RECV_SUCC_TRANS = 10200,         /* Receive transparent transmission data */
    QIOT_RECV_SUCC_PHYMODEL_RECV = 10210, /* Receice TSL data */
    QIOT_RECV_SUCC_PHYMODEL_REQ = 10211,  /* Receive TSL data request */
    QIOT_RECV_SUCC_PHYMODEL_SERVER= 10212,/* Receives TSL service data issued by the platform */
    QIOT_RECV_SUCC_SUB_STATE_REQ = 10220, /* Receive sub-device device status data reques */
    QIOT_RECV_SUCC_SUB_INFO_REQ = 10230,  /* Receive sub-device device info data reques */
    QIOT_RECV_ERR_LIMIT = 10428,          /* Traffic limiting caused by excessive device cache. */
    QIOT_RECV_ERR_BUFFER = 10473,         /* Failed to receive data whose length exceeds the device cache limit */
};
enum
{
    QIOT_LOGOUT_SUCC = 10200, /* Successful de-registration (successful disconnection) */
};
enum
{
    QIOT_OTA_TASK_NOTIFY = 10700, /* There is an upgrade task */
    QIOT_OTA_START = 10701,       /* the device starts downloading firmware package. */
    QIOT_OTA_DOWNLOADING = 10702, /* Firmware is downloaded in progress. */
    QIOT_OTA_DOWNLOADED = 10703,  /* the firmware package is downloaded. */
    QIOT_OTA_UPDATING = 10704,    /* Firmware is being upgraded. */
    QIOT_OTA_UPDATE_OK = 10705,   /* Firmware is upgraded successfully. */
    QIOT_OTA_UPDATE_FAIL = 10706, /* Failed to upgrade the firmware. */
    QIOT_OTA_UPDATE_FLAG = 10707, /* Advertisement of the first device operation result */
};
enum
{
    QIOT_SERVER_ERRCODE_RATE_LIMIT = 10428,     /* Traffic limiting caused by high-frequency messages on the device */
    QIOT_SERVER_ERRCODE_QUANTITY_LIMIT = 10429, /* Traffic limiting caused by excessive number of single device activations or daily requests */
    QIOT_SERVER_ERRCODE_SUBDEV_UNLOGIN = 10442,/* Device is not logged into Developer Center */
};

enum
{
    QIOT_DATA_COLL_SEND_SUCCESS = 0,        /* 数据发送成功 */
    QIOT_DATA_COLL_SEND_FAIL = 1,           /* 数据发送失败 */
    QIOT_DATA_COLL_DELAYTIME = 2,           /* 收到暂停发送，单位：秒 */
    QIOT_DATA_COLL_SEND_RETRY = 3,          /* 数据发送失败，并重试 */
    QIOT_DATA_COLL_CONN_FAIL = 10,          /* 连接数采服务器失败 */
    QIOT_DATA_COLL_TRANS_FAIL = 11,         /* 本次传输异常结束 */
    QIOT_DATA_COLL_DISENBLE = 12,           /* 数采通道未开启 */
    QIOT_DATA_COLL_CONN_RETRY = 13,         /* 连接服务失败，并重试 */
    QIOT_DATA_COLL_CLOSE = 20,              /* 数采通道已关闭 */
};
/* ql_iotDp.h */
typedef enum
{
    QIOT_DPDATA_TYPE_BOOL = 0,
    QIOT_DPDATA_TYPE_INT,
    QIOT_DPDATA_TYPE_FLOAT,
    QIOT_DPDATA_TYPE_TEXT,
    QIOT_DPDATA_TYPE_STRUCT,
    QIOT_DPDATA_TYPE_RAW,
} QIot_dpDataType_e;
#define QIOT_DPDATA_TYPE_BYTE QIOT_DPDATA_TYPE_TEXT

typedef struct
{
    qint16_t pkgId;
    void *ttlvHead;    
}QIot_tsl_t;

/**************************************************************************
 * @brief Releases data table resources
 * @param ttlvHead Data table
 * @retval void
 ***************************************************************************/
void Ql_iotTtlvFree(void **ttlvHead);
/**************************************************************************
 * @brief Gets the number of nodes in the data table.
 * @param [in] ttlvHead Data table
 * @retval  The number of nodes in the data table
 ***************************************************************************/
quint32_t Ql_iotTtlvCountGet(const void *ttlvHead);
/**************************************************************************
 * @brief Extracts data nodes from the data table
 * @param [in] ttlvHead Data table
 * @param [in] index Data node index
 * @param [out] id Data node ID
 * @param [out] type Data node type
 * @retval Data node point
 * @note The return value does not need to be released after being used.
 ***************************************************************************/
void *Ql_iotTtlvNodeGet(const void *ttlvHead, quint16_t index, quint16_t *id, QIot_dpDataType_e *type);
/**************************************************************************
 * @brief Gets data node type.
 * @param [in] ttlvNode Data node
 * @param [out] type Data node type
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvNodeGetType(const void *ttlvNode, QIot_dpDataType_e *type);
/**************************************************************************
 * @brief Gets the node data in bool type.
 * @param [in] ttlvNode Data node
 * @param [out] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvNodeGetBool(const void *ttlvNode, qbool *value);
/**************************************************************************
 * @brief Gets the node data in integer type.
 * @param [in] ttlvNode Data node
 * @param [out] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvNodeGetInt(const void *ttlvNode, qint64_t *value);
/**************************************************************************
 * @brief Gets the node data in float type.
 * @param [in] ttlvNode Data node
 * @param [out] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvNodeGetFloat(const void *ttlvNode, double *value);
/**************************************************************************
 * @brief Gets the node data in string type.
 * @param [in] ttlvNode Data node
 * @retval Null: Failed execution; Others: Node data
 * @note The return value does not need to be released after being used.
 ***************************************************************************/
char *Ql_iotTtlvNodeGetString(const void *ttlvNode);
/**************************************************************************
 * @brief Gets the node data in byte type
 * @param [in] ttlvNode Data node
 * @param [out] value Node data
 * @retval 0: Failed execution; >0: Length of node data actually read
 * @note The return value does not need to be released after being used.
 ***************************************************************************/
quint32_t Ql_iotTtlvNodeGetByte(const void *ttlvNode, quint8_t **value);
/**************************************************************************
 * @brief Gets the node data in struct type
 * @param [in] ttlvNode Data node
 * @retval Pointer of the data table.
 * @note The return value does not need to be released after being used.
 ***************************************************************************/
void *Ql_iotTtlvNodeGetStruct(const void *ttlvNode);
/**************************************************************************
 * @brief Gets the node data in raw type
 * @param [in] ttlvNode Data node
 * @param [out] value Node data
 * @retval 0: Failed execution; >0: Length of node data actually read
 * @remark The return value does not need to be released after being used.
 ***************************************************************************/
quint32_t Ql_iotTtlvNodeGetRaw(const void *ttlvNode, quint8_t **value);

/**************************************************************************
 * @brief Gets the type of data for the specified ID node
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [out] type Node data type
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdGetType(const void *ttlvHead, quint16_t id, QIot_dpDataType_e *type);
/**************************************************************************
 * @brief Gets the specified ID node data in bool type
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [out] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdGetBool(const void *ttlvHead, quint16_t id, qbool *value);
/**************************************************************************
 * @brief Gets the specified ID node data in integer type
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [out] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdGetInt(const void *ttlvHead, quint16_t id, qint64_t *value);
/**************************************************************************
 * @brief Gets the specified ID node data in float type.
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [out] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdGetFloat(const void *ttlvHead, quint16_t id, double *value);
/**************************************************************************
 * @brief Gets the specified ID node data in string type
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @retval null: Failed execution; Others: Node data
 * @note The return value does not need to be released after being used.
 ***************************************************************************/
char *Ql_iotTtlvIdGetString(const void *ttlvHead, quint16_t id);
/**************************************************************************
 * @brief Gets the specified ID node data in byte type.
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [out] value Node data
 * @retval 0: Failed execution; >0: Length of node data actually read
 * @note The return value does not need to be released after being used.
 ***************************************************************************/
quint32_t Ql_iotTtlvIdGetByte(const void *ttlvHead, quint16_t id, quint8_t **value);
/**************************************************************************
 * @brief Gets the specified ID node data in struct type
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @retval Pointer of the data table.
 * @note The return value does not need to be released after being used.
 ***************************************************************************/
void *Ql_iotTtlvIdGetStruct(const void *ttlvHead, quint16_t id);
/**************************************************************************
 * @brief Gets the specified ID node data in raw type.
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [out] value Node data
 * @retval 0: Failed execution; >0: Length of node data actually read
 * @remark The return value does not need to be released after being used.
 ***************************************************************************/
quint32_t Ql_iotTtlvIdGetRaw(const void *ttlvHead, quint16_t id, quint8_t **value);
/* ID being 0 indicates adding an array node. */
/**************************************************************************
 * @brief Adds the node data in bool type.
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [in] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdAddBool(void **ttlvHead, quint16_t id, qbool value);
/**************************************************************************
 * @brief Adds the node data in integer type
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [in] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdAddInt(void **ttlvHead, quint16_t id, qint64_t num);
/**************************************************************************
 * @brief Adds the node data in float type
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [in] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdAddFloat(void **ttlvHead, quint16_t id, double num);
/**************************************************************************
 * @brief To add a node in float type to the TTLV linked list, you need to specify how many decimal places to keep.
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [in] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdAddFloat_ex(void **ttlvHead, quint16_t id, double value, quint8_t precision);
/**************************************************************************
 * @brief Adds the node data in byte type
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [in] data Node data
 * @param [in] len Length of node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdAddByte(void **ttlvHead, quint16_t id, const quint8_t *data, quint32_t len);
/**************************************************************************
 * @brief Adds the node data in string type
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [in] data Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdAddString(void **ttlvHead, quint16_t id, const char *data);
/**************************************************************************
 * @brief Adds the node data in raw type
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [in] data Node data
 * @param [in] len Length of node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdAddRaw(void **ttlvHead, quint16_t id, const quint8_t *data, quint32_t len);
/**************************************************************************
 * @brief Adds the node data in struct type
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 * @param [in] value Node data
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotTtlvIdAddStruct(void **ttlvHead, quint16_t id, void *vStruct);
/**************************************************************************
 * @brief Delete the specified ID node
 * @param [in] ttlvHead Data table.
 * @param [in] id Data node ID
 ***************************************************************************/
void Ql_iotTtlvRemove(void **ttlvHead, quint16_t id);

#if (1 == QTH_ENABLE_PASSTRANS)
/**************************************************************************
 * @brief Sends transparent transmission data to Developer Center
 * @param [in] mode Data sending mode：0: QoS = 0, at most once.
 *                                    1: QoS = 1, at least once.
 *                                    2: QoS = 2, exactly only once
 * @param [in] payload Data to be sent
 * @param [in] len Length of the data to be sent. Unit: byte
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotCmdBusPassTransSend(quint16_t mode, quint8_t *payload, quint32_t len);
/**************************************************************************
 * @brief Sends transparent transmission data to Developer Center
 * @param [in] mode Data sending mode：0: QoS = 0, at most once.
 *                                    1: QoS = 1, at least once.
 *                                    2: QoS = 2, exactly only once
 * @param [in] payload Data to be sent
 * @param [in] len Length of the data to be sent. Unit: byte
 * @retval -1: Failed execution; 1–65535: Uplink data ID
 * @note Ql_iotCmdBusPassTransSend_ex() is the extension function of Ql_iotCmdBusPassTransSend(). It is recommended to call Ql_iotCmdBusPassTransSend_ex().
 * @note You need to manually call Ql_iotTtlvFree() to release ttlvHead.
 ***************************************************************************/
qint32_t Ql_iotCmdBusPassTransSend_ex(quint16_t mode, quint8_t *payload, quint32_t len);
#endif/*QTH_ENABLE_PASSTRANS */
#if ( 1 == QTH_ENABLE_TSL )
/**************************************************************************
 * @brief Sends TSL data to Developer Center.
 * @param [in] mode Data sending mode：0: QoS = 0, at most once.
 *                                    1: QoS = 1, at least once.
 *                                    2: QoS = 2, exactly only once
 * @param [in] ttlvHead TTLV data head to be sent
 * @retval True:Successful execution; False: Failed execution
 * @note You need to manually call Ql_iotTtlvFree() to release ttlvHead.
 ***************************************************************************/
qbool Ql_iotCmdBusPhymodelReport(quint16_t mode, const void *ttlvHead);
/**************************************************************************
 * @brief Sends TSL data to Developer Center.
 * @param [in] mode Data sending mode：0: QoS = 0, at most once.
 *                                    1: QoS = 1, at least once.
 *                                    2: QoS = 2, exactly only once
 * @param [in] ttlvHead TTLV data head to be sent
 * @retval -1: Failed execution; 1–65535: Uplink data ID
 * @note Ql_iotCmdBusPhymodelReport_ex() is the extension function of Ql_iotCmdBusPhymodelReport(). It is recommended to call Ql_iotCmdBusPhymodelReport_ex().
 ***************************************************************************/
qint32_t Ql_iotCmdBusPhymodelReport_ex(quint16_t mode, const void *ttlvHead);
/**************************************************************************
 * @brief 	Replies to the querying of TSL data from Developer Center
 * @param [in] mode Data sending mode：0: QoS = 0, at most once.
 *                                    1: QoS = 1, at least once.
 *                                    2: QoS = 2, exactly only once
 * @param [in] PkgId Request package ID issued by Developer Center
 * @param [in] ttlvHead TTLV data head to be sent
 * @retval True:Successful execution; False: Failed execution
 * @note You need to manually call Ql_iotTtlvFree() to release ttlvHead.
 ***************************************************************************/
qbool Ql_iotCmdBusPhymodelAck(quint16_t mode, quint16_t pkgId, const void *ttlvHead);
#endif/*QTH_ENABLE_TSL */

#if (1== QTH_ENABLE_LOCIN)
/**************************************************************************
 * @brief Obtains location data of the built-in positioning feature of the module
 * @param [in] titleTttlv TTLV data table head of NMEA type to be obtained.
 * @retval TTLV data table, whose node is location data
 * @note Call Ql_iotTtlvFree() to release the resource after getting the information
 ***************************************************************************/
void *Ql_iotLocGetData(const void *titleTtlv);
/**************************************************************************
 * @brief Obtains NMEA sentences type of the built-in positioning feature of the module.
 * @retval TTLV data table, node is the supported positioning type
 * @note Call Ql_iotTtlvFree() to release the resource after getting the information
 ***************************************************************************/
void *Ql_iotLocGetSupList(void);
/**************************************************************************
 * @brief Reports the location data of the built-in positioning feature of the device.
 * @param [in] titleTtlv TTLV data table head of positioning type to be reported
 * @retval True:Successful execution; False: Failed execution
 * @remark You need to manually call Ql_iotTtlvFree() to release titleTtlv.
 ***************************************************************************/
qbool Ql_iotCmdBusLocReportInside(void *titleTtlv);
/**************************************************************************
 * @brief Reports the location data of the built-in positioning feature of the device.
 * @param [in] titleTtlv TTLV data table head of positioning type to be reported
 * @retval -1: Failed execution; 1–65535: Uplink data ID
 * @note Call Ql_iotTtlvFree() to release the resource after getting the information
 ***************************************************************************/
qint32_t Ql_iotCmdBusLocReportInside_ex(void *titleTtlv);
#endif/*QTH_ENABLE_LOCIN */
/**************************************************************************
 * @brief Reports location data obtained from external GNSS module.
 * @param [in] nmeaTtlv TTLV data table head of NMEA sentence data to be reported
 * @retval True:Successful execution; False: Failed execution
 * @note You need to manually call Ql_iotTtlvFree() to release nmeaTtlv.
 ***************************************************************************/
qbool Ql_iotCmdBusLocReportOutside(void *nmeaTtlv);
/**************************************************************************
 * @brief Reports location data obtained from external GNSS module.
 * @param [in] nmeaTtlv TTLV data table head of NMEA sentence data to be reported
 * @retval -1: Failed execution; 1–65535: Uplink data ID
 * @note Call Ql_iotTtlvFree() to release the resource after getting the information
 ***************************************************************************/
qint32_t Ql_iotCmdBusLocReportOutside_ex(void *nmeaTtlv);

/**************************************************************************
 * @brief Requests OTA upgrade plan from Developer Center.
 * @param [in] mode Whether extra file verification SHA256 information is needed.
 *                  0 Not needed
 *                  1 Needed
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotCmdOtaRequest(quint32_t mode);
/**************************************************************************
 * @brief Configures OTA upgrade operations.
 * @param [in] action OTA upgrade operation
 *                    0 Refuse the upgrade
 *                    1 Confirm the upgrade
 *                    2 MCU requests downloading the next firmware data package
 *                    3 MCU reports the upgrading status
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotCmdOtaAction(quint8_t action);

/**************************************************************************
 * @brief Reads firmware data stored in the device.
 * @param [in] startAddr Start address of reading data. Unit: byte.
 * @param [out] data Pointer to the buffer that stores data to be read
 * @param [in] maxLen Length of data to be read
 * @retval 0: Failed execution; > 0: Length of data actually read
 ***************************************************************************/
quint32_t Ql_iotCmdOtaMcuFWDataRead(quint32_t startAddr, quint8_t data[], quint32_t maxLen);

enum
{
    QIOT_DPID_STATUS_BATTERY = 1,   /* Battery power (percentage) */
    QIOT_DPID_STATUS_VOLTAGE = 2,   /* Voltage (V) */
    QIOT_DPID_STATUS_SIGNAL = 3,    /* RSSI */
    QIOT_DPID_STATUS_FLASHFREE = 4, /* Available space (byte) */
    QIOT_DPID_STATUS_RSRP = 5,      /* RSRP */
    QIOT_DPID_STATUS_RSRQ = 6,      /* LTE RSRQ */
    QIOT_DPID_STATUS_SNR = 7,       /* SNR */
    QIOT_DPID_STATUS_MAX,
};
/* 模组信息 */
enum
{
    QIOT_DPID_INFO_MODEL_TYPE = 1,   /* Module model */
    QIOT_DPID_INFO_MODEL_VER = 2,    /* Module firmware version */
    QIOT_DPID_INFO_MCU_VER = 3,      /* MCU version */
    QIOT_DPID_INFO_CELLID = 4,       /* Cell ID */
    QIOT_DPID_INFO_ICCID = 5,        /* ICCID */
    QIOT_DPID_INFO_MCC = 6,          /* MCC */
    QIOT_DPID_INFO_MNC = 7,          /* MNC */
    QIOT_DPID_INFO_LAC = 8,          /* LAC */
    QIOT_DPID_INFO_PHONE_NUM = 9,    /* Phone number */
    QIOT_DPID_INFO_SIM_NUM = 10,     /* IMSI */
    QIOT_DPID_INFO_SDK_VER = 11,     /* QuecThing SDK version number*/
    QIOT_DPID_INFO_LOC_SUPLIST = 12, /* List of the supported positioning type */
    QIOT_DPIO_INFO_DP_VER = 13,      /* Data protocol version */
    QIOT_DPIO_INFO_CP_VER = 14,      /* Communication protocol version number */
	QIOT_DPID_INFO_LOG_DURATION = 16,/* log reporting duration */
    QIOT_DPID_INFO_LOG_LEVEL = 17,   /* log reporting level */
    QIOT_DPIO_INFO_MODULE_ID = 18,   /* Module ID */  
    QIOT_DPID_INFO_MAX,
};
/**************************************************************************
 * @brief Reports device status
 * @param [in] ids Reports the specified device information
 * @param [in] size Device status ID list
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotCmdSysStatusReport(quint16_t ids[], quint32_t size);
/**************************************************************************
 * @brief Reports the specified device information
 * @param [in] ids Device information ID list
 * @param [in] size Number of device information ID.
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotCmdSysDevInfoReport(quint16_t ids[], quint32_t size);
/**************************************************************************
 * 功能 @brief 请求NTP时间和时区
 * 输出 @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotCmdSysNTPReq(void);
/**************************************************************************
 * @brief Gets device status
 * @param [in] ids Device status ID list
 * @param [in] size Number of device status ID
 * @retval TTLV data table. Node is device status
 * @note Call Ql_iotTtlvFree() to release the pointer after getting the device status.
 ***************************************************************************/
void *Ql_iotSysGetDevStatus(quint16_t ids[], quint32_t size);
/**************************************************************************
 * @brief Gets the specified device information
 * @param [in] ids evice information ID list
 * @param [in] size Number of device information ID.
 * @retval TTLV data table. Node is device information
 * @note Call Ql_iotTtlvFree() to release the pointer after getting the device status.
 ***************************************************************************/
void *Ql_iotSysGetDevInfo(quint16_t ids[], quint32_t size);
#if (1== QTH_ENABLE_BINDCODE)
/**************************************************************************
 * @brief Reports device binding information.
 * @param [in] bindcode String type. Bind code of the device. Range: 0–9, A–F
 * @param [in] timeout Maximum allowable biding time. Range: 0-3600
 * @retval True:Successful execution; False: Failed execution
 * @note The bindcode length is fixed to 16 bytes
 ***************************************************************************/
qbool Ql_iotDBindcodeSet(const char *bindcode, quint32_t timeout);
/**************************************************************************
 * @brief Gets bind code of the device.
 * @param [out] bindcode Bind code of the device
 * @retval Remaining time for binding the device
 * @note The return value does not need to be released after being used.
 ***************************************************************************/
quint32_t Ql_iotDBindcodeGet(char **bindcode);
#endif/*QTH_ENABLE_BINDCODE */

enum
{
    QIOT_DPAPP_M2M = (1 << 0),
    QIOT_DPAPP_SUBDEV = (1 << 1),
};
typedef quint32_t QIot_dpAppType_e;

/* quos_modbus.h */
#if (1 == QTH_ENABLE_MODBUS)
/* uart parity bit */
typedef enum
{
    QIOT_MBUART_PARITY_NONE = 0,
    QIOT_MBUART_PARITY_EVEN = 1,
    QIOT_MBUART_PARITY_ODD = 2,
    QIOT_MBUART_PARITY_MARK = 3,
    QIOT_MBUART_PARITY_SPACE = 4,
} QIot_MBParity_e;
/* uart data bits */
typedef enum
{
    QIOT_MBUART_DATABITS_5 = 0,
    QIOT_MBUART_DATABITS_6 = 1,
    QIOT_MBUART_DATABITS_7 = 2,
    QIOT_MBUART_DATABITS_8 = 3,
} QIot_MBDataBits_e;
/* uart stop bits */
typedef enum
{
    QIOT_MBUART_STOPBITS_1 = 0,
    QIOT_MBUART_STOPBITS_1_5 = 1,
    QIOT_MBUART_STOPBITS_2 = 2,
} QIot_MBStopBits_e;

typedef struct
{
    quint16_t port;
    quint32_t baudrate;
    QIot_MBDataBits_e dataBits;
    QIot_MBParity_e parity;
    QIot_MBStopBits_e stopBits;
} QIot_MBPortCfg_t;

/**************************************************************************
 * @brief This callback function is called when Modbus components need to send data to serial port. The serial port sending ability should be implemented in this callback function.
 * @param [in] port Serial port ID
 * @param [in] buf Data to be sent.
 * 出入 @param bufLen Length of the data to be sent
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
typedef qbool (*QIot_MBSend_f)(quint16_t port, const quint8_t *buf, quint32_t bufLen);
/**************************************************************************
 * @brief After Modbus components are initialized, the device information contained in the configuration file will be inputted in the callback function. You should implement the operations of serial port sending and receiving and connection between the device and Developer Center
 * @param [in] pk ProductKey generated when you create the product in Developer Center.
 * @param [in] ps ProductSecret generated when you create the product in Developer Center.
 * @param [in] portInfo Serial port configurations in the configuration file
 * @param [in] portNum Number of serial ports in the configuration file.
 ***************************************************************************/
typedef void (*QIot_MBInitCb_f)(char *pk, char *ps, QIot_MBPortCfg_t *portInfo[], quint32_t portNum);

/**************************************************************************
 * @brief Initializes Modbus components.
 * @param [in] portList List of serial ports used to burn configuration file
 * @param [in] portNum Number of serial ports used to burn configuration file.
 * @param [in] sendFunc Callback function of sending data to the serial port.
 * @param [in] initCb Initialization callback function
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotMBInit(quint16_t portList[], quint32_t portNum, QIot_MBSend_f sendFunc, QIot_MBInitCb_f initCb);
/**************************************************************************
 * @brief Transfers the format of the TSL data issued by Developer Center to Modbus format and sends the data to Modbus sub-device.
 * @param [in] ttlvHead TTLV data table
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotMBCloudRecv(const void *ttlvHead);
/**************************************************************************
 * @brief Forwards Modbus data received by the serial port to Modbus components and processes the Modbus data.
 * @param [in] port Serial port ID.
 * @param [in] data Modbus data received by the serial port
 * @param [in] len Length of Modbus data received by the serial port
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotMBLocalRecv(quint16_t port, quint8_t *data, quint32_t len);
/**************************************************************************
 * @brief De-initializes Modbus components
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotMBDeinit(void);
#endif/*QTH_ENABLE_MODBUS */

typedef enum
{
    QIOT_CONNMODE_IDLE, /* Exit from or do not connect to Developer Center */
    QIOT_CONNMODE_REQ,  /* Connect to Developer Center */
    QIOT_CONNMODE_AUTO, /* The device will  automatically access Developer Center after connecting to the network in AT command solution. */
} QIot_connMode_e;
typedef enum
{
    QIOT_PPROTOCOL_MQTT = 1, /* MQTT protocol */
} QIot_protocolType_t;
typedef enum
{
    QIOT_STATE_UNINITIALIZE = 0,        /* Uninitialized */
    QIOT_STATE_INITIALIZED = 1,         /* Initialized */
    QIOT_STATE_AUTHENTICATING = 2,      /* Authenticating */
    QIOT_STATE_AUTHENTICATED = 3,       /* Authenticated */
    QIOT_STATE_AUTHENTICATE_FAILED = 4, /* Authentication failed */
    QIOT_STATE_CONNECTING = 5,          /* Registering */
    QIOT_STATE_CONNECTED = 6,           /* Registered and is waiting for subscribing */
    QIOT_STATE_CONNECT_FAIL = 7,        /* Registration failed */
    QIOT_STATE_SUBSCRIBED = 8,          /* Subscribed and data can be sent */
    QIOT_STATE_SUBSCRIBE_FAIL = 9,      /* Subscription failed */
    QIOT_STATE_DISCONNECTING = 10,      /* De-registering */
    QIOT_STATE_DISCONNECTED = 11,       /* De-registered */
    QIOT_STATE_DISCONNECT_FAIL = 12,    /* De-registration failed */
} QIot_state_e;

/**************************************************************************
 * @brief Initializes configurations and enables QuecThing.
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotInit(void);
/**************************************************************************
 * @brief Configures the connection mode between the device and Developer Center.
 * @param [in] mode Connection mode；See QIot_connMode_e for details.
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotConfigSetConnmode(QIot_connMode_e mode);
/**************************************************************************
 * @brief Gets the connection mode between the device and Developer Center.
 * @retval Connection mode. See QIot_connMode_e for details
 ***************************************************************************/
QIot_connMode_e Ql_iotConfigGetConnmode(void);
/**************************************************************************
 * @brief Sets product information.
 * @param [in] pk ProductKey generated when you create the product on Developer Center.
 * @param [in] ps ProductSecret generated when you create the product on Developer Center.
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotConfigSetProductinfo(const char *pk, const char *ps);
/**************************************************************************
 * @brief Gets product information.
 * @param [out] pk ProductKey generated when you create the product on Developer Center.
 * @param [in] ps ProductSecret generated when you create the product on Developer Center.
 * @param [out] ver Protocol version used during the device authentication process.
 * @note None of the obtained data needs to be released. If the content of the obtained parameter is NULL, it indicates failed obtaining.
 ***************************************************************************/
qbool Ql_iotConfigGetProductinfo(char **pk, char **ps, char **ver);
/**************************************************************************
 * @brief Sets server information.
 * @param [in] type Protocol type. Optional parameter. Default value QIOT_PPROTOCOL_MQTT is used if this parameter is omitted
 * @param [in] serverUrl Server address (domain name and port of Developer Center).
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotConfigSetServer(QIot_protocolType_t type, const char *serverUrl);
/**************************************************************************
 * @brief Gets server information.
 * @param [out] type Protocol type.
 * @param [out] serverUrl Server address (domain name and port of Developer Center).
 * @note The server IP address does not need to be released after being used.
 ***************************************************************************/
void Ql_iotConfigGetServer(QIot_protocolType_t *type, char **serverUrl);
/**************************************************************************
 * @brief Configures the device lifetime.
 * @param [in] lifetime Device lifetime. If MQTT is used, range: 1–65535;Unit: second
 * @retval True:Successful execution; False: Failed execution
 * @note Optional parameter. The default value of the heartbeat is 120 (s). The default value will be adopted if this parameter is not configured.
 ***************************************************************************/
qbool Ql_iotConfigSetLifetime(quint32_t lifetime);
/**************************************************************************
 * @brief Gets the device lifetime.
 * @retval Device lifetime. Unit: second.
 ***************************************************************************/
quint32_t Ql_iotConfigGetLifetime(void);
/**************************************************************************
 * @brief Configures PDP context ID used by device to connect Developer Center.
 * @param [in] contextID PDP context ID. Optional parameter. Default value 1 is used if this parameter is omitted
 * @retval True:Successful execution; False: Failed execution
 * @note Optional parameter. The default value is 1
 ***************************************************************************/
qbool Ql_iotConfigSetPdpContextId(quint8_t contextID);
/**************************************************************************
 * @brief Gets the PDP context ID used by device to connect Developer Center.
 * @retval PDP context ID used by device to connect Developer Center
 ***************************************************************************/
quint8_t Ql_iotConfigGetPdpContextId(void);
#if (1 == QTH_ENABLE_SESSION)
/**************************************************************************
 * @brief Enables or disables encryption mode for the connection between the device and Developer Center
 * @param [in] flag Enable or disable encryption mode of the session between the device and Developer Center
 *                  FALSE: Disable (Default)
 *                  TRUE: Enable
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotConfigSetSessionFlag(qbool flag);
/**************************************************************************
 * @brief Queries the encryption mode of the connection between the device and Developer Center.
 * @retval FALSE: Disable (Default)
 *                TRUE: Enable
 * @note Optional parameter. Default value is used if this parameter is omitted.
 ***************************************************************************/
qbool Ql_iotConfigGetSessionFlag(void);
#endif/*QTH_ENABLE_SESSION */
/**************************************************************************
 * @brief Sets software version ID of the device.
 * @param [in] appVer Software version ID of the device
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotConfigSetAppVersion(const char *appVer);
/**************************************************************************
 * @brief Gets software version ID of the device
 * @retval Software version ID of the device
 * @note You must discard rather than release the return value after using it.
 ***************************************************************************/
char *Ql_iotConfigGetSoftVersion(void);
/**************************************************************************
 * @brief Sets MCU ID and the corresponding version number.
 * @param [in] compno MCU ID. Maximum length: 32 bytes.
 * @param [in] version Version number corresponding to the MCU ID. Maximum length: 64 bytes
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotConfigSetMcuVersion(const char *compno, const char *version);
/**************************************************************************
 * @brief Gets MCU ID and the corresponding version number.
 * @param [in] compno MCU ID. All configured MCU information will be gotten if this parameter is set to NULL
 * @param [out] version Version number corresponding to the MCU ID. Maximum length: 64 bytes
 * @retval Length of the string of MCU ID and the corresponding version number.
 * @note You must discard rather than release the return value after using it.
 ***************************************************************************/
quint32_t Ql_iotConfigGetMcuVersion(const char *compno, char **version);
/**************************************************************************
 * @brief Sets callback function for the device and Developer Center interaction event.
 * @param [in] eventCb Callback function for the device and Developer Center interaction event.
 ***************************************************************************/
void Ql_iotConfigSetEventCB(void (*eventCb)(quint32_t event, qint32_t errcode, const void *value, quint32_t valLen));
/**************************************************************************
 * @brief Gets the connection status between the device and Developer Center.
 * @retval Connection status. See QIot_state_e for details
 ***************************************************************************/
QIot_state_e Ql_iotGetWorkState(void);
#if (1 == QTH_ENABLE_DKDS)        
/**************************************************************************
 * @brief Customizes DeviceKey and DeviceSecret
 * @param [in] dk Devicekey, that is, customized unique identifier of the device. Maximum length: 16 bytes.
 * @param [in] ds DeviceSecret generated after device authentication. The length is fixed to 32 bytes. Only when DK is customized, can DS be configured.
 * @retval True:Successful execution; False: Failed execution
 * @note Only when DK is neither NULL nor the default value can the DS be configured. When you call this API, if DK and DS are set to NULL, the DK will be restored to the default value. When you call this API, if DK is not set to NULL but DS is set to NULL, the DS will be cleared.
 ***************************************************************************/
qbool Ql_iotConfigSetDkDs(const char *dk, const char *ds);
/**************************************************************************
 * @brief Gets the customized DeviceKey and DeviceSecret
 * @param [out] dk Customized DK
 * @param [out] ds Customized DS.
 * @retval True:Successful execution; False: Failed execution
 * @note You must discard rather than release the return value after using it.
 ***************************************************************************/
qbool Ql_iotConfigGetDkDs(char **dk, char **ds);
#endif/*QTH_ENABLE_DKDS */
#if (1 == QTH_ENABLE_DATACOLL)
/**************************************************************************
* @brief 数采通道文件发送
* @param lastPack 当前是否为最后一包
* @param packNum 文件分包发送序号
* @param dataLen 数据内容长度
* @param data 文件数据内容
* @retval 文件发送结果
* @remark packNum序号递增，从0开始；若仅有一包数据，dataLen则需要小于1024；若有连续包，第一包需要为2的N次方，且后续包长度需与第一包长度保持一致，最后一包长度需要小于等于第一包文件长度
***************************************************************************/
qbool Ql_iotDataCollSend(qbool lastPack, quint32_t packNum, quint16_t dataLen, quint8_t *data);
#endif/*QTH_ENABLE_DATACOLL */
#if (1== QTH_ENABLE_RST)
/**************************************************************************
 * @brief Resets device and app's binding relation.
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotRst(void);
#endif/*QTH_ENABLE_RST */
/**************************************************************************
 * @brief Gets the authentication of device
 * @param [out] authType authentication 
 * @retval True:Successful execution; False: Failed execution
 * @remark You must discard rather than release the return value after using it.
 ***************************************************************************/
qbool Ql_iotConfigGetAuth(quint32_t *authType);
#if (1 == QTH_ENABLE_ODOS)
/**************************************************************************
 * @brief 设置设备为一机一密的认证方式
 * @param [in] pk Devicekey, that is, customized unique identifier of the device. Maximum length: 16 bytes.
 * @param [in] ps ProductSecret generated when you create the product on Developer Center.
 * @param [in] dk Devicekey, that is, customized unique identifier of the device. Maximum length: 16 bytes.
 * @param [in] ds DeviceSecret generated after device authentication. The length is fixed to 32 bytes. Only when DK is customized, can DS be configured.
 * @retval True:Successful execution; False: Failed execution
 * @remark 参数均不能为空
 ***************************************************************************/
qbool Ql_iotConfigSetAuthODOS(const char *pk,const char *ps,const char *dk,const char *ds);
#endif/*QTH_ENABLE_ODOS */
/**************************************************************************
 * @brief Clear all device's config information.
 * @retval True:Successful execution; False: Failed execution
 * @note Advise to use it only during the debugging phase
 ***************************************************************************/
qbool Ql_iotClear(void);
/* ql_HOtaConfig.h */
#if (1 == QTH_ENABLE_HTTP_OTA)
/**************************************************************************
 * @brief Callback function for HTTP OTA service event.
 * @param [in] event Callback function for HTTP OTA service event.
 * @param [in] errcode Event code
 * @param [in] value Callback data
 * @param [in] valLen Length of the callback data
 * @note Some callback function events contain no data, so the value carried in the callback function events may be NULL.
 ***************************************************************************/
typedef void (*eventCb_f)(quint32_t event, qint32_t errcode, const void *value, quint32_t valLen);
/**************************************************************************
 * @brief Registers callback function for HTTP OTA service event.
 * @param [in] eventCb Callback function for HTTP OTA service event.
 ***************************************************************************/
void Ql_iotHttpOtaSetEventCb(eventCb_f eventCb);
/**************************************************************************
 * @brief Configures parameters and queries OTA upgrade plan in Developer Center.
 * @param [in] battery Current battery power of the device. Range: 0–100
 * @param [in] upmode Upgrade mode
 * @param [in] pk ProductKey generated when you create the product in Developer Center.
 * @param [in] ps ProductSecret generated when you create the product in Developer Center.
 * @param [in] url Address of Developer Center
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotHttpOtaReq(quint8_t battery, quint8_t upmode, const char *pk, const char *ps, const char *url);
/**************************************************************************
 * @brief Gets HTTP OTA upgrade information
 * @param [out] battery Current battery power of the device.
 * @param [out] upmode Upgrade mode
 * @param [out] pk ProductKey generated when you create the product in Developer Center.
 * @param [in] ps ProductSecret generated when you create the product in Developer Center.
 * @param [in] url Address of Developer Center
 * @note You must discard rather than release the return value after using it.
 ***************************************************************************/
void Ql_iotHttpOtaGet(quint8_t *battery, quint8_t *upmode, char **pk, char **ps, char **url);
#endif/*QTH_ENABLE_HTTP_OTA */

/* ql_iotGwDev.h */
#if (1 == QTH_ENABLE_GATEWAY)
/**************************************************************************
 * @brief Callback function for the interaction events between the sub-device and the gateway after the sub-device connects to the gateway
 * @param [in] event Event identifier
 * @param [in] errcode Event code
 * @param [in] subPk ProductKey generated when a product is created on Developer Center.
 * @param [in] subDk Unique identifier of the sub-device
 * @param [in] value  Callback data
 * @param [in] valLen Length of the callback data
 ***************************************************************************/
typedef void (*SubEventCb_f)(quint32_t event, qint32_t errcode, const char *subPk, const char *subDk, const void *value, quint32_t valLen);
/**************************************************************************
 * @brief Registers the callback function for the interaction event between the sub-device and the gateway.
 * @param [in] eventCb Callback function for the interaction events between the sub-device and the gateway after the sub-device connects to the gateway
 ***************************************************************************/
void Ql_iotConfigSetSubDevEventCB(SubEventCb_f eventCb);
/**************************************************************************
 * @brief Connects sub-device to gateway or authenticates sub-device.
 * @param [in] subPk ProductKey generated when a product is created on Developer Center.
 * @param [in] subPs ProductSecret generated when a product is created on Developer Center.
 * @param [in] subDk Unique identifier of the sub-device.
 * @param [in] subDs The device secret of the sub-device.
 * @param [in] sessionType Encryption method of data interaction of the sub-device.
 * @param [in] keepalive Keepalive time of the sub-device.
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotSubDevConn(const char *subPk, const char *subPs, const char *subDk, const char *subDs, quint8_t sessionType, quint16_t keepalive);
/**************************************************************************
 * @brief Disconnects the sub-device from the gateway.
 * @param [in] subPk ProductKey generated when a product is created on Developer Center.
 * @param [in] subDk  Unique identifier of the sub-device.
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotSubDevDisconn(const char *subPk, const char *subDk);
#if (1 == QTH_ENABLE_PASSTRANS)
/**************************************************************************
 * @brief Sends transparent tranmission data of the sub-device to Developer Center.
 * @param [in] subPk ProductKey generated when a product is created on Developer Center.
 * @param [in] subDk  Unique identifier of the sub-device.
 * @param [in] payload Pointer to the transparent transmission data to be reported.
 * @param [in] payloadLen Length of the transparent transmission data to be reported.
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotSubDevPassTransSend(const char *subPk, const char *subDk, quint8_t *payload, quint16_t payloadlen);
/**************************************************************************
 * @brief Sends transparent tranmission data of the sub-device to Developer Center
 * @param [in] subPk ProductKey generated when a product is created on Developer Center.
 * @param [in] subDk  Unique identifier of the sub-device.
 * @param [in] payload Pointer to the transparent transmission data to be reported.
 * @param [in] payloadLen Length of the transparent transmission data to be reported.
 * @retval -1: Failed execution; 1–65535: Uplink data ID
 ***************************************************************************/
qint32_t Ql_iotSubDevPassTransSend_ex(const char *subPk, const char *subDk, quint8_t *payload, quint16_t payloadlen);
#endif/*QTH_ENABLE_PASSTRANS */
#if (1 == QTH_ENABLE_TSL)
/**************************************************************************
 * @brief Sends TSL data of sub-device to Developer Center.
 * @param [in] subPk ProductKey generated when a product is created on Developer Center.
 * @param [in] subDk  Unique identifier of the sub-device.
 * @param [in] ttlvHead Pointer to TTLV data chain header.
 * @retval True:Successful execution; False: Failed execution
 * 备注 @note You need to manually release the ttlvHead.
 ***************************************************************************/
qbool Ql_iotSubDevTslReport(const char *subPk, const char *subDk, const void *ttlvHead);
/**************************************************************************
 * @brief Sends TSL data of sub-device to Developer Center.
 * @param [in] subPk ProductKey generated when a product is created on Developer Center.
 * @param [in] subDk  Unique identifier of the sub-device.
 * @param [in] ttlvHead Pointer to TTLV data chain header.
 * @retval -1: Failed execution; 1–65535: Uplink data ID
 * @note Ql_iotSubDevTslReport_ex() is the extension function of Ql_iotSubDevTslReport(). It is recommended to call Ql_iotSubDevTslReport_ex().
 ***************************************************************************/
qint32_t Ql_iotSubDevTslReport_ex(const char *subPk, const char *subDk, const void *ttlvHead);
/**************************************************************************
 * @brief Replies to TSL data requested by Developer Center to the sub-device.
 * @param [in] subPk ProductKey generated when a product is created on Developer Center.
 * @param [in] subDk  Unique identifier of the sub-device.
 * @param [in] pkgId The replied TTLV package ID. The ID is obtained through the event.
 * @param [in] ttlvHead Pointer to TTLV data chain header.
 * @retval You need to manually release the ttlvHead.
 ***************************************************************************/
qbool Ql_iotSubDevTslAck(const char *subPk, const char *subDk, quint16_t pkgId, const void *ttlvHead);
#endif/*QTH_ENABLE_TSL */
/**************************************************************************
 * @brief De-registers the sub-device.
 * @param [in] subPk ProductKey generated when a product is created on Developer Center.
 * @param [in] subPs ProductSecret generated when a product is created on Developer Center.
 * @param [in] subDk  Unique identifier of the sub-device.
 * @param [in] subDs The device secret of the sub-device.
 * @retval True:Successful execution; False: Failed execution
 * @note Once the sub-device deregisters from the gateway, the old subDS is invalid. The sub-device needs to be authenticated again and a new subDS will be returned.
 ***************************************************************************/
qbool Ql_iotSubDevDeauth(const char *subPk, const char *subPs, const char *subDk, const char *subDs);
/**************************************************************************
 * @brief Refreshes the last interaction time between sub-device and gateway.
 * @param [in] subPk ProductKey generated when a product is created on Developer Center.
 * @param [in] subDk  Unique identifier of the sub-device.
 * @retval True:Successful execution; False: Failed execution
 ***************************************************************************/
qbool Ql_iotSubDevHTB(const char *subPk, const char *subDk);
#endif/*QTH_ENABLE_GATEWAY */
#endif/*__QIOT_API_H__ */
