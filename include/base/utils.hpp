/**
 * @file include/utils.hpp
 *
 * @brief 
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


#ifndef UTILS_HPP
#define UTILS_HPP

#ifdef _WIN32
#include "base/win32.hpp"
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#undef HAVE_CONFIG_H
#endif

#include <vector>
#include <list>
#include <string>
#ifndef HAVE_STOD
#include <cstdlib>
#endif
#include <stdexcept>
#include <numeric>
#include <cmath>
#include "base/exception.hpp"

//#define DEBUG_LOG(a) std::cerr << a << std::endl;

namespace utils {
  /**
   * Dump configuration and compilation information for debugging purpose
   * @param out stream to write to
   */
  void dumpConfig(std::ostream &out);

  /**
   * Overload std::to_string in case it does not exist
   * and write the function otherwise.
   * @param num Integer value only.
   * @return A string with num
   */
  template<typename T>
  std::string to_string(T num);

  /**
   * Overload std::stoi in case it does not exist
   * and write the function otherwise.
   * @param str string containing a double
   * @return the converted integer number
   */
  inline int stoi(const std::string& str) {
#ifdef HAVE_STOI
    try {
      return std::stoi(str);
    }
    catch(const std::invalid_argument& ex) {
      throw EXCEPTION(ex.what(),ERRDIV);
    }
    catch(const std::out_of_range& ex) {
      throw EXCEPTION(ex.what(),ERRDIV);
    }
    catch(...) {
      throw EXCEPTION("Bad cast string -> int",ERRDIV);
    }
#else
    long int val = strtol(str.c_str(), nullptr, 10);
    if ( errno == ERANGE 
        || val > ((1<<(sizeof(int)*8)/2)-1) 
        || val < -((1<<(sizeof(int)*8)/2)-1) ) 
      throw std::out_of_range("Bad string number");
    return (int) val;
#endif
  }

  /**
   * Overload std::stod in case it does not exist
   * and write the function otherwise.
   * @param str string containing a double
   * @return the converted double number.
   */
  inline double stod(const std::string& str) {
    //First change D exp notation in E exp notation (Fortran to C++)
    std::string s(str);
    size_t pos(s.find_first_of("Dd"));
    if (pos != std::string::npos) s[pos] = 'e';
#ifdef HAVE_STOD
    return std::stod(s);
#else
    double val = strtod(s.c_str(), nullptr);
    if ( errno == ERANGE ) throw std::out_of_range("Bad string number");
    return val;
#endif
  }

  /**
   * The string is transformed to be in lower case only
   * @param str The string to modify.
   */
  void tolower(std::string& str);

  /**
   * The string is transformed to be in upper case only
   * @param str The string to modify.
   */
  void toupper(std::string& str);

  /**
   * The string is transformed to be in lower case only
   * @param str The string to modify.
   */
  std::string tolower(const std::string& str);

  /**
   * The string is transformed to be in upper case only
   * @param str The string to modify.
   */
  std::string toupper(const std::string& str);

  /**
   * Trim right a string by copy
   * @param str The string to trim
   * @param delimiters Character to ignore
   * @return The trimmed string
   */
  inline std::string rtrim(const std::string& str, const std::string& delimiters = " \f\n\r\t\v" ) {
    return str.substr( 0, str.find_last_not_of( delimiters ) + 1 );
  }

  /**
   * Trim left a string by copy
   * @param str The string to trim
   * @param delimiters Character to ignore
   * @return The trimmed string
   */
  inline std::string ltrim(const std::string& str, const std::string& delimiters = " \f\n\r\t\v" ) {
    return str.substr( str.find_first_not_of( delimiters ) );
  }

  /**
   * Trim left and right a string by copy
   * @param str The string to trim
   * @param delimiters Character to ignore
   * @return The trimmed string
   */
  inline std::string trim(const std::string& str, const std::string& delimiters = " \f\n\r\t\v" ) {
    return rtrim( ltrim( str, delimiters ), delimiters );
  }

  /**
   * Trim right a string by erasing
   * @param str The string to trim
   * @param delimiters Character to ignore
   */
  inline void rtrim(std::string& str, const std::string& delimiters = " \f\n\r\t\v" ) {
    str.erase( str.find_last_not_of( delimiters ) + 1 );
  }

  /**
   * Trim left a string by erasing
   * @param str The string to trim
   * @param delimiters Character to ignore
   */
  inline void ltrim(std::string& str, const std::string& delimiters = " \f\n\r\t\v" ) {
    str.erase( 0, str.find_first_not_of( delimiters ) );
  }

  /**
   * Trim left and right a string by erasing
   * @param str The string to trim
   * @param delimiters Character to ignore
   */
  inline void trim(std::string& str, const std::string& delimiters = " \f\n\r\t\v" ) {
    ltrim( str, delimiters );
    rtrim( str, delimiters );
  }

  /**
   * Split a string into a vector of string.
   * The split is done with the delim character.
   * @param str Input string to split.
   * @param delim Delimiter to perform the split.
   * @return A vector a string from the input string splitted.
   */
  std::vector<std::string> explode(const std::string& str, const char delim);

  //template<typename T>
  double mean(std::vector<double>::const_iterator first, std::vector<double>::const_iterator last);

  //template<typename T>
  double deviation(std::vector<double>::const_iterator first, std::vector<double>::const_iterator last, const double meanV);

  /**
   * Small function to print mean value of plot function
   */
  void sumUp(const std::list<std::vector<double>>& y, const std::list<std::string>& labels,std::ostream& sum);
}

#endif  // UTILS_HPP
