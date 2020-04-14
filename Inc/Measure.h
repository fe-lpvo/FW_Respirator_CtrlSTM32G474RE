/*
 * Measure.h
 *
 * Created: 6. 04. 2020 07:06:36
 *  Author: maticpi
 */ 


#ifndef MEASURE_H_
#define MEASURE_H_

#include "ADC.h"
#include "CommonDefinitions.h"
#include "ErrorHandling.h"
#include "motor.h"

#ifndef AVR
#define PROGMEM
#endif

void MeasureInit();
void MeasureFlow(MeasuredParams_t* Measured);
void MeasurePressure(MeasuredParams_t* Measured);
void MeasureVolume(MeasuredParams_t* Measured);

#define PRESSURE_MIN	(16*96UL)
#define PRESSURE_MAX	(16*918UL)
#define PRESSURE_SPAN	(PRESSURE_MAX - PRESSURE_MIN)
#define PRESSURE_ZERO_TRESHOLD	(2*16)
#define PRESSURE_MAX_MMH2O	500
#define FLOW_ZERO_TRESHOLD	100

#endif /* MEASURE_H_ */
