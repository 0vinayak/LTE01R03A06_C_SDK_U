
#include "ble_defs.h"


union LDSUnion Live_Data;
union ErrorUnion error_data;


Live_Data.lds_data.vehicle_speed_value = 15;//vd_VehSpdKmph_u8;                                                           // BLE
Live_Data.lds_data.motor_speed_value = 0;//0;                                                                            // BLE
Live_Data.lds_data.battery_voltage_value = 30;//UART_RX_Data_un.RX_Spl_St.Battery_Voltage;                                // UART
Live_Data.lds_data.battery_soc_value = 20;// mi_BatSOC_u8;                                                                 // UART
Live_Data.lds_data.throttle_value = 5;//UART_RX_Data_un.RX_Spl_St.Throttle;                                              // UART
Live_Data.lds_data.pas_mode_value = 3;//UART_RX_Data_un.RX_Spl_St.PAS_Mode;                                              // UART
Live_Data.lds_data.ride_mode_value = 1;//Vehicle_Control_data.vcs_data.ride_mode_value;                                  // BLE
Live_Data.lds_data.dte_value = 40;//UART_RX_Data_un.RX_Spl_St.RemMilage_0 | (UART_RX_Data_un.RX_Spl_St.RemMilage_1 << 8); // UART
Live_Data.lds_data.time_to_charge_value = 0;                                                                         // BLE   ??
//odo_big_value += (uint32_t)Live_Data.lds_data.vehicle_speed_value * (stop_odo_timer() * 0.1) / 3600 * 1000;
Live_Data.lds_data.current_trip_distance_value = 60;//(uint8_t)(uint32_t)((odo_big_value - odo_start_value) / 1000); // BLE
Live_Data.lds_data.current_trip_max_speed_value = 30;//vd_CurTrpMaxSpd_u8;                                           // BLE   ??
Live_Data.lds_data.side_stand_value = 0;//UART_RX_Data_un.RX_Spl_St.Side_Stand;                                     // UART
Live_Data.lds_data.headlamp_value = 1;//UART_RX_Data_un.RX_Spl_St.Headlight_Status;                                 // UART
Live_Data.lds_data.brake_value = 0;//UART_RX_Data_un.RX_Spl_St.PwrOffBrk_sts;                                       // UART
Live_Data.lds_data.cruise_control_status = 1;//UART_RX_Data_un.RX_Spl_St.Cruise_sts;                                // UART
Live_Data.lds_data.walk_mode_status = 0;//UART_RX_Data_un.RX_Spl_St.Cruise6km_sts;                                  // UART
Live_Data.lds_data.toast_notification = 1;//fm_Notification;                                                        // UART  ??
// Live_Data.lds_data.vehicle_odo_reading          =   vd_VehOdoKm_u16                                 ;   //BLE
Live_Data.lds_data.vehicle_odo_reading = 35;//odo_big_value;

Live_Data.lds[0] = 15;
Live_Data.lds[1] = 15;
Live_Data.lds[2] = 15;
Live_Data.lds[3] = 15;
Live_Data.lds[4] = 15;
Live_Data.lds[5] = 15;
Live_Data.lds[6] = 15;
Live_Data.lds[7] = 15;
Live_Data.lds[8] = 15;
Live_Data.lds[9] = 15;
Live_Data.lds[10] = 15;
Live_Data.lds[11] = 15;
Live_Data.lds[12] = 15;
Live_Data.lds[13] = 15;
Live_Data.lds[14] = 15;

Live_Data.lds[15] = 15;
Live_Data.lds[16] = 15;
Live_Data.lds[17] = 15;
Live_Data.lds[18] = 15;
Live_Data.lds[19] = 15;
//Live_Data.lds[0] = 15;

//error_data.error[0] = 1;

for (size_t i = 0; i < 10; i++)
{
    error_data.error[i] = 1;
}

// error_data.bits.e1 = 1; 
// error_data.bits.e2 = 0;
// error_data.bits.e3 = 1;
// error_data.bits.e4 = 0;
// error_data.bits.e5 = 1;
// error_data.bits.e6 = 1;
// error_data.bits.e7 = 1;
// error_data.bits.e8 = 0;
// error_data.bits.e9 = 1;
// error_data.bits.e10 = 0;