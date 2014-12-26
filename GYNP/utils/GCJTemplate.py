import time

def read():
    while True:
        try:
            ret = map(int, raw_input().split())
            if len(ret) > 0: 
                return ret
        except:
            # import traceback
            # traceback.print_exc()
            pass

class GCJJob(object):
    def __init__(self, prob_name, solve_func):
        self.prob_name = prob_name
        self.solve_func = solve_func
        if self.prob_name in ['A', 'B', 'C', 'D']:
            self.write_filehandle = open(self.prob_name + '.out', 'w')
    def write(self, case_num, out_res, debug_mode):
        wstr = 'Case #%d: %s' % (case_num, str(out_res))
        try:
            self.write_filehandle.write(wstr + '\n')
            self.write_filehandle.flush()
            if debug_mode:
                print wstr
        except:
            # import traceback
            # traceback.print_exc()
            print wstr
    def run(self, debug_mode = False):
        start_tms = time.time()
        tot_casenum = input()
        for case_num in xrange(1, tot_casenum + 1):
            print 'NOTICE:: Solving problem %d/%d...' % (case_num, tot_casenum)
            self.write(case_num, self.solve_func(), debug_mode)
        print 'Used Time = %lfms' % (time.time() - start_tms)
        self.write_filehandle.close()
