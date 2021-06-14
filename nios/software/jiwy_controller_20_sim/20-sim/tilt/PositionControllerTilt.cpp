/**********************************************************
 * This file is generated by the 20-sim C++ Code Generator
 *
 *  file:  PositionControllerTilt.cpp
 *  subm:  PositionControllerTilt
 *  model: PositionControllerTilt
 *  expmt: Jiwy
 *  date:  June 14, 2021
 *  time:  6:19:39 PM
 *  user:  20-sim 4.8 Campus License
 *  from:  Universiteit Twente
 *  build: 4.8.3.10415
 **********************************************************/

/* Standard include files */
#include <stdio.h>
#include <math.h>
/* Include the header for memcpy and memset
 * You may need to change this into <memory.h> for older compilers
 */
#include <string.h>

/* 20-sim include files */
#include "PositionControllerTilt.h"

/* Delta margin used for end time checking */
const XXDouble c_delta = 1.0e-7;

/* this PRIVATE function sets the input variables from the input vector */
void PositionControllerTilt::CopyInputsToVariables (XXDouble *u)
{
	/* copy the input vector to the input variables */
	m_V[8] = u[0];		/* corr */
	m_V[9] = u[1];		/* in */
	m_V[10] = u[2];		/* position */

}

/* this PRIVATE function uses the output variables to fill the output vector */
void PositionControllerTilt::CopyVariablesToOutputs (XXDouble *y)
{
	/* copy the output variables to the output vector */
	y[0] = 	m_V[11];		/* out */

}

PositionControllerTilt::PositionControllerTilt(void)
{
	m_number_constants = 0;
	m_number_parameters = 7;
	m_number_initialvalues = 3;
	m_number_variables = 12;
	m_number_states = 3;
	m_number_rates = 3;
	m_number_matrices = 0;
	m_number_unnamed = 0;

	/* the variable arrays */
	m_C = new XXDouble[0 + 1];		/* constants */
	m_P = new XXDouble[7 + 1];		/* parameters */
	m_I = new XXDouble[3 + 1];		/* initial values */
	m_V = new XXDouble[12 + 1];		/* variables */
	m_s = new XXDouble[3 + 1];		/* states */
	m_R = new XXDouble[3 + 1];		/* rates (or new states) */
	m_M = new XXMatrix[0 + 1];		/* matrices */
	m_U = new XXDouble[0 + 1];		/* unnamed */
	m_workarray = new XXDouble[0 + 1];

	Reset(0.0);
	m_finish_time = 20.0;
}

void PositionControllerTilt::Reset(XXDouble starttime)
{
	m_start_time = starttime;
	m_step_size = 0.01;
	m_time = starttime;
	m_major = true;
	m_stop_run = false;

	/* Clear the allocated variable memory */
	memset(m_C, 0, (0 + 1) * sizeof(XXDouble));
	memset(m_P, 0, (7 + 1) * sizeof(XXDouble));
	memset(m_I, 0, (3 + 1) * sizeof(XXDouble));
	memset(m_V, 0, (12 + 1) * sizeof(XXDouble));
	memset(m_s, 0, (3 + 1) * sizeof(XXDouble));
	memset(m_R, 0, (3 + 1) * sizeof(XXDouble));
	memset(m_M, 0, (0 + 1) * sizeof(XXDouble));
	memset(m_U, 0, (0 + 1) * sizeof(XXDouble));
	memset(m_workarray, 0, (0 + 1) * sizeof(XXDouble));


	state = initialrun;
}

bool PositionControllerTilt::IsFinished(void)
{
	return (state == finished);
}

PositionControllerTilt::~PositionControllerTilt(void)
{
	/* free memory */
	delete[] m_C;
	delete[] m_P;
	delete[] m_I;
	delete[] m_V;
	delete[] m_s;
	delete[] m_R;
	delete[] m_M;
	delete[] m_U;
	delete[] m_workarray;
}

/* the initialization function for submodel */
void PositionControllerTilt::Initialize (XXDouble *u, XXDouble *y, XXDouble t)
{
	/* initialization phase (allocating memory) */
	m_initialize = true;
	m_stop_run = false;

	/* set the constants */


	/* set the parameters */
	m_P[0] = 0.0;		/* corrGain\K */
	m_P[1] = 1.6;		/* PID1\kp */
	m_P[2] = 0.05;		/* PID1\tauD */
	m_P[3] = 0.001;		/* PID1\beta */
	m_P[4] = 10.5;		/* PID1\tauI */
	m_P[5] = -0.99;		/* SignalLimiter2\minimum */
	m_P[6] = 0.99;		/* SignalLimiter2\maximum */


	/* set the initial values */
	m_I[0] = 0.0;		/* PID1\uD_previous_initial */
	m_I[1] = 0.0;		/* PID1\error_previous_initial */
	m_I[2] = 0.0;		/* PID1\uI_previous_initial */


	/* set the states */
	m_s[0] = m_I[0];		/* PID1\uD_previous */
	m_s[1] = m_I[1];		/* PID1\error_previous */
	m_s[2] = m_I[2];		/* PID1\uI_previous */


	/* set the matrices */


	/* (re-)initialize the integration method */
	myintegmethod.Initialize(this);
	
	/* copy the inputs */
	m_time = t;
	CopyInputsToVariables (u);

	/* calculate initial and static equations */
	CalculateInitial ();
	CalculateStatic ();
	CalculateInput ();
	CalculateDynamic ();
	CalculateOutput ();

	/* Set the outputs */
	CopyVariablesToOutputs (y);

	/* end of initialization phase */
	m_initialize = false;

	state = mainrun;
}

/* the function that calculates the submodel */
void PositionControllerTilt::Calculate (XXDouble *u, XXDouble *y /*, XXDouble t*/)
{
	switch (state)
	{
		case initialrun:	/* calculate the model for the first time */
			Initialize(u, y, 0.0);
			break;
		case mainrun:	/* calculate the model */
			if ( ( m_time <= (m_finish_time - m_step_size  + c_delta )) || ( m_finish_time == 0.0 ) )
			{
				/* another precessor submodel could determine the parameters of this submodel
				   and therefore the static parameter calculations need to be performed. */
				CalculateStatic ();
				CopyInputsToVariables (u);
				CalculateInput ();
				myintegmethod.Step();
				CalculateOutput ();
				CopyVariablesToOutputs (y);
			}
			else
			{
				state = finished;
			}

			if ( ( m_stop_run == true ) || (( m_finish_time != 0.0 ) && ( m_time + c_delta >= m_finish_time)) )
			{
				state = finished;
			}
			break;
		case finished:
			break;
		default:
			break;
	}
}

/* the termination function for submodel */
void PositionControllerTilt::Terminate (XXDouble *u, XXDouble *y /*, XXDouble t */)
{
	/* copy the inputs */
	CopyInputsToVariables (u);

	/* calculate the final model equations */
	CalculateFinal ();

	/* set the outputs */
	CopyVariablesToOutputs (y);
}


/* This function calculates the initial equations of the model.
 * These equations are calculated before anything else
 */
void PositionControllerTilt::CalculateInitial (void)
{

}

/* This function calculates the static equations of the model.
 * These equations are only dependent from parameters and constants
 */
void PositionControllerTilt::CalculateStatic (void)
{

}

/* This function calculates the input equations of the model.
 * These equations are dynamic equations that must not change
 * in calls from the integration method (like random and delay).
 */
void PositionControllerTilt::CalculateInput (void)
{

}

/* This function calculates the dynamic equations of the model.
 * These equations are called from the integration method
 * to calculate the new model rates (that are then integrated).
 */
void PositionControllerTilt::CalculateDynamic (void)
{
	/* PID1\factor = 1 / (sampletime + PID1\tauD * PID1\beta); */
	m_V[3] = 1.0 / (m_step_size + m_P[2] * m_P[3]);

	/* corrGain\input = corr; */
	m_V[0] = m_V[8];

	/* PlusMinus2\plus1 = in; */
	m_V[5] = m_V[9];

	/* PlusMinus2\minus1 = position; */
	m_V[6] = m_V[10];

	/* corrGain\output = corrGain\K * corrGain\input; */
	m_V[1] = m_P[0] * m_V[0];

	/* PID1\error = PlusMinus2\plus1 - PlusMinus2\minus1; */
	m_R[1] = m_V[5] - m_V[6];

	/* PID1\uD = PID1\factor * (((PID1\tauD * PID1\uD_previous) * PID1\beta + (PID1\tauD * PID1\kp) * (PID1\error - PID1\error_previous)) + (sampletime * PID1\kp) * PID1\error); */
	m_R[0] = m_V[3] * (((m_P[2] * m_s[0]) * m_P[3] + (m_P[2] * m_P[1]) * (m_R[1] - m_s[1])) + (m_step_size * m_P[1]) * m_R[1]);

	/* PID1\uI = PID1\uI_previous + (sampletime * PID1\uD) / PID1\tauI; */
	m_R[2] = m_s[2] + (m_step_size * m_R[0]) / m_P[4];

	/* PID1\output = PID1\uI + PID1\uD; */
	m_V[2] = m_R[2] + m_R[0];

	/* PlusMinus1\output = corrGain\output + PID1\output; */
	m_V[4] = m_V[1] + m_V[2];

	/* SignalLimiter2\output = (if PlusMinus1\output < SignalLimiter2\minimum then SignalLimiter2\minimum else (if PlusMinus1\output > SignalLimiter2\maximum then SignalLimiter2\maximum else PlusMinus1\output end) end); */
	m_V[7] = ((m_V[4] < m_P[5]) ? 
		/* SignalLimiter2\minimum */
		m_P[5]
	:
		/* (if PlusMinus1\output > SignalLimiter2\maximum then SignalLimiter2\maximum else PlusMinus1\output end) */
		((m_V[4] > m_P[6]) ? 
			/* SignalLimiter2\maximum */
			m_P[6]
		:
			/* PlusMinus1\output */
			m_V[4]
		)
	);

}

/* This function calculates the output equations of the model.
 * These equations are not needed for calculation of the rates
 * and are kept separate to make the dynamic set of equations smaller.
 * These dynamic equations are called often more than one time for each
 * integration step that is taken. This makes model computation much faster.
 */
void PositionControllerTilt::CalculateOutput (void)
{
	/* out = SignalLimiter2\output; */
	m_V[11] = m_V[7];

}

/* This function calculates the final equations of the model.
 * These equations are calculated after all the calculations
 * are performed
 */
void PositionControllerTilt::CalculateFinal (void)
{

}



bool PositionControllerTilt::SetFinishTime(XXDouble newtime)
{
	if ((newtime <= 0.0) || ( newtime > m_time))
	{
		m_finish_time = newtime;
		return true;
	}

	return false;
}

