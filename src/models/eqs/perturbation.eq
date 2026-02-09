extern MY_FLOAT e1, e2, coef[10], freq[10];

diff(x,t) = e1 * y;
diff(y,t) = -x + e2*sum( coef[i] * sin( freq[i] * t), i = 0, 9);