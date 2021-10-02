from cylinder import *
from matrix_functions import *
from camera import check_key_press


def main():
    pg.init()
    screen = pg.display.set_mode((WIDTH, HEIGHT))   
    clock = pg.time.Clock()

    base_bottom, base_top = get_cylinder(20, WIDTH / 8, HEIGHT / 2)

    while True:
        screen.fill(BLACK)
        
        view_matrix = check_key_press()
        pg.event.pump()
        for i in range(len(base_bottom)):
            base_bottom[i] = np.dot(base_bottom[i], view_matrix)
            base_top[i] = np.dot(base_top[i], view_matrix)

        draw(screen, base_bottom, base_top)

        pg.display.set_caption(str(clock.get_fps()))
        pg.display.update()
        clock.tick(FPS)
 
        
if __name__ == "__main__":
    main()