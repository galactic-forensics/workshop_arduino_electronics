"""Plot lowest temperature that can be reached

For Arduino code, use code for exercise 15.
"""


import matplotlib.pyplot as plt

power_levels = [0, 25, 50, 75, 100]  # in percent, zero is room temperature
temp_c = [23, 17, 11, 7, 3]
voltage = [0, 3.9, 6.81, 9.13, 11.52]

fig, ax = plt.subplots(1, 1)
ax2 = ax.twinx()

ax.plot(power_levels, temp_c, "o--", label="Temperature")
ax2.plot(power_levels, voltage, "s:", color="tab:red", label="Voltage")

ax.set_xlabel("Power level (%)")
ax.set_ylabel("Temperature achieved ($^{\\circ}$C)")
ax2.set_ylabel("Voltage (V)")
fig.legend()


# fig.show()
fig.savefig("exercise_16_plot.pdf")
