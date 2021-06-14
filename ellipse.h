#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <iostream>
#include "color.h"
#include "vec2.h"
#include "shape.h"

// using namespace std;

/* simple data representation of an implicit ellipse */
class ellipse : public shape {
  public:
	ellipse(double cX, double cY, double r1, double r2, color C) : shape{C, 0}, 
		center(cX, cY), radii(r1, r2) {}
	ellipse(vec2 inC, double r1, double r2, double d, color C) : shape{C, d},
		 center(inC), radii(r1, r2) {}
	ellipse(vec2 inC, vec2 inR, double d, color C) : shape{C, d},
		 center(inC), radii(inR) {}
	ellipse(double cX, double cY, double r1, double r2, double d, color C) : shape{C, d},
		center(cX, cY), radii(r1, r2) {}

	bool eval(double x, double y) override {
		if( ((center.x()-x)*(center.x()-x))/(radii.x()*radii.x()) + 
				((center.y()-y)*(center.y()-y))/(radii.y()*radii.y()) - 1.0f < 0) {
			return true;
		}
		return false;
	}

	void validate();

	// void validate() {
 //        try {
 //                try {
 //                        if (center.x() < 0 || center.y() < 0)
 //                                throw out_of_range("ellipse center less zero");
 //                } catch (const out_of_range& p) {
 //                        std::cout << p.what() << std::endl;
 //                        this->setColor(color(0));
 //                }

 //                if (radii.x() == 0 || radii.y() == 0) {
 //                        throw domain_error("ellipse divide zero");
 //                }
 //        } catch (const domain_error& p) {
 //                std::cout << p.what() << std::endl;
 //                this->setRadii(vec2(2,2));
 //                this->setColor(color(255, 0, 0));
 //        }
// }



	//note lifted getters

	double getMaxR() {return fmax(radii.x(), radii.y());}
	vec2 getCenter() const { return center; }

	void setCenter(vec2 inCenter) { center = inCenter; }
	void setRadii(vec2 inRadii) { radii = inRadii; }

	friend std::ostream& operator<<(std::ostream &out, const shape &theEllipse);

  private:
	vec2 center; //center point of ellipse
	vec2 radii; //radii of the ellipse
	//note lifted data
};


#endif