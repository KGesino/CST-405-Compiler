float getPi() {
    return 3.14159;
}

float addFloats(float a, float b) {
    float result;
    result = a + b;
    return result;
}

int main() {
    int i, j, k;
    float x, y, z, r;
    float arr[3];
    float mat[2][3];
    bool flag1, flag2, resultBool;

    /* Basic float ops */
    x = 1.5;
    y = 2.25;
    z = x + y;
    print(z);

    r = z - 1.0;
    print(r);

    /* Multiplication tests */
    z = x * y;         /* expect 3.375 */
    print(z);

    r = z * 2.0;       /* expect 6.75 */
    print(r);

    /* 1D float array */
    arr[0] = 3.5;
    arr[1] = 4.5;
    arr[2] = arr[0] * arr[1];
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

    mat[0][2] = mat[0][0] * mat[1][1];
    print(mat[0][2]);

    /* Function calls returning floats */
    z = getPi();
    print(z);

    x = addFloats(1.25, 2.75);
    print(x);

    /* Simple integer multiplication */
    i = 5;
    j = 3;
    k = i * j;  /* expect 15 */

    /* Instead of print((float)k); just assign it to a float */
    x = k;
    print(x);

    return 0;
}
