float getPi() {
    return 3.14159;
}

float addFloats(float a, float b) {
    float result;
    result = a + b;
    return result;
}

int main() {
    int i;
    float x, y, z, r;
    float arr[3];
    float mat[2][3];

    /* Basic float ops */
    x = 1.5;
    y = 2.25;
    z = x + y;
    print(z);

    r = z - 1.0;
    print(r);

    /* 1D float array */
    arr[0] = 3.5;
    arr[1] = 4.5;
    arr[2] = arr[0] + arr[1];
    print(arr[2]);

    /* 2D float array initialization */
    mat[0][0] = 1.1;
    mat[0][1] = 2.2;
    mat[0][2] = 3.3;
    mat[1][0] = 4.4;
    mat[1][1] = 5.5;
    mat[1][2] = 6.6;

    /* Simple load and arithmetic */
    x = mat[0][1] + mat[1][2];
    print(x);

    y = 0.0;
    z = 1.0;
    mat[0][1] = mat[0][0] + mat[1][1];  /* removed (int) casts */
    print(mat[0][1]);

    r = mat[1][0] + mat[1][1] + mat[1][2];
    print(r);

    print(mat[1][2]);

    /* Function calls returning floats */
    z = getPi();
    print(z);

    x = addFloats(1.25, 2.75);
    print(x);

    return 0;
}
