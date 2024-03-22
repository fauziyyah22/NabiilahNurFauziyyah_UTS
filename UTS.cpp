#include <iostream> // Library untuk input-output standar
#include <iomanip>  // Library untuk manajemen format output
#include <string>   // Library untuk penggunaan string
using namespace std;

// Struktur untuk merepresentasikan informasi tugas
struct Tugas {
    int id;             // ID tugas
    string nama;        // Nama tugas
    string deskripsi;   // Deskripsi tugas
    string deadline;    // Deadline tugas
    bool completed;     // Status keberhasilan tugas
};

// Struktur untuk simpul linked list
struct Node {
    Tugas data; // Data tugas yang disimpan dalam simpul
    Node* next; // Pointer menuju simpul berikutnya
};

// Fungsi untuk membuat simpul baru dalam linked list
Node* createNode(Tugas data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Fungsi untuk menambahkan simpul baru di akhir linked list
void append(Node*& head, Tugas data) {
    Node* newNode = createNode(data);
    if (head == nullptr) { // Jika linkedlist kosong
        head = newNode;    // Simpul baru menjadi kepala
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode; // Menambahkan simpul baru di belakang simpul terakhir
    }
}

// Fungsi untuk mencetak daftar tugas dalam bentuk tabel
void printTasks(Node* head) {
    system("cls"); // Membersihkan layar sebelum mencetak daftar tugas
    cout << "=======================================================================================" << endl;
    cout << "| ID  |        Nama         |        Deskripsi        |     Deadline    |  Keterangan |" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    Node* temp = head;
    while (temp != nullptr) {
        // Mencetak informasi tugas dalam format tabel
        cout << "|" << setw(5) << temp->data.id << "| " << setw(20) << temp->data.nama << "| " << setw(23) << temp->data.deskripsi
             << " | " << setw(15) << temp->data.deadline << " | " << setw(9) << (temp->data.completed ? "Selesai" : "Belum") << "   |" << endl;
        temp = temp->next;
    }
    cout << "=======================================================================================" << endl;
}

// Fungsi untuk menambahkan tugas baru
void addTask(Node*& head, int& taskIdCounter) {
    string nama, deskripsi, deadline;
    cout << "Masukkan nama tugas: ";
    cin.ignore();   // Mengabaikan karakter newline yang masih tersisa di buffer
    getline(cin, nama);
    cout << "Masukkan deskripsi tugas: ";
    getline(cin, deskripsi);
    cout << "Masukkan deadline tugas: ";
    getline(cin, deadline);
    Tugas newTask;
    newTask.id = taskIdCounter++;   // Menetapkan ID baru untuk tugas
    newTask.nama = nama;
    newTask.deskripsi = deskripsi;
    newTask.deadline = deadline;
    newTask.completed = false;      // Set tugas sebagai belum selesai
    append(head, newTask);          // Menambahkan tugas ke linkedlist
}

// Fungsi untuk menghapus tugas berdasarkan ID
void deleteTask(Node*& head, int id) {
    if (head == nullptr) {      // Jika linkedlist kosong, tidak perlu melakukan apa-apa
        return;
    }
    if (head->data.id == id) {  // Jika tugas yang akan dihapus adalah kepala linkedlist
        Node* temp = head;
        head = head->next;      // Mengubah kepala linkedlist menjadi simpul berikutnya
        delete temp;            // Menghapus simpul yang mengandung tugas yang dihapus
        return;
    }
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr && curr->data.id != id) {
        prev = curr;        // Menyimpan simpul sebelumnya
        curr = curr->next;  // Melanjutkan ke simpul berikutnya
    }
    if (curr == nullptr) {  // Jika tugas tidak ditemukan dalam linkedlist
        cout << "Tidak ditemukan tugas dengan ID " << id << endl;
        return;
    }
    prev->next = curr->next; // Mehubungkan simpul sebelumnnya dengan simpul berikutnya
    delete curr;             // Menghapus simpul yang mengandung tugas yang dihapus
}

// Fungsi untuk menyelesaikan tugas berdasarkan ID
void completeTask(Node* head, int id) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.id == id) {
            temp->data.completed = true;
            return;
        }
        temp = temp->next;
    }
    cout << "Tidak ditemukan tugas dengan ID " << id << endl;
}

int main() {
    Node* head = nullptr;
    int taskIdCounter = 1;
    char pilihan;
    do {
        cout << "\n===== APLIKASI MANAJEMEN TUGAS =====" << endl;
        cout << "====================================" << endl;
        cout << "Menu: " << endl;
        cout << "1. Tambah Tugas" << endl;
        cout << "2. Hapus Tugas" << endl;
        cout << "3. Tandai Selesai" << endl;
        cout << "4. Tampilkan Daftar Tugas" << endl;
        cout << "5. Keluar" << endl;
        cout << "====================================" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                addTask(head, taskIdCounter);
                break;
            case '2':
                int idToDelete;
                cout << "Masukkan ID tugas yang ingin dihapus: ";
                cin >> idToDelete;
                deleteTask(head, idToDelete);
                break;
            case '3':
                int idToComplete;
                cout << "Masukkan ID tugas yang telah selesai: ";
                cin >> idToComplete;
                completeTask(head, idToComplete);
                break;
            case '4':
                printTasks(head);
                break;
            case '5':
                cout << "Keluar dari aplikasi." << endl;
                cout << "\nTerima kasih telah menggunakan program ini\n";
                for (int j = 0; j < 60; j++) {
                cout << "=";}
                cout << "\nNama     : Nabiilah Nur Fauziyyah";
                cout << "\nNPM      : 2310631170105";
                cout << "\nKelas    : 2C - Informatika";
                cout << "\nAplikasi Manajemen Tugas " << "\n";
                for (int j = 0; j < 60; j++) {
                cout << "=";}
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != '5');

    // Membersihkan memori linked list
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
