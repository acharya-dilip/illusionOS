#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>


struct mainWidget {
    GtkWidget *windowMain;
    GtkWidget *gridParent;
}mainWidget;
static void activate (GtkApplication *app,gpointer user_data) {

    //Connects the styles.css file to the software
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "styles.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    //Init of windowMain
    mainWidget.windowMain = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(mainWidget.windowMain),"IllusionOS");
    gtk_window_present(GTK_WINDOW(mainWidget.windowMain));
    gtk_window_fullscreen(GTK_WINDOW(mainWidget.windowMain));

    //Init of gridParent
    mainWidget.gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(mainWidget.windowMain),mainWidget.gridParent);

}


int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    app= gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}