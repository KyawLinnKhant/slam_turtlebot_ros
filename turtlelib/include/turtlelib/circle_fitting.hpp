// MIT License
//
// Copyright (c) 2024 Kyaw Linn Khant
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#ifndef CIRCLE_FITTING_INCLUDE_GUARD_HPP
#define CIRCLE_FITTING_INCLUDE_GUARD_HPP
/// \file
/// \brief Circle fitting algorithm
// https://nu-msr.github.io/navigation_site/lectures/circle_fit.html
// https://projecteuclid.org/journals/electronic-journal-of-statistics/volume-3/issue-none/Error-analysis-for-circle-fitting-algorithms/10.1214/09-EJS419.full

#include <iosfwd>
#include <cmath>
#include <armadillo>
#include "turtlelib/geometry2d.hpp"

namespace turtlelib
{
    /// \brief Circle size and location
    struct Circle
    {
        /// \brief the x coordinate of the circle's centroid
        double x = 0.0;

        /// \brief the y coordinate of the circle's centroid
        double y = 0.0;

        /// \brief the radius of the circle
        double R = 0.0;
    };

    /// \brief circle fitting algorithm
    /// \param cluster (std::vector<turtlelib::Vector2D>) pass one cluster in to fit a circle to
    /// \return radius and x,y coordinates of circle (turtlelib::Circle)
    Circle circle_fitting(std::vector<turtlelib::Point2D> cluster);

}

#endif