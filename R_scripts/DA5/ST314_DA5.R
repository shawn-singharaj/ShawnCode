# Shawn Singharaj
# DA5

# Population hip surgery df
population <- tibble(
  hip = c(rep("Infection", 19560), rep("No infection", 632440))
)

ggplot(population, aes(x = hip)) + 
  geom_bar() + 
  labs(x = "", y = "Count", 
       title = "Ceramic hip patients who develop infection")

population %>%
  count(hip) %>%
  mutate(p = n/sum(n))

# 400 sampled 
samp1 <- population %>%
  sample_n(400)

samp1 %>%
  count(hip) %>%
  mutate(p = n/sum(n))

samp2 <- population %>%
  sample_n(400)

samp2 %>%
  count(hip) %>%
  mutate(p = n/sum(n))

# 500 sampled 
samp3 <- population %>%
  sample_n(500)

samp3 %>%
  count(hip) %>%
  mutate(p = n/sum(n))

# 1000 sampled
samp4 <- population %>%
  sample_n(1000)

samp4 %>%
  count(hip) %>%
  mutate(p = n/sum(n))


# 10000 samples of 400
sample_props400 <- population %>%
  rep_sample_n(size = 400, reps = 10000, replace = TRUE) %>%
  count(hip) %>%
  mutate(p_hat = n/sum(n)) %>%
  filter(hip == "Infection")

ggplot(sample_props400, aes(x = p_hat)) +
  geom_histogram(binwidth = 0.01) +
  labs(x = "p_hat (Develops infection)", 
       title = "Sampling Distribution of p_hat", 
       subtitle = "Sample size = 400, Number of samples = 10,000")


# 15 samples of 100
sample_props_small <- population %>%
  rep_sample_n(size = 100, reps = 15, replace = TRUE) %>%
  count(hip) %>%
  mutate(p_hat = n/sum(n)) %>%
  filter(hip == "Infection")


# 10a
pnorm(0.02, 0.03, 0.00853)
# 0.1205317

# 10b
pnorm(0.08, 0.03, 0.00853, FALSE)
# 2.291248e-09

# 10c
pnorm(0.06, 0.03, 0.00853) - pnorm(0.02, 0.03, 0.00853) 
# 0.8792501