#include <iostream>
using namespace std;    


class Matrix {
private:
    int _m, _n;         // _m = мөрийн тоо, _n = баганын тоо
    float **_values;    // 2 хэмжээст динамик массив (pointer to pointer)

    // Санах ой нөөцлөх функц
    void allocate(int m, int n) {
        _m = m;                         // мөрийн тоог хадгална
        _n = n;                         // баганын тоог хадгална
        _values = new float*[m];        // мөр бүрт pointer массив үүсгэнэ

        for (int i = 0; i < m; i++) {   // мөр бүрээр гүйх
            _values[i] = new float[n];  // тухайн мөрт n хэмжээтэй багана үүсгэнэ

            for (int j = 0; j < n; j++) // багана бүрээр гүйх
                _values[i][j] = 0;      // анхны утгыг 0 болгоно
        }
    }

    // Санах ой чөлөөлөх функц
    void deallocate() {
        for (int i = 0; i < _m; i++)    // мөр бүрийг устгана
            delete[] _values[i];

        delete[] _values;               // pointer массивыг устгана
    }

public:
    // Constructor (анх үүсгэх)
    Matrix(int m = 1, int n = 1) {      // default нь 1x1 матриц
        allocate(m, n);                 // санах ой нөөцлөх
    }

    // Copy Constructor (хуулбарлах)
    Matrix(const Matrix &other) {       // өөр матрицыг параметрээр авна
        allocate(other._m, other._n);   // ижил хэмжээтэй санах ой үүсгэнэ

        for (int i = 0; i < _m; i++)    // бүх элементээр гүйж
            for (int j = 0; j < _n; j++)
                _values[i][j] = other._values[i][j]; // утгыг хуулна
    }

    // Destructor (устгах үед дуудагдана)
    ~Matrix() {
        deallocate();                  // санах ойг суллана
    }

    // Getter функцууд
    int getRow() const { return _m; }      // мөрийн тоо буцаана
    int getColumn() const { return _n; }   // баганын тоо буцаана

    float getValue(int i, int j) const {   // i,j байрлалын утга авах
        return _values[i][j];
    }

    // Setter функцууд
    void setValue(int i, int j, float value) { // i,j байрлалд утга оноох
        _values[i][j] = value;
    }

    float** getValues() const {             // бүх массив буцаах
        return _values;
    }

    void setValues(float **values) {        // бүх массив оноох
        for (int i = 0; i < _m; i++)
            for (int j = 0; j < _n; j++)
                _values[i][j] = values[i][j];
    }

    // Row устгах (r-р мөр устгана)
    void removeRow(int r) {
        for (int i = r; i < _m - 1; i++)        // устгах мөрөөс доош
            for (int j = 0; j < _n; j++)
                _values[i][j] = _values[i + 1][j]; // дараагийн мөрийг дээш татна

        _m--;                                   // мөрийн тоог багасгана
    }

    // Column устгах (c-р багана устгана)
    void removeColumn(int c) {
        for (int i = 0; i < _m; i++)            // мөр бүрээр гүйх
            for (int j = c; j < _n - 1; j++)
                _values[i][j] = _values[i][j + 1]; // баруун талын утгыг зүүн тийш шилжүүлнэ

        _n--;                                   // баганын тоог багасгана
    }

    // Resize (хэмжээ өөрчлөх)
    void resize(int newM, int newN) {
        float **newArr = new float*[newM];      // шинэ массив үүсгэнэ

        for (int i = 0; i < newM; i++) {
            newArr[i] = new float[newN];        // мөр бүрт шинэ багана

            for (int j = 0; j < newN; j++) {
                if (i < _m && j < _n)           // хуучин массив дотор байвал
                    newArr[i][j] = _values[i][j]; // хуучин утгыг авна
                else
                    newArr[i][j] = 0;           // үгүй бол 0
            }
        }

        deallocate();                           // хуучин санах ойг устгана

        _values = newArr;                       // шинэ массив онооно
        _m = newM;                              // шинэ мөр
        _n = newN;                              // шинэ багана
    }

    // Operator + (Matrix + Matrix)
    Matrix operator+(const Matrix &other) {
        Matrix result(_m, _n);                  // шинэ матриц үүсгэнэ

        for (int i = 0; i < _m; i++)
            for (int j = 0; j < _n; j++)
                result._values[i][j] = _values[i][j] + other._values[i][j]; // элемент бүрийг нэмнэ

        return result;                          // үр дүнг буцаана
    }

    // Operator + (Matrix + float)
    Matrix operator+(float val) {
        Matrix result(_m, _n);

        for (int i = 0; i < _m; i++)
            for (int j = 0; j < _n; j++)
                result._values[i][j] = _values[i][j] + val; // бүх элементэд val нэмнэ

        return result;
    }

    // Operator -
    Matrix operator-(const Matrix &other) {
        Matrix result(_m, _n);

        for (int i = 0; i < _m; i++)
            for (int j = 0; j < _n; j++)
                result._values[i][j] = _values[i][j] - other._values[i][j]; // хасна

        return result;
    }

    // Operator * (Matrix үржих)
    Matrix operator*(const Matrix &other) {
        Matrix result(_m, other._n); // шинэ хэмжээ

        for (int i = 0; i < _m; i++) {
            for (int j = 0; j < other._n; j++) {
                result._values[i][j] = 0;

                for (int k = 0; k < _n; k++) // дундах хэмжээс
                    result._values[i][j] += _values[i][k] * other._values[k][j];
            }
        }

        return result;
    }

    // Operator =
    Matrix& operator=(const Matrix &other) {
        if (this == &other) return *this; // өөртэйгээ адил эсэхийг шалгах

        resize(other._m, other._n);       // хэмжээг тааруулна

        for (int i = 0; i < _m; i++)
            for (int j = 0; j < _n; j++)
                _values[i][j] = other._values[i][j]; // утга хуулна

        return *this;
    }

    // ++ оператор
    Matrix& operator++() {
        for (int i = 0; i < _m; i++)
            for (int j = 0; j < _n; j++)
                _values[i][j]++; // бүх элемент +1

        return *this;
    }

    // -- оператор
    Matrix& operator--() {
        for (int i = 0; i < _m; i++)
            for (int j = 0; j < _n; j++)
                _values[i][j]--; // бүх элемент -1

        return *this;
    }

    // += оператор
    Matrix& operator+=(const Matrix &other) {
        for (int i = 0; i < _m; i++)
            for (int j = 0; j < _n; j++)
                _values[i][j] += other._values[i][j];

        return *this;
    }

    // -= оператор
    Matrix& operator-=(const Matrix &other) {
        for (int i = 0; i < _m; i++)
            for (int j = 0; j < _n; j++)
                _values[i][j] -= other._values[i][j];

        return *this;
    }

    // *= оператор
    Matrix& operator*=(const Matrix &other) {
        *this = *this * other; // үржүүлээд өөртөө онооно
        return *this;
    }

    // [][] оператор (matrix[i][j] ашиглах)
    float* operator[](int i) {
        return _values[i]; // i-р мөрийг буцаана
    }

    // Transpose (хөрвүүлэх)
    Matrix transpose() {
        Matrix t(_n, _m); // багана мөр солигдоно

        for (int i = 0; i < _m; i++)
            for (int j = 0; j < _n; j++)
                t._values[j][i] = _values[i][j]; // байр солих

        return t;
    }

    // Print (шалгах зориулалттай)
    void print() {
        for (int i = 0; i < _m; i++) {
            for (int j = 0; j < _n; j++)
                cout << _values[i][j] << " ";
            cout << endl;
        }
    }
};

int main() {
    Matrix A(2,2), B(2,2);

    A.setValue(0,0,1);
    A.setValue(0,1,2);
    A.setValue(1,0,3);
    A.setValue(1,1,4);

    B = A;

    Matrix C = A + B;
    Matrix D = A * B;

    C.print();
    cout << endl;
    D.print();

    return 0;
}
