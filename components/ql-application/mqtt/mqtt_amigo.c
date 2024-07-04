#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ql_api_osi.h"
#include "ql_api_nw.h"

#include "ql_log.h"
#include "ql_api_datacall.h"
#include "ql_mqttclient.h"

#include "ql_ssl.h"

#define QL_MQTT_LOG_LEVEL QL_LOG_LEVEL_INFO
#define QL_MQTT_LOG(msg, ...) QL_LOG(QL_MQTT_LOG_LEVEL, "ql_MQTT", msg, ##__VA_ARGS__)
#define QL_MQTT_LOG_PUSH(msg, ...) QL_LOG_PUSH("ql_MQTT", msg, ##__VA_ARGS__)
static ql_task_t mqtt_task = NULL;

#define MQTT_CLIENT_IDENTITY "quectel_01"
#define MQTT_CLIENT_USER "test"
#define MQTT_CLIENT_PASS "3Motorad"

#define MQTT_CLIENT_QUECTEL_URL "mqtts://mqtt.emotorad.com:8883"

#define MQTT_CLIENT_QUECTEL_SSL_URL "mqtts://mqtt.emotorad.com:8883"

static ql_sem_t mqtt_semp;
static int mqtt_connected = 0;

static void mqtt_state_exception_cb(mqtt_client_t *client)
{
    QL_MQTT_LOG("mqtt session abnormal disconnect");
    mqtt_connected = 0;
}

static void mqtt_connect_result_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_e status)
{
    QL_MQTT_LOG("status: %d", status);
    if (status == 0)
    {
        mqtt_connected = 1;
    }
    ql_rtos_semaphore_release(mqtt_semp);
}

static void mqtt_requst_result_cb(mqtt_client_t *client, void *arg, int err)
{
    QL_MQTT_LOG("err: %d", err);

    ql_rtos_semaphore_release(mqtt_semp);
}

static void mqtt_inpub_data_cb(mqtt_client_t *client, void *arg, int pkt_id, const char *topic, const unsigned char *payload, unsigned short payload_len)
{
    QL_MQTT_LOG("topic: %s", topic);
    QL_MQTT_LOG("payload: %s", payload);
}

static void mqtt_disconnect_result_cb(mqtt_client_t *client, void *arg, int err)
{
    QL_MQTT_LOG("err: %d", err);

    ql_rtos_semaphore_release(mqtt_semp);
}

static void mqtt_app_thread(void *arg)
{
    int ret = 0;
    int i = 0, run_num = 1;
    int profile_idx = 1;
    ql_data_call_info_s info;
    char ip4_addr_str[16] = {0};
    mqtt_client_t mqtt_cli;
    uint8_t nSim = 0;
    uint16_t sim_cid;
    struct mqtt_connect_client_info_t client_info = {0};
    char *token = NULL;
    ql_rtos_semaphore_create(&mqtt_semp, 0);
    ql_rtos_task_sleep_s(10);

    char *client_id = (char *)malloc(256);
    char *client_user = (char *)malloc(256);
    char *client_pass = (char *)malloc(256);

    QL_MQTT_LOG("========== mqtt demo start ==========");
    QL_MQTT_LOG("wait for network register done");

    while ((ret = ql_network_register_wait(nSim, 120)) != 0 && i < 10)
    {
        i++;
        ql_rtos_task_sleep_s(1);
    }
    if (ret == 0)
    {
        i = 0;
        QL_MQTT_LOG("====network registered!!!!====");
    }
    else
    {
        QL_MQTT_LOG("====network register failure!!!!!====");
        goto exit;
    }

    ql_set_data_call_asyn_mode(nSim, profile_idx, 0);

    QL_MQTT_LOG("===start data call====");
    ret = ql_start_data_call(nSim, profile_idx, QL_PDP_TYPE_IP, "airtelgprs.com", NULL, NULL, 0);
    QL_MQTT_LOG("===data call result:%d", ret);
    if (ret != 0)
    {
        QL_MQTT_LOG("====data call failure!!!!=====");
    }
    memset(&info, 0x00, sizeof(ql_data_call_info_s));

    ret = ql_get_data_call_info(nSim, profile_idx, &info);
    if (ret != 0)
    {
        QL_MQTT_LOG("ql_get_data_call_info ret: %d", ret);
        ql_stop_data_call(nSim, profile_idx);
        goto exit;
    }
    QL_MQTT_LOG("info->profile_idx: %d", info.profile_idx);
    QL_MQTT_LOG("info->ip_version: %d", info.ip_version);

    QL_MQTT_LOG("info->v4.state: %d", info.v4.state);
    inet_ntop(AF_INET, &info.v4.addr.ip, ip4_addr_str, sizeof(ip4_addr_str));
    QL_MQTT_LOG("info.v4.addr.ip: %s\r\n", ip4_addr_str);

    inet_ntop(AF_INET, &info.v4.addr.pri_dns, ip4_addr_str, sizeof(ip4_addr_str));
    QL_MQTT_LOG("info.v4.addr.pri_dns: %s\r\n", ip4_addr_str);

    inet_ntop(AF_INET, &info.v4.addr.sec_dns, ip4_addr_str, sizeof(ip4_addr_str));
    QL_MQTT_LOG("info.v4.addr.sec_dns: %s\r\n", ip4_addr_str);

    while (run_num <= 100)
    {
        int test_num = 0;
        int ret = MQTTCLIENT_SUCCESS;

        QL_MQTT_LOG("==============mqtt_client_test[%d]================\n", run_num);

        if (QL_DATACALL_SUCCESS != ql_bind_sim_and_profile(nSim, profile_idx, &sim_cid))
        {
            QL_MQTT_LOG("nSim or profile_idx is invalid!!!!");
            break;
        }

        if (ql_mqtt_client_init(&mqtt_cli, sim_cid) != MQTTCLIENT_SUCCESS)
        {
            QL_MQTT_LOG("mqtt client init failed!!!!");
            break;
        }

        QL_MQTT_LOG("mqtt_cli:%d", mqtt_cli);
        client_info.keep_alive = 60;
        client_info.pkt_timeout = 5;
        client_info.retry_times = 3;
        client_info.clean_session = 1;
        client_info.will_qos = 0;
        client_info.will_retain = 0;
        client_info.will_topic = NULL;
        client_info.will_msg = NULL;
        client_info.client_id = MQTT_CLIENT_IDENTITY;
        client_info.client_user = MQTT_CLIENT_USER;
        client_info.client_pass = MQTT_CLIENT_PASS;
        client_info.ssl_cfg = NULL;
        ret = ql_mqtt_connect(&mqtt_cli, MQTT_CLIENT_QUECTEL_URL, mqtt_connect_result_cb, NULL, (const struct mqtt_connect_client_info_t *)&client_info, mqtt_state_exception_cb);
        if (ret == MQTTCLIENT_WOUNDBLOCK)
        {
            QL_MQTT_LOG("====wait connect result");
            ql_rtos_semaphore_wait(mqtt_semp, QL_WAIT_FOREVER);
            if (mqtt_connected == 0)
            {
                ql_mqtt_client_deinit(&mqtt_cli);
                break;
            }
        }
        else
        {
            QL_MQTT_LOG("===mqtt connect failed ,ret = %d", ret);
            break;
        }

        ql_mqtt_set_inpub_callback(&mqtt_cli, mqtt_inpub_data_cb, NULL);

        while (test_num < 10 && mqtt_connected == 1)
        {
            if (ql_mqtt_sub_unsub(&mqtt_cli, "topic/telemetry/gps/live", 1, mqtt_requst_result_cb, NULL, 1) == MQTTCLIENT_WOUNDBLOCK)
            {
                QL_MQTT_LOG("======wait subscrible result");
                ql_rtos_semaphore_wait(mqtt_semp, QL_WAIT_FOREVER);
            }

            if (ql_mqtt_publish(&mqtt_cli, "topic/telemetry/gps/live", "hi, mqtt qos 0", strlen("hi, mqtt qos 0"), 0, 0, mqtt_requst_result_cb, NULL) == MQTTCLIENT_WOUNDBLOCK)
            {
                QL_MQTT_LOG("======wait publish result");
                ql_rtos_semaphore_wait(mqtt_semp, QL_WAIT_FOREVER);
            }

            if (ql_mqtt_publish(&mqtt_cli, "topic/telemetry/gps/live", "hi, mqtt qos 1", strlen("hi, mqtt qos 1"), 1, 0, mqtt_requst_result_cb, NULL) == MQTTCLIENT_WOUNDBLOCK)
            {
                QL_MQTT_LOG("======wait publish result");
                ql_rtos_semaphore_wait(mqtt_semp, QL_WAIT_FOREVER);
            }

            if (ql_mqtt_publish(&mqtt_cli, "topic/telemetry/gps/live", "hi, mqtt qos 2", strlen("hi, mqtt qos 2"), 2, 0, mqtt_requst_result_cb, NULL) == MQTTCLIENT_WOUNDBLOCK)
            {
                QL_MQTT_LOG("======wait publish result");
                ql_rtos_semaphore_wait(mqtt_semp, QL_WAIT_FOREVER);
            }

            if (ql_mqtt_sub_unsub(&mqtt_cli, "topic/telemetry/gps/live", 1, mqtt_requst_result_cb, NULL, 0) == MQTTCLIENT_WOUNDBLOCK)
            {
                QL_MQTT_LOG("=====wait unsubscrible result");
                ql_rtos_semaphore_wait(mqtt_semp, QL_WAIT_FOREVER);
            }
            test_num++;
            ql_rtos_task_sleep_ms(500);
        }
        if (mqtt_connected == 1 && ql_mqtt_disconnect(&mqtt_cli, mqtt_disconnect_result_cb, NULL) == MQTTCLIENT_WOUNDBLOCK)
        {
            QL_MQTT_LOG("=====wait disconnect result");
            ql_rtos_semaphore_wait(mqtt_semp, QL_WAIT_FOREVER);
        }
        QL_MQTT_LOG("==============mqtt_client_test[%d] end=======%x=========\n", run_num, &mqtt_cli);
        ql_mqtt_client_deinit(&mqtt_cli);
        mqtt_connected = 0;
        run_num++;
        ql_rtos_task_sleep_s(1);
        break;
    }
exit:
    ql_rtos_semaphore_delete(mqtt_semp);
    ql_rtos_task_delete(mqtt_task);

    return;
}

int ql_mqtt_app_init(void)
{
    QlOSStatus err = QL_OSI_SUCCESS;

    err = ql_rtos_task_create(&mqtt_task, 16 * 1024, APP_PRIORITY_ABOVE_NORMAL, "QmqttApp", mqtt_app_thread, NULL, 5);
    if (err != QL_OSI_SUCCESS)
    {
        QL_MQTT_LOG("mqtt_app init failed");
    }

    return err;
}