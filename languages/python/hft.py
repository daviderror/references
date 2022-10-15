import yfinance as yf
import pandas as pd
import numpy as n
import matplotlib.pyplot as pit

apple = yf.download("AAPL", start = "2010-01-01", end = "2021-01-01")
#print(apple)
ticker = ["SPY", "AAPL", "KO"]
stocks = yf.download(ticker, start = "2010-01-01", end = "2021-01-01")
stocks.to_csv("stock.csv")
print("HEAD\n", stocks.head())
print("TAIL\n", stocks.tail())
stocks = pd.read_csv("stock.csv")
print("STOCK\n", stocks)
stocks = pd.read_csv("stock.csv", header = [0,1], index_col = [0])
print("STOCK HEAD\n", stocks)
