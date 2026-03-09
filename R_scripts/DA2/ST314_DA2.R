# Shawn Singharaj
# Assignment 2

# Load data set births in NC
data(births)

# Return dimensions + vars
glimpse(births)

# Show only birth weights
births$weight

# Plot number of hospital visits made by mother and baby's weight
ggplot(data = births, aes(x = visits, y = weight)) + geom_point()

# Convert lbs to oz
births$weight * 16
# Add new var to table %>% is piping
births <- births %>% 
  mutate(weight_oz = weight * 16)

# add older father bool var
births <- births %>%
  mutate(older_father = m_age < f_age)


# PART 2:
library(openintro)
data(births14)
# 1000 x 13
glimpse(births14)

# scatterplot
ggplot(data = births14, aes(x = weeks, y = weight)) + geom_point()

# Create weight_kg var
births14 <- births14 %>% 
  mutate(weight_kg = weight / 2.205)
# 3.264472
mean(births14$weight_kg)

# Add older father bool var
births14 <- births14 %>%
  mutate(older_father = mage < fage)


# Histograms, Bar plots, Box plots:
# ONE VAR
# Histogram
ggplot(loan50, aes(x = loan_amount)) + 
  geom_histogram(bins = 10, fill = "blue", color = "black") +
  labs(x = "Loan Amount (USD)", y = "Frequency",
       title = "Distitbution of Loan Amounts Received from the Lending Club")

# Boxplot
ggplot(loan50, aes(x = loan_amount)) + 
  geom_boxplot() +
  labs(x = "Loan Amount (USD)", 
       title = "Distribution of Loan Amounts Received from Lending Club") + 
  theme(axis.text.y = element_blank(), 
        axis.ticks.y = element_blank())

summary(loan50$loan_amount)
mean(loan50$loan_amount)
median(loan50$loan_amount)
sd(loan50$loan_amount)
IQR(loan50$loan_amount)

# TWO VARS
ggplot(loan50, aes(x = loan_amount, y = homeownership)) + 
  geom_boxplot() +
  labs(x = "Loan Amount (USD)", 
       y = "Homeownership Type", 
       title = "Distribution of Loan Amounts Received from Lending Club by Homeownership Type")

sum(loan50$homeownership == "rent")

table(loan50$homeownership)
# Proportion relative to dataset
prop.table(table(loan50$homeownership))

# Bar plot
ggplot(loan50, aes(x = homeownership)) + 
  geom_bar() + 
  labs(x = "Homeownership Type",
       title = "Distribution of Homeownership Types for 50 Lending Club Loans")


# PART 3:
# Histogram
options(scipen=999)
ggplot(loan50, aes(x = total_credit_limit)) + 
  geom_histogram(bins = 10, fill = "purple", color = "black") +
  labs(x = "Total Credit Limit (USD)", y = "Frequency",
       title = "Total Credit Limit Data from Lending Club")

# Boxplot
ggplot(loan50, aes(x = total_credit_limit)) + 
  geom_boxplot() +
  labs(x = "Total Credit Limit (USD)", 
       title = "Total Credit Limit Data from Lending Club") + 
  theme(axis.text.y = element_blank(), 
        axis.ticks.y = element_blank())

# Outlier: > 643626
summary(loan50$total_credit_limit)
1.5 * IQR(loan50$total_credit_limit) + 299766 

mean(loan50$total_credit_limit)
median(loan50$total_credit_limit)
sd(loan50$total_credit_limit)
IQR(loan50$total_credit_limit)

# Boxplot homeownership and total credit limit
ggplot(loan50, aes(x = total_credit_limit, y = homeownership)) + 
  geom_boxplot() +
  labs(x = "Total Credit Limit (USD)", 
       y = "Homeownership Type", 
       title = "Distribution of Total Credit Limit by Lending Club to Homeownership Type")

# loan purpose
table(loan50$loan_purpose)
prop.table((table(loan50$loan_purpose)))

# Barplot
ggplot(loan50, aes(x = loan_purpose)) + 
  geom_bar() + 
  labs(x = "Purpose for Loan",
       title = "Loan Purpose per Lending Club")
