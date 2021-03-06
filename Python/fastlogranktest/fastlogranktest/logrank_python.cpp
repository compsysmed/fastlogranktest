#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <thread>
#include "boost/math/distributions.hpp"


std::vector<double> pvalues;
std::vector<std::vector<double>> groupas;
std::vector<std::vector<char>> groupacensoreds;
std::vector<std::vector<double>> groupbs;
std::vector<std::vector<char>> groupbcensoreds;

bool compareFunction(std::pair<double, char>& a, std::pair<double, char>& b)
{
	return a.first < b.first;
}

std::vector<std::pair<double, char>> cpugetpairvector(std::vector<double>& vect1, std::vector<char>& vect2)
{
	std::vector<std::pair<double, char>> target(vect1.size());
	for (unsigned long long i = 0; i < target.size(); i++)
		target[i] = std::make_pair(vect1[i], vect2[i]);
	return target;
}

double logrank_instance(std::vector<double>& groupa, std::vector<char>& groupacensored, std::vector<double>& groupb, std::vector<char>& groupbcensored, bool teststatistic) {

	std::vector<std::pair<double, char>> groupaboth = cpugetpairvector(groupa, groupacensored);
	std::vector<std::pair<double, char>> groupbboth = cpugetpairvector(groupb, groupbcensored);

	std::sort(groupaboth.begin(), groupaboth.end(), compareFunction);
	std::sort(groupbboth.begin(), groupbboth.end(), compareFunction);

	unsigned long long na = groupaboth.size();
	unsigned long long nb = groupbboth.size();
	unsigned long long nasize = na;
	unsigned long long nbsize = nb;
	unsigned long long n = na + nb;
	long double oa = 0.0;
	long double ea = 0.0;
	long double var = 0.0;
	unsigned long long indexa = 0;
	unsigned long long indexb = 0;

	while (na > 0 && nb > 0) {
		double value = groupaboth[indexa].first;
		unsigned long long count = 0;
		unsigned long long countb = 0;
		unsigned long long minusna = 0;
		unsigned long long minusnb = 0;

		if (indexb < nbsize && groupbboth[indexb].first < value) {
			++minusnb;
			value = groupbboth[indexb].first;
			if (groupbboth[indexb].second == 1) {
				++countb;

			}
			++indexb;
			while (indexb < nbsize && value == groupbboth[indexb].first) {
				if (groupbboth[indexb].second == 1) {
					++countb;
				}
				++indexb;
				++minusnb;
			}
		}
		else if (indexb < nbsize && groupbboth[indexb].first == value) {
			++minusna;
			if (groupaboth[indexa].second == 1) {
				++count;

			}
			++indexa;
			while (indexa < nasize && value == groupaboth[indexa].first) {
				if (groupaboth[indexa].second == 1) {
					++count;
				}
				++indexa;
				++minusna;
			}
			while (indexb < nbsize && value == groupbboth[indexb].first) {
				if (groupbboth[indexb].second == 1) {
					++countb;
				}
				++indexb;
				++minusnb;
			}
		}
		else {
			++minusna;
			if (indexa < nasize && groupaboth[indexa].second == 1) {
				++count;

			}
			++indexa;
			while (indexa < nasize && value == groupaboth[indexa].first) {
				if (groupaboth[indexa].second == 1) {
					++count;
				}
				++indexa;
				++minusna;
			}
		}

		ea += static_cast<long double>(na * (count + countb)) / static_cast<long double>(n);
		oa += count;
		var += (static_cast<long double>(na) * static_cast<long double>(nb * (count + countb)) * static_cast<long double>(n - (count + countb))) / (static_cast<long double>(n) * static_cast<long double>(n) * static_cast<long double>(n - 1));
		na -= minusna;
		nb -= minusnb;
		n = na + nb;
	}
	long double logrank = ((oa - ea) * (oa - ea)) / var;
	if (teststatistic) {
		return static_cast<double>(logrank);
	}
	double pvalue = 1.0;
	if (logrank >= 0) {
		pvalue = (1.0 - boost::math::cdf(boost::math::chi_squared(1), logrank));
		//std::cout << pvalue << std::endl;
	}
	return pvalue;
}

double logrank_instance(std::vector<double>& groupa, std::vector<char>& groupacensored, std::vector<double>& groupb, std::vector<char>& groupbcensored) {
	return logrank_instance(groupa, groupacensored, groupb, groupbcensored, false);
}

void startthread(unsigned long long start, unsigned long long end, bool teststatistic) {
	for (unsigned long long j = start; j < end; ++j) {
		pvalues[j] = logrank_instance(groupas[j], groupacensoreds[j], groupbs[j], groupbcensoreds[j], teststatistic);
	}
}

std::vector<double> cpu_parallel_logrank(std::vector<std::vector<double>>& groupas_, std::vector<std::vector<char>>& groupacensoreds_, std::vector<std::vector<double>>& groupbs_, std::vector<std::vector<char>>& groupbcensoreds_, unsigned threadnumber, bool teststatistic) {

	//std::cout << "Use " << threadnumber << " threads!" << std::endl;
	groupas = groupas_;
	groupbs = groupbs_;
	groupacensoreds = groupacensoreds_;
	groupbcensoreds = groupbcensoreds_;
	unsigned long long totalsize = groupas.size();
	pvalues.resize(totalsize);
	std::vector<std::thread> threads(threadnumber);
	unsigned long long countperthread = (totalsize / threadnumber) + 1;
	unsigned long long countperthreadstart = 0;
	for (unsigned j = 0; j < threadnumber; ++j) {
		unsigned long long start = countperthreadstart;
		countperthreadstart += countperthread;
		unsigned long long end = countperthreadstart;
		if (end > totalsize) {
			end = totalsize;
		}
		threads[j] = (std::thread(startthread, start, end, teststatistic));
		//threads[j]= std::thread(logrank_instance, groupas[j], groupacensoreds[j], groupbs[j], groupbcensoreds[j], j);
		//logrank_instance(groupas[j], groupacensoreds[j], groupbs[j], groupbcensoreds[j], j);
	}

	for (unsigned j = 0; j < threadnumber; ++j) {
		threads[j].join();
	}

	return pvalues;
}

std::vector<double> cpu_parallel_logrank(std::vector<std::vector<double>>& groupas, std::vector<std::vector<char>>& groupacensoreds, std::vector<std::vector<double>>& groupbs, std::vector<std::vector<char>>& groupbcensoreds, unsigned threadnumber) {
	return cpu_parallel_logrank(groupas, groupacensoreds, groupbs, groupbcensoreds, threadnumber, false);
}

std::vector<double> cpu_parallel_logrank1(std::vector<std::vector<double>>& groupas, std::vector<std::vector<char>>& groupacensoreds, std::vector<std::vector<double>>& groupbs, std::vector<std::vector<char>>& groupbcensoreds, bool teststatistic) {
	return cpu_parallel_logrank(groupas, groupacensoreds, groupbs, groupbcensoreds, std::thread::hardware_concurrency(), teststatistic);
}

std::vector<double> cpu_parallel_logrank(std::vector<std::vector<double>>& groupas, std::vector<std::vector<char>>& groupacensoreds, std::vector<std::vector<double>>& groupbs, std::vector<std::vector<char>>& groupbcensoreds) {
	return cpu_parallel_logrank(groupas, groupacensoreds, groupbs, groupbcensoreds, std::thread::hardware_concurrency(), false);
}