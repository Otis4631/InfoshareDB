#include <string.h>
#include "tools.h"
#include "gtk_pubfun.h"
#include <boost/algorithm/string/classification.hpp>  
#include <boost/algorithm/string/split.hpp>  
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
void BKDHash(string Aim, int &u, int &v){ // 字符串哈希
	int HH1 = 0, HH2 = 0, seed1 = 137, seed2 = 131;
	for(int i = 0; Aim[i]; i ++){
		HH1 = HH1*seed1 + Aim[i];
		HH2 = HH2*seed2 + Aim[i];
	}
	u = HH1 & 0x7fffffff;
	v = HH2 & 0x7fffffff;
}

 extern pGoodNode GoodHead,GoodTail;



//--------------------------------声明所有货物头尾指针链表-------------------------------


//-----------------------------------------------------------------------------------------

//-----------------------------------------------*********************排序***************  -----------------------------------------------
bool Cmp(pGoodNode u, pGoodNode v){ // 判断
	return u->price < v->price;
}

void Swap(pGoodNode &u, pGoodNode &v){ // 交换
	swap(*u, *v);
	swap(u->Next, v->Next);
	swap(u->Ahead, v->Ahead);
}


void Quick_Sort(pGoodNode Begin, pGoodNode End){ // 快排
	if(Begin == End){
		return;
	}
	pGoodNode i = Begin, j = Begin->Next;
	while(j != End){
		if(Cmp(j, Begin)){
			i = i->Next;
			Swap(i, j);
		}
		j = j->Next;
	}
	Swap(Begin, i);
	Quick_Sort(Begin, i);
	Quick_Sort(i->Next, End);
}

//----------------------------------------------排序结束--------------------------------------------------------

void init_struct_node (Node *node,vector<string> * ary) {
		node->name = ary->at(0);
		BKDHash(node->name,node->Hasharr[1], node->Hasharr[2]);

		node->city=ary->at(1);
		BKDHash(node->city,node->Hasharr[3], node->Hasharr[4]);

		node->count=atoi(ary->at(2).c_str());
		BKDHash(ary->at(2),node->Hasharr[5], node->Hasharr[6]);

		node->price = atoi(ary->at(3).c_str());
		BKDHash(ary->at(3),node->Hasharr[7], node->Hasharr[8]);

		node->logo=ary->at(4);
		BKDHash(node->logo,node->Hasharr[9], node->Hasharr[10]);

		node->material=ary->at(5);
		BKDHash(node->material,node->Hasharr[11], node->Hasharr[12]);

		node->style=ary->at(6);
		BKDHash(node->style,node->Hasharr[13], node->Hasharr[14]);

		node->color=ary->at(7);
		BKDHash(node->color,node->Hasharr[15], node->Hasharr[16]);

		node->function=ary->at(8);
		BKDHash(node->function,node->Hasharr[17], node->Hasharr[18]);

}
typedef struct Hash{
	pGoodNode To;
	struct Hash *Next;
} Hash;
Hash HashChart[55][60][60];

/*--------------------------------Main_system_init--------------------------*/
void on_Main_system_init_clicked(GtkWidget * button,gpointer userdata){
	gtk_widget_show(GTK_WIDGET(file_window));
}
void on_file_window_ok_clicked(GtkWidget *button,gpointer userdata){
	const gchar* filepath=NULL;// 提供初始化数据的文件路径
	filepath=gtk_file_chooser_get_filename(filechooser);
	if (filepath==NULL||strlen(filepath)<5) 
	{
		debug_popbox ("*** 请先选择文件名称");
	}
	else {
		vector<string> ary;
		
		GoodHead->Next = NULL;
		//GoodTail = GoodHead;
		pGoodNode p;
		
		FILE *fp=fopen(filepath,"r");

		char str[2000];
		while(fscanf(fp,"%s",str)!=EOF)
		{
			ary.clear();			
			ary.push_back (str);
			boost::split( ary, str, boost::is_any_of( ";" ), boost::token_compress_on );  
			GoodNode onenode;
			init_struct_node(&onenode,&ary);
			//---------------------------顺序建立链表，AllGoodHead 为头节点，AllGoodTail 为未节点。
			p = new Node; 			
			(*p) = onenode;
			p->Ahead = GoodTail;
			p->Next = GoodHead->Next;
			GoodHead->Next = p;
			//-------------------------------------------------------------------------------------
			
			add_to_list (liststore1, &ary,LIST_COLNUM );
		}	
	}
	
	gtk_widget_hide(GTK_WIDGET(file_window));
}





void on_file_window_cancel_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_hide(GTK_WIDGET(file_window));
}
void on_Main_search_clicked(GtkWidget * button,gpointer userdata){}
void on_Main_update_clicked(GtkWidget * button,gpointer userdata){
	gtk_widget_show(GTK_WIDGET(Update));
}
void on_Main_up_clicked(GtkWidget *button,gpointer userdata){
	
}
void on_Main_sort_up_clicked(GtkWidget *button,gpointer userdata){
	GtkListStore * liststore;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_clear(liststore);
	Quick_Sort(GoodHead->Next,NULL);

	GtkTreeIter iter;
	pGoodNode p ;
	p = GoodHead->Next;


	while(p != NULL){
		
		g_print("1 %s\n",(p->name).c_str());
		//printf("%s\n",GoodHead->Next->name);
		gtk_list_store_append(liststore, &iter);
		g_print("2 %s\n",(p->name).c_str());
		
		gtk_list_store_set (liststore, &iter, 0, (p->name).c_str(), NULL);

		gtk_list_store_set (liststore, &iter, 1, (p->city).c_str(), NULL);
g_print("%s\n",(p->city).c_str());
		gtk_list_store_set (liststore, &iter, 2, (p->city).c_str(), NULL);
		gtk_list_store_set (liststore, &iter, 3, (p->city).c_str(), NULL);
		gtk_list_store_set (liststore, &iter, 4, (p->logo).c_str(), NULL);
g_print("%s\n",(p->logo).c_str());
		gtk_list_store_set (liststore, &iter, 5, (p->material).c_str(), NULL);
		gtk_list_store_set (liststore, &iter, 6, (p->style).c_str(), NULL);
		gtk_list_store_set (liststore, &iter, 7, (p->color).c_str(), NULL);
		gtk_list_store_set (liststore, &iter, 8, (p->function).c_str(), NULL);
		
		p = p->Next;
	}
}

void on_Main_transport_clicked(GtkWidget *button,gpointer userdata){
	windowShow(GTK_WIDGET(Transport));
}




























