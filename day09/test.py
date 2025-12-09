from pathlib import Path
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon, Rectangle

text = (Path(__file__).parent / "input").read_text()

points = [[int(v[0]), int(v[1])] for v in (l.split(',') for l in text.splitlines())]

fig, ax = plt.subplots()

minx = min(p[0] for p in points)
maxx = max(p[0] for p in points)
miny = min(p[1] for p in points)
maxy = max(p[1] for p in points)

ax.add_patch(Polygon([[p[0]-minx, p[1]-miny] for p in points], fill=False))

r1 = (6073, 67455)
r2 = (94582, 50408)

ax.add_patch(Rectangle([min(r1[0], r2[0])-minx, min(r1[1], r2[1])-minx], abs(r1[0]-r2[0]), abs(r1[1]-r2[1]), alpha=.5))
ax.set_ylim([0, maxy-miny])
ax.set_xlim([0, maxx-minx])
plt.show()


