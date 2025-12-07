//
// Created by g4sker on 12/7/25.
//

#include "JustaGuiFramework.h"

#include <stdio.h>
#include <gtk/gtk.h>
struct widgets{
    int isOccupied;
    char widgetName[100];
    GtkWidget *widget;
    //For the display thing
    GtkWidget *placeholderLabel;
    GtkWidget *gridChildBox;
    GtkWidget *labelWidgetInfo;
    GtkWidget *frameWidgetLabel;
    GtkWidget *buttonDeleteWidget;
    GtkWidget *buttonEditWidget;

    char label[100];
    struct grid {
        int row;
        int col;
        int rowSpan;
        int colSpan;
    }grid;
    struct minSize{
    int height;
    int width;
    }minSize;
    struct widgetType {
        char widgetTypeName[100];
        int isButton;
        int isEntry;
        int isLabel;
        int isTextView;
    }type;
    struct entry {
        int hasPlaceHolderText;
        char placeholderText[100];
    }entry;
    struct margins {
        int top;
        int bottom;
        int start;
        int end;
    }margin;
}widget[100];
int widgetCount;
void screenAddWidget();
void registerWidget(GtkButton *button, gpointer user_data);
void declareWidgetLabels();
void deleteWidget(GtkButton *button, gpointer user_data);
void screenWindowChild();
void exportGui();
void declareWidgets();
void widgetAttributeWidgets(GtkWidget *window, int i);
void editWidget(GtkButton *button, gpointer user_data);
void importGui();
void readWidgetData(char *filepath);
void navFolder();



//Globalised variables
GtkWidget *windowChild;
GtkWidget *gridParentWidgets;
void screenWindowChild() {
    //Init of windowChild
    windowChild = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowChild),"JustaGuiFramework");
    gtk_window_set_default_size(GTK_WINDOW(windowChild),200,200);
    gtk_window_present(GTK_WINDOW(windowChild));
    gtk_widget_add_css_class(windowChild,"windowChild");
    //Init of gridParent
    GtkWidget *gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowChild),gridParent);
    //MArgins & Paddings
    gtk_widget_set_margin_start(gridParent,10);
    gtk_widget_set_margin_end(gridParent,10);
    gtk_widget_set_margin_top(gridParent,10);
    gtk_widget_set_margin_bottom(gridParent,10);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);
    //Declares the widgets with their appropiriate widgetType
    declareWidgets();
    for (int i=0;i<widgetCount;i++) {
        if (widget[i].isOccupied==1) {
            gtk_grid_attach(GTK_GRID(gridParent),widget[i].widget,
            widget[i].grid.col,
            widget[i].grid.row,
            widget[i].grid.colSpan,
            widget[i].grid.rowSpan);
            gtk_widget_set_size_request(widget[i].widget,
                widget[i].minSize.width,
                widget[i].minSize.height);
        }
    }
}

//GLovalisized variables
GtkWidget *windowAddWidget;
void screenAddWidget() {




    //Init of windowAddWidget
    windowAddWidget = gtk_window_new();
    gtk_window_set_default_size(GTK_WINDOW(windowAddWidget),300,300);
    gtk_window_set_title(GTK_WINDOW(windowAddWidget),"Add Widget");
    gtk_window_present(GTK_WINDOW(windowAddWidget));



    widgetAttributeWidgets(windowAddWidget,widgetCount);


    //Init of buttonAddWidget
    GtkWidget *buttonRegisterWidget = gtk_button_new_with_label("Add Widget");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),buttonRegisterWidget,0,20,10,1);
    g_signal_connect(buttonRegisterWidget,"clicked",G_CALLBACK(registerWidget),GINT_TO_POINTER(widgetCount));
    //Margins & Paddings
    gtk_widget_set_margin_top(buttonRegisterWidget,10);

}


void editWidget(GtkButton *button, gpointer user_data) {
    int i = GPOINTER_TO_INT(user_data);
    //Init of windowEditWidget
    GtkWidget *windowEditWidget = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowEditWidget),"Edit Widget");
    gtk_window_set_default_size(GTK_WINDOW(windowEditWidget),400,500);
    gtk_window_present(GTK_WINDOW(windowEditWidget));

    //Calls the declaration of the widgets in windowEditWidget
    widgetAttributeWidgets(windowEditWidget,i);

    //Init of buttonSaveEdit
    GtkWidget *buttonSaveEdit = gtk_button_new_with_label("Save Changes");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),buttonSaveEdit,0,20,10,1);
    g_signal_connect(buttonSaveEdit,"clicked",G_CALLBACK(registerWidget),GINT_TO_POINTER(i));
    //Margins & Paddings
    gtk_widget_set_margin_top(buttonSaveEdit,10);
}

//Glovbized Varuables
GtkWidget *entryWidgetName;
GtkWidget *dropdownWidgets;
GtkWidget *spinbuttonGridPlacementRow;
GtkWidget *spinbuttonGridPlacementColumn;
GtkWidget *spinbuttonGridPlacementRowSpan;
GtkWidget *spinbuttonGridPlacementColumnSpan;
GtkWidget *spinbuttonMinHeight;
GtkWidget *spinbuttonMinWidth;
GtkWidget *spinbuttonMarginStart;
GtkWidget *spinbuttonMarginEnd;
GtkWidget *spinbuttonMarginTop;
GtkWidget *spinbuttonMarginBottom;
GtkWidget *entryLabel;
const char *widgetList[]={"Button","Label","Entry","T.View",NULL};
GtkStringList *listWidgets;

void widgetAttributeWidgets(GtkWidget *window,int i) {
    printf("updateScreenAddWidgets() is executing");

    //Init of defaultAdjustment
    GtkAdjustment *defaultAdjustmentRow = gtk_adjustment_new(widget[i].grid.row, 0.0, 1000.0, 1.0, 10.0, 0.0);
    GtkAdjustment *defaultAdjustmentColumn = gtk_adjustment_new(widget[i].grid.col, 0.0, 1000.0, 1.0, 10.0, 0.0);
    GtkAdjustment *defaultAdjustmentRowSpan = gtk_adjustment_new(widget[i].grid.rowSpan, 0.0, 1000.0, 1.0, 10.0, 0.0);
    GtkAdjustment *defaultAdjustmentColumnSpan = gtk_adjustment_new(widget[i].grid.colSpan, 0.0, 1000.0, 1.0, 10.0, 0.0);
    GtkAdjustment *defaultAdjustmentMinHeight = gtk_adjustment_new(widget[i].minSize.height, 0.0, 1000.0, 1.0, 10.0, 0.0);
    GtkAdjustment *defaultAdjustmentMinWidth = gtk_adjustment_new(widget[i].minSize.width, 0.0, 1000.0, 1.0, 10.0, 0.0);
    GtkAdjustment *defaultAdjustmentMarginStart = gtk_adjustment_new(widget[i].margin.start, 0.0, 1000.0, 1.0, 10.0, 0.0);
    GtkAdjustment *defaultAdjustmentMarginEnd = gtk_adjustment_new(widget[i].margin.end, 0.0, 1000.0, 1.0, 10.0, 0.0);
    GtkAdjustment *defaultAdjustmentMarginTop = gtk_adjustment_new(widget[i].margin.top, 0.0, 1000.0, 1.0, 10.0, 0.0);
    GtkAdjustment *defaultAdjustmentMarginBottom = gtk_adjustment_new(widget[i].margin.bottom, 0.0, 1000.0, 1.0, 10.0, 0.0);

     //Init of gridParentWidgets
    gridParentWidgets = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window),gridParentWidgets);
    //Margins & Paddings
    gtk_widget_set_margin_top(gridParentWidgets,10);
    gtk_widget_set_margin_bottom(gridParentWidgets,10);
    gtk_widget_set_margin_end(gridParentWidgets,10);
    gtk_widget_set_margin_start(gridParentWidgets,10);


    //Init of entryWidgetName
    entryWidgetName = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParentWidgets),entryWidgetName,0,0,8,1);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryWidgetName),"Enter Widget Name");
    gtk_editable_set_text(GTK_EDITABLE(entryWidgetName),widget[i].widgetName);
    //Margins & Paddings
    gtk_widget_set_size_request(entryWidgetName,210,-1);


    //Init of dropdownWidgets
    listWidgets = gtk_string_list_new(widgetList);
    dropdownWidgets = gtk_drop_down_new(G_LIST_MODEL (listWidgets), NULL);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),dropdownWidgets,8,0,2,1);
    g_signal_connect(dropdownWidgets,"notify::selected",G_CALLBACK(widgetAttributeWidgets),NULL);


    //Init of entrylabel
    entryLabel = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParentWidgets),entryLabel,0,1,10,1);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryLabel),"Enter Widget Label/Placeholder Text");
    //Margins & Paddings
    gtk_widget_set_margin_top(entryLabel,10);


    //Init of labelPlacement
    GtkWidget *labelPlacement = gtk_label_new("Grid Placement:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelPlacement,0,2,6,1);
    gtk_widget_set_halign(labelPlacement,GTK_ALIGN_START);
    gtk_widget_set_margin_start(labelPlacement,6);
    gtk_widget_set_margin_top(labelPlacement,6);
    gtk_widget_set_margin_bottom(labelPlacement,10);



    //Init of labelGridPlacementRow
    GtkWidget *labelGridPlacementRow = gtk_label_new("Row:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelGridPlacementRow,0,3,1,1);
    gtk_widget_set_margin_top(labelGridPlacementRow,4);



    //Init of spinbuttonGridPlacementRow
    spinbuttonGridPlacementRow = gtk_spin_button_new(defaultAdjustmentRow,1,0);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),spinbuttonGridPlacementRow,1,3,5,1);


    //Init of labelGridPlacementColumn
    GtkWidget *labelGridPlacementColumn = gtk_label_new("Col:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelGridPlacementColumn,6,3,1,1);
    gtk_widget_set_margin_top(labelGridPlacementColumn,4);



    //Init of spinbuttonGridPlacementColumn
    spinbuttonGridPlacementColumn = gtk_spin_button_new(defaultAdjustmentColumn ,1,0);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),spinbuttonGridPlacementColumn,7,3,3,1);


    //Init of labelGridPlacementRowSpan
    GtkWidget *labelGridPlacementRowSpan = gtk_label_new("Height:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelGridPlacementRowSpan,0,4,1,1);
    gtk_widget_set_margin_top(labelGridPlacementRowSpan,4);


    //Init of spinbuttonGridPlacementRowSpan
    spinbuttonGridPlacementRowSpan = gtk_spin_button_new(defaultAdjustmentRowSpan,1,0);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),spinbuttonGridPlacementRowSpan,1,4,5,1);
    gtk_widget_set_margin_top(spinbuttonGridPlacementRowSpan,4);



    //Init of labelGridPlacementColumnSpan
    GtkWidget *labelGridPlacementColumnSpan = gtk_label_new("Width:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelGridPlacementColumnSpan,6,4,1,1);
    gtk_widget_set_margin_top(labelGridPlacementColumnSpan,4);



    //Init of spinbuttonGridPlacementColumnSpan
    spinbuttonGridPlacementColumnSpan = gtk_spin_button_new(defaultAdjustmentColumnSpan ,1,0);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),spinbuttonGridPlacementColumnSpan,7,4,3,1);
    gtk_widget_set_margin_top(spinbuttonGridPlacementColumnSpan,4);



    //Init of labelMinSize
    GtkWidget *labelMinSize = gtk_label_new("Minimum Size:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelMinSize,0,5,6,1);
    gtk_widget_set_halign(labelMinSize,GTK_ALIGN_START);
    gtk_widget_set_margin_start(labelMinSize,6);
    gtk_widget_set_margin_top(labelMinSize,6);
    gtk_widget_set_margin_bottom(labelMinSize,10);



    //Init of labelMinHeight
    GtkWidget *labelMinHeight = gtk_label_new("Height:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelMinHeight,0,6,1,1);
    gtk_widget_set_margin_top(labelMinHeight,4);



    //Init of spinbuttonMinHeight
    spinbuttonMinHeight = gtk_spin_button_new(defaultAdjustmentMinHeight,1,0);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),spinbuttonMinHeight,1,6,5,1);
    gtk_widget_set_margin_top(spinbuttonMinHeight,4);


    //Init of labelMinWidth
    GtkWidget *labelMinWidth = gtk_label_new("Width:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelMinWidth,6,6,1,1);
    gtk_widget_set_margin_top(labelMinWidth,4);


    //Init of spinbuttonMinWidth
    spinbuttonMinWidth = gtk_spin_button_new(defaultAdjustmentMinWidth ,1,0);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),spinbuttonMinWidth,7,6,3,1);
    gtk_widget_set_margin_top(spinbuttonMinWidth,4);


    //Init of labelMargins
    GtkWidget *labelMargins = gtk_label_new("Margin Size for Widget:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelMargins,0,7,10,1);
    gtk_widget_set_halign(labelMargins,GTK_ALIGN_START);
    gtk_widget_set_margin_start(labelMargins,6);
    gtk_widget_set_margin_top(labelMargins,10);
    gtk_widget_set_margin_bottom(labelMargins,10);



    //Init of labelMarginStart
    GtkWidget *labelMarginStart = gtk_label_new("Start:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelMarginStart,0,8,1,1);
    gtk_widget_set_margin_top(labelMarginStart,4);



    //Init of spinbuttonMarginStart
    spinbuttonMarginStart = gtk_spin_button_new(defaultAdjustmentMarginStart,1,0);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),spinbuttonMarginStart,1,8,5,1);
    gtk_widget_set_margin_top(spinbuttonMarginStart,4);



    //Init of labelMarginEnd
    GtkWidget *labelMarginEnd = gtk_label_new("End:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelMarginEnd,6,8,1,1);
    gtk_widget_set_margin_top(labelMarginEnd,4);



    //Init of spinbuttonMarginEnd
    spinbuttonMarginEnd = gtk_spin_button_new(defaultAdjustmentMarginEnd ,1,0);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),spinbuttonMarginEnd,7,8,3,1);
    gtk_widget_set_margin_top(spinbuttonMarginEnd,4);



    //Init of labelMarginTop
    GtkWidget *labelMarginTop = gtk_label_new("Top:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelMarginTop,0,9,1,1);
    gtk_widget_set_margin_top(labelMarginTop,4);



    //Init of spinbuttonMarginTop
    spinbuttonMarginTop = gtk_spin_button_new(defaultAdjustmentMarginTop,1,0);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),spinbuttonMarginTop,1,9,5,1);
    gtk_widget_set_margin_top(spinbuttonMarginTop,4);



    //Init of labelMarginBottom
    GtkWidget *labelMarginBottom = gtk_label_new("Bottom:");
    gtk_grid_attach(GTK_GRID(gridParentWidgets),labelMarginBottom,6,9,1,1);
    gtk_widget_set_margin_top(labelMarginBottom,4);



    //Init of spinbuttonMarginBottom
    spinbuttonMarginBottom = gtk_spin_button_new(defaultAdjustmentMarginBottom ,1,0);
    gtk_grid_attach(GTK_GRID(gridParentWidgets),spinbuttonMarginBottom,7,9,3,1);
    gtk_widget_set_margin_top(spinbuttonMarginBottom,4);
}



//It registers/Inputs the values of the widgets and their properties in the widget struct
void  registerWidget(GtkButton *button, gpointer user_data) {

    int i = GPOINTER_TO_INT(user_data);

    //Function to hold all the logic for when the buttonRegister
    widget[i].isOccupied = 1;
    strcpy(widget[i].widgetName,gtk_editable_get_text(GTK_EDITABLE(entryWidgetName)));
    const char *widgetType = gtk_string_list_get_string(GTK_STRING_LIST(listWidgets), gtk_drop_down_get_selected(GTK_DROP_DOWN(dropdownWidgets)));
    strcpy(widget[i].type.widgetTypeName,widgetType);
    if(strcmp(widget[i].type.widgetTypeName,"Button")==0){
        strcpy(widget[i].label,gtk_editable_get_text(GTK_EDITABLE(entryLabel)));
        widget[i].type.isButton = 1;
    }
    else if(strcmp(widgetType,"Label")==0){
        strcpy(widget[i].label,gtk_editable_get_text(GTK_EDITABLE(entryLabel)));
        widget[i].type.isLabel = 1;
    }
    else if(strcmp(widgetType,"Entry")==0) {
        widget[i].type.isEntry = 1;
        if (strcmp(gtk_editable_get_text(GTK_EDITABLE(entryLabel)),"")!=0){
            strcpy(widget[i].entry.placeholderText,gtk_editable_get_text(GTK_EDITABLE(entryLabel)));
            widget[i].entry.hasPlaceHolderText = 1;
        }
    }else if(strcmp(widgetType,"T.View")==0){
        widget[i].type.isTextView = 1;
    }
        widget[i].grid.row = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonGridPlacementRow));
        widget[i].grid.col = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonGridPlacementColumn));
        widget[i].grid.rowSpan = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonGridPlacementRowSpan));
        widget[i].grid.colSpan = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonGridPlacementColumnSpan));
    //Checks if colspan and rowspan is 0 or less and defaults the value to -1 if that's the case
        if (widget[i].grid.rowSpan<=0 && widget[i].grid.colSpan<=0) {
            widget[i].grid.rowSpan=1;
            widget[i].grid.colSpan=1;
        }else if (widget[i].grid.rowSpan<=0) {
            widget[i].grid.rowSpan=1;
        }else if (widget[i].grid.colSpan<=0) {
            widget[i].grid.colSpan=1;
        }
        widget[i].minSize.height = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonMinHeight));
        widget[i].minSize.width = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonMinWidth));
        //checks if min height or width is 0 or less if so defaults it to -1
        if (widget[i].minSize.height<=0 && widget[i].minSize.width<=0) {
            widget[i].minSize.height=-1;
            widget[i].minSize.width=-1;
        }else if (widget[i].minSize.height<=0) {
            widget[i].minSize.height=-1;
        }else if (widget[i].minSize.width<=0) {
            widget[i].minSize.width=-1;
        }
        //Reads and stores the margin values
        widget[i].margin.top = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonMarginTop));
        widget[i].margin.bottom = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonMarginBottom));
        widget[i].margin.start = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonMarginStart));
        widget[i].margin.end = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonMarginEnd));
        //Increases the widgetCount as more widgets are added
        widgetCount++;
        gtk_window_destroy(GTK_WINDOW(windowAddWidget));
        declareWidgetLabels();
    }


    //Globalization of variables
    GtkWidget *scrolledWindowWidgets;
    GtkWidget *gridWidgets;
    void JustaGuiFramework(){

        //init of windowMain
        GtkWidget *windowMain = gtk_window_new();
        gtk_window_set_default_size(GTK_WINDOW(windowMain),400,500);
        gtk_window_set_title(GTK_WINDOW(windowMain),"JustaGuiFramework");
        gtk_window_present(GTK_WINDOW(windowMain));
        //init of headerMain
        GtkWidget *headerMain = gtk_header_bar_new();
        gtk_window_set_titlebar(GTK_WINDOW(windowMain),headerMain);
        //init of button add widget
        GtkWidget *buttonAddWidget = gtk_button_new_with_label("➕");
        gtk_header_bar_pack_start(GTK_HEADER_BAR(headerMain),buttonAddWidget);
        g_signal_connect(buttonAddWidget,"clicked",G_CALLBACK(screenAddWidget),NULL);
        //init buttonChildWindow
        GtkWidget *buttonChildWindow = gtk_button_new_with_label("🧭");
        gtk_header_bar_pack_start(GTK_HEADER_BAR(headerMain),buttonChildWindow);
        g_signal_connect(buttonChildWindow,"clicked",G_CALLBACK(screenWindowChild),NULL);
        //init of gridParent
        GtkWidget *gridParent = gtk_grid_new();
        gtk_window_set_child(GTK_WINDOW(windowMain),gridParent);
        //Margins & Paddings
        gtk_widget_set_margin_start(gridParent,10);
        gtk_widget_set_margin_end(gridParent,10);
        gtk_widget_set_margin_top(gridParent,10);
        gtk_widget_set_margin_bottom(gridParent,10);
        gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
        gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);
        //init of labelWidgets
        GtkWidget *labelWidgets = gtk_label_new("Widgets");
        gtk_grid_attach(GTK_GRID(gridParent),labelWidgets,0,0,10,1);
        gtk_widget_add_css_class(labelWidgets,"labelWidgets");
        //Init of scrolledWindowWidgets
        scrolledWindowWidgets = gtk_scrolled_window_new();
        gtk_grid_attach(GTK_GRID(gridParent),scrolledWindowWidgets,0,1,10,10);
        gtk_widget_set_size_request(scrolledWindowWidgets,380,400);
        //Init of gridScrolledWindow
        gridWidgets = gtk_grid_new();
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindowWidgets),gridWidgets);

        //Init of buttonImportGui
        GtkWidget *buttonImportGui = gtk_button_new_with_label("Import");
        gtk_grid_attach(GTK_GRID(gridParent),buttonImportGui,0,12,10,1);
        g_signal_connect(buttonImportGui,"clicked",G_CALLBACK(importGui),NULL);
        gtk_widget_set_size_request(buttonImportGui,400,-1);

        //Init of buttonExportGui
        GtkWidget *buttonExportGui = gtk_button_new_with_label("Export");
        gtk_grid_attach(GTK_GRID(gridParent),buttonExportGui,0,13,10,1);
        g_signal_connect(buttonExportGui,"clicked",G_CALLBACK(exportGui),NULL);
        gtk_widget_set_size_request(buttonExportGui,400,-1);
    }




void on_file_selected(GObject *source, GAsyncResult *res, gpointer user_data) {
        GtkFileDialog *dialog = GTK_FILE_DIALOG(source);
        GFile *file = gtk_file_dialog_open_finish(dialog, res, NULL);
        char *filePath = g_file_get_path(file);
        readWidgetData(filePath);
        g_free(filePath);
        g_object_unref(file);
    }
    void importGui() {
        GtkFileDialog *dialog = gtk_file_dialog_new();
        gtk_file_dialog_open(dialog, NULL, NULL, on_file_selected, NULL);
    }
    void readWidgetData(char *filepath) {
            FILE *file = fopen(filepath,"r");
            fread(&widgetCount, sizeof(widgetCount), 1, file);
            fread(&widget,sizeof(widget),widgetCount,file);
            fclose(file);
        declareWidgetLabels();
    }



    void declareWidgetLabels() {
        //Removes the old widgets
        GtkWidget *child;
        while ((child = gtk_widget_get_first_child(GTK_WIDGET(gridWidgets))) != NULL) {
            gtk_grid_remove(GTK_GRID(gridWidgets), child);
        }
        //Adds plaques/Labels for widgets with some of their info
        for (int i=0; i < widgetCount; i++) {
            //checks if the widget is occupied
            if (widget[i].isOccupied==1){

                //Init of frameWidgetLabel
                widget[i].frameWidgetLabel = gtk_frame_new(NULL);
                gtk_grid_attach(GTK_GRID(gridWidgets),widget[i].frameWidgetLabel,0,i,1,1);
                gtk_widget_set_size_request(widget[i].frameWidgetLabel,380,50);


                //init of gridChildBox
                widget[i].gridChildBox=gtk_grid_new();
                gtk_frame_set_child(GTK_FRAME(widget[i].frameWidgetLabel),widget[i].gridChildBox);

                //init of placeholderLabel
                widget[i].placeholderLabel = gtk_label_new("");
                gtk_grid_attach(GTK_GRID(widget[i].gridChildBox),widget[i].placeholderLabel,0,0,10,1);
                gtk_widget_set_size_request(widget[i].placeholderLabel,380,-1);

                //init of labelWidgetinfo
                char widgetInfo[200];
                snprintf(widgetInfo,sizeof(widgetInfo),"%s \n"
                                                       "Widget Type: %s \n"
                                                       "Grid Placement: %d %d",
                                                       widget[i].widgetName,
                                                       widget[i].type.widgetTypeName,
                                                       widget[i].grid.row,
                                                       widget[i].grid.col);
                widget[i].labelWidgetInfo = gtk_label_new(widgetInfo);
                gtk_grid_attach(GTK_GRID(widget[i].gridChildBox),widget[i].labelWidgetInfo,1,0,1,1);


                //Init of buttonEditWidget
                widget[i].buttonEditWidget = gtk_button_new_with_label("📝");
                g_signal_connect(widget[i].buttonEditWidget,"clicked",G_CALLBACK(editWidget),GINT_TO_POINTER(i));
                gtk_grid_attach(GTK_GRID(widget[i].gridChildBox),widget[i].buttonEditWidget,8,0,1,1);
                gtk_widget_set_halign(widget[i].buttonEditWidget,GTK_ALIGN_END);
                gtk_widget_set_valign(widget[i].buttonEditWidget,GTK_ALIGN_CENTER);


                //Init of buttonDeleteWidget
                widget[i].buttonDeleteWidget = gtk_button_new_with_label("✖️");
                g_signal_connect(widget[i].buttonDeleteWidget,"clicked",G_CALLBACK(deleteWidget),GINT_TO_POINTER(i));
                gtk_grid_attach(GTK_GRID(widget[i].gridChildBox),widget[i].buttonDeleteWidget,9,0,1,1);
                gtk_widget_set_halign(widget[i].buttonDeleteWidget,GTK_ALIGN_START);
                gtk_widget_set_valign(widget[i].buttonDeleteWidget,GTK_ALIGN_CENTER);



            }
        }
    }




    //Overrites the widget that is to be deleted with the succeeding widget and soon
    void deleteWidget(GtkButton *button, gpointer user_data){
        int i = GPOINTER_TO_INT(user_data);
        for (int j = i; j!=widgetCount ; j++) {
            widget[j] = widget[j+1];
        }
        declareWidgetLabels();
        widgetCount--;
    }
    char filepath[200];

    void exportGuiData() {
        //Writes the widget data in binary for other program to read
        if (strcmp(filepath,"")==0) {
            FILE *file1 = fopen("ExportedGui/build/widget.data","w");
            fwrite(&widgetCount,sizeof(widgetCount),1,file1);
            fwrite(&widget,sizeof(widget),widgetCount,file1);
            fclose(file1);
        }else {
            char temp[250];
            snprintf(temp,sizeof(temp),"%s/widget.data",filepath);
            FILE *file1 = fopen(temp,"w");
            fwrite(&widgetCount,sizeof(widgetCount),1,file1);
            fwrite(&widget,sizeof(widget),widgetCount,file1);
            fclose(file1);
        }



        //Writes the data in a documentation style for a hooman to read
        FILE *file2 = fopen("ExportedGui/build/WidgetDocumentation.txt","w");
        fprintf(file2,"S.N. \t Widget Name \t Widget Type \t Row \t Row Span \t Column \t Column Span \t Min Width \t Min Height \t Margin Top \t Margin Bottom \t Margin Start \t Margin End \n");
        for (int i =0; i<widgetCount;i++) {
            fprintf(file2,"%d \t %s \t %s \t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \n",
                i+1,
                widget[i].widgetName,
                widget[i].type.widgetTypeName,
                widget[i].grid.row,
                widget[i].grid.rowSpan,
                widget[i].grid.col,
                widget[i].grid.colSpan,
                widget[i].minSize.width,
                widget[i].minSize.height,
                widget[i].margin.top,
                widget[i].margin.bottom,
                widget[i].margin.start,
                widget[i].margin.end);
        }
        fclose(file2);
    }

GtkWidget *entryFilePath;
void exportGui() {

    //Init of windowExportGui
    GtkWidget *windowExportGui = gtk_window_new();
    gtk_window_set_default_size(GTK_WINDOW(windowExportGui),300,150);
    gtk_window_set_title(GTK_WINDOW(windowExportGui),"Export To:");
    gtk_window_present(GTK_WINDOW(windowExportGui));

    //Init of gridExportGui
    GtkWidget *gridExportGui = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowExportGui),gridExportGui);
    gtk_widget_set_halign(gridExportGui,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridExportGui, GTK_ALIGN_CENTER);


    //Init of entryFilePath
    entryFilePath = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridExportGui),entryFilePath,0,0,20,1);
    gtk_widget_set_size_request(entryFilePath,230,-1);

    //Init of buttonChoosePath
    GtkWidget *buttonChoosePath = gtk_button_new_with_label("📂");
    gtk_grid_attach(GTK_GRID(gridExportGui),buttonChoosePath,20,0,1,1);
    g_signal_connect(buttonChoosePath,"clicked",G_CALLBACK(navFolder),NULL);

    //Init of buttonExport
    GtkWidget *buttonExport = gtk_button_new_with_label("Export");
    gtk_grid_attach(GTK_GRID(gridExportGui),buttonExport,0,1,21,1);
    g_signal_connect(buttonExport,"clicked",G_CALLBACK(exportGuiData),NULL);


}
void setFilePath(GObject *source, GAsyncResult *res, gpointer user_data) {
        //Fetches the file path
        GtkFileDialog *dialogNav = GTK_FILE_DIALOG(source);
        GFile *folder = gtk_file_dialog_select_folder_finish(dialogNav, res, NULL);
        char *path = g_file_get_path(folder);
        strcpy(filepath,path);
        //Set the entryDir to the desired file path
        gtk_editable_set_text(GTK_EDITABLE(entryFilePath),path);

    }
void navFolder() {
        GtkWindow *windowNav = GTK_WINDOW(NULL);
        GtkFileDialog *dialogNav = gtk_file_dialog_new();

        GFile *home = g_file_new_for_path(g_get_home_dir());
        gtk_file_dialog_set_initial_folder(dialogNav, home);
        g_object_unref(home);
        gtk_file_dialog_select_folder(dialogNav, windowNav, NULL,setFilePath,windowNav);
    }


    //Declares the widget in the struct according to the information and configurations provided
    void declareWidgets() {
        //Sets the widgets as null
        int i=0;
        while (widget[i].widget!=NULL) {
            widget[i].widget=NULL;
            i++;
        }
        //This Part   actualy does the comparing and declaring
        for (int j = 0; j<widgetCount;j++) {
            if (widget[j].type.isButton==1) {
                widget[j].widget = gtk_button_new_with_label(widget[j].label);
            }else if (widget[j].type.isLabel==1){
                widget[j].widget = gtk_label_new(widget[j].label);
            }else if (widget[j].type.isTextView==1){
            widget[j].widget = gtk_text_view_new();
            }else if (widget[j].type.isEntry==1) {
                widget[j].widget = gtk_entry_new();
                    if (widget[j].entry.hasPlaceHolderText==1) {
                    gtk_entry_set_placeholder_text(GTK_ENTRY(widget[j].widget),widget[j].entry.placeholderText);
                }
            }
            //Registering the Margins values
            gtk_widget_set_margin_top(widget[j].widget,widget[j].margin.top);
            gtk_widget_set_margin_bottom(widget[j].widget,widget[j].margin.bottom);
            gtk_widget_set_margin_start(widget[j].widget,widget[j].margin.start);
            gtk_widget_set_margin_end(widget[j].widget,widget[j].margin.end);
        }
    }


//Hours Spent: