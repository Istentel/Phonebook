#include <stdio.h>
#include <conio.h>
#include <windows.h>

struct agenda {
	char nume[20];
	char prenume[20];
	char numar[15];
	char detalii[50];
};

void exists() {
	FILE* file;
	if ((file = fopen("numar.txt", "r")) != NULL)
	{
		fclose(file);
		return;
	}


	if ((file = fopen("numar.txt", "a")) != NULL) {
		fputs("0\n\n", file);
		fputs("4", file);
		//fputs("0", file);
		fclose(file);
		return;
	}
}

void saveNumber(int nrContact) {
	FILE* numar;
	numar = fopen("numar.txt", "r+");
	if (numar == NULL) {
		fprintf(stderr, "\nEroare deschidere fisier\n");
		exit(1);
	}

	fseek(numar, 0, SEEK_CUR);
	fprintf(numar, "%d", nrContact);
	//fseek(numar, 0, SEEK_CUR);

	fclose(numar);
	return;
}

int getNumber() {
	int nr, size;
	FILE* numar;
	numar = fopen("numar.txt", "a+");
	if (numar == NULL) {
		fprintf(stderr, "\nEroare deschidere fisier\n");
		exit(1);
	}
	else {
		if (NULL != numar) {
			fseek(numar, 0, SEEK_END);
			size = ftell(numar);

			if (0 == size) {
				return 0;
			}
		}

		//fseek(numar, 0, SEEK_CUR);
		rewind(numar);
		fscanf(numar, "%d", &nr);

		fclose(numar);
		return nr;
	}
}

struct agenda verificareNumar(struct agenda* contact) {
	int ans, nr;
	FILE* numar;
	if ((numar = fopen("numarverificare.txt", "r")) != NULL) {
		fscanf(numar, "%d", &nr);
		fclose(numar);
		
	}
	else {
		nr = 0;
	}
	if (nr == 0) {
		if (strlen((*contact).numar) != 10) {
			if (strlen((*contact).numar) > 10 || strlen((*contact).numar) < 10) {
				printf("Numarul introdus nu este corect doriti sa il reintroduceti(1/0): ");
				scanf("%d", &ans);
				if (ans == 1) {
					printf("\nNumar: ");
					scanf("%s", &contact->numar);
					verificareNumar(contact);
				}
			}
		}
	}
	
}

void adaugare() {
	int nr = getNumber();
	FILE* date;
	struct agenda contacte[20];
	date = fopen("data.txt", "a+");
	if (date == NULL) {
		fprintf(stderr, "Eroare deschidere fisier.\n");
		exit(1);
	}

	printf("Nume: ");
	scanf("%s", &contacte[nr].nume);

	printf("Prenume: ");
	scanf("%s", &contacte[nr].prenume);

	printf("Numar: ");
	scanf("%s", &contacte[nr].numar);

	verificareNumar(&contacte[nr]);

	printf("Detalii: ");
	scanf("%s", &contacte[nr].detalii);

	fwrite(&contacte[nr], sizeof(struct agenda), 1, date);

	if (fwrite != 0)
		printf("Contactul a fost salvat cu succes!\n");
	else
		printf("Eroare salvare contact!\n");

	saveNumber(nr+1);
	fclose(date);
	//system("pause");
	return;
}

void modificareContact() {
	struct agenda contactNou;
	int nr;
	FILE* date;
	date = fopen("data.txt", "r+");
	if (date == NULL) {
		fprintf(stderr, "Eroare deschidere fisier!\n");
	}
	if (getNumber() == 0) {
		printf("Nu aveti nici un numar de modificat!\n");
		system("pause");
		return;
	}
	do {
		printf("Introduceti numarul contactului pe care doriti sa il modificati: ");
		scanf("%d", &nr);
		if (nr < 0 || nr > getNumber()) 
			printf("Contactul nu exista!\n");
	} while (nr < 0 || nr > getNumber());

	printf("Nume: ");
	scanf("%s", &contactNou.nume);

	printf("Prenume: ");
	scanf("%s", &contactNou.prenume);

	printf("Numar: ");
	scanf("%s", &contactNou.numar);

	verificareNumar(&contactNou);

	printf("Detalii: ");
	scanf("%s", &contactNou.detalii);

	fseek(date, (nr-1)*sizeof(struct agenda), SEEK_SET);
	fwrite(&contactNou, sizeof(struct agenda), 1, date);

	if (fwrite != 0)
		printf("Contactul a fost modificat cu succes!\n");
	else
		printf("Eroare modificare contact!\n");

	fclose(date);
	return;
}

void stergereContacte() {
	int nr;
	FILE* date;
	date = fopen("data.txt", "w");
	if (date == NULL) {
		fprintf(stderr, "Eroare deschidere fisier!\n");
	}
	saveNumber(0);
	fclose(date);
	return;
}

void afisareContacte() {
	FILE* date;
	int i = 1;
	struct agenda contacte;
	date = fopen("data.txt", "a+");

	if (date == NULL) {
		fprintf(stderr, "\nEroare deschidere fisier!\n");
		exit(1);
	}

	if (date != NULL) {
		fseek(date, 0, SEEK_END);
		if (ftell(date) == 0) {
			printf("Nu aveti nici un contact.\n");
		}
	}
	fseek(date, 0, SEEK_SET);
	while (fread(&contacte, sizeof(struct agenda), 1, date)) {
		printf("%d. %s %s %s %s\n", i, contacte.nume, contacte.prenume, contacte.numar, contacte.detalii);
		i++;
	}

	fclose(date);
}

int getCuloare() {
	FILE* numar;
	int culoare;
	if ((numar = fopen("numar.txt", "r")) == NULL) {
		printf("Eroare deschidere fisier.\n");
		exit(1);
	}
	else {
		fseek(numar, 1, SEEK_SET);
		fseek(numar, 1, SEEK_CUR);
		fscanf(numar, "%d", &culoare);
		if (culoare < 1 || culoare > 14) {
			fclose(numar);
			int nr = getNumber();
			numar = fopen("numar.txt", "w");
			fprintf(numar, "%d", nr);
			fclose(numar);
			return 10;
		}
		fclose(numar);
		return culoare;
	}
}


void schimbareCuloareMeniu() {
	system("cls");
	FILE* numar;
	int culoare;
	printf("Blue - 1\nGreen - 2\nCyan - 3\nRed - 4\nMagenta - 5\nBrown - 6\nLightgray - 7\nDarkgary - 8\nLightBlue - 9\nLightGreen - 10\nLightCyan - 11\nLightRed - 12\nLightMagenta - 13\nYellow - 14\n");
	do {
		printf("Introduceti numarul culorii dorite:");
		scanf("%d", &culoare);
		if (culoare < 1 || culoare >14)
			printf("Numarul trebuie sa fie cuprins intre 1 si 14.\n");
	} while (culoare < 1 || culoare >14);
	if ((numar = fopen("numar.txt", "r+")) == NULL) {
		printf("Eroare deschidere fisier.\n");
	}
	else {
		fseek(numar, 1, SEEK_SET);
		fseek(numar, 1, SEEK_CUR);
		fprintf(numar, "\n%d", culoare);
		//fseek(numar, 0, SEEK_CUR);
		fclose(numar);
	}
}

void dezactivareVerificare() {
	FILE *numar;
	int nr;
	system("cls");
	do {
		printf("Doriti sa dezactivati verificarea numarului de telefon(1/0): ");
		scanf("%d", &nr);
		if (nr < 0 || nr>1)
			printf("Numarul introdus trebuie sa fie 1 sau 0.\n");
	} while (nr < 0 || nr>1);
	if ((numar = fopen("numarverificare.txt", "w")) != NULL) {
		rewind(numar);
		fprintf(numar,"%d", nr);
		if(nr == 1)
			printf("Functia se va dezactiva dupa restartarea programului\n");
		else
			printf("Functia se va activa dupa restartarea programului\n");
		system("pause");

	}
	else {
		printf("Eroare deschidere fisier dezacticare numar.");
		exit(1);
	}

}

void optiuni() {
	char* meniu[3] = { "Schimbare culoare meniu\n", "Dezactivare verificare numar\n","Iesire optiuni\n" };
	int pointer = 0;
	int nr = 0;

	while (1) {
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		
		for (int i = 0; i < 3; i++) {
			if (i == pointer) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), getCuloare());
				printf("%s", meniu[i]);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("%s", meniu[i]);
			}
		}
		while (1) {
			nr = getch();
			if (nr == 72) {
				pointer -= 1;
				if (pointer == -1) {
					pointer = 2;
				}
				break;
			}
			else if (nr == 80) {
				pointer += 1;
				if (pointer == 3) {
					pointer = 0;
				}
				break;
			}
			else if (nr == 10 || nr == 13) {

				switch (pointer) {
				case 0: {schimbareCuloareMeniu(); break; }
				case 1: {dezactivareVerificare(); break; }
				case 2: {return; }
				}
				break;
			}
			break;
		}
		
	}
}

void main() {
	char* meniu[5] = {"Agaugare contact\n", "Editare contact\n", "Stergere contacte\n", "Optiuni\n", "Iesire\n"};
	int pointer = 0;
	int nr = 0;
	exists();

	while (1) {
		fflush(stdin);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		afisareContacte();
		printf("\tMeniu\n");
		
		for (int i = 0; i < 5; i++) {
			if (i == pointer) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), getCuloare());
				printf("%s", meniu[i]);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("%s", meniu[i]);
			}
		}
		while (1) {
			
			nr = getch();
			if (nr == 72) {
				pointer -= 1;
				if (pointer == -1) {
					pointer = 4;
				}
				break;
			}
			else if (nr == 80) {
				pointer += 1;
				if (pointer == 5) {
					pointer = 0;
				}
				break;
			}
			else if (nr == 10 || nr == 13) {

				switch (pointer) {
				case 0: {adaugare(); break; }
				case 1: {modificareContact(); break; }
				case 2: {stergereContacte(); break; }
				case 3: {optiuni(); break; }
				case 4: {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); return 0; }
				}
				break;
			}
			break;
		}
		//Sleep(150);
	}
}