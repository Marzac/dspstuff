/**
	FastExp2f
	Fast exponential of 2 approximation
	(c) Frédéric Meslin - Fred's Lab 2018-2020
	http://www.fredslab.net
	MIT license
	
	Copyright 2020 Frédéric Meslin
	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**/

#ifndef FASTEXP2F_H
#define FASTEXP2F_H

#include <stdint.h>
#include <math.h>

template<int N>
struct FastExp2f
{
	constexpr FastExp2f() :	values()
	{
		for (int i = 0; i < N + 1; i++) {
			double t = i / (double) N;
			values[i] = (float) exp2(t - 16.0);
		}
	}

	float operator()(float t) const {
		
		float pos = t * N;
		if (t < 0.0f) pos = -pos;

		int s = (int) pos;
		int e = s / N;
		int i = s & (N - 1);
		float f = pos - (float) (e * N + i);
		
		float v1 = values[i];
		float v2 = values[i+1];
		uint32_t k = (uint32_t) 1 << (16 + e);
		float v = k * ((v2 - v1) * f + v1);
		return t < 0.0f ? 1.0f / v : v;
	}

	float values[N+1];
};

#endif
