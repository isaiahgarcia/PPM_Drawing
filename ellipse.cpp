#include "ellipse.h"
#include "vec2.h"
#include <stdexcept>

using namespace std;

std::ostream& operator<<(std::ostream &out, const ellipse &theEllipse) {
        out << "an ellipse\n";
        return out;
}

void ellipse::validate() {
        try {
                try {
                        if (center.x() < 0 || center.y() < 0)
                                throw out_of_range("ellipse center less zero");
                } catch (const out_of_range& p) {
                        std::cout << p.what() << std::endl;
                        this->setColor(color(0));
                }

                if (radii.x() == 0 || radii.y() == 0) {
                        throw domain_error("ellipse divide zero");
                }
        } catch (const domain_error& p) {
                std::cout << p.what() << std::endl;
                this->setRadii(vec2(2,2));
                this->setColor(color(255, 0, 0));
        }
}

