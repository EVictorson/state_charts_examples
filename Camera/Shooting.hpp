#ifndef BOOST_STATECHART_EXAMPLE_SHOOTING_HPP_INCLUDED
#define BOOST_STATECHART_EXAMPLE_SHOOTING_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright 2002-2006 Andreas Huber Doenni
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "Camera.hpp"

#include <boost/statechart/event.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/deferral.hpp>

#include <boost/mpl/list.hpp>
#include <boost/config.hpp>

#ifdef BOOST_INTEL
#  pragma warning( disable: 304 ) // access control not specified
#endif

namespace sc = boost::statechart;
namespace mpl = boost::mpl;

struct EvInFocus : sc::event< EvInFocus > {};

struct Focusing;
// Shooting metastate belonging to Camera state machine with initial state Focusing
struct Shooting : sc::simple_state< Shooting, Camera, Focusing >
{
  //typedef sc::transition< EvShutterRelease, NotShooting > reactions;
  typedef sc::transition< EvShutterRelease, sc::deep_history< Idle >> reactions;
  
  Shooting();
  ~Shooting();

  void DisplayFocused( const EvInFocus & )
  {
    std::cout << "Focused!\n";
  }
};

// The focusing circuit then moves the lenses accordingly and sends the 
// EvInFocus event as soon as it is done. Of course, the user can fully-press 
// the shutter while the lenses are still in motion. Without any precautions, 
// the resulting EvShutterFull event would simply be lost because the Focusing 
// state does not define a reaction for this event. As a result, the user would 
// have to fully-press the shutter again after the camera has finished focusing. 
// To prevent this, the EvShutterFull event is deferred inside the Focusing state. 
// This means that all events of this type are stored in a separate queue, which is 
// emptied into the main queue when the Focusing state is exited.

  // Focusing state belonging to the Shooting Metastate
  struct Focusing : sc::state< Focusing, Shooting >
  {
    typedef mpl::list<
      sc::custom_reaction< EvInFocus >,
      sc::deferral< EvShutterFull >
    > reactions;

    Focusing( my_context ctx );
    sc::result react( const EvInFocus & );
  };



#endif
