int main() {
    int a, b, c, d;

    a = 10;
    b = 5;
    c = 20;
    d = 10;

    while ((a > b) * (c > d)) {
        write('r');
        write('=');
        write((a > b) * (c > d));
        writeln;
        a = a - 1;
    }

    return 0;
}
