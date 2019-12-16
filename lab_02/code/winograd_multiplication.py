import random
def mult_matrix_winograd(matrix_1, matrix_2):
    num_row_1 = len(matrix_1)       #a
    num_col_1 = len(matrix_1[0])    #b
    num_row_2 = len(matrix_2)       #b
    num_col_2 = len(matrix_2[0])    #c

    if (num_col_1 != num_row_2):
        return

    d = num_col_1 // 2

    row_factor = [0 for i in range (num_row_1)]
    col_factor = [0 for i in range (num_col_2)]

    for i in range(num_row_1):
        for j in range(d):
            row_factor[i] += matrix_1[i][j * 2] * matrix_1[i][j * 2 + 1]

    for i in range (num_col_2):
        for j in range (d):
            col_factor[i] += matrix_2[j * 2][i] * matrix_2[j * 2 + 1][i]

    res_matrix = [[0 for i in range (num_col_2)] for i in range (num_row_1)]

    for i in range (num_row_1):
        for j in range (num_col_2):
            res_matrix[i][j] = -row_factor[i] - col_factor[j]
            for k in range (d):
                res_matrix[i][j] += (matrix_1[i][k * 2 + 1] + matrix_2[2 * k][j]) * (matrix_1[i][k * 2] + matrix_2[2 * k + 1][j])
                if (num_col_1 % 2):
                    res_matrix[i][j] += matrix_1[i][num_col_1 - 1] * matrix_2[num_col_1 - 1][j]

   # if (num_col_1 % 2):
    #    for i in range (num_row_1):
     #       for j in range (num_col_2):
      #          res_matrix[i][j] += matrix_1[i][num_col_1] * matrix_2[num_col_1][j]

    return res_matrix

def mult_matrix(matrix_1, matrix_2):
    a = len(matrix_1)
    b = len(matrix_1[0])
    c = len(matrix_2[0])

    if (len(matrix_2) != b):
        return

    res_matrix = [[0 for i in range (c)] for j in range (a)]

    for i in range (a):
        for j in range (b):
            for k in range (c):
                res_matrix[i][k] += matrix_1[i][j] * matrix_2[j][k]

    return res_matrix

def mult_matrix_winograd_mod(matrix_1, matrix_2):
    num_row_1 = len(matrix_1)       #a
    num_col_1 = len(matrix_1[0])    #b
    num_row_2 = len(matrix_2)       #b
    num_col_2 = len(matrix_2[0])    #c

    if (num_col_1 != num_row_2):
        return

    row_factor = [0 for i in range (num_row_1)]
    col_factor = [0 for i in range (num_col_2)]

    for i in range(0, num_row_1):
        for j in range(1, num_col_1, 2):
            row_factor[i] -= matrix_1[i][j] * matrix_1[i][j - 1]

    for j in range(0, num_col_2):
        for i in range(1, num_col_1, 2):
            col_factor[j] -= matrix_2[i][j] * matrix_2[i - 1][j]

    res_matrix = [[0 for i in range (num_col_2)] for i in range (num_row_1)]

    for i in range(0, num_row_1):
        for j in range(0, num_col_2):
            res_matrix[i][j] = row_factor[i] + col_factor[j]
            for k in range(1, num_col_1, 2):
                res_matrix[i][j] += (matrix_1[i][k - 1] + matrix_2[k][j]) * (matrix_1[i][k] + matrix_2[k - 1][j])
            if (1 == num_col_1 % 2):
                res_matrix[i][j] += matrix_1[i][num_col_1 - 1] * matrix_2[num_col_1 - 1][j]

    return res_matrix

def rand_matrix(m, n):
    matrix = [[0] * n for i in range(m)]

    for i in range(0, m):
        for j in range(0, n):
            matrix[i][j] = random.randint(-10, 10)

    return matrix

def print_matrix(m):
    for i in range(len(m)):
        for j in range(len(m[0])):
            print(m[i][j], end = ' ')
        print()

def main():
    a = [[1,2], [45, 11]]
    b = [[11, 11], [12, 3]]

    print("M_1 = [n1 * m1]")
    n1 = int(input("n1: "))
    m1 = int(input("m1: "))

    print("M_2 = [n2 * m2]")
    n2 = int(input("n2: "))
    m2 = int(input("m2: "))

    if (m1 != n2):
        print("Ошибка!")
        return -1

    matrix_1 = rand_matrix(n1, m1)
    matrix_2 = rand_matrix(n2, m2)

    print_matrix(matrix_1)
    print_matrix(matrix_2)

    print("Классический алгоритм:")
    print_matrix(mult_matrix(matrix_1, matrix_2))
    print("Алгоритм Винограда:")
    print_matrix(mult_matrix_winograd(matrix_1, matrix_2))
    print("Модифицированный алгоритм Винограда:")
    print_matrix(mult_matrix_winograd_mod(matrix_1, matrix_2))
if __name__ == '__main__':
    main()

