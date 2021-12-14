//////////////////////////////////////////////////////////////////////////////
// Copyright 2002-2006 Andreas Huber Doenni
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "Precompiled.hpp"
#include "Shooting.hpp"
#include <iostream>
#include <chrono>
#include <thread>

#include <boost/config.hpp>

#ifdef BOOST_INTEL
#  pragma warning( disable: 383 ) // reference to temporary used
#endif


Shooting::Shooting()
{
  std::cout << "Entering Shooting\n";
}

Shooting::~Shooting()
{
  std::cout << "Exiting Shooting\n";
}

// Storing state belonging to Shooting metastate
struct Storing : sc::simple_state< Storing, Shooting >
{
  Storing()
  {
    std::cout << "Picture taken!\n";
  }
};

// Focused state
struct Focused : sc::simple_state< Focused, Shooting >
{
  typedef sc::custom_reaction< EvShutterFull > reactions;

  sc::result react( const EvShutterFull & );
};

// react to the EvShutterFull event
sc::result Focused::react( const EvShutterFull & )
{
  if ( context< Camera >().IsMemoryAvailable() )
  {
    return transit< Storing >();
  }
  else
  {
    std::cout << "Cache memory full. Please wait...\n";
    return discard_event();
  }
}

// Focusing state (pass in state machine context)
Focusing::Focusing( my_context ctx ) : my_base( ctx )
{
  std::cout<<"Focusing..."<<std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  std::cout<<"Focusing complete!"<<std::endl;

  // after focusing is complete post the EvInFocus event
  post_event( boost::intrusive_ptr< EvInFocus >( new EvInFocus() ) );
}

// React to the EvInFocus event by transitioning to the focused state
sc::result Focusing::react( const EvInFocus & evt )
{
  // transit to Focused state and call DisplayFocused helper function
  return transit< Focused >( &Shooting::DisplayFocused, evt );
}
