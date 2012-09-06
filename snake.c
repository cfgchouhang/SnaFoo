#include"snake.h"

int main(int argc,char *argv[])
{
    GtkWidget *window;
    GtkWidget *fixed,*box;
    GtkWidget *sbtn,*pbtn,*ebtn;
    Plate plate;
    
    gtk_init(&argc,&argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(window,WIDTH,HEIGHT);
    gtk_window_set_title(GTK_WINDOW(window),"Snake by CFG");
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    
    fixed = gtk_fixed_new();
    //hbox = gtk_hbox_new(TRUE,15);
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,15);
    sbtn = gtk_button_new_with_label("New");
    pbtn = gtk_toggle_button_new_with_label("Pause");
    ebtn = gtk_button_new_with_label("End");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pbtn),FALSE);
    plate.label = gtk_label_new("0");
    gtk_label_set_markup(GTK_LABEL(plate.label),"<span font_desc=\"12\"\
                         foreground=\"black\">Score : 0</span>");
    
    gtk_box_pack_start(GTK_BOX(box),sbtn,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),pbtn,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(box),ebtn,TRUE,FALSE,20);
    gtk_box_pack_start(GTK_BOX(box),plate.label,TRUE,FALSE,5);
    gtk_fixed_put(GTK_FIXED(fixed),box,0,0);
    init_plate(&plate,fixed,WIDTH,HEIGHT);
    
    //g_signal_connect(G_OBJECT(plate.dr),"draw",
    //               G_CALLBACK(expose),&plate);
    g_signal_connect(window,"destroy",
                     G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(G_OBJECT(window),"key-press-event",
                     G_CALLBACK(key_press),&plate);

    g_signal_connect(sbtn,"clicked",
                     G_CALLBACK(new_game),&plate);
    g_signal_connect(ebtn,"clicked",
                     G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(pbtn,"clicked",
                     G_CALLBACK(pause_game),&plate);

    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_widget_show_all(window);
    plate.timeoutid = 
        g_timeout_add(plate.interval,(GSourceFunc)automove,&plate);
    printf("%d\n",plate.interval);
    gtk_main();

    return 0;
}
