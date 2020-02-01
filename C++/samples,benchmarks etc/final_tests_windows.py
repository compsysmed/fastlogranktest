from lifelines.statistics import logrank_test
import fast_logrank
import logrank_function
import fastlogranktest
import random
import time
import subprocess

indexstart = 0
indexend = 5
countoftestslist = [100000, 10000, 1000, 100, 10]
setsizelist = [100, 1000, 10000, 100000, 1000000]

for index in range(indexstart, indexend):
    time0 = time.time()
    t1s = []
    t2s = []
    e1s = []
    e2s = []
    referencepvalues = []
    pythonpvalues = []
    cythonpythonpvalues = []
    cythoncpppvalues = []
    cythonmulticpppvalues = []
    pythonerrors = 0
    cythonpythonerrors = 0
    cythoncpperrors = 0
    cythonmulticpperrors = 0
    cpperrors = 0
    countoftests = countoftestslist[index]
    setsize = setsizelist[index]
    minvalue = 0
    maxvalue = 10
    timelifelines = 0
    timepython = 0
    timecythonpython = 0
    timecythoncpp = 0
    timecythonmulticpp = 0
    timecpp = 0
    timewriteinput = 0
    survivalinformation = []
    censoredinformation = []
    inputvalues = []

    print("generate inputs")
    # generate survival times
    for i in range(setsize):
        value = random.uniform(minvalue, maxvalue)
        survivalinformation.append(value)
    # generate censored information
    for i in range(setsize):
        value = random.randint(0, 1)
        censoredinformation.append(value)
    # generate tests
    for i in range(countoftests):
        t1 = []
        e1 = []
        t2 = []
        e2 = []
        inputvalue = []
        for j in range(setsize):
            value = random.randint(1, 2)
            if value == 1:
                t1.append(survivalinformation[j])
                e1.append(censoredinformation[j])
            elif value == 2:
                t2.append(survivalinformation[j])
                e2.append(censoredinformation[j])
            inputvalue.append(value)
        t1s.append(t1)
        t2s.append(t2)
        e1s.append(e1)
        e2s.append(e2)
        inputvalues.append(inputvalue)

    print(str(time.time() - time0) + "s")
    print("write inputfile")
    # write inputfile
    time1 = time.time()
    input = open("Outputfiles/finalreferenceinput" + str(index) + ".txt", "w")
    for i in range(setsize):
        input.write(str(survivalinformation[i]))
        if i < (setsize - 1):
            input.write("\t")
    input.write("\n")
    for i in range(setsize):
        value = random.randint(0, 1)
        censoredinformation.append(value)
        input.write(str(censoredinformation[i]))
        if i < (setsize - 1):
            input.write("\t")
    input.write("\n")
    for i in range(countoftests):
        for j in range(setsize):
            input.write(str(inputvalues[i][j]))
            if j < (setsize - 1):
                input.write("\t")
        input.write("\n")
    input.close()
    timewriteinput = time.time() - time1

    print(str(timewriteinput) + "s")
    print("calculate with lifelines")
    # lifelines
    time1 = time.time()
    for i in range(countoftests):
        referencepvalues.append(logrank_test(t1s[i], t2s[i], e1s[i], e2s[i]).p_value)
    timelifelines = time.time() - time1

    print(str(timelifelines) + "s")
    print("write outputfile")
    # write output
    time1 = time.time()
    output = open("Outputfiles/finalreferenceoutput" + str(index) + ".txt", "w")
    for i in range(countoftests):
        output.write(str(referencepvalues[i]) + "\n")
    output.close()

    print(str(time.time() - time1) + "s")
    print("calculate with python")
    # python
    time1 = time.time()
    for i in range(countoftests):
        pythonpvalues.append(logrank_function.logrank_test1(t1s[i], t2s[i], e1s[i], e2s[i]))
    timepython = time.time() - time1

    print(str(timepython) + "s")
    print("calculate with cython(python)")
    # cytonpython
    time1 = time.time()
    for i in range(countoftests):
        cythonpythonpvalues.append(fast_logrank.logrank_test(t1s[i], t2s[i], e1s[i], e2s[i]))
    timecythonpython = time.time() - time1

    print(str(timecythonpython) + "s")
    print("calculate with cython(cpp)")
    # cytoncpp
    time1 = time.time()
    for i in range(countoftests):
        cythoncpppvalues.append(fastlogranktest.logrank_test(t1s[i], t2s[i], e1s[i], e2s[i]))
    timecythoncpp = time.time() - time1

    print(str(timecythoncpp) + "s")
    print("calculate with cython(cpp)(multithreaded)")
    # cythonmulticpp
    time1 = time.time()
    cythonmulticpppvalues = fastlogranktest.multi_logrank_test(t1s, t2s, e1s, e2s)
    timecythonmulticpp = time.time() - time1

    print(str(timecythonmulticpp) + "s")
    print("calculate with cpp(multithreaded)")
    # cpp
    time1 = time.time()
    processstring = "logrank_windows_v1.2.exe Outputfiles\\finalreferenceinput" + str(
        index) + ".txt Outputfiles\\cppoutput" + str(index) + ".txt"
    process = subprocess.run(processstring, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print(process.stdout.decode("utf-8"))
    print(process.stderr.decode("utf-8"))
    timecpp = time.time() - time1

    print("check everything")
    # checks
    for i in range(countoftests):
        if abs(referencepvalues[i] - pythonpvalues[i]) > 0.00000001:
            print(referencepvalues[i])
            print(pythonpvalues[i])
            pythonerrors += 1
        if abs(referencepvalues[i] - cythonpythonpvalues[i]) > 0.00000001:
            print(referencepvalues[i])
            print(cythonpythonpvalues[i])
            cythonpythonerrors += 1
        if abs(referencepvalues[i] - cythoncpppvalues[i]) > 0.00000001:
            print(referencepvalues[i])
            print(cythoncpppvalues[i])
            cythoncpperrors += 1
        if abs(referencepvalues[i] - cythonmulticpppvalues[i]) > 0.00000001:
            print(referencepvalues[i])
            print(cythonmulticpppvalues[i])
            cythonmulticpperrors += 1
    processfile = open("Outputfiles/cppoutput" + str(index) + ".txt", "r")
    referencefile = open("Outputfiles/finalreferenceoutput" + str(index) + ".txt", "r")
    value1 = processfile.readline()
    while value1 != "":
        value2 = referencefile.readline()
        # print(value2)
        if abs(float(value1) - float(value2)) > 0.00000001:
            cpperrors += 1
            print(value1)
            print(value2)
        value1 = processfile.readline()

    # write information
    errorfile = open("Outputfiles/errors" + str(index) + ".txt", "w")
    if (pythonerrors + cythonpythonerrors + cythoncpperrors + cythonmulticpperrors + cpperrors) == 0:
        print("0 errors occured\n")
        errorfile.write("0 errors occured")
    else:
        errorstr = "python: " + str(pythonerrors) + " errors\ncython(selfgenerated): " + str(
            cythonpythonerrors) + " errors\ncython(own cpp): " + str(
            cythoncpperrors) + " errors\ncython(multi cpp): " + str(cythonmulticpperrors) + " errors\ncpp: " + str(
            cpperrors) + " errors"
        print(errorstr)
        errorfile.write(errorstr)
    errorfile.close()
    timestr = "countoftests=" + str(countoftests) + "\nsetsize=" + str(setsize) + "\nlifelines.statistics: " + str(
        timelifelines) + "s\npython: " + str(timepython) + "s\ncython(selfgenerated): " + str(
        timecythonpython) + "s\ncython(own cpp): " + str(timecythoncpp) + "s\ncython(multi cpp): " + str(
        timecythonmulticpp) + "s\ncpp: " + str(timecpp) + "s\nWrite inputfile: " + str(
        timewriteinput) + "s\nWhole time: " + str(time.time() - time0) + "s"
    timefile = open("Outputfiles/times" + str(index) + ".txt", "w")
    timefile.write(timestr)
    timefile.close()
    print(timestr)
