# Create figure for Adafruit 372 thermistor lookup table.

import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

# parameter precision to print out
PREC = 12

# read the csv file
fname = "thermistor_lookup_table_adafruit_372.csv"
data = np.loadtxt(fname, delimiter=",", skiprows=1)

temperature_c = data[:, 0]
resistance_kohm = data[:, 1]

# calculate temperature according to b-parameter equation
kelvin_to_c = 273.15
b_param = 3950  # K
t0 = 298.15
temperature_beqn = (
    1 / (1 / 287 + 1 / b_param * np.log(resistance_kohm / 10)) - kelvin_to_c
)

# determine a fit for Steinhard-Hall equation and print parameters
def steinhard_hall(x, a, b, c):
    """Function to calculate Steinhard-Hall value

    1/T = a + b ln(R) + c (ln(R))^3

    :param x: Resistance
    :param a, b, c: Constants
    """
    return a + b * np.log(x) + c * np.log(x) ** 3


temperature_k = temperature_c + kelvin_to_c
params, _ = curve_fit(steinhard_hall, resistance_kohm, 1 / temperature_k)

print(
    f"Parameters Steinhard-Hall: "
    f"a={params[0]:.{PREC}f}, b={params[1]:.{PREC}f}, c={params[2]:.{PREC}f}"
)

temperature_steinhard_hall_c = (
    1 / steinhard_hall(resistance_kohm, params[0], params[1], params[2]) - kelvin_to_c
)


# make the plot
fig, plt = plt.subplots(1, 1)
fig.set_size_inches((5, 4))

plt.plot(resistance_kohm, temperature_c, "-", label="Lookup table")
plt.plot(resistance_kohm, temperature_steinhard_hall_c, ":", label="Steinhard-Hall")
plt.plot(resistance_kohm, temperature_beqn, "--", label="B-parameter equation")
# plt.semilogx()

plt.set_xlabel("Resistance (k$\\Omega$)")
plt.set_ylabel("Temperature ($\\degree\\mathrm{C}$)")

plt.legend()

fig.tight_layout()

# fig.show()
fig.savefig("thermistor.pdf")
