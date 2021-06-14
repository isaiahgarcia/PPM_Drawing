#ifndef IMAGE_H
#define IMAGE_H

#include <math.h>
#include "color.h"

using namespace std;

template <typename T>
class image  {
	public:
		image(int w, int h, T backGround) : width(w), height(h) {
			for(int i=0; i <width*height; i++)
				thePixels.push_back(backGround);
		}

		int w() const {return width; }
		int h() const {return height; }
	    void writePixel(ostream& out, int x, int y, T cOut) const;
	    void writeHeader(ostream& out) const;
	    void writeNewLine(ostream& out) const;
	    void setPixel(int x, int y, T in) {
	    	thePixels.at(mapXY(x,y)) = in;
	    }
	    void fullWriteOut(ostream& out);

	private:
		int mapXY(int x, int y) {return y*(width-1) + x; }
		int width;
		int height;
		vector<T> thePixels;
};

template<typename T> 
void image<T>::fullWriteOut(ostream& out) {
	writeHeader(out);
	//for each pixel, write out its T
	for (int y=0; y < height; y++) {
		for (int x =0; x < width; x++) {
			writePixel(out, x, y, thePixels.at(mapXY(x, y)));
		}
		writeNewLine(out);
	}
}

// template specialization: ppm
template <> 
void image<color>::writePixel(ostream& out, int x, int y, color cOut) const {
	out << static_cast<int>(clamp(cOut.r(), 0.0, 255)) << " "
					<< static_cast<int>(clamp(cOut.g(), 0.0, 255)) << " "
					<< static_cast<int>(clamp(cOut.b(), 0.0, 255)) << endl; 
}

// template specialization: pgm
template <> 
void image<int>::writePixel(ostream& out, int x, int y, int cOut) const {
 	out << static_cast<int>(cOut) << endl;
}

// template specialization: pbm
template <> 
void image<bool>::writePixel(ostream& out, int x, int y, bool cOut) const {
 	out << static_cast<int>(cOut) << endl;
}

// template specialization: ascii
template <> 
void image<char>::writePixel(ostream& out, int x, int y, char cOut) const {
 	out << cOut; 
}

template <typename T> 
void image<T>::writeNewLine(ostream& out) const {
 	out << "\n"; 
}

// template specialization: ppm
template <> 
void image<color>::writeHeader(ostream& out) const {
	//PPM format header
 	out << "P3\n" << width << " " << height << "\n255\n"; 
}

// template specialization: pgm
template <> 
void image<int>::writeHeader(ostream& out) const {
	//PGM format header
 	out << "P2\n" << width << " " << height << "\n255\n"; 
}

// template specialization: pbm
template <> 
void image<bool>::writeHeader(ostream& out) const {
	//PBM format header
 	out << "P1\n" << width << " " << height; 
}

// template specialization: ascii
template <> 
void image<char>::writeHeader(ostream& out) const {
	//ASCII format header
 	out << "Ascii Header\n" << width << " " << height << endl;
}

#endif


