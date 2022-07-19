"""
This program measure the time for the computation.
"""

import subprocess
import time


if __name__=="__main__":

    st = time.time()
    cmd = 'ALOS_pre_process data/IMG-HH-ALPSRP207600640-H1.0__A data/LED-ALPSRP207600640-H1.0__A -V'
    subprocess.run(cmd, shell=True)
    ed = time.time()
    elapsed_time = ed - st
    print('elapsed time = ', elapsed_time)


    st = time.time()
    cmd = 'esarp data/IMG-HH-ALPSRP207600640-H1.0__A.PRM data/IMG-HH-ALPSRP207600640-H1.0__A.SLC'
    subprocess.run(cmd, shell=True)
    ed = time.time()
    elapsed_time = ed - st
    print('elapsed time = ', elapsed_time)


    st = time.time()
    cmd = './readRAWfromGMTSAR/build/readRAWfromGMTSAR'
    subprocess.run(cmd, shell=True)
    ed = time.time()
    elapsed_time = ed - st
    print('elapsed time = ', elapsed_time)

    print('done.')
