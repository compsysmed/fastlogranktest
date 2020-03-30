===============================
fastlogranktest
===============================

Perform the Log-Rank-Test very fast

* Free software: GPL-3 license


Description
-----------
Calculate the Log-Rank-Test very fast

Usage
--------
logrank_test(groupa, groupb, groupacensored, groupbcensored)

Arguments
---------
groupa:
vector of group a's survival times

groupb:
vector of group b's survival times

groupacensored:
vector of censored information of group a's survival times

groupbcensored:
vector of censored information of group b's survival times

teststatistic:
(optional) if true, you get the test-statistic value instead of p-value

Value
--------
p-value

Description
------------
Calculate multiple Log-Rank-Tests very fast using threading

Usage
--------
multi_logrank_test(groupas, groupbs, groupacensoreds, groupbcensoreds, threadnumber = NULL)

Arguments
---------
groupas:
list of vectors of groupa's survival times

groupbs:
list of vectors of groupb's survival times

groupacensoreds:
list of vectors of censored information of groupa's survival times

groupbcensoreds:
list of vectors of censored information of groupb's survival times

teststatistic:
(optional) if true, you get the test-statistic values instead of p-value

threadnumber:
(optional) set the number of threads used for this function

Value
--------
vector of p-values (same order as input)
