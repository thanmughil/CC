def valid_move(available_coins, max_take):
    return 1 <= available_coins <= max_take

def play_game(n, m):
    available_coins = n
    player_turn = 1

    while available_coins > 0:
        print(f"\nAvailable coins: {available_coins}")
        max_take = min(m, available_coins)
        player_name = f"Player {player_turn}"
        
        while True:
            coins_taken = int(input(f"{player_name}, take between 1 and {max_take} coins: "))

            if valid_move(coins_taken, max_take):
                break
            else:
                print(f"Invalid move! Please choose between 1 and {max_take} coins.")

        available_coins -= coins_taken

        if available_coins <= 0:
            print(f"\n{player_name} wins!")
        else:
            player_turn = 3 - player_turn  # Switch between players (1 <-> 2)

if __name__ == "__main__":
    n = int(input("Enter the number of coins: "))
    m = int(input("Enter the maximum number of coins a player can take: "))

    if m >= n:
        print("Invalid input: Maximum coins to take should be less than the total number of coins.")
    else:
        play_game(n, m)
