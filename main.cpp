#include <gtk/gtk.h>
#include <string>
#include "tools.h"
#include "gtk_pubfun.h"
#include <stdlib.h>

//加载的glade布局文件的名称
#define FPATH_GLADE "img/1.glade"
#define w_(builder,type,name) name=GTK_##type(gtk_builder_get_object(builder,#name))


pGoodNode GoodHead = new GoodNode,GoodTail = new GoodNode;


/***************   主界面声明   **********************/
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
GtkEntry	* Main_file_path;



GtkTreeView *Main_treeview;


GtkWindow	*Main;

GtkWidget *liststore1;

GtkEntry	*Main_key;
/***************** 主界面声明结束 **********************/


/*****************    物流界面    **********************/
GtkEntry	* Transport_city1;
GtkEntry	* Transport_city2;
GtkEntry	* Transport_t_route;
GtkEntry	* Transport_c_route;

GtkEntry 	* Transport_time;
GtkEntry 	* Transport_cost;
GtkButton 	* Transport_search;
GtkButton 	* Transport_quit;

GtkWindow	* Transport;
/*****************    物流界面结束   **********************/


/*****************    商品信息更新   **********************/
GtkWindow	* Update;
GtkComboBox * Update_combox;
GtkEntry 	* Update_input;
GtkButton	* Update_ok;
GtkButton	* Update_cancel;
/*****************    商品信息更新结束 ********************/


/*****************   文件选择对话框    ********************/
GtkWindow 	* file_window;
GtkFileChooser 	*filechooser;
GtkButton	* file_window_ok;
GtkButton	* file_window_cancel;
/*****************   文件选择对话框结束 ********************/


void get_widgets (GtkBuilder * gb){
	w_(gb, WINDOW, Main);
	w_(gb, WINDOW, Transport);
	w_(gb, WINDOW, Update);
	w_(gb, WINDOW, file_window);
	
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
	
	w_(gb, BUTTON, Transport_search);
	w_(gb, BUTTON, Transport_quit);
	
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
	w_(gb, ENTRY, Main_file_path);
	
	w_(gb, ENTRY, Update_input);
	
	
	w_(gb, TREE_VIEW, Main_treeview);
	w_(gb, WIDGET,liststore1);
	w_(gb,COMBO_BOX,Update_combox);
	
	

	
	
	
	
	
	
	
}
void mywidget_init();



int main (int argc, char * argv[])
{
	GtkBuilder *gb;

	/*初始化gtk环境，加载glade布局文件，生成接口gb*/
	gtk_init (&argc, &argv);
	gb=gtk_load_glade ("1.glade");
	if (gb == NULL) {
		g_print("** fail load glade file:%s\n", FPATH_GLADE);
		return -1;
	}
	g_print("== load success\n");
	/*初始化自己布局变量，并完成相应初始化布局*/
	get_widgets (gb);// 从接口gb中提取需要操作的控件（如果要增减，请到该函数内部调整）
	mywidget_init ();// 显示窗口及控件 show
	
	
	
	
	
	/***************************   信号绑定回调函数 *****************************/
	//g_signal_connect(Main_search,"clicked",G_CALLBACK(on_Main_search_clicked),NULL);
	g_signal_connect(Main,"delete_event",G_CALLBACK(Main_destory),NULL);
	g_signal_connect(Main_system_init,"clicked",G_CALLBACK(on_Main_system_init_clicked),NULL);
	//g_signal_connect(Main_update,"clicked",G_CALLBACK(on_Main_update_clicked),NULL);
	g_signal_connect(Main_sort_up,"clicked",G_CALLBACK(on_Main_sort_up_clicked),NULL);
	g_signal_connect(Main_sort_down,"clicked",G_CALLBACK(on_Main_sort_down_clicked),NULL);
	//g_signal_connect(Main_down,"clicked",G_CALLBACK(on_Main_down_clicked),NULL);
	g_signal_connect(Main_transport,"clicked",G_CALLBACK(on_Main_transport_clicked),NULL);
	//g_signal_connect(Main_about,"clicked",G_CALLBACK(on_Main_about_clicked),NULL);
	
	//g_signal_connect(Main_treeview, "row_activated",G_CALLBACK(on_Main_treeview_clicked),NULL);
	g_signal_connect(Transport,"delete_event",G_CALLBACK(windowHide),NULL);
	//g_signal_connect(Transport_search,"clicked",G_CALLBACK(on_Transport_search_clicked),NULL);
	//g_signal_connect(Transport_quit,"clicked",G_CALLBACK(on_Transport_quit_clicked),NULL);
	
	
	//g_signal_connect(Update,"delete_event",G_CALLBACK(windowHide),NULL);
	//g_signal_connect(Update_ok,"clicked",G_CALLBACK(on_Update_ok_clicked),NULL);
	//g_signal_connect(Update_cancel,"clicked",G_CALLBACK(on_Update_cancel_clicked),NULL);
	
	
	g_signal_connect(file_window,"delete_event",G_CALLBACK(windowHide),NULL);
	g_signal_connect(file_window_ok,"clicked",G_CALLBACK(on_file_window_ok_clicked),NULL);
	g_signal_connect(file_window_cancel,"clicked",G_CALLBACK(on_file_window_cancel_clicked),NULL);
	gtk_main ();//守护程序，保证显示的窗口不退出
	
	return 0;
}
	
void mywidget_init()
{
	if (Main==NULL){
		g_print("** unknown main-window\n");
		exit(0);
	}
	init_list(GTK_WIDGET(Main_treeview), LIST_COLNUM);

	gtk_widget_show_all (GTK_WIDGET(Main));
}
	
	






