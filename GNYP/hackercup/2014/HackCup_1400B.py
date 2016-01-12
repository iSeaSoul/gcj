import sys
sys.path.append('../../')

from utils import GCJTemplate as gt

def read_player():
    player_name, sp, h = raw_input().split()
    return player_name, int(sp), int(h)

def simulate_game(np, nm, nop):
    play_time = [0 for i in xrange(np)]
    playing = [False for i in xrange(np)]

    for i in xrange(nop):
        play_time[i] += 1
        playing[i] = True

    for tm in xrange(nm):
        max_playing_tm = -1
        max_playing_id = -1
        min_non_playing_tm = nm
        min_non_playing_id = -1
        for i in xrange(np):
            if playing[i]:
                if play_time[i] >= max_playing_tm:
                    max_playing_tm = play_time[i]
                    max_playing_id = i
            else:
                if play_time[i] < min_non_playing_tm:
                    min_non_playing_tm = play_time[i]
                    min_non_playing_id = i

        playing[max_playing_id] = False
        playing[min_non_playing_id] = True
        for i in xrange(np):
            if playing[i]:
                play_time[i] += 1

    playing_ids = []
    for i in xrange(np):
        if playing[i]:
            playing_ids.append(i)

    return playing_ids

def solve():
    n_players, n_minutes, n_on_players = gt.read_int()
    players = sorted([read_player() for i in xrange(n_players)],\
            key = lambda player: (player[1], player[2]), \
            reverse = True)

    # for player in players: print player

    final_names = []
    for final_id in simulate_game((n_players + 1) >> 1, n_minutes, n_on_players):
        final_names.append(players[final_id << 1][0])

    for final_id in simulate_game(n_players >> 1, n_minutes, n_on_players):
        final_names.append(players[(final_id << 1) | 1][0])

    return ' '.join(sorted(final_names))

gt.GCJJob('HackCup_1400B', solve).run(True)
