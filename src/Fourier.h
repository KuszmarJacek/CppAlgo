#pragma once

#include <iostream>
#include <complex>
#include <vector>
#include <numbers>
#include <cmath>

using namespace std::complex_literals;

std::vector<std::complex<double>> dft(std::vector<std::complex<double>> arr)
{
	std::vector<std::complex<double>> res;

	for(int k = 0; k < arr.size(); k++)
	{
		std::complex<double> sum = 0. + 0i;
		for(int j = 0; j < arr.size(); j++)
		{
			//      N = arr.size()
			//      N-1
			//       ∑ Xn * e^(-2πi/N * nk)
			//      n=0
			std::complex<double> exponent(0.0, std::numbers::pi / arr.size() * -2.0 * j * k);
			sum += arr[j] * std::exp(exponent);
		}
		res.push_back(sum);
	}

	return res;
};

//arr has to be of size 2 ^ n
void fft(std::vector<std::complex<double>>& arr)
{
	if(arr.size() == 1)
	{
		return;
	}

	std::vector<std::complex<double>> even;
	std::vector<std::complex<double>> odd;

	for(int k = 0; k < arr.size(); k++)
	{
		if(k % 2 == 0)
		{
			even.push_back(arr[k]);
		}
		else if(k % 2 == 1)
		{
			odd.push_back(arr[k]);
		}
	}

	fft(even);
	fft(odd);

	for(int k = 0; k < arr.size() / 2; k++)
	{
		//N = arr.size()
		//      N-1
		//       ∑ Xn * e^(-2πi/N * nk)
		//      n=0
		//std::polar(r, theta) is the same as r * std::exp(theta * 1i)
		//t = 1 * e^(-2πi/N * nk)
		std::complex<double> twiddleFactor = std::polar(1.0, -2 * std::numbers::pi * k / arr.size());
		arr[k] = even[k] + (twiddleFactor * odd[k]);
		arr[k + arr.size() / 2] = even[k] - (twiddleFactor * odd[k]);
	}
}
