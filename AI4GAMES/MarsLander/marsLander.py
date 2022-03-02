import sys
import math
import numpy as np
import time


GRAVITY = -3.711


def next_state(
    x: float,
    y: float,
    h_speed: float,
    v_speed: float,
    fuel: int,
    angle: int,
    power: int,
    new_angle: int,
    new_power: int
) -> tuple:
    assert new_power <= 1 and new_power >= - \
        1, f"Wrong new_power -> {new_power}"
    power += new_power
    power = max(0, power)
    power = min(4, power)
    assert power in np.arange(0, 5), f"Wrong power -> {power}"
    fuel -= power
    assert new_angle <= 15 and new_angle >= - \
        15, f"Wrong new_angle -> {new_angle}"
    angle += new_angle
    angle = max(-90, angle)
    angle = min(90, angle)
    assert new_angle <= 90 and new_angle >= -90, f"Wrong angle -> {angle}"

    radians = (angle * math.pi) / 180.0
    a_h = -math.sin(radians) * power  # horizontal acceleration
    a_v = math.cos(radians) * power + GRAVITY  # vertical acceleration

    x += h_speed + a_h / 2.0  # delta x
    y += v_speed + a_v / 2.0  # delta y

    h_speed += a_h
    v_speed += a_v
    return x, y, h_speed, v_speed, fuel, angle, power


def get_function_params(x1, y1, x2, y2):
    a = (y1 - y2) / (x1 - x2)
    b = y1 - a * x1
    return a, b


def create_map_points(input_surface):
    result_map = {}
    for i in range(len(input_surface)-1):
        x, y = input_surface[i]
        x2, y2 = input_surface[i+1]
        a, b = get_function_params(x, y, x2, y2)
        for x_i in range(x, x2+1):
            result_map[x_i] = a * x_i + b
    return result_map

# helper functions


def determine_dist_reward(lx1, lx2, ly, x, y, x_start, y_start):
    max_dist_x = 0
    max_dist_y = 0
    close_x = 0
    if lx1 <= x <= lx2:
        close_x = 0
    else:
        close_x = min(abs(x - lx1), abs(x - lx2)) ** 2

    max_dist_x = min(abs(x_start - lx1), abs(x_start - lx2)) ** 2
    close_y = (y - ly) ** 2
    max_dist_y = (y_start - ly) ** 2

    max_dist = np.sqrt(max_dist_x + max_dist_y)
    act_dist = np.sqrt(close_x + close_y)

    return (1 - act_dist / max_dist) * 100


def determine_angle_reward(angle):
    if angle == 0:
        return 200
    return ((90-abs(angle))/90)*100


def intersection(x, y, map):
    return y < map[int(x)]


def find_landing(map_input):
    for i in range(len(map_input) - 1):
        if map_input[i][1] == map_input[i + 1][1] and abs(map_input[i][0] - map_input[i + 1][0]) >= 1000:
            return map_input[i][0], map_input[i + 1][0], map_input[i + 1][1]


def simulate_run(
    actions,
    x=2500,
    y=2700,
    map=map_points,
    h_speed=0,
    v_speed=0,
    fuel=5501,
    angle=0,
    power=0,
    landing_x1=4000,
    landing_x2=5500,
    landing_y=150
):
    x_start, y_start = x, y

    crash = False
    path = [(x, y)]
    for new_angle, new_power in actions:
        new_angle = int(round(new_angle))
        new_power = int(round(new_power))
        x_new, y_new, h_speed_new, v_speed_new, fuel_new, angle_new, power_new = next_state(
            x, y, h_speed, v_speed, fuel, angle, power, new_angle, new_power)
        if fuel <= 0 or x_new < 0 or y_new < 0 or x_new >= 7000 or y_new >= 2800 or intersection(x_new, y_new, map):
            path.append((x_new, y_new))
            crash = True
            break

        x, y, h_speed, v_speed, fuel, angle, power = x_new, y_new, h_speed_new, v_speed_new, fuel_new, angle_new, power_new
        path.append((x, y))

    distance_reward = determine_dist_reward(
        landing_x1, landing_x2, landing_y, x, y, x_start, y_start)
    angle_reward = determine_angle_reward(angle)
    if abs(v_speed) <= 40:
        v_speed_reward = 1000
    else:
        crash = True
        v_speed_reward = 0

    if abs(h_speed) <= 20:
        h_speed_reward = 1000
    else:
        crash = True
        h_speed_reward = 0

    total_reward = distance_reward*10 + angle_reward + v_speed_reward + h_speed_reward
    if crash:
        total_reward -= 1000
    return total_reward, path


class Node:
    def __init__(self, action, parent) -> None:
        self._current_action = action  # pair[int, int]  angle and power
        self._children = {}  # dict[action, Node]
        self._score = -1e18
        self._visited = 0
        self._parent = parent

    def _backpropagate(self, score):
        individual_score = 0
        iters = 0
        while self._parent is not None:
            self._visited += 1
            self._score = max(self._score, score)
            iters += 1
            individual_score += self._score
            self = self._parent
        return individual_score / iters

    def rollout(
        self,
        genotype: np.ndarray,
        x: int, y: int,
        h_speed: int, v_speed: int,
        fuel: int, angle: int, power: int,
        map_points: list,
        landing_x1=4000,
        landing_x2=5500,
        landing_y=150
    ) -> float:
        x_start, y_start = x, y
        crash = False

        # do the actions from previous nodes:

        for new_angle, new_power in actions:
            new_angle = int(round(new_angle))
            new_power = int(round(new_power))
            x2, y2, h_speed2, v_speed2, fuel2, angle2, power2 = next_state(
                x=x, y=y, h_speed=h_speed, v_speed=v_speed, fuel=fuel, angle=angle, power=power,
                new_angle=new_angle, new_power=new_power
            )
            if fuel <= 0 or x2 < 0 or x2 >= 7000 or y2 > 2800 or intersection(x2, y2, map_points):
                if abs(v_speed2) >= 40 or abs(h_speed2) >= 20 or abs(h_speed) >= 20 or abs(v_speed) >= 40 or x2 < landing_x1 or x2 > landing_x2 or angle != 0 or new_angle != 0 or abs(y2 - landing_y) > 1:
                    crash = True
                break
            x, y, h_speed, v_speed, fuel, angle, power = x2, y2, h_speed2, v_speed2, fuel2, angle2, power2

        # rollout new genotype
        next_node = self
        for new_angle, new_power in genotype:
            new_angle = int(round(new_angle))
            new_power = int(round(new_power))
            # assert isinstance(new_angle, np.int64) and isinstance(new_power, np.int64), f"{new_angle} {new_power} {type(new_angle)} {type(new_power)}"
            x2, y2, h_speed2, v_speed2, fuel2, angle2, power2 = next_state(
                x=x, y=y, h_speed=h_speed, v_speed=v_speed, fuel=fuel, angle=angle, power=power,
                new_angle=new_angle, new_power=new_power
            )
            if fuel <= 0 or x2 < 0 or x2 >= 7000 or y2 > 2800 or intersection(x2, y2, map_points):
                if abs(v_speed2) >= 40 or abs(h_speed2) >= 20 or abs(h_speed) >= 20 or abs(v_speed) >= 40 or x2 < landing_x1 or x2 > landing_x2 or angle != 0 or new_angle != 0 or abs(y2 - landing_y) > 1:
                    crash = True
                break
            x, y, h_speed, v_speed, fuel, angle, power = x2, y2, h_speed2, v_speed2, fuel2, angle2, power2

            new_angle, new_power = int(
                round(new_angle)),  int(round(new_power))

            if (new_angle, new_power) in self._children:
                next_node = self._children[(new_angle, new_power)]
            else:
                self._children[(new_angle, new_power)] = Node(
                    action=(new_angle, new_power), parent=self)
                next_node = self._children[(new_angle, new_power)]

        distance_reward = determine_dist_reward(
            landing_x1, landing_x2, landing_y, x, y, x_start, y_start)
        angle_reward = determine_angle_reward(angle)
        if abs(v_speed) <= 40:
            v_speed_reward = 1000
        else:
            crash = True
            v_speed_reward = 0

        if abs(h_speed) <= 20:
            h_speed_reward = 1000
        else:
            crash = True
            h_speed_reward = 0

        score = distance_reward * 5 + angle_reward + \
            v_speed_reward * 2 + h_speed_reward * 2
        if crash:
            score -= 1000000

        return next_node._backpropagate(score=score)


actions = []


class RHEA:
    def __init__(self, N, chromosome_len=20, n_mutations=5):
        self._N: int = N
        self._d: int = chromosome_len
        self.n_mutations: int = n_mutations
        self._best_individual = None
        self._best_cost = -1e18
        self._scores = np.ones(N)
        self.node = Node(action=None, parent=None)
        self.cost_history = []  # List[Tuple[min, mean, max]]
        self.population_std = []
        self.population_angles = np.random.randint(
            low=-15,
            high=16,
            size=(self._N, self._d)
        )
        # 1 - increase thrust | 0 - nothing | -1 - decrease thrust
        self.population_thrust = np.random.randint(
            low=1,
            high=2,
            size=(self._N, self._d)
        )
        self.population = np.stack(
            (self.population_angles, self.population_thrust), axis=2)

    def _parents_selection(self) -> np.ndarray:
        """ Roulette method """
        fitness_values = self._scores.copy()
        fitness_values = fitness_values - fitness_values.min()
        if fitness_values.sum() > 0:
            fitness_values = fitness_values / fitness_values.sum()
        else:
            fitness_values = np.ones(
                len(self.population)) / len(self.population)

        ids = np.random.choice(
            np.arange(self._N),
            size=self._N,
            replace=True,
            p=fitness_values
        )
        return ids

    def _replacement_and_crossover(self, ids) -> None:
        self.population = self.population[ids]

        parents_ids = np.arange(self._N)
        np.random.shuffle(parents_ids)

        p1 = self.population[parents_ids[self._N // 2]]
        p2 = self.population[self._N // 2:]

        r = np.random.rand(self._N // 2)[:, np.newaxis, np.newaxis]
        children1 = r * p1 + (1 - r) * p2
        children2 = (1 - r) * p1 + r * p2

        self.population = np.vstack((children1, children2))
        self.population[:, :, 1] = np.round(
            self.population[:, :, 1]).astype(np.int)

    def _mutation(self) -> None:
        random_indices = np.random.randint(
            0, self._d, size=(self.n_mutations, self._N))

        self.population[:, :, 0][np.arange(
            self._N), random_indices] = np.random.uniform(-15, 15, size=self._N)
        self.population[:, :, 1][np.arange(
            self._N), random_indices] = np.random.randint(-1, 2, size=self._N)

    def run(self, x: int, y: int,
            h_speed: int, v_speed: int,
            fuel: int, angle: int, power: int,
            map_points: list,
            l: int, r: int, h: int):
        start_time = time.time()
        while time.time() - start_time < 0.9:  # here we can put the time constraint
            # evaluate current population
            self.population_rollout(
                x, y, h_speed, v_speed, fuel, angle, power, map_points, l, r, h)

            best_cost_index = self._scores.argmax()
            best_current_individual = self.population[best_cost_index]
            if self._scores[best_cost_index] > self._best_cost:
                self._best_cost = self._scores[best_cost_index]
                self._best_individual = best_current_individual

            parents_ids = self._parents_selection()
            self._replacement_and_crossover(ids=parents_ids)
            self._mutation()
            self.population[self._scores.argmin(
            )] = best_current_individual

        action = self._best_individual[0]
        actions.append(action)

        if tuple(action) in self.node._children:
            self.node = self.node._children[tuple(action)]
        else:
            self.node._children[tuple(action)] = Node(
                action=tuple(action), parent=self.node)
            self.node = self.node._children[tuple(action)]

        # rolling best individual
        self._best_individual = self._best_individual[1:]
        self._best_individual = np.stack((np.append(self._best_individual[:, 0], np.random.randint(
            low=-15, high=16)), np.append(self._best_individual[:, 1], np.random.randint(low=-1, high=2))), axis=1)
        # rolling population
        # self.population = np.delete(self.population, 0, 1)
        # self._best_cost = -1e18
        temp = []
        for arr in self.population:
            t = list(arr)[1:]
            t.append([np.random.randint(low=-15, high=16),
                      np.random.randint(low=-1, high=2)])
            temp.append(t)
        self.population = np.array(temp)

    def population_rollout(
        self,
        x: int, y: int,
        h_speed: int, v_speed: int,
        fuel: int, angle: int, power: int,
        map_points: list,
        l: int, r: int, h: int
    ):
        scores = []
        for individual in self.population:
            individual_score = self.node.rollout(
                genotype=individual,
                x=x, y=y,
                h_speed=h_speed, v_speed=v_speed,
                fuel=fuel, angle=angle, power=power,
                map_points=map_points,
                landing_x1=l, landing_x2=r, landing_y=h
            )
            scores.append(individual_score)
        self._scores = np.array(scores)


MAP = []

n = int(input())  # the number of points used to draw the surface of Mars.
for i in range(n):
    # land_x: X coordinate of a surface point. (0 to 6999)
    # land_y: Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
    land_x, land_y = [int(j) for j in input().split()]
    MAP.append((land_x, land_y))

map_points = create_map_points(MAP)

CHROMOSOME_LEN = 60
actions = []
model = RHEA(N=20, chromosome_len=CHROMOSOME_LEN, n_mutations=2)

landing_x1, landing_x2, landing_y = find_landing(MAP)
x_start, y_start, h_speed_start, v_speed_start, fuel_start, angle_start, power_start = None, None, None, None, None, None, None

# game loop
k = 0
while True:
    # hs: the horizontal speed (in m/s), can be negative.
    # vs: the vertical speed (in m/s), can be negative.
    # f: the quantity of remaining fuel in liters.
    # r: the rotation angle in degrees (-90 to 90).
    # p: the thrust power (0 to 4).
    x, y, hs, vs, f, r, p = [int(i) for i in input().split()]

    if x_start == None:
        x_start, y_start, h_speed_start, v_speed_start, fuel_start, angle_start, power_start = x, y, hs, vs, f, r, p
    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr, flush=True)
    model.run(x=x_start, y=y_start,
              h_speed=h_speed_start, v_speed=v_speed_start,
              fuel=fuel_start, angle=angle_start, power=power_start,
              map_points=map_points,
              l=landing_x1, r=landing_x2, h=landing_y)
    # R P. R is the desired rotation angle. P is the desired thrust power.
    print(
        f"{max(-90, min(r + int(round(actions[k][0])), 90))} {min(4, max(0, p + int(round(actions[k][1]))))}")
    k += 1
