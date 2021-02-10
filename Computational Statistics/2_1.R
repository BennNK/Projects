#solution to problem 2.1 for Computational Statistics Third Edition by Geof H. Givens and Jennifer A. Hoeting


library(pracma)

#problem 2.1.a
X = c(1.77, -0.23,
      2.76, 3.80, 3.47, 56.75, -1.34, 4.24, - 2.44, 3.29, 3.71, - 2.40, 4.53, - 0.07, -1.05,
      -13.87, - 2.53, - 1.75, 0.27, 43.21)
# log-likelihood
g <- function(mu){
  - sum (log(1+(X-mu)^2))
}

#generate 200 data points of function g 
mu <- seq(min(X)+qt(0.1, df=1), max(X)+qt(0.9, df=1), length=200)
g.val <- numeric(length(mu))
for(i in 1:length(mu)){
  g.val[i] <- g(mu[i])
}

#plot the log-likelyhood
#plot(mu, g.val, type="l",ylab = 'log-likelyhood')
#abline(h=0, col="red")


#gradient, which is the derivative of loglikelihood function
f = function(mu){
  2*sum((1/(1+(X-mu)^2))*(X-mu))
}

#plot gradient
# f.val <- numeric(length(mu))
# for(i in 1:length(mu)){
#   f.val[i] <- f(mu[i])
# }
# 
# plot(mu, f.val, type="l", ylab = 'gradient')
# abline(h=0, col="red")

#calculate MLE using Newton¨CRaphson with different starting points
starting_points = c(-11,- 1, 0, 1.5, 4, 4.7, 7, 8, 38)
MLE = rep(NA, length(starting_points))
n_iter_Newton = rep(NA, length(starting_points))
for (i in 1:length(starting_points))
{
  r = newton(f, starting_points[i], maxiter = 100000)
  MLE[i]=r[1]
  n_iter_Newton[i]= r[3]
}


#try using the mean of X as the starting point of Newton¨CRaphson
m = mean(X)
r = newton(f, m, maxiter = 100000)


#problem 2.1.b

my.bisection <- function(interval, g, max.iter = 100000){
  # interval: [a_0, b_0], g: the score function
  # if (....) stop("invalid arguments...")
  fn.val <- c(g(interval[1]), g(interval[2]))
  
  if( fn.val[1] * fn.val[2] > 0) stop("invalid argument")
  
  for(t in 0:max.iter){
    m <-  (interval[1] + interval[2])/2 # mean(interval)
    fn.m <- g(m)
    if(fn.val[1]*fn.m <= 0){
      interval[2] <- m
      fn.val[2] <- fn.m
    } else { # fn.val[2]*fn.m <= 0
      interval[1] <- m
      fn.val[1] <- fn.m
    }
    
    abline(h=0, col=2, lwd=3)
    lines(interval, rep(0, 2), col="blue", lwd=3)
    
    cat("[", t, "]", "interval:", interval, "\n")
    Sys.sleep(2)
    abline(h=0, col=0, lwd=3)
    Sys.sleep(0.1)
  }
}

#uncomment the below line if you want to run the bisection function. Or else it will take too long for the bisection function to run.
#my.bisection(c(-1, 1), g=f, max.iter = 1000)

#try some other starting points
# starting with [min(X)+qt(0.1, df=1), max(X)+qt(0.9, df=1)] interval
#uncomment the below line if you want to run the bisection function. Or else it will take too long for the bisection function to run.
#my.bisection(c(min(X)+qt(0.1, df=1), max(X)+qt(0.9, df=1)), g=f, max.iter = 1000)

# starting with [-1,3] interval
#uncomment the below line if you want to run the bisection function. Or else it will take too long for the bisection function to run.
#my.bisection(c(-1,2), g=f, max.iter = 1000)


# starting with [20,60] interval
#uncomment the below line if you want to run the bisection function. Or else it will take too long for the bisection function to run.
#my.bisection(c(20,42.7), g=f, max.iter = 1000)


#problem 2.1.c
#use fixed-point method

my.fixed_point <- function(x0, g, alpha, max.iter = 100000){
  
  x = x0
  #update x using g (the derivative function of the loglikelihood function) and scaling factor alpha
  for(t in 1:max.iter){
    prev = x
    x = alpha*g(x)+x
    #if accuracy meets the requirement then conclude that a convergence is met and the iterations should stop
    if( abs((prev - x)/x) < 1e-3) break
    
  }
  result=c(x,t)
  
  return(result)
}

#check how starting point (x0) and alpha parameter affects the convergence speed and correctness of fixed point method
starting_points_fp = c(-10,-1,0,1,20,50)
scaling_factors = c(1,0.64,0.25)
for(i in 1:length(starting_points_fp))
{
  for(j in 1:length(scaling_factors))
  {
    MLE_from_fixed_point = my.fixed_point(starting_points_fp[i],g=f, alpha=scaling_factors[j])
    print(paste("starting point is", starting_points_fp[i], ", scaling factor is", scaling_factors[j], ", converged at", MLE_from_fixed_point[1],", number of iterations is", MLE_from_fixed_point[2]), quote = FALSE)
  }
}

#problem 2.1.d
# check how starting interval affects secant method
# intervals are as follows
left = c(-1, min(X)+qt(0.1, df=1), -3, 20)
right = c(1, max(X)+qt(0.9, df=1),  3, 60)

for (i in 1:length(left))
{
  result_secant = secant(f, left[i], right[i])
  print(paste("secant starting interval is(", left[i], ",", right[i],"), MLE is", result_secant[1], ", number of iteration is", result_secant[3]))
  
}





#plot(n_ite, log_liks, type = 'l',main = 'log-likelyhood vs number of iterations',xlab = 'number of iterations', ylab = 'log-likelyhood')