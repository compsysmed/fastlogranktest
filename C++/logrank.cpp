#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <boost/math/distributions.hpp>
#include <stdio.h>
#include <thread>
//#include <mutex>


std::vector<double> pvalues;
//std::mutex pvalueslock;
std::vector<double> survivalinformation;
std::vector<char> censoredinformation;
std::vector<std::string> file;


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

std::vector<double> cpuparsevector(std::string& line)
{
	std::vector<double> vector;
	for (unsigned long long k = 0; k < line.length(); ++k) {
		std::string parsestr = "";
		while (k < line.length() && line.at(k) != ',') {
			parsestr += line.at(k);
			k++;
		}
		//std::cout<<std::stof(parsestr)<<std::endl;
		vector.push_back(std::stod(parsestr));
	}
	return vector;
}

std::vector<double> getsurvivalvector(std::string& line)
{
	std::vector<double> vector;
	for (unsigned long long k = 0; k < line.length(); ++k) {
		std::string parsestr = "";
		while (k < line.length() && line.at(k) != '\t') {
			parsestr += line.at(k);
			k++;
		}
		//std::cout<<std::stof(parsestr)<<std::endl;
		vector.push_back(std::stod(parsestr));
	}
	return vector;
}

std::vector<char> cpuparsevectorcensored(std::string& line)
{
	std::vector<char> vector;
	for (unsigned long long k = 0; k < line.length(); ++k) {
		std::string parsestr = "";
		char element = line.at(k);
		if (element != ',' && element != '\n') {
			vector.push_back(element);
		}

	}
	return vector;
}

std::vector<char> getcensoredvector(std::string& line)
{
	std::vector<char> vector;
	for (unsigned long long k = 0; k < line.length(); k += 2) {
		std::string parsestr = "";
		char element = line.at(k);
		if (element != ',' && element != '\t') {
			vector.push_back(element);
		}

	}
	return vector;
}

void logrank_instance(std::vector<double> groupa, std::vector<char> groupacensored, std::vector<double> groupb, std::vector<char> groupbcensored, unsigned long long index) {

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
	//long double ob = 0.0;
	//long double eb = 0.0;
	long double var = 0.0;

	unsigned long long indexa = 0;
	unsigned long long  indexb = 0;

	while (na > 0 && nb > 0) {
		double value = groupaboth[indexa].first;
		unsigned long long count = 0;
		unsigned long long countb = 0;
		unsigned long long minusna = 0;
		unsigned long long minusnb = 0;

		if (indexb < nbsize && groupbboth[indexb].first < value) {
			++minusnb;
			value = groupbboth[indexb].first;
			if (groupbboth[indexb].second == '1') {
				++countb;

			}
			++indexb;
			while (indexb < nbsize && value == groupbboth[indexb].first) {
				if (groupbboth[indexb].second == '1') {
					++countb;
				}
				++indexb;
				++minusnb;
			}
		}
		else if (indexb < nbsize && groupbboth[indexb].first == value) {
			++minusna;
			if (groupaboth[indexa].second == '1') {
				++count;

			}
			++indexa;
			while (indexa < nasize && value == groupaboth[indexa].first) {
				if (groupaboth[indexa].second == '1') {
					++count;
				}
				++indexa;
				++minusna;
			}
			while (indexb < nbsize && value == groupbboth[indexb].first) {
				if (groupbboth[indexb].second == '1') {
					++countb;
				}
				++indexb;
				++minusnb;
			}
		}
		else {
			++minusna;
			if (indexa < nasize && groupaboth[indexa].second == '1') {
				++count;

			}
			++indexa;
			while (indexa < nasize && value == groupaboth[indexa].first) {
				if (groupaboth[indexa].second == '1') {
					++count;
				}
				++indexa;
				++minusna;
			}
		}

		ea += static_cast<long double>(na * (count + countb)) / static_cast<long double>(n);
		//eb += (long double (nb) * (long double((count + countb)) / long double(n)));
		//ob += countb;
		oa += count;
		var += (static_cast<long double>(na) * static_cast<long double>(nb * (count + countb)) * static_cast<long double>(n - (count + countb))) / (static_cast<long double>(n) * static_cast<long double>(n) * static_cast<long double>(n - 1));
		na -= minusna;
		nb -= minusnb;
		n = na + nb;
		//std::cout<<value<<std::endl<<n<<std::endl<<na<<std::endl<<nb<<std::endl<<std::endl;

	}

	//long double oldlogrank= (((oa-ea)*(oa-ea))/ea)+(((ob-eb)*(ob-eb))/eb);
	long double logrank = ((oa - ea) * (oa - ea)) / var;
	//long double control=((oa-ea)*(oa-ea))/ea;
	//long double controllogrank= ((ob-eb)*(ob-eb))/var;
	//std::cout << logrank << std::endl;
	//double pvalue = (1.0 - boost::math::cdf(boost::math::chi_squared(1), logrank));
	double pvalue = 1.0;
	if (logrank >= 0) {
		pvalue = (1.0 - boost::math::cdf(boost::math::chi_squared(1), logrank));
		//std::cout << pvalue << std::endl;
	}
	//pvalueslock.lock();
	//std::cout<<pvalue<<std::endl;
	pvalues[index] = pvalue;
	//pvalueslock.unlock();
}

void startthread(unsigned long long start, unsigned long long end) {
	for (unsigned long long j = start; j < end; ++j) {
		std::vector<double> groupa;
		std::vector<char> groupacensored;
		std::vector<double> groupb;
		std::vector<char> groupbcensored;
		unsigned long long position = 0;
		std::string line = file[j];
		for (unsigned long long j = 0; j < line.length(); j += 2) {
			//std::cout<<line.at(j);
			if (line.at(j) == '1') {
				groupa.push_back(survivalinformation[position]);
				groupacensored.push_back(censoredinformation[position]);
			}
			else if (line.at(j) == '2') {
				groupb.push_back(survivalinformation[position]);
				groupbcensored.push_back(censoredinformation[position]);
			}
			++position;
		}
		logrank_instance(groupa, groupacensored, groupb, groupbcensored, j);
	}
}


void cpu_parallel_logrank(std::string& input, std::string& output, int threadnumber) {
	std::time_t wholetime = std::time(nullptr);
	std::ifstream infile(input);
	std::ofstream outfile(output);


	if (infile.is_open() && outfile.is_open()) {
		//int i=0;
		std::cout << "Use " << threadnumber << " threads!" << std::endl;
		std::string line = "";
		getline(infile, line);
		survivalinformation = getsurvivalvector(line);
		getline(infile, line);
		censoredinformation = getcensoredvector(line);
		while (getline(infile, line)) {//&&i<1) {
			file.push_back(line);
		}
		std::cout << "Reading time: " << std::time(nullptr) - wholetime << "s" << std::endl;
		std::time_t logranktime = std::time(nullptr);

		unsigned long long totalsize = file.size();
		pvalues.resize(totalsize);
		std::vector<std::thread> threads(threadnumber);
		unsigned long long countperthread = (totalsize / threadnumber) + 1;
		unsigned countperthreadstart = 0;
		for (unsigned j = 0; j < threadnumber; ++j) {
			unsigned long long start = countperthreadstart;
			countperthreadstart += countperthread;
			unsigned long long end = countperthreadstart;
			if (end > totalsize) {
				end = totalsize;
			}
			threads[j] = (std::thread(startthread, start, end));
			//threads[j]= std::thread(logrank_instance, groupas[j], groupacensoreds[j], groupbs[j], groupbcensoreds[j], j);
			//logrank_instance(groupas[j], groupacensoreds[j], groupbs[j], groupbcensoreds[j], j);
		}

		for (unsigned j = 0; j < threadnumber; ++j) {
			threads[j].join();
		}

		for (unsigned long long k = 0; k < pvalues.size(); ++k) {
			//std::cout<<std::setprecision(16) << pvalues[k] << std::endl;
			outfile << std::setprecision(16) << pvalues[k] << "\n";
		}

		std::cout << "Logrank time: " << std::time(nullptr) - logranktime << "s" << std::endl;


	}
	else {
		std::cout << "Unable to open file" << std::endl;
	}

	std::cout << "Whole time: " << std::time(nullptr) - wholetime << "s" << std::endl;
	infile.close();
	outfile.close();

}



int main(int argc, char* argv[]) {

	if (argc == 2) {
		std::string input = argv[1];
		unsigned position = 0;
		std::string seperator = "";
		for (unsigned k = 0; k < input.length(); ++k) {
			if (input[k] == '/') {
				position = k;
				seperator = "/";
			}
			else if (input[k] == '\\') {
				position = k;
				seperator = "\\";
			}
		}
		std::string output = input.substr(0, position) + seperator + "output.txt";
		cpu_parallel_logrank(input, output, std::thread::hardware_concurrency());
		std::cout << "Outpath: " << output << std::endl;
	}
	else if (argc == 3) {
		std::string input = argv[1];
		std::string output = argv[2];
		cpu_parallel_logrank(input, output, std::thread::hardware_concurrency());
	}
	else if (argc == 4) {
		std::string input = argv[1];
		std::string output = argv[2];
		cpu_parallel_logrank(input, output, std::stoi(argv[3]));
	}
	else {
		std::cout << "first argument: inputpath (required)\nsecond argument: outputpath (optional)\nthird argument: threadnumber (optional) (requires second argument)" << std::endl;
	}
	return 0;
}



