set terminal png

set yrange [-1.5:1.5]

set output 'aufg1_stoerm.png'
plot 'stoerm.txt' w l

set output 'aufg1_dopr.png'
plot 'dopr.txt' w l
