int check(int x) {
    int y;
    y = x + 1;

    if (y > 5)
        y = y - 1;
    else
        y = 0;

    return y;
}

int loopfun(int n) {
    int i;
    i = 0;

    while (i < n)
        i = i + 1;

    return i;
}

void main() {
    int a;
    int b;

    a = check(7);
    b = loopfun(5);
}
