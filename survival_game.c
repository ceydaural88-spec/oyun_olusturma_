#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---  DURUM DEĞİŞKENLERİ ---
int saglik = 100;
int enerji = 100;
int yemek = 5;
int siginak = 0; // 0=Yok, 1=Var
char envanter[50] = "Temel Ekipman";

// ---  FONKSİYONLAR ---

void deger_sinirla() {
    if (saglik > 100) saglik = 100;
    if (saglik < 0) saglik = 0;
    if (enerji > 100) enerji = 100;
    if (enerji < 0) enerji = 0;
}

void durum_goster() {
    printf("\n[Envanter] Envanteriniz: %s\n", envanter);
    printf("[Saglik] Can: %d%%\n", saglik);
    printf("[Enerji] Enerji: %d%%\n", enerji);
    printf("[Yemek] Yiyecek: %d adet\n", yemek);
    printf("[Siginak] Barinak: %s\n", (siginak == 1 ? "VAR" : "YOK"));
}

int oyun_bitti_mi() {
    if (saglik <= 0 || enerji <= 0) {
        printf("\n*** KARAKTER HAYATTA KALAMADI ***\n");
        printf("Can: %d, Enerji: %d.\n", saglik, enerji);
        return 1;
    }
    return 0;
}

// --- KOMUT FONKSİYONLARI ---

// R - Dinlen komutu (Aritmetik işlemler ve Mantıksal &&)
void komut_dinlen() {
    printf("\n[Komut: R] Dinleniliyor... Enerji toplanıyor.\n");

    enerji += 20; // Enerji artışı
    
    // Yeterli enerji varsa VE sağlık tam değilse, sağlık kazan
    if (enerji >= 50 && saglik < 100) { 
        saglik += 10;
        printf("-> Derin dinlenme sağlandi. (+10 Sağlık)\n");
    }

    if (yemek > 0) {
        yemek -= 1; 
        printf("-> Yemek tüketildi (-1 yemek).\n");
    }

    deger_sinirla();
    durum_goster();
}

// A - Avlan komutu (Aritmetik ve Mantıksal &&, ||)
void komut_avlan() {
    printf("\n[Komut: A] Avlaniyorsunuz. Enerji harcaniyor (-15).\n");
    enerji -= 15;
    
    int sans = rand() % 100;

    if (sans < 40 && yemek < 10) { // %40 şans VE envanter dolu değilse
        yemek += 2;
        printf("-> Basari! 2 birim yemek bulundu.\n");
    } else if (sans >= 90 || enerji < 10) { // %10 şans VEYA enerji cok dusukse
        saglik -= 15;
        printf("-> Basarisiz! Ciddi bir yaralanma oldu (-15 Sağlık).\n");
    } else {
        printf("-> Basarisiz! Avlanma verimsizdi.\n");
    }

    deger_sinirla();
    durum_goster();
}

// S - Sığınak arama komutu (IF-ELSE Yapısı)
void komut_siginak_ara() {
    printf("\n[Komut: S] Sığınak aranıyor...\n");
    
    if (siginak == 1) {
        printf("Zaten bir sığınaginiz var. Kaynaklari tuketmeyin.\n");
    } else {
        int sans = rand() % 100;
        
        if (sans > 70) { // %30 şans
            siginak = 1; 
            printf("-> TEBRIKLER! Kalici bir sığınak bulundu.\n");
        } else {
            enerji -= 5;
            printf("-> Basarisiz. Sığınak bulunamadi. (-5 Enerji)\n");
        }
    }
    
    deger_sinirla();
    durum_goster();
}

// F - Tehlike Dalgası (FOR Döngüsü Zorunluluğu)
void komut_tehlike() {
    printf("\n[Komut: F] TEHLIKE DALGASI basliyor (4 tur)...\n");
    
    // FOR DÖNGÜSÜ: 4 turluk simülasyon
    int tur;
    for ( tur = 1; tur <= 4; tur++) {
        int olay = rand() % 10; // 0-9 arası olay
        
        printf("Tur %d: ", tur);

        if (olay < 3) { // %30 şans
            saglik -= 8; 
            printf("Fiziksel hasar alındı! -8 Can.\n");
        } else if (olay >= 7 && siginak == 1) { // %30 şans VE sığınak varsa
            printf("Sığınak sayesinde tehlike savuşturuldu.\n");
        } else {
            enerji -= 4; 
            printf("Mücadele yordu. -4 Enerji.\n");
        }
        
        deger_sinirla();
        if (oyun_bitti_mi()) return; 
    }
    durum_goster();
}

// P - Şifreli İlerleme (DO-WHILE Döngüsü Zorunluluğu)
void komut_sifre() {
    char sifre_giris;
    const char dogru_sifre = 'C'; 
    int deneme_sayisi = 0;
    
    printf("\n[Komut: P] Gizli bir kapı ile karsilastiniz. Sifreyi girin!\n");
    
    // DO-WHILE DÖNGÜSÜ: Doğru şifre girilene kadar veya deneme bitene kadar tekrar eder
    do {
        deneme_sayisi++;
        printf("Deneme %d. Sifre Karakteri: ", deneme_sayisi);
        
        // Boşluk karakterlerini yoksaymak için " %c" kullanılır
        if (scanf(" %c", &sifre_giris) != 1) continue; 
        
        if (sifre_giris != dogru_sifre) {
            printf("YANLIS! Engel asilamadi. Tekrar deneyin.\n");
            enerji -= 5;
            deger_sinirla();
            if (oyun_bitti_mi()) return;
        }

    } while (sifre_giris != dogru_sifre && deneme_sayisi < 3); // 3 deneme hakkı

    if (sifre_giris == dogru_sifre) {
        printf("-> BASARI! Gizli kapidan gectiniz.\n");
    } else {
        printf("-> BASARISIZ! 3 denemede sifreyi bulamadiniz. Geri cekiliyorsunuz.\n");
    }
    
    durum_goster();
}

// --- ANA PROGRAM ---
int main() {
    char komut;
    
    // Rastgele sayı üreteci başlangıcı (Sadece bir kez çağrılır)
    srand(time(NULL));

    printf("--- HAYATTA KALMA SIMULATORU ---\n");
    printf("Komutlar: (A)vlan, (S)iginak, (R)dinlen, (E)nvanter, (F)tehlike, (P)sifre, (X)cikis\n");
    
    durum_goster();

    // Ana Komut Dinleme Döngüsü (DO-WHILE)
    do {
        printf("\n-----------------------------------------------------\n");
        printf("Komut girin (A/S/R/E/F/P/X): ");
        
        if (scanf(" %c", &komut) != 1) {
            komut = 'X'; 
        }

        // Komut sistemini yönetme (SWITCH-CASE)
        switch (komut) {
            case 'A': komut_avlan(); break; 
            case 'S': komut_siginak_ara(); break; 
            case 'R': komut_dinlen(); break; 
            case 'F': komut_tehlike(); break; 
            case 'P': komut_sifre(); break; 
            case 'E': durum_goster(); break; 
            case 'X': break; 
            default: printf("Gecersiz komut. Lutfen tek bir karakter girin.\n");
        }
        
    } while (komut != 'X' && !oyun_bitti_mi()); 

    return 0;
}
