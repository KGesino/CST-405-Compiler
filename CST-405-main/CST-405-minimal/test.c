int x;
int y;
int z;
int r;

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

int arr[3];
arr[0] = 5;
arr[1] = 10;
arr[2] = arr[0] + arr[1];
print(arr[2]);

/* ===== NEW: 2D ARRAY TESTS ===== */
int mat[2][3];      // Declare 2D array (2 rows, 3 columns)

/* Assign values directly */
mat[0][0] = 1;
mat[0][1] = 2;
mat[0][2] = 3;

mat[1][0] = 4;
mat[1][1] = 5;
mat[1][2] = 6;

/* Access and compute */
x = mat[0][1] + mat[1][2];
print(x);

/* Assign using computed indices */
y = 1;
z = 2;
mat[y][z] = mat[0][0] + mat[1][1];
print(mat[y][z]);

/* More arithmetic with array elements */
r = mat[1][0] + mat[1][1] + mat[1][2];
print(r);

/* Cross-check that mat[1][2] retained value */
print(mat[1][2]);
