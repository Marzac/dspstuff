/**
	SinI16
	Mimapped sinus waveform
	(c) Frédéric Meslin - Fred's Lab 2018-2020
	http://www.fredslab.net
	MIT license
	
	Copyright 2020 Frédéric Meslin
	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**/

#ifndef SINI16_H
#define SINI16_H

#include <stdint.h>
#include <math.h>

template<int N, int S>
struct SinI16
{
	constexpr static const int mm = (int) log2(N);
	constexpr SinI16() : values()
	{
		int size = N;
		int16_t * samples = values;
		for (int i = 0; i <= mm; i++) {
			makeSine(samples, size);
			samples += size + 1;
			size /= 2;
		}
	}
	
	void makeSine(int16_t * samples, int size)
	{
		double scale = (double) (1 << S);
		for (int i = 0; i < size; i++) {
			double v = sin((2.0 * M_PI * i) / size);
			samples[i] = (int16_t) (v * scale);
		}
		samples[size] = samples[0];
	}
	
	int16_t operator()(int32_t pos) const
	{
		int i = pos >> 8;
		int16_t v1 = values[i];
		int16_t v2 = values[i+1];
		int16_t f = pos & 0xFF;
		return v1 + (((v2 - v1) * f) >> 8);
	}
	
	int16_t values[N * 2 + mm];
};

#endif
