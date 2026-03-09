# Shawn Singharaj
# DA6

# PART 1

population <- tibble(
  climate_change_affects = c(rep("Yes", 310000), rep("No", 190000))
)

ggplot(population, aes(x = climate_change_affects)) +
  geom_bar() +
  labs(
    x = "", y = "",
    title = "Do you think climate change is affecting your local community?"
  )

population %>%
  count(climate_change_affects) %>%
  mutate(p = n /sum(n))

n <- 180
samp <- population %>%
  sample_n(size = n)

samp %>%
  count(climate_change_affects) %>%
  mutate(p = n /sum(n))

qnorm((1 + 0.95) / 2)
qnorm((1 + 0.85) / 2)
qnorm((1 + 0.99) / 2)

# 0.633 point estimate
p_hat <- 0.633
crit <- qnorm((1 + 0.95) / 2)
se <- sqrt((p_hat * (1 - p_hat)) / 180)

lower <- p_hat - crit * se
upper <- p_hat + crit * se

critical_value <- qnorm(0.975, 0, 1)

sample_props180 <- population %>%
  rep_sample_n(size = 180, reps = 10000, replace = TRUE) %>%
  count(climate_change_affects) %>%
  filter(climate_change_affects == "Yes") %>%
  mutate(p_hat = n / 180) %>%
  mutate(lower = p_hat - (critical_value * sqrt((p_hat*(1-p_hat))/180)), 
         upper = p_hat + (critical_value * sqrt((p_hat*(1-p_hat))/180))) %>%
  mutate(capture_parameter = (lower <= 0.62 & upper >= 0.62))

mean(sample_props180$capture_parameter)

# PART 2
data(births)
non_smoker <- births %>%
  filter(smoke == "nonsmoker")
samp_mean <- mean(non_smoker$m_age)
samp_error <- sd(non_smoker$m_age) / sqrt(100)
samp_crit_t <- qt(0.95, 99)

samp_lower <- samp_mean - samp_crit_t * samp_error
samp_higher <- samp_mean + samp_crit_t * samp_error
