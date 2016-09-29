set title "compute-pi"
set xlabel "N"
set ylabel "Time(second)"
set term png enhanced font 'Verdana,10'
set datafile separator ","
set output 'runtime.png'

plot  "result_clock_gettime.csv" using 1:2 title 'baseline' with lines lt rgb 'blue' , \
"result_clock_gettime.csv" using 1:4 title 'openmp_2' with lines lt rgb 'red' , \
"result_clock_gettime.csv" using 1:6 title 'openmp_4' with lines lt rgb 'orange' , \
"result_clock_gettime.csv" using 1:8 title 'avx' with lines lt rgb 'green' , \
"result_clock_gettime.csv" using 1:10 title 'avxunroll' with lines lt rgb 'purple'


set xlabel 'N'
set ylabel 'Error'
set logscale y
set style fill solid
set title 'Compute_pi Error'
set term png enhanced font 'Verdana,10'
set xrange[0:300000]
set output 'error.png'

plot "result_clock_gettime.csv" using 1:3 title 'baseline' with lines lt rgb 'blue', \
     "result_clock_gettime.csv" using 1:5 title 'openmp_2' with lines lt rgb 'red', \
     "result_clock_gettime.csv" using 1:7 title 'openmp_4' with lines lt rgb 'orange', \
     "result_clock_gettime.csv" using 1:7 title 'avx' with lines lt rgb 'green', \
     "result_clock_gettime.csv" using 1:7 title 'avxunroll' with lines lt rgb 'purple', \



