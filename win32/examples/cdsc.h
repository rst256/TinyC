#ifndef _C_DATA_STORE_CONTAINER_H
#define _C_DATA_STORE_CONTAINER_H

//#define DLL_EXPORT __declspec(dllexport)
//#include<stdio.h>
//#include<stdlib.h>
//#include<stdbool.h>

#ifdef _CDSC_PUBLIC_DECL
	#define CDSC_PUBDECL(D) 
#else
	#define CDSC_PUBDECL(D) D
#endif

struct dyn_list_ist{
    int val;
    struct dyn_list_ist * next;
};
typedef struct dyn_list_ist * dyn_list_it;

typedef struct {
	unsigned int count;
	unsigned int sizeof_item;
	dyn_list_it head;
	dyn_list_it curr;
} dyn_list_t;

dyn_list_it head = 0;
dyn_list_it curr = 0;

dyn_list_it* create_list(int val){
    printf("\n creating list with headnode as [%p]\n",val);
    dyn_list_it ptr = (dyn_list_it )malloc(sizeof(dyn_list_it));
    if(0 == ptr)    {
        printf("\n Node creation failed \n");
        return 0;
    }
    ptr->val = val;
    ptr->next = 0;

    head = curr = ptr;
    return ptr;
}

dyn_list_it  add_to_list(int val, int add_to_end)
{
    if(0 == head)
    {
        return (create_list(val));
    }

    if(add_to_end)
        printf("\n Adding node to end of list with value [%p]\n",val);
    else
        printf("\n Adding node to beginning of list with value [%p]\n",val);

    dyn_list_it ptr = (dyn_list_it )malloc(sizeof(dyn_list_it));
    if(0 == ptr)
    {
        printf("\n Node creation failed \n");
        return 0;
    }
    ptr->val = val;
    ptr->next = 0;

    if(add_to_end)
    {
        curr->next = ptr;
        curr = ptr;
    }
    else
    {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}

dyn_list_it  search_in_list(int val, dyn_list_it * prev)
{
    dyn_list_it ptr = head;
    dyn_list_it tmp = 0;
    int found = 0;

    printf("\n Searching the list for value [%p] \n",val);

    while(ptr != 0)
    {
        if(ptr->val == val)
        {
            found = 1;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if(1 == found)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return 0;
    }
}

int delete_from_list(int val){
    dyn_list_it prev = 0;
    dyn_list_it del = 0;

    printf("\n Deleting value [%p] from list\n",val);

    del = search_in_list(val,&prev);
    if(del == 0){
        return -1;
    }
    else
    {
        if(prev != 0)
            prev->next = del->next;

        if(del == curr)
        {
            curr = prev;
        }
        else if(del == head)
        {
            head = del->next;
        }
    }

    free(del);
    del = 0;

    return 0;
}

void print_list(void)
{
    dyn_list_it ptr = head;

    printf("\n -------Printing list Start------- \n");
    while(ptr != 0)
    {
        printf("\n [%p] \n",ptr->val);
        ptr = ptr->next;
    }
    printf("\n -------Printing list End------- \n");

    return;
}

int main(void)
{
    int i = 0, ret = 0;
    dyn_list_it ptr = 0;

    print_list();

    for(i = 5; i<10; i++)
        add_to_list(i,1);

    print_list();

    for(i = 4; i>0; i--)
        add_to_list(i, 0);

    print_list();

    for(i = 1; i<10; i += 4)
    {
        ptr = search_in_list(i, 0);
        if(0 == ptr)
        {
            printf("\n Search [val = %p] failed, no such element found\n",i);
        }
        else
        {
            printf("\n Search passed [val = %p]\n",ptr->val);
        }

        print_list();

        ret = delete_from_list(i);
        if(ret != 0)
        {
            printf("\n delete [val = %p] failed, no such element found\n",i);
        }
        else
        {
            printf("\n delete [val = %p]  passed \n",i);
        }

        print_list();
    }

    return 0;
}

DLL_EXPORT void HelloWorld (void)
{
    //MessageBox (0, "Hello World!", "From DLL", MB_ICONINFORMATION);
}
#endif // _C_DATA_STORE_CONTAINER_H