# Shawn Singharaj
# DA8

brand1 <- c(50,54,53,47,61,56,51,51,48,56,53,43,58,52,48)
brand2 <- c(57,61,47,52,53,57,56,53,67,58,62,56,56,62,57)

# summary
mean(brand1)
sd(brand1)
length(brand1)

mean(brand2)
sd(brand2)
length(brand2)

mean_difference <- mean(brand1) - mean(brand2)
std_error <- sqrt((sd(brand1)^2 / length(brand1)) + 
                    (sd(brand2)^2 / length(brand2)))                
                  
# Sattherwhaite DF = 27.944

# 90% interval calculation
crit <- qt(0.95, 27.944)

lower <- mean_difference - crit * std_error
upper <- mean_difference + crit * std_error
# (-7.803, -1.930)

# p value
t_statistic <- mean_difference / std_error
p_value <- 2 * (1 - pt(abs(t_statistic), 27.944))

# Part 2
p_value_f <- 1-pf(2.189, 4, 1167)
