/**
 * @file mendeleev.hpp
 *
 * @brief Periodic table to get some constants species related.
 *
 * @author Jordan Bieder <jordan.bieder@cea.fr>
 *
 * @copyright Copyright 2014 Jordan Bieder
 *
 * This file is part of AbiOut.
 *
 * AbiOut is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AbiOut is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AbiOut.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MENDELEEV_HPP
#define MENDELEEV_HPP

#include "base/utils.hpp"
#include "base/exception.hpp"
#include <string>
#include <locale>

/**
 * A public structure to access some general data that can be tuned.
 * Basically it contains the name, mass, radius and a color for each specie.
 */
struct mendeleev {

 /** Define the name of each specie. */
 static const char name[119][4];

 /** Define the mass of each specie. */
 static double mass[119];

 /** Define the radius of each specie. */
 static double radius[119];

 /** Define the color of each specie. */
 static float color[119][3];

 /**
  * find the znucl corresponding to a string
  * @param inname Symbol of the specie to find
  * @return The znucl value correponding to the name
  */
 static unsigned znucl(const std::string &inname);

 /**
  * find the znucl corresponding to a mass
  * @param inmass
  * @return The znucl value correponding to the name
  */
 static unsigned znucl(const double inmass);
};
#endif  // MENDELEEV_H PP
