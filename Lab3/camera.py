import pygame as pg
from matrix_functions import *
from constants import *


rotation_angle = 0.05
approach = 1.05
view_matrix_default = [[1, 0, 0, 0],
                       [0, 1, 0, 0],
                       [0, 0, 1, 0],
                       [0, 0, 0, 1]]


def check_key_press():
    x, y, z = WIDTH / 2, HEIGHT / 2, 200
    key = pg.key.get_pressed()
    if key[pg.K_q]:
        view_matrix = translate([-x, -y, -z])
        view_matrix = np.dot(view_matrix, scale(approach))
        view_matrix = np.dot(view_matrix, translate([x, y, z]))
        return view_matrix
    if key[pg.K_w]:
        view_matrix = translate([-x, -y, -z])
        view_matrix = np.dot(view_matrix, rotate_x(rotation_angle))
        view_matrix = np.dot(view_matrix, translate([x, y, z]))
        return view_matrix
    if key[pg.K_e]:
        view_matrix = translate([-x, -y, -z])
        view_matrix = np.dot(view_matrix, scale(1/approach))
        view_matrix = np.dot(view_matrix, translate([x, y, z]))
        return view_matrix
    if key[pg.K_a]:
        view_matrix = translate([-x, -y, -z])
        view_matrix = np.dot(view_matrix, rotate_y(-rotation_angle))
        view_matrix = np.dot(view_matrix, translate([x, y, z]))
        return view_matrix
    if key[pg.K_s]:
        view_matrix = translate([-x, -y, -z])
        view_matrix = np.dot(view_matrix, rotate_x(-rotation_angle))
        view_matrix = np.dot(view_matrix, translate([x, y, z]))
        return view_matrix
    if key[pg.K_d]:
        view_matrix = translate([-x, -y, -z])
        view_matrix = np.dot(view_matrix, rotate_y(rotation_angle))
        view_matrix = np.dot(view_matrix, translate([x, y, z]))
        return view_matrix
    
    return view_matrix_default

