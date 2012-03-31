#include <stdio.h>
#include <stdlib.h>

struct _node;
typedef struct _node * Linked_List;
typedef struct _node{
    unsigned short value;
    Linked_List next;
} Node;
typedef Linked_List Natural;

Linked_List create(){
    return NULL;
}

void destroy(Linked_List * p){
    Linked_List tmp, list = *p;
    while(list){
        tmp = list->next;
        free(list);
        list = tmp;
    }
    *p = NULL;
}

Linked_List mknode(unsigned short v, Linked_List next){
    Linked_List ret = malloc(sizeof(struct _node));
    ret->value = v;
    ret->next = next;
    return ret;
}

int is_empty(Linked_List l){
    return l==NULL;
}

int contains(Linked_List l, unsigned short v){
    return l && (l->value == v || contains(l->next, v));
}

int length(Linked_List l){
    return l?1+length(l->next):0;
}

int insert(Linked_List * l, int pos, unsigned short v){
    if(pos){
        return l && insert(&(*l)->next, pos-1, v);
    }else{
        *l = mknode(v, *l);
        return 1;
    }
}

int list_remove(Linked_List * l, int pos){
    if(pos){
        return l && list_remove(&(*l)->next, pos-1);
    }else{
        Linked_List tmp = (*l)->next;
        *l = (*l)->next;
        free(tmp);
    }

}

unsigned short getElement(Linked_List l, int pos){
    return pos?getElement(l->next, pos-1):l->value;
}

Natural assign(unsigned long v){
    Natural res = NULL;
    while(v > 0){
        res = mknode(v%10, res);
        v /= 10;
    }
    return res;
}

void print(Natural n){
    if(n){
        printf("%d --> ", n->value);
        print(n->next);
    }else{
        printf("NULL\n");
    }
}

void show(Natural n){
    if(n){
        printf("%d", n->value);
        show(n->next);
    }else{
        printf("\n");
    }
}

void erase(Natural n){
    destroy(&n);
}

int is_greater(Natural a, Natural b){
    int la = length(a), lb = length(b);

    if(la < lb){
        return 0;
    }else if(la > lb){
        return 1;
    }else{
        while(a && a->value == b->value){
            a = a->next;
            b = b->next;
        }
        return a && a->value > b->value;
    }
}

Natural copy_reverse(Natural old) {
    Natural res = create();
    while(old) {
        res = mknode(old->value, res);
        old = old->next;
    }
    return res;
}

Natural add(Natural a, Natural b){
    Natural ar = copy_reverse(a), br = copy_reverse(b), borig = br, aorig = ar;
    Natural res = create();
    int carry = 0, val;
    while(ar || br || carry){
        val = (ar?ar->value:0) + (br?br->value:0) + carry;
        carry = 0;
        if(val >= 10){
            val = val%10;
            carry = 1;
        }
        res = mknode(val, res);
        ar = ar?ar->next:NULL;
        br = br?br->next:NULL;
    }
    erase(aorig);
    erase(borig);
    return res;
}

Natural normalizate(Natural n){
    while(n && n->value == 0){
        Natural tmp = n->next;
        free(n);
        n = n->next;
    }
    return n;
}

Natural sub(Natural a, Natural b){
    if(is_greater(b,a)){
        return create();
    }
    Natural ar = copy_reverse(a), br = copy_reverse(b), borig = br, aorig = ar;
    Natural res = create();
    int carry = 0, val;
    while(ar){
        val = 10 + ar->value - (br?br->value:0) - carry;
        carry = 0;
        if(val < 10){
            carry = 1;
        }else{
            val = val%10;
        }
        res = mknode(val, res);
        ar = ar->next;
        br = br?br->next:NULL;
    }
    erase(aorig);
    erase(borig);
    return normalizate(res);
}

Natural mul(Natural n1, Natural n2){
    Natural res = assign(0), one = assign(1), cnt=add(n2,NULL), tmp;
    while(cnt){
        tmp = add(res, n1);
        erase(res);
        res = tmp;
        tmp = sub(cnt, one);
        erase(cnt);
        cnt = tmp;
    }
    erase(one);
    return res;
}

Natural fact(unsigned long n){
    Natural res = assign(1), tmpa, tmpb;
    while(n){
        tmpa = assign(n--);
        tmpb = mul(res, tmpa);
        erase(tmpa);
        erase(res);
        res = tmpb;
    }
}

void main(){
    print(mknode(20,mknode(10,NULL)));
    show(fact(200));
}

