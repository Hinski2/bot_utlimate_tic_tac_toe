import csv
import matplotlib.pyplot as plt
from collections import defaultdict

def analizuj_dane(plik_csv):
    wyniki_bota = defaultdict(lambda: {'wygrane': 0, 'przegrane': 0, 'remisy': 0})

    for wiersz in plik_csv:
        typ_bota1 = wiersz[0]
        typ_bota2 = wiersz[1]
        wynik = int(wiersz[2])

        if wynik == 0:
            wyniki_bota[typ_bota1]['wygrane'] += 1
            wyniki_bota[typ_bota2]['przegrane'] += 1
        elif wynik == 1:
            wyniki_bota[typ_bota1]['przegrane'] += 1
            wyniki_bota[typ_bota2]['wygrane'] += 1
        elif wynik == 2:
            wyniki_bota[typ_bota1]['remisy'] += 1
            wyniki_bota[typ_bota2]['remisy'] += 1

    return wyniki_bota

def generuj_wykresy(wyniki):
    for typ_bota, statystyki in wyniki.items():
        labels = ['Wygrane', 'Przegrane', 'Remisy']
        sizes = [statystyki['wygrane'], statystyki['przegrane'], statystyki['remisy']]
        colors = ['green', 'red', 'yellow']
        explode = (0.1, 0, 0)

        suma_partii = sum(sizes)

        fig, ax = plt.subplots()
        ax.pie(sizes, explode=explode, labels=labels, colors=colors, autopct='%1.1f%%', shadow=True, startangle=140)
        ax.axis('equal')

        plt.title(f'Statystyki dla bota {typ_bota} (Suma partii: {suma_partii})')
        plt.savefig(f'wykres_{typ_bota}.png', bbox_inches='tight')
        plt.close()

if __name__ == "__main__":
    with open('./dane.csv', 'r') as plik:
        czytacz_csv = csv.reader(plik, delimiter=';')
        wyniki = analizuj_dane(czytacz_csv)
        generuj_wykresy(wyniki)
