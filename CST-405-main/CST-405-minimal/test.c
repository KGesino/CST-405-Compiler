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
    bool flag1, flag2, resultBool;

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
    mat[0][1] = mat[0][0] + mat[1][1];
    print(mat[0][1]);

    r = mat[1][0] + mat[1][1] + mat[1][2];
    print(r);

    print(mat[1][2]);

    /* Function calls returning floats */
    z = getPi();
    print(z);

    x = addFloats(1.25, 2.75);
    print(x);

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
    i = 5;
    if (i == 5) {
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

    /* Basic boolean assignment and printing */
    flag1 = true;
    flag2 = false;
    resultBool = !flag2;  /* should be true */
    if (resultBool) {
        print(1100.0);
    }

    /* AND / OR logic tests */
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

    /* Compound boolean expressions */
    resultBool = (flag1 && (x > 0.0)) || (r < 5.0);
    if (resultBool) {
        print(1600.0);
    } else {
        print(1700.0);
    }

    /* Boolean with relational chaining */
    flag1 = (x < r);
    flag2 = !(z > y);
    if (flag1 && flag2) {
        print(1800.0);
    } else {
        print(1900.0);
    }

    return 0;
}
