set title "compute-pi"
set xlabel "N"
set ylabel "Time(second)"
set term png enhanced font 'Verdana,10'
set datafile separator ","
set output 'runtime.png'

plot  "result_clock_gettime.csv" using 1:2 title 'baseline' with lines lt rgb 'blue' , \
"result_clock_gettime.csv" using 1:3 title 'openmp_2' with lines lt rgb 'red' , \
"result_clock_gettime.csv" using 1:4 title 'openmp_4' with lines lt rgb 'orange' , \
"result_clock_gettime.csv" using 1:5 title 'avx' with lines lt rgb 'green' , \
"result_clock_gettime.csv" using 1:6 title 'avxunroll' with lines lt rgb 'purple'
