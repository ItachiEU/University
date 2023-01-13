# Zadanie 1

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import random

fig, ax = plt.subplots()
fig.set_size_inches(10, 10)
ax.set_title("Snake")
ax.set_facecolor('black')
ax.set_xticks([x for x in range(0, 10)])
ax.set_yticks([y for y in range(0, 10)])

squares = [(random.randint(0, 10), random.randint(0, 10)) for _ in range(5)]
ax.scatter([x for x, y in squares], [
           y for x, y in squares], color='red', marker='s', s=100)

snake = [(5, 5), (5, 6), (5, 7)]

direction = random.choice(['right', 'left', 'up', 'down'])
speed = 0.5


def update(num):
    global snake, squares, direction, speed, fig

    head = snake[0]
    if direction == 'right':
        new_head = (head[0] + 1, head[1])
    elif direction == 'left':
        new_head = (head[0] - 1, head[1])
    elif direction == 'up':
        new_head = (head[0], head[1] + 1)
    elif direction == 'down':
        new_head = (head[0], head[1] - 1)

    # let's make sure the snake doesn't change direction every single move
    if random.random() < 0.4:
        if direction in ['right', 'left']:
            direction = random.choice(['up', 'down'])
        else:
            direction = random.choice(['left', 'right'])

    if new_head[0] < 0 or new_head[0] > 9 or new_head[1] < 0 or new_head[1] > 9:
        print('Game Over!')
        ani.event_source.stop()
        return

    snake.insert(0, new_head)
    snake.pop()
    ax.clear()
    ax.scatter([x for x, y in squares], [
        y for x, y in squares], color='red', marker='s', s=100)
    ax.plot([x for x, y in snake], [y for x, y in snake],
            color='green', linewidth=5)

    if set(snake).intersection(set(squares)):
        print('Game Over!')
        ani.event_source.stop()
        return


ani = animation.FuncAnimation(
    fig, update, frames=None, interval=int(1000 * speed))

plt.gca().set_title("test")
plt.show()
