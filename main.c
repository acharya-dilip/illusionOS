#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>


struct mainWidget {
    GtkWidget *windowMain;
    GtkWidget *gridParent;
    GtkWidget *buttonNotSoSpammy;
    GtkWidget *frameTopBar;
    GtkWidget *labelTime;
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
    gtk_widget_add_css_class(mainWidget.windowMain,"Desktop");

    //Init of gridParent
    mainWidget.gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(mainWidget.windowMain),mainWidget.gridParent);
    //Margins & Paddings
    gtk_widget_set_margin_start(mainWidget.gridParent,10);
    gtk_widget_set_margin_end(mainWidget.gridParent,10);

    //Init of frameTopBar
    mainWidget.frameTopBar = gtk_frame_new(NULL);
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent),mainWidget.frameTopBar,0,0,100,1);
    gtk_widget_set_size_request(mainWidget.frameTopBar,gtk_widget_get_width(mainWidget.windowMain),-1);
    gtk_widget_set_hexpand(mainWidget.frameTopBar, TRUE);
    gtk_widget_add_css_class(mainWidget.frameTopBar,"TopBar");

    //Init of labelTime
    mainWidget.labelTime = gtk_label_new("Dec 6  11:11 PM");
    gtk_frame_set_child(GTK_FRAME(mainWidget.frameTopBar),mainWidget.labelTime);
    gtk_widget_set_halign(mainWidget.labelTime,GTK_ALIGN_CENTER);

    //Init of buttonNotSoSpammy
    mainWidget.buttonNotSoSpammy = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent),mainWidget.buttonNotSoSpammy,0,1,1,2);
    gtk_widget_set_size_request(mainWidget.buttonNotSoSpammy,64,64);


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