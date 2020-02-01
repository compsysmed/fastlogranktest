#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
test_fastlogranktest
----------------------------------

Tests for `fastlogranktest` module.
"""

import fastlogranktest
import logrank_function
import random

t1s = []
t2s = []
e1s = []
e2s = []
inputstring = ""
referencepvalues = []
cythoncpppvalues = []
cythonmulticpppvalues = []
cythoncpperrors = 0
cythonmulticpperrors = 0
countoftests = 1000
setsize = 1000
minvalue = 0
maxvalue = 100
survivalinformation = []
censoredinformation = []

print("generate inputs")
# generate survival times
for i in range(setsize):
    value = random.uniform(minvalue, maxvalue)
    survivalinformation.append(value)
    inputstring += (str(value))
    if i < (setsize - 1):
        inputstring += ("\t")
inputstring += ("\n")
# generate censored information
for i in range(setsize):
    value = random.randint(0, 1)
    censoredinformation.append(value)
    inputstring += (str(value))
    if i < (setsize - 1):
        inputstring += ("\t")
inputstring += ("\n")
# generate tests
for i in range(countoftests):
    t1 = []
    e1 = []
    t2 = []
    e2 = []
    for j in range(setsize):
        value = random.randint(1, 2)
        if value == 1:
            t1.append(survivalinformation[j])
            e1.append(censoredinformation[j])
        elif value == 2:
            t2.append(survivalinformation[j])
            e2.append(censoredinformation[j])
        inputstring += (str(value))
        if j < (setsize - 1):
            inputstring += ("\t")
    t1s.append(t1)
    t2s.append(t2)
    e1s.append(e1)
    e2s.append(e2)
    inputstring += ("\n")

print("calculate with python")
# python
for i in range(countoftests):
    referencepvalues.append(logrank_function.logrank_test(t1s[i], t2s[i], e1s[i], e2s[i]))

print("calculate with cython(cpp)")
# cytoncpp
for i in range(countoftests):
    cythoncpppvalues.append(fastlogranktest.logrank_test(t1s[i], t2s[i], e1s[i], e2s[i]))

print("calculate with cython(cpp)(multithreaded)")
# cythonmulticpp
cythonmulticpppvalues = fastlogranktest.multi_logrank_test(t1s, t2s, e1s, e2s)

print("check everything\n")
# checks
for i in range(countoftests):
    if abs(referencepvalues[i] - cythoncpppvalues[i]) > 0.00000001:
        print(referencepvalues[i])
        print(cythoncpppvalues[i])
        cythoncpperrors += 1
    if abs(referencepvalues[i] - cythonmulticpppvalues[i]) > 0.00000001:
        print(referencepvalues[i])
        print(cythonmulticpppvalues[i])
        cythonmulticpperrors += 1

if (cythoncpperrors + cythonmulticpperrors) == 0:
    print("0 errors occured")
else:
    errorstr = "cython(own cpp): " + str(cythoncpperrors) + " errors\ncython(multi cpp): " + str(
        cythonmulticpperrors) + " errors"
    print(errorstr)
    exit(-1)
