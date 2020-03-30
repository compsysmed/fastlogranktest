# distutils: language=c++
from .logrank_python cimport logrank_instance
from .logrank_python cimport cpu_parallel_logrank
from .logrank_python cimport cpu_parallel_logrank1
#import scipy.stats as sp
from libcpp.vector cimport vector

def logrank_test(vector[double] groupa, vector[double] groupb, vector[char] groupacensored, vector[char] groupbcensored, **kwargs):
    if "teststatistic" in kwargs:
        return logrank_instance(groupa, groupacensored, groupb, groupbcensored, kwargs.get("teststatistic"))
    else:
        return logrank_instance(groupa, groupacensored, groupb, groupbcensored)
    #return 1 - sp.chi2.cdf(logrank, df=1)
	
def multi_logrank_test(vector[vector[double]] groupas, vector[vector[double]] groupbs, vector[vector[char]] groupacensoreds, vector[vector[char]] groupbcensoreds, **kwargs):
    cdef vector[double] testvalues
    if "threadnumber" in kwargs:
        if "teststatistic" in kwargs:
            return cpu_parallel_logrank(groupas, groupacensoreds, groupbs, groupbcensoreds, kwargs.get("threadnumber"), kwargs.get("teststatistic"))
        else:
            return cpu_parallel_logrank(groupas, groupacensoreds, groupbs, groupbcensoreds, kwargs.get("threadnumber"), False)
    else:
        if "teststatistic" in kwargs:
            return cpu_parallel_logrank1(groupas, groupacensoreds, groupbs, groupbcensoreds, kwargs.get("teststatistic"))
        else:
            return cpu_parallel_logrank(groupas, groupacensoreds, groupbs, groupbcensoreds)
    #cdef vector[double] pvalues
    #cdef unsigned long long i
    #for i in range(testvalues.size()):
    #   pvalues.push_back(1 - sp.chi2.cdf(testvalues[i], df=1))
    #return pvalues