#include "expor.h"

void createList_wilayah(List_wilayah &L){ // Wilayah = Double Linked List
    first(L) = nil;
    last(L) = nil;
}
void createList_komoditas(List_komoditas &L){ // Komoditas = Single Circular Linked List
    first(L) = nil;
}
void createList_relasi(List_relasi &L){ // Relasi = Circular Double Linked List
    first(L) = nil;
    last(L) = nil;
}
adr_wilayah newWilayah(infotype_wilayah x){ // Membuat elemen wilayah baru berdasarkan info wilayah
    adr_wilayah P;
    P = new elm_wilayah;
    info(P) = x;
    next(P) = nil;
    prev(P) = nil;
    return P;
}
adr_komoditas newKomoditas(infotype_komoditas x){ // Membuat elemen komoditas baru berdasarkan info komoditas
    adr_komoditas P;
    P = new elm_komoditas;
    info(P) = x;
    next(P) = nil;
    return P;
}
adr_relasi newRelasi(adr_wilayah P, adr_komoditas Q){ // Membuat elemen relasi baru berdasarkan info wilayah dan komoditas
    adr_relasi R;
    R = new elm_relasi;
    wilayah(R) = P;
    komoditas(R) = Q;
    next(R) = nil;
    prev(R) = nil;
    return R;
}
// a. Tambahkan data wilayah (insert last)
void insertWilayah(List_wilayah &L, adr_wilayah P){
    if(first(L) == nil){
        first(L) = P;
        last(L) = P;
    }else{
        next(last(L)) = P;
        prev(P) = last(L);
        last(L) = P;
    }
}
// b. Tambahkan data komoditas (insert first single circular linked list)
void insertKomoditas(List_komoditas &L, adr_komoditas P){
    adr_komoditas last;
    if(first(L) == nil){
        first(L) = P;
        next(P) = P;
    }else{
        last = first(L);
        while(next(last) != first(L)){ // mencari elemen terakhir dari single circular linked list, yaitu elemen yang nextnya adalah first
            last = next(last);
        }
        next(last) = P;
        next(P) = first(L);
    }
}
// c. Mencari data wilayah tertentu
adr_wilayah findWilayah(List_wilayah L, string namadaerah){
    adr_wilayah P;
    P = first(L);
    while(P != nil && info(P).namadaerah != namadaerah){ // mencari data wilayah berdasarkan nama daerah, jika tidak ditemukan maka P = nil
        P = next(P);
    }
    return P; // P = nil jika tidak ditemukan, P = adr_wilayah jika ditemukan
}
// d. Menambahkan relasi antara wilayah dan komoditas
void insertRelasi(List_relasi &L, adr_relasi P){ // insert last circular double linked list
    if(first(L) == nil){ // jika list relasi kosong
        first(L) = P;
        last(L) = P;
        next(P) = P;
        prev(P) = P;
    }else{ // jika list relasi tidak kosong
        next(last(L)) = P; // menghubungkan elemen terakhir dengan elemen baru
        prev(P) = last(L); // menghubungkan elemen baru dengan elemen terakhir
        last(L) = P;    // mengubah elemen terakhir menjadi elemen baru
        next(P) = first(L); // menghubungkan elemen baru dengan elemen pertama
        prev(first(L)) = P; // menghubungkan elemen terakhir dengan elemen pertama
    }
}
// e. Mencari data wilayah yang memiliki komoditas tertentu
adr_komoditas findKomoditas(List_komoditas L, string namakomoditas){
    // Mencari data komoditas berdasarkan namanya, dilakukan di list komoditas (circular single linked list)
    adr_komoditas P, last;
    P = first(L);
    last = first(L);
    while(next(last) != first(L)){ // mencari elemen terakhir dari single circular linked list, yaitu elemen yang nextnya adalah first
        last = next(last);
    }
    while(P != last && info(P).namakomoditas != namakomoditas){ // mencari data komoditas berdasarkan nama komoditas, jika tidak ditemukan maka P = last
        P = next(P);
    }
    if(info(P).namakomoditas == namakomoditas){ // jika ditemukan
        return P;
    }else{ // jika tidak ditemukan
        return nil;
    }
}
void deleteRelasi(List_relasi &L, adr_relasi &P){
    if(first(L) == P){ // jika elemen yang akan dihapus adalah elemen pertama
        if(next(P) == P){ // jika hanya ada 1 elemen
            first(L) = nil;
            last(L) = nil;
        }else{ // jika lebih dari 1 elemen
            first(L) = next(P);
            prev(first(L)) = last(L);
            next(last(L)) = first(L);
        }
    }else if(last(L) == P){ // jika elemen yang akan dihapus adalah elemen terakhir
        last(L) = prev(P);
        next(last(L)) = first(L);
        prev(first(L)) = last(L);
    }else{ // jika elemen yang akan dihapus berada di tengah

        next(prev(P)) = next(P);
        prev(next(P)) = prev(P);
    }
    next(P) = nil;
    prev(P) = nil;
}
// f. Menghapus wilayah beserta relasinya (delete di data ke X (tergantung adr_wilayah))
void deleteWilayah(List_wilayah &L, adr_wilayah &P){
    if(first(L) == P){ // jika elemen yang akan dihapus adalah elemen pertama
        if(next(P) == P){ // jika hanya ada 1 elemen
            first(L) = nil;
            last(L) = nil;
        }else{ // jika lebih dari 1 elemen
            first(L) = next(P);
            prev(first(L)) = last(L);
            next(last(L)) = first(L);
        }
    }else if(last(L) == P){ // jika elemen yang akan dihapus adalah elemen terakhir
        last(L) = prev(P);
        next(last(L)) = first(L);
        prev(first(L)) = last(L);
    }else{ // jika elemen yang akan dihapus adalah elemen di tengah
        next(prev(P)) = next(P);
        prev(next(P)) = prev(P);
    }
    next(P) = nil; // menghapus relasi elemen P dengan elemen didepannya
    prev(P) = nil; // menghapus relasi elemen P dengan elemen dibelakangnya
}
// g. Menghapus data wilayah yang memiliki komoditas tertentu (delete di data ke X (tergantung adr_relasi)) (melakukan delete di circular double linked list/list relasi)
void deleteKomoditas(List_relasi &L, adr_relasi &P){
    if(first(L) == P){ // jika elemen yang akan dihapus adalah elemen pertama
        if(next(P) == P){ // jika hanya ada 1 elemen
            first(L) = nil;
            last(L) = nil;
        }else{ // jika lebih dari 1 elemen
            first(L) = next(P);
            prev(first(L)) = last(L);
            next(last(L)) = first(L);
        }
    }else if(last(L) == P){ // jika elemen yang akan dihapus adalah elemen terakhir
        last(L) = prev(P);
        next(last(L)) = first(L);
        prev(first(L)) = last(L);
    }else{ // jika elemen yang akan dihapus adalah elemen di tengah
        next(prev(P)) = next(P);
        prev(next(P)) = prev(P);
    }
    next(P) = nil; // menghapus relasi elemen P dengan elemen didepannya
    prev(P) = nil; // menghapus relasi elemen P dengan elemen dibelakangnya
}
adr_relasi findRelasi(List_relasi L, adr_wilayah P, adr_komoditas Q){
    // Mencari data relasi berdasarkan data wilayah dan data komoditas, dilakukan di list relasi (circular double linked list)
    adr_relasi R, last;
    R = first(L);
    last = first(L);
    while(next(last) != first(L)){ // mencari elemen terakhir dari double circular linked list, yaitu elemen yang nextnya adalah first
        last = next(last);
    }
    while(R != last && (wilayah(R) != P || komoditas(R) != Q)){ // mencari data relasi berdasarkan data wilayah dan data komoditas, jika tidak ditemukan maka R = last
        R = next(R);
    }
    if(wilayah(R) == P && komoditas(R) == Q){ // jika ditemukan
        return R;
    }else{ // jika tidak ditemukan
        return nil;
    }
}
// h. Menampilkan data wilayah beserta komoditasnya
void printWilayah(List_relasi L){
    adr_relasi P;
    P = first(L);
    if(P != nil){ // jika list relasi tidak kosong
        while (next(P) != first(L)) {
            cout << "Wilayah " << info(wilayah(P)).namadaerah << " memiliki komoditas " << info(komoditas(P)).namakomoditas << endl;
            P = next(P);
        }
        cout << "Wilayah " << info(wilayah(P)).namadaerah << " memiliki komoditas " << info(komoditas(P)).namakomoditas << endl; // menampilkan data wilayah terakhir,
        //karena sebelumnya tidak ditampilkan karena kondisi while berhenti ketika next(P) = first(L)
    }else{
        cout << "Data wilayah kosong" << endl;
    }
}
// i. Menampilkan data wilayah yang paling sedikit komoditasnya (Dilakukan di list relasi dengan menggunakan dua looping, yang pertama untuk mencari data wilayah dengan jumlah komoditas terkecil,
// yang kedua untuk menampilkan data wilayah dengan jumlah komoditas terkecil)
void printWilayahMin(List_relasi L){
    adr_relasi P;
    P = first(L);
    int min = 0;
    if(P != nil){ // jika list relasi tidak kosong
        while (next(P) != first(L)) {
            if(info(komoditas(P)).jumlahkomoditas > min){ // mencari data wilayah dengan jumlah komoditas terkecil
                min = info(komoditas(P)).jumlahkomoditas;
            }
            P = next(P);
        }
        if(info(komoditas(P)).jumlahkomoditas < min){ // menampilkan data wilayah terakhir,
            //karena sebelumnya tidak ditampilkan karena kondisi while berhenti ketika next(P) = first(L)
            min = info(komoditas(P)).jumlahkomoditas;
        }
        P = first(L);
        while (next(P) != first(L)) {
            if(info(komoditas(P)).jumlahkomoditas == min){ // mencari data wilayah dengan jumlah komoditas terkecil
                cout << "Wilayah " << info(wilayah(P)).namadaerah << " memiliki komoditas " << info(komoditas(P)).namakomoditas << endl;
            }
            P = next(P);
        }
        if(info(komoditas(P)).jumlahkomoditas == min){ // menampilkan data wilayah terakhir,
            //karena sebelumnya tidak ditampilkan karena kondisi while berhenti ketika next(P) = first(L)
            cout << "Wilayah " << info(wilayah(P)).namadaerah << " memiliki komoditas " << info(komoditas(P)).namakomoditas << endl;
        }
    }else{
        cout << "Data wilayah kosong" << endl;
    }
}
/* j. Menampilkan data wilayah yang paling banyak komoditasnya (Dilakukan di list relasi dengan menggunakan dua looping, yang pertama untuk mencari data wilayah dengan jumlah
komoditas terbanyak, yang kedua untuk menampilkan data wilayah dengan jumlah komoditas terbanyak) */
void printWilayahMax(List_relasi L){
    adr_relasi P;
    P = first(L);
    int max = 0;
    if(P != nil){ // jika list relasi tidak kosong
        while (next(P) != first(L)) {
            if(info(komoditas(P)).jumlahkomoditas > max){ // mencari data wilayah dengan jumlah komoditas terbanyak
                max = info(komoditas(P)).jumlahkomoditas;
            }
            P = next(P);
        }
        if(info(komoditas(P)).jumlahkomoditas > max){ // menampilkan data wilayah terakhir,
            //karena sebelumnya tidak ditampilkan karena kondisi while berhenti ketika next(P) = first(L)
            max = info(komoditas(P)).jumlahkomoditas;
        }
        P = first(L);
        while (next(P) != first(L)) {
            if(info(komoditas(P)).jumlahkomoditas == max){ // mencari data wilayah dengan jumlah komoditas terbanyak
                cout << "Wilayah " << info(wilayah(P)).namadaerah << " memiliki komoditas " << info(komoditas(P)).namakomoditas << endl;
            }
            P = next(P);
        }
        if(info(komoditas(P)).jumlahkomoditas == max){ // menampilkan data wilayah terakhir,
            //karena sebelumnya tidak ditampilkan karena kondisi while berhenti ketika next(P) = first(L)
            cout << "Wilayah " << info(wilayah(P)).namadaerah << " memiliki komoditas " << info(komoditas(P)).namakomoditas << endl;
        }
    }else{
        cout << "Data wilayah kosong" << endl;
    }
}
// Menu
int selectMenu(){
    int select;
    select = 0;
    /*nama saya windy ikhsana*/
    cout << endl;
    cout << "1. Tambah data wilayah" << endl;
    cout << "2. Tambah data komoditas" << endl;
    cout << "3. Cari data wilayah" << endl;
    cout << "4. Menambahkan relasi antara wilayah dan komoditas" << endl;
    cout << "5. Mencari wilayah yang memiliki komoditas tertentu" << endl;
    cout << "6. Menghapus data wilayah dan semua relasinya" << endl;
    cout << "7. Menghapus data wilayah yang memiliki komoditas tertentu" << endl;
    cout << "8. Menampilkan seluruh wilayah beserta komoditasnya" << endl;
    cout << "9. Menampilkan data wilayah yang paling sedikit komoditasnya" << endl;
    cout << "10. Menampilkan data wilayah yang paling banyak komoditasnya" << endl;
    cout << "0. Keluar" << endl;
    cout << "====================================================================================================================" << endl;
    cout << "Pilih menu : ";
    cin >> select;
    return select;
}


