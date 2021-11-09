# Create figure for Adafruit 372 thermistor lookup table.

import matplotlib.pyplot as plt
import numpy as np

# read the csv file
fname = "thermistor_lookup_table_adafruit_372.csv"
data = np.loadtxt(fname, delimiter=",", skiprows=1)

temperature_c = data[:, 0]
resistance_kohm = data[:, 1]

# make the plot
fig, plt = plt.subplots(1, 1)
fig.set_size_inches((5, 4))

plt.semilogx(resistance_kohm, temperature_c, "-", label="Adafruit 3950 NTC")

plt.set_xlabel("Resistance (k$\\Omega$)")
plt.set_ylabel("Temperature ($\\degree\\mathrm{C}$)")

plt.legend()

fig.tight_layout()

# fig.show()
fig.savefig("thermistor.pdf")
