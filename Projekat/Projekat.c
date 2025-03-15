#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define SVET "svet.txt"
#define EVROPA "evropa.txt"
#define AZIJA "azija.txt"
#define AFRIKA "afrika.txt"
#define REZULTATI1 "rezultati1.txt"
#define REZULTATI2 "rezultati2.txt"
#define REZULTATI3 "rezultati3.txt"

void ucitajPitanja(int kategorija, struct pitanje p[40]);
void upisiRezultat(char ime[20], int poeni, int brojPitanja);
struct korisnik ucitajKorisnike(int brojPitanja);

struct pitanje {
	char drzava[20];
	char grad[20];
};

struct korisnik{
	char ime[20];
	int poeni;
};

int main() {

	int i, j;
	int kategorija;
	int brojPitanja;
	int proveraKategorije = 0;
	int proveraBroja = 0;
	char username[20];
	struct pitanje pitanja[40];
	struct pitanje rezerva;
	int k = sizeof(pitanja) / sizeof(pitanja[0]);
	char odgovor[20];
	int bodoviOdgovora = 0;
	double bodoviVremena = 1200;
	int bodoviUkupno;
	int* ptr;
	clock_t pocetak, kraj;
	double vreme;
	struct korisnik najbolji;

	// Unos korisnickog imena
	printf("Unesite vase korisnicko ime: ");
	gets(username); 
	// Odabir kategorije
	printf("Izaberite jednu od kategorija(1 - Svet, 2 - Evropa, 3 - Azija, 4 - Afrika):\n");
	scanf("%d", &kategorija);
	while (proveraKategorije == 0) {
		if (kategorija > 0 && kategorija < 5) {
			proveraKategorije = 1;
		}
		else {
			printf("GRESKA: Niste lepo izabrali kategoriju!\n");
			printf("Izaberite jednu od kategorija(1 - Svet, 2 - Evropa, 3 - Azija, 4 - Afrika):\n");
			scanf("%d", &kategorija);
		}
	}
	// Odabir broja pitanja
	printf("Odaberite broj pitanja(1 - 10, 2 - 20, 3 - 30):\n");
	scanf("%d", &brojPitanja);
	while (proveraBroja == 0) {
		if (brojPitanja > 0 && brojPitanja < 4) {
			proveraBroja = 1;
		}
		else {
			printf("GRESKA: Niste lepo izabrali broj pitanja!\n");
			printf("Odaberite broj pitanja(1 - 10, 2 - 20, 3 - 30):\n");
			scanf("%d", &brojPitanja);
		}
	}
	// Ucitavanje odgovarajucih pitanja
	ucitajPitanja(kategorija, pitanja);
	// Uklanjanje razmaka ucitanog od strane fgets
	for (i = 0; i < 40; i++) {
		pitanja[i].drzava[strcspn(pitanja[i].drzava, "\n")] = '\0';
		pitanja[i].grad[strcspn(pitanja[i].grad, "\n")] = '\0';
	}
	// Mesanje redosleda pitanja
	srand(time(NULL));
	for (i = k - 1; i > 0; i--) {
		j = rand() % (i + 1);
		rezerva = pitanja[i];
		pitanja[i] = pitanja[j];
		pitanja[j] = rezerva;
	}
	// Postavljanje pitanja
	pocetak = clock();
	if (brojPitanja == 1) {
		for (i = 0; i < 10; i++) {
			printf("Koji je glavni grad %s?\n", pitanja[i].drzava);
			scanf("%s", &odgovor);
			for (j = 0; j <= strlen(odgovor); j++) {
				odgovor[j] = tolower(odgovor[j]);
			}
			if (strcmp(odgovor, pitanja[i].grad) == 0) {
				bodoviOdgovora++;
				printf("Tacan odgovor!\n");
			}
			else {
				printf("Netacan odgovor!\n");
			}
		}
	}
	else if (brojPitanja == 2) {
		for (i = 0; i < 20; i++) {
			printf("Koji je glavni grad %s?\n", pitanja[i].drzava);
			scanf("%s", &odgovor);
			for (j = 0; j <= strlen(odgovor); j++) {
				odgovor[j] = tolower(odgovor[j]);
			}
			if (strcmp(odgovor, pitanja[i].grad) == 0) {
				bodoviOdgovora++;
				printf("Tacan odgovor!\n");
			}
			else {
				printf("Netacan odgovor!\n");
			}
		}
	}
	else if (brojPitanja == 3) {
		for (i = 0; i < 30; i++) {
			printf("Koji je glavni grad %s?\n", pitanja[i].drzava);
			scanf("%s", &odgovor);
			for (j = 0; j <= strlen(odgovor); j++) {
				odgovor[j] = tolower(odgovor[j]);
			}
			if (strcmp(odgovor, pitanja[i].grad) == 0) {
				bodoviOdgovora++;
				printf("Tacan odgovor!\n");
			}
			else {
				printf("Netacan odgovor!\n");
			}
		}
	}
	// Bodovanje
	kraj = clock();
	vreme = ((double) (kraj - pocetak)) / CLOCKS_PER_SEC;
	bodoviVremena = bodoviVremena - vreme;
	bodoviOdgovora = bodoviOdgovora * 10;
	bodoviUkupno = (int)bodoviVremena + bodoviOdgovora;
	ptr = (int*)malloc(bodoviUkupno * sizeof(int));
	if (ptr == NULL) {
		printf("GRESKA: Memorija nije alocirana!\n");
		exit(0);
	}
	// Prikazivanje i Upisivanje rezultata
	printf("\n");
	if (brojPitanja == 1) {
		printf("Uspesno ste odgovorili na %d/10 pitanja.\n", bodoviOdgovora / 10);
		printf("Za to Vam je bilo potrebno %.2lf sekundi.\n", vreme);
		printf("Postignutim rezultatom osvojili ste %d poena.\n", bodoviUkupno);

		upisiRezultat(username, bodoviUkupno, brojPitanja);
		najbolji = ucitajKorisnike(brojPitanja);
		najbolji.ime[strcspn(najbolji.ime, "\n")] = '\0';
		printf("Najbolji rezultat u odabranoj kategoriji ima korisnik %s sa %d poena.\n", najbolji.ime, najbolji.poeni);
	}
	else if (brojPitanja == 2) {
		printf("Uspesno ste odgovorili na %d/20 pitanja.\n", bodoviOdgovora / 10);
		printf("Za to Vam je bilo potrebno %.2lf sekundi.\n", vreme);
		printf("Postignutim rezultatom osvojili ste %d poena.\n", bodoviUkupno);

		upisiRezultat(username, bodoviUkupno, brojPitanja);
		najbolji = ucitajKorisnike(brojPitanja);
		najbolji.ime[strcspn(najbolji.ime, "\n")] = '\0';
		printf("Najbolji rezultat u odabranoj kategoriji ima korisnik %s sa %d poena.\n", najbolji.ime, najbolji.poeni);
	}
	else if (brojPitanja == 3) {
		printf("Uspesno ste odgovorili na %d/30 pitanja.\n", bodoviOdgovora / 10);
		printf("Za to Vam je bilo potrebno %.2lf sekundi.\n", vreme);
		printf("Postignutim rezultatom osvojili ste %d poena.\n", bodoviUkupno);

		upisiRezultat(username, bodoviUkupno, brojPitanja);
		najbolji = ucitajKorisnike(brojPitanja);
		najbolji.ime[strcspn(najbolji.ime, "\n")] = '\0';
		printf("Najbolji rezultat u odabranoj kategoriji ima korisnik %s sa %d poena.\n", najbolji.ime, najbolji.poeni);
	}

	return 0;
}

// Funkcija za ucitavanje pitanja
void ucitajPitanja(int kategorija, struct pitanje p[40]) {
	int i;
	FILE* f;

	if (kategorija == 1) {
		if (f = fopen(SVET, "r") != NULL) {
			f = fopen(SVET, "r");
			for (i = 0; i < 40; i++) {
				fgets(p[i].drzava, 20, (FILE*)f);
				fgets(p[i].grad, 20, (FILE*)f);
			}
			fclose(f);
		}
		else {
			printf("GRESKA: Fajl svet.txt nije pronadjen!\n");
			exit(0);
		}
	}
	else if (kategorija == 2) {
		if (f = fopen(EVROPA, "r") != NULL) {
			f = fopen(EVROPA, "r");
			for (i = 0; i < 40; i++) {
				fgets(p[i].drzava, 20, (FILE*)f);
				fgets(p[i].grad, 20, (FILE*)f);
			}
			fclose(f);
		}
		else {
			printf("GRESKA: Fajl evropa.txt nije pronadjen!\n");
			exit(0);
		}
	}
	else if (kategorija == 3) {
		if (f = fopen(AZIJA, "r") != NULL) {
			f = fopen(AZIJA, "r");
			for (i = 0; i < 40; i++) {
				fgets(p[i].drzava, 20, (FILE*)f);
				fgets(p[i].grad, 20, (FILE*)f);
			}
			fclose(f);
		}
		else {
			printf("GRESKA: Fajl azija.txt nije pronadjen!\n");
			exit(0);
		}
	}
	else if (kategorija == 4) {
		if (f = fopen(AFRIKA, "r") != NULL) {
			f = fopen(AFRIKA, "r");
			for (i = 0; i < 40; i++) {
				fgets(p[i].drzava, 20, (FILE*)f);
				fgets(p[i].grad, 20, (FILE*)f);
			}
			fclose(f);
		}
		else {
			printf("GRESKA: Fajl afrika.txt nije pronadjen!\n");
			exit(0);
		}
	}
}

// Funkcija za upisivanje rezultata
void upisiRezultat(char ime[20], int poeni, int brojPitanja) {
	FILE* f;
	if (brojPitanja == 1) {
		if (f = fopen(REZULTATI1, "a") != NULL) {
			f = fopen(REZULTATI1, "a");
			fputs(ime, (FILE*)f);
			fputs("\n", (FILE*)f);
			fprintf(f, "%d\n", poeni);
			fclose(f);
		}
		else {
			printf("GRESKA: Fajl rezultati1.txt nije pronadjen!\n");
			exit(0);
		}
	}
	else if (brojPitanja == 2) {
		if (f = fopen(REZULTATI2, "a") != NULL) {
			f = fopen(REZULTATI2, "a");
			fputs(ime, (FILE*)f);
			fputs("\n", (FILE*)f);
			fprintf(f, "%d\n", poeni);
			fclose(f);
		}
		else {
			printf("GRESKA: Fajl rezultati2.txt nije pronadjen!\n");
			exit(0);
		}
	}
	if (brojPitanja == 3) {
		if (f = fopen(REZULTATI3, "a") != NULL) {
			f = fopen(REZULTATI3, "a");
			fputs(ime, (FILE*)f);
			fputs("\n", (FILE*)f);
			fprintf(f, "%d\n", poeni);
			fclose(f);
		}
		else {
			printf("GRESKA: Fajl rezultati3.txt nije pronadjen!\n");
			exit(0);
		}
	}
}

// Funkcija za ucitavanje najboljeg rezultata
struct korisnik ucitajKorisnike(int brojPitanja) {
	FILE* f;
	struct korisnik v;
	struct korisnik m;
	int max = 0;

	if (brojPitanja == 1) {
		if (f = fopen(REZULTATI1, "r") != NULL) {
			f = fopen(REZULTATI1, "r");
			while (!feof(f)) {
				fgets(m.ime, 20, (FILE*)f);
				fscanf(f, "%d", &m.poeni);
				if (m.poeni > max) {
					max = m.poeni;
					v = m;
				}
			}
			fclose(f);
		}
		else {
			printf("GRESKA: Fajl rezultati1.txt nije pronadjen!\n");
			exit(0);
		}
	}
	else if (brojPitanja == 2) {
		if (f = fopen(REZULTATI2, "r") != NULL) {
			f = fopen(REZULTATI2, "r");
			while (!feof(f)) {
				fgets(m.ime, 20, (FILE*)f);
				fscanf(f, "%d", &m.poeni);
				if (m.poeni > max) {
					max = m.poeni;
					v = m;
				}
			}
			fclose(f);
		}
		else {
			printf("GRESKA: Fajl rezultati2.txt nije pronadjen!\n");
			exit(0);
		}
	}
	else if (brojPitanja == 3) {
		if (f = fopen(REZULTATI3, "r") != NULL) {
			f = fopen(REZULTATI3, "r");
			while (!feof(f)) {
				fgets(m.ime, 20, (FILE*)f);
				fscanf(f, "%d", &m.poeni);
				if (m.poeni > max) {
					max = m.poeni;
					v = m;
				}
			}
			fclose(f);
		}
		else {
			printf("GRESKA: Fajl rezultati3.txt nije pronadjen!\n");
			exit(0);
		}
	}

	return v;
}