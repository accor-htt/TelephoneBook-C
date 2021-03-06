#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

typedef struct
{
	char *name;			// Имя контакта
	char *phone;		// Телефон
} Contact;

typedef struct
{
	char letter;		// Буква страницы
	Contact *contacts;	// Список контактов
	int countCont;		// Кол-во контактов
} Page;

typedef struct
{
	Page pages[32];		// Список страниц
	int countPage;		// Кол-во страниц
} Book;


// Функция выделяет память под пустой (обнуляется указатель и переменная кол-ва)
// телефонный справочник.
Book *createBook();

// Функция выводит текстовое меню приветствия программы
void showMenu();

// Функция создает контакт
bool createContact(Book *b);

// Функция загружает файл с сохраненной структурой
Book * loadData(char *path);

void sortingData(Book *b);

// Функция сохраняет файл с созданной структурой
void save(Book *b);

// Функиця выводит на экран полный список всех контактов
void showBook(Book *b);

// Функция изменяет имя (если оно находится в справочнике) на имя, введенное пользователем
bool changeName(Book *b, char *name, char *ch_name);

// Функция изменяет номер телефона (если оно находится в справочнике) на телефон, введенный пользователем
bool changePhone(Book *b, char *phone, char *ch_phone);

// Функция возвращает указатель на страницу с буквой letter из книги b.
// Если страницы не существует, то возвращается NULL.
Page *searchPage(Book *b, char letter);

// Функция возвращает указатель на контакт с заданным именем.
// Если страницы не существует то возвращается NULL
Contact *searchContactByName(Book *b, char *name);

// Функция возвращает указатель на контакт с заданным телефоном.
// Если страницы не существует то возвращается NULL
Contact *searchContactByPhone(Book *b, char *phone);

// Функция заполняет объект структуры Contact передаваемыми значениями name и
// phone. Содержимое name и phone копируется побайтово, а не сохраняется
// как указатель.
void fillContact(const char *name, const char *phone, Contact *c);

// Функция отображает найденый контакт по введеному имени для поиска
void showContactWithName(Book *b, char *name);

// Функция отображает найденый контакт по введеному телефону для поиска
void showContactWithPhone(Book *b, char *phone);

// Очищает выделенную под телефонный справочник память. После вызова функции
// телефонный справочник использовать нельзя.
void deleteBook(Book *book);

// Очищает переданную страницу, удаляя список контактов.
void deletePage(Page *page);

// Очищает запись контакта.
//void deleteContact(Book *b, char *name);
bool deleteContact(Book * b, char * name);

int main()
{
	system("chcp 1251");
	system("cls");

	Book *book = NULL;
	int choose;
	showMenu();

	printf("\nВаш выбор : ");
	scanf("%d", &choose);

	if (choose == 1)
	{
		book = createBook();
	}
	else if (choose == 2)
	{
		char path[30];
		printf("\nВведите название файла в папке: ");
		scanf("%s", path);
		book = loadData(path);

		if (!book)
		{
			printf("Загрузка не удалась или файл не существует.\n");
			system("pause>null");
			return NULL;
		}
	}
	else
		exit(0);

	int check;
	char switchName[100];
	char switchPhone[100];

	do
	{
		system("cls");
		int num;
		printf("Выберите необходимое действие:\n"
			" 1. Добавить контакт\n 2. Показать книгу\n 3. Поиск по имени\n 4. Поиск по телефону\n"
			" 5. Изменить имя\n 6. Изменить телефон\n 7. Удалить запись\n 8. Сохранение\n 0. Выход\n");
		printf("Ваш выбор : ");
		scanf("%d", &num);
		printf("\n");

		switch (num)
		{
		case 1: // Добавить контакт
			if (createContact(book))
			{
				save(book);
			}
			break;

		case 2:  // Показать книгу
			showBook(book);
			break;

		case 3: // Поиск по имени
			printf("Введите имя для поиска: ");
			scanf("%s", switchName);
			showContactWithName(book, switchName);
			break;

		case 4: // Поиск по телефону
			
			printf("Введите телефон для поиска: ");
			scanf("%s", switchPhone);
			showContactWithPhone(book, switchPhone);
			break;

		case 5: // Изменить имя
			showBook(book);
			char bufName[100];
			printf("Введите имя для изменения: ");
			scanf("%s", switchName);
			printf("Изменение имени: ");
			scanf("%s", bufName);

			if (changeName(book, switchName, bufName))
			{
				printf("Имя успешно измененно\n");
			}
			//sortingData(book);
			break;

		case 6: // Изменить телефон
			showBook(book);
			char bufPhone[100];
			printf("Введите телефон для изменения: ");
			scanf("%s", switchPhone);
			printf("Изменение телефона: ");
			scanf("%s", bufPhone);

			if (changePhone(book, switchPhone, bufPhone))
			{
				printf("Телефон успешно изменен\n");
			}
			break;

		case 7: // Удалить запись
			showBook(book);
			printf("Введите имя для удаления: ");
			scanf("%s", switchName);
			if (deleteContact(book, switchName))
			{
				printf("Контакт успешно удален");
			}
			break;

		case 8: // Сохранение
			save(book);
			break;

		//case 9:  // Обновление
			//printf("База данных обновлена");
			//break;

		case 0: // Выход
			deleteBook(book);
			exit(0);
			break;
		}
		printf("\n/1 - Вызвать меню\t/0 - Закрыть программу\n");
		scanf_s("%d", &check);
	} while (check != 0);

	int variant;
	printf("Сохранить данные(1 - да, 0 - нет) : ");
	scanf("%d", &variant);
	if (variant == 1)
	{
		save(book);
	}
	else if (variant == 0)
	{
		printf("\nХорошо\n");
	}

	printf("\nОчистка памяти...\n");
	deleteBook(book);

	printf("Закрытие программы.\n");

	system("pause");
	return 0;
}

Book *createBook()
{
	Book *newBook = (Book*)malloc(sizeof(Book));

	if (newBook)
	{
		newBook->countPage = 32;

		for (int i = 0; i < newBook->countPage; i++)
		{
			newBook->pages[i].contacts = NULL;
			newBook->pages[i].countCont = 0;
			newBook->pages[i].letter = 'А' + i;
		}
	}

	return newBook;
}

void showMenu()
{
	printf("---Телефонная книга---\n\n");
	printf("\n");
	printf(" 1. Создать новую\n");
	printf(" 2. Открыть\n");
	printf(" 3. Отказаться\n");
}

Book * loadData(char *path)
{
	FILE *f = fopen(path, "r");

	if (!f)
		return NULL;

	Book *b = createBook();

	if (!b)
		return NULL;

	if (f != NULL)
	{
		char *name;
		char *phone;

		while (!feof(f))
		{
			name = (char *)malloc(sizeof(char) * 100);
			phone = (char *)malloc(sizeof(char) * 100);
			fscanf(f, "%s %s", name, phone);

			if (feof(f))
				break;
			name = (char *)realloc(name, strlen(name) + 1);
			phone = (char *)realloc(phone, strlen(phone) + 1);

			// Взяли текущее кол-во контактов и увеличили на 1. 
			int j = b->pages[name[0] - 'А'].countCont++;
			b->pages[name[0] - 'А'].contacts = (Contact *)realloc(b->pages[name[0] - 'А'].contacts, sizeof(Contact) * (j + 1));
			b->pages[name[0] - 'А'].contacts[j].name = name;
			b->pages[name[0] - 'А'].contacts[j].phone = phone;
		}

		fclose(f);
	}

	return b;
}

void sortingData(Book *b)
{
	char *temp;
	int i, j;

	temp = (char*)malloc(sizeof(char) * 100);

	for (i = 1; i < b->countPage; i++)
	{
		for (j = 0; j < b->pages->countCont; ++j)
		{
			if (strcmp(b->pages[i].contacts[j].name, b->pages[i].contacts[j + 1].name) < 0)
			{
				strcpy(temp, b->pages[i].contacts[j].name);
				strcpy(b->pages[i].contacts[j].name, b->pages[i].contacts[j + 1].name);
				strcpy(b->pages[i].contacts[j + 1].name, temp);
			}
		}
	}
}

void save(Book *b)
{
	int i = 0, j = 0;
	FILE *f;

	f = fopen("phonebook.txt", "w");
	for (i = 0; i < b->countPage; i++)
	{
		for (j = 0; j < b->pages[i].countCont; j++)
		{
			fprintf(f, "%s %s\n", b->pages[i].contacts[j].name, b->pages[i].contacts[j].phone);
		}
	}
	printf("Ваш файл успешно сохранен");
	fclose(f);
}

bool createContact(Book *b)
{
	char name[100];
	char phone[100];

	do
	{
		printf("Имя : ");
		scanf("%s", name);
		printf("Номер : ");
		scanf("%s", phone);
		printf("\n");

		if (name[0] < 'А' || name[0] > 'Я')
		{
			printf("Возможны имена начинающиеся только с русских заглавных букв (кроме Ё, Ь, Ъ)\n");
		}

		if (searchContactByName(b, name))
		{
			printf("Такой контакт уже существует\n");
			return NULL;
		}

	} while (name[0] < 'А' || name[0] > 'Я');
	int i = name[0] - 'А';
	Page *p = b->pages + (name[0] - 'А');

	// Добавляем контакт на страницу
	int j = p->countCont++;
	p->contacts = (Contact*)realloc(p->contacts, sizeof(Contact) * p->countCont);
	p->contacts[j].name = NULL;
	p->contacts[j].phone = NULL;

	// Заполняем полученный пустой контакт новыми значениями
	fillContact(name, phone, p->contacts + (p->countCont - 1));
	return true;
}

Page *searchPage(Book *b, char letter)
{
	Page *searchP = NULL;
	if (b)
	{
		int i;

		for (i = 0; i < b->countPage; ++i)
		{
			if (b->pages[i].letter == letter)
			{
				searchP = b->pages + i;
				break;
			}
		}
	}

	return searchP;
}

void fillContact(const char *name, const char *phone, Contact *c)
{
	if (c)
	{
		if (c->name)
			free(c->name);
		c->name = (char*)malloc(strlen(name) + 1);
		strcpy(c->name, name);

		if (c->phone)
			free(c->phone);
		c->phone = (char*)malloc(strlen(phone) + 1);
		strcpy(c->phone, phone);
	}
}

void showBook(Book *b)
{
	int i, j;

	printf("|\tИмя\t|\tТелефон\t|\n");
	for (i = 0; i < b->countPage; ++i)
	{
		for (j = 0; j < b->pages[i].countCont; ++j)
		{
			printf("|\t%s\t|\t%s\t|\n", b->pages[i].contacts[j].name, b->pages[i].contacts[j].phone);
		}
	}
}

void showContactWithName(Book *b, char *name)
{
	if (b)
	{
		Contact *c = searchContactByName(b, name);
		if (c)
		{
			printf("Фамилия: %s\n", c->name);
			printf("Номер: %s\n", c->phone);
		}
		else
		{
			printf("Такого контакта не существует");
		}
	}
}

void showContactWithPhone(Book *b, char *phone)
{
	if (b)
	{
		Contact *c = searchContactByPhone(b, phone);
		if (c)
		{
			printf("Фамилия: %s\n", c->name);
			printf("Номер: %s\n", c->phone);
		}
		else
		{
			printf("Такого контакта не существует");
		}
	}
}

Contact *searchContactByName(Book *b, char *name)
{
	Contact *searchN = NULL;

	if (b)
	{
		int i, j;

		for (i = 0; i < b->countPage; ++i)
		{
			for (j = 0; j < b->pages[i].countCont; ++j)
			{
				if (strcmp(b->pages[i].contacts[j].name, name) == 0)
				{
					searchN = b->pages[i].contacts + j;
					break;
				}
			}
		}
	}

	return searchN;
}

Contact *searchContactByPhone(Book *b, char *phone)
{
	Contact *searchP = NULL;

	if (b)
	{
		int i, j;

		for (i = 0; i < b->countPage; ++i)
		{
			for (j = 0; j < b->pages[i].countCont; ++j)
			{
				if (strcmp(b->pages[i].contacts[j].phone, phone) == 0)
				{
					// Разъименовываем 
					searchP = &b->pages[i].contacts[j];
					break;
				}
			}
		}
	}

	return searchP;
}

bool changeName(Book *b, char *name, char *ch_name)
{
	if (b)
	{
		Contact *c = searchContactByName(b, name);

		if (c)
		{
			// Запоминаем телефон.
			char *phone = c->phone;
			c->phone = NULL;
			// Удаляем старый контакт.
			deleteContact(b, name);

			// ПО СУТИ КОД createContact(), но без ввода. Если убрать ввод,
			// то можно использовать ее.
			// Плучаем нужную страницу. Увеличиваем размер contacts
			Page * p = b->pages + (ch_name[0] - 'А');
			
			// Стерли контакт, следовательно нам нужно увеличить количество контактов, на заменяемый. 
			int j = p->countCont++;

			// Возвращаем прежний размер
			p->contacts = (Contact*)realloc(p->contacts, sizeof(Contact) * p->countCont);
			// Обнуляем 
			p->contacts[j].name = NULL;
			p->contacts[j].phone = NULL;

			// Заполняем полученный пустой контакт новыми значениями
			fillContact(ch_name, phone, p->contacts + (p->countCont - 1));
			return true;
		}
		printf("Контакт не найден\n");
	}

	return false;
}

bool changePhone(Book *b, char *phone, char *ch_phone)
{
	if (b)
	{
		Contact *c = searchContactByPhone(b, phone);
		if (c)
		{
			// ВЫЗОВ НЕ ПРАВИЛЬНЫЙ. Размер c->phone может быть < 100 и поэтому
			// это может спровоцировать ошибки.
			//strcpy_s(c->phone, 100, ch_phone);
			c->phone = (char *)realloc(c->phone, (strlen(ch_phone) + 1) * sizeof(char));
			strcpy(c->phone, ch_phone);
			return true;
		}
		printf("Телефон не найден\n");
	}

	return false;
}

void deleteBook(Book *book)
{
	int i;

	if (book)
	{
		if (book->pages)
		{
			for (i = 0; i < book->countPage; ++i)
				deletePage(book->pages + i);
		}
		free(book);
	}
}

void deletePage(Page *page)
{
	int i;

	if (page)
	{
		for (i = 0; i < page->countCont; ++i)
		{
			free(page->contacts[i].name);
			free(page->contacts[i].phone);
		}

		free(page->contacts);
		page->countCont = 0;
	}

}

bool deleteContact(Book * b, char * name)
{
	if (b)
	{
		Page * p = b->pages + (name[0] - 'А');
		Contact *c = searchContactByName(b, name);

		if (c == NULL)
		{
			printf("Такая запись не найдена");
			return NULL;
		}

		if (c->name)
			free(c->name);
		if (c->phone)
			free(c->phone);

		// Получаем индекс контакта.
		int iContact = c - p->contacts;

		for (int i = iContact; i < p->countCont - 1; ++i)
		{
			p->contacts[i].name = p->contacts[i + 1].name;
			p->contacts[i].phone = p->contacts[i + 1].phone;
		}

		p->countCont--;
		p->contacts = (Contact*)realloc(p->contacts, sizeof(Contact) * p->countCont);
		return true;
	}
}