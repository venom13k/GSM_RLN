#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GtkWidget *zveno_add;
GtkWidget *vbox;
int n;

static gboolean delete_event( GtkWidget *widget,
			      GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}


static GtkWidget *make_zveno(int n2);

static void callback( GtkWidget *widget,
                      gpointer   data )
{

	GtkWidget *zv;
	printf ("SIGNAL\n");

	zv = make_zveno(n);
	gtk_box_pack_start (GTK_BOX (vbox), zv, FALSE, FALSE,0);
	gtk_widget_show_all( vbox );
}



static GtkWidget *make_zveno(int n2)
{
	GtkWidget *vbox2;
	GtkWidget *vbox4;
	GtkWidget *vbox0;
	GtkWidget *hbox;
	GtkWidget *hbox1;
	GtkWidget *hbox2;
	GtkWidget *entry;
	GtkWidget *combo;
	GtkWidget *aspectframe;
	GtkWidget *label;

	gchar str[255];

	sprintf(str, "Звено %d", n2);

	aspectframe = gtk_aspect_frame_new (str, 0 , 0, 0, TRUE);

	vbox0 = gtk_vbox_new (FALSE, 0);

	gtk_container_set_border_width (GTK_CONTAINER (vbox0), 3);
	gtk_container_add (GTK_CONTAINER (aspectframe), vbox0);

	hbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox0), hbox, FALSE, FALSE, 0);

	vbox2 = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (hbox), vbox2);



	label = gtk_label_new ("Тип звена: ");
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_box_pack_start (GTK_BOX (vbox2), label, FALSE, FALSE, 0);


	combo = gtk_combo_new();

        GList *glist = NULL;

        glist = g_list_append (glist, "Динамическое");
        glist = g_list_append (glist, "Усилительное");
        glist = g_list_append (glist, "Сумматор"); 
        glist = g_list_append (glist, "Возмущение");

        gtk_combo_set_popdown_strings (GTK_COMBO (combo), glist);
    
    /* can free glist now, combo takes a copy */

        gtk_box_pack_start (GTK_BOX (vbox2), combo, TRUE, FALSE, 0);


	vbox4 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX (hbox), vbox4, TRUE, TRUE, 5);

	hbox1 = gtk_hbox_new (TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox4), hbox1, TRUE, TRUE, 5);


	label = gtk_label_new ("Коэф-ты числителя :");
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_box_pack_start (GTK_BOX (hbox1), label, FALSE, TRUE, 0);


	entry = gtk_entry_new ();
	gtk_editable_select_region (GTK_EDITABLE (entry),
			        0, GTK_ENTRY (entry)->text_length);

	gtk_box_pack_end (GTK_BOX (hbox1), entry, TRUE, TRUE, 0);

	hbox2 = gtk_hbox_new (TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox4), hbox2, TRUE, TRUE, 5);



	label = gtk_label_new ("Коэф-ты знаменателя :");
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_box_pack_start (GTK_BOX (hbox2), label, FALSE, TRUE, 0);


	entry = gtk_entry_new ();
	gtk_editable_select_region (GTK_EDITABLE (entry),
			        0, GTK_ENTRY (entry)->text_length);

	gtk_box_pack_end (GTK_BOX (hbox2), entry, TRUE, TRUE, 0);
	n++;

	return aspectframe;
}





int main( int   argc,
          char *argv[] )
{

	GtkWidget *main_vbox;
	GtkWidget *window;
	GtkWidget *zveno;
	GtkWidget *frame;
	GtkWidget *scrolled;
	GtkWidget *hbox;

	gint width = 800;
	gint height = 400;

	n   = 0;
	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "GUI_RLN");
	gtk_window_set_default_size (GTK_WINDOW (window), width, height);
	g_signal_connect (window, "delete-event",
		    G_CALLBACK (delete_event), NULL);

	main_vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), main_vbox);

	hbox = gtk_hbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX (main_vbox), hbox, FALSE, FALSE, 0);


	zveno_add = gtk_button_new_with_label("Добавить звено");

	g_signal_connect (GTK_OBJECT(zveno_add), "clicked",
			      G_CALLBACK (callback), NULL);

        gtk_box_pack_start (GTK_BOX (hbox), zveno_add, FALSE, FALSE, 0);



	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(
		GTK_SCROLLED_WINDOW(scrolled),
		GTK_POLICY_AUTOMATIC,
		GTK_POLICY_AUTOMATIC);



	gtk_container_add (GTK_CONTAINER (main_vbox), scrolled);

	vbox = gtk_vbox_new (FALSE, 0);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled),vbox);

	n++;
	zveno = make_zveno(n);
	gtk_box_pack_start (GTK_BOX (vbox), zveno, FALSE, FALSE,0);





	gtk_widget_show_all  (window);

	gtk_main ();
    
return 0;
}
