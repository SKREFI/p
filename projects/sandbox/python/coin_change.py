from collections import defaultdict


def f(coins, amount):
    dp = [amount+1 for i in range(amount+1)]
    print(dp)
    dp[0] = 0

    for i in range(1, amount+1):
        for c in coins:
            if c > i:
                continue
            else:
                dp[i] = min(dp[i], dp[i-c]+1)

    return dp[amount] if dp[amount] != amount+1 else -1


if __name__ == "__main__":
    coins = [1, 2, 5]
    amount = 11
 
    print(f(coins, amount))
