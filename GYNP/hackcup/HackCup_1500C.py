import sys
sys.path.append('../')

from utils.GCJTemplate import *
import Queue

laser_char = ['^', '>', 'V', '<']
laser_dir = [(-1, 0), (0, 1), (1, 0), (0, -1)]

INF = 1000000

def solve():
    N, M = read_int()
    maze = [raw_input() for i in xrange(N)]

    can_visit = make_array(True, (4, N, M))
    can_reach = lambda x, y: x >= 0 and x < N and y >= 0 and y < M and \
        maze[x][y] != '#' and maze[x][y] not in laser_char

    def mark(t, x, y, d):
        step = 1
        while can_reach(x + laser_dir[d][0] * step, y + laser_dir[d][1] * step):
            can_visit[t][x + laser_dir[d][0] * step][y + laser_dir[d][1] * step] = False
            step += 1

    for i in xrange(N):
        for j in xrange(M):
            if maze[i][j] in laser_char:
                laser_type = laser_char.index(maze[i][j])
                for t in xrange(4):
                    mark(t, i, j, (laser_type + t) % 4)
            elif maze[i][j] == 'S':
                sx, sy = i, j
            elif maze[i][j] == 'G':
                gx, gy = i, j

    # if not can_visit[0][sx][sy]:
    #     return 'impossible'

    min_step = make_array(INF, (4, N, M))
    q = Queue.Queue()

    def pushQ(t, x, y, step):
        q.put((t, x, y))
        min_step[t][x][y] = step

    pushQ(0, sx, sy, 0)
    while not q.empty():
        cstate = q.get()
        cstep = min_step[cstate[0]][cstate[1]][cstate[2]]
        for d in xrange(4):
            nt, nx, ny = (cstate[0] + 1) % 4, cstate[1] + laser_dir[d][0], cstate[2] + laser_dir[d][1]
            if can_reach(nx, ny) and can_visit[nt][nx][ny] and min_step[nt][nx][ny] == INF:
                pushQ(nt, nx, ny, cstep + 1)

    ret = min(min_step[0][gx][gy], min_step[1][gx][gy], min_step[2][gx][gy], min_step[3][gx][gy])
    return ret if ret != INF else 'impossible'

GCJJob('C', solve).run(True)
