#ifndef TOOLS_H
#define TOOLS_H
//列表的列数，TODO：需根据你自己的数据列数目调整
#define LIST_COLNUM 9
#define RMAX 10000000
#include <gtk/gtk.h>
#include <string>
#include <stdlib.h>

using namespace std;

/***************   主界面声明   **********************/
extern GtkButton 	* Main_about;
extern GtkButton 	* Main_search;
extern GtkButton 	* Main_up;
extern GtkButton 	* Main_down;
extern GtkButton 	* Main_system_init;
extern GtkButton 	* Main_update;
extern GtkButton 	* Main_sort_up;
extern GtkButton 	* Main_sort_down;
extern GtkButton 	* Main_transport;
extern GtkEntry		* Main_filepath;


extern GtkTreeView *Main_treeview;


extern GtkWindow	*Main;

extern GtkWidget *liststore1;

extern GtkEntry	*Main_key;

/***************** 主界面声明结束 **********************/


/*****************    物流界面    **********************/
extern GtkEntry	* Transport_city1;
extern GtkEntry	* Transport_city2;
extern GtkEntry	* Transport_t_route;
extern GtkEntry	* Transport_c_route;

extern GtkEntry 	* Transport_time;
extern GtkEntry 	* Transport_cost;
extern GtkButton 	* Transport_search;
extern GtkButton 	* Transport_quit;

extern GtkWindow	* Transport;
/*****************    物流界面结束   **********************/


/*****************    商品信息更新   **********************/
extern GtkWindow	* Update;
extern GtkComboBox * Update_combox;
extern GtkEntry 	* Update_input;
extern GtkButton	* Update_ok;
extern GtkButton	* Update_cancel;
/*****************    商品信息更新结束 ********************/


/*****************   文件选择对话框    ********************/
extern GtkWindow 	* file_window;
extern GtkFileChooser 	*filechooser;
extern GtkButton	* file_window_ok;
extern GtkButton	* file_window_cancel;
/*****************   文件选择对话框结束 ********************/


typedef struct Node {
	
	int Hasharr[20];
	struct Node *Ahead,*Next;
	string name;
	string city;
	int  count; //库存
	int  price; 
	string logo; //品牌
	string material; // 材质
	string style; //款式
	string color;
	string function;//功能特点

}GoodNode, *pGoodNode;



void on_Main_system_init_clicked(GtkWidget * button,gpointer userdata);
void on_file_window_ok_clicked(GtkWidget *button,gpointer userdata);
void on_file_window_cancel_clicked(GtkWidget *button,gpointer userdata);
void on_Main_search_clicked(GtkWidget * button,gpointer userdata);
void on_Main_update_clicked(GtkWidget * button,gpointer userdata);
void on_Main_sort_up_clicked(GtkWidget * button,gpointer userdata);
void on_Main_transport_clicked(GtkWidget *button,gpointer userdata);

























#endif
