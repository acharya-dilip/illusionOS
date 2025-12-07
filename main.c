#include "main.h"

#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

#include "JustaGuiFramework.h"
#include "NotSoNotFallty.h"
#include "NotSoNotSecure.h"
#include "NotSoNotSpooky.h"
#include "NotSoSpacy.h"
#include "NotSoSpammy.h"
#include "SendyMaily.h"
#include "ThreeEyedRaven.h"

gboolean updateTopBarTime(gpointer user_data);
//Global Variable
GtkWindow *windowMainDesktop;
struct mainWidget {
    GtkWidget *gridParent;
    GtkWidget *frameTopBar;
    GtkWidget *labelTime;
    GtkWidget *buttonNotSoNotFallty;
    GtkWidget *buttonJustaGuiFramework;
    GtkWidget *buttonNotSoSpacy;
    GtkWidget *buttonNotSoNotSpooky;
} mainWidget;

static void activate(GtkApplication *app, gpointer user_data) {
    //Connects the styles.css file to the software
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "styles.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    //Init of windowMain
    windowMainDesktop = GTK_WINDOW(gtk_application_window_new(app));
    gtk_window_set_title(GTK_WINDOW(windowMainDesktop), "IllusionOS");
    gtk_window_present(GTK_WINDOW(windowMainDesktop));
    gtk_window_fullscreen(GTK_WINDOW(windowMainDesktop));
    gtk_widget_add_css_class(GTK_WIDGET(windowMainDesktop), "Desktop");



    //Init of gridParent
    mainWidget.gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowMainDesktop), mainWidget.gridParent);


    //Init of frameTopBar
    mainWidget.frameTopBar = gtk_frame_new(NULL);
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent), mainWidget.frameTopBar, 0, 0, 100, 1);
    gtk_widget_set_size_request(mainWidget.frameTopBar, gtk_widget_get_width(GTK_WIDGET(windowMainDesktop)), -1);
    gtk_widget_set_hexpand(mainWidget.frameTopBar, TRUE);
    gtk_widget_add_css_class(mainWidget.frameTopBar, "TopBar");
    //Margins & Paddings

    //Init of labelTime
    mainWidget.labelTime = gtk_label_new("Dec 6  11:11 PM");
    gtk_frame_set_child(GTK_FRAME(mainWidget.frameTopBar), mainWidget.labelTime);
    gtk_widget_set_halign(mainWidget.labelTime, GTK_ALIGN_CENTER);
    updateTopBarTime(NULL);
    g_timeout_add_seconds(15,updateTopBarTime, mainWidget.labelTime);

    //Init of buttonNotSoSpammy
    GtkWidget *buttonNotSoSpammy = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent), buttonNotSoSpammy, 0, 1, 1, 1);
    gtk_widget_set_size_request(buttonNotSoSpammy, 84, 84);
    gtk_widget_add_css_class(buttonNotSoSpammy, "DesktopIcon");
    gtk_widget_add_css_class(buttonNotSoSpammy, "IconNotSoSpammy");
    g_signal_connect(buttonNotSoSpammy, "clicked", G_CALLBACK(NotSoSpammy), NULL);
    gtk_widget_set_hexpand(buttonNotSoSpammy,FALSE);
    gtk_widget_set_vexpand(buttonNotSoSpammy,FALSE);


    //Init of buttonSendyMaily
    GtkWidget *buttonSendyMaily = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent), buttonSendyMaily, 1, 1, 1, 1);
    gtk_widget_set_size_request(buttonSendyMaily, 84, 84);
    gtk_widget_add_css_class(buttonSendyMaily, "DesktopIcon");
    gtk_widget_add_css_class(buttonSendyMaily, "IconSendyMaily");
    g_signal_connect(buttonSendyMaily, "clicked", G_CALLBACK(SendyMaily), NULL);
    gtk_widget_set_hexpand(buttonSendyMaily,FALSE);
    gtk_widget_set_vexpand(buttonSendyMaily,FALSE);

    //Init of buttonThreeEyedRaven
    GtkWidget *buttonThreeEyedRaven = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent), buttonThreeEyedRaven, 0, 2, 1, 1);
    gtk_widget_set_size_request(buttonThreeEyedRaven, 84, 84);
    gtk_widget_add_css_class(buttonThreeEyedRaven, "DesktopIcon");
    gtk_widget_add_css_class(buttonThreeEyedRaven, "IconThreeEyedRaven");
    g_signal_connect(buttonThreeEyedRaven, "clicked", G_CALLBACK(ThreeEyedRaven), NULL);
    gtk_widget_set_hexpand(buttonThreeEyedRaven,FALSE);
    gtk_widget_set_vexpand(buttonThreeEyedRaven,FALSE);


    //Init of buttonNotSoNotSecure
    GtkWidget *buttonNotSoNotSecure = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent),buttonNotSoNotSecure, 1, 2, 1, 1);
    gtk_widget_set_size_request(buttonNotSoNotSecure, 84, 84);
    gtk_widget_add_css_class(buttonNotSoNotSecure, "DesktopIcon");
    gtk_widget_add_css_class(buttonNotSoNotSecure, "IconNotSoNotSecure");
    g_signal_connect(buttonNotSoNotSecure, "clicked", G_CALLBACK(NotSoNotSecure), NULL);
    gtk_widget_set_hexpand(buttonNotSoNotSecure,FALSE);
    gtk_widget_set_vexpand(buttonNotSoNotSecure,FALSE);

    //Init of buttonNotSoNotFallty
    mainWidget.buttonNotSoNotFallty = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent), mainWidget.buttonNotSoNotFallty, 0, 3, 1, 1);
    gtk_widget_set_size_request(mainWidget.buttonNotSoNotFallty, 84, 84);
    gtk_widget_add_css_class(mainWidget.buttonNotSoNotFallty, "DesktopIcon");
    gtk_widget_add_css_class(mainWidget.buttonNotSoNotFallty, "IconNotSoNotFallty");
    g_signal_connect(mainWidget.buttonNotSoNotFallty, "clicked", G_CALLBACK(NotSoNotFallty), NULL);
    gtk_widget_set_hexpand(mainWidget.buttonNotSoNotFallty,FALSE);
    gtk_widget_set_vexpand(mainWidget.buttonNotSoNotFallty,FALSE);

    //Init of buttonJustaGuiFramework
    mainWidget.buttonJustaGuiFramework = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent), mainWidget.buttonJustaGuiFramework, 1, 3, 1, 1);
    gtk_widget_set_size_request(mainWidget.buttonJustaGuiFramework, 84, 84);
    gtk_widget_add_css_class(mainWidget.buttonJustaGuiFramework, "DesktopIcon");
    gtk_widget_add_css_class(mainWidget.buttonJustaGuiFramework, "IconJustaGuiFramework");
    g_signal_connect(mainWidget.buttonJustaGuiFramework, "clicked", G_CALLBACK(JustaGuiFramework), NULL);
    gtk_widget_set_hexpand(mainWidget.buttonJustaGuiFramework,FALSE);
    gtk_widget_set_vexpand(mainWidget.buttonJustaGuiFramework,FALSE);

    //Init of buttonNotSoSpacy
    mainWidget.buttonNotSoSpacy = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent), mainWidget.buttonNotSoSpacy, 0, 4, 1, 1);
    gtk_widget_set_size_request(mainWidget.buttonNotSoSpacy, 84, 84);
    gtk_widget_add_css_class(mainWidget.buttonNotSoSpacy, "DesktopIcon");
    gtk_widget_add_css_class(mainWidget.buttonNotSoSpacy, "IconNotSoSpacy");
    g_signal_connect(mainWidget.buttonNotSoSpacy, "clicked", G_CALLBACK(NotSoSpacy), NULL);
    gtk_widget_set_hexpand(mainWidget.buttonNotSoSpacy,FALSE);
    gtk_widget_set_vexpand(mainWidget.buttonNotSoSpacy,FALSE);

    //Init of buttonNotSoNotSpooky
    mainWidget.buttonNotSoNotSpooky = gtk_button_new();
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent), mainWidget.buttonNotSoNotSpooky, 1, 4, 1, 1);
    gtk_widget_set_size_request(mainWidget.buttonNotSoNotSpooky, 84, 84);
    gtk_widget_add_css_class(mainWidget.buttonNotSoNotSpooky, "DesktopIcon");
    gtk_widget_add_css_class(mainWidget.buttonNotSoNotSpooky, "IconNotSoNotSpooky");
    g_signal_connect(mainWidget.buttonNotSoNotSpooky, "clicked", G_CALLBACK(NotSoNotSpooky), NULL);
    gtk_widget_set_hexpand(mainWidget.buttonNotSoNotSpooky,FALSE);
    gtk_widget_set_vexpand(mainWidget.buttonNotSoNotSpooky,FALSE);



    //Init of frameDock
    GtkWidget *frameDock = gtk_frame_new(NULL);
    gtk_grid_attach(GTK_GRID(mainWidget.gridParent),frameDock,10,30,10,1);
    gtk_widget_set_size_request(frameDock,74*6,74);
    gtk_widget_add_css_class(frameDock,"Dock");
    gtk_widget_set_halign(frameDock,GTK_ALIGN_END);
    gtk_widget_set_valign(frameDock,GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(frameDock,405-84);
    gtk_widget_set_margin_start(frameDock,175);






}
//This is a continious Poling function that fetches the current time every 15 seconds
gboolean updateTopBarTime(gpointer user_data) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char temp[50];
    strftime(temp, sizeof(temp), "%b %-d %l:%M %p", timeinfo);
    gtk_label_set_text(GTK_LABEL(mainWidget.labelTime),temp);

    return TRUE;
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
