#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;
typedef long double f80;

typedef struct Pointer {
    u32 Dim;
    size_t *Length;
    size_t Size;
    void *Ptr;
    void (*func)(void *Data);
} Pointer;

s8 Bounce(size_t Size,int index){
    if(index>=0&&index<Size) return 1;
    return 0;
}

void FillBuffer(void **Branch,u32 Dim,size_t *Length,size_t Size){
    size_t length = 1;
    for(int i = 0;i<Dim;i++){
        length *= Length[i];
    }
    (*Branch) = (void*)calloc(length,Size);
    if(!(*Branch)){
        printf("Couldn't allocate Buffer!\n");
    }else{
        printf("Buffer created!\n");
    }
}

void DestroyBranch(void **Branch,u32 Dim,size_t *Length){
    if((*Branch)) free((*Branch));
    if(!(*Branch)){
        printf("Couldn't free Buffer!\n");
    }else{
        printf("Buffer freed!\n");
    }
}

void KillPointer(Pointer *P){
    printf("Kill Pointer:\n");
    DestroyBranch(&P->Ptr,P->Dim,P->Length);
    printf("End Pointer:\n");
}

Pointer GetPointer(u32 Dim,size_t Length[],size_t Size,void (*func)(void *Data)){
    Pointer p;
    p.Dim = Dim;
    p.Length = Length;
    p.Size = Size;
    p.func = func;
    printf("Init:\n");
    FillBuffer(&p.Ptr,Dim,Length,Size);
    printf("Done:\n");
    return p;
}

void* GetBranch(void **Branch,u32 Dim,u32 Index[],size_t Length[],u32 Size){
    u32 index = 0;
    index += Index[0] * Size;
    for(int i = 1;i<Dim;i++){
        index += Index[i] * Size * Length[i-1];
    }
    return &(((char*)(*Branch))[index]);
}

void* GetItem(Pointer *p,u32 Index[]){
    printf("Get Element: ");
    for(int i = 0;i<p->Dim;i++){
        printf("%i ",(int)Index[i]);
    }
    printf(" \n");

    int i = 0;
    for(;i<p->Dim;i++){
        if(!(Index[i]>=0&&Index[i]<p->Length[i])){
            break;
        }
    }
    if(i==p->Dim) return GetBranch(&p->Ptr,p->Dim,Index,p->Length,p->Size);
    else printf("Get: Index out of Bounce Exception");
    return NULL;
}

void SetBranch(void **Branch,u32 Dim,u32 Index[],size_t Length[],u32 Size,void *Item){
    u32 index = 0;
    index += Index[0] * Size;
    for(int i = 1;i<Dim;i++){
        index += Index[i] * Size * Length[i-1];
    }
    for(int i = 0;i<Size;i++){
        ((char*)(*Branch))[index+i] = ((char*)Item)[i];
    }
}

void* SetItem(Pointer *p,u32 Index[],void *Item){
    printf("Get Element: ");
    for(int i = 0;i<p->Dim;i++){
        printf("%i ",(int)Index[i]);
    }
    printf(" \n");

    int i = 0;
    for(;i<p->Dim;i++){
        if(!(Index[i]>=0&&Index[i]<p->Length[i])){
            break;
        }
    }
    if(i==p->Dim) SetBranch(&p->Ptr,p->Dim,Index,p->Length,p->Size,Item);
    else printf("Get: Index out of Bounce Exception");
}

void PrintPointer(Pointer *P){
    size_t size = 1;
    for(int i = 0;i<P->Dim;i++){
        size *= P->Length[i];
    }
    for(int i = 0;i<size;i++){
        P->func(&((char*)P->Ptr)[i*P->Size]);
    }
}
