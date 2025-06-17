#include <gtk/gtk.h>
#include "../../model/triage_queue/triage_queue.h"

void showTriageQueueGUI(TriageQueue* queue) {
    gtk_init(NULL, NULL);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fila de Atendimento - Protocolo de Manchester");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);

    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    TriageNode* current = queue->front;
    while (current != NULL) {
        const char* color;
        switch (current->triage->priority) {
            case RED:
                color = "red";
                break;
            case ORANGE:
                color = "orange";
                break;
            case YELLOW:
                color = "yellow";
                break;
            case GREEN:
                color = "green";
                break;
            case BLUE:
                color = "blue";
                break;
            default:
                color = "black";
                break;
        }

        char markup[512];
        snprintf(markup, sizeof(markup),
                 "<span foreground=\"%s\" weight=\"bold\">ID: %ld | Paciente ID: %ld | Prioridade: %d</span>",
                 color,
                 current->triage->id,
                 current->triage->patientId,
                 current->triage->priority
        );

        GtkWidget* label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(label), markup);
        gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

        current = current->next;
    }

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}
