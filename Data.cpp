bool Cmp(pGoodNode u, pGoodNode v){ // 判断
	return u->jg < v->jg;
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

void BKDHash(string Aim, int &u, int &v){ // 字符串哈希
	int HH1 = 0, HH2 = 0, seed1 = 137, seed2 = 131;
	for(int i = 0; Aim[i]; i ++){
		HH1 = HH1*seed1 + Aim[i];
		HH2 = HH2*seed2 + Aim[i];
	}
	u = HH1 & 0x7fffffff;
	v = HH2 & 0x7fffffff;
}

void Add(pGoodNode keke, pGoodNode Tail){ // 增加链表
	pGoodNode Tmp = Tail->Ahead;
	Tmp->Next = keke;
	keke->Next = Tail;
	Tail->Ahead = keke;
	keke->Ahead = Tmp;
}

void Delete(pGoodNode Tmp){ // 删除链表
	pGoodNode u = Tmp->Ahead, v = Tmp->Next;
	u->Next = v;
	v->Ahead = u;
	delete Tmp;
}

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
	HashChart[p1][p2][p3] = new Hash(Tmp, HashChart[p1][p2][p3]);
}

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
	Hash TT = HashChart[p1][p2][p3];
	if(TT != NULL){
		while(TT != NULL){
			if(Aim == TT->To->name){
				break;
			}
			TT = TT->Next;
		}
	}
	return TT;
}

void Free_Hash(){ // 释放哈希
	Hash p1, p2;
	for(int i = 0; i < 53; i ++){
		for(int j = 0; j < 57; j ++){
			for(int k = 0; k < 59; k ++){
				if(HashChart[i][j][k] == NULL) continue;
				p1 = HashChart[i][j][k];
				HashChart[i][j][k] = NULL;
				while(p1 != NULL){
					p2 = p1->Next;
					Delete p1;
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
	Tail->Ahead = Begin;
}
