#solution to problem 2.3 for Computational Statistics Third Edition by Geof H. Givens and Jennifer A. Hoeting


library(numDeriv)
library(maxLik)

#2.3.b

#inputdata (both treatment and control)
T = c((6), 6, 6, 6, 7, (9), (10), 10, (11), 13, 16, (17), (19), (20), 22, 23, (25), (32), (32), (34), (35),1, 1, 2, 2, 3, 4, 4,5, 5, 8, 8, 8, 8, 11,11, 12, 12, 15, 17, 22, 23)
w = c(0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)
delta = c(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)


#log-likelihood
#p is alpha, beta_0 and beta_1
l = function(p){
  
  f = 0
  for(i in 1:length(T))
  {
    f = f + w[i]*log(T[i]^p[1]*exp(p[2]+delta[i]*p[3]))-T[i]^p[1]*exp(p[2]+delta[i]*p[3])+p[1]*w[i]*log(1/T[i])
  }
  return (f)
}

#newton
mvnewton <- function (f, p, n = 10000)
{
  
  for (i in 1:n) {
    old_p = p
   
    p = p - solve(hessian(func=l, x=p),grad(func=l, x=p)) 
    
    if ((dist(rbind(p, old_p)))/sqrt(sum(old_p^2)) < 1e-3) break
  }
  
  result = c(p,i)
  
  return (result)
}
#test Newton
init_p = c(-1,-1,-1)

#mle = mvnewton(f = l, p = init_p)


#2.3.c
#use a package instead of custom newton function for multimonial Newton MLE calculation


mle_c = maxLik(logLik = l, start = init_p)


#2.3.e

mle.gauss.seidel <- function (a,b,mu,debug=F)
{
  ss <- sufficient.statistics(a,b)
  
  gamma.a <- log ((ss$sum.a2 - 2*ss$sum.a*mu + ss$n.a*mu^2) / ss$n.a)
  gamma.b <- log ((ss$sum.b2 - 2*ss$sum.b*mu + ss$n.b*mu^2) / ss$n.b)
  
  converged <- F
  n <- 0
  
  while (!converged && n<100)
  {
    if (debug) cat(n,mu,gamma.a,gamma.b,"\n")
    
    old <- c(mu,gamma.a,gamma.b)
    
    mu <- (ss$sum.a/exp(gamma.a) + ss$sum.b/exp(gamma.b)) / 
      (ss$n.a/exp(gamma.a) + ss$n.b/exp(gamma.b))
    
    gamma.a <- log ((ss$sum.a2 - 2*ss$sum.a*mu + ss$n.a*mu^2) / ss$n.a)
    gamma.b <- log ((ss$sum.b2 - 2*ss$sum.b*mu + ss$n.b*mu^2) / ss$n.b)
    
    new <- c(mu,gamma.a,gamma.b)
    
    n <- n + 1
    
    converged <- all (abs(old-new) < 1e-12)
  }
  
  if (!converged) cat("WARNING: Convergence not observed\n")
  
  list (mu=mu, gamma.a=gamma.a, gamma.b=gamma.b, 
        log.likelihood = log.likelihood(ss,mu,gamma.a,gamma.b),
        cov = solve(-hessian(ss,mu,gamma.a,gamma.b)), n.iterations=n)
}



