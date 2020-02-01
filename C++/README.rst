===============================
fastlogranktest
===============================

Perform the Log-Rank-Test very fast

* Free software: BSD license


Description
-----------
Calculate the Log-Rank-Test very fast on a Inputfile.


Fileformat Input
----------------
First line: different survival times (doubles possible), tab seperated

Second line: censored information (just 0 or 1), tab seperated

All other lines:

Every line is one test. Values from 0 to 2:

* 0 means the value at this index from the first line (and from the second line) isn't part of a group so it will be ignored

* 1 means part of the first group

* 2 means part of the second group. Values are tab seperated

(sample Inputfiles with the right Outputiles can be found in "/samples,benchmarks etc/Outputfiles/"


Usage
--------
(if the compiled versions don't work for your system you can compile the logrank_v1.2.cpp yourself)

:Windows:

PATH_TO_EXE_DIRECTORY\\logrank_windows_v1.2.exe


:Linux:

PATH_TO_PROGRAMM_DIRECTORY/logrank_linux_v1.2

if you already navigated to the containing folder:

./logrank_linux_v1.2

(make sure that you set the permissions of "logrank_linux_v1.2" as executable)


Arguments
---------
* First argument: path to inputfile (required)

* Second argument: path to outputfile (optional)(if not set will create a output.txt in same directory where inputfile is)

* Third argument: number of threads (optional)(is only setable if second argument is given)


Fileformat Output
-----------------
Lists every pvalue in a new line in the same order as the Inputfile