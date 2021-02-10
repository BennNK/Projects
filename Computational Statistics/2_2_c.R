
X <-c(3.91,4.85,2.28,4.06,3.7,4.0,5.56,3.53,2.28,1.96,2.54,3.88,2.22,3.47,4.82,2.46,2.99,2.54,0.52,2.5)
mu<-mean(X)



l<-function(mu){sum (log ((1-cos(X-mu))))}
g <- function(mu){
  sum((1/(1-cos(X-mu))*sin(X-mu)))
}
g.prime<-function(mu){
  sum(sin(x-mu)/(cos(x-mu)-1))
}


mu <- seq(-pi,pi, length=200)
g.val <- numeric(length(mu))
for(i in 1:length(mu)){
  g.val[i] <- l(mu[i])
}
#g gradient,test mu
plot(mu, g.val, type="l")
abline(h=0, col="red")

theta=0.06194696

my.newton <-function(x,g,itr=100000)
{
 
   g.prime <- function(mu){
    sum((1/(1-cos(X-mu))*sin(X-mu)))
  }
  g.2prime<-function(mu){
    sum(sin(x-mu)/(cos(x-mu)-1))
  }
  
  
  
  ## MAIN
  for(i in 1:itr)
  {x = x - g.prime(x)/g.2prime(x)
  }
  return(x)
  
}
mu=my.newton(x=1,g=g,itr=100000)
mu
mu=my.newton(x=-2.7,g=g,itr=100000)
mu
mu=my.newton(x=2.7,g=g,itr=100000)
mu
mu=my.newton(x=1,g=g,itr=100000)
mu
mu=my.newton(x=1.5,g=g,itr=100000)
mu
mu=my.newton(x=4,g=g,itr=100000)
mu
mu=my.newton(x=4.7,g=g,itr=100000)
mu
mu=my.newton(x=7,g=g,itr=100000)
mu
mu=my.newton(x=8.44,g=g,itr=100000)
mu
mu=my.newton(x=38,g=g,itr=100000)
mu



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
    # cat("[", t, "]", "interval:", interval, "\n")
    
    
  }
  return(m)
}

my.bisection(c(-0.5,0.5), g=g,
             max.iter = 100000)



## MAIN
my.fixp<-function(x,alpha,itr=100000,g)
{
  for(i in 1:itr)
  {x = alpha*g(x) + x}
  return(x)}
my.fixp(x=-1,alpha=1,itr=10000,g=g)
my.fixp(x=-1,alpha=0.64,itr=10000,g=g)
my.fixp(x=-1,alpha=0.25,itr=10000,g=g)


my.sec<-function(mu0,mu1,itr=100,g)
{
  
  #cat("interval:", mu0, "\n")
  for(i in 1:itr)
  {x=mu1-g(mu1)*(mu1-mu0)/(g(mu1)-g(mu0))
  
  mu0=mu1
  mu1=x
  if(g(mu1)==g(mu0)){break}
  #cat("interval:", mu0, "\n")
  }
  return(mu1)
}
my.sec(-2,-1,itr=100,g=g)
my.sec(-3,3,itr=100000,g=g)
my.sec(-3,1,itr=100000,g=g)
my.sec(-3,20,itr=100000,g=g)


