"""

"""

import glob
import subprocess

if __name__=='__main__':
    infilenames = glob.glob('data/*.bmp')

    for infilename in infilenames:
        #print(infilename)
        outfilename = infilename + '.png'
        modulationPercent = 400
        cmd = 'convert {0} -modulate {1} {2}'.format(infilename, modulationPercent, outfilename)
        print(cmd)

        subprocess.run(cmd, shell=True)

    print("done.")