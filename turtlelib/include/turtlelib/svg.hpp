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
// SVG.h
#ifndef SVG_H
#define SVG_H

#include <iostream>
#include <fstream>
#include <vector>

/// \file
/// \brief SVG File generator.

/// \brief SVG File generator class.
class SVG {
public:
    /// \brief Creates the .svg file 
    /// \param width width of the file
    /// \param height height of the file
    SVG(int width, int height);

    /// \brief Adds a rectangle to the .svg
    /// \param x x coordinate of the rectangle
    /// \param y y coordinate of the rectangle
    /// \param width width of the rectangle
    /// \param height height of the rectangle
    void addRectangle(int x, int y, int width, int height);

    /// \brief Creates a circle in the .svg
    /// \param cx x coordinate of the centre
    /// \param cy y coordinate of the centre
    /// \param r radius of the circle
    /// \param color color of the circle
    void addCircle(int cx, int cy, int r, const std::string& color);

    /// \brief Adds a line in the .svg
    /// \param x1 x of the start of the line
    /// \param y1 y of the start of the line
    /// \param x2 x of the end of the line
    /// \param y2 y of the end of the line
    /// \param stroke color of the line
    void addLine(int x1, int y1, int x2, int y2, const std::string& stroke);

    /// \brief Adds text to the .svg
    /// \param x x coordinate of the text box
    /// \param y y coordinate of the text box
    /// \param text the text that is written to the .svg
    void addText(int x, int y, const std::string& text);

    /// \brief saves the .svg to a specific file
    /// \param filename name of the file to save to
    /// \param additionalContent .the svg example that is modified
    void saveToFile(const std::string& filename, const std::string& additionalContent);
    
    /// \brief Gets the width of the image
    /// \return the width of the .svg
    int getWidth();
    
    /// \brief Gets the height of the image
    /// \return the height of the .svg
    int getHeight();

private:
    /// \brief width of the svg file
    int width;
    /// \brief height of the svg file
    int height;
    /// \brief detail elements of the svg file
    std::vector<std::string> elements;
};

#endif // SVG_H