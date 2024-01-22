import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import os

if __name__ == "__main__":

    df = pd.read_csv('./dane.csv', sep=';', header=None)
    df.columns = ['bot4', 'bot5', 'wynik']
    bot4_wins = len(df[df['wynik'] == 1])
    bot4_losses = len(df[df['wynik'] == 0])
    bot4_draws = len(df[df['wynik'] == 2])
    ratio = bot4_wins / (bot4_losses + bot4_draws + 1e-7)  # avoid division by zero

    df['wynik'].value_counts().plot(kind='pie', colors=['green', 'red', 'blue'], labels=['Wygrane', 'Przegrane', 'Remisy'], autopct='%1.1f%%')
    plt.title('Wykres dla random vs normal')
    if not os.path.exists('wykresy'):
        os.makedirs('wykresy')
    plt.savefig(f'wykresy/wykresRandomNormal.png')
    plt.clf()