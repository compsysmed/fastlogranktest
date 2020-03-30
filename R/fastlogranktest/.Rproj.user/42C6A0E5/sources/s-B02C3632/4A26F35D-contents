#' Calculate the Log-Rank-Test very fast
#' @param groupa vector of group a's survival times
#' @param groupb vector of group b's survival times
#' @param groupacensored vector of censored information of group a's survival times
#' @param groupbcensored vector of censored information of group b's survival times
#' @param teststatistic (optional) if true, you get the test-statistic value instead of p-value
#' @return p-value
#' @examples
#' T1 <- c(6, 6, 6, 6, 7, 9, 10, 10, 11, 13, 16, 17, 19, 20, 22, 23, 25, 32, 32, 34, 35)
#' E1 <- c(1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0)
#' T2 <- c(1, 1, 2, 2, 3, 4, 4, 5, 5, 8, 8, 8, 8, 11, 11, 12, 12, 15, 17, 22, 23)
#' E2 <- c(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)
#' logrank_test(T1, T2, E1, E2)
#' #4.168809e-05
#' logrank_test(T1, T2, E1, E2, teststatistic = TRUE)
#' #16.79294
#' @export
#' @import Rcpp
#' @useDynLib fastlogranktest, .registration = TRUE
logrank_test <- function(groupa, groupb, groupacensored, groupbcensored, teststatistic=NULL){
  if(is.null(teststatistic)||teststatistic==FALSE){
    logrank_instance(groupa, groupb, groupacensored, groupbcensored, FALSE)
  }
  else{
    logrank_instance(groupa, groupb, groupacensored, groupbcensored, TRUE)
  }
}
#' Calculate multiple Log-Rank-Tests very fast
#' @param groupas list of vectors of groupa's survival times
#' @param groupbs list of vectors of groupb's survival times
#' @param groupacensoreds list of vectors of censored information of groupa's survival times
#' @param groupbcensoreds list of vectors of censored information of groupb's survival times
#' @param teststatistic (optional) if true, you get the test-statistic values instead of p-value
#' @param threadnumber (optional) set the number of threads used for this function
#' @return vector of p-values (same order as input)
#' @examples
#' T1 <- c(6, 6, 6, 6, 7, 9, 10, 10, 11, 13, 16, 17, 19, 20, 22, 23, 25, 32, 32, 34, 35)
#' E1 <- c(1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0)
#' T2 <- c(1, 1, 2, 2, 3, 4, 4, 5, 5, 8, 8, 8, 8, 11, 11, 12, 12, 15, 17, 22, 23)
#' E2 <- c(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)
#' t1s<-list(T1, T1, T1)
#' e1s<-list(E1, E1, E1)
#' t2s<-list(T2, T2, T2)
#' e2s<-list(E2, E2, E2)
#' multi_logrank_test(t1s, t2s, e1s, e2s)
#' #4.168809e-05 4.168809e-05 4.168809e-05
#' multi_logrank_test(t1s, t2s, e1s, e2s, teststatistic = TRUE)
#' #16.79294 16.79294 16.79294
#' @export
#' @import Rcpp
#' @useDynLib fastlogranktest, .registration = TRUE
multi_logrank_test <- function(groupas, groupbs, groupacensoreds, groupbcensoreds, threadnumber=NULL, teststatistic=NULL){
  if(is.null(threadnumber)){
    if(is.null(teststatistic)||teststatistic==FALSE){
      cpu_parallel_logrank(groupas, groupbs, groupacensoreds, groupbcensoreds, FALSE)
    }
    else{
      cpu_parallel_logrank(groupas, groupbs, groupacensoreds, groupbcensoreds, TRUE)
    }
  }
  else{
    if(is.null(teststatistic)||teststatistic==FALSE){
      cpu_parallel_logrank1(groupas, groupbs, groupacensoreds, groupbcensoreds, threadnumber, FALSE)
    }
    else{
      cpu_parallel_logrank1(groupas, groupbs, groupacensoreds, groupbcensoreds, threadnumber, TRUE)
    }
  }
}
