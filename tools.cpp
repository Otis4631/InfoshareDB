#include "h/tools.h"
#include "h/gtk_pubfun.h"
void BKDHash(string Aim, int &u, int &v){ // 字符串哈希
	int HH1 = 0, HH2 = 0, seed1 = 137, seed2 = 131;
	for(int i = 0; Aim[i]; i ++){
		HH1 = HH1*seed1 + Aim[i];
		HH2 = HH2*seed2 + Aim[i];
	}
	u = HH1 & 0x7fffffff;
	v = HH2 & 0x7fffffff;
}
//--------------------------------声明所有货物头尾指针链表-------------------------------
extern pGoodNode GoodHead,GoodTail;
extern pGoodNode P;
//---------------------------------------------*********************排序***************-----------------------------------------------
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

//----------------------------------------------建立哈希表,Hash查找------------------------------------------------------
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
//----------------------------------------------Hash查找结束------------------------------------------------------------
bool Judge(pGoodNode Temp, int w[], int sum){
	if(!sum) return true;
	int record = 0;
	for(int i = 1; i <= 9; i ++){
		if(w[record*2+1] == Temp->Hasharr[i*2-1] && w[record*2+2] == Temp->Hasharr[i*2]) record ++;
		if(record == sum) break;
	}
	return record == sum;
}

void set_one_to_list(pGoodNode p){ 	//根据链表节点更新一条信息。
	GtkListStore * liststore;
	GtkTreeIter iter;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_append(liststore, &iter);
		gtk_list_store_set (liststore, &iter,
				    0, (p->name).c_str(),
				    1, (p->city).c_str(),
				    2, (p->count).c_str(),
				    3, (p->price).c_str(),
				    4, (p->logo).c_str(),
				    5, (p->material).c_str(),
				    6, (p->style).c_str(),
				    7, (p->color).c_str(),
				    8, (p->function).c_str(),
				    -1);
	
}
/*--------------------------------Main_system_init--------------------------*/
void on_Main_system_init_clicked(GtkWidget * button,gpointer userdata){
	gtk_widget_show(GTK_WIDGET(file_window));
}

void on_file_window_ok_clicked(GtkWidget *button,gpointer userdata){
	struct timeval stime,etime;
	float time;
	gettimeofday(&stime,NULL);
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
		pGoodNode p;
		Sequence = 1;
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
		}
		P = Sequence? GoodHead->Next: GoodTail->Ahead;
		p = P;		
		int gg = 0;
		while(gg < 20){
			if(Sequence && p == GoodTail) break;
			else if(!Sequence && p == GoodHead) break;
			set_one_to_list(p);
			p = Sequence? p->Next: p->Ahead;
			gg ++;
		}
		gettimeofday(&etime,NULL);
		time = 1000000*(etime.tv_sec - stime.tv_sec) + (etime.tv_usec - stime.tv_usec);
		time /= 1000000;
		const gchar cstr[] = "初始化已完成，用时：";
		g_print("%s%fs\n",cstr,time);
	}
	debug_popbox("系统初始化完成！");
	gtk_widget_hide(GTK_WIDGET(file_window));
}
/*********************************************系统初始化结束****************************************/
//---------------------------------价格升序排列------------------------------------------------------
void on_Main_sort_up_clicked(GtkWidget *button,gpointer userdata){
	struct  timeval stime,etime;
	float time;
	gettimeofday(&stime,NULL);
	if(GoodHead->int_price == 0){
		Quick_Sort(GoodHead->Next,GoodTail);
		GoodHead->int_price = 1;
	}
	Sequence = true;
	GtkListStore * liststore;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_clear(GTK_LIST_STORE(liststore));
	Sequence = true;
	P = GoodHead->Next;
	pGoodNode p = P;
	int gg = 0;
	while(gg < 20){
		if(p == GoodTail) break;
		set_one_to_list(p);
		p = p->Next;
		gg ++;
	}
	gettimeofday(&etime,NULL);
	time = 1000000*(etime.tv_sec - stime.tv_sec) + (etime.tv_usec - stime.tv_usec);
	time /= 1000000;
	const gchar cstr[] = "升序已完成，用时：";
	g_print("%s%fs\n",cstr,time);

}
//--------------------------------价格降序排列---------------------------------------------------------
void on_Main_sort_down_clicked(GtkWidget *button,gpointer userdata){
	struct timeval stime,etime;
	float time;
	gettimeofday(&stime,NULL);
	if(GoodHead->int_price == 0){
		Quick_Sort(GoodHead->Next,GoodTail);
		GoodHead->int_price = 1;
	}
	Sequence = false;
	GtkListStore * liststore;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_clear(GTK_LIST_STORE(liststore));
	Sequence = false;
	P = GoodTail->Ahead;
	pGoodNode p = P;
	int gg = 0;
	while(gg < 20){
		if(!Sequence && p == GoodHead) break;
		set_one_to_list(p);
		p = p->Ahead;
		gg ++;
	}
	gettimeofday(&etime,NULL);
	time = 1000000*(etime.tv_sec - stime.tv_sec) + (etime.tv_usec - stime.tv_usec);
	time /= 1000000;
	const gchar cstr[] = "降序已完成，用时：";
	g_print("%s%fs\n",cstr,time);
}
//------------------------------查找-----------------------------------------------------------------
void on_Main_search_clicked(GtkWidget *button,gpointer userdata){
	struct timeval stime,etime;
	float time;
	gettimeofday(&stime,NULL);
	int KEY[20];
	char Get_Str[300];
	strcpy(Get_Str, gtk_entry_get_text(GTK_ENTRY(Main_key)));
	GtkListStore * liststore;
	liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	gtk_list_store_clear(GTK_LIST_STORE(liststore));
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
	P = Sequence? GoodHead->Next: GoodTail->Ahead;
	pGoodNode p = P;
	int gg = 0;
	while(gg < 20){
		if(Sequence && p == GoodTail) break;
		else if(!Sequence && p == GoodHead) break;
		if(Judge(p, KEY, num/2)){
			set_one_to_list(p);
			gg ++;
		}
		p = Sequence? p->Next: p->Ahead;
	}
	gettimeofday(&etime,NULL);
	time = 1000000*(etime.tv_sec - stime.tv_sec) + (etime.tv_usec - stime.tv_usec);
	time /= 1000000;
	const gchar cstr[] = "搜索已完成，用时：";
	g_print("%s%fs\n",cstr,time);d
}
//-------------------------双击TreeView显示基本信息-----------------------------------------
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
     char str[100] ;
     GtkTreeStore* store  = NULL;
     GtkTreeSelection* selection = NULL;
     selection = gtk_tree_view_get_selection(Main_treeview);  
     gtk_tree_selection_get_selected(selection, (GtkTreeModel**)&store, &iter);
     gtk_tree_model_get_value(GTK_TREE_MODEL(store), &iter, 0, &value[0]);
     strcpy(str, g_value_get_string(&value[0]));
     pGoodNode p = HashFind(str, 1);
     gint row;
     row = gtk_combo_box_get_active(Update_combox);
     if(row == -1)
     {
     	debug_popbox("请先选择需要更新的条目！");
     }
     else{
	 GtkListStore * liststore;
	 liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
	 update_to_list (GTK_WIDGET(liststore),&iter, row, gtk_entry_get_text(Update_input));
	 gtk_widget_hide(GTK_WIDGET(Update));
     
     }
}
void on_file_select_down_ok(GtkWidget * button,GtkFileSelection *fs){
	struct timeval stime,etime;
	float time;
	gettimeofday(&stime,NULL);

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
		FILE *fp = fopen(filename,"r");
		while(fscanf(fp,"%s",temp)!=EOF){
			int i=0;
			while(temp[i] != ';' && temp[i] != '\0'){
				str[i++] = temp[i];
			}
			str[i] = '\0';
			p = HashFind(str, 0);
			if(p == NULL) continue;
			pGoodNode Sr = p->Ahead, SSr = p->Next;
			Sr->Next = SSr;
			SSr->Ahead = Sr;
			delete p;
		}
		if(GoodHead->Next != GoodTail){	
			P = Sequence? GoodHead->Next: GoodTail->Ahead;
			p = P;
			int gg = 0;
			while(gg < 20){
				if(Sequence && p == GoodTail) break;
				else if(!Sequence && p == GoodHead) break;
				set_one_to_list(p);
				p = Sequence? p->Next: p->Ahead;
				gg ++;
			}
		}
		gtk_widget_destroy(GTK_WIDGET(fs));	//销毁文件选则对话框 fs}
	}
	gettimeofday(&etime,NULL);
	time = 1000000*(etime.tv_sec - stime.tv_sec) + (etime.tv_usec - stime.tv_usec);
	time /= 1000000;
	const gchar cstr[] = "下架已完成，用时：";
	g_print("%s%fs\n",cstr,time);
}
void on_file_select_up_ok(GtkWidget * button,GtkFileSelection *fs){
	struct timeval stime,etime;
	float time;
	gettimeofday(&stime,NULL);
	const gchar * filename;//路径或文件名
	//从参数 fs 中获取路径
	filename = gtk_file_selection_get_filename(fs);
	if (filename == NULL||strlen(filename)<5) 
		debug_popbox ("请先选择文件名称");
	else {
		vector<string> ary;
		GtkListStore * liststore;
		liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Main_treeview)));
		gtk_list_store_clear(GTK_LIST_STORE(liststore));
		pGoodNode p;
		FILE *fp =	fopen(filename,"r");
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
		}
		P = Sequence? GoodHead->Next: GoodTail->Ahead;
		p = P;
	
		int gg = 0;
		while(gg < 20){
			if(Sequence && p == GoodTail) break;
			else if(!Sequence && p == GoodHead) break;
			set_one_to_list(p);
			p = Sequence? p->Next: p->Ahead;
			gg ++;
		}
	}
	gtk_widget_destroy(GTK_WIDGET(fs));	//销毁文件选则对话框 fs
	gettimeofday(&etime,NULL);
	time = 1000000*(etime.tv_sec - stime.tv_sec) + (etime.tv_usec - stime.tv_usec);
	time /= 1000000;
	const gchar cstr[] = "下架已完成，用时：";
	g_print("%s%lfs\n",cstr,time);
}
void on_Main_up_clicked(GtkWidget *button,gpointer userdata){
	GtkWidget * dialog;
	//创建文件选择对话框
	dialog = gtk_file_selection_new("请选择一个文件：");
	gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
	gtk_signal_connect (GTK_OBJECT(dialog), "destroy", GTK_SIGNAL_FUNC(gtk_widget_destroy), &dialog);
	
	// 给确定按钮添加回掉函数
	g_signal_connect(
		GTK_OBJECT(GTK_FILE_SELECTION(dialog)->ok_button),
		"clicked",
		GTK_SIGNAL_FUNC(on_file_select_up_ok),
		GTK_FILE_SELECTION(dialog));

	//给取消按钮添加回掉函数
	gtk_signal_connect_object(
		GTK_OBJECT(GTK_FILE_SELECTION(dialog)->cancel_button),
		"clicked",
		GTK_SIGNAL_FUNC(gtk_widget_destroy),
		GTK_OBJECT(dialog));

	gtk_widget_show(dialog);
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
//******************************************物流
 int Cost[25][25][3];
 int  Time[25][25][3];
void on_Transport_search_clicked (GtkWidget *button,gpointer userdata)
{
  freopen("./in/datain", "r", stdin);
    const gchar *City1 = gtk_entry_get_text(GTK_ENTRY(Transport_city1));
    const gchar *City2 = gtk_entry_get_text(GTK_ENTRY(Transport_city2));

    int city1=City1[0]-'0'-17;   //char 变 int,A变0
    int city2=City2[0]-'0'-17;

    if(city1<0||city1>17||city2<0||city2>17||City1==NULL||City2==NULL)
      {
	debug_popbox("没有该城市！");
	return ;
      }
    if(city1==city2)
      {
	 gtk_entry_set_text(Transport_time,"0.0");
         gtk_entry_set_text(Transport_cost,"0.0");
	 gtk_entry_set_text(Transport_c_route,City1);
	 gtk_entry_set_text(Transport_t_route,City2);
	 return ;
      }
    const int inf = 0x3f3f3f3f;
    memset(Cost, inf, sizeof( Cost));
    memset(Time, inf, sizeof( Time));

    for(int i=0;i<108;i++)  //108个数据
    {
        double time;
  	int cost,u,v;
	char U,V;
        cin>>U>>V>>cost>>time;
	u=U-'0'-17;v=V-'0'-17;
	Cost[u][v][0]=Cost[v][u][0]=cost;
	Time[u][v][1]=Time[v][u][1]=(int)(time*10);

     }

      for(int k = 0; k <17; k ++){
        for(int i = 0; i <17; i ++){
            for(int j = 0; j <17; j ++){
                if(Cost[i][j][0] > Cost[i][k][0] + Cost[k][j][0])
		  {
                    Cost[i][j][0] = Cost[i][k][0] + Cost[k][j][0];
                    //Cost[i][j][1] = Cost[i][k][1] + Cost[k][j][1];
                    Cost[i][j][2] = k;
		  }
            }
        }
    }
    for(int k = 0; k <17; k ++){
        for(int i = 0; i <17; i ++){
            for(int j = 0; j <17; j ++){
                if(Time[i][j][1] > Time[i][k][1] + Time[k][j][1])
		{
		  //Time[i][j][0] = Time[i][k][0] + Time[k][j][0];
                    Time[i][j][1] = Time[i][k][1] + Time[k][j][1];
                    Time[i][j][2] = k;
                }
            }
        }
    }
    cout<< Time[city1][city2][1]<<" "<<Cost[city1][city2][0]<<endl;
    gtk_entry_set_text(Transport_c_route,"");
    gtk_entry_set_text(Transport_t_route,"");
    if(Time[city1][city2][1]==inf||Cost[city1][city2][0]==inf)
      {	
	debug_popbox("该城市道路不通！");
	return ;
      }
    char c1[20],c2[20],c3[20];
    c1[2]=Time[city1][city2][1]%10;
    sprintf(c1, "%d", Time[city1][city2][1]/10);
    sprintf(c3, "%d", Time[city1][city2][1]%10);
    sprintf(c2, "%d", Cost[city1][city2][0]);
    gtk_entry_set_text(Transport_time,c1);
    gtk_entry_append_text(Transport_time,".");
    gtk_entry_append_text(Transport_time,c3);
    gtk_entry_set_text(Transport_cost,c2);
    cout<<"entrymin"<<endl;

    gtk_entry_append_text(Transport_c_route,City1);
    DisplayPath1(city1,city2);//花费
    gtk_entry_append_text(Transport_c_route,City2);

    gtk_entry_append_text(Transport_t_route,City1);
    DisplayPath2(city1,city2);//时间
    gtk_entry_append_text(Transport_t_route,City2);
    cout<<"enddisplay"<<endl;
}
void DisplayPath1(int u,int v)
{
  const int inf=0x3f3f3f3f;
  if(Cost[u][v][2]==inf)
    return ;
  else
    {  
        DisplayPath1(u, Cost[u][v][2]);  
        cout << Cost[u][v][2];
        char f[2];
        f[0]=(char)(Cost[u][v][2]+17+48);
	f[1]='\0';
       gtk_entry_append_text(Transport_c_route,f);
       DisplayPath1(Cost[u][v][2],v);
    }  
}
void DisplayPath2(int u,int v)
{
  const int inf=0x3f3f3f3f;
  if(Time[u][v][2]==inf)
    return ;
  else
    {  
        DisplayPath2(u, Time[u][v][2]);  
        cout << Time[u][v][2];
        char f[2];
        f[0]=(char)(Time[u][v][2]+17+48);
	f[1]='\0';
       gtk_entry_append_text(Transport_t_route,f);
       DisplayPath2(Time[u][v][2],v);
    }  
}

void on_Main_pgdown_clicked (GtkWidget *button,gpointer userdata){
	char Get_Str[300];
	strcpy(Get_Str, gtk_entry_get_text(GTK_ENTRY(Main_key)));
	string keke;
	int num = 0, last = 0, pos = 0, KEY[20], gg = 0;
	while(1){
		while(Get_Str[pos] == ' ') pos ++;
		last = pos;
		if(Get_Str[pos] == '\0') break;
		while(Get_Str[pos] != ' ' && Get_Str[pos] != '\0') pos ++;
		BKDHash(keke.assign(Get_Str, last, pos - last), KEY[num+1], KEY[num+2]);
		num += 2;
	}
	pGoodNode p = P;
	while(gg < 20){
		if(Sequence && p != GoodTail) break;
		else if(!Sequence && p != GoodHead) break;
		if(Judge(p, KEY, num/2)) gg ++;
		p = Sequence? p->Next: p->Ahead;
	}
	if(gg < 20){
		debug_popbox("已经到最后一页！");
		return;
	}
	pGoodNode record = p;
	gg = 0;
	while(gg < 20){
		if(Sequence && p != GoodTail) break;
		else if(!Sequence && p != GoodHead) break;
		if(Judge(p, KEY, num/2))gg ++;
		p = Sequence? p->Next: p->Ahead;
	}
	if(gg == 0){
		debug_popbox("已经到最后一页！");
		record = NULL;
		return;
	}
	gtk_list_store_clear(GTK_LIST_STORE(liststore1));
	P = p = record;
	gg = 0;
	while(gg < 20){
		if(Sequence && p != GoodTail) break;
		else if(!Sequence && p != GoodHead) break;
		if(Judge(p, KEY, num/2)){
			set_one_to_list(p);
			gg ++;
		}
		p = Sequence? p->Next: p->Ahead;
	}
}
void on_Main_pgup_clicked (GtkWidget *button,gpointer userdata){
	char Get_Str[300];
	strcpy(Get_Str, gtk_entry_get_text(GTK_ENTRY(Main_key)));
	string keke;
	int num = 0, last = 0, pos = 0, KEY[20], gg = 0;
	while(1){
		while(Get_Str[pos] == ' ') pos ++;
		last = pos;
		if(Get_Str[pos] == '\0') break;
		while(Get_Str[pos] != ' ' && Get_Str[pos] != '\0') pos ++;
		BKDHash(keke.assign(Get_Str, last, pos - last), KEY[num+1], KEY[num+2]);
		num += 2;
	}
	pGoodNode p = P;
	while(gg < 20){
		if(Sequence && p != GoodTail) break;
		else if(!Sequence && p != GoodHead) break;
		if(Judge(p, KEY, num/2)) gg ++;
		p = Sequence? p->Ahead: p->Next;
	}
	if(gg < 20){
		debug_popbox("已经到最后一页！");
		return;
	}
	pGoodNode record = p;
	gg = 0;
	while(gg < 20){
		if(Sequence && p != GoodTail) break;
		else if(!Sequence && p != GoodHead) break;
		if(Judge(p, KEY, num/2)) gg ++;
		p = Sequence? p->Next: p->Ahead;
	}
	if(!gg){
		debug_popbox("已经到最后一页！");
		return;
	}
	P = p = record;
	while(gg < 20){
		if(Sequence && p != GoodTail) break;
		else if(!Sequence && p != GoodHead) break;
		if(Judge(p, KEY, num/2)){
			set_one_to_list(p);
			gg ++;
		}
		p = Sequence? p->Next: p->Ahead;
	}
}










void on_Transport_cancel_clicked(GtkWidget *button, gpointer userdata){
    	gtk_widget_hide(GTK_WIDGET(Transport));
}
void on_Update_cancel_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_hide(GTK_WIDGET(Update));
}
void on_file_window_cancel_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_hide(GTK_WIDGET(file_window));
}
void on_Main_update_clicked(GtkWidget * button,gpointer userdata){
	gtk_widget_show(GTK_WIDGET(Update));
}
void on_Main_transport_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_show(GTK_WIDGET(Transport));
}
void on_Main_about_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_show(GTK_WIDGET(About));
}
void on_About_ok_clicked(GtkWidget *button,gpointer userdata){
	gtk_widget_hide(GTK_WIDGET(About));
}

