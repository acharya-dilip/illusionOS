#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

#include "NotSoSpammy.h"
#include "SendyMaily.h"
#include "ThreeEyedRaven.h"


struct mainWidget {
    GtkWidget *windowMain;
    GtkWidget *gridParent;
    GtkWidget *buttonNotSoSpammy;
    GtkWidget *frameTopBar;
    GtkWidget *labelTime;
    GtkWidget *buttonSendyMaily;
    GtkWidget *buttonThreeEyedRaven;
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


    //Init of frameTopBar
    mainWidget.frameTopBar = gtk_frame_new(NULL);
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent),mainWidget.frameTopBar,0,0,100,1);
    gtk_widget_set_size_request(mainWidget.frameTopBar,gtk_widget_get_width(mainWidget.windowMain),-1);
    gtk_widget_set_hexpand(mainWidget.frameTopBar, TRUE);
    gtk_widget_add_css_class(mainWidget.frameTopBar,"TopBar");
    //Margins & Paddings

    //Init of labelTime
    mainWidget.labelTime = gtk_label_new("Dec 6  11:11 PM");
    gtk_frame_set_child(GTK_FRAME(mainWidget.frameTopBar),mainWidget.labelTime);
    gtk_widget_set_halign(mainWidget.labelTime,GTK_ALIGN_CENTER);

    //Init of buttonNotSoSpammy
    mainWidget.buttonNotSoSpammy = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent),mainWidget.buttonNotSoSpammy,0,1,1,1);
    gtk_widget_set_size_request(mainWidget.buttonNotSoSpammy,84,84);
    gtk_widget_add_css_class(mainWidget.buttonNotSoSpammy,"DesktopIcon");
    gtk_widget_add_css_class(mainWidget.buttonNotSoSpammy,"IconNotSoSpammy");
    g_signal_connect(mainWidget.buttonNotSoSpammy,"clicked",G_CALLBACK(NotSoSpammy),NULL);

    //Init of buttonSendyMaily
    mainWidget.buttonSendyMaily = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent),mainWidget.buttonSendyMaily,1,1,1,1);
    gtk_widget_set_size_request(mainWidget.buttonSendyMaily,84,84);
    gtk_widget_add_css_class(mainWidget.buttonSendyMaily,"DesktopIcon");
    gtk_widget_add_css_class(mainWidget.buttonSendyMaily,"IconSendyMaily");
    g_signal_connect(mainWidget.buttonSendyMaily,"clicked",G_CALLBACK(SendyMaily),NULL);

    //Init of buttonThreeEyedRaven
    mainWidget.buttonThreeEyedRaven = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent),mainWidget.buttonThreeEyedRaven,0,2,1,2);
    gtk_widget_set_size_request(mainWidget.buttonThreeEyedRaven,84,84);
    gtk_widget_add_css_class(mainWidget.buttonThreeEyedRaven,"DesktopIcon");
    gtk_widget_add_css_class(mainWidget.buttonThreeEyedRaven,"IconSendyMaily");
    g_signal_connect(mainWidget.buttonThreeEyedRaven,"clicked",G_CALLBACK(ThreeEyedRaven),NULL);
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