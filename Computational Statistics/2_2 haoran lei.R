#solution to problem 2.2 for Computational Statistics Third Edition by Geof H. Givens and Jennifer A. Hoeting
# =
# theta

library(pracma)

X =c(3.91, 4.85,
       2.28, 4.06, 3.70, 4.04, 5.46, 3.53, 2.28, 1.96, 2.53, 3.88, 2.22, 3.47, 4.82, 2.46, 2.99,
       2.54, 0.52, 2.50)

#2.2.a


  #log-likelihood function
l = function(theta){
  sum (log ((1-cos(X-theta))))
}

  #200 sithetalated data for the log-likelihood function
theta = seq(-pi,pi, length=200)
l.val = numeric(length(theta))
for(i in 1:length(theta)){
  l.val[i] = l(theta[i])
}

  #plot
# plot(theta, l.val, type="l",xlab = 'theta', ylab = 'log-likelyhood')
# abline(h=0, col="red")

#2.2.c
  #gradient function
g = function(theta){
  sum((1/(1-cos(X-theta))*sin(theta - X)))
}

# #plot gradient
# g.val = numeric(length(theta))
# for(i in 1:length(theta)){
#   g.val[i] = g(theta[i])
# }
# plot(theta, g.val, type="l",xlab = 'theta', ylab = 'gradient')
# abline(h=0, col="red")


  #calculate MLE using Newton¨CRaphson with different starting points
starting_points = c(0.0619, -2.7, 2.7)
MLE = rep(NA, length(starting_points))
n_iter_Newton = rep(NA, length(starting_points))
for (i in 1:length(starting_points))
{
  r = newton(g, starting_points[i], maxiter = 100000)
  MLE[i]=r[1]
  n_iter_Newton[i]= r[3]
}


#2.2.d

  #calculate MLE using Newton¨CRaphson with different starting points
starting_points_d = seq(from = -pi, to = pi, by = 2*pi/199)
# write.csv(r_object, file = filepath, row.names = FALSE)
#write.csv(starting_points_d,"C:/Users/Ben/Desktop/stat546/startingp.csv")
MLE = rep(NA, length(starting_points_d))
n_iter_Newton = rep(NA, length(starting_points_d))
for (i in 1:length(starting_points_d))
{
  r = newton(g, starting_points_d[i], maxiter = 100000)
  MLE[i]=r[1]
  n_iter_Newton[i]= r[3]
}
#write.csv(MLE,"C:/Users/Ben/Desktop/stat546/MLEs of -pi to pi.csv")


#2.2.e
#find the nearest two points that gives different convergence result
starting_points_e = seq(from = -2.5, to = -2.38, by = 0.002)
#write.csv(starting_points_e,"C:/Users/Ben/Desktop/stat546/starting_e.csv")
MLE_e = rep(NA, length(starting_points_e))
n_iter_Newton_e = rep(NA, length(starting_points_e))
for (i in 1:length(starting_points_e))
{
  r = newton(g, starting_points_e[i], maxiter = 100000)
  MLE_e[i]=r[1]
  n_iter_Newton_e[i]= r[3]
}
#write.csv(MLE_e,"C:/Users/Ben/Desktop/stat546/MLEs of e.csv")





