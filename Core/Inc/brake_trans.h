/**
  ******************************************************************************
  * @file    brake_trans.h
  * @author  Jaycee Alipio
  ******************************************************************************
  * @attention
  *
  * Bruin Supermileage DAQ Team
  *
  * Converts brake transducer voltage into PSI value
  *
  ******************************************************************************
  */

#ifndef BRAKE_PRESSURE_H
#define BRAKE_PRESSURE_H

#include <stdint.h>

// CAN Frame uses 8 bytes, but we will use float (4 bytes) for faster computation and less resources

typedef struct
{
	uint32_t adc_raw;
	float psi_value;
	uint32_t can_id;
	uint8_t can_data[8]; // Up to 8 bytes for CAN data
}BrakeTrans;

// ---- Hardware Constants ----
#define BRAKE_TRANS_ADC_MAX     4095U
#define BRAKE_TRANS_VREF        3.3f       // STM32 ADC reference voltage
#define BRAKE_TRANS_DIVIDER     2.0f       // Voltage divider ratio (sensor -> ADC)
#define BRAKE_TRANS_VMAX        4.5f       // Sensor full-scale voltage
#define BRAKE_TRANS_VMIN        0.5f       // Sensor zero-pressure voltage

// ---- Calibration Constants ----
#define BRAKE_TRANS_SLOPE       125.0f
#define BRAKE_TRANS_OFFSET      62.5f

// ---- Physical Limits ----
#define PSI_MAX					500.0f
#define PSI_MIN					0.0f

static inline float BrakeTrans_ADCtoPSI(uint32_t adc_counts)
{
	float v_sensor = (adc_counts * BRAKE_TRANS_VREF * BRAKE_TRANS_DIVIDER) / BRAKE_TRANS_ADC_MAX;
	float psi = (BRAKE_TRANS_SLOPE * v_sensor) - BRAKE_TRANS_OFFSET;
	if (psi < PSI_MIN) psi = PSI_MIN;
	if (psi > PSI_MAX) psi = PSI_MAX;
	return psi;
}


#endif // BRAKE_PRESSURE_H
