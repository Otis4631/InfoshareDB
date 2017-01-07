#include "gtk_pubfun.h"
#include <string.h>

GtkBuilder * gtk_load_glade (gchar * filename)
{
	GtkBuilder *gb;
	
	// 新建对象
	gb=gtk_builder_new ();

	// 载入文件
	if (!gtk_builder_add_from_file (gb, filename,NULL))
		return NULL;

	// 连接文件中包含的所有信号
	gtk_builder_connect_signals(gb, NULL);

	return gb;
}

int init_list (GtkWidget * list, int colNum) {
	GtkCellRenderer *rend=NULL;
	GtkTreeViewColumn *col=NULL;
	int i=0;
	char colName[BUFSIZE_1K]={0};	//列名称

	if (colNum<1||colNum>99)//合法性检查，列数在1～99
		return -1;
	rend=gtk_cell_renderer_text_new();
	string ColName[] = {
		"商品名称",
		"卖家地点",
		"存货",
		"价钱",
		"品牌",
		"材质",
		"形状",
		"颜色",
		"功能关键字"
	};
	//循环添加列，按内部规则指定列名称
	for (i=0; i < colNum; i++) {
		strcpy(colName,ColName[i].c_str());
		col=gtk_tree_view_column_new_with_attributes (colName, rend, "text", i, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(list), col);
	}

	return 0;
}
int getColNum(GtkWidget * widget) {
	GtkTreeModel * model;
	int columns=0;//TreeView的列数

	model=gtk_tree_view_get_model(GTK_TREE_VIEW(widget));//得到TREEVIEW的model
	columns=gtk_tree_model_get_n_columns(model);//获取列数

	return columns;
}

bool update_to_list (GtkWidget * widget, GtkTreeIter * iter, 
	int icol, const gchar* str) 
{
	if (icol<1 || str==NULL) {
		return false;
	}
	gtk_list_store_set (GTK_LIST_STORE(widget), iter, icol, str, -1);

	return true;
}

bool add_to_list(GtkWidget * list, vector<string> * colValues, int colNum) {
	GtkListStore * store;
	GtkTreeIter iter;
	int i=0;

	store=GTK_LIST_STORE(list);
	gtk_list_store_append(store, &iter);
	for (i=0; i < colNum && i<colValues->size(); i++) {
		gtk_list_store_set (store, &iter, i, colValues->at(i).c_str(), -1);
	}

	return true;
}

//弹出对话框，显示指定文本
void debug_popbox(const gchar * str, GtkWidget * widget, GtkTreeIter* iter)
{
	GtkWidget * dialog;	//对话框

	dialog = gtk_message_dialog_new(NULL,
		GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK,
		str,
		NULL);
	gtk_dialog_run(GTK_DIALOG(dialog));	//显示dialog对话框并等待按钮,在有按钮按下之后继续

	// tmp： 演示示例用，将当前活动行到第2列值改为AAAA
	/*if (widget!=NULL && iter!=NULL) {
		GtkListStore * store=GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(widget)));
		update_to_list (GTK_WIDGET(store), iter, 1, "AAAA");
	}*/

	gtk_widget_destroy(dialog);			//销毁dialog对话框
}

void windowShow (GtkWidget * widget, gpointer data) {
	gtk_widget_show_all (widget);
}

void windowHide (GtkWidget * widget, gpointer data) {
	gtk_widget_hide (widget);
}

