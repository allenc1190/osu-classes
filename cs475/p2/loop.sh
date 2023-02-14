for t in 1 2 4 8 12 16 24 32;
do
  for n in 1000 2000 3000 4000 5000 6000 7000;
  do
    g++ -O3   p2.cpp  -DNUMT=$t -DNUMNODES=$n  -o p2  -lm  -fopenmp
    ./p2
  done
done