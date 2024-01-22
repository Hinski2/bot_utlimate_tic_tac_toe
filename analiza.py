import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import os

if __name__ == "__main__":
    idx = 0
    best_ratio = 0
    best_idx = 0
    DIFF, SELECT = 0, 2

    for SQRT in (0.2, 0.4, 0.8, 1): #6
        for WINS in (2, 3): #2
            if(idx <= 3):
                idx += 1
                continue

            subprocess.call(["./a.out", str(DIFF), str(SQRT), str(WINS), str(SELECT)])

            df = pd.read_csv('./dane.csv', sep=';', header=None)
            df.columns = ['bot4', 'bot5', 'wynik']
            bot4_wins = len(df[df['wynik'] == 1])
            bot4_losses = len(df[df['wynik'] == 0])
            bot4_draws = len(df[df['wynik'] == 2])
            ratio = bot4_wins / (bot4_losses + bot4_draws + 1e-7)  # avoid division by zero

            if ratio > best_ratio:
                best_ratio = ratio
                best_idx = idx

            df['wynik'].value_counts().plot(kind='pie', colors=['green', 'red', 'blue'], labels=['Wygrane', 'Przegrane', 'Remisy'], autopct='%1.1f%%')
            plt.title(f'DIFF={DIFF}, SQRT={SQRT}, WINS={WINS}, SELECT={SELECT}, Iteracja={idx}')
            if not os.path.exists('wykresy'):
                os.makedirs('wykresy')
            plt.savefig(f'wykresy/wykres_v3_{idx}.png')
            plt.clf()

            idx += 1

    print(f'Bot 4 miał najlepsze statystyki wygranych do przegranych dla idx: {best_idx}')
