#include <string.h>
#include "tools.h"
#include "gtk_pubfun.h"
#include <boost/algorithm/string/classification.hpp>  
#include <boost/algorithm/string/split.hpp>  
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
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
	if(u == v) return;
	if(u->Next == v){
		u->Next = v->Next;
		v->Ahead = u->Ahead;
		u->Ahead = v;
		v->Next = u;
		u->Next->Ahead = u;
		v->Ahead->Next = v;
	}
	else{
		pGoodNode Th = u->Next, Tt = v->Ahead;
		u->Next = v->Next;
		v->Ahead = u->Ahead;
		v->Ahead->Next = v;
		u->Next->Ahead = u;
		v->Next = Th;
		u->Ahead = Tt;
		Th->Ahead = v;
		Tt->Next = u;
	}
	swap(u, v);
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


typedef struct Haha{
	pGoodNode To;
	struct Haha *Next;
} Hash;
Hash *HashChart[55][60][60];

//----------------------------------------------建立哈希表------------------------------------------------------

void HashNode(pGoodNode Tmp){ // 顺延建立哈希
	string Aim = Tmp->name;
	int p1 = 0, p2 = 0, p3 = 0;
	for(int i = 0; Aim[i] = '\0'; i ++){
		if(i%3 == 0) p1 += Aim[i];
		else if(i%3 == 1) p2 += Aim[i];
		else p3 += Aim[i];
	}
	p1 = (p1%53 + 53)%53;
	p2 = (p2%57 + 57)%57;
	p3 = (p3%59 + 59)%59;
	Hash * TTmp = new Hash;
	TTmp->To = Tmp;
	TTmp->Next = HashChart[p1][p2][p3];
	HashChart[p1][p2][p3] = TTmp;
}
/*
pGoodNode HashFind(pGoodNode Tmp){ // 查找
	string Aim = Tmp->name;
	int p1 = 0, p2 = 0, p3 = 0;
	for(int i = 0; Aim[i] != '\0'; i ++){
		if(i%3 == 0) p1 += Aim[i];
		else if(i%3 == 1) p2 += Aim[i];
		else p3 += Aim[i];
	}
	p1 = (p1%53 + 53)%53;
	p2 = (p2%57 + 57)%57;
	p3 = (p3%59 + 59)%59;
	Hash *TT = HashChart[p1][p2][p3];
	if(TT != NULL){
		while(TT != NULL){
			if(Aim == TT->To->name){
				break;
			}
			TT = TT->Next;
		}
	}
	return TT;
}*/

void Free_Hash(){ // 释放哈希
	Hash *p1, *p2;
	for(int i = 0; i < 53; i ++){
		for(int j = 0; j < 57; j ++){
			for(int k = 0; k < 59; k ++){
				if(HashChart[i][j][k] == NULL) continue;
				p1 = HashChart[i][j][k];
				HashChart[i][j][k] = NULL;
				while(p1 != NULL){
					p2 = p1->Next;
					delete p1;
					p1 = p2;
				}
			}
		}
	}
}

void Free_Node(pGoodNode Begin, pGoodNode End){ // 释放内存
	pGoodNode Tmp;
	while(Begin->Next != End){
		Tmp = Begin->Next;
		Begin->Next = Tmp->Next;
		delete Tmp;
	}
	End->Ahead = Begin;
}


//----------------------------------------------查找------------------------------------------------------------

bool Judge(pGoodNode Temp, int *w, int sum){
	if(!sum) return true;
	int record = 1;
	for(int i = 1; i <= 9; i ++){
		if(*(w + record*2+1) == Temp->Hasharr[i*2-1] && *(w + record*2+2) == Temp->Hasharr[i*2]) record ++;
		if(record == sum) break;
	}
	return record == sum;
}




















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
		gtk_list_store_clear(GTK_LIST_STORE(liststore1));
		vector<string> ary;
		Free_Hash();
		Free_Node(GoodHead, GoodTail);
		GoodHead->count = 0;
		//GoodTail = GoodHead;
		pGoodNode p;
		
		FILE *fp=fopen(filepath,"r");

		char str[500];
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
			p->Ahead = GoodHead;
			p->Next = GoodHead->Next;
			p->Next->Ahead = p;
			GoodHead->Next = p;
			//-------------------------------------------------------------------------------------
			
			HashNode(p);
			add_to_list (liststore1, &ary,LIST_COLNUM );
		}	
	}
	
	gtk_widget_hide(GTK_WIDGET(file_window));
}
void on_file_window_cancel_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_hide(GTK_WIDGET(file_window));
}

void on_Main_update_clicked(GtkWidget * button,gpointer userdata){
	gtk_widget_show(GTK_WIDGET(Update));
}
void on_Main_up_clicked(GtkWidget *button,gpointer userdata){
	
}
void on_Main_sort_up_clicked(GtkWidget *button,gpointer userdata){
	GtkListStore * liststore;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_clear(liststore);
	if(GoodHead->count == 0){
		Quick_Sort(GoodHead->Next,GoodTail);
		GoodHead->count = 1;
	}

	GtkTreeIter iter;
	pGoodNode p ;
	p = GoodHead->Next;


	while(p != GoodTail){
		
		char  price[20];
		char  count[20];
		sprintf(count,"%d",p->count);
		sprintf(price,"%d",p->price);

		gtk_list_store_append(liststore, &iter);
		
		gtk_list_store_set (liststore, &iter, 0, (p->name).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 1, (p->city).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 2, (count), -1);
		gtk_list_store_set (liststore, &iter, 3, (price), -1);
		gtk_list_store_set (liststore, &iter, 4, (p->logo).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 5, (p->material).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 6, (p->style).c_str(),-1);
		gtk_list_store_set (liststore, &iter, 7, (p->color).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 8, (p->function).c_str(), -1);
		
		p = p->Next;
	}
}

void on_Main_transport_clicked(GtkWidget *button,gpointer userdata){
	windowShow(GTK_WIDGET(Transport));
}
void on_Main_sort_down_clicked(GtkWidget *button,gpointer userdata){
	GtkListStore * liststore;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_clear(liststore);
	if(GoodHead->count == 0){
		Quick_Sort(GoodHead->Next,GoodTail);
		GoodHead->count = 1;
	}

	GtkTreeIter iter;
	pGoodNode p ;
	p = GoodTail->Ahead;


	while(p != GoodHead){
		
		char  price[20];
		char  count[20];
		sprintf(count,"%d",p->count);
		sprintf(price,"%d",p->price);

		gtk_list_store_append(liststore, &iter);
		
		gtk_list_store_set (liststore, &iter, 0, (p->name).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 1, (p->city).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 2, (count), -1);
		gtk_list_store_set (liststore, &iter, 3, (price), -1);
		gtk_list_store_set (liststore, &iter, 4, (p->logo).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 5, (p->material).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 6, (p->style).c_str(),-1);
		gtk_list_store_set (liststore, &iter, 7, (p->color).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 8, (p->function).c_str(), -1);
		
		p = p->Ahead;
	}
}

void on_Main_search_clicked(GtkWidget *button,gpointer userdata){
	int KEY[20];
	char Get_Str[300];
	strcpy(Get_Str, gtk_entry_get_text(GTK_ENTRY(Main_key)));
	string keke;
	int num = 0, last = 0, pos;
	while(1){
		while(Get_Str[pos] == ' ') pos ++;
		last = pos;
		while(Get_Str[pos] != ' ' && Get_Str[pos] != '\0') pos ++;
		if(Get_Str[pos] == '\0') break;
		BKDHash(keke.assign(Get_Str, last, pos - last), KEY[num+1], KEY[num+2]);
		num += 2;
	}
	GtkListStore * liststore;
	GtkTreeIter iter;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_clear(GTK_LIST_STORE(liststore));
	pGoodNode p = GoodHead->Next;
	while(p != GoodTail){
		if(Judge(p, KEY, num/2)){
			char  price[20];
			char  count[20];
			sprintf(count,"%d",p->count);
			sprintf(price,"%d",p->price);
			gtk_list_store_append(liststore, &iter);
			gtk_list_store_set (liststore, &iter, 0, (p->name).c_str(), -1);
			gtk_list_store_set (liststore, &iter, 1, (p->city).c_str(), -1);
			gtk_list_store_set (liststore, &iter, 2, (count), -1);
			gtk_list_store_set (liststore, &iter, 3, (price), -1);
			gtk_list_store_set (liststore, &iter, 4, (p->logo).c_str(), -1);
			gtk_list_store_set (liststore, &iter, 5, (p->material).c_str(), -1);
			gtk_list_store_set (liststore, &iter, 6, (p->style).c_str(),-1);
			gtk_list_store_set (liststore, &iter, 7, (p->color).c_str(), -1);
			gtk_list_store_set (liststore, &iter, 8, (p->function).c_str(), -1);
		
			p = p->Next;
		}
	}
}

void on_Main_update_clicked(GtkWidget *button,gpointer userdata){
	windowShow(GTK_WIDGET(Update));
}

void on_Update_cancel_clicked(GtkWidget *button,gpointer userdata){
	windowHide(GTK_WINDOW(Update));
}



























