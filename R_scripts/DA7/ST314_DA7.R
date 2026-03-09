# Shawn Singharaj
# DA7

# Is average caffeine consumption among women greater than 200 mg?
# alpha = 0.05

caffeine <- read_csv(file.choose())

ggplot(caffeine, aes(x = consumption)) + 
  geom_boxplot() +
  labs(x = "Caffeine Consumption (mg)", 
       title = "Distribution of Caffeine Consumption Sample, Females 18+") + 
  theme(axis.text.y = element_blank(), 
        axis.ticks.y = element_blank())

sample_mean <- mean(caffeine$consumption)
sample_sd <- sd(caffeine$consumption)

# p value to the right of
caffeine_p <- 1 - pt(1.03, 46)

t.test(caffeine$consumption, mu=200, alternative="greater", conf.level=1-0.05)

# Part 2
population <- read_csv(file.choose())

mu_co2 <- mean(population$CombCO2)
sd_co2 <- sd(population$CombCO2)
se_co2 <- sd_co2 / sqrt(896)

n <- 45
sample <- population %>%
  sample_n(size = n)

# Ho: mu = mu co2 emission
# Ha: mu != mu co2 emission

mean_co2 <- mean(sample$CombCO2)
sd_sample_co2 <- sd(sample$CombCO2)
se_sample_co2 <- sd_sample_co2 / sqrt(n)

# t test statistic
t_co2 <- (mean_co2 - mu_co2) / se_sample_co2
co2_p <- 2 * (1 - pt(abs(t_co2), n - 1))

# 10000 samples of 45
sample_means45 <- population %>%
  rep_sample_n(size = n, reps = 10000, replace = TRUE) %>%
  group_by(replicate) %>%
  summarise(mean = mean(CombCO2), sd = sd(CombCO2))

# Histogram
ggplot(sample_means45, aes(x = mean)) + 
  geom_histogram(bins = 10, fill = "blue", color = "black") +
  labs(x = "CO2", y = "Frequency",
       title = "Sampling Distribution of Combined CO2 Emissions, n = 45")

sample_means45 <- sample_means45 %>%
  mutate(t = (mean-mu_co2)/(sd/sqrt(n)))

# Histogram t stat
ggplot(sample_means45, aes(x = t)) + 
  geom_histogram(bins = 10, fill = "blue", color = "black") +
  labs(x = "t test statistic", y = "Frequency",
       title = "T Test statistic of Sampling Distribution of Combined CO2 Emissions, n = 45")

sample_means45 <- sample_means45 %>%
  mutate(p_val = 2*(1-pt(abs(t), 44)))

# p value histogram
ggplot(sample_means45, aes(x = p_val)) + 
  geom_histogram(binwidth = 0.05, 
                 boundary = 0, 
                 color = "black",
                 fill = c(rep("#D55E00", 1), rep("#999999", 19))) + 
  labs(x = "p-values", 
       title = "Distribution of p-values from 10000 \nRandom Samples from the Population")

mean(sample_means45$p_val <= 0.05) * 100
