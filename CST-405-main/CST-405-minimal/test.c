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

    /* =======================================================
     * BASIC FLOAT OPERATIONS
     * ======================================================= */
    x = 1.5;
    y = 2.25;
    z = x + y;             /* addition */
    print(z);

    r = z - 1.0;           /* subtraction */
    print(r);

    /* --- NEW: Float multiplication and division --- */
    z = x * y;             /* expect 3.375 */
    print(z);

    r = z / 2.0;           /* expect 1.6875 */
    print(r);

    /* --- NEW: Float division chain --- */
    x = 10.0;
    y = 2.0;
    z = x / y;             /* expect 5.0 */
    print(z);

    z = z / 2.0;           /* expect 2.5 */
    print(z);

    /* =======================================================
     * 1D FLOAT ARRAY
     * ======================================================= */
    arr[0] = 3.5;
    arr[1] = 4.5;
    arr[2] = arr[0] + arr[1];
    print(arr[2]);

    /* --- NEW: Array multiplication --- */
    arr[0] = arr[0] * 2.0;  /* 7.0 */
    print(arr[0]);

    arr[1] = arr[1] * arr[0];  /* 4.5 * 7.0 = 31.5 */
    print(arr[1]);

    /* =======================================================
     * 2D FLOAT ARRAY INITIALIZATION
     * ======================================================= */
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
    mat[0][1] = mat[0][0] + mat[1][1];
    print(mat[0][1]);

    r = mat[1][0] + mat[1][1] + mat[1][2];
    print(r);

    print(mat[1][2]);

    /* --- NEW: Matrix-based multiplication --- */
    mat[0][2] = mat[0][0] * mat[1][1];  /* 1.1 * 5.5 = 6.05 */
    print(mat[0][2]);

    mat[1][0] = mat[1][2] * 2.0;        /* 6.6 * 2 = 13.2 */
    print(mat[1][0]);

    /* =======================================================
     * FUNCTION CALLS RETURNING FLOATS
     * ======================================================= */
    z = getPi();
    print(z);

    x = addFloats(1.25, 2.75);
    print(x);

    /* =======================================================
     * INTEGER MULTIPLICATION AND DIVISION TESTS
     * ======================================================= */
    i = 10;
    j = 2;
    k = i * j;   /* expect 20 */
    print(k);

    k = i / j;   /* expect 5 */
    print(k);

    /* Mixed-type: multiply int and float */
    x = i * 2.5;    /* expect 25.0 */
    print(x);

    y = 7.5 * i;    /* expect 75.0 */
    print(y);

    /* =======================================================
     * IF STATEMENT TESTS
     * ======================================================= */

    /* Simple if without else */
    if (x > 2.0) {
        print(100.0);
    }

    /* If with else */
    if (x < 3.0) {
        print(200.0);
    } else {
        print(300.0);
    }

    /* Nested if */
    if (r > 10.0) {
        if (r < 20.0) {
            print(400.0);
        } else {
            print(500.0);
        }
    } else {
        print(600.0);
    }

    /* If comparing integers */
    if (i == 10) {
        print(700.0);
    } else {
        print(800.0);
    }

    /* Compound if expression */
    if ((x + y) > (r - 10.0)) {
        print(900.0);
    } else {
        print(1000.0);
    }

    /* =======================================================
     * BOOLEAN TESTS
     * ======================================================= */

    flag1 = true;
    flag2 = false;
    resultBool = !flag2;  /* should be true */
    if (resultBool) {
        print(1100.0);
    }

    if (flag1 && flag2) {
        print(1200.0);
    } else {
        print(1300.0);
    }

    if (flag1 || flag2) {
        print(1400.0);
    } else {
        print(1500.0);
    }

    resultBool = (flag1 && (x > 0.0)) || (r < 5.0);
    if (resultBool) {
        print(1600.0);
    } else {
        print(1700.0);
    }

    flag1 = (x < r);
    flag2 = !(z > y);
    if (flag1 && flag2) {
        print(1800.0);
    } else {
        print(1900.0);
    }

    /* =======================================================
     * WHILE LOOP TESTS
     * ======================================================= */

    i = 0;
    while (i < 3) {
        print(3000.0 + i);
        i = i + 1;
    }

    j = 5;
    while (j > 0) {
        print(4000.0 + j);
        j = j - 1;
    }

    /* Nested while with if */
    i = 0;
    while (i < 2) {
        j = 0;
        while (j < 2) {
            if (i == j) {
                print(5000.0 + i * 10 + j);
            } else {
                print(5100.0 + i * 10 + j);
            }
            j = j + 1;
        }
        i = i + 1;
    }



    return 0;
}
