#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

typedef struct Phone {
    char brand[50];
    char model[50];
    double price;
    int quantity;
    struct Phone *next;
} Phone;

Phone *warehouse = NULL;

Phone *create_phone(const char *brand, const char *model, double price, int quantity) {
    Phone *new_phone = (Phone *)malloc(sizeof(Phone));
    strcpy(new_phone->brand, brand);
    strcpy(new_phone->model, model);
    new_phone->price = price;
    new_phone->quantity = quantity;
    new_phone->next = NULL;
    return new_phone;
}

void add_phone(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Dodaj Telefon", GTK_WINDOW(data), GTK_DIALOG_MODAL, "Dodaj", GTK_RESPONSE_OK, "Anuluj", GTK_RESPONSE_CANCEL, NULL);
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *brand_entry = gtk_entry_new();
    GtkWidget *model_entry = gtk_entry_new();
    GtkWidget *price_entry = gtk_entry_new();
    GtkWidget *quantity_entry = gtk_entry_new();

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Marka:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), brand_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Model:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), model_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Cena:"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), price_entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Ilosc:"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), quantity_entry, 1, 3, 1, 1);

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        Phone *new_phone = create_phone(
            gtk_entry_get_text(GTK_ENTRY(brand_entry)),
            gtk_entry_get_text(GTK_ENTRY(model_entry)),
            atof(gtk_entry_get_text(GTK_ENTRY(price_entry))),
            atoi(gtk_entry_get_text(GTK_ENTRY(quantity_entry)))
        );
        new_phone->next = warehouse;
        warehouse = new_phone;
    }

    gtk_widget_destroy(dialog);
}

void delete_phone(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Usun Telefon", GTK_WINDOW(data), GTK_DIALOG_MODAL, "Usuń", GTK_RESPONSE_OK, "Anuluj", GTK_RESPONSE_CANCEL, NULL);
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *model_entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(content_area), model_entry);

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        const char *model_to_delete = gtk_entry_get_text(GTK_ENTRY(model_entry));
        Phone *current = warehouse, *prev = NULL;

        while (current) {
            if (strcmp(current->model, model_to_delete) == 0) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    warehouse = current->next;
                }
                free(current);
                g_print("Usunieto model: %s\n", model_to_delete);
                break;
            }
            prev = current;
            current = current->next;
        }
    }

    gtk_widget_destroy(dialog);
}

void search_phone(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Szukaj Telefonu", GTK_WINDOW(data), GTK_DIALOG_MODAL, "Szukaj", GTK_RESPONSE_OK, "Anuluj", GTK_RESPONSE_CANCEL, NULL);
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *search_entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(content_area), search_entry);

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        const char *search_term = gtk_entry_get_text(GTK_ENTRY(search_entry));
        Phone *current = warehouse;
        g_print("Wyniki wyszukiwania:\n");
        while (current) {
            if (strstr(current->brand, search_term) || strstr(current->model, search_term)) {
                g_print("Marka: %s, Model: %s, Cena: %.2f, Ilosc: %d\n", current->brand, current->model, current->price, current->quantity);
            }
            current = current->next;
        }
    }

    gtk_widget_destroy(dialog);
}

void update_phone(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Aktualizuj Telefon", GTK_WINDOW(data), GTK_DIALOG_MODAL, "Aktualizuj", GTK_RESPONSE_OK, "Anuluj", GTK_RESPONSE_CANCEL, NULL);
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *model_entry = gtk_entry_new();
    GtkWidget *price_entry = gtk_entry_new();
    GtkWidget *quantity_entry = gtk_entry_new();

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Model do aktualizacji:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), model_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Nowa Cena:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), price_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Nowa Ilosc:"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), quantity_entry, 1, 2, 1, 1);

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        const char *model_to_update = gtk_entry_get_text(GTK_ENTRY(model_entry));
        double new_price = atof(gtk_entry_get_text(GTK_ENTRY(price_entry)));
        int new_quantity = atoi(gtk_entry_get_text(GTK_ENTRY(quantity_entry)));

        Phone *current = warehouse;
        while (current) {
            if (strcmp(current->model, model_to_update) == 0) {
                current->price = new_price;
                current->quantity = new_quantity;
                g_print("Zaktualizowano model: %s\n", model_to_update);
                break;
            }
            current = current->next;
        }
    }

    gtk_widget_destroy(dialog);
}

void display_phones(GtkWidget *widget, gpointer data) {
    Phone *current = warehouse;
    g_print("Lista telefonow w magazynie:\n");
    while (current) {
        g_print("Marka: %s, Model: %s, Cena: %.2f, Ilosc: %d\n", current->brand, current->model, current->price, current->quantity);
        current = current->next;
    }
}

void clear_warehouse(GtkWidget *widget, gpointer data) {
    Phone *current = warehouse;
    while (current) {
        Phone *to_delete = current;
        current = current->next;
        free(to_delete);
    }
    warehouse = NULL;
    g_print("Magazyn wyczyszczony.\n");
}

void count_phones(GtkWidget *widget, gpointer data) {
    int count = 0;
    Phone *current = warehouse;
    while (current) {
        count++;
        current = current->next;
    }
    g_print("Liczba telefonów w magazynie: %d\n", count);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *add_button, *delete_button, *search_button, *update_button, *list_button, *clear_button, *count_button, *exit_button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Magazyn Telefonow");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 135);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    add_button = gtk_button_new_with_label("Dodaj Telefon");
    g_signal_connect(add_button, "clicked", G_CALLBACK(add_phone), window);
    gtk_grid_attach(GTK_GRID(grid), add_button, 0, 0, 1, 1);

    delete_button = gtk_button_new_with_label("Usun Telefon");
    g_signal_connect(delete_button, "clicked", G_CALLBACK(delete_phone), window);
    gtk_grid_attach(GTK_GRID(grid), delete_button, 1, 0, 1, 1);

    search_button = gtk_button_new_with_label("Szukaj Telefonu");
    g_signal_connect(search_button, "clicked", G_CALLBACK(search_phone), window);
    gtk_grid_attach(GTK_GRID(grid), search_button, 0, 1, 1, 1);

    update_button = gtk_button_new_with_label("Aktualizuj Telefon");
    g_signal_connect(update_button, "clicked", G_CALLBACK(update_phone), window);
    gtk_grid_attach(GTK_GRID(grid), update_button, 1, 1, 1, 1);

    list_button = gtk_button_new_with_label("Wyswietl Liste");
    g_signal_connect(list_button, "clicked", G_CALLBACK(display_phones), window);
    gtk_grid_attach(GTK_GRID(grid), list_button, 0, 2, 1, 1);

    clear_button = gtk_button_new_with_label("Wyczysc Magazyn");
    g_signal_connect(clear_button, "clicked", G_CALLBACK(clear_warehouse), window);
    gtk_grid_attach(GTK_GRID(grid), clear_button, 1, 2, 1, 1);

    count_button = gtk_button_new_with_label("Policz Telefony");
    g_signal_connect(count_button, "clicked", G_CALLBACK(count_phones), window);
    gtk_grid_attach(GTK_GRID(grid), count_button, 0, 3, 1, 1);

    exit_button = gtk_button_new_with_label ("Wyjscie");
    g_signal_connect_swapped (exit_button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_grid_attach (GTK_GRID(grid), exit_button, 1, 3, 1, 1);

    gtk_widget_show_all(window);
}

int main (int    argc, char **argv){
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.magazyn", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}