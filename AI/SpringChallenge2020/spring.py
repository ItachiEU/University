import sys
import math
import collections

# width: size of the grid
# height: top left corner is (x=0, y=0)
width, height = [int(i) for i in input().split()]
last_pos = dict()
walls = set()
spaces = set()

for i in range(height):
    row = input()  # one line of the grid: space " " is floor, pound "#" is wall
    for j in range(len(row)):
        if row[j] == '#':
            walls.add((j, i))
        if row[j] == ' ':
            spaces.add((j, i))


def find_closest(start, pellet_positions, on_speed, out_of_bounds):
    vis = set()
    q = collections.deque()
    vis.add(start)

    q.append(start)
    potential_target = (0, 0)
    while len(q) > 0:
        pos = q.popleft()
        if pellet_positions.get(pos, (0, 0))[0] == 1:
            if on_speed and pos != out_of_bounds:
                if abs(start[0] - pos[0]) + abs(start[1] - pos[1]) >= 2:
                    return pos
                potential_target = pos
            elif pos != out_of_bounds:
                return pos

        if ((width + pos[0] - 1) % width, pos[1]) not in walls and ((width + pos[0] - 1) % width, pos[1]) not in vis and ((width + pos[0] - 1) % width, pos[1]) in spaces:
            #print('wszedlem', file=sys.stderr)
            q.append(((width + pos[0] - 1) % width, pos[1]))
            potential_target = ((width + pos[0] - 1) % width, pos[1])
            vis.add(((width + pos[0] - 1) % width, pos[1]))
        if ((pos[0] + 1) % width, pos[1]) not in walls and ((pos[0] + 1) % width, pos[1]) not in vis and ((pos[0] + 1) % width, pos[1]) in spaces:
            q.append(((pos[0] + 1) % width, pos[1]))
            potential_target = ((pos[0] + 1) % width, pos[1])
            vis.add(((pos[0] + 1) % width, pos[1]))
        if (pos[0], (height + pos[1] - 1) % height) not in walls and (pos[0], (height + pos[1] - 1) % height) not in vis and (pos[0], (height + pos[1] - 1) % height) in spaces:
            q.append((pos[0], (height + pos[1] - 1) % height))
            potential_target = (pos[0], (height + pos[1] - 1) % height)
            vis.add((pos[0], (height + pos[1] - 1) % height))
        if (pos[0], (pos[1] + 1) % height) not in walls and (pos[0], (pos[1] + 1) % height) not in vis and (pos[0], (pos[1] + 1) % height) in spaces:
            q.append((pos[0], (pos[1] + 1) % height))
            potential_target = (pos[0], (pos[1] + 1) % height)
            vis.add((pos[0], (pos[1] + 1) % height))

    print('tu', file=sys.stderr)
    return potential_target


def ruch(my_pacs, enemy_pacs, pellet_positions, on_speed, speed_turn):
    move = f''
    for pac in my_pacs:
        ID = pac[0]
        temp = pac[1]
        out_of_bounds = (-1, -1)
        if last_pos.get(ID, ((-1, -1), (-1, -1)))[0] == temp:
            # tutaj jakos ogarnac ze nie chcemy tego powtorzyc bo sie zdezylismy
            out_of_bounds = last_pos.get(ID, ((-1, -1), (-1, -1)))[1]
        if not speed_turn:
            pos = find_closest(temp, pellet_positions, on_speed, out_of_bounds)
            last_pos[ID] = (temp, pos)
            move += f'MOVE {ID} ' + f"{pos[0]} " + f"{pos[1]} |"
        else:
            move += f'SPEED {ID} |'
    print(move)


# game loop
while True:
    my_score, opponent_score = [int(i) for i in input().split()]
    visible_pac_count = int(input())  # all your pacs and enemy pacs in sight
    my_pacs = set()
    enemy_pacs = set()
    on_speed = False
    speed_turn = False
    for i in range(visible_pac_count):
        # pac_id: pac number (unique within a team)
        # mine: true if this pac is yours
        # x: position in the grid
        # y: position in the grid
        # type_id: unused in wood leagues
        # speed_turns_left: unused in wood leagues
        # ability_cooldown: unused in wood leagues
        pac_id, mine, x, y, type_id, speed_turns_left, ability_cooldown = input().split()
        pac_id = int(pac_id)
        mine = mine != "0"
        x = int(x)
        y = int(y)
        if mine:
            my_pacs.add((pac_id, (x, y)))
        else:
            enemy_pacs.add((pac_id, (x, y)))
        speed_turns_left = int(speed_turns_left)
        ability_cooldown = int(ability_cooldown)
        if ability_cooldown == 0 and mine == 1:
            speed_turn = True
        if speed_turns_left > 0:
            on_speed = True

    visible_pellet_count = int(input())  # all pellets in sight

    pellet_positions = dict()
    for i in range(visible_pellet_count):
        # value: amount of points this pellet is worth
        x, y, value = [int(j) for j in input().split()]
        pellet_positions[(x, y)] = (1, value)

    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr)

    # MOVE <pacId> <x> <y>

    #print("SPEED TURN: ", speed_turn, file=sys.stderr, flush=True)

    ruch(my_pacs, enemy_pacs, pellet_positions, on_speed, speed_turn)
