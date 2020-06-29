// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-


// -- BEGIN LICENSE BLOCK ----------------------------------------------
// This file is part of FZIs ic_workspace.
//
// This program is free software licensed under the LGPL
// (GNU LESSER GENERAL PUBLIC LICENSE Version 3).
// You can find a copy of this license in LICENSE folder in the top
// directory of the source code.
//
// © Copyright 2014 FZI Forschungszentrum Informatik, Karlsruhe, Germany
//
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Georg Heppner <heppner@fzi.de>
 * \date    2014-5-22
 *
 */
//----------------------------------------------------------------------

#ifndef LWA4PSTATE_H
#define LWA4PSTATE_H

#include <icl_comm_websocket/RobotState.h>

namespace icl_comm {
namespace websocket {

class LWA4PState : public RobotState
{
public:

  enum MovementState
  {
    eST_DEACTIVATED,
    eST_CONTROLLED,
    eST_FAULT,
    eST_CHAIN_BUILT_UP,
    eST_IPM_MODE,
    eST_ERROR_ACKED,
    eST_COMMUTATION_FOUND,
    eST_PSEUDE_ABSOLUT_CALIBRATED,
    eST_JITTER_SYNCED,
    eST_SWITCH_OF_POSE_DIFFERS,
    eST_SWITCH_OF_POSE_VERIFIED,
    eST_READY,
    eST_ENABLED,
    eST_ABSOLUTE_POSITION_LOST,
    eST_DIMENSION
  };

  LWA4PState();


  /*!
   * \brief getStateJSON Returns the current robot state as JSON encoded String
   * \return current robot state as JSON encoded String
   */
  virtual std::string getStateJSON();

  virtual void setMovementState(const int &movement_state);

private:
  //! Current movement state of the whole robot
  MovementState m_movement_state;


};

}} // End of NS

#endif // LWA4PSTATE_H
