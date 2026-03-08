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
// SVG.cpp
#include "turtlelib/svg.hpp"

SVG::SVG(int width, int height) : width(width), height(height) {
    elements.push_back("<svg width=\"" + std::to_string(width) + "\" height=\"" + std::to_string(height) + "\">");
}

void SVG::addRectangle(int x, int y, int w, int h) {
    elements.push_back("<rect x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) +
                       "\" width=\"" + std::to_string(w) + "\" height=\"" + std::to_string(h) + "\"/>");
}

void SVG::addCircle(int cx, int cy, int r, const std::string& color) {
    elements.push_back("<circle cx=\"" + std::to_string(cx) + "\" cy=\"" + std::to_string(cy) +
                       "\" r=\"" + std::to_string(r) + "\" stroke=\"" + color + "\" fill=\"" + color + "\" stroke-width=\"1\"/>");
}

void SVG::addLine(int x1, int y1, int x2, int y2, const std::string& stroke) {
    elements.push_back("<line x1=\"" + std::to_string(x1) + "\" y1=\"" + std::to_string(y1) +
                       "\" x2=\"" + std::to_string(x2) + "\" y2=\"" + std::to_string(y2) + "\" stroke=\"" + stroke + "\" stroke-width=\"2\" marker-start=\"url(#Arrow1Sstart)\"/>");
}

void SVG::addText(int x, int y, const std::string& text) {
    elements.push_back("<text x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) + "\">" + text + "</text>");
}

void SVG::saveToFile(const std::string& filename, const std::string& additionalContent) {
    elements.push_back(additionalContent);
    elements.push_back("</svg>");
    
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const std::string& element : elements) {
            file << element << "\n";
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int SVG::getWidth(){
    return width;
}
