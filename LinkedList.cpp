#include <iostream>
#include <string>     
using namespace std;  

// template ашиглаж байгаа тул T оронд ямар ч datatype орж болно
template <typename T>
class Node {

public:

    // Node дотор хадгалагдах өгөгдөл
    T data;

    // Дараагийн node-ийн хаягийг хадгалах pointer
    Node<T>* next;

    // Constructor функц
    // Шинэ node үүсэх үед автоматаар ажиллана
    Node(T value) {

        // Орж ирсэн value-г data-д хадгалж байна
        data = value;

        // Шинэ node эхэндээ дараагийн node-гүй тул nullptr
        next = nullptr;
    }
};

//LINKED LIST CLASS

template <typename T>
class LinkedList {

private:

    // Жагсаалтын хамгийн эхний node-г заах pointer
    Node<T>* head;

    // Жагсаалтын нийт элементийн тоо
    int size;

public:

    // Constructor
    // LinkedList шинээр үүсэхэд автоматаар ажиллана
    LinkedList() {

        // Эхэндээ ямар ч node байхгүй
        head = nullptr;

        // Элемент байхгүй тул хэмжээ 0
        size = 0;
    }

    // ================= ADD FUNCTION =================
    // Жагсаалтын хамгийн сүүлд элемент нэмнэ

    void add(T t) {

        // Шинэ node үүсгэж байна
        // t утга data хэсэгт хадгалагдана
        Node<T>* newNode = new Node<T>(t);

        // Хэрэв linked list хоосон бол
        if (head == nullptr) {

            // Шинэ node-г head болгоно
            // Өөрөөр хэлбэл хамгийн эхний элемент болно
            head = newNode;
        }

        // Хэрэв өмнө нь элементүүд байгаа бол
        else {

            // temp pointer ашиглан head-ээс эхэлж байна
            Node<T>* temp = head;

            // temp-ийг хамгийн сүүлийн node хүртэл шилжүүлнэ
            // next нь nullptr болсон үед хамгийн сүүлд хүрсэн байна
            while (temp->next != nullptr) {

                // Дараагийн node руу шилжинэ
                temp = temp->next;
            }

            // temp одоо хамгийн сүүлийн node дээр байгаа
            // Түүний next-д шинэ node-г холбоно
            temp->next = newNode;
        }

        // Элемент нэмэгдсэн тул хэмжээг 1-ээр нэмнэ
        size++;
    }

    //INSERT FUNCTION
    // index байрлалд шинэ элемент оруулна

    void insert(T t, int index) {

        // Буруу index орсон эсэхийг шалгаж байна
        if (index < 0 || index > size) {

            cout << "Index aldaa!" << endl;
            return;
        }

        // Оруулах шинэ node үүсгэж байна
        Node<T>* newNode = new Node<T>(t);

        // Хэрэв 0-р index буюу хамгийн эхэнд оруулах бол
        if (index == 0) {

            // Шинэ node-ийн next нь хуучин head болно
            newNode->next = head;

            // Шинэ node-г head болгож байна
            head = newNode;
        }

        // Хэрэв дунд эсвэл сүүлд оруулах бол
        else {

            // temp pointer head-ээс эхэлнэ
            Node<T>* temp = head;

            // Оруулах байрлалын өмнөх node хүртэл явна
            for (int i = 0; i < index - 1; i++) {

                // Дараагийн node руу шилжинэ
                temp = temp->next;
            }

            // Шинэ node-ийн next нь temp-ийн дараагийн node болно
            newNode->next = temp->next;

            // temp-ийн next одоо шинэ node-г заана
            temp->next = newNode;
        }

        // Элемент нэмэгдсэн тул хэмжээг өсгөнө
        size++;
    }

    //GET FUNCTION
    // index дахь элементийн утгыг буцаана

    T get(int index) {

        // Index зөв эсэхийг шалгаж байна
        if (index < 0 || index >= size) {

            throw out_of_range("Index aldaa!");
        }

        // temp pointer head-ээс эхэлнэ
        Node<T>* temp = head;

        // temp-ийг хэрэгтэй index хүртэл шилжүүлнэ
        for (int i = 0; i < index; i++) {

            temp = temp->next;
        }

        // temp одоо шаардлагатай node дээр очсон
        // data-г буцааж байна
        return temp->data;
    }

    //DELETE FUNCTION
    // index дахь элементийг устгана

    // delete keyword тул deleteAt гэж нэрлэсэн
    void deleteAt(int index) {

        // Index зөв эсэхийг шалгаж байна
        if (index < 0 || index >= size) {

            cout << "Index aldaa!" << endl;
            return;
        }

        // temp эхний node-ийг зааж эхэлнэ
        Node<T>* temp = head;

        // Хэрэв эхний элементийг устгах бол
        if (index == 0) {

            // head-ийг дараагийн node руу шилжүүлнэ
            head = head->next;

            // Хуучин эхний node-ийн memory-г суллана
            delete temp;
        }

        // Хэрэв дундах эсвэл сүүлийн node устгах бол
        else {

            // Устгах node-ийн өмнөх node-г хадгалах pointer
            Node<T>* prev = nullptr;

            // temp-ийг устгах node хүртэл явуулна
            for (int i = 0; i < index; i++) {

                // Одоогийн node-г prev хадгална
                prev = temp;

                // temp дараагийн node руу шилжинэ
                temp = temp->next;
            }

            // prev-ийн next одоо temp-ийн дараагийн node-г заана
            // Ингэснээр temp жагсаалтаас сална
            prev->next = temp->next;

            // temp node-ийн memory-г суллана
            delete temp;
        }

        // Элемент устсан тул хэмжээг бууруулна
        size--;
    }

    //LENGTH FUNCTION
    // Жагсаалтын уртыг буцаана

    int length() {

        // size хувьсагчид хадгалагдсан хэмжээг буцаана
        return size;
    }

    // PRINT
    // Жагсаалтыг хэвлэх нэмэлт функц

    void print() {

        // temp pointer head-ээс эхэлнэ
        Node<T>* temp = head;

        // temp nullptr болох хүртэл бүх node-оор явна
        while (temp != nullptr) {

            // Одоогийн node-ийн data-г хэвлэнэ
            cout << temp->data << " -> ";

            // Дараагийн node руу шилжинэ
            temp = temp->next;
        }

        // Сүүлийн node-ийн дараа nullptr гэж хэвлэж байна
        cout << "nullptr" << endl;
    }
};

// MAIN

int main() {

    // Integer төрлийн LinkedList үүсгэж байна
    LinkedList<int> list;

    // add ашиглан сүүлд элементүүд нэмж байна
    list.add(10);
    list.add(20);
    list.add(30);

    // Жагсаалтыг хэвлэнэ
    cout << "Add hiisnii daraa: ";
    list.print();

    // 1-р index дээр 15 оруулж байна
    list.insert(15, 1);

    cout << "Insert hiisnii daraa: ";
    list.print();

    // 2-р index дахь утгыг авч байна
    cout << "Index 2 dahi element: ";
    cout << list.get(2) << endl;

    // 1-р index дахь элементийг устгаж байна
    list.deleteAt(1);

    cout << "Delete hiisnii daraa: ";
    list.print();

    // Жагсаалтын уртыг хэвлэж байна
    cout << "Length: ";
    cout << list.length() << endl;

    return 0;
}
