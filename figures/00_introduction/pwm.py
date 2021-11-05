import matplotlib.pyplot as plt
from matplotlib.ticker import StrMethodFormatter
import numpy as np

LEVELS = [0.6, 0.2]
VOLTS = 5
STEPS = 10

fig, ax = plt.subplots(1)
fig.set_size_inches((5, 4))

colors = "tab:blue", "tab:orange"

# make the y data
ydat = [0, VOLTS] * STEPS
ydat.append(0)
ydat.append(0)
ydat = np.array(ydat)

for lit, level in enumerate(LEVELS):
    xdat = np.zeros(STEPS * 2 + 2)
    for it in range(STEPS):
        xdat[2 * it + 1] = it + 0.5 - level / 2
        xdat[2 * it + 2] = it + 0.5 + level / 2
    xdat[-1] = STEPS

    ax.step(xdat, ydat, "-", color=colors[lit], where="post", alpha=0.75, label=level)

    ax.axhline(level * VOLTS, color=colors[lit], linestyle="--")

ax.set_xlabel("Cycle")
ax.set_ylabel("Voltage (V)")

ax.legend(loc="upper right", title="Duty Cycle")

# fig.show()
fig.savefig("pwm.pdf")
