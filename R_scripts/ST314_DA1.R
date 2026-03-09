# Shawn Singharaj

18/3+9^2
x <- 18 + 2
x * 3

# Question 1: Area of circle w/ r = 3
r <- 3
circle <- pi * r^2

# Question 2, mean()
# mean(x, trim, na.rm), Returns trimmed arithmetic mean of given values in parameter.
# Arguments: 
# x = R object, such as a vector c(0:10)
# trim = fraction 0:0.5 of observations to be trimmed from each end of x before mean
# is computed. Values outside are taken as nearest endpoint.
# na.rm = logical bool indicating whether NA values should be stripped before computation.

# Question 3: use sum()
y <- c(7, 8, 8, 10, 12)
sum_of_y <- sum(y)

# ex.
# Store the values of my first 7 quiz scores in the variable quizzes
quizzes <- c(90, 85, 88, 88, 92, 78, 100)
# Compute the average of my first 7 quiz scores
mean(quizzes)
# Calculate the minimum score I would need on the last quiz 
# to get an average of 90
(90*8)-sum(quizzes)