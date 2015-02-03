set terminal png
set output 'aufg3.png'
plot 'aufg3.txt' u 1:2 w l title "numerisch", '' u 1:3 w l title "analytisch"
