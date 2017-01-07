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
 * ��ʼ���б����ƶ�������Ŀ�����У�������Ϊ�ı���������������1��99
 *	��ע��������Ϊ�ڲ������壬���Ҫ�Զ����������������޸ģ�
 *
 * @param list 	 [in]	GTK_TREE_VIEW����ʹ�ø���GtkWidget���ݽ���
 * @param colNum [in]	Ҫ�����б������
 *
 * @return 0	�ɹ�
 *	<0	ʧ��
 *
 */
int init_list (GtkWidget * list, int colNum);

/**
 *
 * ��ȡTreeView�ؼ�������
 *
 * @param widget [in]	GTK_TREE_VIEW����ʹ�ø���GtkWidget���ݽ���
 *
 * @return �еĸ���
 *
 */
int getColNum(GtkWidget * widget);

/**
 *
 * ����TreeView & ListStore��ָ���С�ָ���е�ֵ
 *	ע���˺���δ���ƶ���������Ч�������
 *
 * @param widget [in]	GTK_LIST_STORE����ʹ�ø���GtkWidget���ݽ���
 * @param iter	 [in]	TreeView��ͼ�µĵ�ǰ���
 * @param icol	 [in]	Ҫ�޸ĵڼ���
 * @param str	 [in]	���ƶ��С���Ҫ���õ���ֵ
 *
 * @return true	���³ɹ�
 *	 false ����ʧ��
 *
 */
bool update_to_list (GtkWidget * widget,GtkTreeIter * iter,int icol,const gchar* str);

/**
 *
 * ����µ��е�TreeView &  ListStore��
 *	ע���˺���δ����������Ч�������
 *
 * @param widget 	[in]	GTK_LIST_STORE����ʹ�ø���GtkWidget���ݽ���
 * @param colValues	[in]	���е�ֵ����˳���ŷ�
 * @param icol	 	[in]	Ҫ�޸ĵڼ���
 * @param str	 	[in]	���ƶ��С���Ҫ���õ���ֵ
 *
 * @return true	���³ɹ�
 *	 false ����ʧ��
 *
 */
bool add_to_list(GtkWidget * widget, vector<string> * colValues, int colNum);


/**
 *
 * ��ʾ/����ָ������
 *
 * @param widget [in]	GTK_WINDOW����
 *
 * @return ���ޣ�
 *
 */
void windowShow (GtkWidget * widget, gpointer data=NULL);
void windowHide (GtkWidget * widget, gpointer data=NULL);





/**
 *
 * �ڵ�����������ʾָ�����ַ���
 *
 * @param str 	 [in]	Ҫ�������ַ���
 * @return ���ޣ�
 *
 */
void debug_popbox(const gchar * str, GtkWidget * widget=NULL, GtkTreeIter* iter=NULL);

#endif

