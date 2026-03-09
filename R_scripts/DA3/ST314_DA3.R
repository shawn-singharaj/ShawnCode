# Shawn Singharaj
# Stats Data Analysis 3

S <- c("heads", "tails")
# simulate a single toin coss
sim_fair_coin <- sample(S, size = 100, replace = TRUE)
# print results
table(sim_fair_coin)

# 20% heads
sim_unfair_coin <- sample(S, size = 100, replace = TRUE, prob = c(0.2, 0.8))
table(sim_unfair_coin)

# roll a die
Die <- c('1', '2', '3', '4', '5', '6')
sim_fair_die <- sample(Die, size = 10, replace = TRUE)
print(sim_fair_die)

# unfair die
sim_unfair_die <- sample(Die, size = 10, replace = TRUE, prob = c(0.1, 0.2, 0.4,
                                                                  0.1, 0.1, 0.1))
print(sim_unfair_die)

# simulate spins
wheel_outcomes <- c(rep(-500,2),rep(150,2),
                    rep(200,4),rep(250,2), 
                    rep(300,2),rep(350,1), 
                    rep(400,3),rep(450,1),
                    rep(500,2),rep(700,1),
                    rep(750,1),rep(800,1), 
                    rep(900,1),rep(1000,1))
spins_thousand <- sample(wheel_outcomes, size = 1000, replace = TRUE)
mean(spins_thousand) 
# display probability mass func
table(as.factor(spins_thousand))/1000
