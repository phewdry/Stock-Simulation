# Stock-Simulation
Usage of Monte Carlo random process to simulate unpredictability of stock trends

basic MCS applied to a stock price. We need a model to specify the behavior of the stock price, and we'll use one of the most common models in finance: geometric Brownian motion (GBM).  GBM assumes that a constant drift is accompanied by random shocks. Therefore, while Monte Carlo simulation can refer to a universe of different approaches to simulation, we will start here with the most basic.


One of the most common ways to estimate risk is the use of a Monte Carlo simulation (MCS). For example, to calculate the value at risk (VaR) of a portfolio, we can run a Monte Carlo simulation that attempts to predict the worst likely loss for a portfolio given a confidence interval over a specified time horizon - we always need to specify two conditions for VaR: confidence and horizon. (For related reading, see The Uses And Limits Of Volatility and Introduction To Value At Risk (VAR) - Part 1 and Part 2.)

In this article, we will review a basic MCS applied to a stock price. We need a model to specify the behavior of the stock price, and we'll use one of the most common models in finance: geometric Brownian motion (GBM). Therefore, while Monte Carlo simulation can refer to a universe of different approaches to simulation, we will start here with the most basic.

Where to Start 
A Monte Carlo simulation is an attempt to predict the future many times over. At the end of the simulation, thousands or millions of "random trials" produce a distribution of outcomes that can be analyzed. The basics steps are:


1. Specify a model (e.g. geometric Brownian motion) 
2. Generate random trials 
3. Process the output


