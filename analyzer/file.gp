set term png
set output "Analyzer.png"
set title "Analyzer"
set xlabel "bandwidth"
set ylabel "CPU Usage
set grid
set style line 22 linetype 3 linewidth 4
plot "file.out" using 1:2 title "Example" with linespoints
