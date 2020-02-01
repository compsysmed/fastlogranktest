import scipy.stats as sp

def logrank_test(groupa, groupb, groupacensored, groupbcensored):
    groupaboth = []
    for i in range(len(groupa)):
        groupaboth.append((groupa[i], groupacensored[i]))
    groupbboth = []
    for i in range(len(groupb)):
        groupbboth.append((groupb[i], groupbcensored[i]))
    groupaboth.sort()
    groupbboth.sort()
    na = len(groupaboth)
    nb = len(groupbboth)
    nasize = na
    nbsize = nb
    n = na + nb
    oa = 0.0
    ea = 0.0
    # ob=0.0
    # eb=0.0
    var = 0.0
    indexa = 0
    indexb = 0
    while na > 0 and nb > 0:
        value = groupaboth[indexa][0]
        count = 0
        countb = 0
        minusna = 0
        minusnb = 0
        if indexb < nbsize and groupbboth[indexb][0] < value:
            minusnb += 1
            value = groupbboth[indexb][0]
            if groupbboth[indexb][1] == 1:
                countb += 1
            indexb += 1
            while indexb < nbsize and value == groupbboth[indexb][0]:
                if groupbboth[indexb][1] == 1:
                    countb += 1
                indexb += 1
                minusnb += 1
        elif indexb < nbsize and groupbboth[indexb][0] == value:
            minusna += 1
            if groupaboth[indexa][1] == 1:
                count += 1
            indexa += 1
            while indexa < nasize and value == groupaboth[indexa][0]:
                if groupaboth[indexa][1] == 1:
                    count += 1
                indexa += 1
                minusna += 1
            while indexb < nbsize and value == groupbboth[indexb][0]:
                if groupbboth[indexb][1] == 1:
                    countb += 1
                indexb += 1
                minusnb += 1
        else:
            minusna += 1
            if indexa < nasize and groupaboth[indexa][1] == 1:
                count += 1
            indexa += 1
            while indexa < nasize and value == groupaboth[indexa][0]:
                if groupaboth[indexa][1] == 1:
                    count += 1
                indexa += 1
                minusna += 1
        ea += (float(na) * (float((count + countb)) / float(n)))
        # eb+=(float(nb)*(float((count+countb))/float(n)))
        # ob+=countb
        oa += count
        var += float((na * nb * (count + countb) * (n - (count + countb)))) / float((n * n * (n - 1)))
        na -= minusna
        nb -= minusnb
        n = na + nb
    logrank = ((oa - ea) * (oa - ea)) / var
    pvalue = 1 - sp.chi2.cdf(logrank, df=1)
    return pvalue
