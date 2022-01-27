data <- read.csv("review.csv")

x <- data.frame(reviewerID = data$reviewerID, asin = data$asin, reviewText = data$reviewText, overall = data$overall, reviewTime = data$reviewTime)

updated_x <- subset(x, overall >= 4)
