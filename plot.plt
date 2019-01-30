set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.5
set pm3d

stats 'out.txt' nooutput

do for [a = 1: int(STATS_blocks - 1)] {
    splot x**2+y**2 + (x**2/2+y**2)**2 + (x**2/2+y**2)**4, 'out.txt' index a u 1:2:3 with linespoints linestyle 1;
    pause 1;
}