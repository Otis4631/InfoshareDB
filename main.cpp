#include <gtk/gtk.h>
#include <string>
#include "h/tools.h"
#include "h/gtk_pubfun.h"
#include <stdlib.h>

//���ص�glade�����ļ�������
#define FPATH_GLADE "./img/1.glade"
#define w_(builder,type,name) name=GTK_##type(gtk_builder_get_object(builder,#name))

pGoodNode GoodHead = new GoodNode,GoodTail = new GoodNode; //�����ڲ�����ͷβ�ڵ㡣
pGoodNode P;
bool Sequence;
/***************   ����������   **********************/
GtkButton 	* Main_about;
GtkButton 	* Main_search;
GtkButton 	* Main_up;
GtkButton 	* Main_down;
GtkButton 	* Main_system_init;
GtkButton 	* Main_update;
GtkButton 	* Main_sort_up;
GtkButton 	* Main_sort_down;
GtkButton 	* Main_transport;
GtkButton	* Main_quit;
GtkButton 	* Main_pgup;
GtkButton 	* Main_pgdown;


GtkEntry	*Main_key;

GtkTreeView *Main_treeview;

GtkWindow	*Main;

GtkWidget *liststore1;
GtkWidget *liststore2;
/***************** �������������� **********************/


/*****************    ��������    **********************/
GtkEntry	* Transport_city1;
GtkEntry	* Transport_city2;
GtkEntry	* Transport_t_route;
GtkEntry	* Transport_c_route;
GtkEntry 	* Transport_time;
GtkEntry 	* Transport_cost;

GtkButton 	* Transport_search;
GtkButton 	* Transport_cancel;

GtkWindow	* Transport;
/*****************    �����������   **********************/


/*****************    ��Ʒ��Ϣ����   **********************/
GtkWindow	* Update;
GtkComboBox * Update_combox;
GtkEntry 	* Update_input;
GtkButton	* Update_ok;
GtkButton	* Update_cancel;
/*****************    ��Ʒ��Ϣ���½��� ********************/


/*****************   �ļ�ѡ��Ի���    ********************/
GtkWindow 	* file_window;
GtkFileChooser 	*filechooser;
GtkButton	* file_window_ok;
GtkButton	* file_window_cancel;
/*****************   �ļ�ѡ��Ի������ ********************/
GtkWindow	* About;
GtkButton 	* About_ok;

GtkWindow	* Welcome;
GtkButton	* Welcome_ok;



void get_widgets (GtkBuilder * gb){
	w_(gb, WINDOW, Main);
	w_(gb, WINDOW, Transport);
	w_(gb, WINDOW, Update);
	w_(gb, WINDOW, file_window);
	w_(gb, WINDOW, About);
	w_(gb, WINDOW, Welcome);

	w_(gb, BUTTON, Main_about);
	w_(gb, BUTTON, Main_search);
	w_(gb, BUTTON, Main_up);
	w_(gb, BUTTON, Main_down);
	w_(gb, BUTTON, Main_system_init);
	w_(gb, BUTTON, Main_update);
	w_(gb, BUTTON, Main_sort_up);
	w_(gb, BUTTON, Main_sort_down);
	w_(gb, BUTTON, Main_transport);
	w_(gb, BUTTON, Main_quit);
	w_(gb, BUTTON, Main_pgup);
	w_(gb, BUTTON, Main_pgdown);
	
	w_(gb, BUTTON, Transport_search);
	w_(gb, BUTTON, Transport_cancel);
	
	w_(gb, BUTTON, Update_cancel);
	w_(gb, BUTTON, Update_ok);
	
	w_(gb, BUTTON, file_window_ok);
	w_(gb, BUTTON, file_window_cancel);
	w_(gb,FILE_CHOOSER,filechooser);
	
	w_(gb, ENTRY, Main_key);
	
	w_(gb, ENTRY, Transport_city1);
	w_(gb, ENTRY, Transport_city2);
	w_(gb, ENTRY, Transport_time);
	w_(gb, ENTRY, Transport_c_route);
	w_(gb, ENTRY, Transport_cost);
	w_(gb, ENTRY, Transport_t_route);
	
	w_(gb, ENTRY, Update_input);
	
	
	w_(gb, TREE_VIEW, Main_treeview);
	w_(gb, WIDGET,liststore1);
	w_(gb, WIDGET,liststore2);
	w_(gb,COMBO_BOX,Update_combox);
	
	w_(gb, BUTTON, About_ok);
	w_(gb, BUTTON, Welcome_ok);
}
void on_Welcome_ok_clicked(GtkWidget *button,gpointer userdata){
  gtk_widget_show_all (GTK_WIDGET(Main));
  gtk_widget_hide(GTK_WIDGET(Welcome));
}
void mywidget_init();
int main (int argc, char * argv[])
{
	GtkBuilder *gb;

	/*��ʼ��gtk����������glade�����ļ������ɽӿ�gb*/
	gtk_init (&argc, &argv);
	gb=gtk_load_glade (FPATH_GLADE);
	if (gb == NULL) {
		g_print("** fail load glade file:%s\n", FPATH_GLADE);
		return -1;
	}
	g_print("== load success\n");
	/*��ʼ���Լ����ֱ������������Ӧ��ʼ������*/
	get_widgets (gb);// �ӽӿ�gb����ȡ��Ҫ�����Ŀؼ������Ҫ�������뵽�ú����ڲ�������
	mywidget_init ();// ��ʾ���ڼ��ؼ� show
	/***************************   �źŰ󶨻ص����� *****************************/
	g_signal_connect(Main_search,"clicked",G_CALLBACK(on_Main_search_clicked),NULL);
	g_signal_connect(Main,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(Update,"delete_event",GTK_SIGNAL_FUNC(gtk_widget_hide),GTK_WIDGET(Update));
	g_signal_connect(Transport,"delete_event",GTK_SIGNAL_FUNC(gtk_widget_hide),GTK_WIDGET(Transport));
	g_signal_connect(file_window,"delete_event",GTK_SIGNAL_FUNC(gtk_widget_hide),GTK_WIDGET(file_window));
	g_signal_connect(About,"delete_event",GTK_SIGNAL_FUNC(gtk_widget_hide),GTK_WIDGET(About));
	g_signal_connect(Welcome,"delete_event",GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
	
	g_signal_connect(Main_quit,"clicked",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(Main_system_init,"clicked",G_CALLBACK(on_Main_system_init_clicked),NULL);
	g_signal_connect(Main_update,"clicked",G_CALLBACK(on_Main_update_clicked),NULL);
	g_signal_connect(Main_sort_up,"clicked",G_CALLBACK(on_Main_sort_up_clicked),NULL);
	g_signal_connect(Main_sort_down,"clicked",G_CALLBACK(on_Main_sort_down_clicked),NULL);
	g_signal_connect(Main_down,"clicked",G_CALLBACK(on_Main_down_clicked),NULL);
	g_signal_connect(Main_up,"clicked",G_CALLBACK(on_Main_up_clicked),NULL);
	g_signal_connect(Main_transport,"clicked",G_CALLBACK(on_Main_transport_clicked),NULL);
	g_signal_connect(Main_about,"clicked",G_CALLBACK(on_Main_about_clicked),NULL);
	g_signal_connect(Main_pgup,"clicked",G_CALLBACK(on_Main_pgup_clicked),NULL);
	g_signal_connect(Main_pgdown,"clicked",G_CALLBACK(on_Main_pgdown_clicked),NULL);

	g_signal_connect(Main_treeview, "row_activated",G_CALLBACK(on_Main_treeview_clicked),NULL);
	
	g_signal_connect(Transport_search,"clicked",G_CALLBACK(on_Transport_search_clicked),NULL);
	g_signal_connect(Transport_cancel,"clicked",G_CALLBACK(on_Transport_cancel_clicked),NULL);
	
	g_signal_connect(Update_ok,"clicked",G_CALLBACK(on_Update_ok_clicked),NULL);
	g_signal_connect(Update_cancel,"clicked",G_CALLBACK(on_Update_cancel_clicked),NULL);
	g_signal_connect(About_ok,"clicked",G_CALLBACK(on_About_ok_clicked),NULL);

	g_signal_connect(Welcome_ok,"clicked",G_CALLBACK(on_Welcome_ok_clicked),NULL);
	g_signal_connect(file_window_ok,"clicked",G_CALLBACK(on_file_window_ok_clicked),NULL);
	g_signal_connect(file_window_cancel,"clicked",G_CALLBACK(on_file_window_cancel_clicked),NULL);
	gtk_main ();//�ػ����򣬱�֤��ʾ�Ĵ��ڲ��˳�
	
	return 0;
}
	
void mywidget_init()
{
	if (Welcome == NULL){
		g_print("** unknown main-window\n");
		exit(0);
	}
	init_list(GTK_WIDGET(Main_treeview), LIST_COLNUM);
	GoodHead->Next = GoodTail;
	GoodTail->Next = GoodHead->Ahead = NULL;
	GoodTail->Ahead = GoodHead;
	
	P = GoodHead;
	Sequence = true;
	gtk_widget_show_all (GTK_WIDGET(Welcome));
}
