//////////////////////////////////////////////////////////////////////////////
// Copyright 2002-2006 Andreas Huber Doenni
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "Precompiled.hpp"
#include "Camera.hpp"
#include "Configuring.hpp"
#include "Shooting.hpp"



// NotShooting state
NotShooting::NotShooting()
{
  std::cout << "Entering NotShooting\n";
}

NotShooting::~NotShooting()
{
  std::cout << "Exiting NotShooting\n";
}

// custom reaction to the EvShutterHalf event
sc::result NotShooting::react( const EvShutterHalf & )
{
  if ( context< Camera >().IsBatteryLow() )
  {
    return forward_event();
  }
  else
  {
    return transit< Shooting >();
  }
}

// Idle state
Idle::Idle()
{
  std::cout << "Entering Idle\n";
}

Idle::~Idle()
{
  std::cout << "Exiting Idle\n";
}

// custom reaction to the EvConfig event
sc::result Idle::react( const EvConfig & )
{
  return transit< Configuring >();
}
