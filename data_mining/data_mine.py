import numpy as np
from scipy.stats import norm, expon, gamma
import matplotlib.pyplot as plt
import pandas as pd
import sys

smallest_float = np.finfo(float).eps


def fit_to_normal_dist(data, labels, figure):
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))

    ax1.plot(data, 'o')
    ax1.set_xlabel(labels[0]['xlabel'])
    ax1.set_ylabel(labels[0]['ylabel'])
    ax1.set_title(labels[0]['title'], fontsize=24,
                  fontweight="bold")

    mu, std = norm.fit(data)
    print(f'{figure}: N({mu}, {std})')
    # the histogram of the data
    ax2.hist(data, bins=25, density=True)
    # normal distribution
    xmin, xmax = ax2.get_xlim()
    x = np.linspace(0, xmax + xmin, 100)
    p = norm.pdf(x, mu, std)

    # plot
    ax2.plot(x, p, '--')
    ax2.set_xlabel(labels[1]['xlabel'])
    ax2.set_ylabel('Hustota pravděpodobnosti')
    ax2.set_title(f'{labels[1]["title"]} N({mu:.2f}, {std ** 2:.2f})', fontsize=24,
                  fontweight="bold")

    fig.tight_layout()
    fig.savefig(f'output/{figure}.pdf')
    fig.show()


def fit_to_exp_dist(data, labels, figure):
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))
    data = np.array(data)
    ax1.plot(data, 'o')
    ax1.set_xlabel(labels[0]['xlabel'])
    ax1.set_ylabel(labels[0]['ylabel'])
    ax1.set_title(labels[0]['title'], fontsize=24,
                  fontweight="bold")

    ax2.hist(data, bins=25, density=True)
    s_mean = data.mean()
    rate = 1. / s_mean
    print(f'{figure}: E({rate})')
    s_max = data.max()
    days = np.linspace(0, s_max, 1000)
    dist_exp = expon.pdf(days, scale=1. / rate)
    ax2.plot(days, dist_exp,
             '--')
    ax2.set_xlabel(labels[1]['xlabel'])
    ax2.set_ylabel('Hustota pravděpodobnosti')
    ax2.set_title(f'{labels[1]["title"]} E({rate:.8f})', fontsize=24,
                  fontweight="bold")
    fig.tight_layout()
    fig.savefig(f'output/{figure}.pdf')
    fig.show()


def fit_to_gamma_dist(data, norm_co, labels, figure):
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))
    data = np.array(data)
    ax1.plot(data, 'o')
    ax1.set_xlabel(labels[0]['xlabel'])
    ax1.set_ylabel(labels[0]['ylabel'])
    ax1.set_title(labels[0]['title'], fontsize=24,
                  fontweight="bold")

    ax2.hist(data, bins=30, density=True)
    x = np.linspace(0, np.amax(data), 1000)
    shape, loc, scale = gamma.fit(data, floc=0)
    print(f'{figure}: G{shape, scale} + {norm_co}')
    y = gamma.pdf(x, shape, loc, scale)
    ax2.plot(x, y,
             '--')
    ax2.set_xlabel(f'{labels[1]["xlabel"]} + {norm_co:.3f} (normalizace) [{labels[1]["unit"]}]' if norm_co > 0 else
                   labels[1]["xlabel"])
    ax2.set_ylabel('Hustota pravděpodobnosti')
    ax2.set_title(f'{labels[1]["title"]} G({shape:.3f},{scale:.3f})', fontsize=24,
                  fontweight="bold")
    fig.tight_layout()
    fig.savefig(f'output/{figure}.pdf')
    fig.show()


def value_neg_correlation(positive, negative):
    fig, (ax1, ax2, ax3, ax4, ax5) = plt.subplots(5, 1, figsize=(12, 10))
    positive = np.array(positive)
    negative = np.array(negative)

    len_neg = negative.shape[0]
    len_pos = positive.shape[0]

    max_value = max(negative.max(), positive.max())

    ax1.plot(positive, 'o', color='C0')
    ax1.set_xlabel('Vzorek')
    ax1.set_ylabel('Délka [m]')
    ax1.set_title(f'Délky osnov postupijících klížení', fontsize=24,
                  fontweight="bold")
    ax1.set_ylim(0, max_value)

    ax2.hist(positive, bins=30, density=True)
    s_mean = positive.mean()
    rate = 1. / s_mean
    s_max = positive.max()
    days = np.linspace(0, s_max, 1000)
    # bin size: interval between two
    # consecutive values in `days`
    dist_exp = expon.pdf(days, scale=1. / rate)
    ax2.plot(days, dist_exp, '--')
    ax2.set_xlabel('Délka [m]')
    ax2.set_ylabel('Hustota pravděpodobnosti')
    ax2.set_title(f'Histogram délky osnov aproximován E({rate:.8f})', fontsize=24,
                  fontweight="bold")

    ax3.plot(negative, 'o', color='C3')
    ax3.set_xlabel('Vzorek')
    ax3.set_ylabel('Délka [m]')
    ax3.set_title(f'Délky osnov nepostupijících klížení', fontsize=24,
                  fontweight="bold")
    ax3.set_ylim(0, max_value)

    ax4.hist(negative, bins=30, density=True, color='C3')
    s_mean = negative.mean()
    rate = 1. / s_mean
    s_max = negative.max()
    s_min = negative.min()
    days = np.linspace(0, s_max, 1000)
    # bin size: interval between two
    # consecutive values in `days`
    dist_exp = expon.pdf(days, scale=1. / rate)
    ax4.plot(days, dist_exp, '--')
    ax4.set_xlabel('Délka [m]')
    ax4.set_ylabel('Hustota pravděpodobnosti')
    ax4.set_title(f'Délky osnov E({rate:.8f})', fontsize=24,
                  fontweight="bold")

    count = len_neg + len_pos
    labels = 'Klížení', 'Zpracováno'
    colors = 'C3', 'C0'
    sizes = [len_neg / count * 100, len_pos / count * 100]
    explode = (0, 0.1)  # only "explode" the 2nd slice (i.e. 'Hogs')
    ax5.pie(sizes, explode=explode, colors=colors, labels=labels, autopct='%1.1f%%',
            shadow=True, startangle=90)
    ax5.axis('equal')
    ax5.set_title(f'Podíl příslušnosti k trídam', fontsize=24,
                  fontweight="bold")
    fig.tight_layout()
    fig.savefig('output/klizeni_pravdepodobnost1.pdf')
    fig.show()


def process_osnovy():
    with open(f'input/osnovy', 'r') as file:
        x = file.read()
        values = x.split()

        integers = []
        for value in values:
            try:
                integer = int(value)
            except ValueError:
                continue
            integers.append(integer)
        fit_to_normal_dist(integers, [
            {'title': 'Počty vyrobených osnov v příslušných dnech výroby', 'xlabel': 'Den',
             'ylabel': 'Kusů'},
            {'title': 'Počty vyrobených osnov', 'xlabel': 'Kusů', 'ylabel': ''}], 'osnova_pocet')
        norm_data = 8 / np.array(integers) * 60
        fit_to_normal_dist(norm_data, [
            {'title': 'Průměrná perioda výroby osnovy v daný den', 'xlabel': 'Den',
             'ylabel': 'Čas [m]'},
            {'title': 'Průměrná perioda výroby osnovy v daný den', 'xlabel': 'Čas [m]',
             'ylabel': '', 'unit': 'm'}], 'osnova_cas')


def process_metry():
    with open(f'input/metry', 'r') as file:
        x = file.read()
        values = x.split()

        positive = []
        negative = []
        for value in values:
            try:
                integer = int(value)
            except ValueError:
                continue
            if integer >= 0:
                positive.append(integer)
            else:
                negative.append(abs(integer))
        fit_to_exp_dist(positive + negative, [
            {'title': 'Délky vyrobených osnov', 'xlabel': 'Osnova', 'ylabel': 'Délka [m]'},
            {'title': 'Délky vyrobených osnov', 'xlabel': 'Délka [m]', 'ylabel': ''}], 'osnova_delka')
        value_neg_correlation(positive, negative)


def process_kontroly():
    with open(f'input/kontroly', 'r') as file:
        lines = file.readlines()

        values = []
        for line in lines:
            line = line.rstrip()
            if line[0] == '#':
                continue
            values.append(int(line.replace(',', '')))

        values = np.array(values)
        fit_to_normal_dist(values, [
            {'title': 'Počet zkontrolovaných metrů', 'xlabel': 'Den', 'ylabel': 'Metrů'},
            {'title': 'Počet zkontrolovaných metrů', 'xlabel': 'Metrů', 'ylabel': ''}], 'kontrola')
        norm_data = 24 * 60 * 60 / values
        norm_co = np.amin(norm_data) - smallest_float
        norm_data = norm_data - np.amin(norm_data) + smallest_float
        fit_to_gamma_dist(norm_data, norm_co, [
            {'title': 'Průměrný čas kontroly 1m výrobku', 'xlabel': 'Vzorek', 'ylabel': 'Čas [s]'},
            {'title': 'Čas kontroly 1m výrobku', 'xlabel': 'Čas', 'ylabel': '', 'unit': 's'}], 'kontrola_cas')


def process_snovani_soukani():
    df = pd.read_excel('input/snovaniSoukani.xlsx', header=None, names=['m', 'kg'])
    df = df.dropna()
    values = 24 * 60 / df['kg']
    values = values[values != np.inf]
    norm = values.min() - smallest_float
    values = values - values.min() + smallest_float
    values = values.to_numpy(dtype='float')
    fit_to_gamma_dist(values, norm, [
        {'title': 'Průměrná doba soukání 1 kg osnovy', 'xlabel': 'Den',
         'ylabel': 'Čas [m]'},
        {'title': 'Průměrná doba soukání 1 kg osnovy', 'xlabel': 'Čas', 'ylabel': '', 'unit': 'm'}], 'soukani_cas')
    df['kg'] = df['kg'] * 70 / 11
    df['var'] = df['kg'] / df['m']
    values = df['var'].to_numpy(dtype='float') * 100
    fit_to_normal_dist(values, [
        {'title': 'Pravděpodobnost soukání osnovy', 'xlabel': 'Den',
         'ylabel': 'Pravděpodobnost [%]'},
        {'title': 'Pravděpodobnost soukání osnovy', 'xlabel': 'Pravděpodobnost [%]', 'ylabel': ''}],
                       'soukani_pravdepodobnost')


def process_navadeni():
    df = pd.read_excel('input/navadeni.xlsx', header=None, names=['together', 'thread', 'done'])
    df = df.dropna().iloc[1:]
    values = df['done'] / df['together']
    values = values.to_numpy(dtype='float')
    values = values * 100
    fit_to_normal_dist(values, [
        {'title': 'Pravděpodobnost navádění osnovy', 'xlabel': 'Den',
         'ylabel': 'Pravděpodobnost [%]'},
        {'title': 'Pravděpodobnost navádění osnovy', 'xlabel': 'Pravděpodobnost [%]', 'ylabel': ''}],
                       'navadeni_pravdepodobnost')
    df = df.dropna().iloc[:-1]
    values = df['thread'] / df['done']
    values = values.to_numpy(dtype='float')
    fit_to_normal_dist(values, [
        {'title': 'Počet nití na osnovu', 'xlabel': 'Den',
         'ylabel': 'Nitě'},
        {'title': 'Počet nití na osnovu', 'xlabel': 'Nitě', 'ylabel': ''}], 'osnova_nite')
    values = 24 * 60 * 60 / df['thread']
    values = values.to_numpy(dtype='float')
    norm = values.min() - smallest_float
    values = values - values.min() + smallest_float
    fit_to_gamma_dist(values, norm, [
        {'title': 'Průměrná doba navedení nitě', 'xlabel': 'Den',
         'ylabel': 'Čas [s]'},
        {'title': 'Průměrná doba navedení nitě', 'xlabel': 'Čas', 'ylabel': '', 'unit': 's'}], 'navadeni_cas')


def process_pritaceni():
    df = pd.read_excel('input/pritaceniMimo.xlsx', header=None, names=['together', 'done'])
    df = df.dropna().iloc[1:]
    values = df['done'] / df['together']
    values = values.to_numpy(dtype='float') * 100
    fit_to_normal_dist(values, [
        {'title': 'Pravděpodobnost přitáčení osnovy', 'xlabel': 'Den',
         'ylabel': 'Pravděpodobnost [%]'},
        {'title': 'Pravděpodobnost přitáčení osnovy', 'xlabel': 'Pravděpodobnost [%]', 'ylabel': ''}],
                       'pritaceni_pravdepodobnost')


def process_klizeni():
    df = pd.read_excel('input/klizeni.xlsx', header=None, names=['done', 'processed', 'm'])
    df = df.dropna().iloc[1:]
    values = df['processed'] / df['done']
    values = values.to_numpy(dtype='float') * 100
    fit_to_gamma_dist(values, 0, [
        {'title': 'Podíl klížených osnov vzhledem k počtu vyrobených osnov', 'xlabel': 'Den',
         'ylabel': 'Podíl [%]'},
        {'title': 'Podíl klížených osnov', 'xlabel': 'Podíl [%]', 'ylabel': ''}],
                      'klizeni_podil')
    values = 24 * 60 * 60 / df['m']
    values = values.to_numpy(dtype='float')
    fit_to_gamma_dist(values, 0, [
        {'title': 'Průmerná doba klížení 1m osnovy', 'xlabel': 'Den',
         'ylabel': 'Čas [s]'},
        {'title': 'Průmerná doba klížení 1m osnovy', 'xlabel': 'Čas [s]', 'ylabel': ''}], 'klizeni_cas')


def process_zakladani():
    with open(f'input/zakladani.txt', 'r') as file:
        lines = file.readlines()
        values = []
        for line in lines:
            line = line.rstrip()
            if line[0] == '#':
                continue
            values.append(int(line.replace(',', '')))

        values = np.array(values)
        values = 24 / values
        fit_to_gamma_dist(values, 0, [
            {'title': 'Průměrná doba zakládání osnovy', 'xlabel': 'Den', 'ylabel': 'Čas [h]'},
            {'title': 'Průměrná doba zakládání osnovy', 'xlabel': 'Čas [h]', 'ylabel': ''}], 'zakladani')


sys.stdout = open('output/params', 'w')

process_osnovy()
process_metry()
process_kontroly()
process_snovani_soukani()
process_navadeni()
process_pritaceni()
process_klizeni()
process_zakladani()
