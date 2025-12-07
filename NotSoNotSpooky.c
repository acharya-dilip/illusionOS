//
// Created by g4sker on 12/7/25.
//

#include "NotSoNotSpooky.h"

#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

#include "main.h"

struct values {
    long long a, b;
    double result, answer;
    int operandType;
    char operand[5];
} val;

void numButPress(GtkButton *button, gpointer user_data);

void operandPress(GtkButton *button, gpointer operand);

void performCalculation();

void pressAns();

//Jumpscares and quirks
void checkSixSeven(int x);

void sixSeven();

int sixSevenCondition;

void checkSixtyNine(int x);

void sixtyNine();

int sixtyNineCondition;

void performSpooky();

int spookyThreshold, spookyStatus;

void randomSpook();

void godsEnlightenment();

void clearEntry();

//Globalised Variables
GtkWidget *entryCal;

void NotSoNotSpooky() {
    //Init of windowSpooky
    GtkWidget *windowSpooky = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowSpooky), "Calculator");
    gtk_window_present(GTK_WINDOW(windowSpooky));
    gtk_window_set_transient_for(GTK_WINDOW(windowSpooky), windowMainDesktop);

    //init of gridParent
    GtkWidget *gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowSpooky), gridParent);
    //MArgins & Paddings
    gtk_widget_set_halign(GTK_WIDGET(gridParent), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(gridParent), GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(GTK_WIDGET(gridParent), 10);
    gtk_widget_set_margin_end(GTK_WIDGET(gridParent), 10);

    //init of entryCal
    entryCal = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent), entryCal, 0, 0, 4, 1);
    gtk_editable_set_editable(GTK_EDITABLE(entryCal),FALSE);

    //init of buttonClear
    GtkWidget *buttonClear = gtk_button_new_with_label("C");
    gtk_grid_attach(GTK_GRID(gridParent), buttonClear, 0, 1, 3, 1);
    g_signal_connect(buttonClear, "clicked", G_CALLBACK(clearEntry), NULL);
    gtk_widget_add_css_class(buttonClear, "spookyButtonClear");

    //init of numbut7
    GtkWidget *numbut7 = gtk_button_new_with_label("7");
    gtk_grid_attach(GTK_GRID(gridParent), numbut7, 0, 2, 1, 1);
    g_signal_connect(numbut7, "clicked", G_CALLBACK(numButPress), GINT_TO_POINTER(7));
    gtk_widget_add_css_class(numbut7, "spookyButton7");

    //init of numbut8
    GtkWidget *numbut8 = gtk_button_new_with_label("8");
    gtk_grid_attach(GTK_GRID(gridParent), numbut8, 1, 2, 1, 1);
    g_signal_connect(numbut8, "clicked", G_CALLBACK(numButPress), GINT_TO_POINTER(8));
    gtk_widget_add_css_class(numbut8, "spookyButton8");

    //init of numbut9
    GtkWidget *numbut9 = gtk_button_new_with_label("9");
    gtk_grid_attach(GTK_GRID(gridParent), numbut9, 2, 2, 1, 1);
    g_signal_connect(numbut9, "clicked", G_CALLBACK(numButPress), GINT_TO_POINTER(9));
    gtk_widget_add_css_class(numbut9, "spookyButton9");

    //init of numbut4
    GtkWidget *numbut4 = gtk_button_new_with_label("4");
    gtk_grid_attach(GTK_GRID(gridParent), numbut4, 0, 3, 1, 1);
    g_signal_connect(numbut4, "clicked", G_CALLBACK(numButPress), GINT_TO_POINTER(4));
    gtk_widget_add_css_class(numbut4, "spookyButton4");

    //init of numbut5
    GtkWidget *numbut5 = gtk_button_new_with_label("5");
    gtk_grid_attach(GTK_GRID(gridParent), numbut5, 1, 3, 1, 1);
    g_signal_connect(numbut5, "clicked", G_CALLBACK(numButPress), GINT_TO_POINTER(5));
    gtk_widget_add_css_class(numbut5, "spookyButton5");

    //init of numbut6
    GtkWidget *numbut6 = gtk_button_new_with_label("6");
    gtk_grid_attach(GTK_GRID(gridParent), numbut6, 2, 3, 1, 1);
    g_signal_connect(numbut6, "clicked", G_CALLBACK(numButPress), GINT_TO_POINTER(6));
    gtk_widget_add_css_class(numbut6, "spookyButton6");

    //init of numbut1
    GtkWidget *numbut1 = gtk_button_new_with_label("1");
    gtk_grid_attach(GTK_GRID(gridParent), numbut1, 0, 4, 1, 1);
    g_signal_connect(numbut1, "clicked", G_CALLBACK(numButPress), GINT_TO_POINTER(1));
    gtk_widget_add_css_class(numbut1, "spookyButton1");

    //init of numbut2
    GtkWidget *numbut2 = gtk_button_new_with_label("2");
    gtk_grid_attach(GTK_GRID(gridParent), numbut2, 1, 4, 1, 1);
    g_signal_connect(numbut2, "clicked", G_CALLBACK(numButPress), GINT_TO_POINTER(2));
    gtk_widget_add_css_class(numbut2, "spookyButton2");

    //init of numbut3
    GtkWidget *numbut3 = gtk_button_new_with_label("3");
    gtk_grid_attach(GTK_GRID(gridParent), numbut3, 2, 4, 1, 1);
    g_signal_connect(numbut3, "clicked", G_CALLBACK(numButPress), GINT_TO_POINTER(3));
    gtk_widget_add_css_class(numbut3, "spookyButton3");

    //init of buttonPoint
    GtkWidget *buttonPoint = gtk_button_new_with_label(".");
    gtk_grid_attach(GTK_GRID(gridParent), buttonPoint, 0, 5, 1, 1);
    g_signal_connect(buttonPoint, "clicked", G_CALLBACK(performSpooky), NULL);
    gtk_widget_add_css_class(buttonPoint, "spookyButtonSkull");

    //init of numbut0
    GtkWidget *numbut0 = gtk_button_new_with_label("0");
    gtk_grid_attach(GTK_GRID(gridParent), numbut0, 1, 5, 1, 1);
    g_signal_connect(numbut0, "clicked", G_CALLBACK(numButPress), GINT_TO_POINTER(0));
    gtk_widget_add_css_class(numbut0, "spookyButton0");

    //init of buttonPercent
    GtkWidget *buttonAns = gtk_button_new_with_label("A");
    gtk_grid_attach(GTK_GRID(gridParent), buttonAns, 2, 5, 1, 1);
    g_signal_connect(buttonAns, "clicked", G_CALLBACK(pressAns), NULL);
    gtk_widget_add_css_class(buttonAns, "spookyButtonAns");


    //For the operand buttons

    //init of buttonDiv
    GtkWidget *buttonDiv = gtk_button_new_with_label("/");
    gtk_grid_attach(GTK_GRID(gridParent), buttonDiv, 3, 1, 1, 1);
    g_signal_connect(buttonDiv, "clicked", G_CALLBACK(operandPress), "/");
    gtk_widget_add_css_class(buttonDiv, "spookyButtonDiv");

    //init of buttonProd
    GtkWidget *buttonProd = gtk_button_new_with_label("×");
    gtk_grid_attach(GTK_GRID(gridParent), buttonProd, 3, 2, 1, 1);
    g_signal_connect(buttonProd, "clicked", G_CALLBACK(operandPress), "×");
    gtk_widget_add_css_class(buttonProd, "spookyButtonProd");

    //init of buttonSub
    GtkWidget *buttonSub = gtk_button_new_with_label("-");
    gtk_grid_attach(GTK_GRID(gridParent), buttonSub, 3, 3, 1, 1);
    g_signal_connect(buttonSub, "clicked", G_CALLBACK(operandPress), "-");
    gtk_widget_add_css_class(buttonSub, "spookyButtonSub");

    //init of buttonSum
    GtkWidget *buttonSum = gtk_button_new_with_label("+");
    gtk_grid_attach(GTK_GRID(gridParent), buttonSum, 3, 4, 1, 1);
    g_signal_connect(buttonSum, "clicked", G_CALLBACK(operandPress), "+");
    gtk_widget_add_css_class(buttonSum, "spookyButtonSum");


    //For the result button

    //init of buttonResult
    GtkWidget *buttonResult = gtk_button_new_with_label("=");
    gtk_grid_attach(GTK_GRID(gridParent), buttonResult, 3, 5, 1, 1);
    g_signal_connect(buttonResult, "clicked", G_CALLBACK(performCalculation), NULL);
    gtk_widget_add_css_class(buttonResult, "spookyButtonRes");
}

//Function that handles the button press for number buttons
void numButPress(GtkButton *button, gpointer user_data) {
    //Increases the spookyThreshold for every number button press
    spookyThreshold += 5;
    //Converts the passed pointer into an integer for usage
    int n = GPOINTER_TO_INT(user_data);
    //checks if 6 and 7 are consectively placed and triggers sixSeven spook if they are
    checkSixSeven(n);
    //checks if 6 and 9 are consecutively placed and triggers sixtyNine spook if they are
    checkSixtyNine(n);
    //Decides weather to set the value as a or based on if operand is present
    if (strcmp(val.operand, "") == 0) {
        //sets the value of digits typed as value of a if operand is absent
        val.a = val.a * 10 + n;
        char temp[50];
        snprintf(temp, sizeof(temp), "%lld", val.a);
        gtk_editable_set_text(GTK_EDITABLE(entryCal), temp);
    } else {
        //Sets the value of digits typed if operand is absent
        val.b = val.b * 10 + n;
        char temp[50];
        snprintf(temp, sizeof(temp), "%s%lld", val.operand, val.b);
        gtk_editable_set_text(GTK_EDITABLE(entryCal), temp);
    }
    //Checks if the program is already in spooky mode
    if (spookyStatus == 0) {
        //if not checks if spookyThreshold is reached 100
        if (spookyThreshold >= 100) {
            //if spooky threshold reached 100 executes function performSpooky
            performSpooky();
        }
    } else {
        system("gst-play-1.0 ./src/sounds/soundWoosh.mp3 >/dev/null 2>&1 &");
    }
    if (spookyThreshold >= 40) {
        randomSpook();
    }
}

void checkSixSeven(int x) {
    if (x == 7) {
        if (sixSevenCondition == 1) {
            sixSeven();
            spookyThreshold += 20;
        }
    }
    if (x == 6) {
        sixSevenCondition = 1;
    } else {
        sixSevenCondition = 0;
    }
}

void sixSeven() {
    system("gst-play-1.0 ./src/sounds/67.mp3 >/dev/null 2>&1 &");
}

void checkSixtyNine(int x) {
    if (x == 9) {
        if (sixtyNineCondition == 1) {
            sixtyNine();
            spookyThreshold -= 15;
        }
    }
    if (x == 6) {
        sixtyNineCondition = 1;
    } else {
        sixtyNineCondition = 0;
    }
}

void sixtyNine() {
    system("gst-play-1.0 ./src/sounds/69.mp3 >/dev/null 2>&1 &");
}

void operandPress(GtkButton *button, gpointer operand) {
    strcpy(val.operand, operand);
    gtk_editable_set_text(GTK_EDITABLE(entryCal), operand);
    //sets the operandType variable
    if (strcmp(operand, "/") == 0) {
        val.operandType = 1;
    }
    if (strcmp(operand, "×") == 0) {
        val.operandType = 2;
    }
    if (strcmp(operand, "-") == 0) {
        val.operandType = 3;
    }
    if (strcmp(operand, "+") == 0) {
        val.operandType = 4;
    }
    if (spookyThreshold >= 50) {
        randomSpook();
    }
}

void pressAns() {
    if (strcmp(val.operand, "") == 0) {
        val.a = val.answer;
        gtk_editable_set_text(GTK_EDITABLE(entryCal), "Ans");
    } else {
        val.b = val.answer;
        char temp[50];
        snprintf(temp, sizeof(temp), "%sAns", val.operand);
        gtk_editable_set_text(GTK_EDITABLE(entryCal), temp);
    }
    if (spookyThreshold >= 40) {
        randomSpook();
    }
}

void performCalculation() {
    // operandType meaning
    // 1 = div
    // 2 = product
    // 3 = subtract
    // 4 = sum
    int result; //This vaaariable is used to store 0 or 1 from the below switch
    //0 indicates successful
    //1 indicates failure
    switch (val.operandType) {
        case 1:
            val.result = val.a / val.b;
            result = 0;
            break;
        case 2:
            val.result = val.a * val.b;
            result = 0;
            break;
        case 3:
            val.result = val.a - val.b;
            result = 0;
            break;
        case 4:
            val.result = val.a + val.b;
            result = 0;
            break;
        default:
            result = 1;
    }

    if (result == 0) {
        //If Result is obtained properly than displays it
        char temp[50];
        snprintf(temp, sizeof(temp), "%3.lf", val.result);
        val.answer = val.result;
        gtk_editable_set_text(GTK_EDITABLE(entryCal), temp);
    } else {
        //if result isn't obtained properly displays error
        gtk_editable_set_text(GTK_EDITABLE(entryCal), "Error!");
        //PLays the womanScreaming sound effect
        system("gst-play-1.0 ./src/sounds/womanScream.mp3 >/dev/null 2>&1 &");
        //Increases the spookThreshold
        spookyThreshold += 20;
    }
    //This if statement check if the god value has be conjoured
    if (val.a == 6940 && val.operandType == 4 && val.b == 67 || val.result == 69487 || val.result == 69420) {
        godsEnlightenment();
    }
    //Stores the recent answer in variable
    val.answer = val.result;
    //Sets the recent answer as the value for the for value unless overridden
    val.a = val.result;
    //Resets the other values after calculation
    val.b = 0;
    val.result = 0;
    val.operandType = 0;
    strcpy(val.operand, "");
    //Triggers the randomSpook function if spookThreshold is reached
    if (spookyThreshold >= 40) {
        randomSpook();
    }
}

//Clears the entry when the clear button is pressed
void clearEntry() {
    gtk_editable_set_text(GTK_EDITABLE(entryCal), "");
    val.a = 0;
    val.b = 0;
    val.result = 0;
    strcpy(val.operand, "");
    //triggers randomspook if threshold value reached 50
    if (spookyThreshold >= 40) {
        randomSpook();
    }
}

//Gobalized Variables
GtkCssProvider *provider = NULL;

void performSpooky() {
    spookyStatus = 1;
    system("gst-play-1.0 ./src/sounds/scream.mp3 >/dev/null 2>&1 &");
    sleep(2);
    //COnnects the spookyStyles.css stylesheet
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "spookyStyles.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );;
    system("while true; do gst-play-1.0 ./src/sounds/bells.mp3 >/dev/null 2>&1; done &");
    if (spookyThreshold >= 40) {
        randomSpook();
    }
}

void randomSpook() {
    int random = (rand() % 10) + 1;
    int spookRes;
    switch (random) {
        case 1:
            system("gst-play-1.0 ./src/sounds/creepy.mp3 >/dev/null 2>&1 &");
            spookRes = 0;
            break;
        case 2:
            system("gst-play-1.0 ./src/src/sounds/scream.mp3 >/dev/null 2>&1 &");
            spookRes = 0;
            break;
        case 3:
            system("gst-play-1.0 ./src/sounds/womanScream.mp3 >/dev/null 2>&1 &");
            spookRes = 0;
            break;
        case 4:
            system("gst-play-1.0 ./src/sounds/witchLaugh.mp3 >/dev/null 2>&1 &");
            spookRes = 0;
        default:
            printf("No Spooks");
            spookRes = 1;
    }
    if (spookRes == 0) {
        spookyThreshold += 20;
    }
}

void godsEnlightenment() {
    //Gives some buffer time before the person gets spooked again
    spookyThreshold = -500;
    //kills the gstreamer processes to stop the spooky sounds
    system("pkill -f 'while true; do gst-play-1.0 ./src/sounds/bells.mp3'");
    system(" pkill gst-play-1.0");
    //Now aaaaaaaaaaaaaaall we gotta figure out is how to stop the css
    GdkDisplay *display = gdk_display_get_default();
    gtk_style_context_remove_provider_for_display(
        display,
        GTK_STYLE_PROVIDER(provider)
    );
    g_object_unref(provider);
    spookyStatus = 0;
}
