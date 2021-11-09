# Create figure for Adafruit 372 thermistor lookup table.

import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

# read the csv file - using relative path with respect to github repo
# todo: adjust me if required
fname = "../../figures/03_temperature/thermistor_lookup_table_adafruit_372.csv"
data = np.loadtxt(fname, delimiter=",", skiprows=1)

temperature_c_all = data[:, 0]
resistance_kohm_all = data[:, 1]

# limit the data to temperature range between -20 and +25 celsius
mask = np.where(np.logical_and(temperature_c_all >= -20, temperature_c_all <= 25))
temperature_c = temperature_c_all[mask]
resistance_kohm = resistance_kohm_all[mask]

# determine a fit for Steinhard-Hall equation and print parameters
def steinhard_hall(x, a, b, c):
    """Function to calculate Steinhard-Hall value

    1/T = a + b ln(R) + c (ln(R))^3

    :param x: Resistance
    :param a, b, c: Constants
    """
    return a + b * np.log(x) + c * np.log(x) ** 3


kelvin_to_c = 273.15
temperature_k = temperature_c + kelvin_to_c
params, _ = curve_fit(steinhard_hall, resistance_kohm, temperature_k)

print(
    f"Parameters Steinhard-Hall: a={params[0]:.3f}, b={params[1]:.3f}, c={params[2]:.3f}"
)
temperature_steinhard_hall_c = (
    steinhard_hall(resistance_kohm, params[0], params[1], params[2]) - kelvin_to_c
)


# make the plot
fig, plt = plt.subplots(1, 1)
fig.set_size_inches((5, 4))

plt.plot(resistance_kohm, temperature_c, "-", label="Lookup table")
plt.plot(resistance_kohm, temperature_steinhard_hall_c, "--", label="Steinhard-Hall")
# plt.semilogx()

plt.set_xlabel("Resistance (k$\\Omega$)")
plt.set_ylabel("Temperature ($\\degree\\mathrm{C}$)")

plt.legend()

fig.tight_layout()

# fig.show()
fig.savefig("thermistor_limited_range.pdf")
