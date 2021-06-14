#ifndef RECT_H
#define RECT_H

#include "vec2.h"
#include "shape.h"
#include <stdexcept>

using namespace std;

/* simple data representation of a rectangle */
class Rect : public shape {
  public:
	Rect(double lX, double lY, double rX, double rY, color C, double deep) : shape{C, deep},
		upperL(lX, lY), lowerR(rX, rY) {}
	
	Rect(vec2(left), vec2(right), color C, double deep) : shape{C, deep},
		upperL(left), lowerR(right) {}
	Rect(vec2(left), double width, double height, color C, double deep) : shape{C, deep},
		upperL(left), lowerR(left.x()+width,left.y()+height) {}

	bool eval(double x, double y) override {
		if ((x >= upperL.x() && x <= lowerR.x()) && (y >= upperL.y() && y <= lowerR.y())) {
			return true;
		}
		return false;
	}

	void translate(vec2 offset) {
		upperL += offset;
		lowerR += offset;
	}

	void validate() { 
		try {
			try {
				if (upperL.x() < 0|| upperL.y() < 0 || lowerR.x() < 0 || lowerR.y() < 0)
					throw out_of_range("rect vert less zero");
			} catch (const out_of_range& p) {
				std::cout << p.what() << std::endl;
				this->setColor(color(0));
			}
			
			if (upperL.x() >= lowerR.x() || upperL.y() >= lowerR.y()) {
				throw domain_error("rect order incorrect");
			}
		} catch (const domain_error& p) {
			std::cout << p.what() << std::endl;
			if (upperL.x() >= lowerR.x() && upperL.y() >= lowerR.y()) {
				this->setLCorner(vec2(lowerR.x(), lowerR.y()));
				this->setRCorner(vec2(upperL.x(), upperL.y()));
			} else if (upperL.x() >= lowerR.x() && upperL.y() < lowerR.y()) {
				vec2 coordinate = upperL;
				this->setLCorner(vec2(lowerR.x(), upperL.y()));
				this->setRCorner(vec2(coordinate.x(), lowerR.y()));
			} else if (upperL.x() < lowerR.x() && upperL.y() >= lowerR.y()) {
				vec2 coordinate = upperL;
				this->setLCorner(vec2(upperL.x(), lowerR.y()));
				this->setRCorner(vec2(lowerR.x(), coordinate.y()));
			} 
			
			this->setColor(color(255, 0, 0));
		}
	}

	double getWidth() const {return lowerR.x() - upperL.x(); }
	double getHeight() const {return lowerR.y() - upperL.y(); }
	double getArea() const {return (lowerR.x() - upperL.x())*(lowerR.y() - upperL.y());}

	void setLCorner(vec2 inLCor) { upperL = inLCor; }
	void setRCorner(vec2 inRCor) {lowerR = inRCor;}

  private:
	vec2 upperL;
	vec2 lowerR;

};

#endif
