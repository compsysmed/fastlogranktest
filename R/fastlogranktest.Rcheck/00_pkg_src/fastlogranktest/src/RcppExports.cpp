// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// logrank_instance
std::vector<double> logrank_instance(std::vector<double>& groupa, std::vector<double>& groupb, std::vector<int>& groupacensored, std::vector<int>& groupbcensored);
RcppExport SEXP _fastlogranktest_logrank_instance(SEXP groupaSEXP, SEXP groupbSEXP, SEXP groupacensoredSEXP, SEXP groupbcensoredSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double>& >::type groupa(groupaSEXP);
    Rcpp::traits::input_parameter< std::vector<double>& >::type groupb(groupbSEXP);
    Rcpp::traits::input_parameter< std::vector<int>& >::type groupacensored(groupacensoredSEXP);
    Rcpp::traits::input_parameter< std::vector<int>& >::type groupbcensored(groupbcensoredSEXP);
    rcpp_result_gen = Rcpp::wrap(logrank_instance(groupa, groupb, groupacensored, groupbcensored));
    return rcpp_result_gen;
END_RCPP
}
// cpu_parallel_logrank1
std::vector<std::vector<double>> cpu_parallel_logrank1(std::vector<std::vector<double>>& groupas_, std::vector<std::vector<double>>& groupbs_, std::vector<std::vector<int>>& groupacensoreds_, std::vector<std::vector<int>>& groupbcensoreds_, unsigned threadnumber);
RcppExport SEXP _fastlogranktest_cpu_parallel_logrank1(SEXP groupas_SEXP, SEXP groupbs_SEXP, SEXP groupacensoreds_SEXP, SEXP groupbcensoreds_SEXP, SEXP threadnumberSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<std::vector<double>>& >::type groupas_(groupas_SEXP);
    Rcpp::traits::input_parameter< std::vector<std::vector<double>>& >::type groupbs_(groupbs_SEXP);
    Rcpp::traits::input_parameter< std::vector<std::vector<int>>& >::type groupacensoreds_(groupacensoreds_SEXP);
    Rcpp::traits::input_parameter< std::vector<std::vector<int>>& >::type groupbcensoreds_(groupbcensoreds_SEXP);
    Rcpp::traits::input_parameter< unsigned >::type threadnumber(threadnumberSEXP);
    rcpp_result_gen = Rcpp::wrap(cpu_parallel_logrank1(groupas_, groupbs_, groupacensoreds_, groupbcensoreds_, threadnumber));
    return rcpp_result_gen;
END_RCPP
}
// cpu_parallel_logrank
std::vector<std::vector<double>> cpu_parallel_logrank(std::vector<std::vector<double>>& groupas, std::vector<std::vector<double>>& groupbs, std::vector<std::vector<int>>& groupacensoreds, std::vector<std::vector<int>>& groupbcensoreds);
RcppExport SEXP _fastlogranktest_cpu_parallel_logrank(SEXP groupasSEXP, SEXP groupbsSEXP, SEXP groupacensoredsSEXP, SEXP groupbcensoredsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<std::vector<double>>& >::type groupas(groupasSEXP);
    Rcpp::traits::input_parameter< std::vector<std::vector<double>>& >::type groupbs(groupbsSEXP);
    Rcpp::traits::input_parameter< std::vector<std::vector<int>>& >::type groupacensoreds(groupacensoredsSEXP);
    Rcpp::traits::input_parameter< std::vector<std::vector<int>>& >::type groupbcensoreds(groupbcensoredsSEXP);
    rcpp_result_gen = Rcpp::wrap(cpu_parallel_logrank(groupas, groupbs, groupacensoreds, groupbcensoreds));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_fastlogranktest_logrank_instance", (DL_FUNC) &_fastlogranktest_logrank_instance, 4},
    {"_fastlogranktest_cpu_parallel_logrank1", (DL_FUNC) &_fastlogranktest_cpu_parallel_logrank1, 5},
    {"_fastlogranktest_cpu_parallel_logrank", (DL_FUNC) &_fastlogranktest_cpu_parallel_logrank, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_fastlogranktest(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}