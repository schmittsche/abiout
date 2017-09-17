/**
 * @file include/graph.hpp
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


#ifndef GRAPH_HPP
#define GRAPH_HPP

#ifdef _WIN32
#include "base/win32.hpp"
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#undef HAVE_CONFIG_H
#endif

#include <string>
#include <list>
#include <vector>
#include <ostream>
#include <fstream>

/** 
 *
 */
class Graph {

  private :

  protected :

    std::string _xlabel; ///< Label for x axis
    std::string _ylabel; ///< Label for y axis
    std::string _title;  ///< Title for the graph


  public :

    /** 
     * Type to know what to do with the plot function
     */
    enum GraphSave { NONE, PRINT, DATA };

    typedef struct Config {
      std::vector<double> x;
      std::list<std::vector<double>> y;
      std::list<std::pair<std::vector<double>,std::vector<double>>> xy;
      std::list<std::string> labels;
      std::vector<short> colors;
      std::string filename;
      std::string xlabel;
      std::string ylabel;
      std::string title;
      GraphSave save;
      bool doSumUp;

      Config() :
        x(),
        y(),
        xy(),
        labels(),
        colors(),
        filename("Untitled"),
        xlabel(),
        ylabel(),
        title("Untitled"),
        save(NONE),
        doSumUp(true) 
      {}
    } Config;

    /**
     * Constructor.
     */
    Graph();

    /**
     * Destructor.
     */
    virtual ~Graph();

    /** 
     * Plot several quantities on the screen
     * @param x The x quantity
     * @param y A vector with several y quantites to plot
     * @param labels The labels corresponding to the y quantities.
     */
    virtual void plot(std::vector<double> x, std::list<std::vector<double>> y, std::list<std::string> labels, std::vector<short> colors) = 0;

    /** 
     * Plot several quantities on the screen
     * @param xy A list of (x,y) pairs to plot
     * @param labels The labels corresponding to the y quantities.
     */
    virtual void plot(std::list< std::pair< std::vector<double>,std::vector<double> > > xy, std::list<std::string> labels, std::vector<short> colors) = 0;

    /**
     * Save the graph
     * @param filename Save to filename
     * */
    virtual void save(std::string filename) = 0;

    /**
     * Clean everything
     */
    virtual void clean() = 0;

    /**
     * Setter
     * @param lab The new value 
     */
    void setXLabel(std::string lab) { _xlabel = lab; };

    /**
     * Setter
     * @param lab The new value 
     */
    void setYLabel(std::string lab) { _ylabel = lab; };

    /**
     * Setter
     * @param lab The new value 
     */
    void setTitle(std::string lab) { _title = lab; };

    /**
     * Add custom command depending on frontend
     * @param customlines The custom commands to add
     */
    virtual void custom(const std::string &customlines) = 0;

    /**
     * Print out the commande to plot
     * @param out ostream for output
     * @param plotname is the filename for the file that would be created when the graph is created
     * Not the script file that would be executed to creat the graph
     */
    virtual void dump(std::ostream& out, std::string& plotname) const = 0;

    /**
     * Creat a file with the current command for plotting.
     * @param filename The name of the file to be written which contains the commands to plot the graph.
     */
    void dump(const std::string& filename) const;

    /**
     * Creat a file with the current command for plotting.
     * @param filename The name of the file to be written which contains the commands to plot the graph.
     */
    static void plot(const Config &conf, Graph* gplot);
};

#endif  // GRAPH_HPP
