#ifndef RGBTYPE_H
#define RGBTYPE_H

struct RGBType
{
	double r = 0;
	double g = 0;
	double b = 0;

	RGBType(){};
	RGBType(double _r, double _b, double _g) : r(_r), g(_g), b(_b) {};

	RGBType clip()
	{
		if (this->r < 0)
			this->r = 0;
		if (this->g < 0)
			this->g = 0;
		if (this->b < 0)
			this->b = 0;

		return RGBType(r, g, b);
	}

	RGBType* divideBy(double value)
	{
		this->r /= value;
		this->g /= value;
		this->b /= value;

		return this;
	}

	RGBType* addColor(RGBType* value)
	{
		this->r += value->r;
		this->g += value->g;
		this->b += value->b;

		return this;
	}

	RGBType* addColor(RGBType value)
	{
		this->r += value.r;
		this->g += value.g;
		this->b += value.b;

		return this;
	}

	RGBType* mixColors(RGBType aBase, double intensityThis, double intensityA)
	{
		double max = intensityThis + intensityA;
		double percentThis = max / intensityThis;
		double percentA = max / intensityA;

		RGBType* base = this->divideBy(percentThis);
		RGBType* a = aBase.divideBy(percentA);

		RGBType* result = this->addColor(a);

		return this;
	}
};

#endif