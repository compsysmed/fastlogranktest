from libcpp.vector cimport vector
cdef extern from "logrank_python.cpp":
    double logrank_instance(vector[double] groupa, vector[char] groupacensored, vector[double] groupb, vector[char] groupbcensored)
cdef extern from "logrank_python.cpp":
    vector[double] cpu_parallel_logrank(vector[vector[double]] groupas, vector[vector[char]] groupacensoreds, vector[vector[double]] groupbs, vector[vector[char]] groupbcensoreds)
cdef extern from "logrank_python.cpp":
    vector[double] cpu_parallel_logrank(vector[vector[double]] groupas, vector[vector[char]] groupacensoreds, vector[vector[double]] groupbs, vector[vector[char]] groupbcensoreds, unsigned threadnumber)