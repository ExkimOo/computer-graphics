import pygame as pg
from constants import *
from matrix_functions import *
from math import pi


def get_cylinder(N, r, h, h0=0):
    base_bottom = get_base(N, r, h0)
    base_top = get_base(N, r, h)

    for i in range(len(base_bottom)):
            base_bottom[i] = np.dot(base_bottom[i], translate([WIDTH / 2, HEIGHT / 2, 0]))
            base_top[i] = np.dot(base_top[i], translate([WIDTH / 2, HEIGHT / 2, 0]))

    return base_bottom, base_top


def get_base(N, r, h):
    angle = 0
    angle_step = 2 * pi / N
    base = np.empty([N, 4], float)

    for i in range(N):
        x = r * sin(angle)
        y = r * cos(angle)
        base[i] = [x, y, h, 1]
        angle += angle_step

    return base


def draw(screen, base_bottom, base_top):
    N = len(base_bottom)
    for i in range(N):
        pg.draw.line(screen, WHITE, [int(base_bottom[i][0]), int(base_bottom[i][1])], [int(base_top[i][0]), int(base_top[i][1])])

    for i in range(N - 1):
        pg.draw.line(screen, WHITE, [int(base_bottom[i][0]), int(base_bottom[i][1])], [int(base_bottom[i + 1][0]), int(base_bottom[i + 1][1])])
        pg.draw.line(screen, WHITE, [int(base_top[i][0]), int(base_top[i][1])], [int(base_top[i + 1][0]), int(base_top[i + 1][1])])
    pg.draw.line(screen, WHITE, [int(base_bottom[0][0]), int(base_bottom[0][1])], [int(base_bottom[N - 1][0]), int(base_bottom[N - 1][1])])
    pg.draw.line(screen, WHITE, [int(base_top[0][0]), int(base_top[0][1])], [int(base_top[N - 1][0]), int(base_top[N - 1][1])])
