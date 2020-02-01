===============================
fastlogranktest
===============================

Perform the Log-Rank-Test very fast

* Free software: BSD license


Description
-----------
Calculate the Log-Rank-Test very fast

Installation
------------
pip install fastlogranktest

(if it fails, make sure python-dev is installed and try the installation again.

linux: sudo apt-get install python-dev)

Usage
--------
logrank_test(groupa, groupb, groupacensored, groupbcensored)

Arguments
---------
groupa:	
list of group a's survival times

groupb:	
list of group b's survival times

groupacensored:	
list of censored information of group a's survival times

groupbcensored:	
list of censored information of group b's survival times

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
list of lists of groupa's survival times

groupbs:	
list of lists of groupb's survival times

groupacensoreds:	
list of lists of censored information of groupa's survival times

groupbcensoreds:	
list of lists of censored information of groupb's survival times

threadnumber:	
(optional) set the number of threads used for this function

Value
--------
list of p-values (same order as input)