from libcpp.vector cimport vector
from libcpp cimport bool
cdef extern from "logrank_python.cpp":
    double logrank_instance(vector[double] groupa, vector[char] groupacensored, vector[double] groupb, vector[char] groupbcensored)
cdef extern from "logrank_python.cpp":
    double logrank_instance(vector[double] groupa, vector[char] groupacensored, vector[double] groupb, vector[char] groupbcensored, bool teststatistic)
cdef extern from "logrank_python.cpp":
    vector[double] cpu_parallel_logrank(vector[vector[double]] groupas, vector[vector[char]] groupacensoreds, vector[vector[double]] groupbs, vector[vector[char]] groupbcensoreds)
cdef extern from "logrank_python.cpp":
    vector[double] cpu_parallel_logrank(vector[vector[double]] groupas, vector[vector[char]] groupacensoreds, vector[vector[double]] groupbs, vector[vector[char]] groupbcensoreds, unsigned threadnumber)
cdef extern from "logrank_python.cpp":
    vector[double] cpu_parallel_logrank1(vector[vector[double]] groupas, vector[vector[char]] groupacensoreds, vector[vector[double]] groupbs, vector[vector[char]] groupbcensoreds, bool teststatistic)
cdef extern from "logrank_python.cpp":
    vector[double] cpu_parallel_logrank(vector[vector[double]] groupas, vector[vector[char]] groupacensoreds, vector[vector[double]] groupbs, vector[vector[char]] groupbcensoreds, unsigned threadnumber, bool teststatistic)