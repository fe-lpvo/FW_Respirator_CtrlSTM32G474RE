/*
 * ActuatorControl.c
 *
 * Created: 4. 04. 2020 10:14:58
 *  Author: maticpi
 */ 
#include "ActuatorControl.h"

  float motorSpeed;
  float motorCurrent;
//TODO: every time control mode is changed, PID could be reset and loaded with appropriate parameters
void ActuatorControl(CtrlParams_t* Control, MeasuredParams_t* Measured, RespSettings_t *Settings, fpidData_t *PIDdata)
{
//  static uint8_t last_mode = CTRL_PAR_MODE_STOP;
//  uint8_t cur_mode = Control->mode;

  motorCurrent=motor_GetCurrent();
	Control->cur_position = motor_GetPosition();
	Control->cur_speed = (Control->cur_position - Control->last_position) / TIME_SLICE_MS;
	
	switch(Control->mode)
	{
// STOP MODES ///////////////////////////////////////////////////////////////////////
		case CTRL_PAR_MODE_STOP:
			motor_SetSpeed(0);
			PID_fReset(PIDdata);
			break;

		case CTRL_PAR_MODE_HOLD_MAX_CLOSED_POSITION:
      motor_SetSpeed(0.01);  //turn motor direction to close (inhale) and
			break;                 //maintain minimum duty cycle to hold clamps together

// SPEED CONTROL MODE ///////////////////////////////////////////////////////////
		case CTRL_PAR_MODE_TARGET_SPEED:
			if (Control->target_speed > 0)
			{
				if (Control->cur_position < CTRL_PAR_MAX_POSITION)	//Obey if within limits
				  { motor_SetSpeed(Control->target_speed);}
				else {  motor_SetSpeed(0); }	//Stop if too far
			}
			else //else if (Control->target_speed < 0)
			{
				if (Control->cur_position > CTRL_PAR_MIN_POSITION)	//Obey if within limits
				  { motor_SetSpeed(Control->target_speed);}
        else {  motor_SetSpeed(0); }  //Stop if too far
			}
			break;

// POSITION REGULATION MODES ///////////////////////////////////////////////////////////
		case CTRL_PAR_MODE_TARGET_POSITION_INHALE:
			if (Control->target_position - Control->cur_position >= 0)
			{
				if (Control->target_position - Control->cur_position > 2) { motorSpeed=100; }
				else { motorSpeed = 50; }
			}
			if (motorSpeed > 0)
			{
				motor_SetSpeed(motorSpeed);
			}
			
		break;
		
		case CTRL_PAR_MODE_TARGET_POSITION: //Replace with PID regulator
		  motorSpeed=0;
			if (Control->target_position - Control->cur_position >= 0)
			{
				if (Control->target_position - Control->cur_position > 2) motorSpeed=50;
				else
				{
					Control->mode=CTRL_PAR_MODE_STOP;
          motor_SetSpeed(0);
				}
			}
			if (Control->target_position - Control->cur_position < 0)
			{
				if (Control->target_position - Control->cur_position < -2) motorSpeed=-25;
				else
				{
					Control->mode=CTRL_PAR_MODE_STOP;
					motor_SetSpeed(0);
				}
			}
			motor_SetSpeed(motorSpeed);
		break;

// PRESSURE REGULATION MODES ///////////////////////////////////////////////////////////
// dummy regulation for motor start-up - should probably be solved differently
		case CTRL_PAR_MODE_DUMMY_REGULATE_PRESSURE_PID_RESET:
			PID_fInit(Settings->PID_Pressure.P_Factor,
			          Settings->PID_Pressure.I_Factor,
			          Settings->PID_Pressure.D_Factor,
			          Settings->PID_Pressure.maxError,
			          Settings->PID_Pressure.maxSumError,
			          PIDdata);
			Control->mode=CTRL_PAR_MODE_DUMMY_REGULATE_PRESSURE;
			//DO NOT PUT BREAK HERE!

		case CTRL_PAR_MODE_DUMMY_REGULATE_PRESSURE:
			//can only regulate inspiration		//pressure span 50mmH2O --> cca 14500 (14500/16 = cca 900)
			motorSpeed = PID_fCalculate(1,Control->target_pressure, Measured->pressure, PIDdata);
			if (Control->target_speed > 0)
			{
				if (Control->cur_position < CTRL_PAR_MAX_POSITION)	//Obey if within limits
				{ motor_SetSpeed(Control->target_speed); }
				else { motor_SetSpeed(0); } //Stop if too far
			}
			else // if (Control->target_speed < 0)
			{
				if (Control->cur_position > CTRL_PAR_MIN_POSITION)	//Obey if within limits
        { motor_SetSpeed(Control->target_speed); }
        else { motor_SetSpeed(0); } //Stop if too far
			}
			break;

////////////////// normal pressure regulation mode /////////////////////////
		case CTRL_PAR_MODE_REGULATE_PRESSURE_PID_RESET:
      PID_fInit(Settings->PID_Pressure.P_Factor,
                Settings->PID_Pressure.I_Factor,
                Settings->PID_Pressure.D_Factor,
                Settings->PID_Pressure.maxError,
                Settings->PID_Pressure.maxSumError,
                PIDdata);
			Control->mode=CTRL_PAR_MODE_REGULATE_PRESSURE;
			//DO NOT PUT BREAK HERE!

		case CTRL_PAR_MODE_REGULATE_PRESSURE:
			//can only regulate inspiration		//pressure span 50mmH2O
		  motorSpeed = PID_fCalculate(1,Control->target_pressure, Measured->pressure, PIDdata);
			if (Control->cur_position >= CTRL_PAR_MAX_POSITION)
			{
				motorSpeed = 0.01;  //minimum speed setting to maintain inhale direction and minimum clamp pressure
			}
			if (motorSpeed < 0) motorSpeed = 0.01;  //minimum speed setting to maintain inhale direction and minimum clamp pressure
			motor_SetSpeed(motorSpeed);
		break;

// VOLUME REGULATION MODES ///////////////////////////////////////////////////////////
// dummy regulation for motor start-up - should probably be solved differently
    case CTRL_PAR_MODE_DUMMY_REGULATE_VOLUME_PID_RESET:
      PID_fInit(Settings->PID_Volume.P_Factor,
                Settings->PID_Volume.I_Factor,
                Settings->PID_Volume.D_Factor,
                Settings->PID_Volume.maxError,
                Settings->PID_Volume.maxSumError,
                PIDdata);
      Control->mode=CTRL_PAR_MODE_DUMMY_REGULATE_VOLUME;
      //DO NOT PUT BREAK HERE!

    case CTRL_PAR_MODE_DUMMY_REGULATE_VOLUME:
      //can only regulate inspiration   //pressure span 50mmH2O --> cca 14500 (14500/16 = cca 900)
      motorSpeed = PID_fCalculate(1,Control->target_volume, Measured->volume_t, PIDdata);
      if (Control->target_speed > 0)
      {
        if (Control->cur_position < CTRL_PAR_MAX_POSITION)  //Obey if within limits
        { motor_SetSpeed(Control->target_speed); }
        else { motor_SetSpeed(0); } //Stop if too far
      }
      else // if (Control->target_speed < 0)
      {
        if (Control->cur_position > CTRL_PAR_MIN_POSITION)  //Obey if within limits
        { motor_SetSpeed(Control->target_speed); }
        else { motor_SetSpeed(0); } //Stop if too far
      }
      break;

////////////////// normal volume regulation mode /////////////////////////
    case CTRL_PAR_MODE_REGULATE_VOLUME_PID_RESET:
      PID_fInit(Settings->PID_Volume.P_Factor,
                Settings->PID_Volume.I_Factor,
                Settings->PID_Volume.D_Factor,
                Settings->PID_Volume.maxError,
                Settings->PID_Volume.maxSumError,
                PIDdata);
      Control->mode=CTRL_PAR_MODE_REGULATE_VOLUME;
      //DO NOT PUT BREAK HERE!

    case CTRL_PAR_MODE_REGULATE_VOLUME:
      //can only regulate inspiration   //pressure span 50mmH2O
      motorSpeed = PID_fCalculate(1,Control->target_volume, Measured->volume_t, PIDdata);
      if (Control->cur_position >= CTRL_PAR_MAX_POSITION)
      {
        motorSpeed = 0.01;  //minimum speed setting to maintain inhale direction and minimum clamp pressure
      }
      if (motorSpeed < 0) motorSpeed = 0.01;  //minimum speed setting to maintain inhale direction and minimum clamp pressure
      motor_SetSpeed(motorSpeed);
    break;

// FLOW REGULATION MODES ///////////////////////////////////////////////////////////
// dummy regulation for motor start-up - should probably be solved differently
    case CTRL_PAR_MODE_DUMMY_REGULATE_FLOW_PID_RESET:
      PID_fInit(Settings->PID_Flow.P_Factor,
                Settings->PID_Flow.I_Factor,
                Settings->PID_Flow.D_Factor,
                Settings->PID_Flow.maxError,
                Settings->PID_Flow.maxSumError,
                PIDdata);
      Control->mode=CTRL_PAR_MODE_DUMMY_REGULATE_FLOW;
      //DO NOT PUT BREAK HERE!

    case CTRL_PAR_MODE_DUMMY_REGULATE_FLOW:
      //can only regulate inspiration
      motorSpeed = PID_fCalculate(1,Control->target_flow, Measured->flow, PIDdata);
      if (Control->target_speed > 0)
      {
        if (Control->cur_position < CTRL_PAR_MAX_POSITION)  //Obey if within limits
        { motor_SetSpeed(Control->target_speed); }
        else { motor_SetSpeed(0); } //Stop if too far
      }
      else // if (Control->target_speed < 0)
      {
        if (Control->cur_position > CTRL_PAR_MIN_POSITION)  //Obey if within limits
        { motor_SetSpeed(Control->target_speed); }
        else { motor_SetSpeed(0); } //Stop if too far
      }
      break;

////////////////// normal flow regulation mode /////////////////////////
		case CTRL_PAR_MODE_REGULATE_FLOW_PID_RESET:
      PID_fInit(Settings->PID_Flow.P_Factor,
                Settings->PID_Flow.I_Factor,
                Settings->PID_Flow.D_Factor,
                Settings->PID_Flow.maxError,
                Settings->PID_Flow.maxSumError,
                PIDdata);
			Control->mode=CTRL_PAR_MODE_REGULATE_FLOW;
      //DO NOT PUT BREAK HERE!

		case CTRL_PAR_MODE_REGULATE_FLOW:
			//can only regulate inspiratory part of the cycle
			motorSpeed = PID_fCalculate(1,Control->target_flow, Measured->flow, PIDdata);
			if (Control->cur_position >= CTRL_PAR_MAX_POSITION)
			{
        motorSpeed = 0.01;  //minimum speed setting to maintain inhale direction and minimum clamp pressure
			}
      if (motorSpeed<0) motorSpeed = 0.01;
      motor_SetSpeed(motorSpeed);
		break;

///////////////////////////////////////////////////////////////////////////////////
// ERROR - UNKNOWN MODE ///////////////////////////////////////////////////////////
		default: //Error: Stop immediately
		ReportError(ActuatorCtrlUnknownMode,FSH("Unknown actuator control mode"));
		Control->mode=CTRL_PAR_MODE_TARGET_POSITION;
		motor_SetSpeed(0);
		break;
	}

//	last_mode = cur_mode;
	Control->last_position = Control->cur_position;
}
