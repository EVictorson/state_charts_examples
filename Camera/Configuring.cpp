//////////////////////////////////////////////////////////////////////////////
// Copyright 2002-2006 Andreas Huber Doenni
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "Precompiled.hpp"
#include "Configuring.hpp"
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>



Configuring::Configuring()
{
  std::cout << "Entering Configuring\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

Configuring::~Configuring()
{
  std::cout << "Exiting Configuring\n";
}
