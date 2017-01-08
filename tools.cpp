#include "tools.h"
#include "gtk_pubfun.h"
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
	return u->int_price < v->int_price;
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

		node->count= ary->at(2);
		BKDHash(ary->at(2),node->Hasharr[5], node->Hasharr[6]);

		node->price = ary->at(3);
		node->int_price = atoi(ary->at(3).c_str());
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
	string Aim;
	Aim = Tmp->name;
	int p1 = 0, p2 = 0, p3 = 0;
	for(int i = 0; Aim[i] != '\0'; i ++){
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

pGoodNode HashFind(char *Aim, int Status){ // 查找
	int p1 = 0, p2 = 0, p3 = 0;
	for(int i = 0; Aim[i] != '\0'; i ++){
		if(i%3 == 0) p1 += Aim[i];
		else if(i%3 == 1) p2 += Aim[i];
		else p3 += Aim[i];
	}
	p1 = (p1%53 + 53)%53;
	p2 = (p2%57 + 57)%57;
	p3 = (p3%59 + 59)%59;
	Hash *Record = HashChart[p1][p2][p3], *fft;
	if(!Record) return NULL;
	if(!strcmp(Aim, (Record->To->name).c_str())){
		if(Status) return Record->To;
		else{
			pGoodNode QAQ = Record->To;
			delete Record;
			HashChart[p1][p2][p3] = NULL;
			return QAQ;
		}
	}
	while(Record->Next){
		fft = Record->Next;
		if(!strcmp(Aim, (fft->To->name).c_str())) break;
		Record = fft;
	}
	if(Status) return Record->Next? Record->Next->To: NULL;
	else{
		pGoodNode QAQ = Record->Next->To;
		Record->Next = Record->Next->Next;
		delete Record->Next;
		return QAQ;
	}
}

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

bool Judge(pGoodNode Temp, int w[], int sum){
	if(!sum) return true;
	int record = 0;
	for(int i = 1; i <= 9; i ++){
		if(w[record*2+1] == Temp->Hasharr[i*2-1] && w[record*2+2] == Temp->Hasharr[i*2]) record ++;
		if(record == sum) break;
	}
	return record == sum;
}

void set_one_to_list(pGoodNode p){
	GtkListStore * liststore;
	GtkTreeIter iter;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_append(liststore, &iter);
		gtk_list_store_set (liststore, &iter, 0, (p->name).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 1, (p->city).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 2, (p->count).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 3, (p->price).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 4, (p->logo).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 5, (p->material).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 6, (p->style).c_str(),-1);
		gtk_list_store_set (liststore, &iter, 7, (p->color).c_str(), -1);
		gtk_list_store_set (liststore, &iter, 8, (p->function).c_str(), -1);
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
		GoodHead->int_price = 0;
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

void on_Main_sort_up_clicked(GtkWidget *button,gpointer userdata){
	time_t time1;
	time_t time2;
	time(&time1);
	if(GoodHead->int_price == 0){
		Quick_Sort(GoodHead->Next,GoodTail);
		GoodHead->int_price = 1;
	}
	pGoodNode p;
	p = GoodHead->Next;
	GtkListStore * liststore;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_clear(GTK_LIST_STORE(liststore));
	while(p != GoodTail){
		set_one_to_list(p);	
		p = p->Next;
	}
	time(&time2);
	double time = difftime(time2,time1)/10;
	const gchar cstr[] = "XXX已完成，用时：";
	g_print("%s%lf\n s",cstr,time);

}
void on_Main_sort_down_clicked(GtkWidget *button,gpointer userdata){
	if(GoodHead->int_price == 0){
		Quick_Sort(GoodHead->Next,GoodTail);
		GoodHead->int_price = 1;
	}
	GtkListStore * liststore;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_clear(GTK_LIST_STORE(liststore));
	pGoodNode p;
	p = GoodTail->Ahead;
	while(p != GoodHead){
		set_one_to_list(p);
		p = p->Ahead;
	}
}

void on_Main_search_clicked(GtkWidget *button,gpointer userdata){
	int KEY[20];
	char Get_Str[300];
	strcpy(Get_Str, gtk_entry_get_text(GTK_ENTRY(Main_key)));
	string keke;
	int num = 0, last = 0, pos = 0;
	while(1){
		while(Get_Str[pos] == ' ') pos ++;
		last = pos;
		if(Get_Str[pos] == '\0') break;
		while(Get_Str[pos] != ' ' && Get_Str[pos] != '\0') pos ++;
		BKDHash(keke.assign(Get_Str, last, pos - last), KEY[num+1], KEY[num+2]);
		num += 2;
	}
	g_print("\n");

	pGoodNode p = GoodHead->Next;
	while(p != GoodTail){
		if(Judge(p, KEY, num/2)){
			set_one_to_list(p);
		}
		p = p->Next;
	}
}


void on_Main_treeview_clicked(GtkWidget *widget,gpointer userdata){
	GtkTreeIter iter;
	GtkTreeModel * model;
	GtkTreeSelection * selection;
	gchar * coltitle;	//列名
	GtkTreeViewColumn *column;
	gchar message[2048];	//tmp：演示示例用，将所有列名称及值取出后放到这里面，然后弹出
	int ipos=0, i=0;	//tmp：演示示例用

	selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection),&model,&iter)) {
		for (i=0;i<LIST_COLNUM;i++) {
			// 获取列名称
			column = gtk_tree_view_get_column(GTK_TREE_VIEW(widget),i);
			coltitle=(gchar *)gtk_tree_view_column_get_title(column);
			ipos+=sprintf (message+ipos, "%s:", coltitle);

			//获取列的值
			char * value;
			gtk_tree_model_get (model,&iter,i,&value, -1);
			ipos+=sprintf (message+ipos, "%s\n", value);
			g_free (value);
		}
	}
	debug_popbox (message, widget, &iter);
}
void on_Update_ok_clicked(GtkWidget *button,gpointer userdata){
     GtkTreeIter iter  = {0};
     GValue value[1] = {0};
     char str[100];
     GtkTreeStore* store  = NULL;
     GtkTreeSelection* selection = NULL;
     selection = gtk_tree_view_get_selection(Main_treeview);  
     gtk_tree_selection_get_selected(selection, (GtkTreeModel**)&store, &iter);
     gtk_tree_model_get_value(GTK_TREE_MODEL(store), &iter, 0, &value[0]);
     strcpy(str, g_value_get_string(&value[0]));
     pGoodNode p = HashFind(str, 1);
     gint row;
     row = gtk_combo_box_get_active(Update_combox);
	GtkListStore * liststore;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	if(p == NULL) {g_print("NULL");}
     switch(row){
     	case 0:
     		p->name = gtk_entry_get_text(Update_input);
		gtk_list_store_set (liststore, &iter, 0, (p->name).c_str(), -1);
     		break;
     	case 1:
     		p->city = gtk_entry_get_text(Update_input);
		gtk_list_store_set (liststore, &iter, 1, (p->city).c_str(), -1);
     		break;
     	case 2:
     		p->count = gtk_entry_get_text(Update_input);
		gtk_list_store_set (liststore, &iter, 2, (p->count).c_str(), -1);
     		break;
     	case 3:
     		p->price = gtk_entry_get_text(Update_input);
		gtk_list_store_set (liststore, &iter, 3, (p->price).c_str(), -1);
     		break;
     	case 4:
     		p->logo = gtk_entry_get_text(Update_input);
		gtk_list_store_set (liststore, &iter, 4, (p->logo).c_str(), -1);
     		break;
     	case 5:
     		p->material = gtk_entry_get_text(Update_input);
		gtk_list_store_set (liststore, &iter, 5, (p->material).c_str(), -1);
     		break;
     }

}
void on_file_select_down_ok(GtkWidget * button,GtkFileSelection *fs){
	const gchar * filename;//路径或文件名

	//从参数 fs 中获取路径
	filename = gtk_file_selection_get_filename(fs);
	if (filename == NULL||strlen(filename)<5) 
		debug_popbox ("请先选择文件名称");
	else {
		GtkListStore * liststore;
		liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
		gtk_list_store_clear(GTK_LIST_STORE(liststore));
		char temp[BUFSIZE_1K];
		char str[BUFSIZE_1K];
		pGoodNode p;
		FILE *fp;
		while(fscanf(fp,"%s",temp)!=EOF){
			int i=0;
			while(temp[i] != ';' && temp[i] != '\0'){
				str[i++] = temp[i];
			}
			str[i] = '\0';
			p = HashFind(str, 0);
			pGoodNode Sr = p->Ahead, SSr = p->Next;
			Sr->Next = SSr;
			SSr->Ahead = Sr;
			delete p;
		}
		p = GoodHead->Next;
		if(!p) g_print("NULL\n");
		while(p!=GoodTail){
			set_one_to_list(p);
			p = p->Next;
		}











	gtk_widget_destroy(GTK_WIDGET(fs));	//销毁文件选则对话框 fs
}
}

void on_Main_down_clicked(GtkWidget *button,gpointer userdata){
	GtkWidget * dialog;

	//创建文件选择对话框
	dialog = gtk_file_selection_new("请选择一个文件：");
	gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
	gtk_signal_connect (GTK_OBJECT(dialog), "destroy", GTK_SIGNAL_FUNC(gtk_widget_destroy), &dialog);
	
	// 给确定按钮添加回掉函数
	g_signal_connect(
		GTK_OBJECT(GTK_FILE_SELECTION(dialog)->ok_button),
		"clicked",
		GTK_SIGNAL_FUNC(on_file_select_down_ok),
		GTK_FILE_SELECTION(dialog));

	//给取消按钮添加回掉函数
	gtk_signal_connect_object(
		GTK_OBJECT(GTK_FILE_SELECTION(dialog)->cancel_button),
		"clicked",
		GTK_SIGNAL_FUNC(gtk_widget_destroy),
		GTK_OBJECT(dialog));

	gtk_widget_show(dialog);
}



















void on_Update_cancel_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_hide(GTK_WIDGET(Update));
}
void on_file_window_cancel_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_hide(GTK_WIDGET(file_window));
}
void on_Transport_cancel_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_hide(GTK_WIDGET(Transport));
}

void on_Main_update_clicked(GtkWidget * button,gpointer userdata){
	gtk_widget_show(GTK_WIDGET(Update));
}
void on_Main_transport_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_show(GTK_WIDGET(Transport));
}






















