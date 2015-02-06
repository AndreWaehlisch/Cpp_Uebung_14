set terminal png

set output 'aufg2_isotrop_1.png'
plot 'step001.txt' w l

set output 'aufg2_isotrop_2.png'
plot 'step005.txt' w l

set output 'aufg2_isotrop_3.png'
plot 'step030.txt' w l

set ylabel 'norm'
set output 'aufg2_isotrop.png'
plot 'aufg2.txt' w l
