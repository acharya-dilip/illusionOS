//
// Created by g4sker on 12/7/25.
//

#include "ThreeEyedRaven.h"

#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

void TERcheckLogin();
void mainWindow();
void deployRaven();
void closeProgram();
//Weather FEtching functions
void fetchWeather();
void fetchWeatherDescrip();
void fetchTempr();
void fetchfeelTempr();
void fetchpercenthumidity();
void fetchmmppt();
void fetchwind();
void fetchSunrise();
void fetchSunset();
//Updates the text view with weather info
void updateWeatherInfo();
void formatMail();
void sendReportMail();
void fetchLocation();
//Recursive writedata function for CURLOPT_WRITEFUNCTION
size_t writedata(void *ptr, size_t size, size_t nmemb, void *userdata);

//Global Weather Fetching Variables
char tempr[512];
char feelTempr[512];
char weatherDescrip[512];
char percenthumidity[512];
char mmppt[512];
char wind[512];
char sunrise[512];
char sunset[512];

struct widgetTER {
    //Globalised Login Variables
    GtkWidget *windowLogin;
    GtkWidget *entryGmail;
    GtkWidget *entryPassword;
    GtkWidget *entryRecipientMail;

}widgetTER;

void ThreeEyedRaven() {
    GtkWidget *gridParentLogin;
    GtkWidget *labelGmail;
    GtkWidget *labelPassword;
    GtkWidget *buttonLogin;

    //Implementation of login window
    widgetTER.windowLogin = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(widgetTER.windowLogin),"Login");
    gtk_window_present(GTK_WINDOW(widgetTER.windowLogin));

    //Implementation of gridParent
    gridParentLogin = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(widgetTER.windowLogin),gridParentLogin);
    //Margins & Paddings
        gtk_widget_set_halign(gridParentLogin,GTK_ALIGN_CENTER);
        gtk_widget_set_margin_top(gridParentLogin,10);
        gtk_widget_set_margin_bottom(gridParentLogin,10);
        gtk_widget_set_margin_start(gridParentLogin,10);
        gtk_widget_set_margin_end(gridParentLogin,10);

    //Implementation of labelGmail
    labelGmail= gtk_label_new("Gmail: ");
    gtk_grid_attach(GTK_GRID(gridParentLogin),labelGmail,0,0,1,1);

    //Implementation of labelPassword
    labelPassword= gtk_label_new("Pass: ");
    gtk_grid_attach(GTK_GRID(gridParentLogin),labelPassword,0,1,1,1);

    //Margins & Paddings
        gtk_widget_set_halign(labelGmail,GTK_ALIGN_END);
        gtk_widget_set_halign(labelPassword,GTK_ALIGN_END);
        gtk_widget_set_margin_end(labelGmail,10);
        gtk_widget_set_margin_bottom(labelGmail,10);
        gtk_widget_set_margin_end(labelPassword,10);
        gtk_widget_set_margin_bottom(labelPassword,10);

    //Implementation of entryGmail
    widgetTER.entryGmail = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParentLogin),widgetTER.entryGmail,1,0,4,1);

    //IMplementation of entryPassword
    widgetTER.entryPassword = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParentLogin),widgetTER.entryPassword,1,1,4,1);
    gtk_entry_set_visibility(GTK_ENTRY(widgetTER.entryPassword),FALSE);

    //Margins & Paddings
        gtk_widget_set_size_request(widgetTER.entryGmail,200,-1);
        gtk_widget_set_size_request(widgetTER.entryPassword,200,-1);

    //Implementation of Button Login
    buttonLogin = gtk_button_new_with_label("Login");
    gtk_grid_attach(GTK_GRID(gridParentLogin),buttonLogin,1,2,4,1);
    g_signal_connect(buttonLogin,"clicked",G_CALLBACK(TERcheckLogin),NULL);

}

void TERcheckLogin() {
    CURL *curl = curl_easy_init();
    CURLcode result;
    if (curl) {
        //conectin to the gmail smtp server
        curl_easy_setopt(curl,CURLOPT_URL,"smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl,CURLOPT_USE_SSL,(long)CURLUSESSL_ALL);

        curl_easy_setopt(curl,CURLOPT_USERNAME,gtk_editable_get_text(GTK_EDITABLE(widgetTER.entryGmail)));
        curl_easy_setopt(curl,CURLOPT_PASSWORD,gtk_editable_get_text(GTK_EDITABLE(widgetTER.entryPassword)));

        //To ignore other steps only do the handshake
        curl_easy_setopt(curl,CURLOPT_NOBODY,1L);
        curl_easy_setopt(curl,CURLOPT_HEADER,0L);
        curl_easy_setopt(curl,CURLOPT_UPLOAD,0L);
        curl_easy_setopt(curl,CURLOPT_READFUNCTION,NULL);

        result = curl_easy_perform(curl);
        if (result == CURLE_OK) {
            gtk_widget_set_visible(widgetTER.windowLogin, FALSE);
            mainWindow();
        }

        curl_easy_cleanup(curl);

    }

}
//Globalised Variables
GtkWidget *entryLocation;
GtkWidget *textviewWeatherInfo;
GtkTextBuffer *bufferWeatherInfo;
void mainWindow() {
    GtkWidget *windowMain;
    GtkWidget *gridParent;
    GtkWidget *buttonFetchLocation;
    GtkWidget *buttonFetchWeather;
    GtkWidget *buttonDeployRaven;


    windowMain = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowMain),"Raven's Weather Report");
    gtk_window_set_default_size(GTK_WINDOW(windowMain),400,400);
    gtk_window_present(GTK_WINDOW(windowMain));
    g_signal_connect(windowMain,"destroy",G_CALLBACK(closeProgram),NULL);

    //Implementation of gridParent
    gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowMain),gridParent);
    gtk_widget_set_halign(gridParent, GTK_ALIGN_CENTER);
    //Margins & Paddigns
        gtk_widget_set_margin_start(gridParent,15);
        gtk_widget_set_margin_end(gridParent,15);
        gtk_widget_set_margin_top(gridParent,15);
        gtk_widget_set_margin_bottom(gridParent,15);

    //Implementaton of entryLocation
    entryLocation = gtk_entry_new();
    gtk_widget_grab_focus(entryLocation);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryLocation),"Enter Your Location");
    gtk_grid_attach(GTK_GRID(gridParent),entryLocation,0,0,4,1);
    //Margins & Paddings
        gtk_widget_set_size_request(entryLocation,355,-1);

    //Implementation of buttonFetchLocation
    buttonFetchLocation = gtk_button_new_with_label("📌");
    gtk_grid_attach(GTK_GRID(gridParent),buttonFetchLocation,4,0,1,1);
    g_signal_connect(buttonFetchLocation,"clicked",G_CALLBACK(fetchLocation),NULL);
    //Margins & Paddings
        gtk_widget_set_margin_start(buttonFetchLocation,10);

    //Implementation of textviewWeatherInfo
    textviewWeatherInfo = gtk_text_view_new();
    gtk_grid_attach(GTK_GRID(gridParent),textviewWeatherInfo,0,1,5,5);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textviewWeatherInfo),TRUE);
    //Margins & Paddings
        gtk_widget_set_size_request(textviewWeatherInfo,370,370);
        gtk_widget_set_margin_bottom(textviewWeatherInfo, 10);
        gtk_widget_set_margin_top(textviewWeatherInfo, 10);

    //Implementation of buttonFetchWeather
    buttonFetchWeather = gtk_button_new_with_label("Rouse the Raven");
    gtk_grid_attach(GTK_GRID(gridParent),buttonFetchWeather,0,6,4,1);
    g_signal_connect(buttonFetchWeather,"clicked",G_CALLBACK(fetchWeather),NULL);

    //Implementation of buttonDeployRaven
    buttonDeployRaven = gtk_button_new_with_label("🦉");
    gtk_grid_attach(GTK_GRID(gridParent),buttonDeployRaven,4,6,1,1);
    g_signal_connect(buttonDeployRaven,"clicked",G_CALLBACK(deployRaven),NULL);
    //Margins & Paddings
        gtk_widget_set_margin_start(buttonDeployRaven,10);


}


void fetchLocation() {
    CURL *curl = curl_easy_init();
    char temp[512];
    if (curl) {
        curl_easy_setopt(curl,CURLOPT_URL,"https://ipapi.co/city/");
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writedata);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,temp);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    gtk_editable_set_text(GTK_EDITABLE(entryLocation),temp);
}


//Globalised Variables
    GtkWidget *windowRaven;
    GtkWidget *lockedEntrySubject;
    GtkWidget *textviewBody;

void deployRaven() {
    GtkWidget *gridParentRaven;
    GtkWidget *lockedEntryUserId;
    GtkWidget *buttonSendRaven;

    //Implementation of WindowRaven
    windowRaven = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowRaven),"Deploy the Raven");
    gtk_window_set_default_size(GTK_WINDOW(windowRaven),400,400);
    gtk_window_present(GTK_WINDOW(windowRaven));

    //Implementation of gridParentRaven
    gridParentRaven = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowRaven),gridParentRaven);
    //MArgins & Paddings
    gtk_widget_set_margin_start(gridParentRaven,10);
    gtk_widget_set_margin_end(gridParentRaven,10);
    gtk_widget_set_margin_top(gridParentRaven,10);
    gtk_widget_set_margin_bottom(gridParentRaven,10);
    gtk_widget_set_halign(gridParentRaven,GTK_ALIGN_CENTER);

    //Implementation of lockedEntryUserId;
    lockedEntryUserId = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParentRaven),lockedEntryUserId,0,0,5,1);
    char userID[128];
    snprintf(userID,sizeof(userID),"User ID: %s",gtk_editable_get_text(GTK_EDITABLE(widgetTER.entryGmail)));
    gtk_editable_set_text(GTK_EDITABLE(lockedEntryUserId),userID);
    gtk_editable_set_editable(GTK_EDITABLE(lockedEntryUserId),FALSE);
    //MArgins & Paddings
    gtk_widget_set_margin_bottom(lockedEntryUserId,10);
    gtk_widget_set_size_request(lockedEntryUserId,370,-1);

    //Implementation of entryRecipientMail
    widgetTER.entryRecipientMail = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgetTER.entryRecipientMail),"Enter Recipient Mail");
    gtk_grid_attach(GTK_GRID(gridParentRaven),widgetTER.entryRecipientMail,0,1,5,1);
    //Margins & Paddings
    gtk_widget_set_margin_bottom(widgetTER.entryRecipientMail,10);

    //Implementation of entrySubject
    lockedEntrySubject = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(lockedEntrySubject),"Raven's Weather Report");
    gtk_grid_attach(GTK_GRID(gridParentRaven),lockedEntrySubject,0,2,5,1);
    //Margins & Paddings
    gtk_widget_set_margin_bottom(lockedEntrySubject,10);

    //Implementation of textviewBody
    textviewBody = gtk_text_view_new_with_buffer(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textviewWeatherInfo)));
    gtk_grid_attach(GTK_GRID(gridParentRaven),textviewBody,0,3,5,5);
    //Margins & Paddings
    gtk_widget_set_margin_bottom(textviewBody,10);
    gtk_widget_set_size_request(textviewBody,370,340);

    //Implementation of buttonSendRaven
    buttonSendRaven = gtk_button_new_with_label("Deploy Raven");
    gtk_grid_attach(GTK_GRID(gridParentRaven),buttonSendRaven,0,8,5,1);
    g_signal_connect(buttonSendRaven,"clicked",G_CALLBACK(sendReportMail),NULL);




}

void formatMail() {
    //extracting the buffer text onto a temp variable
    GtkTextBuffer *buffertemp = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textviewBody));
    GtkTextIter start, end;
    gchar *temp;
    gtk_text_buffer_get_start_iter(buffertemp,&start);
    gtk_text_buffer_get_end_iter(buffertemp,&end);
    temp=gtk_text_buffer_get_text(buffertemp,&start,&end,FALSE);

FILE *file = fopen("mail.txt","w");
    if (file) {
        fprintf(file,
                "To: %s \r\n"
                "From: %s \r\n"
                "Subject: %s \r\n"
                "\r\n"
                "%s\r\n",
                gtk_editable_get_text(GTK_EDITABLE(widgetTER.entryRecipientMail)),
                gtk_editable_get_text(GTK_EDITABLE(widgetTER.entryGmail)),
                gtk_editable_get_text(GTK_EDITABLE(lockedEntrySubject)),
                temp);

        fclose(file);
    }

}

void sendReportMail() {
    CURL *curl = curl_easy_init();
    CURLcode res;
    if (curl) {
        //connectin to the smtp google server
        curl_easy_setopt(curl,CURLOPT_URL,"smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl,CURLOPT_USE_SSL,(long)CURLUSESSL_ALL);
        //fetching the user credentials
        curl_easy_setopt(curl,CURLOPT_USERNAME,gtk_editable_get_text(GTK_EDITABLE(widgetTER.entryGmail)));
        curl_easy_setopt(curl,CURLOPT_PASSWORD,gtk_editable_get_text(GTK_EDITABLE(widgetTER.entryPassword)));
        curl_easy_setopt(curl,CURLOPT_MAIL_FROM,gtk_editable_get_text(GTK_EDITABLE(widgetTER.entryGmail)));
        //Recipients stuff
        struct curl_slist *recipients=NULL;
        recipients = curl_slist_append(recipients,gtk_editable_get_text(GTK_EDITABLE(widgetTER.entryRecipientMail)));
        curl_easy_setopt(curl,CURLOPT_MAIL_RCPT,recipients);
        //THe real mail sending part
        formatMail();
        FILE *payload = fopen("mail.txt","r");
        curl_easy_setopt(curl,CURLOPT_READDATA,payload);
        curl_easy_setopt(curl,CURLOPT_UPLOAD,1L);



        res=curl_easy_perform(curl);
        fclose(payload);
        remove ("mail.txt");


        if (res == CURLE_OK) {
            gtk_window_destroy(GTK_WINDOW(windowRaven));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);


    }


}


void fetchWeather(){
    fetchWeatherDescrip();
    fetchTempr();
    fetchfeelTempr();
    fetchpercenthumidity();
    fetchmmppt();
    fetchwind();
    fetchSunrise();
    fetchSunset();
    updateWeatherInfo();
}

void fetchWeatherDescrip(){
    CURL *curl = curl_easy_init();
    char temp[512];
    if (curl) {
        char tempurl[512];
        snprintf(tempurl,sizeof(tempurl),"https://wttr.in/%s?format=%%C",gtk_editable_get_text(GTK_EDITABLE(entryLocation)));
        curl_easy_setopt(curl,CURLOPT_URL,tempurl);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writedata);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,temp);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    strcpy(weatherDescrip,temp);
}



void fetchTempr(){
    CURL *curl = curl_easy_init();
    char temp[512];
    if (curl) {
        char tempurl[512];
        snprintf(tempurl,sizeof(tempurl),"https://wttr.in/%s?format=%%t",gtk_editable_get_text(GTK_EDITABLE(entryLocation)));
        curl_easy_setopt(curl,CURLOPT_URL,tempurl);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writedata);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,temp);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    strcpy(tempr,temp);

}

void fetchfeelTempr(){
    CURL *curl = curl_easy_init();
    char temp[512];
    if (curl) {
        char tempurl[512];
        snprintf(tempurl,sizeof(tempurl),"https://wttr.in/%s?format=%%f",gtk_editable_get_text(GTK_EDITABLE(entryLocation)));
        curl_easy_setopt(curl, CURLOPT_URL,tempurl);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writedata);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA, temp);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    strcpy(feelTempr,temp);

}

//Implementation of function to fetch humidity percentage
void fetchpercenthumidity(){
    CURL *curl = curl_easy_init();
    char temp[512];
    if (curl) {
        char tempurl[512];
        snprintf(tempurl, sizeof(tempurl),"https://wttr.in/%s?format=%%h",gtk_editable_get_text(GTK_EDITABLE(entryLocation)));
        curl_easy_setopt(curl, CURLOPT_URL,tempurl);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writedata);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, temp);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    strcpy(percenthumidity,temp);
}


//Implementation of function to fetch quantity of precipitate in mm
void fetchmmppt(){
    CURL *curl = curl_easy_init();
    char temp[512];
    if (curl) {
        char tempurl[512];
        snprintf(tempurl,sizeof(tempurl),"https://wttr.in/%s?format=%%p",gtk_editable_get_text(GTK_EDITABLE(entryLocation)));
        curl_easy_setopt(curl, CURLOPT_URL,tempurl);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,writedata);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, temp);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    strcpy(mmppt,temp);
}

//Implementation of fetchwind
void fetchwind() {
    CURL *curl = curl_easy_init();
    char temp[512];
    if (curl) {
        char tempurl[512];
        snprintf(tempurl,  sizeof(tempurl),"https://wttr.in/%s?format=%%w",gtk_editable_get_text(GTK_EDITABLE(entryLocation)));
        curl_easy_setopt(curl,CURLOPT_URL,tempurl);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writedata);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, temp);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    strcpy(wind,temp);
}

//Implementation of fetchSunrise
void fetchSunrise() {
    CURL *curl = curl_easy_init();
    char temp[512];
    if (curl) {
        char tempurl[512];
        snprintf(tempurl, sizeof(tempurl),"https://wttr.in/%s?format=%%S",gtk_editable_get_text(GTK_EDITABLE(entryLocation)));
        curl_easy_setopt(curl,CURLOPT_URL,tempurl);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writedata);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA, temp);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    strcpy(sunrise,temp);
}

//Implementation of fetchSunset
void fetchSunset() {
    CURL *curl = curl_easy_init();
    char temp[512];
    if (curl) {
        char tempurl[512];
        snprintf(tempurl, sizeof(tempurl),"https://wttr.in/%s?format=%%s",gtk_editable_get_text(GTK_EDITABLE(entryLocation)));
        curl_easy_setopt(curl,CURLOPT_URL,tempurl);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writedata);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,temp);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    strcpy(sunset,temp);
}


//To write the data received
size_t writedata(void *ptr, size_t size, size_t nmemb, void *userdata){
    char *buf = (char *)userdata;
    size_t total = size * nmemb;
    memcpy(buf, ptr, total);
    buf[total] = '\0';
    return total;
}

void updateWeatherInfo(){
    char weatherinfo[1024];
    snprintf(weatherinfo,sizeof(weatherinfo),
        "\n"
        "As the three eyed Raven gazes onto the world with\n "
        "His magical eyes\n"
        "He seeks the answers to the world...\n"
        "He Observes from his Magical Gaze that....\n"
        "The Magical Rooster Announces the \n"
        "Sunrise to be at %s \n"
        "While the Mage measures\n"
        " the heat to be %s \n"
        "Despite the Mage's attempt the Sensitive Salamander urges that \n"
        "he feels like it's %s \n"
        "As the Magical Prince turns into a frog \n"
        "in %s humidity \n "
        "The Birds Fly with the wind at %s \n"
        "As the chance of %s rain remains stagnant \n"
        "The Wizard declares the Weather to be %s \n"
        "The Owl announces the \n"
        "Sun to set at %s \n"
        ,sunrise,tempr,feelTempr,percenthumidity,wind,mmppt,weatherDescrip,sunset
        );

    //To Set the buffer text for text view weatherinfo
    GtkTextBuffer *weatherInfoText = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textviewWeatherInfo));
    gtk_text_buffer_set_text(weatherInfoText,weatherinfo,-1);

}

void closeProgram(){
    gtk_window_destroy(GTK_WINDOW(widgetTER.windowLogin));
}
