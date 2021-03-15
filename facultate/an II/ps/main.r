# Sierpinsky Triangle

# Initialise triangle
p <- c(0, 500, 1000)
q <- c(0, 1000, 0)
x11()
par(mar = rep(0, 4))
plot(p, q, col= "red", pch = 15, cex = 1, axes = FALSE)

# Random starting point
x <- sample(0:1000, 1)
y <- sample(0:1000, 1)

# Chaos game
for (i in 1:10000) {
<<<<<<< HEAD
  Sys.sleep(.005)
=======
  Sys.sleep(.001)
>>>>>>> 34fa06a7e982fa15bac1d4d0c615b9ac3e80f396
  n <- sample(1:3, 1)
  x <- floor(x + (p[n] - x) / 2)
  y <- floor(y + (q[n] - y) / 2)
  points(x, y, pch = 15, cex = 0.5)
}
