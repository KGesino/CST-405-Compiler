int getNumber() {
    return 42;
}

int main() {
    int x, y, z, r;
    int arr[3];
    int mat[2][3];

    x = 10;
    y = 20;
    z = x + y;
    print(z);

    x = z + 5;
    print(x);

    y = x + y + z;
    print(y);

    r = x - 2;
    print(r);

    arr[0] = 5;
    arr[1] = 10;
    arr[2] = arr[0] + arr[1];
    print(arr[2]);

    /* 2D array */
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[1][0] = 4;
    mat[1][1] = 5;
    mat[1][2] = 6;

    x = mat[0][1] + mat[1][2];
    print(x);

    y = 1;
    z = 2;
    mat[y][z] = mat[0][0] + mat[1][1];
    print(mat[y][z]);

    r = mat[1][0] + mat[1][1] + mat[1][2];
    print(r);

    print(mat[1][2]);

    x = getNumber();
    print(x);

    return 0;
}
