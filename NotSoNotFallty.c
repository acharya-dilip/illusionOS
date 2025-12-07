//
// Created by g4sker on 12/7/25.
//

#include "NotSoNotFallty.h"

#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

#include "main.h"

void initProject();
void navFolder();
void setFilePath(GObject *source, GAsyncResult *res, gpointer user_data);
void updateFilePath();
void fetchFilePath();

void initgitrepo();
void initghrepo();
void createghrepo();

void commit();
void clearCommitInfo();

void pushWindow();
void push();

void config();
void updateRemoteRepo();
void fetchRemoteRepo();
void updateGitCredentials();
void fetchGitCredentials();
void updateRemoteStuff();

//Global Variables
char filepath[256];
char remoterepo[256];
char ghusername[128];
char patoken[128];


//Globalised stuff for initProject
GtkWidget
*windowInit,
*entryDir;
void initProject() {
    GtkWidget
    *gridParent,
    *buttonNav,
    *buttonProceed,
    *headerInitProj,
    *buttonInitRepo;

    //Init of windowInit
    windowInit = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowInit),"Navigate to Project");
    gtk_window_present(GTK_WINDOW(windowInit));
    gtk_window_set_transient_for(GTK_WINDOW(windowInit),windowMainDesktop);

    //Init of headerInitProj
    headerInitProj = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(windowInit),headerInitProj);

    //Init of ButtonInitRepo
    buttonInitRepo = gtk_button_new_with_label("➕");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerInitProj),buttonInitRepo);
    g_signal_connect(buttonInitRepo,"clicked",G_CALLBACK(initghrepo),NULL);


    //Init of gridParent
    gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowInit),gridParent);
    //MArgins & Paddings
    gtk_widget_set_margin_start(gridParent,10);
    gtk_widget_set_margin_end(gridParent,10);
    gtk_widget_set_margin_top(gridParent,10);
    gtk_widget_set_margin_bottom(gridParent,10);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);

    //Init of entryDir
    entryDir = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryDir,0,1,5,1);
    //Margins& Paddings
    gtk_widget_set_size_request(entryDir,280,-1);
    //Call fetchFilePath to see if any previous dir is stored
    fetchFilePath();


    //Init of buttonNav
    buttonNav = gtk_button_new_with_label("🗀");
    gtk_grid_attach(GTK_GRID(gridParent),buttonNav,5,1,1,1);
    g_signal_connect(buttonNav,"clicked",G_CALLBACK(navFolder),NULL);
    //MArgins & Paddings
    gtk_widget_set_margin_start(buttonNav,10);

    //Init of buttonProceed
    buttonProceed = gtk_button_new_with_label("Proceed");
    gtk_grid_attach(GTK_GRID(gridParent),buttonProceed,0,2,6,1);
    g_signal_connect(buttonProceed,"clicked",G_CALLBACK(updateFilePath),NULL);
    //MArgins & Paddings
    gtk_widget_set_margin_top(buttonProceed,10);


}

void updateFilePath() {
    //Automatically inits git repo in set filepath
    initgitrepo();
    //sets the filepath var to the file path in the entry
    strcpy(filepath,gtk_editable_get_text(GTK_EDITABLE(entryDir)));
    //Writing the filepath to a txt file for persistancy
    FILE *file = fopen("filePath.txt","w");
    fprintf(file,
        "%s",filepath);
    fclose(file);
    gtk_window_destroy(GTK_WINDOW(windowInit));
}

void initgitrepo() {
    char temp[256];
    snprintf(temp,sizeof(temp),"cd %s && git init",filepath);
    system(temp);
}


void fetchFilePath() {
    FILE *file = fopen("filePath.txt","r");
    fscanf(file,"%s",filepath);
    fclose(file);
    gtk_editable_set_text(GTK_EDITABLE(entryDir),filepath);

}

void navFolder() {
    GtkWindow *windowNav = GTK_WINDOW(NULL);
    GtkFileDialog *dialogNav = gtk_file_dialog_new();

    GFile *home = g_file_new_for_path(g_get_home_dir());
    gtk_file_dialog_set_initial_folder(dialogNav, home);
    g_object_unref(home);
    gtk_file_dialog_select_folder(dialogNav, windowNav, NULL,setFilePath,windowNav);
}

void setFilePath(GObject *source, GAsyncResult *res, gpointer user_data) {
    //Fetches the file path
    GtkFileDialog *dialogNav = GTK_FILE_DIALOG(source);
    GFile *folder = gtk_file_dialog_select_folder_finish(dialogNav, res, NULL);
    char *path = g_file_get_path(folder);
    //Set the entryDir to the desired file path
    gtk_editable_set_text(GTK_EDITABLE(entryDir),path);

}

//Globalised variables
GtkWidget
    *windowGhRepo,
    *entryRepoName,
    *entryVisibility;

void initghrepo() {
    GtkWidget
    *gridParent,
    *labelRepoName,
    *labelVisibility,
    *buttonCreateGhRepo;

    //Init of windowGhRepo
    windowGhRepo = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowGhRepo),"Create Github Repo");
    gtk_window_present(GTK_WINDOW(windowGhRepo));
    gtk_window_set_transient_for(GTK_WINDOW(windowGhRepo),windowMainDesktop);


    //Init of gridParent
    gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowGhRepo),gridParent);
    //MArgins & Paddings
    gtk_widget_set_margin_start(gridParent,10);
    gtk_widget_set_margin_end(gridParent,10);
    gtk_widget_set_margin_top(gridParent,10);
    gtk_widget_set_margin_bottom(gridParent,10);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);

    //Init of labelRepoName
    labelRepoName = gtk_label_new("Repo Name:");
    gtk_grid_attach(GTK_GRID(gridParent),labelRepoName,0,0,1,1);
    //Margins & Paddings
    gtk_widget_set_halign(labelRepoName,GTK_ALIGN_END);
    gtk_widget_set_margin_end(labelRepoName,10);

    //Init of entryRepoName
    entryRepoName = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryRepoName,1,0,4,1);
    //MArgins & Paddings
    gtk_widget_set_size_request(entryRepoName,280,-1);

    //Init of labelVisibility
    labelVisibility = gtk_label_new("Visibility:");
    gtk_grid_attach(GTK_GRID(gridParent),labelVisibility,0,1,1,1);
    //Margins & Paddings
    gtk_widget_set_halign(labelVisibility,GTK_ALIGN_END);
    gtk_widget_set_margin_end(labelVisibility,10);

    //Init of entryVisibility
    entryVisibility = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryVisibility,1,1,4,1);
    gtk_editable_set_text(GTK_EDITABLE(entryVisibility),"public");

    //Init of buttonCreateGhRepo
    buttonCreateGhRepo = gtk_button_new_with_label("Create Repository");
    gtk_grid_attach(GTK_GRID(gridParent),buttonCreateGhRepo,1,2,4,1);
    g_signal_connect(buttonCreateGhRepo,"clicked",G_CALLBACK(createghrepo),NULL);

}

void createghrepo(){
    char command[256];
    snprintf(command,sizeof(command),"cd %s && gh repo create %s --%s",
        filepath,
        gtk_editable_get_text(GTK_EDITABLE(entryRepoName)),
        gtk_editable_get_text(GTK_EDITABLE(entryVisibility)));
    system(command);
    fetchGitCredentials();
    snprintf(remoterepo,sizeof(remoterepo),"https://github.com/%s/%s.git",
        ghusername,
        gtk_editable_get_text(GTK_EDITABLE(entryRepoName)));
    gtk_window_destroy(GTK_WINDOW(windowGhRepo));

}


//Globalised Variables
    GtkWidget
    *entryCommitTitle,
    *textviewCommitMessage,
    *windowMainNotSoNotFallty;
//for a test
void NotSoNotFallty() {
    FILE *file = fopen("filePath.txt","a");
    fclose(file);

    //Executes the navigater window thingy
    initProject();
    //Widgets for MainProgram
    GtkWidget
    *gridParent,
    *labelCommitMsg,
    *buttonPush,
    *headerMainWindow,
    *buttonCommit;

    //Init of windowMainNotSoNotFallty
    windowMainNotSoNotFallty = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowMainNotSoNotFallty),"NotSoNotFallty");
    gtk_window_set_default_size(GTK_WINDOW(windowMainNotSoNotFallty),270,320);
    gtk_window_present(GTK_WINDOW(windowMainNotSoNotFallty));

    //Init of headerMainWindow
    headerMainWindow = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(windowMainNotSoNotFallty),headerMainWindow);

    //Init of buttonPush
    buttonPush = gtk_button_new_with_label("🌐");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerMainWindow),buttonPush);
    g_signal_connect(buttonPush,"clicked",G_CALLBACK(pushWindow),NULL);


    //Init of gridParent
    gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowMainNotSoNotFallty),gridParent);
    //Margins & Paddings
    gtk_widget_set_margin_start(gridParent,10);
    gtk_widget_set_margin_end(gridParent,10);
    gtk_widget_set_margin_top(gridParent,10);
    gtk_widget_set_margin_bottom(gridParent,10);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);

    //Init of entryCommitTitle
    entryCommitTitle = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryCommitTitle,0,1,10,1);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryCommitTitle),"Enter Commit Title");
    //MArgins & Paddings
    gtk_widget_set_size_request(entryCommitTitle,300,-1);
    gtk_widget_set_margin_bottom(entryCommitTitle,6);

    //Init of labelCommitMsg
    labelCommitMsg = gtk_label_new("Commit Message:");
    gtk_grid_attach(GTK_GRID(gridParent),labelCommitMsg,0,2,10,1);
    //Margins & Padding
    gtk_widget_set_halign(labelCommitMsg,GTK_ALIGN_START);


    //Init of textviewCommitMessage
    textviewCommitMessage = gtk_text_view_new();
    gtk_grid_attach(GTK_GRID(gridParent),textviewCommitMessage,0,3,10,10);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textviewCommitMessage), GTK_WRAP_WORD_CHAR);
    //Margins & Paddings
    gtk_widget_set_size_request(textviewCommitMessage,300,200);
    gtk_widget_set_margin_bottom(textviewCommitMessage,10);


    //Init of buttonCommit
    buttonCommit = gtk_button_new_with_label("Commit");
    gtk_grid_attach(GTK_GRID(gridParent),buttonCommit,0,15,10,1);
    g_signal_connect(buttonCommit,"clicked",G_CALLBACK(commit),NULL);


}

void commit() {
    char command[1024];
    snprintf(command,sizeof(command),"cd %s && git add .",filepath);
    if (system(command)==0) {
        //Fetching text from the textviewCommitMesage
        GtkTextBuffer *bufferCommitMessage = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textviewCommitMessage));
        GtkTextIter start,end;
        gchar *commitMsg;
        gtk_text_buffer_get_start_iter(bufferCommitMessage,&start);
        gtk_text_buffer_get_end_iter(bufferCommitMessage,&end);
        commitMsg = gtk_text_buffer_get_text(bufferCommitMessage,&start,&end,FALSE);
        snprintf(command,sizeof(command),"cd %s && git commit -m \"%s\" -m \"%s\"",
            filepath,
            gtk_editable_get_text(GTK_EDITABLE(entryCommitTitle)),
            commitMsg);
        system(command);
        clearCommitInfo();
    }
    else {
        //Place a window that prompts user to init git if it fails and to try again
    }
}

void clearCommitInfo() {
    gtk_editable_set_text(GTK_EDITABLE(entryCommitTitle),"");
    GtkTextBuffer *tempbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textviewCommitMessage));
    gtk_text_buffer_set_text(tempbuffer,"",-1);
}

//Globalised Variables
GtkWidget
    *windowPush,
    *entryBranch;
void pushWindow() {
    GtkWidget
    *headerPush,
    *buttonConfig,
    *gridParent,
    *labelBranch,
    *buttonPush;

    //init of windowPush
    windowPush = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowPush),"Push To Remote");
    gtk_window_present(GTK_WINDOW(windowPush));

    //Init of headerPush
    headerPush = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(windowPush),headerPush);

    //Init of buttonConfig
    buttonConfig = gtk_button_new_with_label("🛠️");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerPush),buttonConfig);
    g_signal_connect(buttonConfig, "clicked", G_CALLBACK(config),NULL);

    //Init of gridParent
    gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowPush),gridParent);
    //Margins & Paddings
    gtk_widget_set_margin_start(gridParent,10);
    gtk_widget_set_margin_end(gridParent,10);
    gtk_widget_set_margin_top(gridParent,10);
    gtk_widget_set_margin_bottom(gridParent,10);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);

    //Init of labelBranch
    labelBranch = gtk_label_new("Push to Branch:");
    gtk_grid_attach(GTK_GRID(gridParent),labelBranch,0,0,1,1);
    //MArgins & Paddings
    gtk_widget_set_margin_end(labelBranch,10);

    //init of entryBranch
    entryBranch = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryBranch,1,0,4,1);
    gtk_widget_set_size_request(entryBranch,220,-1);
    gtk_editable_set_text(GTK_EDITABLE(entryBranch),"master");

    //init of buttonPush
    buttonPush = gtk_button_new_with_label("Push");
    gtk_grid_attach(GTK_GRID(gridParent),buttonPush,1,1,4,1);
    g_signal_connect(buttonPush,"clicked",G_CALLBACK(push),NULL);
    //Margins & Paddings
    gtk_widget_set_margin_top(buttonPush,4);

}

void push() {
    //fetch the stuff need
    fetchRemoteRepo();
    fetchGitCredentials();

    char authurl[256];
    char repourlclean[512];
       strcpy(repourlclean,strstr(remoterepo,"github.com"));
     snprintf(authurl,sizeof(authurl)," https://%s:%s@%s ",
         ghusername,
         patoken,
         repourlclean);
    printf("%s",authurl);
    char command[400];
     snprintf(command,sizeof(command),"cd %s && git push %s %s",
         filepath,
         authurl,
         gtk_editable_get_text(GTK_EDITABLE(entryBranch)));
    if (system(command)!=0){
        printf("fallback for push is triggered");
    snprintf(command,sizeof(command),"cd %s && git push origin %s",
        filepath,
        gtk_editable_get_text(GTK_EDITABLE(entryBranch)));
    system(command);
    }
    gtk_window_destroy(GTK_WINDOW(windowPush));
}

//Globalised Variables
GtkWidget
    *entryRepo,
    *entryUsername,
    *entryToken,
    *windowConfig;

void config() {
    GtkWidget
            *headerConfig,
            *gridParent,
            *labelRepo,
            *labelUsername,
            *labelToken,
            *buttonProceed;

    //Init of windowConfig
    windowConfig = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowConfig),"Configure");
    gtk_window_present(GTK_WINDOW(windowConfig));

    //Init of headerConfig
    headerConfig = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(windowConfig),headerConfig);

    //Init of gridParent
    gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowConfig),gridParent);
    //Margins & Paddings
    gtk_widget_set_margin_start(gridParent,10);
    gtk_widget_set_margin_end(gridParent,10);
    gtk_widget_set_margin_top(gridParent,10);
    gtk_widget_set_margin_bottom(gridParent,10);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);

    //Init of labelrepo
    labelRepo = gtk_label_new("Github Repo:");
    gtk_grid_attach(GTK_GRID(gridParent),labelRepo,0,0,1,1);
    //Margins & Paddings
    gtk_widget_set_margin_end(labelRepo,10);
    gtk_widget_set_halign(labelRepo,GTK_ALIGN_END);

    //Init of entryRepo
    entryRepo = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryRepo,1,0,8,1);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryRepo),"Enter Github Repo URL");
    //fetch the stored remote repo if there's one
    fetchRemoteRepo();

    //Init of labelUsername
    labelUsername = gtk_label_new("Username:");
    gtk_grid_attach(GTK_GRID(gridParent),labelUsername,0,1,1,1);
    //Margins & Paddings
    gtk_widget_set_margin_end(labelUsername,10);
    gtk_widget_set_halign(labelUsername,GTK_ALIGN_END);

    //Init of entryUsername
    entryUsername = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryUsername,1,1,8,1);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryUsername),"Enter Github Username");
    //Margins & Paddings
    gtk_widget_set_size_request(entryUsername,360,-1);

    //Init of labelToken
    labelToken = gtk_label_new("PA Token:");
    gtk_grid_attach(GTK_GRID(gridParent),labelToken,0,2,1,1);
    //Margins & Paddings
    gtk_widget_set_margin_end(labelToken,10);
    gtk_widget_set_halign(labelToken,GTK_ALIGN_END);

    //Init of entryToken
    entryToken = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryToken,1,2,8,1);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryToken),"Enter Personal Access Token");
    gtk_entry_set_visibility(GTK_ENTRY(entryToken),FALSE);
    //fetch git credentials
    fetchGitCredentials();

    //Init of buttonProceed
    buttonProceed = gtk_button_new_with_label("Proceed");
    gtk_grid_attach(GTK_GRID(gridParent),buttonProceed,1,4,8,1);
    g_signal_connect(buttonProceed,"clicked",G_CALLBACK(updateRemoteStuff),NULL);

}

void updateRemoteStuff() {
    updateRemoteRepo();
    updateGitCredentials();
    gtk_window_destroy(GTK_WINDOW(windowConfig));
}

void updateRemoteRepo() {
    //checks if there's a file named ghrepo.txt if not creates tge file
    FILE *pf = fopen("ghrepo.txt","a");
    fclose(pf);
    //Writes the repo url to the ghrepo.txt file
    FILE *file = fopen("ghrepo.txt","w");
    fprintf(file,"%s",
                    gtk_editable_get_text(GTK_EDITABLE(entryRepo)));
    fclose(file);

    char temp[512];
    snprintf(temp,sizeof(temp),"cd %s && git remote set-url origin %s",
    filepath,
    gtk_editable_get_text(GTK_EDITABLE(entryRepo)));
    if (system(temp)!=0){
        snprintf(temp,sizeof(temp),"cd %s && git remote add origin %s",
                                     filepath,
                                     gtk_editable_get_text(GTK_EDITABLE(entryRepo)));
    }
}


void fetchRemoteRepo() {
    FILE *pf = fopen("ghrepo.txt","a");
    fclose(pf);
    //Scans the remote repo url from ghrepo.txt
    FILE *file = fopen("ghrepo.txt","r");
    fscanf(file,"%s",remoterepo);
    fclose(file);
    printf("%s",remoterepo);
    gtk_editable_set_text(GTK_EDITABLE(entryRepo),remoterepo);

}

void updateGitCredentials() {
    FILE *pf = fopen("credentials.txt","a");
    fclose(pf);

    FILE *file = fopen("credentials.txt","w");
    fprintf(file,"%s %s",
        gtk_editable_get_text(GTK_EDITABLE(entryUsername)),
              gtk_editable_get_text(GTK_EDITABLE(entryToken)));

    //You can also add git credential manager overrite thing with system()

}

void fetchGitCredentials() {
    FILE *pf = fopen("credentials.txt","a");
    fclose(pf);
    FILE *file = fopen("credentials.txt","r");
    fscanf(file,"%s %s",
        ghusername,
        patoken);
    gtk_editable_set_text(GTK_EDITABLE(entryUsername),ghusername);
    gtk_editable_set_text(GTK_EDITABLE(entryToken),patoken);
}

