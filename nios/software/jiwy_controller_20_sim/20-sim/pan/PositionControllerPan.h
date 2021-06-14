/**********************************************************
 * This file is generated by the 20-sim C++ Code Generator
 *
 *  file:  PositionControllerPan.h
 *  subm:  PositionControllerPan
 *  model: PositionControllerPan
 *  expmt: Jiwy
 *  date:  June 14, 2021
 *  time:  6:18:55 PM
 *  user:  20-sim 4.8 Campus License
 *  from:  Universiteit Twente
 *  build: 4.8.3.10415
 *
 **********************************************************/

/* This file describes the model functions
   that are supplied for computation.

   The model itself is the PositionControllerPan.cpp file
*/
#ifndef PositionControllerPan_H
#define PositionControllerPan_H

/* 20-sim include files */
#include "../common/xxmodel.h"
#include "../common/xxinteg.h"


class PositionControllerPan: virtual public Submodel20sim
{
	public:
		enum stateflags_PositionControllerPan {initialrun, mainrun, finished};

		/**
		 * PositionControllerPan constructor
		 */
		PositionControllerPan(void);

		/**
		 * PositionControllerPan destructor
		 */
		virtual ~PositionControllerPan(void);

		/**
		 * PositionControllerPan Initialization of the model and calculation of the values for the start time t
		 * @param u	This is the array with all input signals for this submodel
		 * @param y	This is the array with all output signals from this submodel
		 * @param t This is the start time for this run
		 */
		void Initialize (XXDouble *u, XXDouble *y, XXDouble t);

		/**
		 * PositionControllerPan Calculate
		 * @param u	This is the array with all input signals for this submodel
		 * @param y	This is the array with all output signals from this submodel
		 */
		void Calculate (XXDouble *u, XXDouble *y /*, XXDouble t*/ );

		/**
		 * PositionControllerPan Terminate
		 * @param u	This is the array with all input signals for this submodel
		 * @param y	This is the array with all output signals from this submodel
		 */
		void Terminate (XXDouble *u, XXDouble *y /*, XXDouble t*/ );


		/**
		 * SetFinishTime()
		 * @brief Overrrides the default finish time (from 20-sim) for this submodel
		 * @param time is the wanted finish time. Use 0.0 to change it to infinite.
		 * 
		 */
		bool SetFinishTime(XXDouble newtime);

		bool IsFinished(void);
		/**
		 * Reset()
		 * @brief Resets the submodel back to its initial state for a new run
		 */
		void Reset(XXDouble starttime);

		stateflags_PositionControllerPan state;

	protected:
		/**
		 * CalculateDynamic()
		 * This function calculates the dynamic equations of the model.
		 * These equations are called from the integration method
		 * to calculate the new model rates (that are then integrated).
		 */
		void CalculateDynamic (void);

	private:
		/* internal submodel computation methods */

		/**
		 * CalculateInitial()
		 * This function calculates the initial equations of the model.
		 * These equations are calculated before anything else
		 */
		void CalculateInitial (void);

		/**
		 * CalculateStatic()
		 * This function calculates the static equations of the model.
		 * These equations are only dependent from parameters and constants
		 */
		void CalculateStatic (void);

		/**
		 * CalculateInput()
		 * This function calculates the input equations of the model.
		 * These equations are dynamic equations that must not change
		 * in calls from the integration method (like random and delay).
		 */
		void CalculateInput (void);

		/**
		 * CalculateOutput()
		 * This function calculates the output equations of the model.
		 * These equations are not needed for calculation of the rates
		 * and are kept separate to make the dynamic set of equations smaller.
		 * These dynamic equations are called often more than one time for each
		 * integration step that is taken. This makes model computation much faster.
		 */
		void CalculateOutput (void);

		/**
		 * CalculateFinal()
		 * This function calculates the final equations of the model.
		 * These equations are calculated after all the calculations
		 * are performed
		 */
		void CalculateFinal (void);

		/**
		 * CopyInputsToVariables
		 * This private function copies the input variables from the input vector
		 * @param u	This is the array with all input signals for this submodel
		 */
		void CopyInputsToVariables (XXDouble *u);

		/**
		 * CopyVariablesToOutputs
		 * This private function copies the output variables to the output vector
		 * @param y	This is the array with all output signals from this submodel
		 */
		void CopyVariablesToOutputs (XXDouble *y);


		Discrete myintegmethod;	///< pointer to the integration method for this submodel
};

#endif	/* PositionControllerPan_H */

