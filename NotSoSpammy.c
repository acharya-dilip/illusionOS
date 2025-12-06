//
// Created by g4sker on 12/6/25.
//

#include "NotSoSpammy.h"
#include <stdio.h>
#include <gtk/gtk.h>


struct loginWidgets {
    GtkWidget *windowLoginScreen;
    GtkWidget *gridParentLogin;
    GtkWidget *labelGmail;
    GtkWidget *labelPassword;
    GtkWidget *entryGmail;
    GtkWidget *entryPassword;
    GtkWidget *buttonLogin;

}login;
void NotSoSpammy() {
     struct moveableFrame {
    GtkWidget *overlay;        // Container that holds the frame
    GtkWidget *box;            // Main container
    GtkWidget *titleBar;       // Top bar with title and close button
    GtkWidget *titleLabel;     // Title text
    GtkWidget *closeButton;    // Close button
    GtkWidget *contentArea;    // Area for your content

    // For dragging
    double drag_start_x;
    double drag_start_y;
    GtkGesture *drag_gesture;
};

    //Implementation of gridParentLogin
    login.gridParentLogin = gtk_grid_new();

    gtk_window_set_child(GTK_WINDOW(login.windowLoginScreen),login.gridParentLogin);

    //Margins & Padding
        gtk_widget_set_size_request(login.gridParentLogin, 350, 100);

    //Implementation of Mail entering field
    //LABEL FOR GMAIL
    login.labelGmail = gtk_label_new("User ID: ");
    gtk_grid_attach(GTK_GRID(login.gridParentLogin),login.labelGmail, 0, 0, 1, 1);
    //Margins & Padding
        gtk_widget_set_halign(login.labelGmail,GTK_ALIGN_END);
        gtk_widget_set_margin_start(login.labelGmail,10);

    //ENTRY FOR GMAIL
    login.entryGmail = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(login.gridParentLogin),login.entryGmail, 4, 0, 1, 1);
    //Margins & Padding
        gtk_widget_set_hexpand(login.entryGmail, TRUE);
        gtk_widget_set_margin_start(login.entryGmail,5);
        gtk_widget_set_margin_end(login.entryGmail,15);
        gtk_widget_set_size_request(login.entryGmail, 100, -1);

    //Implementation of Password entry
    login.labelPassword = gtk_label_new("Password: ");
    gtk_grid_attach(GTK_GRID(login.gridParentLogin),login.labelPassword, 0, 1, 1, 1);
    //Margins & Padding
        gtk_widget_set_halign(login.labelPassword,GTK_ALIGN_END);
        gtk_widget_set_margin_start(login.labelPassword,10);
    login.entryPassword = gtk_entry_new();
    //MAKING IT SO THAT WHEN YOU TYPE PASSWORD IT WON't BE VISIBLE
    gtk_entry_set_visibility(GTK_ENTRY(login.entryPassword),FALSE);
    gtk_grid_attach(GTK_GRID(login.gridParentLogin),login.entryPassword, 4, 1, 6, 1);
    //Margins & PAdding
        gtk_widget_set_margin_start(login.entryPassword,5);
        gtk_widget_set_margin_end(login.entryPassword,15);

    //Implementation of buttonLogin
    login.buttonLogin = gtk_button_new_with_label("Login");
    gtk_grid_attach(GTK_GRID(login.gridParentLogin),login.buttonLogin, 2, 2, 6, 1);
    // g_signal_connect(login.buttonLogin, "clicked",G_CALLBACK(checkLogin),NULL);

    //Margins & Padding

    gtk_widget_set_margin_end(login.buttonLogin,15);
}
