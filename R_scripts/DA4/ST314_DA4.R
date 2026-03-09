# Shawn Singharaj
# DA4


# PART 1
# Simulate exponential distribution
sim_exp <- rexp(n = 60, rate = 1/3)
df <- data.frame(sim_exp)

# Histogram for sim_exp
ggplot(df, aes(sim_exp)) + 
  geom_histogram(bins = 60, fill = "blue", color = "black") +
  labs(x = "Continuous Rainfall (in hrs)", y = "Frequency",
       title = "Corvallis Rainfall Duration in January")
mean(sim_exp)

# What is the probability that a randomly chosen rainfall event in Corvallis in January is longer than 4 hours
# Theoretical prob
1-pexp(q = 3.5, rate = 1/3)

# empirical prob
df |>
  filter(sim_exp > 3.5) |>
  summarise(proportion = n()/nrow(df))


# PART 2
library(openintro)
data(births14)

# mage histrogram
ggplot(births14, aes(x = mage)) + 
  geom_histogram(bins = 10, fill = "blue", color = "black") +
  labs(x = "Mother's Age", y = "Frequency",
       title = "Distitbution of Mother's Age of 1,000 Newborns in NC, 2014")

# fage histrogram
ggplot(births14, aes(x = fage)) + 
  geom_histogram(bins = 10, fill = "blue", color = "black") +
  labs(x = "Father's Age", y = "Frequency",
       title = "Distitbution of Father's Age of 1,000 Newborns in NC, 2014")

mage_mean <- mean(births14$mage)
mage_sd <- sd(births14$mage)

# Density histogram of mage
ggplot(births14, aes(x = mage)) + 
  geom_histogram(aes(y = after_stat(density)), 
                 bins = 20, color = "black", fill = "lightyellow") + 
  stat_function(fun = dnorm, args = c(mean = mage_mean, sd = mage_sd), 
                col = "tomato", linewidth = 1)

fage_mean <- mean(births14$fage, na.rm = TRUE)
fage_sd <- sd(births14$fage, na.rm = TRUE)

# Density histogram of mage
ggplot(births14, aes(x = fage)) + 
  geom_histogram(aes(y = after_stat(density)), 
                 bins = 20, color = "black", fill = "lightyellow") + 
  stat_function(fun = dnorm, args = c(mean = fage_mean, sd = fage_sd), 
                col = "tomato", linewidth = 1)

# What is the probability that a randomly selected mother of a newborn in North Carolina in 2014 is older than 30 years old?
1 - pnorm(30, mage_mean, mage_sd)
# Calculate empirically
births14 |>
  filter(mage > 30) |>
  summarise(percent = n() / nrow(births14))

# What is the probability that a randomly selected mother in NC, 2014, is younger than 20?
# Theoretical:
pnorm(20, mage_mean, mage_sd)
# Empirically:
births14 |>
  filter(mage < 20) |>
  summarise(percent = n() / nrow(births14))

