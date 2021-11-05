import matplotlib.pyplot as plt
from matplotlib.ticker import StrMethodFormatter
import numpy as np

# ADC resolution and reference voltage
RES = 4
VOLT = 10

steps = 2 ** RES - 1

dvolt = VOLT / steps

xdat = np.arange(-dvolt, VOLT + dvolt, dvolt) + dvolt / 2
ydat = np.arange(-1, steps + 1, 1)


fig, ax = plt.subplots(1, 1)
fig.set_size_inches((5, 4))

ax.step(xdat, ydat, "-")

ax.set_xlim((0, VOLT))
ax.set_ylim((-0.5, steps + 0.5))

ax.yaxis.set_major_formatter(StrMethodFormatter("{x:04b}"))
ax.yaxis.set_ticks(np.arange(0, steps + 1, 1))

ax.set_xlabel("Applied voltage (V)")
ax.set_ylabel("ADC Level")

ax.text(9.5, 1, "$U_\\mathrm{ref} = 10\\,$V", ha="right")

fig.tight_layout()

# fig.show()
fig.savefig("adc.pdf")
