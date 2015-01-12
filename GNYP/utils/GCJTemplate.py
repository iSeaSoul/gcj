import time

def read_int():
    while True:
        try:
            ret = map(int, raw_input().split())
            if len(ret) > 0: 
                return ret
        except:
            pass

def read_double():
    while True:
        try:
            ret = map(float, raw_input().split())
            if len(ret) > 0: 
                return ret
        except:
            pass

def make_array(val, dim):
    '''
    Usage: make_array(-1, (2, 3))
    '''
    return [val if len(dim) == 1 else make_array(val, dim[1:]) for i in xrange(dim[0])]

def idle():
    pass

class GCJJob(object):
    def __init__(self, prob_name, solve_func):
        self.prob_name = prob_name
        self.solve_func = solve_func
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
    def run(self, debug_mode=False):
        start_tms = time.time()
        tot_casenum = input()
        for case_num in xrange(1, tot_casenum + 1):
            print 'NOTICE:: Solving problem %d/%d...' % (case_num, tot_casenum)
            self.write(case_num, self.solve_func(), debug_mode)
        print 'Used Time = %.3lfms' % (time.time() - start_tms)
        self.write_filehandle.close()
