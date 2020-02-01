# distutils: language=c++

import scipy.stats as sp
from libcpp.vector cimport vector
from libcpp.pair cimport pair
from libcpp.algorithm cimport sort
from libcpp cimport bool

cdef bool compareFunction(pair[double, char] a, pair[double, char] b):
    return a.first < b.first

def logrank_test(vector[double] groupa, vector[double] groupb, vector[char] groupacensored, vector[char] groupbcensored):
    cdef unsigned long long i
    cdef vector[pair[double, char]] groupaboth
    for i in range(groupa.size()):
        groupaboth.push_back((groupa[i], groupacensored[i]))
    cdef vector[pair[double, char]] groupbboth
    for i in range(groupb.size()):
        groupbboth.push_back((groupb[i], groupbcensored[i]))
    sort(groupaboth.begin(), groupaboth.end(), compareFunction)
    sort(groupbboth.begin(), groupbboth.end(), compareFunction)
    cdef unsigned long long na = groupaboth.size()
    cdef unsigned long long nb = groupbboth.size()
    cdef unsigned long long nasize = na
    cdef unsigned long long nbsize = nb
    cdef unsigned long long n = na + nb
    cdef long double oa = 0.0
    cdef long double ea = 0.0
    # cdef long double ob=0.0
    # cdef long double eb=0.0
    cdef long double var = 0.0
    cdef unsigned long long indexa = 0
    cdef unsigned long long indexb = 0
    cdef double value
    cdef unsigned long long count
    cdef unsigned long long countb
    cdef unsigned long long minusna
    cdef unsigned long long minusnb
    while na > 0 and nb > 0:
        value = groupaboth[indexa].first
        count = 0
        countb = 0
        minusna = 0
        minusnb = 0
        if indexb < nbsize and groupbboth[indexb].first < value:
            minusnb += 1
            value = groupbboth[indexb].first
            if groupbboth[indexb].second == 1:
                countb += 1
            indexb += 1
            while indexb < nbsize and value == groupbboth[indexb].first:
                if groupbboth[indexb].second == 1:
                    countb += 1
                indexb += 1
                minusnb += 1
        elif indexb < nbsize and groupbboth[indexb].first == value:
            minusna += 1
            if groupaboth[indexa].second == 1:
                count += 1
            indexa += 1
            while indexa < nasize and value == groupaboth[indexa].first:
                if groupaboth[indexa].second == 1:
                    count += 1
                indexa += 1
                minusna += 1
            while indexb < nbsize and value == groupbboth[indexb].first:
                if groupbboth[indexb].second == 1:
                    countb += 1
                indexb += 1
                minusnb += 1
        else:
            minusna += 1
            if indexa < nasize and groupaboth[indexa].second == 1:
                count += 1
            indexa += 1
            while indexa < nasize and value == groupaboth[indexa].first:
                if groupaboth[indexa].second == 1:
                    count += 1
                indexa += 1
                minusna += 1
        ea += <long double>(na * (count + countb)) / <long double>(n)
        # eb+=(float(nb)*(float((count+countb))/float(n)))
        # ob+=countb
        oa += count
        var += (<long double>(na) * <long double>(nb * (count + countb)) * <long double>(n - (count + countb))) / (<long double>(n) * <long double>(n) * <long double>(n - 1))
        na -= minusna
        nb -= minusnb
        n = na + nb
    cdef long double logrank = ((oa - ea) * (oa - ea)) / var
    return (1 - sp.chi2.cdf(logrank, df=1))