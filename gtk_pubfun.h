#ifndef GTK_PUBFUN_H
#define GTK_PUBFUN_H

#include <gtk/gtk.h>
#include <vector>
#include <string>

using namespace std;

#define BUFSIZE_1K 1024
GtkBuilder * gtk_load_glade (gchar * filename);



/**
 *
 * 初始化列表，按制定到列数目构造列，列类型为文本，列数量限制在1～99
 *	（注：列名称为内部规则定义，如果要自定义列名称请自行修改）
 *
 * @param list 	 [in]	GTK_TREE_VIEW对象，使用父类GtkWidget传递进来
 * @param colNum [in]	要构建列表的列数
 *
 * @return 0	成功
 *	<0	失败
 *
 */
int init_list (GtkWidget * list, int colNum);

/**
 *
 * 获取TreeView控件的列数
 *
 * @param widget [in]	GTK_TREE_VIEW对象，使用父类GtkWidget传递进来
 *
 * @return 列的个数
 *
 */
int getColNum(GtkWidget * widget);

/**
 *
 * 设置TreeView & ListStore中指定行、指定列的值
 *	注：此函数未对制定列数的有效性做检查
 *
 * @param widget [in]	GTK_LIST_STORE对象，使用父类GtkWidget传递进来
 * @param iter	 [in]	TreeView试图下的当前活动行
 * @param icol	 [in]	要修改第几列
 * @param str	 [in]	给制定行、列要设置的新值
 *
 * @return true	更新成功
 *	 false 更新失败
 *
 */
bool update_to_list (GtkWidget * widget,GtkTreeIter * iter,int icol,const gchar* str);

/**
 *
 * 添加新的行到TreeView &  ListStore中
 *	注：此函数未对列数的有效性做检查
 *
 * @param widget 	[in]	GTK_LIST_STORE对象，使用父类GtkWidget传递进来
 * @param colValues	[in]	各列的值，按顺序排放
 * @param icol	 	[in]	要修改第几列
 * @param str	 	[in]	给制定行、列要设置的新值
 *
 * @return true	更新成功
 *	 false 更新失败
 *
 */
bool add_to_list(GtkWidget * widget, vector<string> * colValues, int colNum);


/**
 *
 * 显示/隐藏指定窗口
 *
 * @param widget [in]	GTK_WINDOW对象
 *
 * @return （无）
 *
 */
void windowShow (GtkWidget * widget, gpointer data=NULL);
void windowHide (GtkWidget * widget, gpointer data=NULL);





/**
 *
 * 在弹出窗口上显示指定的字符串
 *
 * @param str 	 [in]	要弹出的字符串
 * @return （无）
 *
 */
void debug_popbox(const gchar * str, GtkWidget * widget=NULL, GtkTreeIter* iter=NULL);

#endif

